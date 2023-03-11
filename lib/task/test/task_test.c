#include <stdio.h> /* for printf */
#include <unistd.h> /* for sleep */

#include "task.h"

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

int TestCreateDestroy(void);
int TestTaskExecute(void);
int TestTaskGetSetTimeUID(void);

int ActionFoo(void *param);
void CleanFoo(void *param);


int main()
{
	RUNTEST(TestCreateDestroy());
	RUNTEST(TestTaskExecute());
	RUNTEST(TestTaskGetSetTimeUID());
	
	return 0;
}

int TestCreateDestroy(void)
{
    int result = 0;
    int a = 42;
    int b = 31;
    time_t tea_time = 0;
    task_t *tsk = NULL;
	
	printf("-------- TESTING CREATE + DESTORY --------\n");
	tea_time = time(NULL);
	tsk = TaskCreate(&ActionFoo, &a, &CleanFoo, &b, tea_time);
	
	result += (NULL == tsk);
	TaskDestroy(tsk);
	result += (30 != b);
	return result;
}

int TestTaskExecute(void)
{
    int result = 0;
    int a = 42;
    int b = 31;
    time_t tea_time = 0;
    task_t *tsk = NULL;
	
	printf("-------- TESTING EXECUTE --------\n");
	tea_time = time(NULL);
	tsk = TaskCreate(&ActionFoo, &a, &CleanFoo, &b, tea_time);
	
	result += (TaskExecute(tsk) != 0);
	result += (43 != a);
	TaskDestroy(tsk);
	
	return result;
}

int TestTaskGetSetTimeUID(void)
{
    int result = 0;
    int a = 42;
    int b = 31;
    time_t tea_time = 0;
    time_t old_time = 0;
    task_t *tsk = NULL;
	
	printf("-------- TESTING GET TIME + SET TIME + GET UID --------\n");
	tea_time = time(NULL);
	tsk = TaskCreate(&ActionFoo, &a, &CleanFoo, &b, tea_time);
	result += (TaskGetTime(tsk) != tea_time);
	old_time = TaskGetTime(tsk);
	TaskSetTime(tsk, 1);
	result += (TaskGetTime(tsk) != old_time + 1);
	
	return result;
}

int ActionFoo(void *param)
{
	++*(int *)param;
	
	return 0;
}
void CleanFoo(void *param)
{
	--*(int *)param;
}
