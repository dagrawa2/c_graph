#include <stdio.h>
#include <windows.h>
#include <string.h>
#include "list_dll.h"
#include "graph_dll.h"

struct vertex {
	char *name;
	list_t *children;
	list_t *parents;
};

struct graph {
	list_t *V;
	int order;
};


vertex_t *void_to_vertex(void *ptr) {
	return (vertex_t *)ptr;
}


vertex_t *vertex_cursor_val(cursor_t *c_ptr) {
	return void_to_vertex(cursor_val(c_ptr));
}

char *vertex_cursor_name(cursor_t *c_ptr) {
	return void_to_vertex(cursor_val(c_ptr))->name;
}

list_t *vertex_cursor_children(cursor_t *c_ptr) {
	return void_to_vertex(cursor_val(c_ptr))->children;
}

list_t *vertex_cursor_parents(cursor_t *c_ptr) {
	return void_to_vertex(cursor_val(c_ptr))->parents;
}


cursor_t vertex_cursor(list_t *L, char *v_name) {
	cursor_t c = cursor(L);
	for (c; c!=NULL; cursor_advance(&c, 1)) {
		if (strcmp(vertex_cursor_name(&c), v_name) == 0) {
			break;
		}
	}
	return c;
}


graph_t *graph_construct(void) {
	graph_t *G = malloc(sizeof(graph_t));
	G->V = list_construct();
	G->order = 0;
	return G;
}

list_t *graph_vertex_list(graph_t *G) {
	return G->V;
}

int graph_order(graph_t *G) {
	return G->order;
}

vertex_t *graph_vertex(graph_t *G, char *v_name) {
	cursor_t c = vertex_cursor(G->V, v_name);
	if (c == NULL) {
		printf("Error -- in graph_vertex: There is no vertex named %s!\n", v_name);
		exit(1);
	}
	return vertex_cursor_val(&c);
}

list_t *graph_vertex_children(graph_t *G, char *v_name) {
	cursor_t c = vertex_cursor(G->V, v_name);
	if (c == NULL) {
		printf("Error -- in graph_vertex: There is no vertex named %s!\n", v_name);
		exit(1);
	}
	return vertex_cursor_children(&c);
}

list_t *graph_vertex_parents(graph_t *G, char *v_name) {
	cursor_t c = vertex_cursor(G->V, v_name);
	if (c == NULL) {
		printf("Error -- in graph_vertex: There is no vertex named %s!\n", v_name);
		exit(1);
	}
	return vertex_cursor_parents(&c);
}
	
int graph_vertex_deg_in(graph_t *G, char *v_name) {
	cursor_t c = vertex_cursor(G->V, v_name);
	if (c == NULL) {
		printf("Error -- in graph_vertex_deg_in: There is no vertex named %s!\n", v_name);
		exit(1);
	}
	return list_len(vertex_cursor_parents(&c));
}

int graph_vertex_deg_out(graph_t *G, char *v_name) {
	cursor_t c = vertex_cursor(G->V, v_name);
	if (c == NULL) {
		printf("Error -- in graph_vertex_deg_out: There is no vertex named %s!\n", v_name);
		exit(1);
	}
	return list_len(vertex_cursor_children(&c));
}


void graph_add_vertex(graph_t *G, char *v_name) {
	cursor_t c = vertex_cursor(G->V, v_name);
	if (c != NULL) {
		printf("Error -- in graph_add_vertex: The vertex %s already exists!\n", v_name);
		exit(1);
	}
	vertex_t *v_ptr = malloc(sizeof(vertex_t));
	v_ptr->name = v_name;
	v_ptr->children = list_construct();
	v_ptr->parents = list_construct();
	list_append(G->V, v_ptr);
	G->order++;
}

void graph_add_edge(graph_t *G, char *v_name, char *w_name) {
	cursor_t c_v = vertex_cursor(G->V, v_name);
	if (c_v == NULL) {
		printf("Error -- in graph_add_edge: There is no vertex named %s!\n", v_name);
		exit(1);
	}
	cursor_t c_w = vertex_cursor(vertex_cursor_children(&c_v), w_name);
	if (c_w != NULL) {
		printf("Error - in graph_add_edge: The edge (%s, %s) already exists!\n", v_name, w_name);
		exit(1);
	}
	c_w = vertex_cursor(G->V, w_name);
	if (c_w == NULL) {
		printf("Error -- in graph_add_edge: There is no vertex named %s!\n", w_name);
		exit(1);
	}
	list_append(vertex_cursor_children(&c_v), vertex_cursor_val(&c_w));
	list_append(vertex_cursor_parents(&c_w), vertex_cursor_val(&c_v));
}

void graph_del_vertex(graph_t *G, char *v_name) {
	cursor_t c_v = vertex_cursor(G->V, v_name);
	if (c_v == NULL) {
		printf("Error -- in graph_vertex_del: There is no vertex named %s!\n", v_name);
		exit(1);
	}
	void *v_ptr = cursor_val(&c_v);
	cursor_t c = cursor(vertex_cursor_parents(&c_v));
	for (c; c!=NULL; cursor_advance(&c, 1)) {
		list_del_by_val(vertex_cursor_children(&c), v_ptr);
	}
	c = cursor(vertex_cursor_children(&c_v));
	for (c; c!=NULL; cursor_advance(&c, 1)) {
		list_del_by_val(vertex_cursor_parents(&c), v_ptr);
	}
	list_destroy(vertex_cursor_children(&c_v));
	list_destroy(vertex_cursor_parents(&c_v));
	list_del_by_val(G->V, v_ptr);
	free(void_to_vertex(v_ptr));
	G->order--;
}

void graph_del_edge(graph_t *G, char *v_name, char *w_name) {
	cursor_t c_v = vertex_cursor(G->V, v_name);
	if (c_v == NULL) {
		printf("Error -- in graph_del_edge: There is no vertex named %s!\n", v_name);
		exit(1);
	}
	cursor_t c_w = vertex_cursor(vertex_cursor_children(&c_v), w_name);
	if (c_w == NULL) {
		printf("Error -- in graph_del_edge: There is no edge named (%s, %s)!\n", v_name, w_name);
		exit(1);
	}
	void *w_ptr = cursor_val(&c_w);
	list_del_by_val(vertex_cursor_children(&c_v), w_ptr);
	list_del_by_val(void_to_vertex(w_ptr)->parents, cursor_val(&c_v));
}	
		
void graph_destroy(graph_t *G) {
	cursor_t c = cursor(G->V);
	for (c; c!=NULL; cursor_advance(&c, 1)) {
		list_destroy(vertex_cursor_children(&c));
		list_destroy(vertex_cursor_parents(&c));
		free(vertex_cursor_val(&c));
	}
	list_destroy(G->V);
	free(G);
}


static void vertex_list_print(list_t *L) {
	cursor_t c = cursor(L);
	printf("[");
	for (c; c!=NULL; cursor_advance(&c, 1)) {
		printf("%s ", vertex_cursor_name(&c));
	}
	printf("]\n");
}

void graph_vertex_list_print(graph_t *G) {
	vertex_list_print(G->V);
}

void graph_vertex_children_print(graph_t *G, char *v_name) {
	vertex_list_print(graph_vertex_children(G, v_name));
}

void graph_vertex_parents_print(graph_t *G, char *v_name) {
	vertex_list_print(graph_vertex_parents(G, v_name));
}

void graph_edge_list_print(graph_t *G) {
	printf("[");
	cursor_t c_1 = cursor(G->V);
	char *c_1_name;
	cursor_t c_2;
	for (c_1; c_1!=NULL; cursor_advance(&c_1, 1)) {
		c_1_name = vertex_cursor_name(&c_1);
		c_2 = cursor(vertex_cursor_children(&c_1));
		for (c_2; c_2!=NULL; cursor_advance(&c_2, 1)) {
			printf("(%s, %s) ", c_1_name, vertex_cursor_name(&c_2));
		}
	}
	printf("]\n");
}


int main(void) {
	printf("Hello from graph.c!\n");
	return 0;
}