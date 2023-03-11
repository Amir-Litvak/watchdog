#include <assert.h> /* for assert */
#include <stdlib.h> /* mallloc + free */
#include <unistd.h> /* sleep */

#include "priority_queue.h" /*priority queue functions*/
#include "task.h" /*task functions*/
#include "scheduler.h"    /* ds functions */

enum task_status
{
	FAIL = -1,
	SUCCESS
};

struct sched
{
	pq_t *scheduler;
	int stop_flag;
};

static int SortFunc(const void *new_data, const void *current_data, void *param);
static int MatchFunc(const void *current_data, void *param);
static int Reschedule(sched_t *sc, task_t *task, int status);
static int Execution(sched_t *sched, task_t *task);

sched_t *SchedCreate(void)
{
	sched_t *scd = (sched_t *)malloc(sizeof(sched_t));
	if (NULL == scd)
	{
		return NULL;
	}
	
	scd->stop_flag = 0;
	scd->scheduler = PQCreate(SortFunc, NULL);
	if (NULL == scd->scheduler)
	{
		free(scd);
		return NULL;
	}
	
	return scd;
}

void SchedDestroy(sched_t *sched)
{
	assert(NULL != sched);
	
	SchedClear(sched);
	PQDestroy(sched->scheduler);
	free(sched);
	sched = NULL;
}

task_uid_t SchedAddTask(sched_t *sched, 
						sc_action_func_t action_func, void *action_param, 
						sc_clean_up_func_t clean_up_func, void *clean_up_param, time_t time)
{
	task_t *task = NULL;
	
	assert(NULL != sched);
	assert(NULL != action_func);
	assert(NULL != clean_up_func);
	assert(-1 != time);
	
	task = TaskCreate(action_func, action_param,
					 clean_up_func, clean_up_param, time);
	if (NULL == task || (PQEnqueue(sched->scheduler, task)))
	{
		return UIDBadUID;
	}
	
	return TaskGetUID(task);
}

void SchedRemoveTask(sched_t *sched, task_uid_t uid)
{
	task_t *task = NULL;
	
	assert(NULL != sched);
	assert(!(UIDIsSame(uid, UIDBadUID)));
	
	task = PQErase(sched->scheduler, &uid, MatchFunc);
	if(NULL != task)
	{
		TaskDestroy(task);
	}
}

int SchedRun(sched_t *sched)
{
	int count_fails = 0;
	task_t *task = NULL;
	
	sched->stop_flag = 0;
	
	while (!SchedIsEmpty(sched) && (1 != sched->stop_flag))
	{
		task = PQPeek(sched->scheduler);
		
		if (time(NULL) >= (TaskGetTime(task)))
		{
			count_fails += Execution(sched, task);
		}
		else
		{
			sleep((TaskGetTime(task)) - time(NULL));
			count_fails += Execution(sched, task);
		}
	}
	
	return count_fails;
}

void SchedStop(sched_t *sched)
{
	assert(NULL != sched);
	
	sched->stop_flag = 1;
}

void SchedClear(sched_t *sched)
{	
	assert(NULL != sched);
	
	while (!SchedIsEmpty(sched))
	{
		TaskDestroy(PQDequeue(sched->scheduler));
	}
}

size_t SchedSize(const sched_t *sched)
{
	assert(NULL != sched);
	
	return PQSize(sched->scheduler);
}

int SchedIsEmpty(const sched_t *sched)
{
	assert(NULL != sched);
	
	return PQIsEmpty(sched->scheduler);
}

static int SortFunc(const void *new_data, const void *current_data, void *param)
{
	time_t new_time = TaskGetTime(new_data);
	time_t current_time = TaskGetTime(current_data);
	(void)param;
	
	return (current_time - new_time);
}

static int MatchFunc(const void *current_data, void *param)
{
	return UIDIsSame(TaskGetUID(current_data), *(task_uid_t *)param);
}

static int Reschedule(sched_t *sc, task_t *task, int status)
{
	TaskSetTime(task, status);
	return (PQEnqueue(sc->scheduler, task));
}

static int Execution(sched_t *sched, task_t *task)
{
	int status = 0;
	int count_fails = 0;
	task = PQDequeue(sched->scheduler);
	status = TaskExecute(task);
			
	if(SUCCESS < status)
	{
		count_fails = Reschedule(sched, task, status);
	}
	else
	{
		count_fails = -(status);
		TaskDestroy(task);
	}
	
	return count_fails;
}

