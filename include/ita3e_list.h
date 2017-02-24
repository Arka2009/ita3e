#include "ita3e.h"

#ifndef G_ITA3E_5
#define G_ITA3E_5

/**
 * list implementation in C.
 * The API is similar to lists in
 * functional languages like OCaml, Scala or Haskell
 * View its as a recursive data structure
 * Operations supported
 *
 * 1. Insert at beginning O(1) (cons operation)
 * 2. Traversal O(n)
 * 3. Linear Search O(n)
 */
typedef ita3e_singlylinked_node_t* ita3e_item_list_t;

int ita3e_item_list_init(ita3e_item_list_t*);
int ita3e_item_list_cons(ita3e_item_t, ita3e_item_list_t*);
int ita3e_item_list_search(key_t, ita3e_item_list_t);
#endif /* G_ITA3E_5 */
