#include <mpi.h>
#include <stdio.h>

#define N 4
int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank, sendbuf[N], recvbuf, resultbuf[N];
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        for (int i = 0; i < N; i++) {
            sendbuf[i] = i;
            printf("Process 0 initialized sendbuf[%d] = %d\n", i, sendbuf[i]);
        }
    }

    MPI_Scatter(sendbuf, 1, MPI_INT, &recvbuf, 1, MPI_INT, 0, MPI_COMM_WORLD);

    printf("Process %d received %d from root process\n", rank, recvbuf);

    recvbuf *= rank;

    printf("Process %d multiplied received value by rank, new value is %d\n", rank, recvbuf);

    MPI_Gather(&recvbuf, 1, MPI_INT, resultbuf, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Process 0 gathered results: ");
        for (int i = 0; i < N; i++)
            printf("%d ", resultbuf[i]);
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}


