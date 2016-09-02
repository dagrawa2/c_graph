#include <stdio.h>
#include "list_dll.h"

int main(void) {
	char *A[] = {"alice", "bob", "chad", "dana"};
	list_t *L = list_construct();
	int i;
	for (i=0; i<4; i++) {
		list_append(L, A[i]);
	}
	cursor_t c = cursor(L);
	printf("[");
	for (c; c!=NULL; cursor_advance(&c, 1)) {
		printf("%s ", (char *)cursor_val(&c));
	}
	printf("]\n");
	list_del_by_val(L, A[1]);
	c = cursor(L);
	printf("[");
	for (c; c!=NULL; cursor_advance(&c, 1)) {
		printf("%s ", (char *)cursor_val(&c));
	}
	printf("]\n");
	list_destroy(L);
	return 0;
}