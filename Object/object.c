#include <stdio.h>
#include <windows.h>
#include "object_dll.h"

struct object {
	int state;
};

object_t *object_construct(int state) {
	object_t *O = malloc(sizeof(object_t));
	O->state = state;
	return O;
}

void object_destroy(object_t *O) {
	free(O);
}

int object_get_state(object_t *O) {
	return O->state;
}

void object_set_state(object_t *O, int state) {
	O->state = state;
}

void object_negate(object_t *O) {
	O->state = -O->state;
}

void object_print_state(object_t *O) {
	printf("%d\n", object_get_state(O));
}

int main(void) {
	printf("Hello from object.c");
	return 0;
}