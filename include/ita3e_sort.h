#include <stdint.h>
#include "ita3e.h"

// Auxiliary Routines used by Sort routines
void ita3e_item_exch(ita3e_item_t*,int,int);
int ita3e_item_array_sorted(ita3e_item_t*, int, int);
int ita3e_item_merge_sort1(ita3e_item_t*, ita3e_item_t*, int, int);
int ita3e_item_merge_subarray(ita3e_item_t*, ita3e_item_t*, int, int, int);
int ita3e_item_array_min(ita3e_item_t*, int, int, ita3e_item_t**); // Find the minimum

// Sort routines 
int ita3e_item_insertion_sort(ita3e_item_t*,int);
int ita3e_item_selection_sort(ita3e_item_t*,int);
int ita3e_item_merge_sort	 (ita3e_item_t*,int);
int ita3e_item_quick_sort	 (ita3e_item_t*,int);
