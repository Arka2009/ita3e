#include <ita3e.h>

#ifndef G_TMP_0
#define G_TMP_0

typedef struct disjointset disjointset_t;
typedef struct disjointset_node disjointset_node_t;

/**
 * The First element of the list (i.e. the head)
 * is the representative member of the set
 */
struct disjointset {
	disjointset_node_t* head;
	disjointset_node_t* tail;
};

struct disjointset_node {
	ita3e_item_t data;
	disjointset_node_t* next;
	disjointset_t* setId;
};

#endif /* G_TMP_0 */
