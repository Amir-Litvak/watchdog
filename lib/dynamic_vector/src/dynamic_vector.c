#include <stddef.h> /*size_t*/
#include <assert.h> /*assert*/
#include <stdlib.h> /*malloc realloc free*/
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
	PASS,
	FAIL
};

int ResizeVector(d_vector_t *vector, size_t new_size);

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
	free(vector->data);
	vector->data = NULL;
	free(vector);
	vector = NULL;
}

size_t DVectorSize(const d_vector_t *vector)
{
	return vector->size;
}

size_t DVectorCapacity(const d_vector_t *vector)
{
	return vector->capacity;
}

int DVectorPushBack(d_vector_t *vector,const void *data)
{
	size_t offset = (vector->size)*(vector->element_size);
	size_t i = 0;
	
	assert(vector->capacity >= vector->size);
	
	for (i = 0; vector->element_size > i; ++i) /*can be replaced with memmove*/
	{
		*(((char *)(vector->data) + offset) + i) = (char)*((char *)data + i);
	}
	++vector->size;
	
	if (vector->capacity == vector->size)
	{
		return ResizeVector(vector, vector->capacity * 2);
	}
	
	return PASS;
}

int DVectorPopBack(d_vector_t  *vector)
{
	--vector->size;
	if (vector->size == (vector->capacity / SHRINK_INDICATOR))
	{
		return ResizeVector(vector, vector->capacity / SHRINK_RATE);
	}
	
	return PASS;
}

void *DVectorGetElement(const d_vector_t *vector, size_t index)
{
	size_t offset = index * vector->element_size;
	
	assert((vector->size) >= index);
	return ((char *)vector->data + offset);
}

int DVectorIsEmpty(const d_vector_t *vector)
{
	return (0 == vector->size);
}

int DVectorReserve(d_vector_t *vector, size_t new_num_of_elements)
{
	if (new_num_of_elements <= (vector->size + 1))
	{
		return ResizeVector(vector, vector->size + 1);
	}
	return ResizeVector(vector, new_num_of_elements);
}

int DVectorShrinkToFit(d_vector_t *vector)
{
	return ResizeVector(vector, vector->size + 1);
}

int ResizeVector(d_vector_t *vector, size_t new_size)
{
	void *backup = vector->data;
	
	vector->data = realloc(vector->data, new_size * vector->element_size);
	if (NULL == vector->data)
	{
		vector->data = backup;
		return FAIL;
	}
	vector->capacity = (new_size);
	
	return PASS;
}
