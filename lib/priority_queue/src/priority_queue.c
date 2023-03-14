#include <assert.h> /* assert */
#include <stdlib.h> /* malloc + free */

#include "heap.h"
#include "priority_queue.h"
#include "dynamic_vector.h"


struct pq
{
	heap_t *queue;
};


typedef struct pkg
{
	pq_is_match_t is_match;
}package_t;


static int Wrapper(const void *data, const void *heap_data, void *param);

pq_t *PQCreate(pq_cmp_func_t cmp_func, void *param)
{
	pq_t *queue = NULL;
	
	assert(NULL != cmp_func);
	
	queue = (pq_t *)malloc(sizeof(pq_t));
	if (NULL == queue)
	{
		return NULL;
	}
	
	queue->queue = HeapCreate(cmp_func, param);
	if (NULL == queue->queue)
	{
		free(queue);
		queue = NULL;
		return NULL;
	}
	
	return queue;
}
	
void PQDestroy(pq_t *pq)
{
	assert(NULL != pq);
	
	HeapDestroy(pq->queue);
	free(pq);
	pq = NULL;
}
	
int PQEnqueue(pq_t *pq, void *data)
{
	assert(NULL != pq);
	assert(NULL != data);
	
	return (HeapPush(pq->queue, data)); 
}
	
void *PQDequeue(pq_t *pq)
{
	assert(NULL != pq);
	
	return HeapPop(pq->queue);
}
	
int PQIsEmpty(const pq_t *pq)
{
	assert(NULL != pq);
	
	return HeapIsEmpty(pq->queue);
}
	
void *PQPeek(const pq_t *pq)
{
	assert(NULL != pq);
	
	return HeapPeek(pq->queue);
}

size_t PQSize(const pq_t *pq)
{
	assert(NULL != pq);
	
	return HeapSize(pq->queue);
}
	
void PQClear(pq_t *pq)
{
	assert(NULL != pq);
	
	while(!PQIsEmpty(pq))
	{
		PQDequeue(pq);
	}
}

void *PQErase(pq_t *pq, void *param, pq_is_match_t is_match)
{
	package_t pack = {NULL};

	assert(NULL != pq);
	assert(NULL != is_match);

	pack.is_match = is_match;

	return HeapRemove(pq->queue, param, &Wrapper, &pack);
}

static int Wrapper(const void *data, const void *heap_data, void *param)
{
	package_t *pack = (package_t *)param;

	return pack->is_match((void *)heap_data, (void *)data);
}

void PrintPQ(pq_t *pq)
{
	PrintHeap(pq->queue);
}

