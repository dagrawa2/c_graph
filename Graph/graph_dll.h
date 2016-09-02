#ifndef GRAPH_DLL_H
#define GRAPH_DLL_H
struct vertex;
typedef struct vertex vertex_t;
struct graph;
typedef struct graph graph_t;
__declspec(dllexport) vertex_t *void_to_vertex(void *ptr);
__declspec(dllexport) vertex_t *vertex_cursor_val(cursor_t *c_ptr);
__declspec(dllexport) char *vertex_cursor_name(cursor_t *c_ptr);
__declspec(dllexport) list_t *vertex_cursor_children(cursor_t *c_ptr);
__declspec(dllexport) list_t *vertex_cursor_parents(cursor_t *c_ptr);
__declspec(dllexport) cursor_t vertex_cursor(list_t *L, char *v_name);
__declspec(dllexport) graph_t *graph_construct(void);
__declspec(dllexport) list_t *graph_vertex_list(graph_t *G);
__declspec(dllexport) int graph_order(graph_t *G);
__declspec(dllexport) vertex_t *graph_vertex(graph_t *G, char *v_name);
__declspec(dllexport) list_t *graph_vertex_children(graph_t *G, char *v_name);
__declspec(dllexport) list_t *graph_vertex_parents(graph_t *G, char *v_name);
__declspec(dllexport) int graph_vertex_deg_in(graph_t *G, char *v_name);
__declspec(dllexport) int graph_vertex_deg_out(graph_t *G, char *v_name);
__declspec(dllexport) void graph_add_vertex(graph_t *G, char *v_name);
__declspec(dllexport) void graph_add_edge(graph_t *G, char *v_name, char *w_name);
__declspec(dllexport) void graph_del_vertex(graph_t *G, char *v_name);
__declspec(dllexport) void graph_del_edge(graph_t *G, char *v_name, char *w_name);
__declspec(dllexport) void graph_destroy(graph_t *G);
__declspec(dllexport) void vertex_list_print(list_t *L);
__declspec(dllexport) void graph_vertex_list_print(graph_t *G);
__declspec(dllexport) void graph_vertex_children_print(graph_t *G, char *v_name);
__declspec(dllexport) void graph_vertex_parents_print(graph_t *G, char *v_name);
__declspec(dllexport) void graph_edge_list_print(graph_t *G);
#endif