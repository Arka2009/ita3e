#include <stdio.h>
#include <stdlib.h>
#include "ita3e.h"
#include "ita3e_queue.h"
#include "ita3e_errors.h"

int ita3e_queue_test() {
	ita3e_item_queue_t q;
	int enq_status, deq_status;
	ita3e_item_t x;
	ita3e_item_queue_init(&q);

	/*	Queue Insertions */
	int num_insertions = 8;
	int i = 1;
	while(i <= num_insertions) {
		ita3e_item_t tmp = ita3e_item_init(rand()/1,rand()/1);
		enq_status 		 = ita3e_item_queue_enq(&q,tmp);
		if(enq_status == E_ITA3E_OVERFLOW) {
			printf(" Queue Overflow ");
			exit(E_ITA3E_OVERFLOW);
		}
		printf(" queue.status-after-enq(%d) : ",i);
		ita3e_item_queue_print(&q);
		printf("\n");
		i++;
	}
	
	/* Queue Deletions	*/
	int num_deletions = 3;
	i = 1;
	while(i <= num_deletions) {
		deq_status = ita3e_item_queue_deq(&q,&x);
		if(deq_status == E_ITA3E_UNDERFLOW) {
			printf(" Queue Underflow ");
			exit(E_ITA3E_UNDERFLOW);
		}
		printf(" queue.status-after-deq(%d) : ",i);
		ita3e_item_queue_print(&q);
		printf("\n");
		printf(" item dequed : ");
		ita3e_item_print(x);
		printf("\n");
		i++;
	}
	return E_ITA3E_OK;
}
