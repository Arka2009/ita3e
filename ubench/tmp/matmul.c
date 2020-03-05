#include <stdio.h>
#define SIZE 100

int first[SIZE][SIZE], second[SIZE][SIZE], multiply[SIZE][SIZE];

int main()
{

  int sum = 0;
  int c,d,k;
 
 
  for (c = 0; c < SIZE; c++) {
    for (d = 0; d < SIZE; d++) {
      	first[c][d] = 1;
        second[c][d] = 1;
        multiply[c][d] = 1;
    }
  }
 
 
    for (c = 0; c < SIZE; c++) {
      for (d = 0; d < SIZE; d++) {
        for (k = 0; k < SIZE; k++) {
          sum = sum + first[c][k]*second[k][d];
        }
        multiply[c][d] = sum;
        sum = 0;
      }
    }
 
 
    //for (c = 0; c < SIZE; c++) {
    //  for (d = 0; d < SIZE; d++) {
    //    printf("%d\t", multiply[c][d]);
    //  }
    //   printf("\n"); 
    //}
 
  return 0;
}
