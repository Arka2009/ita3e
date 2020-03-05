#include <stdio.h>
#include <stdlib.h>

typedef char holder_t;

void towers_of_hanoi(int n, holder_t src, holder_t dst, holder_t tmp) {
    static unsigned int af = 0;
    if (n > 0) {
        towers_of_hanoi(n-1, src, tmp, dst);
        printf("ACTIVATION%d : moving %d from %c to %c\n",af++,n,src,dst);
        towers_of_hanoi(n-1, tmp, dst, src);
    }
}

int main() {
    towers_of_hanoi(5,'s','d','t');
    return 0;
}
