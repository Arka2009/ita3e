#include <stdint.h>

#define MAX_ARRAY_SIZE 100

// (Comparable) Tagged Satellite Type
struct ItemType {
	uint8_t tag;
	uint16_t payload;
} ita3e_item_t ;

// Compare functions
uint8_t ita3e_item_compare_isEqual(ita3e_item_t, ita3e_item_t);
uint8_t ita3e_item_compare_isGreater(ita3e_item_t, ita3e_item_t);
uint8_t ita3e_item_compare_isLesser(ita3e_item_t, ita3e_item_t);
void ita3e_item_print(ita3e_item_t);

// Initialize an array of ita3e_item_t elements
int ita3e_item_array_init(ita3e_item_t *, int);
void ita3e_item_array_print(ita3e_item_t *, int);
