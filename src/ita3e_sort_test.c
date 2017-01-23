#include <stdio.h>
#include <stdlib.h>
#include "ita3e_sort.h"
#include "ita3e_errors.h"

int ita3e_sort_test() {
	int N = 20;
	ita3e_item_t* A = (ita3e_item_t*)calloc(N,sizeof(ita3e_item_t));
	if(A == NULL) {
		fprintf(stderr,"Dynamic memory allocation for array creation unsuccessful");
		return E_ITA3E_HEAPLOW;
	}
	ita3e_item_array_init(A,N);
	printf(" Original Array \n");
	ita3e_item_array_print(A,N);
	ita3e_item_merge_sort(A,N); 	
	printf("\n Sorted Array \n");
	ita3e_item_array_print(A,N);
	free(A);
	return E_ITA3E_OK;
}
