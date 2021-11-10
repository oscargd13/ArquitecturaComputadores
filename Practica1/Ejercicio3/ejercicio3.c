#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv){
    int rank;
    int size;
    int userValue = 7;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    for(int i=0; i < 2; i++){
        if(rank == 0){
            if(i == 0){
                printf("Al proceso %d le ha entrado el valor %d y lo va a mandar al proceso %d \n", rank, userValue, rank+1);
            }else{
                printf("El proceso %d ha recibido el valor %d del proceso %d \n", rank, userValue, size-1);
            }
            MPI_Send(&userValue, 1, MPI_INT, rank+1, 0, MPI_COMM_WORLD);
            MPI_Recv(&userValue, 1, MPI_INT, size-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }else{
            MPI_Recv(&userValue, 1, MPI_INT, rank-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            if(rank+1 < size){
                MPI_Send(&userValue, 1, MPI_INT, rank+1, 0, MPI_COMM_WORLD);
            }
            if(rank == size-1){
                MPI_Send(&userValue, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
            }
            printf("El proceso %d ha recibido el valor %d del proceso %d \n", rank, userValue, rank-1);
        }
    }
    MPI_Finalize();
    return 0;
}