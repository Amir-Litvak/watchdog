#include <stdio.h> /* for printf */
#include <signal.h>
#include <unistd.h>

#include "watchdog.h"

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

int TestWDStartStop(char *argv[]);

int main(int argc, char *argv[])
{
	RUNTEST(TestWDStartStop(argv));
	
	return 0;
}

int TestWDStartStop(char *argv[])
{
    int result = 0;
    size_t counter = 0;
	
	printf("-------------- TESTING StartWD AND StopWD FUNCS --------------\n");
	result += (StartWD(argv) != 0);

    for(counter = 0; counter < 60; ++counter)
    {
       sleep(1);
       if(40 == counter)
       {
            StopWD();
       }
    }

	return result;
}


