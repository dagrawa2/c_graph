#ifndef LIST_H
#define LIST_H
struct node;
__declspec(dllexport) typedef struct node node_t;
__declspec(dllexport) typedef struct node *cursor_t;
struct list;
__declspec(dllexport) typedef struct list list_t;
__declspec(dllexport) list_t *list_construct(void);
__declspec(dllexport) cursor_t cursor(list_t *L_ptr);
__declspec(dllexport) void cursor_advance(cursor_t *c_ptr, int steps);
__declspec(dllexport) void *cursor_val(cursor_t *c_ptr);
__declspec(dllexport) void list_append(list_t *L_ptr, void *val);
__declspec(dllexport) int list_len(list_t *L_ptr);
__declspec(dllexport) void *list_get(list_t *L_ptr, int ind);
__declspec(dllexport) void list_del_first(list_t *L_ptr);
__declspec(dllexport) void list_del_mid(list_t *L_ptr, int ind);
__declspec(dllexport) void list_del_last(list_t *L_ptr);
__declspec(dllexport) void list_del_by_ind(list_t *L_ptr, int ind);
__declspec(dllexport) void list_del_by_val(list_t *L_ptr, void *val);
__declspec(dllexport) void list_destroy(list_t *L_ptr);
#endif