#include <stdio.h> /* for printf */

#include "uid.h"

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

int TestCreate(void);
int TestIsSame(void);

int main()
{
	RUNTEST(TestCreate());
	RUNTEST(TestIsSame());
	
	return 0;
}

int TestCreate(void)
{
    int result = 0;
    task_uid_t uid = UIDCreate();
    	
	printf("Testing Create\n");
	result += (UIDIsSame(uid, UIDBadUID) != 0);
	   
	return result;
}

int TestIsSame(void)
{
    int result = 0;
    task_uid_t uid1 = UIDCreate();
    task_uid_t uid2 = UIDCreate();
	
	printf("Testing IsSame\n");
	result += (UIDIsSame(uid1, uid2) != 0);
	   
	return result;
}

