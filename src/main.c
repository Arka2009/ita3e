#include <stdio.h>
#include <stdlib.h>
#include "ita3e.h"
#include "ita3e_sort.h"
#include "ita3e_DataStructures.h"

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

int main() {
	struct ArrayQueue q;
	int enq_status, deq_status, x;

	QueueInit(&q);
	
	/*	Queue Insertions	*/
	enq_status = Enq(&q,rand()/112034);
	if(enq_status == OVERFLOW) {
		printf(" Queue Overflow ");
		exit(EXIT_FAILURE);
	}
	DisplayQueue(&q);
	
	enq_status = Enq(&q,rand()/112312);
	if(enq_status == OVERFLOW) {
		printf(" Queue Overflow ");
		exit(EXIT_FAILURE);
	}
	DisplayQueue(&q);
	
	enq_status = Enq(&q,rand()/886521);
	if(enq_status == OVERFLOW) {
		printf(" Queue Overflow ");
		exit(EXIT_FAILURE);
	}
	DisplayQueue(&q);
	
	enq_status = Enq(&q,rand()/998233);
	if(enq_status == OVERFLOW) {
		printf(" Queue Overflow ");
		exit(EXIT_FAILURE);
	}
	DisplayQueue(&q);

	/* Queue Deletions	*/
	deq_status = Deq(&q,&x);
	if(deq_status == UNDERFLOW) {
		printf(" Queue Underflow ");
		exit(EXIT_FAILURE);
	}
	DisplayQueue(&q);
	printf(" Deq Value %d \n",x);

	deq_status = Deq(&q,&x);
	if(deq_status == UNDERFLOW) {
		printf(" Queue Underflow ");
		exit(EXIT_FAILURE);
	}
	DisplayQueue(&q);
	printf(" Deq Value %d \n",x);
	
	deq_status = Deq(&q,&x);
	if(deq_status == UNDERFLOW) {
		printf(" Queue Underflow ");
		exit(EXIT_FAILURE);
	}
	DisplayQueue(&q);
	printf(" Deq Value %d \n",x);
	
	deq_status = Deq(&q,&x);
	if(deq_status == UNDERFLOW) {
		printf(" Queue Underflow ");
		exit(EXIT_FAILURE);
	}
	DisplayQueue(&q);
	printf(" Deq Value %d \n",x);

	return EXIT_SUCCESS;
}
