#include <disjointset_linkedlist.h>

int init_set(disjointset_t* s) {
	s->head = NULL;
	s->tail = NULL;
	return 0;
}

disjoint_t* make_set(ita3e_item_t data) {
	disjoint_t* set = (disjoint_t*)malloc(sizeof(disjoint_t));
	if(set == NULL) {
		fprintf(stderr,"malloc for set failed");
		return NULL;
	}
	disjointset_node_t* node = (disjointset_node_t*)malloc(sizeof(disjointset_node_t));
	if(node == NULL) {
		fprintf(stderr,"malloc for the node failed");
		return NULL;
	}
	set->head = node;
	set->tail = node;
	node->setId = set;
	node->next = NULL;
}
