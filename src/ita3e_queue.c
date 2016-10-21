#include <stdio.h>
#include <stdlib.h>
#include "ita3e_queue.h"
#include "ita3e_errors.h"

void ita3e_item_array_queue_init(ita3e_item_array_queue_t* q) {
	q->head = 0;
	q->tail = 0;
	q->count = 0;
	int i;
	for(i=0; i<MAX_ARRAY_SIZE; i++) {
		q->elements[i] = ita3e_item_init(0,0);
	}
}

int ita3e_item_linked_queue_init(ita3e_item_linked_queue_t* lq) {
	lq->count	 = 0;
	lq->head	 = NULL;
	lq->tail	 = NULL;
	return E_ITA3E_OK;
}

int ita3e_item_array_queue_isFull(ita3e_item_array_queue_t* q) {
	return (q->count == MAX_ARRAY_SIZE);
}

int ita3e_item_array_queue_isEmpty(ita3e_item_array_queue_t* q) {
	return (q->count == 0);
}

int ita3e_item_array_queue_enq(ita3e_item_array_queue_t* q, ita3e_item_t x) {
	if(ita3e_item_array_queue_isFull(q)) return E_ITA3E_OVERFLOW;
	else {
		q->elements[q->head] = x;
		q->head = (q->head < MAX_ARRAY_SIZE-1)?(q->head + 1):0;
		q->count++;
		return E_ITA3E_OK;
	}
}

int ita3e_item_array_queue_deq(ita3e_item_array_queue_t* q, ita3e_item_t* x_ptr) {
	if(ita3e_item_array_queue_isEmpty(q)) return E_ITA3E_UNDERFLOW;
	else {
		*x_ptr = q->elements[q->tail];
		q->tail = (q->tail < MAX_ARRAY_SIZE-1)?(q->tail + 1):0;
		q->count--;
		return E_ITA3E_OK;
	}
}

void ita3e_item_array_queue_print(ita3e_item_array_queue_t* q) {
	ita3e_item_t sub[MAX_ARRAY_SIZE];
	int j,i;
	int h = q->head;
	int t = q->tail;
	int count = q->count;

	if(ita3e_item_array_queue_isEmpty(q)) printf(" Queue is Empty \n");
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

	ita3e_item_array_print(sub,count);
}
