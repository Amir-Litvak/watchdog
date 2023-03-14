#include <stddef.h> /*size_t*/
#include <assert.h> /*assert*/
#include <stdlib.h> /*malloc realloc free*/
#include <string.h> /* memove */

#include "dynamic_vector.h" /*d_vector_t*/

#define SHRINK_RATE 2 /* 50% */
#define SHRINK_INDICATOR 4 /* 100/4=25% */
#define GROWTH_RATE 2 /* 50% */

struct vector 
{
    void *data;
    size_t size;
    size_t element_size;
    size_t capacity;
};

enum status
{
	SUCCESS,
	FAIL
};

static int ResizeVector(d_vector_t *vector, size_t new_size);

d_vector_t *DVectorCreate(size_t element_size, size_t capacity)
{
	d_vector_t *vector = malloc(sizeof(d_vector_t));
	if (NULL == vector)
	{
		return NULL;
	}
	vector->data = malloc(element_size * capacity);
	if (NULL == vector->data)
	{
		free(vector);
		vector = NULL;
		return NULL;
	}
	
	(vector->size) = 0;
	(vector->capacity) = capacity;
	(vector->element_size) = element_size; 

	return vector;
}

void DVectorDestroy(d_vector_t *vector)
{
	assert(NULL != vector);
	
	free(vector->data);
	vector->data = NULL;
	free(vector);
	vector = NULL;
}

size_t DVectorSize(const d_vector_t *vector)
{
	assert(NULL != vector);
	
	return vector->size;
}

size_t DVectorCapacity(const d_vector_t *vector)
{
	assert(NULL != vector);
	
	return vector->capacity;
}

int DVectorPushBack(d_vector_t *vector,const void *data)
{
	size_t offset = 0;
	
	assert(NULL != vector);
	assert(NULL != data);
	assert(vector->capacity >= vector->size);

	offset = (vector->size)*(vector->element_size);
	
	memmove(((char *)(vector->data) + offset), data, vector->element_size);
	++vector->size;
	
	if (vector->capacity == vector->size)
	{
		return ResizeVector(vector, vector->capacity * GROWTH_RATE);
	}
	
	return SUCCESS;
}

int DVectorPopBack(d_vector_t  *vector)
{
	assert(NULL != vector);
	
	--vector->size;
	if (vector->size <= (vector->capacity / SHRINK_INDICATOR))
	{
		return ResizeVector(vector, vector->capacity / SHRINK_RATE);
	}
	
	return SUCCESS;
}

void *DVectorGetElement(const d_vector_t *vector, size_t index)
{
	size_t offset = 0;
	
	assert(NULL != vector);
	assert((vector->size) >= index);

	offset = index * vector->element_size;

	return ((char *)vector->data + offset);
}

int DVectorIsEmpty(const d_vector_t *vector)
{
	assert(NULL != vector);
	
	return (0 == vector->size);
}

int DVectorReserve(d_vector_t *vector, size_t new_num_of_elements)
{
	assert(NULL != vector);
	
	if (new_num_of_elements <= (vector->size + 1))
	{
		return DVectorShrinkToFit(vector);
	}

	return ResizeVector(vector, new_num_of_elements);
}

int DVectorShrinkToFit(d_vector_t *vector)
{
	assert(NULL != vector);
	
	return ResizeVector(vector, vector->size + 1);
}

static int ResizeVector(d_vector_t *vector, size_t new_size)
{
	void *backup = vector->data;
	
	vector->data = realloc(vector->data, new_size * vector->element_size);
	if (NULL == vector->data)
	{
		vector->data = backup;
		return FAIL;
	}
	vector->capacity = (new_size);
	
	return SUCCESS;
}
