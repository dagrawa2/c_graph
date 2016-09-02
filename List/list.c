#include <stdio.h>
#include <windows.h>
#include "list.h"

struct node {
	void *val;
	struct node *next;
};

struct list {
	cursor_t head;
	cursor_t tail;
	int len;
};

list_t list_construct(void) {
	list_t L;
	L.head = NULL;
	L.tail = NULL;
	L.len = 0;
	return L;
}

cursor_t cursor_construct(list_t *L_ptr) {
	return L_ptr->head;
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

void list_apend(list_t *L_ptr, void *val) {
	if (L_ptr->len == 0) {
	L_ptr->tail = malloc(sizeof(node_t));
		if (L_ptr->tail == NULL) {
			printf("Error: Not enough memory!");
			exit(1);
		}
		L_ptr->head = L_ptr->tail;
	}
	else {
		L_ptr->tail->next = malloc(sizeof(node_t));
		if (L_ptr->tail->next == NULL) {
			printf("Error: Not enough memory!");
			exit(1);
		}
		L_ptr->tail = L_ptr->tail->next;
	}
	L_ptr->tail->val = val;
	L_ptr->tail->next = NULL;
	L_ptr->len++;
}

int list_len(list_t *L_ptr) {
	return L_ptr->len;
}

void *list_get(list_t *L_ptr, int ind) {
	cursor_t c = cursor_construct(L_ptr);
	if (ind < 0) {
		printf("Error: List index cannot be negative!");
		exit(1);
	}
	else if (ind >= L_ptr->len) {
		printf("Error: List index out of range!");
		exit(1);
	}
	cursor_advance(&c, ind);
	return c->val;
}

static void list_del_first(list_t *L_ptr) {
	cursor_t c = cursor_construct(L_ptr);
	L_ptr->head = c->next;
	free(c);
	if (L_ptr->len == 1) {
		L_ptr->tail = NULL;
	}
	L_ptr->len--;
}

static void list_del_mid(list_t *L_ptr, int ind) {
	cursor_t c = cursor_construct(L_ptr);
	cursor_t temp = NULL;
	cursor_advance(&c, ind-1);
	temp = c->next;
	c->next = temp->next;
	free(temp);
	L_ptr->len--;
}

static void list_del_last(list_t *L_ptr) {
	cursor_t c = cursor_construct(L_ptr);
	cursor_advance(&c, L_ptr->len-2);
	c->next = NULL;
	free(L_ptr->tail);
	L_ptr->tail = c;
	L_ptr->len--;
}

void list_del_by_ind(list_t *L_ptr, int ind) {
	if (ind < 0) {
		printf("Error: List index cannot be negative!");
		exit(1);
	}
	if (ind >= L_ptr->len) {
		printf("Error: List index out of range!");
		exit(1);
	}
	if (ind == 0) {
		list_del_first(L_ptr);
	}
	else if (ind == L_ptr->len-1) {
		list_del_last(L_ptr);
	}
	else {
		list_del_mid(L_ptr, ind);
	}
}

void list_del_by_val(list_t *L_ptr, void *val) {
	cursor_t c = cursor_construct(L_ptr);
	int ind = 0;
	for (c; c!=NULL; cursor_advance(&c, 1)) {
		if (c->val == val) {
			break;
		}
		ind++;
	}
	if (ind == L_ptr->len) {
		printf("Error: This value does not exist!");
		exit(1);
	}
	if (ind == 0) {
		list_del_first(L_ptr);
	}
	else if (ind == L_ptr->len-1) {
		list_del_last(L_ptr);
	}
	else {
		cursor_t temp = cursor_construct(L_ptr);
		cursor_advance(&temp, ind-1);
		temp->next = c->next;
		free(c);
		L_ptr->len--;
	}
}



void list_destroy(list_t *L_ptr) {
	int n = L_ptr->len;
	for (int i=0; i<n; i++) {
		list_del_first(L_ptr);
	}
}

int main(void) {
	char *A[] = {"alice", "bob", "chad", "dana"};
	list_t L = list_construct();
	int i;
	for (i=0; i<4; i++) {
		list_apend(&L, A[i]);
	}
	cursor_t c = cursor_construct(&L);
	printf("[");
	for (c; c!=NULL; cursor_advance(&c, 1)) {
		printf("%s ", (char *)cursor_val(&c));
	}
	printf("]\n");
	list_del_by_val(&L, A[1]);
	c = cursor_construct(&L);
	printf("[");
	for (c; c!=NULL; cursor_advance(&c, 1)) {
		printf("%s ", (char *)cursor_val(&c));
	}
	printf("]\n");
	list_destroy(&L);
	return 0;
}