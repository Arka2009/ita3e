#define _GNU_SOURCE
#include <fftw3.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/* Compute t2 - t1 */
inline long long calculate_time_diff_spec(struct timespec t2, struct timespec t1) {
    long long elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000000000LL + t2.tv_nsec - t1.tv_nsec;
	return elapsedTime;
}

/* set the affinity of a thread */
int affinity_set_cpu(int _id) {
	int cpuid = _id % 64;
	cpu_set_t set;
	CPU_ZERO(&set);
	CPU_SET(cpuid, &set);
	CPU_SET(cpuid+64, &set);
	CPU_SET(cpuid+128, &set);
	CPU_SET(cpuid+192, &set);
	int rc = pthread_setaffinity_np(pthread_self(),sizeof(cpu_set_t),&set);
	//printf("task_aff:%d affined to cpuid:%d\n",_id,cpuid);
	if(rc != 0) {
		fprintf(stderr,"Set Affinity failed for tid#%u\n",_id);
		return -1;
	}
	return 0;
}

#define SAMPLES 3000
int main(int argc, char **argv) {
	if(argc < 3) {
		fprintf(stderr,"Enter the size of FFT and number of threads \n");
		exit(EXIT_FAILURE);
	}
	int N 			= atoi(argv[1]);
	int num_threads = atoi(argv[2]);
	int i			= 0;
	FILE *fdfftw3   = fopen("log/fftw3_perf.csv","w");
	if(!fdfftw3) {
		fprintf(stderr,"Cannot open csv for dumping\n");
		exit(EXIT_FAILURE);
	}

	if(fftw_init_threads() <= 0) {
		fprintf(stderr,"MT FFTW initialization failed\n");
		exit(EXIT_FAILURE);
	}
	fftw_plan_with_nthreads(num_threads);

    fftw_complex *in, *out;
    fftw_plan p;
    in  = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
	struct timespec start, end;
	long long timediff;
    
	//p= fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
	p= fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_MEASURE);

	for(i = 0; i < SAMPLES; i++) {
		clock_gettime(CLOCK_MONOTONIC,&start);
    	fftw_execute(p); /* repeat as needed */
		clock_gettime(CLOCK_MONOTONIC,&end);
		timediff = calculate_time_diff_spec(end,start);
		fprintf(fdfftw3,"sample:%d,%lld\n",i,timediff);
	}
    fftw_destroy_plan(p);
    fftw_free(in);
	fftw_free(out);
	fftw_cleanup_threads();

	return 0;
}
