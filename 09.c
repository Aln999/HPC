#include <stdio.h> 
#include <mpi.h> 
int main(int argc, char* argv[]) { 
int rank, size, data = 100; 
MPI_Request req; 
MPI_Status status; 
double start_time, end_time, block_time, nonblock_time; 
MPI_Init(&argc, &argv); 
MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
MPI_Comm_size(MPI_COMM_WORLD, &size); 
if (rank == 0) { 
        // Blocking Send 
        start_time = MPI_Wtime(); 
        MPI_Send(&data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD); 
        block_time = MPI_Wtime() - start_time; 
 
        // Non-blocking Send 
        start_time = MPI_Wtime(); 
        MPI_Isend(&data, 1, MPI_INT, 1, 1, MPI_COMM_WORLD, &req); 
        MPI_Wait(&req, &status); 
        nonblock_time = MPI_Wtime() - start_time; 
 
        printf("Time taken by blocking send: %f\n", block_time); 
        printf("Time taken by nonblocking send: %f\n", nonblock_time); 
    }  
    else if (rank == 1) { 
        // Blocking Receive 
        start_time = MPI_Wtime(); 
        MPI_Recv(&data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status); 
        block_time = MPI_Wtime() - start_time; 
 
        // Non-blocking Receive 
        start_time = MPI_Wtime(); 
        MPI_Irecv(&data, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &req); 
        MPI_Wait(&req, &status); 
        nonblock_time = MPI_Wtime() - start_time; 
 
        printf("Time taken by blocking receive: %f\n", block_time); 
        printf("Time taken by nonblocking receive: %f\n", nonblock_time); 
    } 
 
    MPI_Finalize(); 
    return 0; 
}