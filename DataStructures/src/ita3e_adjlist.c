#include <stdio.h>
#include <stdlib.h>
#include "ita3e_errors.h"
#include "ita3e_adjlist.h"

#define MAX(a,b) 	(a > b ? a : b)

/* Construct an completely unconnected graph E = 0 */
int ita3e_item_adjlist_cons0(ita3e_item_adjlist_t *g, int num_vertices) {
	g->vertex_array = (ita3e_item_list_t*)calloc(num_vertices, sizeof(ita3e_item_list_t));
	g->num_vertices	= num_vertices;
	if(g->vertex_array)
		return E_ITA3E_OK;
	else {
		fprintf(stderr,"Memory allocation for adjacency list failed \n");
		exit(E_ITA3E_HEAPLOW);
	}

	/* Iterate over the number of nodes and fill the values */
	key2_t i = 0;
	for(i = 0; i < num_vertices; i++) {
		g->vertex_array[i].visited 	 = false;
		g->vertex_array[i].vertex_id = i;
		g->vertex_array[i].next		 = NULL;
		g->vertex_array[i].data		 = ita3e_item_init(i,rand()%276);
	}
}

/* Connect node-u and node-v */
int ita3e_item_adjlist_connect(ita3e_item_adjlist_t *g, key2_t u, key2_t v) {

	/* Do a bounds check of u and v */
	if((u >= g->num_vertices)  || (v >= g->num_vertices)) {
		fprintf(stderr,"No such vertex exists\n");
		exit(EXIT_FAILURE);
	}

	/* Insertion into the adjacency linked list */
	ita3e_item_list_insert(&(g->vertex_array[u].next),v,0);
	ita3e_item_list_insert(&(g->vertex_array[v].next),u,0);
	return E_ITA3E_OK;
}

/* Visualize the graph */
//static void print_dot_null(key2_t tag, int nullcount, FILE* stream) {
//    fprintf(stream,"    null%d [shape=point];\n",nullcount);
//    fprintf(stream,"    %d -> null%d;\n",tag,nullcount);
//}

static explore(ita3e_item_adjlist_t *g, key2_t u) {
	g->vertex_array[u].visited = true;

	/* traverse the list pointed to by v */
		
}

/* Print the dot file */
int ita3e_item_adjlist_print_dot(const ita3e_item_adjlist_t *g, FILE *stream) {
	//static int nullcount = 0;

	fprintf(stream,"graph UDGraph {\n");
}
