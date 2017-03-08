#include "ita3e.h"

#ifndef G_ITA3E_4
#define G_ITA3E_4

/*
 * The (rooted) btree data structure is used in many ADTs
 */
// Type of each tree node for binary trees
typedef struct TreeNode {
	ita3e_item_t data;
	struct TreeNode* left;
	struct TreeNode* right;
} ita3e_item_tree_node_t ;

//typedef struct BinaryTree {
//	ita3e_item_tree_node_t* root;
//	int size;
//} ita3e_item_btree_t;

typedef ita3e_item_tree_node_t* ita3e_item_btree_t;

int ita3e_item_btree_init(ita3e_item_btree_t*);
int ita3e_item_btree_height(ita3e_item_btree_t);
int ita3e_item_btree_nodes(ita3e_item_btree_t);
int ita3e_item_btree_cons(ita3e_item_btree);


#endif /* G_ITA3E_4 */
