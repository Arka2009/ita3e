#include "ita3e.h"

#ifndef G_ITA3E_2
#define G_ITA3E_2

//#define LINKED_STACK

// Implements an Array Stack
typedef struct ArrayStack {
	ita3e_item_t elements[MAX_ARRAY_SIZE];
	int top;
	int count;
} ita3e_item_array_stack_t;

// Implements an Linked Stack
typedef struct LinkedStack {
	ita3e_singlylinked_node_t* top;
	int count;
} ita3e_item_linked_stack_t;

#ifdef LINKED_STACK
	typedef ita3e_item_linked_stack_t ita3e_item_stack_t;
#else
	typedef ita3e_item_array_stack_t  ita3e_item_stack_t;
#endif

// (Array) Stack Methods/Operations
void ita3e_item_array_stack_init	  	(ita3e_item_array_stack_t*);
void ita3e_item_array_stack_print		(ita3e_item_array_stack_t*);
int  ita3e_item_array_stack_isFull 		(ita3e_item_array_stack_t*);
int  ita3e_item_array_stack_isEmpty		(ita3e_item_array_stack_t*);
int  ita3e_item_array_stack_push		(ita3e_item_array_stack_t*, ita3e_item_t);
int  ita3e_item_array_stack_pop			(ita3e_item_array_stack_t*, ita3e_item_t*);

// (Linked List) Stack Methods/Operations
void ita3e_item_linked_stack_init	  	(ita3e_item_linked_stack_t*);
void ita3e_item_linked_stack_print 		(ita3e_item_linked_stack_t*);
int  ita3e_item_linked_stack_isFull 	(ita3e_item_linked_stack_t*);
int  ita3e_item_linked_stack_isEmpty	(ita3e_item_linked_stack_t*);
int  ita3e_item_linked_stack_push		(ita3e_item_linked_stack_t*, ita3e_item_t);
int  ita3e_item_linked_stack_pop		(ita3e_item_linked_stack_t*, ita3e_item_t*);

// Common (Unified) Implementation
void ita3e_item_stack_init				(ita3e_item_stack_t*);
void ita3e_item_stack_print				(ita3e_item_stack_t*);
int  ita3e_item_stack_isFull			(ita3e_item_stack_t*);
int  ita3e_item_stack_isEmpty			(ita3e_item_stack_t*);
int  ita3e_item_stack_push				(ita3e_item_stack_t*, ita3e_item_t);
int  ita3e_item_stack_pop				(ita3e_item_stack_t*, ita3e_item_t*);
#endif /* G_ITA3E_2 */
