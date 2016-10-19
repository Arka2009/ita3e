#include<stdio.h>
#include<stdlib.h>
#include"ita3e.h"
#include"ita3e_sort.h"

/*	Refer page-18, ita3e */
void InsertionSort(int * A, int length) {
	int i, j, key;
	for(j = 1; j < length; j++) {
		key = A[j];
		// Insert A[j] into the sorted sequence A[0...j-1].
		i = j-1;
		while(i>=0 && A[i] > key) {
			A[i+1] = A[i];
			i--;
		}
		A[i+1] = key;
	}
}

/* Refer page-30,31, ita3e */
//void Merge(int * A, int p, int q, int r) {
//	int n1 = q-p+1;
//	int n2 = 	r-p;
//	int i, j, L[], R[];
//	for(i = 0; i < n1; i++) {
//	}
//}
