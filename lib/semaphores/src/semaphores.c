#include <stdio.h> /* i/o */ 
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h>

#include "semaphores.h" /* ILR&D funcs */

#define MAX_SEM (1)

enum status
{
    FAILURE = -1,
    SUCCESS = 0
};

/*typedef int semid_t;*/

semid_t SemCreate(const char *name, int proj_id, int sem_value)
{
    int status = SUCCESS;
    int identifier = 0;
    FILE *fp = fopen(name, "w+");
    key_t id_key = ftok(name, proj_id);

    identifier = semget(id_key, MAX_SEM, IPC_CREAT | 0666);
    if (FAILURE == identifier)
    {
        fclose(fp);
        return FAILURE;
    }

    status = semctl(identifier, 0, SETVAL, sem_value);
    if (FAILURE == status)
    {
       printf("FAILED AF\n");
    }

    fclose(fp);
    return identifier;
}

int SemDestroy(semid_t id)
{
    return semctl(id, 0, IPC_RMID);
}

int SemIncrement(semid_t id, int num, int set_undo)
{
    struct sembuf op;

    op.sem_num = 0;
    op.sem_op = num;
    op.sem_flg = 0;
	if(1 == set_undo)
	{
		op.sem_flg = SEM_UNDO;
	}

    return semop(id, &op, 1);
}

int SemDecrement(semid_t id, int num, int set_undo)
{
    struct sembuf op;
    
    op.sem_num = 0;
    op.sem_op = -num;
    op.sem_flg = 0;
	if(1 == set_undo)
	{
		op.sem_flg = SEM_UNDO;
	}

    return semop(id, &op, 1);
}

int SemGetVal(semid_t id)
{  
    return semctl(id, 0, GETVAL);
}

