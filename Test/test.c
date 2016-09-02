#include <stdio.h>
#include "test.h"

void print_hello(void) {
	printf("Hello from test.h!\n");
}

int main(void) {
	printf("This is function main from test.c\n");
	return 0;
}