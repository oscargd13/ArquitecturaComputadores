#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv){
    int rank;
    int size;
    int value = 8;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank == 0){
        printf("EL proceso %d tiene el valor %d y se lo va a mandar a %d \n", rank, value, rank+1);
        MPI_Send(&value, 1, MPI_INT, rank+1, 0, MPI_COMM_WORLD);
    }else{
        MPI_Recv(&value, 1, MPI_INT, rank-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        if(rank+1 < size){
            MPI_Send(&value, 1, MPI_INT, rank+1, 0, MPI_COMM_WORLD);
        }
        printf("El proceso %d ha recivido el valor %d del proceso %d \n", rank, value, rank-1);
    }
    MPI_Finalize();
    return 0;
}