#ifndef __HEAP_H__
#define __HEAP_H__

#include <stddef.h> /* size_t */

/*****************************************************************************
																 
*******************************************************************************

								Heap
								
********************************************************************************
Despcription:
Heap data structure is a complete binary tree that satisfies the heap property, 
where any given node is: (1) always greater than its child node/s and the key of 
the root node is the largest among all other nodes, or (2) always smaller than the 
child node/s and the key of the root node is the smallest among all other nodes. 

-------------------------------------------------------------------------------

Operations on Heap:
	- Create and Destroy a Heap.
	- Pop or Push an element from the Heap.
	- Peek on the "Root" node.
	- Check if the Heap is empty, and get its current size.
	- replace an element on the Heap.

*******************************************************************************/


/*******************************************************************************
                                 Typedefs
*******************************************************************************/

/*
return 0 if equal
returns > 1 if new_data > current_data
returns < 1 if new_data < current_data
*/
typedef int (*heap_cmp_func_t)(const void *new_data, const void *current_data, void *cmp_param);

/*
bool return: 1 if match, 0 if not a match
*/
typedef int (*is_match_t)(const void *data, const void *heap_data, void *param);

typedef struct heap heap_t;

/*******************************************************************************
                                Functions
*******************************************************************************/

/******************************************************************************
HeapCreate
Description: Create a new Heap.
Parameters: 
	- cmp: 	a pointer to a user-sent compare function.
	- cmp_param: a paremeter to be used in the compare function.
Return value:						
	- 	a pointer to the newly-created Heap. 
	-	in case of failure, will return NULL.
Time Complexity: O(1).			
Notes: 	in case of wrong or NULL reference, undefined behaviour occurs.
*****************************************************************************/
heap_t *HeapCreate(heap_cmp_func_t cmp, void *cmp_param);

/******************************************************************************
HeapDestroy
Description: Destroy a Heap.
Parameters: 
	- heap: a pointer to the to-be-destroyed Heap.
Time Complexity: O(1).
Notes: in case of wrong or NULL reference, undefined behaviour occurs.
*****************************************************************************/
void HeapDestroy(heap_t *heap);

/******************************************************************************
HeapPush
Description: Push an element to a Heap.
Parameters: 
	- heap: a pointer to a Heap.
	- new_data: a pointer to the new element.
Return value:
	- in case of success, will return 0. 
	- else, will return 1. 
Time Complexity: O(log n).
Notes: 
	- in case of wrong or NULL reference, undefined behaviour occurs.
	- even when the allocation fails, the new element will be added. 
*****************************************************************************/
int HeapPush(heap_t *heap, void *new_data);

/******************************************************************************
HeapPop
Description: Pop an element from the Heap.  
Parameters: 
	- heap: a Pointer to a heap.
Return value:
	- the data stored in the "poped" element. 
Time Complexity: O(log n).
Notes: in case of wrong or NULL reference, undefined behaviour occurs.
*****************************************************************************/
void *HeapPop(heap_t *heap);

/******************************************************************************
HeapRemove
Description: Removes an element from the Heap.
Parameters: 
	- 	heap: a pointer to a Heap.
	-	to_remove: a void pointer with the data to remove.
	-	match_func: a pointer to a user-send function.
	-	match_param: a parameter to be used in the match_func.
Return value: 
	- 	None.
Time Complexity: O(n).
Notes: in case of wrong or NULL reference, undefined behaviour occurs.
*****************************************************************************/
void *HeapRemove(heap_t *heap, void *to_remove, is_match_t match_func, void *match_param);

/******************************************************************************
HeapPeek
Description: Peek on the "root" node of the Heap. 
Parameters: 
	- 	heap: a pointer to a Heap.
Return value: 
	- 	a void pointer with the data stored in the "root" node.
Time Complexity: O(1).
Notes: in case of wrong or NULL reference, undefined behaviour occurs.
*****************************************************************************/
void *HeapPeek(heap_t *heap); 

/******************************************************************************
HeapReplace
Description: Removes an element from the Heap and insert new_data.
Parameters: 
	- 	heap: a pointer to a Heap.
	-	new_data: a pointer to the new data to replace.
Return value: 
	- in case of success, will return 0. 
	- else, will return 1. 
Time Complexity: O(log n).
Notes: in case of wrong or NULL reference, undefined behaviour occurs.
*****************************************************************************/
int HeapReplace(heap_t *heap, void *new_data);

/******************************************************************************
HeapSize
Description: Checks the number of elements in a Heap.
Parameters: 
	- heap: a pointer to a Heap.
Return value:
	- the number of elements in the Heap.
Time Complexity: O(1).
Notes: in case of wrong or NULL reference, undefined behaviour occurs.
*****************************************************************************/
size_t HeapSize(const heap_t *heap);

/******************************************************************************
HeapIsEmpty
Description: Checks if a Heap is empty.
Parameters: 
	- heap: a pointer to a heap.
Return value:
	- TRUE (1) 
	- FALSE (0).
Time Complexity: O(1).
Notes: in case of wrong or NULL reference, undefined behaviour occurs.
*****************************************************************************/
int HeapIsEmpty(const heap_t *heap);



void PrintHeap(heap_t *heap);

#endif /* __HEAP_H__ */
