/*****************************************************************************
*Name: Amir Litvak													 			 
*Reviewer: Tom 											 			 
*Date: 05/21/22													 			 
*heap.c														 			 
******************************************************************************/

#include <assert.h> /* for assert */
#include <stdlib.h> /* malloc + free */
#include <stdio.h> /* testing purposes, will be removed after CR approve */

#include "dynamic_vector.h"
#include "heap.h"

#define LAST_INDEX (HeapSize(heap) - 1)
#define HEAP_SIZE (60)
#define HEAP_ROOT (0)

static void HeapifyUp(heap_t *heap, int current_index);
static void HeapifyDown(heap_t *heap, size_t current_index);
static void SwapElements(void **element1, void **element2);
static size_t GetParent(size_t child_index);
static size_t GetLeftChild(size_t parent_index);
static size_t GetRightChild(size_t parent_index);
static size_t GetEldest(heap_t *heap, size_t parent_index);
static int HasNoChildren(size_t heap_size, size_t parent_index);
static size_t FindElement(heap_t *heap, void *to_remove, is_match_t match_func, 
															void *match_param);

enum status
{
	SUCCESS = 0,
	FAIL
};


struct heap
{
	d_vector_t *heap;
	heap_cmp_func_t cmp;
	void *cmp_param;
};

heap_t *HeapCreate(heap_cmp_func_t cmp, void *cmp_param)
{
	heap_t *new_heap = NULL;
	
	assert(NULL != cmp);
	
	new_heap = (heap_t *)malloc(sizeof(heap_t));
	if(NULL == new_heap)
	{
		return NULL;
	}
	
	new_heap->heap = DVectorCreate(sizeof(size_t), 60);
	if(NULL == new_heap->heap)
	{
		free(new_heap);
		new_heap = NULL;
		return NULL;
	}
	
	new_heap->cmp = cmp;
	new_heap->cmp_param = cmp_param;
	
	return new_heap;
}

void HeapDestroy(heap_t *heap)
{
	assert(NULL != heap);
	
	DVectorDestroy(heap->heap);
	heap->heap = NULL;
	
	free(heap);
	heap = NULL;
}

int HeapPush(heap_t *heap, void *new_data)
{	
	int status = SUCCESS;
	
	assert(NULL != heap);
	
	status = DVectorPushBack(heap->heap, &new_data);
	HeapifyUp(heap, LAST_INDEX);
	
	return status;
}

void *HeapPop(heap_t *heap)
{	
	void *return_value = NULL;
	void **root_element = NULL;
	void **last_element = NULL;	
	
	assert(NULL != heap);
	assert(!HeapIsEmpty(heap));
	
	root_element = DVectorGetElement(heap->heap, HEAP_ROOT);
	last_element = DVectorGetElement(heap->heap, LAST_INDEX);
	return_value = *root_element;
	
	SwapElements(root_element, last_element);
	DVectorPopBack(heap->heap);
	HeapifyDown(heap, HEAP_ROOT);

	return return_value;
}

void *HeapRemove(heap_t *heap, void *to_remove, is_match_t match_func, 
															void *match_param)
{
	void **to_remove_element = NULL;
	void **last_element = NULL;
	void *return_value = NULL;
	size_t heap_size = 0;
	size_t index = 0;
	
	assert(NULL != heap);
	assert(NULL != match_func);	
	
	heap_size = HeapSize(heap);
	index = FindElement(heap, to_remove, match_func, match_param);

	if(index < heap_size)
	{
		to_remove_element = DVectorGetElement(heap->heap, index);
		last_element = DVectorGetElement(heap->heap, LAST_INDEX);
		return_value = *to_remove_element;
		
		SwapElements(to_remove_element, last_element);
		DVectorPopBack(heap->heap);
		HeapifyUp(heap, index);
		HeapifyDown(heap, index);
	}
	
	return return_value;
}

static size_t FindElement(heap_t *heap, void *to_remove, is_match_t match_func, 
															void *match_param)
{
	void **current_element = NULL;
	size_t index = 0;	
	size_t heap_size = 0;
		
	assert(NULL != heap);
	
	heap_size = HeapSize(heap);
	
	for(index = 0; index < heap_size; ++index)
	{
		current_element = DVectorGetElement(heap->heap, index);
		
		if(1 == (match_func(to_remove, *current_element, match_param)))
		{
			return index;
		}
	}
	
	return index; 
}

void *HeapPeek(heap_t *heap)
{
	void **data = NULL;
	
	assert(NULL != heap);
	
	data = DVectorGetElement(heap->heap, HEAP_ROOT);
	
	return *data;
}

size_t HeapSize(const heap_t *heap)
{
	assert(NULL != heap);
	
	return DVectorSize(heap->heap);
}

int HeapIsEmpty(const heap_t *heap)
{
	assert(NULL != heap);
	
	return DVectorIsEmpty(heap->heap);
}

static void HeapifyUp(heap_t *heap, int current_index)
{    
    size_t parent_index = 0;
    void **current_element = NULL;
    void **parent_element = NULL;
    int cmp_val = 0;

    assert(NULL != heap);

    while(current_index)
    {
        current_element = DVectorGetElement(heap->heap, current_index);
        parent_index = GetParent(current_index);
        parent_element = DVectorGetElement(heap->heap, parent_index);
        
        cmp_val = (heap->cmp)(*current_element, *parent_element, heap->cmp_param);
        if(0 < cmp_val)
        {    
            SwapElements(current_element, parent_element);
        }
        
        current_index = parent_index;
    }
}

static void HeapifyDown(heap_t *heap, size_t current_index)
{
	size_t child_to_swap_index = 0;
	size_t size = 0;
    void **current_element = NULL;
    void **child_to_swap_element = NULL;
    int cmp_val = 0;
	
    assert(NULL != heap);
	
	size = HeapSize(heap);
	
    while(!HasNoChildren(size, current_index) && current_index < size)
    {
    	current_element = DVectorGetElement(heap->heap, current_index);
    	child_to_swap_index = GetEldest(heap, current_index);
        child_to_swap_element = DVectorGetElement(heap->heap, 
        											child_to_swap_index);
    	
    	cmp_val = (heap->cmp)(*child_to_swap_element, *current_element, 
    													heap->cmp_param);      
        if(0 < cmp_val)
        {    
            SwapElements(current_element, child_to_swap_element);
        }
 
        current_index = child_to_swap_index;
    }
}

static size_t GetEldest(heap_t *heap, size_t parent_index)
{
	void **left_child = NULL;
	void **right_child = NULL;
	int eldest_index = 0;
	
	assert(NULL != heap);
	
	left_child = DVectorGetElement(heap->heap, GetLeftChild(parent_index));
	eldest_index = GetLeftChild(parent_index);
	
	if (LAST_INDEX >= GetRightChild(parent_index))
	{
		right_child = DVectorGetElement(heap->heap, GetRightChild(parent_index));
		if (0 < (heap->cmp)(*right_child, *left_child, heap->cmp_param))
		{
			eldest_index = GetRightChild(parent_index);
		}
	}
	
	return eldest_index;
}

static void SwapElements(void **element1, void **element2)
{
    void *temp = NULL;
    
    assert(NULL != element1);
    assert(NULL != element2);
    
    temp = *element1;
    *element1 = *element2;
    *element2 = temp;
}

static size_t GetParent(size_t child_index)
{
    assert(0 != child_index);
    
    return ((child_index - 1) / 2);
}

static size_t GetLeftChild(size_t parent_index)
{
    return ((parent_index * 2) + 1);
}

static size_t GetRightChild(size_t parent_index)
{
    return ((parent_index * 2) + 2);
}

static int HasNoChildren(size_t heap_size, size_t parent_index)
{
	size_t left_index = GetLeftChild(parent_index);
	size_t right_index = GetRightChild(parent_index);

	return ((left_index > heap_size - 1) && (right_index > heap_size - 1));
}

void PrintHeap(heap_t *heap)
{
	int *printer = NULL;
	size_t i = 0;
	size_t length = DVectorSize(heap->heap);
	
	assert(NULL != heap);
	
	for (i = 0; i < length; ++i)
	{
		printer = *(void **)(DVectorGetElement(heap->heap, i));
		assert(printer != NULL);
		printf (" %d |", *printer);
	}
	printf("\n");
}

