#include <assert.h> /* for assert */
#include <stdlib.h> /* malloc + free */

#include "task.h" /* declarations */

extern const task_uid_t UIDBadUID;

struct task
{
    time_t time;
    task_action_func_t action_func;
    void *action_param;
    task_clean_up_func_t clean_up_func;
    void *clean_up_param;
    task_uid_t uid;
};

static void InitTask(task_t *task, task_action_func_t action_func,
			void *action_param, task_clean_up_func_t clean_up_func, 
							void *clean_up_param, time_t time);

task_t *TaskCreate(task_action_func_t action_func, void *action_param, 
task_clean_up_func_t clean_up_func, void *clean_up_param, time_t time)
{
	task_t *tsk = NULL;
	assert(NULL != action_func);
	assert(NULL != clean_up_func);
	assert(-1 != time);
	
	tsk = (task_t *)malloc(sizeof(task_t));
	if(NULL == tsk)
	{
		return NULL;
	}
	InitTask(tsk, action_func, action_param, clean_up_func, clean_up_param, 
																		time);
	if(UIDIsSame(tsk->uid, UIDBadUID))
	{
		free(tsk);
		tsk = NULL;
		return NULL;
	}
	
	return tsk;
}
				
void TaskDestroy(task_t *task)
{
	assert(NULL != task);
	
	task->clean_up_func(task->clean_up_param);
	free(task);
	task = NULL;
}

int TaskExecute(task_t *task)
{
	assert(NULL != task);
	
	return (task->action_func(task->action_param));
}

time_t TaskGetTime(const task_t *task)
{
	assert(NULL != task);
	
	return task->time;
}

task_uid_t TaskGetUID(const task_t *task)
{
	assert(NULL != task);
	
	return task->uid;
}

void TaskSetTime(task_t *task, time_t add_time)
{
	assert(NULL != task);
	assert(-1 != add_time);
	
	task->time += add_time;
}

static void InitTask(task_t *task, task_action_func_t action_func,
			void *action_param, task_clean_up_func_t clean_up_func, 
							void *clean_up_param, time_t time)
{
	assert(NULL != task);
	assert(NULL != action_func);
	assert(NULL != clean_up_func);
	assert(-1 != time);
	
	task->time = time;
	task->action_func = action_func;
	task->action_param = action_param;
	task->clean_up_func = clean_up_func;
	task->clean_up_param = clean_up_param;
	task->uid = UIDCreate();
}






