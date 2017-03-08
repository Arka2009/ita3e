#include <stdio.h>
#include <stdlib.h>
#include "ita3e.h"
#include "ita3e_list.h"
#include "ita3e_errors.h"

int ita3e_item_list_init(ita3e_item_list_t* l) {
	*l = NULL; 			// An Empty list is an initialized list
	return E_ITA3E_OK;
}

/* prepends an item, (appending is not supported) */
int ita3e_item_list_cons(ita3e_item_list_t* l, ita3e_item_t x) {
	ita3e_singlylinked_node_t* tmp = \
	(ita3e_singlylinked_node_t*)malloc(sizeof(ita3e_singlylinked_node_t));
	
	if(!tmp) {
		fprintf(stderr,"Dynamic memory allocation failed");
		return E_ITA3E_HEAPLOW;
	}
	#ifdef ITA3E_DEBUG
	printf("List Before Push : ");
	ita3e_item_list_traverse(*l, true);
	#endif
	tmp->data = x;
	tmp->next = *l;
	*l = tmp;
	return E_ITA3E_OK;
}

/* returns the head of the list */
//int ita3e_item_list_head(ita3e_item_list_t* l, ita3e_item_t* x) {
//	if(*l == NULL) {
//		fprintf(stderr,"Underflow");
//		return E_ITA3E_UNDERFLOW; 
//	}
//	*
//}

/* Print the contents of each node */
int ita3e_item_list_traverse_aux(ita3e_item_list_t l, int depth, bool forward) {
	if(l == NULL) {
		if(depth == 0)
			printf("List is empty\n");
		printf("[]\n");
		return E_ITA3E_OK;
	}
	else {
		if(forward) {
			ita3e_item_print(l->data);
			printf(":");
			
			ita3e_item_list_traverse_aux(l->next,++depth,forward);
		}
		else {
			ita3e_item_list_traverse_aux(l->next,++depth,forward);
			
			printf(":");
			ita3e_item_print(l->data);
		}
	}
	return E_ITA3E_OK;
}

int ita3e_item_list_traverse(ita3e_item_list_t l, bool forward) {
	return ita3e_item_list_traverse_aux(l,0,forward);
}
