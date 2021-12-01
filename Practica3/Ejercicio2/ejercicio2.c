#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
    int size, rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int array[4];
    int data;

    if(rank == 0){
        for(int i = 0; i < size; i++){
            array[i] = i;
        }
        printf("Process %d has data: ", rank);
        for(int i = 0; i < size; i++){
            printf("%d ", array[i]);
        }
        printf("\n");
    }

    MPI_Scatter(array, 1, MPI_INT, &data, 1, MPI_INT, 0, MPI_COMM_WORLD);

    data = data + rank;
    printf("Process %d has data: %d\n", rank, data);
    
    MPI_Gather(&data, 1, MPI_INT, array, 1, MPI_INT, 0, MPI_COMM_WORLD);

    //ROOT
    if(rank == 0){
        printf("Process %d has data: ", rank);
        for(int i = 0; i < size; i++){
            printf("%d ", array[i]);
        }
        printf("\n");
    }
    MPI_Finalize();
}