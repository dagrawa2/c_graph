#include <stdio.h>
#include <windows.h>
#include "list_dll.h"

struct node {
	void *val;
	struct node *next;
};

struct list {
	cursor_t head;
	cursor_t tail;
	int len;
};

list_t *list_construct(void) {
	list_t *L = malloc(sizeof(list_t));
	L->head = NULL;
	L->tail = NULL;
	L->len = 0;
	return L;
}

cursor_t cursor(list_t *L) {
	return L->head;
}

void cursor_advance(cursor_t *c_ptr, int steps) {
	for (int i=0; i<steps; i++) {
		if (*c_ptr != NULL) {
			*c_ptr = (*c_ptr)->next;
		}
	}
}

void *cursor_val(cursor_t *c_ptr) {
	return (*c_ptr)->val;
}

void list_append(list_t *L, void *val) {
	if (L->len == 0) {
	L->tail = malloc(sizeof(node_t));
		if (L->tail == NULL) {
			printf("Error: Not enough memory!\n");
			exit(1);
		}
		L->head = L->tail;
	}
	else {
		L->tail->next = malloc(sizeof(node_t));
		if (L->tail->next == NULL) {
			printf("Error: Not enough memory!\n");
			exit(1);
		}
		L->tail = L->tail->next;
	}
	L->tail->val = val;
	L->tail->next = NULL;
	L->len++;
}

int list_len(list_t *L) {
	return L->len;
}

void *list_get(list_t *L, int ind) {
	cursor_t c = cursor(L);
	if (ind < 0) {
		printf("Error: List index cannot be negative!\n");
		exit(1);
	}
	else if (ind >= L->len) {
		printf("Error: List index out of range!\n");
		exit(1);
	}
	cursor_advance(&c, ind);
	return c->val;
}

static void list_del_first(list_t *L) {
	cursor_t c = cursor(L);
	L->head = c->next;
	free(c);
	if (L->len == 1) {
		L->tail = NULL;
	}
	L->len--;
}

static void list_del_mid(list_t *L, int ind) {
	cursor_t c = cursor(L);
	cursor_t temp = NULL;
	cursor_advance(&c, ind-1);
	temp = c->next;
	c->next = temp->next;
	free(temp);
	L->len--;
}

static void list_del_last(list_t *L) {
	cursor_t c = cursor(L);
	cursor_advance(&c, L->len-2);
	c->next = NULL;
	free(L->tail);
	L->tail = c;
	L->len--;
}

void list_del_by_ind(list_t *L, int ind) {
	if (ind < 0) {
		printf("Error: List index cannot be negative!\n");
		exit(1);
	}
	if (ind >= L->len) {
		printf("Error: List index out of range!\n");
		exit(1);
	}
	if (ind == 0) {
		list_del_first(L);
	}
	else if (ind == L->len-1) {
		list_del_last(L);
	}
	else {
		list_del_mid(L, ind);
	}
}

void list_del_by_val(list_t *L, void *val) {
	cursor_t c = cursor(L);
	int ind = 0;
	for (c; c!=NULL; cursor_advance(&c, 1)) {
		if (c->val == val) {
			break;
		}
		ind++;
	}
	if (ind == L->len) {
		printf("Error: This value does not exist!\n");
		exit(1);
	}
	if (ind == 0) {
		list_del_first(L);
	}
	else if (ind == L->len-1) {
		list_del_last(L);
	}
	else {
		cursor_t temp = cursor(L);
		cursor_advance(&temp, ind-1);
		temp->next = c->next;
		free(c);
		L->len--;
	}
}

void list_destroy(list_t *L) {
	int n = L->len;
	for (int i=0; i<n; i++) {
		list_del_first(L);
	}
	free(L);
}

int main(void) {
	printf("Hello from list.c!\n");
	return 0;
}