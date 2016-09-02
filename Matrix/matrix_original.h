#ifndef MATRIX_H
#define MATRIX_H
struct matrix;
struct matrix matrix_construct_raw(int m, int n);
struct matrix matrix_construct_zeros(int m, int n);
struct matrix matrix_construct_fill(int m, int n, float B[]);
struct matrix matrix_iden(int n);
static void destroy_func(struct matrix *A);
static float get_func(struct matrix *A, int i, int j);
static void set_func(struct matrix *A, int i, int j, float x);
static struct matrix transpose_func(struct matrix *A);
static struct matrix scale_func(struct matrix *A, float k);
static struct matrix pinverse_func(struct matrix *A, int steps, float step_size);
struct matrix matrix_add(struct matrix A, struct matrix B);
struct matrix matrix_subtract(struct matrix A, struct matrix B);
struct matrix matrix_mult(struct matrix A, struct matrix B);

void print_matrix(struct matrix A);
#endif