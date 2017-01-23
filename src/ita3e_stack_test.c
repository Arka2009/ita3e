#include <stdio.h>
#include <stdlib.h>
#include "ita3e.h"
#include "ita3e_stack.h"
#include "ita3e_errors.h"

int ita3e_stack_test() {
	ita3e_item_stack_t stack;
	int push_status, pop_status;
	ita3e_item_t x;
	ita3e_item_stack_init(&stack);
	
	/* Stack Push */
	int num_insertions = 3;
	int i = 1;
	while(i <= num_insertions) {
		ita3e_item_t tmp = ita3e_item_init(rand()/112034,rand()/882034);
		push_status = ita3e_item_stack_push(&stack,tmp);
		if(push_status != E_ITA3E_OK) {
			printf(" Unable to push(err-%d)\n",push_status);
			exit(push_status);
		}
		printf(" Item to be pushed(%d) : ",i);
		ita3e_item_print(tmp);
		printf("\n");
		printf(" stack.status-after-push(%d) : ",i);
		ita3e_item_stack_print(&stack);
		printf("\n");
		i++;
	}

	/* Stack Pop */
	int num_deletions = 4;
	i = 1;
	while(i <= num_deletions) {
		pop_status = ita3e_item_stack_pop(&stack,&x);
		if(pop_status != E_ITA3E_OK) {
			printf(" Unable to pop(err-%d)\n",pop_status);
			exit(pop_status);
		}
		printf(" stack.status-after-pop(%d) : ",i);
		ita3e_item_stack_print(&stack);
		printf("\n");
		printf(" Item poped(%d) : ",i);
		ita3e_item_print(x);
		printf("\n");
		i++;
	}
	return E_ITA3E_OK;
}
