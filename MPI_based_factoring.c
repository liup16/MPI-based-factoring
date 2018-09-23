// Author: Patrick Aung
// Finds the total number of divisors of a bignumber through parallelization

// to compile: mpicc -std=c99 -Wall MPI_based_factoring.c -o MPI_based_factoring
// to run: mpirun -np num_of_cores ./MPI_based_factoring userinput_number

#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]){

	int comm_sz;	// Number of processes
	int my_rank;	// My process rank
	int localsum = 0;
	int globalsum = 0;
	double startTime, endTime, elapsed;
	unsigned long long bignumber;

	MPI_Init(&argc, &argv);	//sets up the MPI. Always this line!
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);	// Get the number of processes
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);	// Get my rank among all the processes

	if (my_rank == 0){
		printf("Enter big number: \n");
		scanf("%llu",&bignumber);
		printf("\nbignumber variable contains %llu\n\n", bignumber);
	}

	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Bcast(&bignumber,1,MPI_UNSIGNED_LONG_LONG,0,MPI_COMM_WORLD);

	startTime = MPI_Wtime();

	for (int i = my_rank+1; i <= bignumber; i+=comm_sz){
		if ((bignumber%i)==0){
			localsum += 1;
		}
	}

	endTime = MPI_Wtime();
	elapsed =  (double)(endTime - startTime) * 1000.0;
	printf("Process %d Divisor Sum: %d\n",my_rank, localsum);
	printf("Process %d Runtime: %f ms\n",my_rank, elapsed);
	printf("---------------------------------------\n");

	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Reduce(&localsum,&globalsum,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);

	if (my_rank == 0){
		endTime = MPI_Wtime();
		elapsed =  (double)(endTime - startTime) * 1000.0;
		printf("Total Divisor Sum: %d\n", globalsum);
		printf("Entire Program Runtime: %f ms\n",elapsed);
		printf("---------------------------------------\n");
	}

	MPI_Finalize();
	return 0;
}
