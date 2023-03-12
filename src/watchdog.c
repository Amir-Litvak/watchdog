#define _POSIX_C_SOURCE (200112L)
#include <assert.h> /* assert */
#include <stdio.h> /* print testing purposes, will be deleted afterwards. */
#include <pthread.h> /* threads */
#include <unistd.h>    /* fork and execpv */
#include <sys/wait.h>  /* waitpid */
#include <sys/types.h> /* pid_t */
#include <stdlib.h>    /* exit */
#include <stdatomic.h> /* atomic var */
#include <string.h> /* memset */
#include <signal.h> /* signals */

#include "scheduler.h"
#include "semaphores.h"
#include "WatchDog.h"

#define CHILD (0)
#define NO_OVERWRITE (0)
#define FORK_FAILED (-1)
#define SEM_FAILED (-1)
#define PID_LEN (15)
#define T_INTERVAL (2)
#define ENV_NAME ("PROC_PID")
#define WD_EXEC ("./WatchDog_proc.out")

enum status
{
    SUCCESS = 0,
    FAIL
};

enum modes
{
    CLIENT = 0,
    WD_PROC
};

enum flag
{
    OFF = 0,
    ON
};

atomic_int g_counter = 0;
atomic_int g_stop_flag = OFF;
atomic_int g_mode = 0;

static semid_t g_client_semaphore = 0;
static semid_t g_wd_semaphore = 0;

pid_t g_opposite_pid = 0;

static void SigHandler1(int signo);
static void SigHandler2(int signo);
static void *WDWatcher(void *arg);
static int SignalTask(void *param);
static void CleanUpFunc(void *param);
static int SetUpDogs(void *pack);
static int RebootTask(void *param);
static int InitSemaphores(void);
static int InitSignals(void);
static int StopTask(void *param);
static void RebootSequence(char **argv);
static int SetUp(void);

int StartWD(char *argv[])
{
    if(SUCCESS != SetUp())
    {
        return FAIL;
    }
    
    if(SUCCESS != SetUpDogs(argv))
    {
        return FAIL;
    }

    return SUCCESS;
}

void StopWD(void)
{
    printf("\n\nSTARTING StopWD\n\n");
    
    /*kill(getpid(), SIGUSR2); - IS THE OTHER BETTER?*/
    kill(atoi(getenv(ENV_NAME)), SIGUSR2);
    /*unsetenv(ENV_NAME);*/
}

static int SetUpDogs(void *pack)
{
    pid_t wd_pid = 0;
    pthread_t wd_thread = 0;
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    if(CLIENT == g_mode)
    {   
        wd_pid = fork();

        if(CHILD == wd_pid)
        {
            execvp(WD_EXEC, pack);
            return FAIL;
        }
        else if (FORK_FAILED == wd_pid)
        {
            return FAIL;
        }

        SemDecrement(g_client_semaphore, 1, 0);
        
        g_opposite_pid = wd_pid;
        if(SUCCESS != pthread_create(&wd_thread, &attr, WDWatcher, pack))
        {
            return FAIL;
        }
    }
    else if(WD_PROC == g_mode)
    {
        SemIncrement(g_client_semaphore, 1, 0);
        g_opposite_pid = getppid();
        WDWatcher(pack);
    }  

    return SUCCESS;
}

static void *WDWatcher(void *arg)
{
    sched_t *dw_sched = NULL;
    task_uid_t task1 = UIDBadUID;
    task_uid_t task2 = UIDBadUID;
    task_uid_t task3 = UIDBadUID;

    dw_sched = SchedCreate();
    if(NULL == dw_sched)
    {
        return NULL;
    }

    task1 = SchedAddTask(dw_sched, SignalTask, NULL, 
                    CleanUpFunc, NULL, time(NULL) + (T_INTERVAL));

    task2 = SchedAddTask(dw_sched, StopTask, dw_sched, 
                    CleanUpFunc, NULL, time(NULL) + (T_INTERVAL+1));

    task3 = SchedAddTask(dw_sched, RebootTask, arg, 
                    CleanUpFunc, NULL, time(NULL) + (T_INTERVAL+2));

    
    if(CLIENT == g_mode)
    {
        SemIncrement(g_client_semaphore, 1, 0);
        while (1 != SemGetVal(g_wd_semaphore))
        {
        }
    }
    else
    {
        SemIncrement(g_wd_semaphore, 1, 0);
        while (1 != SemGetVal(g_client_semaphore))
        {
        }
    }

    printf("\n\n STARTING SCHED RUN at pid:%d\n\n", getpid());
    SchedRun(dw_sched);

	SchedDestroy(dw_sched);

    return arg;
}

/********************** TASK FUNCS ***********************/

static int SignalTask(void *param)
{
    printf("signal task: g_stop_flag is (1 on ,0 off): %d at pid: %d\n", g_stop_flag, getpid());
    
    ++g_counter;
    kill(g_opposite_pid, SIGUSR1);
    printf("#######SIG1SENT to:|%d|###\n", g_opposite_pid);

	return T_INTERVAL;
}

static int RebootTask(void *param)
{
    printf("check task: g_counter is: %d at pid: %d\n", g_counter, getpid());

	if(10 < g_counter)
    {
        g_counter = 0;

        RebootSequence(param);
    }
	
	return (T_INTERVAL);
}

static int StopTask(void *param)
{
    sched_t *sched = (sched_t *)param;

    printf("stop task: g_stop_flag is (1 on ,0 off): %d at pid: %d\n", g_stop_flag, getpid());

    if(ON == g_stop_flag)
    {
        printf("\n\n SENDING SIGUSR2 TO: %d\n\n", g_opposite_pid);
        kill(g_opposite_pid, SIGUSR2);
        SchedStop(sched);
        return SUCCESS;
    }

	return T_INTERVAL;
}

static void CleanUpFunc(void *param)
{
	(void)param;
    SemDestroy(g_client_semaphore);
    SemDestroy(g_wd_semaphore);
    unsetenv(ENV_NAME);
}
/*********************************************************/

/*********************** AUX FUNCS ***********************/

static int SetUp(void)
{
    char client_pid[PID_LEN] = {0};
    
    if(FAIL == InitSemaphores())
    {
        return FAIL;
    }

    if(FAIL == InitSignals())
    {
        return FAIL;
    }

    sprintf(client_pid, "%d", getpid());
    
    if(SUCCESS != setenv(ENV_NAME, client_pid, NO_OVERWRITE))
    {
        return FAIL;
    }

    if(0 == strcmp(getenv(ENV_NAME), client_pid))
    {
        g_mode = CLIENT;
    }
    else
    {
        g_mode = WD_PROC;
    }

    return SUCCESS;
}

static void RebootSequence(char **argv)
{
    pid_t child_pid = 0;
    
    if(CLIENT == g_mode)
    {
        child_pid = fork();
        if(CHILD == child_pid)
        {
            execvp(WD_EXEC, argv);
        }
    }
    else
    {
        unsetenv(ENV_NAME);
        execvp(argv[0], argv);
    }

    g_opposite_pid = child_pid;
}

static int InitSemaphores(void)
{
    g_client_semaphore = SemCreate("client", 0 ,0);
    if(SEM_FAILED == g_client_semaphore)
    {
        return FAIL;
    }

    g_wd_semaphore = SemCreate("wd", 0 ,0);
    if(SEM_FAILED == g_wd_semaphore)
    {
        return FAIL;
    }

    return SUCCESS;
}

static int InitSignals(void)
{
    struct sigaction sa1;
    struct sigaction sa2;

    memset(&sa1, 0, sizeof(sa1));
    sa1.sa_handler = &SigHandler1;
        
    memset(&sa2, 0, sizeof(sa2));
    sa2.sa_handler = &SigHandler2;
        
    if (sigaction(SIGUSR1, &sa1, NULL))
    {
            return FAIL;
    }

    if (sigaction(SIGUSR2, &sa2, NULL))
    {
            return FAIL;
    }

    return SUCCESS;
}

/*********************************************************/

/******************** SIGNAL HANDLERS ********************/

static void SigHandler1(int signo)
{
    (void)signo;
    g_counter = 0;
}

static void SigHandler2(int signo)
{
    (void)signo;
    g_stop_flag = ON;
}

/*********************************************************/



