#include "ita3e_queue.h"
#include <stdlib.h>
#include <stdio.h>

// Call The Client
int main(int argc, char** argv) {
	//return ita3e_array_queue_test();
	//return ita3e_linked_queue_test();
	//return ita3e_linked_stack_test();
	return ita3e_indexedseq_test(argc, argv);
}
