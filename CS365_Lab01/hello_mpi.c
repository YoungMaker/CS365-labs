// CS 365 - Lab 1

#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char **argv)
{
	// TODO: add your code here
	MPI_Init(&argc, &argv);

	int rank;
	int max_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &max_rank);
	
	printf("Hello from process %i\n", rank);

	int n = 0;

	if(rank == 0) {
		printf("Enter a positive integer:\n ");
		fflush(stdout);
		scanf("%i", &n);
		for(int i=1; i< max_rank; i++) {
			MPI_Send(&n, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
		}
	}
	else{
		MPI_Recv(&n, 1, MPI_INT, 0, 0,  MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}
	

	

	int chunk_size = (n / max_rank);
	int start_count = rank * chunk_size;
	if(rank == (max_rank-1)) {
		chunk_size += (n % max_rank);
	}	
	int end_count = start_count + chunk_size;
	
	printf("proc %i, start %i, end %i\n", rank, start_count, end_count);
	fflush(stdout);	

	int counter = 0;
	for(int i=start_count+1; i<=end_count; i++) {
		counter+= i;
	}
	
	if(rank == 0) { //recive all of the final calculations
		int global_sum = counter;
		int recv;
		for(int i=1; i< max_rank; i++) {
			MPI_Recv(&recv, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			global_sum+= recv;
		}
		printf("Global Sum = %i\n", global_sum);
		fflush(stdout);
	}
	else {
		printf("proc %i, local sum = %i\n", rank, counter);
		fflush(stdout);
		MPI_Send(&counter, 1, MPI_INT, 0,0, MPI_COMM_WORLD);
	}

	MPI_Finalize();
	

	return 0;
}

