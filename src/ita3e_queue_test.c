#include <stdio.h>
#include <stdlib.h>
#include "ita3e.h"
#include "ita3e_sort.h"
#include "ita3e_queue.h"
#include "ita3e_errors.h"

/*	Main Function */
/*int main(int argc, char* argv[]) {	
	if(argc != 2) {
		printf("Requires Exactly two arguments \n");
		return ILLEGAL_ARG_COUNT;
	}

	int arraylength = atoi(argv[1]);

	if(arraylength > MAX_ARRAY_SIZE) {
		printf("Cannot Handle such a huge array \n");
		return MAX_ARRAY_LIMIT_REACHED;
	}

	int A[MAX_ARRAY_SIZE];
	
	ArrayInit(A, arraylength);
	printf("Input Array \n");	
	DisplayArrayInt(A,arraylength);
	InsertionSort(A,arraylength);
	printf("Output Array \n");	
	DisplayArrayInt(A,arraylength);
	return 0;
}*/

int ita3e_array_queue_test() {
	ita3e_item_array_queue_t q;
	int enq_status, deq_status;
	ita3e_item_t x;

	ita3e_item_array_queue_init(&q);
	
	/*	Queue Insertions	*/
	ita3e_item_t tmp = ita3e_item_init(rand()/112034,rand()/882034);
	enq_status 			 = ita3e_item_array_queue_enq(&q,tmp);
	if(enq_status == E_ITA3E_OVERFLOW) {
		printf(" Queue Overflow ");
		exit(E_ITA3E_OVERFLOW);
	}
	
	tmp = ita3e_item_init(rand()/122264,rand()/912234);
	enq_status = ita3e_item_array_queue_enq(&q,tmp);
	if(enq_status == E_ITA3E_OVERFLOW) {
		printf(" Queue Overflow ");
		exit(E_ITA3E_OVERFLOW);
	}
	ita3e_item_array_queue_print(&q);
	
	tmp = ita3e_item_init(rand()/322264,rand()/3456474);
	enq_status = ita3e_item_array_queue_enq(&q,tmp);
	if(enq_status == E_ITA3E_OVERFLOW) {
		printf(" Queue Overflow ");
		exit(E_ITA3E_OVERFLOW);
	}
	ita3e_item_array_queue_print(&q);
	
	tmp = ita3e_item_init(rand()/37264,rand()/9956474);
	enq_status = ita3e_item_array_queue_enq(&q,tmp);
	if(enq_status == E_ITA3E_OVERFLOW) {
		printf(" Queue Overflow ");
		exit(E_ITA3E_OVERFLOW);
	}
	ita3e_item_array_queue_print(&q);

	/* Queue Deletions	*/
	deq_status = ita3e_item_array_queue_deq(&q,&x);
	if(deq_status == E_ITA3E_UNDERFLOW) {
		printf(" Queue Underflow ");
		exit(E_ITA3E_UNDERFLOW);
	}
	ita3e_item_array_queue_print(&q);
	printf(" Deq Value \n");
	ita3e_item_print(x);
	printf("\n");

	deq_status = ita3e_item_array_queue_deq(&q,&x);
	if(deq_status == E_ITA3E_UNDERFLOW) {
		printf(" Queue Underflow ");
		exit(E_ITA3E_UNDERFLOW);
	}
	ita3e_item_array_queue_print(&q);
	printf(" Deq Value \n");
	ita3e_item_print(x);
	printf("\n");
	
	deq_status = ita3e_item_array_queue_deq(&q,&x);
	if(deq_status == E_ITA3E_UNDERFLOW) {
		printf(" Queue Underflow ");
		exit(E_ITA3E_UNDERFLOW);
	}
	ita3e_item_array_queue_print(&q);
	printf(" Deq Value \n");
	ita3e_item_print(x);
	printf("\n");
	
	deq_status = ita3e_item_array_queue_deq(&q,&x);
	if(deq_status == E_ITA3E_UNDERFLOW) {
		printf(" Queue Underflow ");
		exit(E_ITA3E_UNDERFLOW);
	}
	ita3e_item_array_queue_print(&q);
	printf(" Deq Value \n");
	ita3e_item_print(x);
	printf("\n");

	return E_ITA3E_OK;
}
