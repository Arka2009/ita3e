#include "cache_ubench.h"
char X[N];

// Performance of strided accesses
void array_init(char *X, int size) {
	int i = 0;
	for(i = 0; i < size; i++)
		X[i] = 0;
}

void cache_ubench(int len, int stride) {
	int i = 0, tot = 0;
	char y = 0;
	struct timespec start, end;
	long long time_diff;

	clock_gettime(CLOCK_THREAD_CPUTIME_ID,&start);
	for(i = 0; i < len; i += stride) {
		y = X[i]; // Access the array element
		tot++;
	}
	clock_gettime(CLOCK_THREAD_CPUTIME_ID,&end);
	time_diff = calculate_time_diff_spec(end,start);
	printf("Time elapsed (in ns) = %lld, iter_count = %d\n",time_diff,tot);
}
