#include <stdio.h>
#include "complex.h"

complex complex_init(float a, float b) {
	complex z;
	z.real = a;
	z.imag = b;
	return z;
}

complex conj(complex z) {
	return complex_init(z.real, -z.imag);
}

complex complex_add(complex z_1, complex z_2) {
	return complex_init(z_1.real+z_2.real, z_1.imag+z_2.imag);
}

complex complex_mult(complex z_1, complex z_2) {
	return complex_init(z_1.real*z_2.real-z_1.imag*z_2.imag, z_1.real*z_2.imag+z_1.imag*z_2.real);
}

float mod_squared(complex z) {
	return z.real*z.real+z.imag*z.imag;
}

complex complex_div(complex z_1, complex z_2) {
	float f;
	complex w;
	f = mod_squared(z_2);
	if (f == 0) {
		printf("Error: Division by zero!");
		exit(1);
	}
	w = complex_mult(z_1, conj(z_2));
	return complex_init(w.real/f, w.imag/f);
}