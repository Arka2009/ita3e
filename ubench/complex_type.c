#include<stdio.h>
#include<complex.h>
#include<stdlib.h>

int main() {
	float complex a = ((float)rand())/((float)RAND_MAX) + I * (((float)rand())/((float)RAND_MAX));
	float complex b = ((float)rand())/((float)RAND_MAX) + I * (((float)rand())/((float)RAND_MAX));

	float complex c = a + b;

	printf("a = %f + %fi\n",crealf(a),cimagf(a));
	printf("b = %f + %fi\n",crealf(b),cimagf(b));
	printf("c = %f + %fi\n",crealf(c),cimagf(c));
}
