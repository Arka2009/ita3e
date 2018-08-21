#include <stdio.h>
#include <stdlib.h>
#include "ita3e.h"
#include "ita3e_list.h"
#include "ita3e_errors.h"

int ita3e_item_list_init(ita3e_item_list_t **l) {
	*l = NULL; 			// An Empty list is an initialized list
	return E_ITA3E_OK;
}

/* construct a list of given length */
int ita3e_item_list_cons(ita3e_item_list_t **l, unsigned int len) {
	ita3e_singlylinked_node_t* tmp;

	/* Base Case */
	printf("value of len = %d\n",len);
	if(!len) {
		*l = NULL;
		return E_ITA3E_OK;
	}

	/* Create a New Node */
	tmp = \
	(ita3e_singlylinked_node_t*)malloc(sizeof(ita3e_singlylinked_node_t));
	
	if(!tmp) {
		fprintf(stderr,"Dynamic memory allocation failed");
		exit(E_ITA3E_OUTOFBOUND);
	}
	*l 		  = tmp;
	tmp->data = ita3e_item_init(rand()/200,rand()/0x4de);
	tmp->next = NULL;
	
	ita3e_item_list_cons(&((*l)->next), --len);

	#ifdef ITA3E_DEBUG
	printf("List Before Push : ");
	ita3e_item_list_traverse(*l, true);
	#endif

	return E_ITA3E_OK;
}

/* Clean the memory allocated to list */
int ita3e_item_list_clean_first(ita3e_item_list_t **l) {
	if(*l == NULL)
		return E_ITA3E_OK;

	ita3e_item_list_t *tmp = *l;
	*l = (*l)->next;
	tmp->next = NULL;
	free(tmp);
	return E_ITA3E_OK;
}

/* Cleanup the entire memory for the linked list */
int ita3e_item_list_clean_all(ita3e_item_list_t **l) {
	int ret;
	if(*l == NULL)
		return E_ITA3E_OK;

	ret = ita3e_item_list_clean_all(&((*l)->next));
	return ret;
}

/* Print the contents of each node */
int ita3e_item_list_traverse_aux(ita3e_item_list_t *l, int depth, bool forward) {
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

int ita3e_item_list_insert_aux(ita3e_item_list_t **l,key_t k,unsigned int pos) {
	ita3e_singlylinked_node_t *tmp;
	//static key_t vertex_id = 0;

	if(!pos) {
		/* Insert at the beginning */
		tmp = \
		(ita3e_singlylinked_node_t*)malloc(sizeof(ita3e_singlylinked_node_t));

		if(!tmp) {
			fprintf(stderr,"Memory allocation failed\n");
			exit(E_ITA3E_OUTOFBOUND);
		}

		tmp->data 		= ita3e_item_init(k,rand() % 0x4edf);
		tmp->next 		= *l;
		tmp->vertex_id 	= k;//vertex_id++;
		*l		  		= tmp;

		return E_ITA3E_OK;
	}
	if (*l)
		ita3e_item_list_insert_aux(&((*l)->next),k,--pos);
	else {
		fprintf(stderr,"Index out of bound\n");
		exit(E_ITA3E_OUTOFBOUND);
	}
	return E_ITA3E_OK;
}

int ita3e_item_list_insert(ita3e_item_list_t **l,key_t k,unsigned int pos) {
	return ita3e_item_list_insert_aux(l,k,pos);
}

int ita3e_item_list_delete(ita3e_item_list_t **l, unsigned int pos) {
	ita3e_singlylinked_node_t *tmp;
	if(!pos) {
		if(!(*l)) {
			fprintf(stderr,"list is empty\n");
			exit(E_ITA3E_UNDERFLOW);
		}
		else {
			tmp = *l;
			*l  = tmp->next;
			free(tmp);
		}
		return E_ITA3E_OK;
	}
	if (*l)
		ita3e_item_list_delete(&((*l)->next),--pos);
	else {
		fprintf(stderr,"Index out of bound\n");
		exit(E_ITA3E_OUTOFBOUND);
	}
	return E_ITA3E_OK;
}

int ita3e_item_list_search(ita3e_item_list_t *l, key_t k, ita3e_item_t *x) {
	int rc = E_ITA3E_OK;

	if(!l)
		return E_ITA3E_KEYNOTFOUND;
	else if(l->data.tag == k) {
		*x = l->data;
		return E_ITA3E_OK;
	}
	else
		rc = ita3e_item_list_search(l->next,k,x);

	return rc;
}

int ita3e_item_list_traverse(ita3e_item_list_t *l, bool forward) {
	return ita3e_item_list_traverse_aux(l,0,forward);
}
