#include "ita3e.h"

#ifndef G_ITA3E_3
#define G_ITA3E_3

/**
 * Guarantees
 * 1. O(1) access (get and set)
 * 2. O(n) for Insertions/Deletions
 */
typedef struct LinearList {
	ita3e_item_t* elements;
	int size;
} ita3e_item_indexedseq_t;

int  ita3e_item_indexedseq_init   (ita3e_item_indexedseq_t*, int);
void ita3e_item_indexedseq_print  (ita3e_item_indexedseq_t*);
int  ita3e_item_indexedseq_get	  (ita3e_item_indexedseq_t*, ita3e_item_t*,int);
int  ita3e_item_indexedseq_set	  (ita3e_item_indexedseq_t*, ita3e_item_t ,int);
int  ita3e_item_indexedseq_insert (ita3e_item_indexedseq_t*, ita3e_item_t, int);
int  ita3e_item_indexedseq_delete (ita3e_item_indexedseq_t*, int);
int  ita3e_item_indexedseq_slice  (ita3e_item_indexedseq_t*, int, int);
#endif /* G_ITA3E_3 */
