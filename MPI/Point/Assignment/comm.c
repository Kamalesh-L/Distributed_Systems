// communication between two processes

#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(NULL, NULL);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int number;
    MPI_Request request;

    if (world_rank == 0) {
        number = 100; // or any other integer
        MPI_Isend(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &request);
        int number_received;
        MPI_Irecv(&number_received, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &request);
        MPI_Wait(&request, MPI_STATUS_IGNORE);
        printf("Process 0 received number %d from process 1\n", number_received);
        printf("Sum of the two values: %d\n", number + number_received);
    } else if (world_rank == 1) {
        int number_received;
        MPI_Irecv(&number_received, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &request);
        MPI_Wait(&request, MPI_STATUS_IGNORE);
        number = 200; // or any other integer
        MPI_Isend(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &request);
        printf("Process 1 received number %d from process 0\n", number_received);
        printf("Product of the two values: %d\n", number * number_received);
    }

    MPI_Finalize();
    return 0;
}