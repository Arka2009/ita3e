#include <stdio.h>
#include <stdlib.h>
#include "ita3e_errors.h"
#include "ita3e_sort.h"

void ita3e_item_array_exch(ita3e_item_t* A, int i, int j) {
	ita3e_item_t tmp = A[i];
	A[i]			 = A[j];
	A[j]			 = tmp;
}

int ita3e_item_array_sorted(ita3e_item_t* A, int lo, int hi) {
	for(int i = lo; i < hi; i++)
		if(ita3e_item_compare(A[i],A[i+1]) > 0) return 0;
	return 1;
}

// Return a "pointer" (array index) to the min element
int ita3e_item_array_min(ita3e_item_t* A, int hi, int lo) {

	if(hi < lo)
		return -1;

	int pos = lo;
	for(int i = lo+1; i <= hi; i++) {
		if(ita3e_item_compare(A[i],A[pos]) < 0)
			pos = i;
	}
	return pos;
}

int ita3e_item_selection_sort(ita3e_item_t* A, int N) {
	int pos = 0;
	for(int i = 0; i < N; i++) {
		pos = ita3e_item_array_min(A,i+1,N-1);
		ita3e_item_array_exch(A,i,pos);	
	}

	if(!ita3e_item_array_sorted(A,0,N-1)) {
		fprintf(stderr,"Selection Sort failed");
		return E_ITA3E_ASSERTFAIL;
	}
	return E_ITA3E_OK;
}

int ita3e_item_insertion_sort(ita3e_item_t* A, int N) {
	int i, j;
	for(i = 1; i < N; i++) {
		for(j = i; j > 0; j--) {
			if(ita3e_item_compare(A[j],A[j-1]) < 0)
				ita3e_item_array_exch(A,j,j-1);
		}
	}
	
	if(!ita3e_item_array_sorted(A,0,N-1)) {
		fprintf(stderr,"Insertion Sort failed");
		return E_ITA3E_ASSERTFAIL;
	}
	return E_ITA3E_OK;
}

int ita3e_item_merge_sort(ita3e_item_t* A, int N) {
	ita3e_item_t* aux = (ita3e_item_t*)calloc(N,sizeof(ita3e_item_t));
	if(aux == NULL) {
		fprintf(stderr,"Auxiliary Storage allocation for merge sort is unsuccessful");
		return E_ITA3E_HEAPLOW;
	}
	int lo = 0;
	int hi = N-1;
	ita3e_item_merge_sort1(A,aux,lo,hi);
	free(aux);

	if(!ita3e_item_array_sorted(A,0,N-1)) {
		fprintf(stderr,"Merge Sort failed");
		return E_ITA3E_ASSERTFAIL;
	}
	return E_ITA3E_OK;
}

int ita3e_item_merge_sort1(ita3e_item_t* A, ita3e_item_t* aux, int lo, int hi) {
	if(lo >= hi) return E_ITA3E_OK;
	int mid = lo + (hi - lo)/2;
	ita3e_item_merge_sort1(A,aux,lo,mid);
	ita3e_item_merge_sort1(A,aux,mid+1,hi);
	ita3e_item_merge_subarray(A,aux,lo,mid,hi);
	return E_ITA3E_OK;
}

int ita3e_item_merge_subarray(ita3e_item_t* A, ita3e_item_t* aux, int lo, int mid, int hi) {
	if(!ita3e_item_array_sorted(A,lo,mid)) {
		fprintf(stderr," Left half Array Unsorted during merge step");
		return E_ITA3E_ASSERTFAIL;
	}
	if(!ita3e_item_array_sorted(A,mid+1,hi)) {
		fprintf(stderr," Right half Array Unsorted during merge step");
		return E_ITA3E_ASSERTFAIL;
	}
	for(int i = lo; i <= hi; i++) 
		aux[i] = A[i];

	int i = lo, j = mid+1, k;
	for(k = lo; k <= hi; k++) {
		if(i > mid) A[k] = aux[j++];
		else if(j > hi) A[k] = aux[i++];
		else if(ita3e_item_compare(aux[i],aux[j]) < 0) A[k] = aux[i++];
		else A[k] = aux[j++];
	}
	return E_ITA3E_OK;
}
