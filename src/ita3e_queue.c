#include <stdio.h>
#include <stdlib.h>
#include "ita3e_queue.h"
#include "ita3e_errors.h"

void ita3e_item_array_queue_init(ita3e_item_array_queue_t* aq) {
	aq->head = 0;
	aq->tail = 0;
	aq->count = 0;
	int i;
	for(i=0; i<MAX_ARRAY_SIZE; i++) {
		aq->elements[i] = ita3e_item_init(0,0);
	}
}

int ita3e_item_array_queue_isFull(ita3e_item_array_queue_t* aq) {
	return (aq->count == MAX_ARRAY_SIZE);
}

int ita3e_item_array_queue_isEmpty(ita3e_item_array_queue_t* aq) {
	return (aq->count == 0);
}

int ita3e_item_array_queue_enq(ita3e_item_array_queue_t* aq, ita3e_item_t x) {
	if(ita3e_item_array_queue_isFull(aq)) return E_ITA3E_OVERFLOW;
	else {
		aq->elements[aq->head] = x;
		aq->head = (aq->head < MAX_ARRAY_SIZE-1)?(aq->head + 1):0;
		aq->count++;
		return E_ITA3E_OK;
	}
}

int ita3e_item_array_queue_deq(ita3e_item_array_queue_t* aq, ita3e_item_t* x_ptr) {
	if(ita3e_item_array_queue_isEmpty(aq)) return E_ITA3E_UNDERFLOW;
	else {
		*x_ptr = aq->elements[aq->tail];
		aq->tail = (aq->tail < MAX_ARRAY_SIZE-1)?(aq->tail + 1):0;
		aq->count--;
		return E_ITA3E_OK;
	}
}

void ita3e_item_array_queue_print(ita3e_item_array_queue_t* aq) {
	ita3e_item_t sub[MAX_ARRAY_SIZE];
	int j,i;
	int h = aq->head;
	int t = aq->tail;
	int count = aq->count;

	if(ita3e_item_array_queue_isEmpty(aq)) {
		printf(" Queue is Empty \n");
		return;
	}

	if(t < h) {
		for(i=0,j=t; j<h; j++, i++) sub[i] = aq->elements[j];
	}
	else {
		for(i=0, j=t; j<MAX_ARRAY_SIZE; j++, i++) sub[i] = aq->elements[j];
		for(j=0; j<h; j++, i++) sub[i] = aq->elements[j];
	}

	ita3e_item_array_print(sub,count);
}

// Queue implemented as linked list
void ita3e_item_linked_queue_init(ita3e_item_linked_queue_t* lq) {
	lq->count	 = 0;
	lq->head	 = NULL;
	lq->tail	 = NULL;
}

int ita3e_item_linked_queue_isFull(ita3e_item_linked_queue_t* lq) {
 	/**
	 * Linked List are dynamically allocated so they are never "full"
	 * unless ofcourse they run out of Heap, which will generate different
	 * error response code.
	 */
	return 0;
}

int ita3e_item_linked_queue_isEmpty(ita3e_item_linked_queue_t* lq) {
	return (lq->count == 0);
}

int ita3e_item_linked_queue_enq(ita3e_item_linked_queue_t* lq, ita3e_item_t x) {
	if(ita3e_item_linked_queue_isFull(lq)) return E_ITA3E_OVERFLOW;
	ita3e_doublylinked_node_t* tmp = (ita3e_doublylinked_node_t*)malloc(sizeof(ita3e_doublylinked_node_t));
	if(!tmp) {
		printf(" Dynamic Memory allocation failed ");
		return E_ITA3E_HEAPLOW;
	}
	tmp->data = x;
	if(ita3e_item_linked_queue_isEmpty(lq)) {
		lq->head = tmp;
		lq->tail = tmp;
	}
	else {
		tmp->next = lq->head;
		tmp->prev = NULL;
		lq->head->prev = tmp;
		lq->head  = tmp;
	}
	lq->count++;
	return E_ITA3E_OK;
}

int ita3e_item_linked_queue_deq(ita3e_item_linked_queue_t* lq, ita3e_item_t* x_ptr) {
	if(ita3e_item_linked_queue_isEmpty(lq)) return E_ITA3E_UNDERFLOW;
	ita3e_doublylinked_node_t* tmp = lq->tail;
	*x_ptr						   = tmp->data;
	if(lq->count == 1) {
		lq->head = NULL;
		lq->tail = NULL;
	}
	else {
		lq->tail 					   = lq->tail->prev;
		lq->tail->next 				   = NULL;
	}
	lq->count--;
	free(tmp);
	return E_ITA3E_OK;
}

void ita3e_item_linked_queue_print(ita3e_item_linked_queue_t* lq) {
	if(ita3e_item_linked_queue_isEmpty(lq)) {
		printf(" Queue is Empty");
		return;	
	}
	ita3e_item_t sub[MAX_ARRAY_SIZE];
	int count = lq->count;
	int i = 0;
	ita3e_doublylinked_node_t* itr = lq->tail;
	while(itr != NULL) {
		sub[i++] = itr->data; 
		itr = itr->prev;
	}
	ita3e_item_array_print(sub,count);
}
