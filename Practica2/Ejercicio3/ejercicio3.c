#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int main(int argc, char **argv){
    int rank, count;

    MPI_Status status;
    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &count);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    float arrayA[1000];
    float arrayB[1000];

    for(int i = 0; i < 1000; i++){
        arrayA[i] = rank;
    }

    MPI_Send(arrayA, 1000, MPI_FLOAT, (rank + 1) % count, 0, MPI_COMM_WORLD);
    printf("I am the process %d I send %f to the process %d\n", rank, arrayA[rand() % 1001], (rank + 1) % count);
    MPI_Recv(arrayB, 1000, MPI_FLOAT, (rank - 1 + count) % count, 0, MPI_COMM_WORLD, &status);
    printf("I am the process %d I recived %f from process %d\n", rank, arrayB[rand() % 1001], (rank - 1 + count) % count);

    MPI_Finalize();
}