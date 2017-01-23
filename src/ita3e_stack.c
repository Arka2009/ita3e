#include <stdio.h>
#include <stdlib.h>
#include "ita3e_stack.h"
#include "ita3e_errors.h"

/* Array Implementation of Stack */
void ita3e_item_array_stack_init(ita3e_item_array_stack_t* astack) {
	astack->top   = -1;
	astack->count = 0;
}

int ita3e_item_array_stack_isFull(ita3e_item_array_stack_t* astack) {
	return astack->count == MAX_ARRAY_SIZE;
}

int ita3e_item_array_stack_isEmpty(ita3e_item_array_stack_t* astack) {
	return astack->count == 0;
}

int ita3e_item_array_stack_push(ita3e_item_array_stack_t* astack, ita3e_item_t x) {
	if(ita3e_item_array_stack_isFull(astack)) {
		fprintf(stderr," Array Stack Full\n");
		return E_ITA3E_OVERFLOW;
	}
	astack->elements[++(astack->top)] = x;
	astack->count++;
	return E_ITA3E_OK;
}

int ita3e_item_array_stack_pop(ita3e_item_array_stack_t* astack, ita3e_item_t* x){
	if(ita3e_item_array_stack_isEmpty(astack)) {
		fprintf(stderr," Array Stack Empty\n");
		return E_ITA3E_UNDERFLOW;
	}
	*x = astack->elements[(astack->top)--];
	astack->count--;
	return E_ITA3E_OK;
}

void ita3e_item_array_stack_print(ita3e_item_array_stack_t* astack) {
	if(ita3e_item_array_stack_isEmpty(astack)) {
		fprintf(stderr," Array Stack Empty \n");
		return;
	}
	ita3e_item_t sub[MAX_ARRAY_SIZE];
	int N = astack->count;
	int j = 0;
	for(int i = N-1; i >= 0; i--)
		sub[j++] = astack->elements[i];
	ita3e_item_array_print(sub,N);
}

/* (Singly) Linked List Implementation */
void ita3e_item_linked_stack_init(ita3e_item_linked_stack_t* lstack) {
	lstack->top = NULL;
	lstack->count = 0;	
}

int ita3e_item_linked_stack_isFull (ita3e_item_linked_stack_t* lstack) {
	return 0;
}

int ita3e_item_linked_stack_isEmpty(ita3e_item_linked_stack_t* lstack) {
	return lstack->count == 0;
}

int ita3e_item_linked_stack_push(ita3e_item_linked_stack_t* lstack, ita3e_item_t x) {
	ita3e_singlylinked_node_t* tmp = (ita3e_singlylinked_node_t*)malloc(sizeof(ita3e_singlylinked_node_t));
	if(!tmp) {
		fprintf(stderr,"Dynamic allocation failed during linked stack push operation\n");
		return E_ITA3E_HEAPLOW;
	}
	tmp->data = x;
	tmp->next = lstack->top;
	lstack->top = tmp;
	lstack->count++;
	return E_ITA3E_OK;
}

int ita3e_item_linked_stack_pop(ita3e_item_linked_stack_t* lstack, ita3e_item_t* x_ptr) {
	if(ita3e_item_linked_stack_isEmpty(lstack)) {
		fprintf(stderr,"Stack Empty cannot pop\n");
		return E_ITA3E_UNDERFLOW;
	}
	ita3e_singlylinked_node_t* tmp = lstack->top;
	lstack->top = lstack->top->next;
	*x_ptr = tmp->data;
	tmp->next = NULL;
	lstack->count--;
	free(tmp);
	return E_ITA3E_OK;
}

void ita3e_item_linked_stack_print(ita3e_item_linked_stack_t* lstack) {
	if(ita3e_item_linked_stack_isEmpty(lstack)) {
		fprintf(stderr,"Stack is Empty\n");
		return;
	}
	ita3e_item_t sub[MAX_ARRAY_SIZE];
	int i = 0;
	int N = lstack->count;
	ita3e_singlylinked_node_t* itr = lstack->top;
	while(itr != NULL) {
		sub[i++] = itr->data;
		itr = itr->next;
	}
	ita3e_item_array_print(sub,N);
}

/* Unified Implementation */
void ita3e_item_stack_init(ita3e_item_stack_t* stack) {
	#ifdef LINKED_STACK
		ita3e_item_linked_stack_init(stack);
	#else
		ita3e_item_array_stack_init(stack);
	#endif
}

int ita3e_item_stack_push(ita3e_item_stack_t* stack, ita3e_item_t x) {
	#ifdef LINKED_STACK
		return ita3e_item_linked_stack_push(stack,x);
	#else
		return ita3e_item_array_stack_push(stack,x);
	#endif
}

int ita3e_item_stack_pop(ita3e_item_stack_t* stack, ita3e_item_t* x) {
	#ifdef LINKED_STACK
		return ita3e_item_linked_stack_pop(stack,x);
	#else
		return ita3e_item_array_stack_pop(stack,x);
	#endif
}

int ita3e_item_stack_isFull(ita3e_item_stack_t* stack) {
	#ifdef LINKED_STACK
		return ita3e_item_linked_stack_isFull(stack);
	#else
		return ita3e_item_array_stack_isFull(stack);
	#endif
}

int ita3e_item_stack_isEmpty(ita3e_item_stack_t* stack) {
	#ifdef LINKED_STACK
		return ita3e_item_linked_stack_isEmpty(stack);
	#else
		return ita3e_item_array_stack_isEmpty(stack);
	#endif
}

void ita3e_item_stack_print(ita3e_item_stack_t* stack) {
	#ifdef LINKED_STACK
		return ita3e_item_linked_stack_print(stack);
	#else
		return ita3e_item_array_stack_print(stack);
	#endif
}
