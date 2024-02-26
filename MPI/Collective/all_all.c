#include <mpi.h>
#include <stdio.h>

#define N 4

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank, sendbuf[N], recvbuf[N];
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    for (int i = 0; i < N; i++) {
        sendbuf[i] = rank;
        printf("Process %d initialized sendbuf[%d] = %d\n", rank, i, sendbuf[i]);
    }

    MPI_Alltoall(sendbuf, 1, MPI_INT, recvbuf, 1, MPI_INT, MPI_COMM_WORLD);

    printf("Process %d received: ", rank);
    for (int i = 0; i < N; i++)
        printf("%d ", recvbuf[i]);
    printf("\n");

    MPI_Finalize();
    return 0;
}