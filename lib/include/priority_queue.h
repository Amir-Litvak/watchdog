#ifndef __PQ__
#define __PQ__

#include <stddef.h>

/*******************************************************************************
  _____      _            _ _              ____                        
 |  __ \    (_)          (_) |            / __ \                       
 | |__) | __ _  ___  _ __ _| |_ _   _    | |  | |_   _  ___ _   _  ___ 
 |  ___/ '__| |/ _ \| '__| | __| | | |   | |  | | | | |/ _ \ | | |/ _ \
 | |   | |  | | (_) | |  | | |_| |_| |   | |__| | |_| |  __/ |_| |  __/
 |_|   |_|  |_|\___/|_|  |_|\__|\__, |    \___\_\\__,_|\___|\__,_|\___|
                                 __/ |                                 
                                |___/                                  
*******************************************************************************/

/*******************************************************************************
                                 Typedefs
*******************************************************************************/

typedef struct pq pq_t;
typedef int(*pq_cmp_func_t)(const void *new_data, const void *current_data,
																 void *param);
typedef int(*pq_is_match_t)(const void *current_data, void *param);

/*******************************************************************************
                                 Functions
*******************************************************************************/


/*******************************************************************************
Description: Creates a Priority Queue.
Parameters: User defined compare function,
			pramater to further customize function.
Return value: returns a to the created queue, NULL if failed.
Complexity: O(1) time
*******************************************************************************/
pq_t *PQCreate(pq_cmp_func_t cmp_func, void *param);

/*******************************************************************************
Description: Destroys the priority queue.
Parameters: Recieves a priority queue pointer.
Return value: none.
Complexity: O(n) time
*******************************************************************************/	
void PQDestroy(pq_t *pq);

/*******************************************************************************
Description: Inserts an element by priority to its respected place in the queue.
Parameters: Recieves a priority queue pointer, data to insert.
Return value: Boolen success status.
Complexity: O(n) time
Notes: Same-priority elements would be inserted by FIFO.
	Inserted data cannot be null.
*******************************************************************************/	
int PQEnqueue(pq_t *pq, void *data);

/*******************************************************************************
Description: Removes an element and returns it's stored data.
Parameters: Recieves a priority queue pointer.
Return value: Returns stored data in element.
Complexity: O(1) time
Notes: Undefined behaviour upon EOQ removal. 
*******************************************************************************/	
void *PQDequeue(pq_t *pq);

/*******************************************************************************
Description: Checks if the queue is empty.
Parameters: Recieves a priority queue pointer.
Return value: Boolean.
Complexity: O(1) time
*******************************************************************************/	
int PQIsEmpty(const pq_t *pq);


/*******************************************************************************
Description: Returns an data from the start of the queue.
Parameters: Recieves a priority queue pointer.
Return value: Data stored in element.
Complexity: O(1) time
*******************************************************************************/	
void *PQPeek(const pq_t *pq);

/*******************************************************************************
Description: Counts the number of elements in queue.
Parameters: Recieves a priority queue pointer.
Return value: Count of elements.
Complexity: O(n) time 
*******************************************************************************/
size_t PQSize(const pq_t *pq);

/*******************************************************************************
Description: Clears the queue - removes all elements without destorying it.
Parameters: Recieves a priority queue pointer.
Return value: None.
Complexity: O(n) time 
*******************************************************************************/	
void PQClear(pq_t *pq);

/*******************************************************************************
Description: Removes one element by parameter.
Parameters: Recieves a priority queue pointer, match function and parameter
			to search the queue for the element
Return value: Stored data in element, NULL if element wasn't found.
Complexity: O(n) time 
*******************************************************************************/
void *PQErase(pq_t *pq, void *param, pq_is_match_t is_match);


void PrintPQ(pq_t *pq);

#endif /* __PQ__ */
