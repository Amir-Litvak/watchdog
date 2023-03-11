#ifndef __TASK__
#define __TASK__

#include <time.h> /* time_t */

#include "uid.h" /* task_uid_t */

/*******************************************************************************
			  _______        _____ _  __
			 |__   __|/\    / ____| |/ /
				| |  /  \  | (___ | ' / 
				| | / /\ \  \___ \|  <  
				| |/ ____ \ ____) | . \ 
				|_/_/    \_\_____/|_|\_\
						                
						                
*******************************************************************************/

/*******************************************************************************
*						       WHAT IS IT?									   *
********************************************************************************
	Task module.
	a module meant for the scheduler.
*******************************************************************************/

/*******************************************************************************
                                 Typedefs
*******************************************************************************/

typedef struct task task_t;
typedef int(*task_action_func_t)(void *action_param);
typedef void(*task_clean_up_func_t)(void *clean_up_param);

/*******************************************************************************
                                 Functions
*******************************************************************************/
	
/*******************************************************************************
Description: Creates a Task.
Parameters: - Action Func + parameter for it
			- Clean up func + parameter for it
			- Time of task
Return value: Returns task pointer,  if fails, returns NULL.
Complexity: O(1) time
*******************************************************************************/
task_t *TaskCreate(task_action_func_t action_func, void *action_param, 
task_clean_up_func_t clean_up_func, void *clean_up_param, time_t time);

/*******************************************************************************
Description: Destorys a Task and deploys function cleanup.
Parameters: - task pointer.
Return value: Void.
Complexity: O(1) time
*******************************************************************************/				
void TaskDestroy(task_t *task);

/*******************************************************************************
Description: Executes the function stored in task.
Parameters: - task pointer.
Return value: boolean.
Complexity: O(1) time
*******************************************************************************/
int TaskExecute(task_t *task);

/*******************************************************************************
Description: Returns time of task.
Parameters: - task pointer.
Return value: Time.
Complexity: O(1) time
*******************************************************************************/
time_t TaskGetTime(const task_t *task);

/*******************************************************************************
Description: Returns UID of task.
Parameters: - task pointer.
Return value: UID.
Complexity: O(1) time
*******************************************************************************/
task_uid_t TaskGetUID(const task_t *task);

/*******************************************************************************
Description: Adds to time of task.
Parameters: - task pointer.
Return value: Void.
Complexity: O(1) time
*******************************************************************************/
void TaskSetTime(task_t *task, time_t add_time);



#endif /* __TASK__ */
