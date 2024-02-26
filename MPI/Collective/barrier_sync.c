#include <mpi.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    sleep(rank);
    printf("Process %d finished work\n", rank);

    MPI_Barrier(MPI_COMM_WORLD);

    if (rank == 0)
        printf("All processes finished\n");

    MPI_Finalize();
    return 0;
}