#include <stdio.h>
#include <windows.h>
#include "object_dll.h"

int main(void) {
	object_t *O = object_construct(0);
	object_print_state(O);
	object_set_state(O, 2);
	object_print_state(O);
	object_negate(O);
	object_print_state(O);
	object_destroy(O);
	return 0;
}