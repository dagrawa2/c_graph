#ifndef OBJECT_H
#define OBJECT_H
struct object;
typedef struct object object_t;
object_t *object_construct(int state);
void object_destroy(object_t *O);
int object_get_state(object_t *O);
void object_set_state(object_t *O, int state);
void object_negate(object_t *O);
void object_print_state(object_t *O);
#endif