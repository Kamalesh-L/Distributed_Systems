#include <mpi.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank, sum;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Reduce(&rank, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
        printf("Sum = %d\n", sum);

    MPI_Finalize();
    return 0;
}