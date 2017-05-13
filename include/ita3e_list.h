#include "ita3e.h"

#ifndef G_ITA3E_5
#define G_ITA3E_5

/*
 * (Linked) List Data Structures used in many ADTs
 */
typedef ita3e_singlylinked_node_t* ita3e_item_list_t;

int ita3e_item_list_init(ita3e_item_list_t*);
int ita3e_item_list_cons(ita3e_item_list_t*, ita3e_item_t); /* prepend */
int ita3e_item_list_traverse(ita3e_item_list_t,bool); /* forward/reverse traversal */
int ita3e_item_list_clean_all(ita3e_item_list_t*);
int ita3e_item_list_clean_first(ita3e_item_list_t*);
#endif /* G_ITA3E_5 */
