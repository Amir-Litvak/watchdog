#ifndef __SCHED__
#define __SCHED__

#include "uid.h" /* for UID operations */

/*******************************************************************************
   _____   _____  _    _  ______  _____   _    _  _       ______  _____  
  / ____| / ____|| |  | ||  ____||  __ \ | |  | || |     |  ____||  __ \ 
 | (___  | |     | |__| || |__   | |  | || |  | || |     | |__   | |__) |
  \___ \ | |     |  __  ||  __|  | |  | || |  | || |     |  __|  |  _  / 
  ____) || |____ | |  | || |____ | |__| || |__| || |____ | |____ | | \ \ 
 |_____/  \_____||_|  |_||______||_____/  \____/ |______||______||_|  \_\
                                                                         
                                                                         
*******************************************************************************/

/*******************************************************************************
*						       WHAT IS IT?									   *
********************************************************************************
	The Scheduler - 
	responsible for executing tasks per their appointed timing.
	Operations on scheduler:
			- Create a scheduler (with dynamic allocation).
			- Destory a shceduler.
			- Add task to scheduler.
			- Remove task from scheduler.
			- Clear the scheduler from all tasks.
			- Checks size of schedule (number of tasks currently in queue).
			- Checks to see if schedule is empty of tasks.
	

*******************************************************************************/

/*******************************************************************************
                                 Typedefs
*******************************************************************************/

typedef struct sched sched_t;
typedef int(*sc_action_func_t)(void *action_param);
typedef void(*sc_clean_up_func_t)(void *clean_up_param);

/*******************************************************************************
                                 Functions
*******************************************************************************/

/*******************************************************************************
Description: Creates a Scheduler.
Parameters: Void
Return value: Returns scheduler pointer, if fails, returns NULL.
Complexity: O(1) time
*******************************************************************************/
sched_t *SchedCreate(void);

/*******************************************************************************
Description: Destorys a Scheduler and frees allocated memory.
Parameters: - Recieves a scheduler pointer.
Return value: Void.
Complexity: O(n) time
*******************************************************************************/
void SchedDestroy(sched_t *sched);

/*******************************************************************************
Description: Creates a new task in the scheduler.
Parameters: - Scheduler pointer to insert the task into.
			- Action Func + parameter for it.
			- Clean up func + parameter for it.
			- Time to perform task.
Return value: Returns the UID of the created task, if fails, returns BadUID.
Complexity: O(n) time
Notes:  - If action_func is NULL, undefined behavior occurs.	
		- If clean_up_func is NULL, undefined behavior occurs.
		- If time is -1, undefined behavior occurs.
		- In case action_param unnecessary, Send NULL.
*******************************************************************************/
task_uid_t SchedAddTask(sched_t *sched, 
sc_action_func_t action_func, void *action_param, 
sc_clean_up_func_t clean_up_func, void *clean_up_param, time_t time);

/*******************************************************************************
Description: Removes a task from the scheduler by it's UID.
Parameters: -Scheduler pointer to remove the task from.
			- UID of task.
Return value: Void.
Complexity: O(n) time
Notes:  - Removing a non-existing task causes undefined behaviour.
*******************************************************************************/
void SchedRemoveTask(sched_t *sched, task_uid_t uid);

/*******************************************************************************
Description: - Deploys Run fuctionality, exectues all task in queue along
			   with clean up operations afterwards.
			 - Tasks are executed based on their alloted time slot.
Parameters: - Scheduler pointer to run from.
Return value: Number of function failures.
Complexity: O(n) time
Notes:  - Runs until schedule queue is empty, or until Stop signal has been given.
		- To restart execution proccess, 'SchedRun' must be reactivated manually.
		- Tasks can reschedule themselves if return value of task action
			   is greater than zero. 			   
*******************************************************************************/
int SchedRun(sched_t *sched);

/*******************************************************************************
Description: Stops a scheduler run.
Parameters: - Scheduler pointer.
Return value: Void.
Complexity: O(1) time
Notes:  - To restart execution proccess, 'SchedRun' must be reactivated manually.
*******************************************************************************/
void SchedStop(sched_t *sched);

/*******************************************************************************
Description: Clears all tasks in queue.
Parameters: - Scheduler pointer.
Return value: Void.
Complexity: O(n) time
*******************************************************************************/
void SchedClear(sched_t *sched);

/*******************************************************************************
Description: Returns number of tasks that are currently in qeueue.
Parameters: - Scheduler pointer.
Return value: Void.
Complexity: O(n) time
*******************************************************************************/
size_t SchedSize(const sched_t *sched);

/*******************************************************************************
Description: Returns a boolean value to indicate whether the schedule is empty.
Parameters: - Scheduler pointer.
Return value: Boolean.
Complexity: O(1) time
*******************************************************************************/
int SchedIsEmpty(const sched_t *sched);

#endif /* __SCHED__ */
