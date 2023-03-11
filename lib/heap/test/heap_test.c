
#include <stdio.h> /* for printf */


#define RUNTEST(test) {\
            if (!test)\
            {\
                printf("\x1b[0;34m");\
                printf("OK!\n\n");\
                printf("\x1b[0m");\
            }\
            else\
            {\
                printf("\x1b[1;35m");\
                printf("\nTest Failed!\n\n");\
                printf("\x1b[0m");\
            }\
        }
        
int ValCheck(int recieved_val, int expected_val, int line);
int TestCreate(void);

int total_fails = 0;

int main()
{
	RUNTEST(TestCreate());
	
	if (0 < total_fails)
	{
		printf("\n\n****** TOTAL FAILS = %d ******\n\n", total_fails);
	}

	return 0;
}

int ValCheck(int recieved_val, int expected_val, int line)
{
	if (recieved_val != expected_val)
	{
		printf("----------------FAIL line %d----------------\n", line);
		printf("got %d, when wanted %d\n",recieved_val, expected_val);
		++total_fails;
		return 1;
	}
	return 0;
}


int TestCreate(void)
{
	dhcp_t *new_dhcp = NULL;
    int result = 0;
    const char *network = "192.100.100.100"; 
    size_t subnet = 24;
	
	printf("Testing Create\n");
	
	new_dhcp = DHCPCreate(network, subnet);
	result += (NULL == new_dhcp);
	result += ValCheck(DHCPAvailableIPs(new_dhcp), 252, __LINE__); 
	printf("counted: %lu\n", DHCPAvailableIPs(new_dhcp));
	
	DHCPDestroy(new_dhcp);
	
	
	   
	return result;
}


