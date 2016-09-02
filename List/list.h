#ifndef LIST_H
#define LIST_H
struct node;
typedef struct node node_t;
typedef struct node *cursor_t;
struct list;
typedef struct list list_t;
list_t list_construct(void);
cursor_t cursor_construct(list_t *L_ptr);
void cursor_advance(cursor_t *c_ptr, int steps);
void *cursor_val(cursor_t *c_ptr);
void list_apend(list_t *L_ptr, void *val);
int list_len(list_t *L_ptr);
void *list_get(list_t *L_ptr, int ind);
void list_del_first(list_t *L_ptr);
void list_del_mid(list_t *L_ptr, int ind);
void list_del_last(list_t *L_ptr);
void list_del_by_ind(list_t *L_ptr, int ind);
void list_del_by_val(list_t *L_ptr, void *val);
void list_destroy(list_t *L_ptr);
#endif