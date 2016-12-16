#include <stdio.h>
#include <stdlib.h>
#include "ita3e_indexedseq.h"
#include "ita3e_errors.h"

int ita3e_item_indexedseq_init(ita3e_item_indexedseq_t* isq, int size) {
	ita3e_item_t* tmp = (ita3e_item_t*)calloc(size,sizeof(ita3e_item_t));
	if(tmp == NULL) {
		fprintf(stderr," Memory Allocation failed while creating indexed sequence ");
		return E_ITA3E_HEAPLOW;
	}
	isq->elements = tmp;
	isq->size	  = size;
	for(int i = 0; i < size; i++)
		isq->elements[i] = ita3e_item_init(0,0);
	return E_ITA3E_OK;
}

int ita3e_item_indexedseq_get(ita3e_item_indexedseq_t* isq, ita3e_item_t* x, int idx) {
	if(idx >= isq->size || idx < 0) {
		fprintf(stderr," Index out of bound \n");
		return E_ITA3E_OUTOFBOUND;
	}
	*x = isq->elements[idx];
	return E_ITA3E_OK;
}

int ita3e_item_indexedseq_set(ita3e_item_indexedseq_t* isq, ita3e_item_t x, int idx) {
	if(idx >= isq->size || idx < 0) {
		fprintf(stderr," Index out of bound \n");
		return E_ITA3E_OUTOFBOUND;
	}
	isq->elements[idx] = x;
	return E_ITA3E_OK;
}


void ita3e_item_indexedseq_print(ita3e_item_indexedseq_t* isq) {
	if(isq->size == 0) {
		fprintf(stderr," Indexed Sequence is Empty \n");
		return;
	}
	ita3e_item_t* sub = isq->elements;
	int count		  = isq->size;
	ita3e_item_array_print(sub,count);
}

int ita3e_item_indexedseq_insert(ita3e_item_indexedseq_t* isq, ita3e_item_t x, int idx) {
	if(idx > isq->size || idx < 0) {
		fprintf(stderr,"Index out of bound\n");
		return E_ITA3E_OUTOFBOUND;
	}
	int new_size  = isq->size + 1;
	ita3e_item_t* aux = (ita3e_item_t*)calloc(new_size,sizeof(ita3e_item_t));
	if(aux == NULL) {
		fprintf(stderr,"Reallocation failed during insertion\n");
		return E_ITA3E_HEAPLOW;
	}
	for(int i = 0; i < new_size; i++) {
		if(i < idx) aux[i] = isq->elements[i];
		else if (i == idx) aux[i] = x;
		else aux[i] = isq->elements[i-1];
	}
	ita3e_item_t* tmp = isq->elements;
	isq->elements     = aux;
	isq->size 		  = new_size;
	free(tmp);
	return E_ITA3E_OK;
}

int ita3e_item_indexedseq_delete(ita3e_item_indexedseq_t* isq, int idx) {
	if(idx >= isq->size || idx < 0) {
		fprintf(stderr,"Index out of bound\n");
		return E_ITA3E_OUTOFBOUND;
	}
	if(isq->size == 0) {
		fprintf(stderr,"Indexed Sequence Empty\n");
		return E_ITA3E_UNDERFLOW;
	}
	int new_size = isq->size - 1;
	if(new_size != 0) {
		ita3e_item_t* aux = (ita3e_item_t*)calloc(new_size,sizeof(ita3e_item_t));
		if(aux == NULL) {
			fprintf(stderr,"Reallocation failed during deletion\n");
			return E_ITA3E_HEAPLOW;
		}
		for(int i = 0; i < new_size; i++) {
			if(i < idx) aux[i] = isq->elements[i];
			else aux[i] = isq->elements[i+1];
		}
		ita3e_item_t* tmp = isq->elements;
		isq->elements     = aux;
		free(tmp);
	}
	else
		isq->elements = NULL;
	isq->size = new_size;
	return E_ITA3E_OK;
}
