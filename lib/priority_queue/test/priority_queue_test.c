/**************************************************************************
 Author: Karen Starkman
 Date: 25/05/2022
 Reviewed By: Revital Yedidi
**************************************************************************/
#include<stdio.h>                                   /* printf            */
#include<assert.h>                                  /* assert            */

#include "Heap_PQ.h"                                /* my implementation */

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


int TestPQCreateDestroyIsEmpty();
int TestPQInsertGetDataCount();
int TestPQRemove();
int TestPQClear();
int TestPQErase();

int main()
{
	RUNTEST(TestPQCreateDestroyIsEmpty());
	RUNTEST(TestPQInsertGetDataCount());
	RUNTEST(TestPQRemove());
	RUNTEST(TestPQClear());
	RUNTEST(TestPQErase());
	return 0;
}

int TestInt(const char *test_name, int expected_result, int result)
{
	(void)test_name;
	return ((expected_result == result) ? 0 : 1);
}

int TestSizeT(const char *test_name, size_t expected_result, size_t result)
{
	(void)test_name;
	return ((expected_result == result) ? 0 : 1);
}

int MatchFunc(const void* data, void *parameter)
{
	assert(NULL != parameter);
	assert(NULL != data);
	
	return *(int *) data == *(int *) parameter;
}

int CmpFunc(const void *new_data, const void *list_data, void *param)
{
	(void)param;
	
	return (*(int *)new_data - *(int *)list_data);
}

int TestPQCreateDestroyIsEmpty()
{
	pq_t *p_queue = NULL;
	int result = 0;
	int param = 1;
	
	p_queue = PQCreate(CmpFunc, &param);
	
	printf("--- TEST FOR Create & Destroy & Is Empty ---\n");
	result += !(1 == PQIsEmpty(p_queue));
	
	
	PQDestroy(p_queue);
	printf("Check memory is free using Valgrind\n");
	return result;
}

int TestPQInsertGetDataCount()
{
	pq_t *p_queue = NULL;
	int result = 0;
	int param = 1;
	
	int int1 = 19;
	int int2 = 13;
	int int3 = 84;
	int int4 = -892;
	
	p_queue = PQCreate(CmpFunc, &param);
	
	/* tests */
	printf("--- TEST FOR Insert & Get Data & Count ---\n");
	result += !(0 == PQEnqueue(p_queue, &int1));
	result += !(0 == PQEnqueue(p_queue, &int2));
	result += !(0 == PQEnqueue(p_queue, &int3));
	result += !(0 == PQEnqueue(p_queue, &int4));
	
	result += TestInt("INSERT", 84, *(int *)PQPeek(p_queue));
	
	result += !(4 == PQSize(p_queue));
	
	result += !(0 == PQIsEmpty(p_queue));
	
	PQDestroy(p_queue);
	
	return result;
}

int TestPQRemove()
{
	pq_t *p_queue = NULL;
	int result = 0;
	int param = 1;
	
	int int1 = 82;
	int int2 = 47;
	int int3 = 84;
	int int4 = -892;
	
	p_queue = PQCreate(CmpFunc, &param);
	
	/* tests */
	printf("--- TEST FOR Remove ---\n");
	result += !(0 == PQEnqueue(p_queue, &int1));
	result += !(0 == PQEnqueue(p_queue, &int2));
	result += !(0 == PQEnqueue(p_queue, &int3));
	result += !(0 == PQEnqueue(p_queue, &int4));
	PrintPQ(p_queue);
	result += TestInt("REMOVE", 84, *(int *)PQPeek(p_queue));
	
	result += TestInt("REMOVE", 84, *(int *)PQDequeue(p_queue));
	result += !(3 == PQSize(p_queue));
	PrintPQ(p_queue);
	result += TestInt("REMOVE", 82, *(int *)PQDequeue(p_queue));
	result += !(2 == PQSize(p_queue));
	PrintPQ(p_queue);
	result += TestInt("REMOVE", 47, *(int *)PQDequeue(p_queue));
	result += !(1 == PQSize(p_queue));
	result += !(0 == PQIsEmpty(p_queue));
	PrintPQ(p_queue);
	result += TestInt("REMOVE", -892, *(int *)PQDequeue(p_queue));
	result += !(1 == PQIsEmpty(p_queue));

	PQDestroy(p_queue);

	return result;
}

int TestPQClear()
{
	pq_t *p_queue = NULL;
	int result = 0;
	int param = 1;
	
	int int1 = 19;
	int int2 = 13;
	int int3 = 84;
	int int4 = -892;
	
	p_queue = PQCreate(CmpFunc, &param);
	
	/* tests */
	printf("--- TEST FOR Clear ---\n");
	result += !(0 == PQEnqueue(p_queue, &int1));
	result += !(0 == PQEnqueue(p_queue, &int2));
	result += !(0 == PQEnqueue(p_queue, &int3));
	result += !(0 == PQEnqueue(p_queue, &int4));
	
	PQClear(p_queue);
	result += !(1 == PQIsEmpty(p_queue));
	
	result += !(0 == PQEnqueue(p_queue, &int1));
	result += !(0 == PQEnqueue(p_queue, &int2));
	result += !(0 == PQEnqueue(p_queue, &int3));
	result += !(0 == PQEnqueue(p_queue, &int4));
	result += !(4 == PQSize(p_queue));
	
	PQDestroy(p_queue);

	return result;
}

int TestPQErase()
{
	pq_t *p_queue = NULL;
	int result = 0;
	int param = 1;
	
	int int1 = 19;
	int int2 = 13;
	int int3 = 84;
	int int4 = -892;
	
	int int5 = 5;
	
	p_queue = PQCreate(CmpFunc, &param);
	
	/* tests */
	printf("--- TEST FOR Erase ---\n");
	result += !(0 == PQEnqueue(p_queue, &int1));
	result += !(0 == PQEnqueue(p_queue, &int2));
	result += !(0 == PQEnqueue(p_queue, &int3));
	result += !(0 == PQEnqueue(p_queue, &int4));
	
	result += !(19 == *(int *)PQErase(p_queue, &int1, MatchFunc));
	result += !(3 == PQSize(p_queue));
	
	result += !(NULL == PQErase(p_queue, &int5, MatchFunc));
	result += !(3 == PQSize(p_queue));
	
	PQDestroy(p_queue);

	return result;
}
