#ifndef __UID__
#define __UID__

#include <time.h> /* time_t */

#include <sys/types.h> /* pid_t */

/*******************************************************************************
							  _    _ _____ _____  
							 | |  | |_   _|  __ \ 
							 | |  | | | | | |  | |
							 | |  | | | | | |  | |
							 | |__| |_| |_| |__| |
							  \____/|_____|_____/ 
												  
												  
*******************************************************************************/

/*******************************************************************************
*						       WHAT IS IT?									   *
********************************************************************************

	UID - unique ID.
	it is a structs that contains 3 fields:
		-PID - proccess ID
		-time - time at conception, counted in seconds since Epoch
		-counter - a static counter that increases each and every UID creation.
	YOU SHOULD NOT, UNDER ANY CIRCUMSTANCES TOUCH OR ALTER THE STRUCT FIELDS, 
								IN ANY WAY.

*******************************************************************************/

/*******************************************************************************
                                 Typedefs
*******************************************************************************/

typedef struct
{
  pid_t pid;
  time_t time;
  size_t counter;
} task_uid_t;

/*******************************************************************************
                                 Functions
*******************************************************************************/

/*******************************************************************************
Description: Creates a UID struct.
Parameters: Void.
Return value: Returns created UID be value, if fails, returns UIDBadUID.
Complexity: O(1) time
*******************************************************************************/
task_uid_t UIDCreate(void);

/*******************************************************************************
Description: Compares two UID structs.
Parameters: Two UID structs.
Return value: Returns boolean value.
Complexity: O(1) time
*******************************************************************************/
int UIDIsSame(task_uid_t uid1, task_uid_t uid2);

/*******************************************************************************
	Serves as a 'NULL' UID and is defined as '0' in all fields.
*******************************************************************************/
extern const task_uid_t UIDBadUID;



#endif /* __UID__ */
