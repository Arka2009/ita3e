#include <stdio.h>
#include <stdlib.h>
#include "ita3e.h"
#include "ita3e_errors.h"
#include "ita3e_btree.h"

int ita3e_btree_test() {
	int ht = 3, num_nodes = 10;
	key_t k = rand() % 1000;
	ita3e_item_btree_t *btree = NULL;
	ita3e_item_t x;
	int ret;
	FILE* fdot = fopen("btree.dot","w");

	/* Construct a tree */
	//printf("Creating a tree of height %d\n",ht);
	//int ret = ita3e_item_btree_cons(&btree,ht);
	
	/* Construct a tree by insertion */
	while(num_nodes-- > 0) {
		k = rand() % 85;
		printf("key to be inserted %d\n",k);
		ita3e_item_btree_insert(&btree,k);
	}

	if(!btree) {
		printf("Creation/Insertion into the btree failed\n");
		exit(EXIT_FAILURE);
	}
	/* Visualize the tree */
	ita3e_item_btree_print_dot(btree,fdot);
	fclose(fdot);

	/* Traversal and print */
	printf("Traversing the tree %d\n",ht);
	ita3e_item_btree_traverse_dfs(btree,inorder);	
	printf("\n");

	/* Search for a key */
	k = 81;
	ret = ita3e_item_btree_search(btree,k,&x);
	if(!ret) {
		printf("key=%d found\n",k);
		ita3e_item_print(x);
	}
	return 0;
}
