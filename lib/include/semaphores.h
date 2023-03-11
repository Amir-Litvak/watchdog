#ifndef __SEMAPHORE__
#define __SEMAPHORE__

typedef int semid_t;

/* return semaphore id, if failed return -1 */
semid_t SemCreate(const char *name, int proj_id, int sem_value);

/* all these functions return 0 for success, 1 for failure */

int SemDestroy(semid_t id);

/* to define the undo option set_undo is 1, else 0 */
int SemIncrement(semid_t id, int num, int set_undo);

/* to define the undo option set_undo is 1, else 0 */
int SemDecrement(semid_t id, int num, int set_undo);

int SemGetVal(semid_t id);

#endif /* __SEMAPHORE__ */
