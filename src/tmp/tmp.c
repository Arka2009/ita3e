#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define N 102400
int main() {
	//uint64_t* ptr = (uint64_t*)calloc(N,sizeof(uint64_t));
	//uint64_t* tmp = ptr;
	//printf("\n Mem-tmp = %lx, Offset[%d] = %lx \n",tmp,N-1,tmp[N-1]);
	//printf("\n Mem-Ptr = %lx, Offset[%d] = %lx \n",ptr,N-1,ptr[N-1]);
	//free(tmp);
	//free(ptr);
	uint64_t array[N];
	printf("\n Mem-array = %lx, Offset[%d] = %lx \n",array,N-1,array[N-1]);
	return 0;
}
