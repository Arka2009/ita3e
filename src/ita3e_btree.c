#include <stdio.h>
#include <stdlib.h>
#include "ita3e_errors.h"
#include "ita3e_btree.h"

int ita3e_item_btree_init(ita3e_item_btree_t* btree) {
	*btree = NULL;
	return E_ITA3E_OK;
}

static unsigned int max(unsigned int a, unsigned int b) {
	return ((a > b) ? a : b);
}

// returns the height of the btree
unsigned int ita3e_item_btree_height(ita3e_item_btree_t btree) {
	if(!btree) {
		return 0;
	}
	else {
		return (1 + max(ita3e_item_btree_height(btree->left),\
						ita3e_item_btree_height(btree->right)));
	}
}

// returns the number of nodes
unsigned int ita3e_item_btree_nodes(ita3e_item_btree_t btree) {
	if(!btree) {
		return 0;
	}
	else {
		return (1 + ita3e_item_btree_nodes(btree->left) + ita3e_item_btree_nodes(btree->right));
	}
}

// constructs a balanced binary tree of height ht
//static ita3e_item_btree_t btree_cons(unsigned int ht) {
//	if(!ht) {
//		return NULL;
//	}
//	else {
//		ita3e_item_btree_node_t* new_node = (ita3e_item_btree_node_t*)malloc(sizeof(ita3e_item_btree_node_t));
//		if(!new_node) {
//			fprintf(stderr,"Cannot allocate memory for a  new tree node\n");
//			return NULL;
//		}
//		new_node->data = ita3e_item_init(rand() % 0xe88,rand() % 0xafd);
//		new_node->left  = btree_cons(ht-1);
//		new_node->right = btree_cons(ht-1);
//	}
//}

// Construct a balanced binary tree with a given height
int ita3e_item_btree_cons(ita3e_item_btree_t* btree, unsigned int ht) {
	int ls, rs;
	
	if(!ht)	{
		*btree = NULL;
		return E_ITA3E_OK;
	}
	else {
		ita3e_item_btree_node_t* new_node = (ita3e_item_btree_node_t*)malloc(sizeof(ita3e_item_btree_node_t));
		if(!new_node) {
			fprintf(stderr,"Cannot allocate memory for a  new tree node\n");
			return E_ITA3E_HEAPLOW;
		}
		*btree = new_node;
		ls = ita3e_item_btree_cons(&(new_node->left),ht-1);
		rs = ita3e_item_btree_cons(&(new_node->right),ht-1);
		if((rs == E_ITA3E_OK) && (ls == E_ITA3E_OK)) {
			return E_ITA3E_OK;
		}
		else {
			return E_ITA3E_HEAPLOW;
		}
	}
}
