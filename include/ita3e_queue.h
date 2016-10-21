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

// Implements an (Singly) Linked Queue
typedef struct LinkedQueue {
	ita3e_singlylinked_node_t* head;
	ita3e_singlylinked_node_t* tail;
	int count;
} ita3e_item_linked_queue_t ;
#endif

// Queue Methods/Operations
void ita3e_item_array_queue_init	  (ita3e_item_array_queue_t*);
void ita3e_item_array_queue_print 	(ita3e_item_array_queue_t*);
int  ita3e_item_array_queue_isFull  (ita3e_item_array_queue_t*);
int	 ita3e_item_array_queue_isEmpty (ita3e_item_array_queue_t*);
int  ita3e_item_array_queue_enq			(ita3e_item_array_queue_t*, ita3e_item_t);
int  ita3e_item_array_queue_deq			(ita3e_item_array_queue_t*, ita3e_item_t *);

int	 ita3e_item_linked_queue_init	   (ita3e_item_linked_queue_t*);
void ita3e_item_linked_queue_print   (ita3e_item_linked_queue_t*);
int  ita3e_item_linked_queue_isFull  (ita3e_item_linked_queue_t*);
int  ita3e_item_linked_queue_isEmpty (ita3e_item_linked_queue_t*);
int  ita3e_item_linked_queue_enq		 (ita3e_item_linked_queue_t*, ita3e_item_t);
int  ita3e_item_linked_queue_deq		 (ita3e_item_linked_queue_t*, ita3e_item_t *);
