#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv){
    int rank = 0;
    int value = 8;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    for(int i=0; i<2; i++){
        if(rank==0){
            
            MPI_Send(&value, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
            printf("I am master %d. Sending message %d.\n", rank, value);

            MPI_Recv(&value, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("I am the master %d. Reciving the message %d.\n", rank, value);
            
        }else{
            
            MPI_Recv(&value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("I am the slave %d. Reciving message %d.\n", rank, value);
            
            MPI_Send(&value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
            printf("I am the slave %d. Sending message %d.\n", rank, value);
            
        }
    }    
    MPI_Finalize();
    return 0;
}