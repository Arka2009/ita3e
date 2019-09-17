#include <ita3e.h>

// Define Apprpriate Exit/Error codes
#define E_ITA3E_OK 										0
#define E_ITA3E_ILLARG 									-1 // Illegal Arg Count
#define E_ITA3E_OVERFLOW 								-2
#define E_ITA3E_UNDERFLOW								-3
#define E_ITA3E_HEAPLOW									-4 // Dynamic Memory Allocation unsuccessful
#define E_ITA3E_OUTOFBOUND								-5 // (Array) Index Out of Bound
#define E_ITA3E_ASSERTFAIL                              -6 // Assertion failure
#define E_ITA3E_KEYNOTFOUND								-7 // (Search) key not found

#define CONJ_ERR(a,b) \
	if((a == E_ITA3E_OK) && (b == E_ITA3E_OK)) \
		E_ITA3E_OK			\
	else if(a == E_ITA3E_OK) \
		b					\
	else					\
		a			
