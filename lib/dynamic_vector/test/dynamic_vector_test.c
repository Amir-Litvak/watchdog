#include <stdio.h> /*printf*/
#include <assert.h> /*assert*/
#include <string.h> /*strcmp*/
#include "dynamic_vector.h"

void DVectorCharTest();
void DVectorIntTest();
void DVectorSizetTest();
void DVectorFloatTest();
void DVectorDoubleTest();
void DVectorStringTest();
void ValCheck(size_t recieved_val, size_t expected_val, int line);
void ValCheckStr(char *recieved_val, char *expected_val, int line);
/*void StackIntTest();
void StackSizetTest();
void StackStringTest();
void StackFloatTest();
void StackDoubleTest();
*/
int total_fails = 0;

int main()
{
	
	DVectorCharTest();
	DVectorIntTest();
/* 	DVectorSizetTest();
	DVectorFloatTest();
	DVectorDoubleTest();
	DVectorStringTest(); */

	
	
	if (0 < total_fails)
	{
		printf("\n\n****** TOTAL FAILS = %d ******\n\n", total_fails);
	}
	return 0;
}


void ValCheck(size_t recieved_val, size_t expected_val, int line)
{
	if (recieved_val != expected_val)
	{
		printf("----------------FAIL line %d----------------\n", line);
		++total_fails;
	}
}

/*
create
push
push - automatic expansion
pop - automatic reduction
reserve - expansion
push
push
shrink - reduction
destroy
*/

void DVectorCharTest()
{
	char ch1 = 'c';
	char ch2 = 'A';
	char ch3 = '*';
	int status = 0;
	int capacity = 2;
	
	d_vector_t *my_vector = DVectorCreate(sizeof(char), capacity);
	assert(NULL != my_vector);
	printf("\n~~~~~CHARS VECTOR~~~~~\n");
	printf("\n~~create~~\n");
	printf("IsEmpty? = %d\n", DVectorIsEmpty(my_vector));
	printf("Size? = %lu\n", DVectorSize(my_vector));
	printf("Capacity? = %lu\n", DVectorCapacity(my_vector));
	ValCheck(DVectorIsEmpty(my_vector), 1, __LINE__);
	ValCheck(DVectorSize(my_vector), 0, __LINE__);
	ValCheck(DVectorCapacity(my_vector), capacity, __LINE__);
	
	status = DVectorPushBack(my_vector, &ch1);
	printf("\n~~push back~~\n");
	printf("Push successful? = %d\n", status);
	printf("IsEmpty? = %d\n", DVectorIsEmpty(my_vector));
	printf("Size? = %lu\n", DVectorSize(my_vector));
	printf("Capacity? = %lu\n", DVectorCapacity(my_vector));
	ValCheck(status, 0, __LINE__);
	ValCheck(DVectorIsEmpty(my_vector), 0, __LINE__);
	ValCheck(DVectorSize(my_vector), 1, __LINE__);
	ValCheck(DVectorCapacity(my_vector), capacity, __LINE__);
	
	printf("\n~~get element~~\n");
	printf("GetElement 0 = %c\n", *(char *)DVectorGetElement(my_vector, 0));
	ValCheck(*(char *)DVectorGetElement(my_vector, 0), ch1, __LINE__);
	
	/*capacity expands automatic*/
	status = DVectorPushBack(my_vector, &ch2);
	printf("\n~~push back~~\n");
	printf("Push successful? = %d\n", status);
	printf("IsEmpty? = %d\n", DVectorIsEmpty(my_vector));
	printf("Size? = %lu\n", DVectorSize(my_vector));
	printf("Capacity? = %lu\n", DVectorCapacity(my_vector));
	ValCheck(status, 0, __LINE__);
	ValCheck(DVectorIsEmpty(my_vector), 0, __LINE__);
	ValCheck(DVectorSize(my_vector), 2, __LINE__);
	ValCheck(DVectorCapacity(my_vector), capacity*2, __LINE__);
	
	printf("\n~~get element~~\n");
	printf("GetElement 0 = %c\n", *(char *)DVectorGetElement(my_vector, 0));
	ValCheck(*(char *)DVectorGetElement(my_vector, 0), ch1, __LINE__);
	printf("GetElement 1 = %c\n", *(char *)DVectorGetElement(my_vector, 1));
	ValCheck(*(char *)DVectorGetElement(my_vector, 1), ch2, __LINE__);
	
	/*capacity reduces automatic*/
	status = DVectorPopBack(my_vector);
	printf("\n~~pop back~~\n");
	printf("Pop successful? = %d\n", status);
	printf("IsEmpty? = %d\n", DVectorIsEmpty(my_vector));
	printf("Size? = %lu\n", DVectorSize(my_vector));
	printf("Capacity? = %lu\n", DVectorCapacity(my_vector));
	ValCheck(status, 0, __LINE__);
	ValCheck(DVectorIsEmpty(my_vector), 0, __LINE__);
	ValCheck(DVectorSize(my_vector), 1, __LINE__);
	ValCheck(DVectorCapacity(my_vector), capacity, __LINE__);
	
	printf("\n~~get element~~\n");
	printf("GetElement 0 = %c\n", *(char *)DVectorGetElement(my_vector, 0));
	ValCheck(*(char *)DVectorGetElement(my_vector, 0), ch1, __LINE__);
	
	capacity = 11;
	status = DVectorReserve(my_vector, capacity);
	printf("\n~~Reserve~~\n");
	printf("Reserve successful? = %d\n", status);
	printf("IsEmpty? = %d\n", DVectorIsEmpty(my_vector));
	printf("Size? = %lu\n", DVectorSize(my_vector));
	printf("Capacity? = %lu\n", DVectorCapacity(my_vector));
	ValCheck(status, 0, __LINE__);
	ValCheck(DVectorIsEmpty(my_vector), 0, __LINE__);
	ValCheck(DVectorSize(my_vector), 1, __LINE__);
	ValCheck(DVectorCapacity(my_vector), capacity, __LINE__);
	
	status = DVectorPushBack(my_vector, &ch3);
	printf("\n~~push back~~\n");
	printf("Push successful? = %d\n", status);
	printf("IsEmpty? = %d\n", DVectorIsEmpty(my_vector));
	printf("Size? = %lu\n", DVectorSize(my_vector));
	printf("Capacity? = %lu\n", DVectorCapacity(my_vector));
	ValCheck(status, 0, __LINE__);
	ValCheck(DVectorIsEmpty(my_vector), 0, __LINE__);
	ValCheck(DVectorSize(my_vector), 2, __LINE__);
	ValCheck(DVectorCapacity(my_vector), capacity, __LINE__);
	
	printf("\n~~get element~~\n");
	printf("GetElement 0 = %c\n", *(char *)DVectorGetElement(my_vector, 0));
	printf("GetElement 1 = %c\n", *(char *)DVectorGetElement(my_vector, 1));
	ValCheck(*(char *)DVectorGetElement(my_vector, 0), ch1, __LINE__);
	ValCheck(*(char *)DVectorGetElement(my_vector, 1), ch3, __LINE__);
	
	status = DVectorPushBack(my_vector, &ch1);
	printf("\n~~push back~~\n");
	printf("Push successful? = %d\n", status);
	printf("IsEmpty? = %d\n", DVectorIsEmpty(my_vector));
	printf("Size? = %lu\n", DVectorSize(my_vector));
	printf("Capacity? = %lu\n", DVectorCapacity(my_vector));
	ValCheck(status, 0, __LINE__);
	ValCheck(DVectorIsEmpty(my_vector), 0, __LINE__);
	ValCheck(DVectorSize(my_vector), 3, __LINE__);
	ValCheck(DVectorCapacity(my_vector), capacity, __LINE__);
	
	printf("\n~~get element~~\n");
	printf("GetElement 2 = %c\n", *(char *)DVectorGetElement(my_vector, 2));
	ValCheck(*(char *)DVectorGetElement(my_vector, 2), ch1, __LINE__);
	
	status = DVectorShrinkToFit(my_vector);
	printf("\n~~ShrinkToFit~~\n");
	printf("Shrink successful? = %d\n", status);
	printf("IsEmpty? = %d\n", DVectorIsEmpty(my_vector));
	printf("Size? = %lu\n", DVectorSize(my_vector));
	printf("Capacity? = %lu\n", DVectorCapacity(my_vector));
	ValCheck(status, 0, __LINE__);
	ValCheck(DVectorIsEmpty(my_vector), 0, __LINE__);
	ValCheck(DVectorSize(my_vector), 3, __LINE__);
	ValCheck(DVectorCapacity(my_vector), 3+1, __LINE__);
	
	DVectorDestroy(my_vector);
}

void DVectorIntTest()
{
	int num1 = 55;
	int num2 = -3;
	int num3 = 66;
	int status = 0;
	int capacity = 2;
	
	d_vector_t *my_vector = DVectorCreate(sizeof(int), capacity);
	assert(NULL != my_vector);
	printf("\n~~~~~INTS VECTOR~~~~~\n");
	printf("\n~~create~~\n");
	printf("IsEmpty? = %d\n", DVectorIsEmpty(my_vector));
	printf("Size? = %lu\n", DVectorSize(my_vector));
	printf("Capacity? = %lu\n", DVectorCapacity(my_vector));
	ValCheck(DVectorIsEmpty(my_vector), 1, __LINE__);
	ValCheck(DVectorSize(my_vector), 0, __LINE__);
	ValCheck(DVectorCapacity(my_vector), capacity, __LINE__);
	
	status = DVectorPushBack(my_vector, &num1);
	printf("\n~~push back~~\n");
	printf("Push successful? = %d\n", status);
	printf("IsEmpty? = %d\n", DVectorIsEmpty(my_vector));
	printf("Size? = %lu\n", DVectorSize(my_vector));
	printf("Capacity? = %lu\n", DVectorCapacity(my_vector));
	ValCheck(status, 0, __LINE__);
	ValCheck(DVectorIsEmpty(my_vector), 0, __LINE__);
	ValCheck(DVectorSize(my_vector), 1, __LINE__);
	ValCheck(DVectorCapacity(my_vector), capacity, __LINE__);
	
	printf("\n~~get element~~\n");
	printf("GetElement 0 = %d\n", *(int *)DVectorGetElement(my_vector, 0));
	ValCheck(*(int *)DVectorGetElement(my_vector, 0), num1, __LINE__);
	
	/*capacity expands automatic*/
	status = DVectorPushBack(my_vector, &num2);
	printf("\n~~push back~~\n");
	printf("Push successful? = %d\n", status);
	printf("IsEmpty? = %d\n", DVectorIsEmpty(my_vector));
	printf("Size? = %lu\n", DVectorSize(my_vector));
	printf("Capacity? = %lu\n", DVectorCapacity(my_vector));
	ValCheck(status, 0, __LINE__);
	ValCheck(DVectorIsEmpty(my_vector), 0, __LINE__);
	ValCheck(DVectorSize(my_vector), 2, __LINE__);
	ValCheck(DVectorCapacity(my_vector), capacity*2, __LINE__);
	
	printf("\n~~get element~~\n");
	printf("GetElement 0 = %d\n", *(int *)DVectorGetElement(my_vector, 0));
	ValCheck(*(int *)DVectorGetElement(my_vector, 0), num1, __LINE__);
	printf("GetElement 1 = %d\n", *(int *)DVectorGetElement(my_vector, 1));
	ValCheck(*(int *)DVectorGetElement(my_vector, 1), num2, __LINE__);
	
	/*capacity reduces automatic*/
	status = DVectorPopBack(my_vector);
	printf("\n~~pop back~~\n");
	printf("Pop successful? = %d\n", status);
	printf("IsEmpty? = %d\n", DVectorIsEmpty(my_vector));
	printf("Size? = %lu\n", DVectorSize(my_vector));
	printf("Capacity? = %lu\n", DVectorCapacity(my_vector));
	ValCheck(status, 0, __LINE__);
	ValCheck(DVectorIsEmpty(my_vector), 0, __LINE__);
	ValCheck(DVectorSize(my_vector), 1, __LINE__);
	ValCheck(DVectorCapacity(my_vector), capacity, __LINE__);
	
	printf("\n~~get element~~\n");
	printf("GetElement 0 = %d\n", *(int *)DVectorGetElement(my_vector, 0));
	ValCheck(*(int *)DVectorGetElement(my_vector, 0), num1, __LINE__);
	
	capacity = 11;
	status = DVectorReserve(my_vector, capacity);
	printf("\n~~Reserve~~\n");
	printf("Reserve successful? = %d\n", status);
	printf("IsEmpty? = %d\n", DVectorIsEmpty(my_vector));
	printf("Size? = %lu\n", DVectorSize(my_vector));
	printf("Capacity? = %lu\n", DVectorCapacity(my_vector));
	ValCheck(status, 0, __LINE__);
	ValCheck(DVectorIsEmpty(my_vector), 0, __LINE__);
	ValCheck(DVectorSize(my_vector), 1, __LINE__);
	ValCheck(DVectorCapacity(my_vector), capacity, __LINE__);
	
	status = DVectorPushBack(my_vector, &num3);
	printf("\n~~push back~~\n");
	printf("Push successful? = %d\n", status);
	printf("IsEmpty? = %d\n", DVectorIsEmpty(my_vector));
	printf("Size? = %lu\n", DVectorSize(my_vector));
	printf("Capacity? = %lu\n", DVectorCapacity(my_vector));
	ValCheck(status, 0, __LINE__);
	ValCheck(DVectorIsEmpty(my_vector), 0, __LINE__);
	ValCheck(DVectorSize(my_vector), 2, __LINE__);
	ValCheck(DVectorCapacity(my_vector), capacity, __LINE__);
	
	printf("\n~~get element~~\n");
	printf("GetElement 0 = %d\n", *(int *)DVectorGetElement(my_vector, 0));
	printf("GetElement 1 = %d\n", *(int *)DVectorGetElement(my_vector, 1));
	ValCheck(*(int *)DVectorGetElement(my_vector, 0), num1, __LINE__);
	ValCheck(*(int *)DVectorGetElement(my_vector, 1), num3, __LINE__);
	
	status = DVectorPushBack(my_vector, &num1);
	printf("\n~~push back~~\n");
	printf("Push successful? = %d\n", status);
	printf("IsEmpty? = %d\n", DVectorIsEmpty(my_vector));
	printf("Size? = %lu\n", DVectorSize(my_vector));
	printf("Capacity? = %lu\n", DVectorCapacity(my_vector));
	ValCheck(status, 0, __LINE__);
	ValCheck(DVectorIsEmpty(my_vector), 0, __LINE__);
	ValCheck(DVectorSize(my_vector), 3, __LINE__);
	ValCheck(DVectorCapacity(my_vector), capacity, __LINE__);
	
	printf("\n~~get element~~\n");
	printf("GetElement 2 = %d\n", *(int *)DVectorGetElement(my_vector, 2));
	ValCheck(*(int *)DVectorGetElement(my_vector, 2), num1, __LINE__);
	
	status = DVectorShrinkToFit(my_vector);
	printf("\n~~ShrinkToFit~~\n");
	printf("Shrink successful? = %d\n", status);
	printf("IsEmpty? = %d\n", DVectorIsEmpty(my_vector));
	printf("Size? = %lu\n", DVectorSize(my_vector));
	printf("Capacity? = %lu\n", DVectorCapacity(my_vector));
	ValCheck(status, 0, __LINE__);
	ValCheck(DVectorIsEmpty(my_vector), 0, __LINE__);
	ValCheck(DVectorSize(my_vector), 3, __LINE__);
	ValCheck(DVectorCapacity(my_vector), 3+1, __LINE__);
	
	DVectorDestroy(my_vector);
}

void DVectorSizetTest()
{
	size_t num1 = 55;
	size_t num2 = 9000;
	size_t num3 = 66;
	int status = 0;
	int capacity = 2;
	
	d_vector_t *my_vector = DVectorCreate(sizeof(size_t), capacity);
	assert(NULL != my_vector);
	printf("\n~~~~~SIZET VECTOR~~~~~\n");
	printf("\n~~create~~\n");
	ValCheck(DVectorIsEmpty(my_vector), 1, __LINE__);
	ValCheck(DVectorSize(my_vector), 0, __LINE__);
	ValCheck(DVectorCapacity(my_vector), capacity, __LINE__);
	
	status = DVectorPushBack(my_vector, &num1);
	printf("\n~~push back~~\n");
	ValCheck(status, 0, __LINE__);
	ValCheck(DVectorIsEmpty(my_vector), 0, __LINE__);
	ValCheck(DVectorSize(my_vector), 1, __LINE__);
	ValCheck(DVectorCapacity(my_vector), capacity, __LINE__);
	
	printf("\n~~get element~~\n");
	ValCheck(*(size_t *)DVectorGetElement(my_vector, 0), num1, __LINE__);
	
	/*capacity expands automatic*/
	status = DVectorPushBack(my_vector, &num2);
	printf("\n~~push back~~\n");
	ValCheck(status, 0, __LINE__);
	ValCheck(DVectorIsEmpty(my_vector), 0, __LINE__);
	ValCheck(DVectorSize(my_vector), 2, __LINE__);
	ValCheck(DVectorCapacity(my_vector), capacity * 2, __LINE__);
	
	printf("\n~~get element~~\n");
	ValCheck(*(size_t *)DVectorGetElement(my_vector, 0), num1, __LINE__);
	ValCheck(*(size_t *)DVectorGetElement(my_vector, 1), num2, __LINE__);
	
	/*capacity reduces automatic*/
	status = DVectorPopBack(my_vector);
	printf("\n~~pop back~~\n");
	ValCheck(status, 0, __LINE__);
	ValCheck(DVectorIsEmpty(my_vector), 0, __LINE__);
	ValCheck(DVectorSize(my_vector), 1, __LINE__);
	ValCheck(DVectorCapacity(my_vector), capacity, __LINE__);
	
	printf("\n~~get element~~\n");
	ValCheck(*(size_t *)DVectorGetElement(my_vector, 0), num1, __LINE__);
	
	capacity = 11;
	status = DVectorReserve(my_vector, capacity);
	printf("\n~~Reserve~~\n");
	ValCheck(status, 0, __LINE__);
	ValCheck(DVectorIsEmpty(my_vector), 0, __LINE__);
	ValCheck(DVectorSize(my_vector), 1, __LINE__);
	ValCheck(DVectorCapacity(my_vector), capacity, __LINE__);
	
	status = DVectorPushBack(my_vector, &num3);
	printf("\n~~push back~~\n");
	ValCheck(status, 0, __LINE__);
	ValCheck(DVectorIsEmpty(my_vector), 0, __LINE__);
	ValCheck(DVectorSize(my_vector), 2, __LINE__);
	ValCheck(DVectorCapacity(my_vector), capacity, __LINE__);
	
	printf("\n~~get element~~\n");
	ValCheck(*(size_t *)DVectorGetElement(my_vector, 0), num1, __LINE__);
	ValCheck(*(size_t *)DVectorGetElement(my_vector, 1), num3, __LINE__);
	
	status = DVectorPushBack(my_vector, &num1);
	printf("\n~~push back~~\n");
	ValCheck(status, 0, __LINE__);
	ValCheck(DVectorIsEmpty(my_vector), 0, __LINE__);
	ValCheck(DVectorSize(my_vector), 3, __LINE__);
	ValCheck(DVectorCapacity(my_vector), capacity, __LINE__);
	
	printf("\n~~get element~~\n");
	ValCheck(*(size_t *)DVectorGetElement(my_vector, 2), num1, __LINE__);
	
	status = DVectorShrinkToFit(my_vector);
	printf("\n~~ShrinkToFit~~\n");
	ValCheck(status, 0, __LINE__);
	ValCheck(DVectorIsEmpty(my_vector), 0, __LINE__);
	ValCheck(DVectorSize(my_vector), 3, __LINE__);
	ValCheck(DVectorCapacity(my_vector), 3+1, __LINE__);
	
	DVectorDestroy(my_vector);
}

void DVectorFloatTest()
{
	float num1 = 10.3;
	float num2 = 22.666;
	float num3 = -12.7;
	int status = 0;
	int capacity = 2;
	
	d_vector_t *my_vector = DVectorCreate(sizeof(float), capacity);
	assert(NULL != my_vector);
	printf("\n~~~~~FLOAT VECTOR~~~~~\n");
	printf("\n~~create~~\n");
	ValCheck(DVectorIsEmpty(my_vector), 1, __LINE__);
	ValCheck(DVectorSize(my_vector), 0, __LINE__);
	ValCheck(DVectorCapacity(my_vector), capacity, __LINE__);
	
	status = DVectorPushBack(my_vector, &num1);
	printf("\n~~push back~~\n");
	ValCheck(status, 0, __LINE__);
	ValCheck(DVectorIsEmpty(my_vector), 0, __LINE__);
	ValCheck(DVectorSize(my_vector), 1, __LINE__);
	ValCheck(DVectorCapacity(my_vector), capacity, __LINE__);
	
	printf("\n~~get element~~\n");
	ValCheck(*(float *)DVectorGetElement(my_vector, 0), num1, __LINE__);
	
	/*capacity expands automatic*/
	status = DVectorPushBack(my_vector, &num2);
	printf("\n~~push back~~\n");
	ValCheck(status, 0, __LINE__);
	ValCheck(DVectorIsEmpty(my_vector), 0, __LINE__);
	ValCheck(DVectorSize(my_vector), 2, __LINE__);
	ValCheck(DVectorCapacity(my_vector), capacity * 2, __LINE__);
	
	printf("\n~~get element~~\n");
	ValCheck(*(float *)DVectorGetElement(my_vector, 0), num1, __LINE__);
	ValCheck(*(float *)DVectorGetElement(my_vector, 1), num2, __LINE__);
	
	/*capacity reduces automatic*/
	status = DVectorPopBack(my_vector);
	printf("\n~~pop back~~\n");
	ValCheck(status, 0, __LINE__);
	ValCheck(DVectorIsEmpty(my_vector), 0, __LINE__);
	ValCheck(DVectorSize(my_vector), 1, __LINE__);
	ValCheck(DVectorCapacity(my_vector), capacity, __LINE__);
	
	printf("\n~~get element~~\n");
	ValCheck(*(float *)DVectorGetElement(my_vector, 0), num1, __LINE__);
	
	capacity = 11;
	status = DVectorReserve(my_vector, capacity);
	printf("\n~~Reserve~~\n");
	ValCheck(status, 0, __LINE__);
	ValCheck(DVectorIsEmpty(my_vector), 0, __LINE__);
	ValCheck(DVectorSize(my_vector), 1, __LINE__);
	ValCheck(DVectorCapacity(my_vector), capacity, __LINE__);
	
	status = DVectorPushBack(my_vector, &num3);
	printf("\n~~push back~~\n");
	ValCheck(status, 0, __LINE__);
	ValCheck(DVectorIsEmpty(my_vector), 0, __LINE__);
	ValCheck(DVectorSize(my_vector), 2, __LINE__);
	ValCheck(DVectorCapacity(my_vector), capacity, __LINE__);
	
	printf("\n~~get element~~\n");
	ValCheck(*(float *)DVectorGetElement(my_vector, 0), num1, __LINE__);
	ValCheck(*(float *)DVectorGetElement(my_vector, 1), num3, __LINE__);
	
	status = DVectorPushBack(my_vector, &num1);
	printf("\n~~push back~~\n");
	ValCheck(status, 0, __LINE__);
	ValCheck(DVectorIsEmpty(my_vector), 0, __LINE__);
	ValCheck(DVectorSize(my_vector), 3, __LINE__);
	ValCheck(DVectorCapacity(my_vector), capacity, __LINE__);
	
	printf("\n~~get element~~\n");
	ValCheck(*(float *)DVectorGetElement(my_vector, 2), num1, __LINE__);
	
	status = DVectorShrinkToFit(my_vector);
	printf("\n~~ShrinkToFit~~\n");
	ValCheck(status, 0, __LINE__);
	ValCheck(DVectorIsEmpty(my_vector), 0, __LINE__);
	ValCheck(DVectorSize(my_vector), 3, __LINE__);
	ValCheck(DVectorCapacity(my_vector), 3+1, __LINE__);
	
	DVectorDestroy(my_vector);
	
}

void DVectorDoubleTest()
{
	double num1 = 10.3;
	double num2 = 22.666;
	double num3 = -12.7;
	int status = 0;
	int capacity = 2;
	
	d_vector_t *my_vector = DVectorCreate(sizeof(double), capacity);
	assert(NULL != my_vector);
	printf("\n~~~~~DOUBLE VECTOR~~~~~\n");
	printf("\n~~create~~\n");
	ValCheck(DVectorIsEmpty(my_vector), 1, __LINE__);
	ValCheck(DVectorSize(my_vector), 0, __LINE__);
	ValCheck(DVectorCapacity(my_vector), capacity, __LINE__);
	
	status = DVectorPushBack(my_vector, &num1);
	printf("\n~~push back~~\n");
	ValCheck(status, 0, __LINE__);
	ValCheck(DVectorIsEmpty(my_vector), 0, __LINE__);
	ValCheck(DVectorSize(my_vector), 1, __LINE__);
	ValCheck(DVectorCapacity(my_vector), capacity, __LINE__);
	
	printf("\n~~get element~~\n");
	ValCheck(*(double *)DVectorGetElement(my_vector, 0), num1, __LINE__);
	
	/*capacity expands automatic*/
	status = DVectorPushBack(my_vector, &num2);
	printf("\n~~push back~~\n");
	ValCheck(status, 0, __LINE__);
	ValCheck(DVectorIsEmpty(my_vector), 0, __LINE__);
	ValCheck(DVectorSize(my_vector), 2, __LINE__);
	ValCheck(DVectorCapacity(my_vector), capacity * 2, __LINE__);
	
	printf("\n~~get element~~\n");
	ValCheck(*(double *)DVectorGetElement(my_vector, 0), num1, __LINE__);
	ValCheck(*(double *)DVectorGetElement(my_vector, 1), num2, __LINE__);
	
	/*capacity reduces automatic*/
	status = DVectorPopBack(my_vector);
	printf("\n~~pop back~~\n");
	ValCheck(status, 0, __LINE__);
	ValCheck(DVectorIsEmpty(my_vector), 0, __LINE__);
	ValCheck(DVectorSize(my_vector), 1, __LINE__);
	ValCheck(DVectorCapacity(my_vector), capacity, __LINE__);
	
	printf("\n~~get element~~\n");
	ValCheck(*(double *)DVectorGetElement(my_vector, 0), num1, __LINE__);
	
	capacity = 11;
	status = DVectorReserve(my_vector, capacity);
	printf("\n~~Reserve~~\n");
	ValCheck(status, 0, __LINE__);
	ValCheck(DVectorIsEmpty(my_vector), 0, __LINE__);
	ValCheck(DVectorSize(my_vector), 1, __LINE__);
	ValCheck(DVectorCapacity(my_vector), capacity, __LINE__);
	
	status = DVectorPushBack(my_vector, &num3);
	printf("\n~~push back~~\n");
	ValCheck(status, 0, __LINE__);
	ValCheck(DVectorIsEmpty(my_vector), 0, __LINE__);
	ValCheck(DVectorSize(my_vector), 2, __LINE__);
	ValCheck(DVectorCapacity(my_vector), capacity, __LINE__);
	
	printf("\n~~get element~~\n");
	ValCheck(*(double *)DVectorGetElement(my_vector, 0), num1, __LINE__);
	ValCheck(*(double *)DVectorGetElement(my_vector, 1), num3, __LINE__);
	
	status = DVectorPushBack(my_vector, &num1);
	printf("\n~~push back~~\n");
	ValCheck(status, 0, __LINE__);
	ValCheck(DVectorIsEmpty(my_vector), 0, __LINE__);
	ValCheck(DVectorSize(my_vector), 3, __LINE__);
	ValCheck(DVectorCapacity(my_vector), capacity, __LINE__);
	
	printf("\n~~get element~~\n");
	ValCheck(*(double *)DVectorGetElement(my_vector, 2), num1, __LINE__);
	
	status = DVectorShrinkToFit(my_vector);
	printf("\n~~ShrinkToFit~~\n");
	ValCheck(status, 0, __LINE__);
	ValCheck(DVectorIsEmpty(my_vector), 0, __LINE__);
	ValCheck(DVectorSize(my_vector), 3, __LINE__);
	ValCheck(DVectorCapacity(my_vector), 3+1, __LINE__);
	
	DVectorDestroy(my_vector);
}

void DVectorStringTest()
{
	char str1[] = "Wakey wakey";
	char str2[] = "Eggs and bakey";
	char str3[] = "I didn't say sell me I said give me";
	int status = 0;
	int capacity = 2;
	
	d_vector_t *my_vector = DVectorCreate(sizeof(str3), capacity);
	assert(NULL != my_vector);
	printf("\n~~~~~STRING VECTOR~~~~~\n");
	printf("\n~~create~~\n");
	ValCheck(DVectorIsEmpty(my_vector), 1, __LINE__);
	ValCheck(DVectorSize(my_vector), 0, __LINE__);
	ValCheck(DVectorCapacity(my_vector), capacity, __LINE__);
	
	status = DVectorPushBack(my_vector, str1);
	printf("\n~~push back~~\n");
	ValCheck(status, 0, __LINE__);
	ValCheck(DVectorIsEmpty(my_vector), 0, __LINE__);
	ValCheck(DVectorSize(my_vector), 1, __LINE__);
	ValCheck(DVectorCapacity(my_vector), capacity, __LINE__);
	
	printf("\n~~get element~~\n");
	ValCheckStr((char *)DVectorGetElement(my_vector, 0), str1, __LINE__);
	
	/*capacity expands automatic*/
	status = DVectorPushBack(my_vector, str2);
	printf("\n~~push back~~\n");
	ValCheck(status, 0, __LINE__);
	ValCheck(DVectorIsEmpty(my_vector), 0, __LINE__);
	ValCheck(DVectorSize(my_vector), 2, __LINE__);
	ValCheck(DVectorCapacity(my_vector), capacity * 2, __LINE__);
	
	printf("\n~~get element~~\n");
	ValCheckStr((char *)DVectorGetElement(my_vector, 0), str1, __LINE__);
	ValCheckStr((char *)DVectorGetElement(my_vector, 1), str2, __LINE__);
	
	/*capacity reduces automatic*/
	status = DVectorPopBack(my_vector);
	printf("\n~~pop back~~\n");
	ValCheck(status, 0, __LINE__);
	ValCheck(DVectorIsEmpty(my_vector), 0, __LINE__);
	ValCheck(DVectorSize(my_vector), 1, __LINE__);
	ValCheck(DVectorCapacity(my_vector), capacity, __LINE__);
	
	printf("\n~~get element~~\n");
	ValCheckStr((char *)DVectorGetElement(my_vector, 0), str1, __LINE__);
	
	capacity = 11;
	status = DVectorReserve(my_vector, capacity);
	printf("\n~~Reserve~~\n");
	ValCheck(status, 0, __LINE__);
	ValCheck(DVectorIsEmpty(my_vector), 0, __LINE__);
	ValCheck(DVectorSize(my_vector), 1, __LINE__);
	ValCheck(DVectorCapacity(my_vector), capacity, __LINE__);
	
	status = DVectorPushBack(my_vector, str3);
	printf("\n~~push back~~\n");
	ValCheck(status, 0, __LINE__);
	ValCheck(DVectorIsEmpty(my_vector), 0, __LINE__);
	ValCheck(DVectorSize(my_vector), 2, __LINE__);
	ValCheck(DVectorCapacity(my_vector), capacity, __LINE__);
	
	printf("\n~~get element~~\n");
	ValCheckStr((char *)DVectorGetElement(my_vector, 0), str1, __LINE__);
	ValCheckStr((char *)DVectorGetElement(my_vector, 1), str3, __LINE__);
	
	status = DVectorPushBack(my_vector, str1);
	printf("\n~~push back~~\n");
	ValCheck(status, 0, __LINE__);
	ValCheck(DVectorIsEmpty(my_vector), 0, __LINE__);
	ValCheck(DVectorSize(my_vector), 3, __LINE__);
	ValCheck(DVectorCapacity(my_vector), capacity, __LINE__);
	
	printf("\n~~get element~~\n");
	ValCheckStr((char *)DVectorGetElement(my_vector, 2), str1, __LINE__);
	
	status = DVectorShrinkToFit(my_vector);
	printf("\n~~ShrinkToFit~~\n");
	ValCheck(status, 0, __LINE__);
	ValCheck(DVectorIsEmpty(my_vector), 0, __LINE__);
	ValCheck(DVectorSize(my_vector), 3, __LINE__);
	ValCheck(DVectorCapacity(my_vector), 3+1, __LINE__);
	
	DVectorDestroy(my_vector);
}

void ValCheckStr(char *recieved_val, char *expected_val, int line)
{
	if (0 != strcmp(recieved_val, expected_val))
	{
		printf("----------------FAIL line %d----------------\n", line);
		++total_fails;
	}
}
