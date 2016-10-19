/**
 * C is a procedural language, 
 * and lacks OO, generic 
 * programming support. 
 * However OO facilities
 * can be adopted in C using opaque objects
 */
#include "ita3e.h"

// Node Type for a singly linked list
struct NodeType0 {
	ita3e_item_t data;
	struct NodeType0* next;
} ita3e_singlylinked_node_t ;

// Node Type for a Doubly linked list
struct NodeType1 {
	ita3e_item_t data;
	struct NodeType1* next;
	struct NodeType1* prev;
} ita3e_doublylinked_node_t ;

// Implements an Array Circular Queue of Strings
typedef struct ArrayQueue {
	ita3e_item_t elements[MAX_ARRAY_SIZE];
	int head;
	int tail;
	int count;
} ita3e_item_array_queue_t ;

// Implements an (Singly) Linked Queue
struct LinkedQueue {
	struct NodeType* head;
	struct NodeType* tail;
	int count;
} ita3e_item_linked_queue_t ;

// Queue Methods/Operations
void ita3e_item_array_queue_init	  (ita3e_item_array_queue_t);
void ita3e_item_array_queue_print 	(ita3e_item_array_queue_t);
int  ita3e_item_array_queue_isFull  (ita3e_item_array_queue_t);
int	 ita3e_item_array_queue_isEmpty (ita3e_item_array_queue_t);
int  ita3e_item_array_queue_enq			(ita3e_item_array_queue_t, ita3e_item_t);
int  ita3e_item_array_queue_deq			(ita3e_item_array_queue_t, ita3e_item_t *);

int	 ita3e_item_linked_queue_init	   (ita3e_item_linked_queue_t);
void ita3e_item_linked_queue_print   (ita3e_item_linked_queue_t);
int  ita3e_item_linked_queue_isFull  (ita3e_item_linked_queue_t);
int  ita3e_item_linked_queue_isEmpty (ita3e_item_linked_queue_t);
int  ita3e_item_linked_queue_enq		 (ita3e_item_linked_queue_t, ita3e_item_t);
int  ita3e_item_linked_queue_deq		 (ita3e_item_linked_queue_t, ita3e_item_t *);
