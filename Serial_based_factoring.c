// Author: Patrick Aung
// Finds the total number of divisors of a bignumber serially

// to compile: gcc Serial_based_factoring.c -o Serial_based_factoring -lm
// to run: ./Serial_based_factoring

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

  unsigned long long bignumber;
  printf("Enter big number: \n");
  scanf("%llu",&bignumber);
  printf("\nbignumber variable contains %llu\n\n", bignumber);

	int divisorSum = 0;
  clock_t startTime, endTime;
	startTime = clock();

  for (int i = 1; i <= bignumber; i++){
    if ((bignumber % i) == 0){
			divisorSum ++;
    }
  }
  endTime = clock();
  double elapsed =  (double)(endTime - startTime) * 1000 / CLOCKS_PER_SEC;
	printf("Total Divisor Sum: %d\n", divisorSum);
	printf("Entire Program Runtime: %f ms\n\n",elapsed);
}
