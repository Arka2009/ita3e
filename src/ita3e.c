#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ita3e.h"
#include "ita3e_errors.h"

int ita3e_item_compare(ita3e_item_t a, ita3e_item_t b) {
	if(a.tag < b.tag) return -1;
	else if(a.tag == b.tag) return 0;
	else return 1;
}

void ita3e_item_print(ita3e_item_t a) {
	printf("<tag:0x%x|payload:0x%x>",a.tag,a.payload);
}

// Array operations
ita3e_item_t ita3e_item_init(uint8_t tag, uint16_t payload) {
	ita3e_item_t x;
	x.tag 		= tag;
	x.payload = payload;
	return x;
}

int ita3e_item_array_init(ita3e_item_t* A, int length) {
	int i;
	time_t t;

	/* Initialize the Random Number Generator	*/
	srand((unsigned) time(&t));
	printf("Initializing array elements \n");
	for(i=0; i<length; i++)
		A[i] = ita3e_item_init(rand() % 256, rand() % 65536);
	
	return E_ITA3E_OK;
}

void ita3e_item_array_print(ita3e_item_t* A, int length) {
	int i;
	printf("{");
	for(i = 0; i < length; i++) {
		ita3e_item_print(A[i]);
		if(i != length -1 ) printf(",");
	}
	printf("}");
}

//void ita3e_item_array_resize(ita3e_item_t* A, int orig_length, int new_length) {
//
//	for(int i = 0; i < orig_length; i++) {
//		A[i] 
//	}
//} 
