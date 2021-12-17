#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){

    int rank;
    int size;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int send[4];
    int recv[4];

    if(size == 4){
        for(int i = 0; i < size; i++){
            send[i] = i;
        }

        printf("The process %d send %d %d %d %d\n", rank, send[0], send[1], send[2], send[3]);
        MPI_Alltoall(&send, 1, MPI_INT, &recv, 1, MPI_INT, MPI_COMM_WORLD);
        printf("After transposition the process %d recive %d %d %d %d\n", rank, recv[0], recv[1], recv[2], recv[3]);
    }

    MPI_Finalize();
}