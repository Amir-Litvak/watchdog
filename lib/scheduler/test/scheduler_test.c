#include <stdio.h> /* for printf */
#include <time.h>
#include <unistd.h> /* sleep */

#include "sched.h"

#define RUNTEST(test) {\
        if (!test)\
        {\
            printf("\x1b[0;32m");\
            printf("OK!\n\n");\
            printf("\x1b[0m");\
        }\
        else\
        {\
            printf("\x1b[1;31m");\
            printf("\nTest Failed!\n\n");\
            printf("\x1b[0m");\
        }\
    }
    
extern const task_uid_t UIDBadUID;

int ActionFunc(void *param);
int ActionFunc1(void *param);
void CleanUpFunc(void *param);
int ActionFunc2(void *param);
void CleanUpFunc2(void *param);
void CleanUpFunc3(void *param);
int ActionFunc3AddTask(void *param);
int ActionFunc4RemoveTask(void *task);

int TestCreateDestory(void);
int TestAddRemoveClear(void);
int TestRunStop(void);

int main()
{
	RUNTEST(TestCreateDestory());
	RUNTEST(TestAddRemoveClear());
	RUNTEST(TestRunStop());
	
	return 0;
}

int TestCreateDestory()
{
	int result = 0;
	sched_t *sc = SchedCreate();
	
	printf("------- TESTING CREATE + DESTORY + ISEMPTY -------\n");
	result += (sc == NULL);
	result += !(SchedIsEmpty(sc));
	
	SchedDestroy(sc);
	
	return result;
}

int TestAddRemoveClear()
{
	int result = 0;
	sched_t *sc = SchedCreate();
	task_uid_t task1 = UIDBadUID;
	task_uid_t task2 = UIDBadUID;
	task_uid_t task3 = UIDBadUID;
	task_uid_t task4 = UIDBadUID;
	task_uid_t task5 = UIDBadUID;
	
	task1 = SchedAddTask(sc, ActionFunc, 0, CleanUpFunc, 0, time(NULL)+2);
	/*sleep(1);*/
	task2 = SchedAddTask(sc, ActionFunc, 0, CleanUpFunc, 0, time(NULL)+5); 
	/*sleep(1);*/
	task3 = SchedAddTask(sc, ActionFunc, 0, CleanUpFunc, 0, time(NULL)+4); 
	/*sleep(1);*/
	task4 = SchedAddTask(sc, ActionFunc, 0, CleanUpFunc, 0, time(NULL)+1);
	/*sleep(1);*/
	task5 = SchedAddTask(sc, ActionFunc, 0, CleanUpFunc, 0, time(NULL)+10);
	
	printf("------- TESTING ADD + REMOVE + CLEAR + SIZE -------\n");
	
	result += (UIDIsSame(task1, UIDBadUID));
	printf("%d\n", result);
	result += (UIDIsSame(task2, UIDBadUID));
	printf("%d\n", result);
	result += (UIDIsSame(task3, UIDBadUID));
	printf("%d\n", result);
	result += (UIDIsSame(task4, UIDBadUID));
	printf("%d\n", result);
	result += (UIDIsSame(task5, UIDBadUID));
	printf("%d\n", result);

	result += (5 != SchedSize(sc));
	
	SchedRemoveTask(sc, task1);
	result += (4 != SchedSize(sc));
	SchedRemoveTask(sc, task2);
	result += (3 != SchedSize(sc));
	
	SchedClear(sc);
	result += !(SchedIsEmpty(sc));
	
	
	SchedDestroy(sc);
	
	return result;
}

int TestRunStop()
{
	int result = 0;
	sched_t *sc = SchedCreate();
	task_uid_t task1 = UIDBadUID;
	task_uid_t task2 = UIDBadUID;
	task_uid_t task3 = UIDBadUID;
	task_uid_t task4 = UIDBadUID;
	task_uid_t task5 = UIDBadUID;
	
	task1 = SchedAddTask(sc, ActionFunc, 0, CleanUpFunc, 0, time(NULL)+20);
	/*sleep(1);*/
	task2 = SchedAddTask(sc, ActionFunc1, 0, CleanUpFunc, 0, time(NULL)+10); 
	/*sleep(1);*/
	task3 = SchedAddTask(sc, ActionFunc2, 0, CleanUpFunc, 0, time(NULL)); 
	/*task4 = SchedAddTask(sc, ActionFunc, 0, CleanUpFunc, 0, time(NULL));
	task5 = SchedAddTask(sc, ActionFunc, 0, CleanUpFunc, 0, time(NULL));*/
	
	printf("------- TESTING RUN + STOP -------\n");
	
	SchedRun(sc);
	
	SchedDestroy(sc);
	
	return result;
}

int ActionFunc(void *param)
{
	(void)param;
	printf("This is an action!\n");
	
	return 0;
}

int ActionFunc1(void *param)	
{
	(void)param;
	printf("This is an action but different!\n");
	
	return 0;
}

int ActionFunc2(void *param)
{
	static int re = 10;
	(void)param;
	printf("This is another action! returns %d \n", re);
	--re;
	return re;
}

void CleanUpFunc(void *param)
{
	(void)param;
	printf("I should REALLY clean the house.\n");
}

/*void CleanUpFunc2(void *param)
{
	(void)param;
	printf("I should REALLY clean the house. And my kitchen.\n");
}

void CleanUpFunc3(void *param)
{
	(void)param;
	printf("Should I clean tho?\n");
}


int ActionFunc3AddTask(void *sched)
{
	(void)param;
	SchedAddTask(sched, ActionFunc, 0, CleanUpFunc2, 0, time(NULL)+25);
}

int ActionFunc4RemoveTask(void *task)
{
	(void)param;
	SchedRemoveTask(sc, task1);
}*/







