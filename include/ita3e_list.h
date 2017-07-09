#include "ita3e.h"

#ifndef G_ITA3E_5
#define G_ITA3E_5

/*
 * (Linked) List Data Structures used in many ADTs
 * Supported APIs
 * Insert/Delete 
 * Search
 */
typedef ita3e_singlylinked_node_t ita3e_item_list_t;

int ita3e_item_list_init(ita3e_item_list_t**);
int ita3e_item_list_cons(ita3e_item_list_t**, unsigned int len); /* construct a list (with random data) of a given length */
int ita3e_item_list_traverse(ita3e_item_list_t*,bool); /* forward/reverse traversal */
int ita3e_item_list_insert(ita3e_item_list_t**,key_t k,unsigned int pos);
int ita3e_item_list_delete(ita3e_item_list_t**,unsigned int pos);
int ita3e_item_list_search(ita3e_item_list_t*,key_t k, ita3e_item_t *);
int ita3e_item_list_clean_all(ita3e_item_list_t**);
int ita3e_item_list_clean_first(ita3e_item_list_t**);
#endif /* G_ITA3E_5 */
