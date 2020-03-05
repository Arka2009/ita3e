#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#define CONSUMERS 1	 /* Hard code to 1 */

pthread_t  thr[CONSUMERS];

/* Holds the time a particular subframe is added */
long long int subframe_addition_time[MAX_SUBFRAMES];
long long int subframe_dispatch_time[MAX_SUBFRAMES];

/* Define a dummy fifo content */
typedef struct __fifo_content_t fifo_content_t;

struct __fifo_content_t {
	uint64_t				data;
	unsigned int 			valid;
	struct __fifo_content_t *next;
};

typedef struct __fifo_t fifo_t;

struct fifo_t {
	fifo_content_t *first;
	fifo_content_t *last;
	pthread_mutex_t	lock;
	unsigned int count;
	pthread_cond_t cv;
};

void fifo_init(fifo *f) {
	f->first = NULL;
	f->last	 = NULL;
	pthread_mutex_init(&f->lock,NULL);
	f->count = 0;
	pthread_cond_init(&f->lock,NULL);
}

void fifo_enq(fifo_t *f, uint64_t x) {
	fifo_content_t *new_node = (fifo_content_t*)malloc(sizeof(fifo_content_t));
	
	if(!new_node) {
		fprintf(stderr,"memory allocation failed !!\n");
		exit(EXIT_FAILURE);
	}

	new_node->data		= x;
	new_node->valid		= 1;
	new_node->next		= NULL;

	pthread_mutex_lock(&f->lock);
	if(f->first == NULL) {
		f->first = new_node;
		f->last  = new_node;
	}
	else {
		f->last->next = new_node;
		f->last		  = new_node;
	}
	f->count++;
	if(f->count > 0)
		pthread_cond_broadcast(&f->cv);
	pthread_mutex_unlock(&f->lock);
}

fifo_content_t fifo_deq(fifo_t *f) {
	fifo_content_t x = {0,0};
	pthread_mutex_lock(&f->lock);
	while(f->count <= 0)
		pthread_cond_wait(&f->cv,&f->lock);
	/*if(f->count == 0) {
		pthread_mutex_unlock(&f->lock);
		return x;
	}*/
	fifo_content_t *old_node = f->first;
	f->first				 = f->first->next;
	x.data					 = f->data;
	x.valid					 = f->valid;
	free(old_node);
	f->count--;
	pthread_mutex_unlock(&f->lock);
	return x;
}

fifo_t fifo;
/* Consumer thread */
#define MAX_SAMPLES 3000
long long int dispatch_time[MAX_SAMPLES];
long long int add_time[MAX_SAMPLES];
struct timespec prog_start_time_spec;

void *thr_cons(void *arg) {
	int *thr_arg 		= (thr_args_t*)arg;
	int thr_id			= *thr_arg;
	affinity_set_cpu(thr_id);

	userS *user = NULL;
	struct timespec dispatch_time;
	fifo_cont_t x;

	while(1) {
		/* Continuously look for work in the fifo */
		x = fifo_deq(&fifo);
		clock_gettime(CLOCK_REALTIME,&dispatch_time);

		dispatch_time[i] = \
		calculate_time_diff_spec(dispatch_time,prog_start_time_spec);
	}
}

/* This also the producer thread */
int main() {
	affinity_set_cpu(62);
	int  i = 0, rc = 0;
	unsigned int subframeId;
	struct timespec add_time;

	/* User info */
	user_parameters *parameters;
	parameter_model pmodel;

	FILE* fd = fopen("thr_comm_timing.csv","w");
	if(!fd) {
		fprintf(stderr,"File open failed \n");
		exit(EXIT_FAILURE);
	}

	/* Initialize the data structures */
	init_data();
	crcInit();
	init_parameter_model(&pmodel);
	buffer_init1();
	uplink_alarm_init(DELTA);
	
	/* Spawn the threads */
	for(i = 0; i < CONSUMERS; i++) {
		/* Setup Arguments */
		thr_args[i].thr_id		= i;
		thr_args[i].user_buffer = &user_buffer;

		/* Start thread */
		rc = pthread_create(&thr[i],NULL,thr_cons,&thr_args[i]);
		if (rc) {
			printf("ERROR; return code from pthread_create() is %d\n", rc);
			exit(EXIT_FAILURE);
		}
	}
	
	clock_gettime(CLOCK_REALTIME, &prog_start_time_spec);
	while (!stop) {
		
		/* Generate user list for next subframe */
		parameters = uplink_parameters(&pmodel);

		/* Wait for DELTA alarm */
		uplink_wait_for_alarm();

		if(parameters) {
			subframeId = parameters->first->subframe;
			
			/* Time stamp, at the point of subframe addition */	
			clock_gettime(CLOCK_REALTIME,&add_time);
			subframe_addition_time[subframeId] = \
			calculate_time_diff_spec(add_time,prog_start_time_spec);		
			
			/* update the stop condition */
			stop = (subframeId < MAX_SUBFRAMES-1)?false:true;

			/* Add the subframes to the user queue */
			pthread_mutex_lock(&user_buffer.lock);
			if (user_buffer.first == NULL)
				user_buffer.first 		= parameters->first;
			else
				user_buffer.last->next 	= parameters->first;
			user_buffer.last 			= parameters->last;
			user_buffer.subframes_count++;
			pthread_mutex_unlock(&user_buffer.lock);

			printf("subframe:%d generated \n",subframeId);
			free(parameters);
		}
	}

	/* Wait for consumers to finish */
	while(user_buffer.subframes_count);

	fprintf(fd,"subframe,add,dispatch\n");
	for(i = 0; i < MAX_SUBFRAMES; i++)
		fprintf(fd,"%d,%lld,%lld\n",i,subframe_addition_time[i],subframe_dispatch_time[i]);

	fclose(fd);
}
