#include <stdio.h>
#include <stdlib.h>
#include <mkl.h>

int main() {
	MKL_COMPACT_PACK = mkl_get_format_compact();
}
