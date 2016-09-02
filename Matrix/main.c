#include <stdio.h>
#include "matrix.h"

void print_matrix(struct matrix A) {
	for (int i=0; i<2; i++) {
		printf("[");
		for(int j=0; j<2; j++) {
			if (j == 1) {
				printf("%3.3f]\n", A.array[2*i+j]);
			}
			else {
				printf("%3.3f, ", A.array[2*i+j]);
			}
		}
	}
}

int main(void) {
	struct matrix A, B, C, I;
	float values[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
float values_C[] = {2.0, 3.0, 3.0, 5.0};
	A = matrix_construct_fill(3, 2, values);
	I = matrix_iden(2);
	printf("A = \n");
	print_matrix(A);
	printf("\nI = \n");
	print_matrix(I);
	printf("\nA.transpose = \n");
	print_matrix((*A.transpose)(&A));
	printf("\nB = A.transpose*A = \n");
	B = matrix_mult((*A.transpose)(&A), A);
	print_matrix(B);
	printf("\nA[0, 1] = %3.3f\n", (*A.get)(&A, 0, 1));
	printf("\nChange an element of A:\n");
	(*A.set)(&A, 0, 1, 5.0);
	printf("\nA[0, 1] = %3.3f\n", (*A.get)(&A, 0, 1));
	printf("\nB-2I = \n");
	print_matrix(matrix_subtract(B, (*I.scale)(&I, 2.0)));
	printf("\nC = \n");
	C = matrix_construct_fill(2, 2, values_C);
	print_matrix(C);
	printf("\nC.pinverse = \n");
	print_matrix((*C.pinverse)(&C, 20000, 0.01));
	(*A.destroy)(&A);
	(*B.destroy)(&B);
	(*C.destroy)(&C);
	(*I.destroy)(&I);
	return 0;
}