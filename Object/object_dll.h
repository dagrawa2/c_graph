#ifndef OBJECT_H
#define OBJECT_H
__declspec(dllexport) struct object;
__declspec(dllexport) typedef struct object object_t;
__declspec(dllexport) object_t *object_construct(int state);
__declspec(dllexport) void object_destroy(object_t *O);
__declspec(dllexport) int object_get_state(object_t *O);
__declspec(dllexport) void object_set_state(object_t *O, int state);
__declspec(dllexport) void object_negate(object_t *O);
__declspec(dllexport) void object_print_state(object_t *O);
#endif