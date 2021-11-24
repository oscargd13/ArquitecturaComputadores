#include<stdio.h>
#include<mpi.h>
#include <stdlib.h>

int main(int argc, char **argv){
    int rank, count, size;
    
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    if(rank == 0){
        float a[10000], b[10000];
        for(int i = 0; i < 10000; i++){
            a[i] = rank;
        }
        MPI_Send(a, 10000, MPI_FLOAT, 1, 22, MPI_COMM_WORLD);
        MPI_Recv(b, 10000, MPI_FLOAT, 1, 22, MPI_COMM_WORLD, &status);
        printf("Process %d:\nValue from random index of array B: %lf\n\n", rank, b[rand() % 10001]);
    }else{
        float a[10000], b[10000];
        for(int i = 0; i < 10000; i++){
            a[i] = rank;
        }
        MPI_Recv(b, 10000, MPI_FLOAT, 0, 22, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_CHAR, &count);
        MPI_Send(a, 10000, MPI_FLOAT, 0, 22, MPI_COMM_WORLD);
        printf("Process %d:\nValue from random index of array B: %lf\n\n", rank, b[rand() % 10001]);
    }
    MPI_Finalize();
    return 0;
}