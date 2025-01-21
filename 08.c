#include <stdio.h> 
#include <mpi.h> 
int main(int argc, char* argv[]) { 
    int rank, size, dims[2] = {0, 0}, periods[2] = {1, 1}, coords[2]; 
    MPI_Comm cart_comm; 
    MPI_Init(&argc, &argv); 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &size); 
    MPI_Dims_create(size, 2, dims); 
    MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, 1, &cart_comm); 
    MPI_Cart_coords(cart_comm, rank, 2, coords); 
    printf("Rank %d coordinates: (%d, %d)\n", rank, coords[0], coords[1]); 
    MPI_Finalize(); 
    return 0; 
}