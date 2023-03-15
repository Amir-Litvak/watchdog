#ifndef __DYNAMIC_VECTOR_H__
#define __DYNAMIC_VECTOR_H__

#include <stddef.h>	/* size_t */

/*******************************************************************************
                                Dynamic Vector
******************************************************************************** 
Attributes and policy:
	-   Random access
	-   Holds elements by value
	-   Growth factor of double the capacity
	-	Reduction factor of half the capacity
	-	Size-Capacity ratio to reduction is 1/4

--------------------------------------------------------------------------------

Operations on DV:
	-	Push back  
	-	Pop back
	-	Get access to element in vector
	-	Get current number of existing elements
	-	Get the current capacity of the vector
	-	Check if vector is empty
	-	Reserve and allocate memory for future insertions
	-	Shrink vector capacity to fit current number of existing elements

*******************************************************************************/

/*******************************************************************************
                                 Typedefs
*******************************************************************************/

typedef struct vector d_vector_t; 

/******************************************************************************/


/*******************************************************************************
                               Func declarations
*******************************************************************************/

/*******************************************************************************
DVectorCreate
Description: creates a new dynamic vector
Parameters: 
	- element_size: size of the element that is to be stored, in bytes.
	- capacity: initial number of elements to be stored.
Return value:
	- in case of failure, will return null
Complexity: O(n) time
*******************************************************************************/
d_vector_t *DVectorCreate(size_t element_size, size_t capacity);


/*******************************************************************************
DVectorDestroy
Description: frees the allocated memory.
Parameters: 
	- *vector: d_vector_t pointer, the dynamic vector that you work on. 
Return value:
	- void
Complexity: O(1) time 
*******************************************************************************/
void DVectorDestroy(d_vector_t *vector);


/*******************************************************************************
DVectorSize
Description: returns the current number of existing elements.
Parameters: 
	- *vector: d_vector_t pointer, the dynamic vector that you work on. 
Return value:
	- returns the size_t value of size.
Complexity: O(1) time 
*******************************************************************************/
size_t DVectorSize(const d_vector_t *vector);


/*******************************************************************************
DVectorCapacity
Description: returns the current capacity number of the vector.
Parameters: 
	- *vector: d_vector_t pointer, the dynamic vector that you work on. 
Return value:
	- returns the size_t value of current capacity.
Complexity: O(1) time
*******************************************************************************/
size_t DVectorCapacity(const d_vector_t *vector);


/*******************************************************************************
DVectorPushBack
Description: Pushes a new element into the vector.
Parameters: 
	- *vector: d_vector_t pointer, the dynamic vector that you work on.
	- *data: the data you wish to push into the vector.
Return value:
	- in case of failure to reallocate memory, will return 1. otherwise return
	  value upon success is 0.
Complexity: O(n) time.
Notes: when reaches full vector capacity, will increase capacity by
	   growth factor of 2.
*******************************************************************************/
int DVectorPushBack(d_vector_t *vector,const void *data);


/*******************************************************************************
DVectorPopBack
Description: Pops the last inserted element of the vector.
Parameters: 
	- *vector: d_vector_t pointer, the dynamic vector that you work on. 
Return value:
	- in case of failure to reallocate memory, will return 1. otherwise return
	  value upon success is 0.
Complexity: O(1) time, 
Notes: if reaches under 1/4 of vector capacity, will decrease capacity by
	   reduction factor of 2.
	  
*******************************************************************************/
int DVectorPopBack(d_vector_t  *vector);


/*******************************************************************************
DVectorGetElement
Description: Get access to element in vector
Parameters: 
	- *vector: d_vector_t pointer, the dynamic vector that you work on. 
	- index: the index of requested element.
Return value:
	- returns pointer to the requested element.
Complexity: O(1) time, 
Notes: if asked to access an index greater than the number of existing elements,
	   undefined behaviour occurs.
*******************************************************************************/
void *DVectorGetElement(const d_vector_t *vector, size_t index);


/*******************************************************************************
DVectorIsEmpty
Description: checks to see if the vector is currently empty.
Parameters: 
	- *vector: d_vector_t pointer, the dynamic vector that you work on. 
Return value:
	- returns boolean int.
Complexity: O(1) time
*******************************************************************************/
int DVectorIsEmpty(const d_vector_t *vector);


/*******************************************************************************
DVectorReserve
Description: Reserves memory for futre element insertions.
Parameters: 
	- *vector: d_vector_t pointer, the dynamic vector that you work on.  
	- new_capacity: asks for the the new capacity value
Return value:
	- in case of failure to reallocate memory, will return 1. otherwise return
	  value upon success is 0.
Complexity: O(n) time
Notes: if the new capacity value is lower than the current number of existing
	   elements in the vector, the capacity will match the size + 1.
*******************************************************************************/
int DVectorReserve(d_vector_t *vector, size_t new_capacity);


/*******************************************************************************
DVectorShrinkToFit
Description: Shrinks vector allocated memory to fit the current number of
			 existing elements + 1.
Parameters: 
	- *vector: d_vector_t pointer, the dynamic vector that you work on.  
Return value:
	- in case of failure to reallocate memory, will return 1. otherwise return
	  value upon success is 0.
Complexity: O(n) time
*******************************************************************************/
int DVectorShrinkToFit(d_vector_t *vector);


#endif /*__D_VECTOR_H__*/
