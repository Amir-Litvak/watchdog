#include <unistd.h> /* getpid() */

#include "uid.h"

const task_uid_t UIDBadUID = {0, 0, 0};

task_uid_t UIDCreate(void)
{
	static size_t counter = 1;
	task_uid_t uid;
	uid.pid = getpid();
	uid.time = time(NULL);
	if(-1 == uid.time)
	{
		return UIDBadUID;
	}
	
	uid.counter = __sync_add_and_fetch(&counter, 1);
	
	return uid;
}

int UIDIsSame(task_uid_t uid1, task_uid_t uid2)
{
	return (uid1.pid == uid2.pid &&
			  uid1.time == uid2.time &&
			  uid1.counter == uid2.counter);
}



