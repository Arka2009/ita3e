#include "ita3e.h"
#include "ita3e_list.h"

#ifndef G_ITA3E_6
#define G_ITA3E_6

/*
 * The adjacency list is a compact data structure to represent
 * graphs with a space complexity of O(V+E). The graphs do not
 * have any edge weights. Basically its an array of several
 * linked lists.
 */

typedef struct __AdjList {
	ita3e_item_list_t *vertex_array;
	int num_vertices;
} ita3e_item_adjlist_t;


/* Construct a Graph from a given dot file */
int ita3e_item_adjlist_cons(ita3e_item_adjlist_t *g, char **dot_file);

/* Construct an completely unconnected graph E = 0 */
int ita3e_item_adjlist_cons0(ita3e_item_adjlist_t *g, int num_vertices);

/* Connect node-u and node-v */
int ita3e_item_adjlist_connect(ita3e_item_adjlist_t *g, key2_t u, key2_t v);

/* Print the dot file */
int ita3e_item_adjlist_print_dot(const ita3e_item_adjlist_t *g, FILE *stream);
#endif /* G_ITA3E_6 */
