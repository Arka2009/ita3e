#include "ita3e.h"

#ifndef G_ITA3E_1
#define G_ITA3E_1

//#define LINKED_Q

// (Circular) Array Queue Implementation
typedef struct ArrayQueue {
	ita3e_item_t elements[MAX_ARRAY_SIZE];
	int head;
	int tail;
	int count;
} ita3e_item_array_queue_t ;

// (Doubly) Linked Queue Implementation
typedef struct LinkedQueue {
	ita3e_doublylinked_node_t* head;
	ita3e_doublylinked_node_t* tail;
	int count;
} ita3e_item_linked_queue_t ;

#ifdef LINKED_Q
	typedef ita3e_item_linked_queue_t ita3e_item_queue_t;
#else
	typedef ita3e_item_array_queue_t  ita3e_item_queue_t;
#endif

// Array Queue Methods/Operations
void ita3e_item_array_queue_init	(ita3e_item_array_queue_t*);
void ita3e_item_array_queue_print 	(ita3e_item_array_queue_t*);
int  ita3e_item_array_queue_isFull  (ita3e_item_array_queue_t*);
int	 ita3e_item_array_queue_isEmpty (ita3e_item_array_queue_t*);
int  ita3e_item_array_queue_enq		(ita3e_item_array_queue_t*, ita3e_item_t);
int  ita3e_item_array_queue_deq		(ita3e_item_array_queue_t*, ita3e_item_t *);

// Linked Queue Methods/Operations
void ita3e_item_linked_queue_init	 (ita3e_item_linked_queue_t*);
void ita3e_item_linked_queue_print   (ita3e_item_linked_queue_t*);
int  ita3e_item_linked_queue_isFull  (ita3e_item_linked_queue_t*);
int  ita3e_item_linked_queue_isEmpty (ita3e_item_linked_queue_t*);
int  ita3e_item_linked_queue_enq	 (ita3e_item_linked_queue_t*, ita3e_item_t);
int  ita3e_item_linked_queue_deq	 (ita3e_item_linked_queue_t*, ita3e_item_t *);

// Common (Unified) Implementation
void ita3e_item_queue_init 		(ita3e_item_queue_t*);
void ita3e_item_queue_print		(ita3e_item_queue_t*);
int  ita3e_item_queue_isFull	(ita3e_item_queue_t*);
int  ita3e_item_queue_isEmpty	(ita3e_item_queue_t*);
int  ita3e_item_queue_enq		(ita3e_item_queue_t*, ita3e_item_t x);
int  ita3e_item_queue_deq		(ita3e_item_queue_t*, ita3e_item_t* x);
#endif /* G_ITA3E_1 */
