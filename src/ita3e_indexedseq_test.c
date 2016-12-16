#include <stdio.h>
#include <stdlib.h>
#include "ita3e.h"
#include "ita3e_indexedseq.h"
#include "ita3e_errors.h"

int ita3e_indexedseq_test(int argc, char** argv) {

	if(argc != 2) {
		fprintf(stderr,"Usage: %s <seed>",argv[0]);
		return E_ITA3E_ILLARG;
	}
	ita3e_item_indexedseq_t isq;
	int size = 5;
	ita3e_item_t val;

	/* Create and Indexed Sequence and initialize it */
	int status, seed = atoi(argv[1]);
	status = ita3e_item_indexedseq_init(&isq, size);
	if(status != E_ITA3E_OK) {
		fprintf(stderr,"IndexedSeq creation failed %d ",status);
		return status;
	}
	for(int i = 0; i < size; i++) {
		val = ita3e_item_init(rand() % 0x788,rand() % 0x208);
		status = ita3e_item_indexedseq_set(&isq,val,i);
		if(status != E_ITA3E_OK) return status;
	}

	/* Display before Insertion */
	printf(" Indexed Sequence before Insertion \n");
	ita3e_item_indexedseq_print(&isq);
	printf("\n");
	
	/* Insert into random locations */
	srand(seed);
	int idx = 0, num_insertions = 2;
	for(int i = 0; i < num_insertions; i++)
	{
		val = ita3e_item_init(rand() % 0x788,rand() % 0x208);
		idx = rand() % size;
		printf("Value[%d] = ",idx);
		ita3e_item_print(val);
		printf("\n");
		ita3e_item_indexedseq_insert(&isq,val,idx);

		/* Display after insertion */
		printf(" Indexed Sequence after(%d) insertion  \n",i);
		ita3e_item_indexedseq_print(&isq);
		printf("\n");
	}

	/* Delete from Random locations */
	srand(rand());
	int num_deletions = 6;
	for(int i = 0; i < num_deletions; i++) {
		idx = rand() % size;
		ita3e_item_indexedseq_delete(&isq,idx);
		
		/* Display after deletion */
		printf(" Indexed Sequence after(%d) deletion from(%d)\n",i,idx);
		ita3e_item_indexedseq_print(&isq);
		printf("\n");
	}
	return E_ITA3E_OK;
}
