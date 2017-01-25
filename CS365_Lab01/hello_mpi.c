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


	MPI_Finalize();

	return 0;
}

