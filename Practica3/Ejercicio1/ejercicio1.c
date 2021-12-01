#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv){
    int rank, size, value;

    MPI_Status status;
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int num = 8;
    int cuadrado = num * num;

    if(rank == 0){
        //comunicacion punto a punto
        for(int i = 1; i < size; i++){
            MPI_Send(&cuadrado, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
        printf("Process %d has send his squaring %d to the rest of the process\n", rank, cuadrado);

    }else{
        MPI_Recv(&cuadrado, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        printf("I am the process %d I recive the squaring %d from the master process\n", rank, cuadrado);
    }
    if(rank == 0){
        //comunicacion colectiva
        MPI_Bcast(&cuadrado, 1, MPI_INT, 0, MPI_COMM_WORLD);
        printf("Process %d has send his squaring %d to the rest of the process (collective comunication)\n", rank, cuadrado);
    }else{
        printf("I am the process %d I recive the squaring %d from the master of collective comunication\n", rank, cuadrado);
    }
    MPI_Finalize();
}