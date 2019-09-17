#include "ita3e.h"

#ifndef G_ITA3E_4
#define G_ITA3E_4

/*
 * The (rooted) binary (search) tree data structure is used as the
 * basis of many ADTs
 */

typedef struct __TreeNode {
	ita3e_item_t data;
	struct __TreeNode *left;
	struct __TreeNode *right;
} ita3e_item_btree_t;

typedef enum {
	preorder,
	inorder,
	postorder,
} dfs_traverse_t ;

/* General (Binary) Tree methods */
int 			ita3e_item_btree_init(ita3e_item_btree_t **bt);
unsigned int 	ita3e_item_btree_height(ita3e_item_btree_t *bt); /* Compute the height */
unsigned int 	ita3e_item_btree_nodes(ita3e_item_btree_t *bt);  /* Count the number of nodes */
int 			ita3e_item_btree_cons(ita3e_item_btree_t **bt, unsigned int); /* Construct a (non-search) btree with a given height */
void 			ita3e_item_btree_print_dot(ita3e_item_btree_t *bt,FILE*);	  /* Visualize the tree using xdot */
int				ita3e_item_btree_traverse_dfs(ita3e_item_btree_t*, dfs_traverse_t);

/* Methods Exclusive to a search tree */
int				ita3e_item_btree_search(ita3e_item_btree_t *bt, key2_t k, ita3e_item_t *x);
int				ita3e_item_btree_insert(ita3e_item_btree_t **bt, key2_t);
//int			ita3e_item_btree_delete(ita3e_item_btree_t **bt, ita3e_item_t *x); /* Quite Tricky */

#endif /* G_ITA3E_4 */
