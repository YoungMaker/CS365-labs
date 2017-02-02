#include <stdio.h>
#include <math.h>
#include <mpi.h>
#include <unistd.h> 

double f(double x);

int main(int argc, char **argv)
{
	MPI_Init(&argc, &argv);

	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	double xmin, xmax;
	int nrects;

	if (rank == 0) {
		printf("xmin: ");
		fflush(stdout);
		scanf("%lf", &xmin);
	
		printf("xmax: ");
		fflush(stdout);
		scanf("%lf", &xmax);
	
		printf("nrects: ");
		fflush(stdout);
		scanf("%i", &nrects);
	}

	// Broadcast input values
	MPI_Bcast(&xmin, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD); //broadcast min/max
	MPI_Bcast(&xmax, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	
	MPI_Bcast(&nrects, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD); //broadcast nrects

	// Divide up work
	int group_size = nrects/size; // size of rectangle group
	int start = rank*group_size; //start of local rectangle group
	if(rank == (size-1)) {
		group_size += group_size % size;
	}
	int end = start + group_size; 



	// Local computation
	double total, interval, dx, midpoint, x, x_2;
    interval = (xmax - xmin);
    dx = interval/nrects;
    total = 0;

    int i=0;
    if(rank != 0) {
        i = start+1;
    }

    usleep((rank*100));
    printf("proc %i, comp_start %i, comp_end %i\n", rank, i, end);
    fflush(stdout);
    
    for(i; i<= end; i++) {
        x = dx*i;
        x_2 = x + dx;
        midpoint = (x_2 + x) / 2;
        total += f(midpoint) * dx;
    }
    usleep((rank*100));
    //printf("proc %i local sum = %lf\n", rank, total);
    //fflush(stdout);

	// Reduce local partial results to produce one global result
    double global_sum = 0;
	MPI_Reduce(&total, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

	// Print the global result (process 0 only)
	if(rank == 0) {
        printf("Area Estimate = %lf\n", global_sum);
        fflush(stdout);
    }

	MPI_Finalize();

	return 0;
}

double f(double x) {
	return (sin(x) + (pow(x, 1.3)*cos(x)) + (x*log(x)));
}
