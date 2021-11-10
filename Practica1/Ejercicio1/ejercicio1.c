#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv){
    int size;
    int rank;
    double start, finish, time;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Barrier(MPI_COMM_WORLD);
    start = MPI_Wtime();
    printf("Hola mundo, soy el proceso %d de un total %d.\n", rank, size);
    MPI_Barrier(MPI_COMM_WORLD);
    finish = MPI_Wtime();
    time = finish - start;
    printf("Tiempo de %d: %f\n", rank, time);

    MPI_Finalize();

    return 0;
}