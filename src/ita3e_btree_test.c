#include <stdio.h>
#include <stdlib.h>
#include "ita3e.h"
#include "ita3e_errors.h"
#include "ita3e_btree.h"

int ita3e_btree_test() {
	int ht = 3;
	ita3e_item_btree_t btree;
	printf("Creating a tree of height %d\n",ht);

	/* Compute height and volume */
	
	/* Dot Visualization */
	FILE* fdot = fopen("btree.dot","w");
	int ret = ita3e_item_btree_cons(&btree,ht);
	ita3e_item_btree_print_dot(btree,fdot);
	fclose(fdot);

	/* Traversal and print */
	ita3e_item_btree_traverse_dfs(btree,postorder);	
	printf("\n");
	return ret;
}
