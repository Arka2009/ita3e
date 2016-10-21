#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ita3e.h"
#include "ita3e_errors.h"

uint8_t ita3e_item_compare_isEqual(ita3e_item_t a, ita3e_item_t b) {
	return (a.tag == b.tag);	
}

uint8_t ita3e_item_compare_isGreater(ita3e_item_t a, ita3e_item_t b) {
	return (a.tag > b.tag);
}

uint8_t ita3e_item_compare_isLesser(ita3e_item_t a, ita3e_item_t b) {
	return (a.tag < b.tag);
}

void ita3e_item_print(ita3e_item_t a) {
	printf(" {tag:%d,payload:%x} ",a.tag,a.payload);
}


int ita3e_item_array_init(ita3e_item_t* A, int length) {
	int i;
	time_t t;

	/* Initialize the Random Number Generator	*/
	srand((unsigned) time(&t));
	printf("Initializing array elements \n");
	for(i=0; i<length; i++) {
		A[i] = ita3e_item_init(rand()/61123452, rand()/1224694);
	}
	
	return E_ITA3E_OK;
}

void ita3e_item_array_print(ita3e_item_t* A, int length) {
	int i;
	printf("\n");
	for(i=0; i<length; i++) {
		ita3e_item_print(A[i]);
	}
	printf("\n");
}

ita3e_item_t ita3e_item_init(uint8_t tag, uint16_t payload) {
	ita3e_item_t x;
	x.tag 		= tag;
	x.payload = payload;
	return x;
}
