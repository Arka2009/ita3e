#include <stdint.h>

#ifndef G_ITA3E_0
#define G_ITA3E_0
#define MAX_ARRAY_SIZE 100

typedef enum {                                                                  
  true  = 1,                                                                    
  false = 0                                                                     
} bool;

// (Comparable) Tagged Satellite Type
typedef uint16_t key_t;

typedef struct ItemType {
	key_t tag;
	uint32_t payload;
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

// Compare functions
int  ita3e_item_compare(ita3e_item_t, ita3e_item_t);
void ita3e_item_print(ita3e_item_t);

// Array Operations
ita3e_item_t ita3e_item_init(uint8_t, uint16_t);
int 	ita3e_item_array_init(ita3e_item_t*, int);
void 	ita3e_item_array_print(ita3e_item_t*, int);
#endif /* G_ITA3E_0 */
