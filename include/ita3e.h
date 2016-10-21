#include <stdint.h>

#define MAX_ARRAY_SIZE 100

#ifndef G_ITA3E_0
#define G_ITA3E_0
// (Comparable) Tagged Satellite Type
typedef struct ItemType {
	uint8_t tag;
	uint16_t payload;
} ita3e_item_t ;

// Node Type for Linked List Kind of Implementation
typedef struct NodeType0 {
	ita3e_item_t data;
	struct NodeType0* next;
} ita3e_singlylinked_node_t ;

typedef struct NodeType1 {
	ita3e_item_t data;
	struct NodeType1* next;
	struct NodeType1* prev;
} ita3e_doublylinked_node_t ;
#endif

// Compare functions
uint8_t ita3e_item_compare_isEqual(ita3e_item_t, ita3e_item_t);
uint8_t ita3e_item_compare_isGreater(ita3e_item_t, ita3e_item_t);
uint8_t ita3e_item_compare_isLesser(ita3e_item_t, ita3e_item_t);
void 		ita3e_item_print(ita3e_item_t);

// Initialize an array of ita3e_item_t elements
ita3e_item_t ita3e_item_init(uint8_t, uint16_t);
int 	ita3e_item_array_init(ita3e_item_t *, int);
void 	ita3e_item_array_print(ita3e_item_t *, int);
