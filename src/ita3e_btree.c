#include <stdio.h>
#include <stdlib.h>
#include "ita3e_errors.h"
#include "ita3e_btree.h"
#define MAX(a,b) 	(a > b ? a : b)

int ita3e_item_btree_init(ita3e_item_btree_t **btree) {
	*btree = NULL;
	return E_ITA3E_OK;
}

/* compute the height of btree */
unsigned int ita3e_item_btree_height(ita3e_item_btree_t *btree) {
	if(!btree)
		return 0;
	else
		return (1 + MAX(ita3e_item_btree_height(btree->left),\
						ita3e_item_btree_height(btree->right)));
}

/* compute the number of nodes */
unsigned int ita3e_item_btree_nodes(ita3e_item_btree_t *btree) {
	if(!btree) {
		return 0;
	}
	else {
		return (1 + ita3e_item_btree_nodes(btree->left) + ita3e_item_btree_nodes(btree->right));
	}
}

/* Construct a balanced binary tree with a given height */
int ita3e_item_btree_cons(ita3e_item_btree_t **btree, unsigned int ht) {
	int ls, rs;
	
	if(!ht)	{
		*btree = NULL;
		return E_ITA3E_OK;
	}
	else {
		struct __TreeNode *new_node = (struct __TreeNode*)malloc(sizeof(struct __TreeNode));
		if(!new_node) {
			fprintf(stderr,"Cannot allocate memory for a  new tree node\n");
			return E_ITA3E_HEAPLOW;
		}
		*btree = new_node;
		new_node->data = ita3e_item_init(rand() % 0xe88,rand() % 0xafd);
		ls = ita3e_item_btree_cons(&(new_node->left),ht-1);
		rs = ita3e_item_btree_cons(&(new_node->right),ht-1);
		if((rs == E_ITA3E_OK) && (ls == E_ITA3E_OK))
			return E_ITA3E_OK;
		else
			return E_ITA3E_HEAPLOW;
	}
}

/* DFS traverse the tree and print it */
int ita3e_item_btree_traverse_dfs(ita3e_item_btree_t *btree, dfs_traverse_t tr) {
	if(!btree)
		return E_ITA3E_OK;

	switch(tr) {
		case preorder :
		{
			ita3e_item_print(btree->data);
			printf(",");
			ita3e_item_btree_traverse_dfs(btree->left,tr);
			ita3e_item_btree_traverse_dfs(btree->right,tr);
			break;
		}

		case inorder :
		{
			ita3e_item_btree_traverse_dfs(btree->left,tr);
			ita3e_item_print(btree->data);
			printf(",");
			ita3e_item_btree_traverse_dfs(btree->right,tr);
			break;
		}
			
		case postorder : 
		{
			ita3e_item_btree_traverse_dfs(btree->left,tr);
			ita3e_item_btree_traverse_dfs(btree->right,tr);
			ita3e_item_print(btree->data);
			printf(",");
			break;
		}

		default :
			printf("Unsupported traversal type\n");	
	}
	return E_ITA3E_OK;
}

/* Visualize the graph */
static void ita3e_item_btree_print_dot_null(key_t tag, int nullcount, FILE* stream) {
	fprintf(stream,"	null%d [shape=point];\n",nullcount);
	fprintf(stream,"	%d -> null%d;\n",tag,nullcount);
}

static void ita3e_item_btree_print_dot_aux(struct __TreeNode *node, FILE* stream) {
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

void ita3e_item_btree_print_dot(ita3e_item_btree_t *tree, FILE* stream) {
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

int ita3e_item_btree_insert(ita3e_item_btree_t **bst, key_t k) {
	ita3e_item_btree_t *new_node;
	if(!(*bst)) {
		/* Base Case the bst is empty */
		new_node = \
		(struct __TreeNode*)malloc(sizeof(struct __TreeNode));
	
		if(!new_node) {
			fprintf(stderr,"Memory Allocation failure");
			exit(EXIT_FAILURE);
		}

		new_node->data = \
		ita3e_item_init(k,rand() % 0xafd);
		
		new_node->left  = NULL;
		new_node->right = NULL;

		*bst = new_node;
		return E_ITA3E_OK;
	}
	if(k < ((*bst)->data).tag) {
		/* Insert into the left subtree */
		ita3e_item_btree_insert(&((*bst)->left),k);
	}
	else if (k > ((*bst)->data).tag) { 
		/* Insert into the right subtree */
		ita3e_item_btree_insert(&((*bst)->right),k);
	}
	return E_ITA3E_OK;
}

int ita3e_item_btree_search(ita3e_item_btree_t *bst, key_t k, ita3e_item_t *x) {
	int ret;
	if(!bst)
		return E_ITA3E_KEYNOTFOUND;
	else if (bst->data.tag == k) {
		*x = bst->data;
		return E_ITA3E_OK;
	}
	else if (k < bst->data.tag)
		ret = ita3e_item_btree_search(bst->left,k,x);
	else
		ret = ita3e_item_btree_search(bst->right,k,x);

	return ret;
}
