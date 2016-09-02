#ifndef COMPLEX_H
#define COMPLEX_H
__declspec(dllexport) typedef struct complex_struct {
	float real;
	float imag;
} complex;
__declspec(dllexport) complex complex_init(float a, float b);
__declspec(dllexport) complex conj(complex z);
__declspec(dllexport) complex complex_add(complex z_1, complex z_2);
__declspec(dllexport) complex complex_mult(complex z_1, complex z_2);
__declspec(dllexport) float mod_squared(complex z);
__declspec(dllexport) complex complex_div(complex z_1, complex z_2);
#endif