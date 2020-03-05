#include <stdio.h>
#include <stdlib.h>

#define MAX_TASKS 24
int main() {
	unsigned int tid  = 0;
	unsigned int i, j = 0;
	for (j = 0; /*j < MAX_TASKS*/; j++) {
		printf("slave%d : j = %d, lim = %d, exit? = %s\n",tid,j,MAX_TASKS,(j < MAX_TASKS)?"true":"false");
		//tasks[i].symbolData = symbolData;
	}
	printf("Done\n");
	exit(EXIT_FAILURE);	
}
