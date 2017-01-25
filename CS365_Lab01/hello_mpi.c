// CS 365 - Lab 1

#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char **argv)
{
	// TODO: add your code here
	MPI_Init(&argc, &argv);

	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	printf("Hello from process %i\n", rank);

	int n = 0;

	if(rank == 0) {
		printf("Enter a positive integer: ");
		fflush(stdout);
		scanf("%i", &n);
	}

	printf("n = %i", n);
    fflush(stdout);

	MPI_Finalize();

	return 0;
}

