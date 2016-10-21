#include "ita3e.h"

// Implements an Array Stack
struct ArrayStack {
	int elements[MAX_ARRAY_SIZE];
	int top;
	int count;
} ita3e_item_array_stack_t;

// Implements an Linked Stack
struct LinkedStack {
	struct NodeType * Top;
	int count;
} ita3e_item_linked_stack_t;

// Stack Methods/Operations
void ita3e_item_array_stack_init	  (ita3e_item_array_stack_t*);
void ita3e_item_array_stack_print		(ita3e_item_array_stack_t*);
int  ita3e_item_array_stack_isFull 	(ita3e_item_array_stack_t*);
int  ita3e_item_array_stack_isEmpty	(ita3e_item_array_stack_t*);
int  ita3e_item_array_stack_push		(ita3e_item_array_stack_t*, ita3e_item_t);
int  ita3e_item_array_stack_pop			(ita3e_item_array_stack_t*, ita3e_item_t *);

void ita3e_item_linked_stack_init	  (ita3e_item_linked_stack_t*);
void ita3e_item_linked_stack_print 	(ita3e_item_linked_stack_t*);
int  ita3e_item_linked_stack_isFull (ita3e_item_linked_stack_t*);
int  ita3e_item_linked_stack_isEmpty(ita3e_item_linked_stack_t*);
int  ita3e_item_linked_stack_push		(ita3e_item_linked_stack_t*, ita3e_item_t);
int  ita3e_item_linked_stack_pop		(ita3e_item_linked_stack_t*, ita3e_item_t *);
