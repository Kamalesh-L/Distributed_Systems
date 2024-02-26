#include <mpi.h>
#include <stdio.h>

#define N 4

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int matrix[N][N];
    if (rank == 0) {
        // Initialize matrix
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                matrix[i][j] = i * N + j;
    }

    MPI_Bcast(matrix, N*N, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank != 0) {
        printf("Process %d received matrix:\n", rank);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++)
                printf("%d ", matrix[i][j]);
            printf("\n");
        }
    }

    MPI_Finalize();
    return 0;
}