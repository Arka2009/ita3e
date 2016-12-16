#include <stdio.h>
#include <stdlib.h>
#include "ita3e_stack.h"
#include "ita3e_errors.h"

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
		printf("Dynamic allocation failed during linked stack push operation\n");
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
		printf(" Stack Empty cannot pop ");
		printf("\n");
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
		printf(" Stack is Empty \n");
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
