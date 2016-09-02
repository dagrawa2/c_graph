#include <stdio.h>
#include <windows.h>
#include <string.h>

int main(void) {
	char *s = "hello";
	char *t = "hello";
	if (strcmp(s, t)==0) {
		printf("yes\n");
	}
	else {
		printf("no\n");
	}
	return 0;
}