#include <stdio.h>
#include <stdlib.h>
#include "cache_ubench.h"

int main() {
	cache_ubench(500,25);
	printf("size of char = %ld\n",sizeof(char));
	return 0;
}
