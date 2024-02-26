// Sending an array of integers from one process to another:

#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(NULL, NULL);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int numbers[10];
    if (world_rank == 0) {
        for (int i = 0; i < 10; i++) {
            numbers[i] = i;
        }
        MPI_Send(numbers, 10, MPI_INT, 1, 0, MPI_COMM_WORLD);
    } else if (world_rank == 1) {
        MPI_Recv(numbers, 10, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 1 received numbers from process 0: ");
        for (int i = 0; i < 10; i++) {
            printf("%d ", numbers[i]);
        }
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}