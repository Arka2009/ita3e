#include "ita3e.h"

#ifndef G_ITA3E_4
#define G_ITA3E_4

// Type of each tree node for binary trees
typedef struct TreeNode {
	ita3e_item_t data;
	struct TreeNode* left;
	struct TreeNode* right;
} ita3e_item_tree_node_t ;

// Rooted Binary Tree with n nodes
typedef struct BinaryTree {
	ita3e_item_tree_node_t* root;
	int size;
} ita3e_item_btree_t;


#endif /* G_ITA3E_4 */
