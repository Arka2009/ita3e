#include <stdio.h>
#include <stdlib.h>

#define N 1000

typedef int vec_t;

void vec_add(vec_t *A, vec_t *B, vec_t *C, int size) {
	int i;
	for(i = 0; i < size; i++)
		C[i] = A[i] + B[i];
}

//void init_vec(vec_t *X, int size) {
//	int i;
//	for(i = 0; i < size; i++)
//		X[i] = (vec_t)(rand() % 100);
//}
//
//vec_t A[N], B[N], C[N];
//
//int main() {
//	init_vec(A,N);
//	init_vec(B,N);
//	vec_add(A,B,C,N);
//	return 0;
//}
