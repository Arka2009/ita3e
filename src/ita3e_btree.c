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
//		new_node->left  = btree_cons(ht-1);
//		new_node->right = btree_cons(ht-1);
//	}
//}

/* Construct a balanced binary tree with a given height */
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
		new_node->data = ita3e_item_init(rand() % 0xe88,rand() % 0xafd);
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

/* DFS traverse the tree and print it */
int ita3e_item_btree_traverse_dfs(ita3e_item_btree_t btree, dfs_traverse_t tr) {
	if(!btree)
		return E_ITA3E_OK;

	switch(tr) {
		case preorder :
			ita3e_item_print(btree->data);
			printf(",");
			ita3e_item_btree_traverse_dfs(btree->left,tr);
			ita3e_item_btree_traverse_dfs(btree->right,tr);
			break;

		case inorder :
			ita3e_item_btree_traverse_dfs(btree->left,tr);
			ita3e_item_print(btree->data);
			printf(",");
			ita3e_item_btree_traverse_dfs(btree->right,tr);
			break;
			
		case postorder :
			ita3e_item_btree_traverse_dfs(btree->left,tr);
			ita3e_item_btree_traverse_dfs(btree->right,tr);
			ita3e_item_print(btree->data);
			printf(",");
			break;

		default :
			printf("Unsupported traversal type\n");	
	}
}

/* Visualize the graph */
static void ita3e_item_btree_print_dot_null(key_t tag, int nullcount, FILE* stream) {
	fprintf(stream,"	null%d [shape=point];\n",nullcount);
	fprintf(stream,"	%d -> null%d;\n",tag,nullcount);
}

static void ita3e_item_btree_print_dot_aux(ita3e_item_btree_node_t* node, FILE* stream) {
	static int nullcount = 0;

	if(node->left) {
		fprintf(stream,"	%d -> %d;\n",(node->data).tag,(node->left->data).tag);
		ita3e_item_btree_print_dot_aux(node->left,stream);
	}
	else
		ita3e_item_btree_print_dot_null((node->data).tag,nullcount++,stream);
	
	if(node->right) {
		fprintf(stream,"	%d -> %d;\n",(node->data).tag,(node->right->data).tag);
		ita3e_item_btree_print_dot_aux(node->right,stream);
	}
	else
		ita3e_item_btree_print_dot_null((node->data).tag,nullcount++,stream);
}

void ita3e_item_btree_print_dot(ita3e_item_btree_node_t* tree, FILE* stream) {
	fprintf(stream,"digraph BTree {\n");
	fprintf(stream,"	node [fontname=\"Arial\"];\n");
	
	if(!tree)
		fprintf(stream,"\n");
	else if (!tree->left && !tree->right)
		fprintf(stream,"	%d;\n",(tree->data).tag);
	else 
		ita3e_item_btree_print_dot_aux(tree,stream);
	fprintf(stream,"}\n");
}
