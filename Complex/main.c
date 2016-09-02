#include <stdio.h>
#include "complex.h"

void complex_print(complex z) {
	if (z.imag >= 0.0) {
		printf("%f+%fi", z.real, z.imag);
	}
	else {
		printf("%f%fi", z.real, z.imag);
	}
}

int main() {
	complex z_1, z_2;
	z_1 = complex_init(1.0, 1.0);
	z_2 = complex_init(2.0, 3.0);
	printf("z_1+z_2 = ");
	complex_print(complex_add(z_1, z_2));
	printf("\n\nz_1*z_2 = ");
	complex_print(complex_mult(z_1, z_2));
	printf("\n\nz_1/z_2 = ");
	complex_print(complex_div(z_1, z_2));
	return 0;
}