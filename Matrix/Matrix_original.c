#include <stdio.h>
#include <windows.h>
#include "matrix.h"

struct matrix {
	float *array;
	int rows;
	int cols;
void (*destroy)(struct matrix *A);
	float (*get)(struct matrix *A, int i, int j);
void (*set)(struct matrix *A, int i, int j, float x);
struct matrix (*transpose)(struct matrix *A);
struct matrix (*scale)(struct matrix *A, float k);
struct matrix (*pinverse)(struct matrix *A, int steps, float step_size);
};

struct matrix matrix_construct_raw(int m, int n) {
	struct matrix A;
	A.array = malloc(m*n*sizeof *A.array);
	if (A.array == 0) {
		printf("Error: Not enough memory!");
		exit(1);
	}
	A.rows = m;
	A.cols = n;
	A.destroy = destroy_func;
	A.get = get_func;
	A.set = set_func;
	A.transpose = transpose_func;
	A.scale = scale_func;
	A.pinverse = pinverse_func;
	return A;
}

struct matrix matrix_construct_zeros(int m, int n) {
	struct matrix A;
	A = matrix_construct_raw(m, n);
	for (int i=0; i<m; i++) {
		for (int j=0; j<n; j++) {
			A.array[n*i+j] = 0.0;
		}
	}
	return A;
}

struct matrix matrix_construct_fill(int m, int n, float B[]) {
	struct matrix A;
	A = matrix_construct_raw(m, n);
	for (int i=0; i<m; i++) {
		for (int j=0; j<n; j++) {
			A.array[n*i+j] = B[n*i+j];
		}
	}
	return A;
}

struct matrix matrix_iden(int n) {
	struct matrix I;
	I = matrix_construct_raw(n, n);
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			if (i == j) {
				I.array[n*i+j] = 1.0;
			}
			else {
				I.array[n*i+j] = 0.0;
			}
		}
	}
	return I;
}

static void destroy_func(struct matrix *A) {
	free(A->array);
}

static float get_func(struct matrix *A, int i, int j) {
	return A->array[A->cols*i+j];
}

static void set_func(struct matrix *A, int i, int j, float x) {
	A->array[A->cols*i+j] = x;
}

static struct matrix transpose_func(struct matrix *A) {
	struct matrix B;
	B = matrix_construct_raw(A->cols, A->rows);
	for (int i=0; i<B.rows; i++) {
		for(int j=0; j<B.cols; j++) {
			B.array[B.cols*i+j] = A->array[A->cols*j+i];
		}
	}
	return B;
}

static struct matrix scale_func(struct matrix *A, float k) {
	struct matrix B;
	B = matrix_construct_raw(A->rows, A->cols);
	for (int i=0; i<B.rows; i++) {
		for(int j=0; j<B.cols; j++) {
			B.array[B.cols*i+j] = k*(A->array[A->cols*i+j]);
		}
	}
	return B;
}

static struct matrix pinverse_func(struct matrix *A, int steps, float step_size) {
	struct matrix I, X, Grad_X_transpose;
	if (A->rows != A->cols) {
		printf("Error: Inversion requires a square matrix!");
		exit(1);
	}
	I = matrix_iden(A->rows);
	X = matrix_iden(A->rows);
	for (int step=0; step<steps; step++) {
		Grad_X_transpose = matrix_mult(transpose_func(A), matrix_subtract(matrix_mult(*A, X), I));
		X = matrix_subtract(X, scale_func(&Grad_X_transpose, step_size));
	}
	return X;
}

struct matrix matrix_add(struct matrix A, struct matrix B) {
	struct matrix C;
	if (A.rows != B.rows) {
		printf("Error: Rows not aligned in matrix_add!");
		exit(1);
	}
	else if (A.cols != B.cols) {
		printf("Error: Columns not aligned in matrix_add!");
		exit(1);
	}
	C = matrix_construct_raw(A.rows, A.cols);
	for (int i=0; i<C.rows; i++) {
		for(int j=0; j<C.cols; j++) {
			C.array[C.cols*i+j] = A.array[A.cols*i+j] + B.array[B.cols*i+j];
		}
	}
	return C;
}

struct matrix matrix_subtract(struct matrix A, struct matrix B) {
	if (A.rows != B.rows) {
		printf("Error: Rows not aligned in matrix_subtract!");
		exit(1);
	}
	else if (A.cols != B.cols) {
		printf("Error: Columns not aligned in matrix_subtract!");
		exit(1);
	}
	return matrix_add(A, scale_func(&B, -1.0));
}

struct matrix matrix_mult(struct matrix A, struct matrix B) {
	struct matrix C;
	float sum;
	if (A.cols != B.rows) {
		printf("Error: Dimensions not aligned in matrix_mult!");
		exit(1);
	}
	C = matrix_construct_raw(A.rows, B.cols);
	for (int i=0; i<C.rows; i++) {
		for(int j=0; j<C.cols; j++) {
			sum = 0.0;
			for (int k=0; k<A.cols; k++) {
				sum += A.array[A.cols*i+k]*B.array[B.cols*k+j];
			}
			C.array[C.cols*i+j] = sum;
		}
	}
	return C;
}


void print_matrix(struct matrix A) {
	for (int i=0; i<A.rows; i++) {
		printf("[");
		for(int j=0; j<A.cols; j++) {
			if (j == A.cols-1) {
				printf("%3.3f]\n", A.array[A.cols*i+j]);
			}
			else {
				printf("%3.3f, ", A.array[A.cols*i+j]);
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