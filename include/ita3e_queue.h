#include "ita3e.h"

#ifndef G_ITA3E_1
#define G_ITA3E_1

// Implements an Array Circular Queue of Strings
typedef struct ArrayQueue {
	ita3e_item_t elements[MAX_ARRAY_SIZE];
	int head;
	int tail;
	int count;
} ita3e_item_array_queue_t ;

// Implements an (Doubly) Linked Queue
typedef struct LinkedQueue {
	ita3e_doublylinked_node_t* head;
	ita3e_doublylinked_node_t* tail;
	int count;
} ita3e_item_linked_queue_t ;

// Array Queue Methods/Operations
void ita3e_item_array_queue_init	  (ita3e_item_array_queue_t*);
void ita3e_item_array_queue_print 	(ita3e_item_array_queue_t*);
int  ita3e_item_array_queue_isFull  (ita3e_item_array_queue_t*);
int	 ita3e_item_array_queue_isEmpty (ita3e_item_array_queue_t*);
int  ita3e_item_array_queue_enq			(ita3e_item_array_queue_t*, ita3e_item_t);
int  ita3e_item_array_queue_deq			(ita3e_item_array_queue_t*, ita3e_item_t *);

// Linked Queue Methods/Operations
void ita3e_item_linked_queue_init	   (ita3e_item_linked_queue_t*);
void ita3e_item_linked_queue_print   (ita3e_item_linked_queue_t*);
int  ita3e_item_linked_queue_isFull  (ita3e_item_linked_queue_t*);
int  ita3e_item_linked_queue_isEmpty (ita3e_item_linked_queue_t*);
int  ita3e_item_linked_queue_enq		 (ita3e_item_linked_queue_t*, ita3e_item_t);
int  ita3e_item_linked_queue_deq		 (ita3e_item_linked_queue_t*, ita3e_item_t *);

// Some Client Code for testing
int ita3e_array_queue_test();
int ita3e_linked_queue_test();
#endif /* G_ITA3E_1 */
