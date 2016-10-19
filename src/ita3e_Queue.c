#include <stdio.h>
#include <stdlib.h>
#include "ita3e_Queue.h"
#include "ita3e_Errors.h"

void ArrayQueueInit(struct ArrayQueue * q) {
	q->head = 0;
	q->tail = 0;
	q->count = 0;
	int i;
	for(i=0; i<MAX_ARRAY_SIZE; i++) {
		q->elements[i] = 0;
	}
}

int LinkedQueueInit(struct LinkedQueue * lq) {
	// Create a Node from the Heap
	struct NodeType * defaultNode = (struct NodeType *) malloc(sizeof(struct NodeType));
	if(!defaultNode) {
		printf(" Cannot Create a New Node, No Space in Heap");
		return E_ITA3E_HEAPLOW; 
	}
	else {
		defaultNode->data = 0;
		defaultNode->next = NULL;
		lq->count	 = 0;
		lq->head	 = defaultNode;
		lq->tail	 = defaultNode;
	}
	return E_ITA3E_OK;
}

int isArrayQueueFull(struct ArrayQueue * q) {
	return (q->count == MAX_ARRAY_SIZE);
}

int isArrayQueueEmpty(struct ArrayQueue * q) {
	return (q->count == 0);
}

int ArrayEnq(struct ArrayQueue * q, int x) {
	if(isArrayQueueFull(q)) return E_ITA3E_OVERFLOW;
	else {
		q->elements[q->head] = x;
		q->head = (q->head < MAX_ARRAY_SIZE-1)?(q->head + 1):0;
		q->count++;
		return E_ITA3E_OK;
	}
}

int ArrayDeq(struct ArrayQueue * q, int * x_ptr) {
	if(isArrayQueueEmpty(q)) return E_ITA3E_UNDERFLOW;
	else {
		*x_ptr = q->elements[q->tail];
		q->tail = (q->tail < MAX_ARRAY_SIZE-1)?(q->tail + 1):0;
		q->count--;
		return E_ITA3E_OK;
	}
}

void DisplayArrayQueue(struct ArrayQueue * q) {
	int sub[MAX_ARRAY_SIZE];
	int j,i;
	int h = q->head;
	int t = q->tail;
	int count = q->count;

	if(isArrayQueueEmpty(q)) printf(" Queue is Empty \n");
	if(t < h) {
		for(i=0,j=t; j<h; j++) {
			sub[i] = q->elements[j];
			i++;
		}
	}
	else {
		for(i=0, j=t; j<MAX_ARRAY_SIZE; j++) {
			sub[i] = q->elements[j];
			i++;
		}
		for(j=0; j<h; j++) {
			sub[i] = q->elements[j];
			i++;
		}
	}

	DisplayArrayInt(sub,count);
}
