// status retrieves information about a message that has been sent or received.

#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(NULL, NULL);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int number;
    MPI_Request request;
    MPI_Status status;

    if (world_rank == 0) {
        number = 100; // or any other integer
        MPI_Isend(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &request);
        MPI_Wait(&request, &status);
        // You can now inspect the 'status' variable for information about the message
        printf("Process 0 sent number %d to process 1\n", number);
    } else if (world_rank == 1) {
        MPI_Irecv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &request);
        MPI_Wait(&request, &status);
        // You can now inspect the 'status' variable for information about the message
        int count;
        MPI_Get_count(&status, MPI_INT, &count);
        printf("Process 1 received number %d from process %d with tag %d\n", number, status.MPI_SOURCE, status.MPI_TAG);
    }

    MPI_Finalize();
    return 0;
}

