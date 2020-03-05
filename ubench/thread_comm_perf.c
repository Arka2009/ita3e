#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<unistd.h>
#include<pthread.h>
/* Dummy Satellite Data Structures */
typedef uint64_t task;

typedef struct task_node task_node_t;

struct task_node {
	task 		t;
	task_node_t *next;
};

/* Queue for synchronizing the producer and consumer synchronisation */
typedef struct {
	pthread_mutex_t lock;
	task_node_t *first;
	task_node_t *last;
	volatile unsigned int qcount;
} thr_buffer_t;

thr_buffer_t gq;

/* Queue enq method */
void thr_buffer_enq(thr_buffer_t *buf, const task t) {
	task_node_t *new_node = (task_node_t*)malloc(sizeof(task_node_t));
	if(!new_node) {
		fprintf(stderr,"memory allocation for task ptr failed \n");
		exit(EXIT_FAILURE);
	}
	new_node->t 		  = t;
	new_node->next		  = NULL;
	pthread_mutex_lock(&buf->lock);
	if(buf->first == NULL) {
		buf->first 		= new_node;
		buf->last  		= new_node;
	}
	else {
		buf->last->next = new_node;
		buf->last		= new_node;
	}
	buf->qcount++;
	pthread_mutex_unlock(&buf->lock);
}

/* Queue deq method */
task thr_buffer_deq(thr_buffer_t *buf) {
	task ret 			  = -1;
	pthread_mutex_lock(&buf->lock);
	if(buf->qcount == 0) {
		pthread_mutex_unlock(&buf->lock);
		return -2;
	}
	task_node_t *old_node = buf->first;
	buf->first 			  = buf->first->next;
	ret					  = old_node->t;
	free(old_node);
	buf->qcount--;
	pthread_mutex_unlock(&buf->lock);
	return ret;
}

#define DELTA1		1000
#define DELTA2		1000
#define NUM_DATA	2000

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

struct timespec t1, e1, t2, e2;
long long timediff1, timediff2;

/* Compute t2 - t1 */
inline long long calculate_time_diff_spec(struct timespec t2, struct timespec t1) {
    long long elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000000000LL + t2.tv_nsec - t1.tv_nsec;
	return elapsedTime;
}

void* producer(void *arg) {
	int *tid = (int*)arg;
	affinity_set_cpu(*tid);

	int num_data = NUM_DATA;

	while(num_data--) {
		/* Produce Data */
		task tmp = rand() % 8876;

		clock_gettime(CLOCK_REALTIME,&t1);		
		thr_buffer_enq(&gq,tmp);
		clock_gettime(CLOCK_REALTIME,&e1);
		timediff1 = calculate_time_diff_spec(e1,t1);
	
		printf("Enq time by thread@%d = %lld\n",*tid,timediff1);
		usleep(DELTA1);
	}
}

void* consumer(void *arg) {
	int *tid = (int*)arg;
	affinity_set_cpu(*tid);

	int num_data = NUM_DATA;
	int tmp = -1;

	while(num_data--) {
		
		clock_gettime(CLOCK_REALTIME,&t2);	
		tmp = thr_buffer_deq(&gq);
		clock_gettime(CLOCK_REALTIME,&e2);
		timediff2 = calculate_time_diff_spec(e2,t2);
		
		if(tmp > 0)
			printf("Deq time by thread@%d = %lld\n",*tid,timediff2);	
		usleep(DELTA2);
	}
}

pthread_t prod, cons;
int main(int argc, char *argv[]) {
	if(argc < 3) {
		fprintf(stderr,"Usage: <exec> <prod_id> <cons_id>\n");
		exit(EXIT_FAILURE);
	}
	int prod_id = atoi(argv[1]);
	int cons_id = atoi(argv[2]);

	pthread_create(&prod,NULL,producer,&prod_id);
	pthread_create(&cons,NULL,consumer,&cons_id);

	pthread_join(prod,NULL);
	pthread_join(cons,NULL);
}
