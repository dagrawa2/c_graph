#include <stdio.h>
#include "list_dll.h"
#include "graph_dll.h"

int main(void) {
	graph_t *G = graph_construct();
	printf("Graph constructed\n");
	graph_add_vertex(G, "alice");
	graph_add_vertex(G, "bob");
	graph_add_vertex(G, "chad");
	graph_add_vertex(G, "dana");
	printf("G.order = %d\n", graph_order(G));
	printf("G.V = ");
	graph_vertex_list_print(G);
	graph_add_edge(G, "alice", "bob");
	graph_add_edge(G, "bob", "dana");
	graph_add_edge(G, "chad", "dana");
	printf("dana.deg_in = %d\n", graph_vertex_deg_in(G, "dana"));
	printf("dana.deg_out = %d\n", graph_vertex_deg_out(G, "dana"));
	printf("edges = ");
	graph_edge_list_print(G);
	printf("deleting (bob, dana)\n");
	graph_del_edge(G, "bob", "dana");
	printf("(bob, dana) deleted\n");
	printf("dana.parents = ");
	graph_vertex_parents_print(G, "dana");
	graph_destroy(G);
	printf("Graph destroyed\n");
	return 0;
}