// mpi probing example
#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(NULL, NULL);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    if (world_rank == 0) {
        int number = 100;
        MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    } else if (world_rank == 1) {
        MPI_Status status;
        MPI_Probe(0, 0, MPI_COMM_WORLD, &status);

        int number_of_integers;
        MPI_Get_count(&status, MPI_INT, &number_of_integers);

        int* buf = (int*)malloc(sizeof(int) * number_of_integers);

        MPI_Recv(buf, number_of_integers, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("Process 1 received %d integers from process 0.\n", number_of_integers);

        free(buf);
    }

    MPI_Finalize();
    return 0;
}