#ifndef MATRIX_H
#define MATRIX_H
__declspec(dllexport) struct matrix;
__declspec(dllexport) struct matrix matrix_construct_raw(int m, int n);
__declspec(dllexport) struct matrix matrix_construct_zeros(int m, int n);
__declspec(dllexport) struct matrix matrix_construct_fill(int m, int n, float B[]);
__declspec(dllexport) struct matrix matrix_iden(int n);
__declspec(dllexport) struct matrix matrix_add(struct matrix A, struct matrix B);
__declspec(dllexport) struct matrix matrix_subtract(struct matrix A, struct matrix B);
__declspec(dllexport) struct matrix matrix_mult(struct matrix A, struct matrix B);

__declspec(dllexport) void destroy_func(struct matrix *A);
__declspec(dllexport) float get_func(struct matrix *A, int i, int j);
__declspec(dllexport) void set_func(struct matrix *A, int i, int j, float x);
__declspec(dllexport) struct matrix transpose_func(struct matrix *A);
__declspec(dllexport) struct matrix scale_func(struct matrix *A, float k);
__declspec(dllexport) struct matrix pinverse_func(struct matrix *A, int steps, float step_size);
#endif