#ifndef GRAPH_H
#define GRAPH_H
struct vertex;
typedef struct vertex vertex_t;
struct graph;
typedef struct graph graph_t;
vertex_t *void_to_vertex(void *ptr);
vertex_t *vertex_cursor_val(cursor_t *c_ptr);
char *vertex_cursor_name(cursor_t *c_ptr);
list_t *vertex_cursor_children(cursor_t *c_ptr);
list_t *vertex_cursor_parents(cursor_t *c_ptr);
cursor_t vertex_cursor(list_t *L, char *v_name);
graph_t *graph_construct(void);
list_t *graph_vertex_list(graph_t *G);
int graph_order(graph_t *G);
vertex_t *graph_vertex(graph_t *G, char *v_name);
list_t *graph_vertex_children(graph_t *G, char *v_name);
list_t *graph_vertex_parents(graph_t *G, char *v_name);
int graph_vertex_deg_in(graph_t *G, char *v_name);
int graph_vertex_deg_out(graph_t *G, char *v_name);
void graph_add_vertex(graph_t *G, char *v_name);
void graph_add_edge(graph_t *G, char *v_name, char *w_name);
void graph_del_vertex(graph_t *G, char *v_name);
void graph_del_edge(graph_t *G, char *v_name, char *w_name);
void graph_destroy(graph_t *G);
void vertex_list_print(list_t *L);
void graph_vertex_list_print(graph_t *G);
void graph_vertex_children_print(graph_t *G, char *v_name);
void graph_vertex_parents_print(graph_t *G, char *v_name);
void graph_edge_list_print(graph_t *G);
#endif