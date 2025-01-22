//sum of array unit 3
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 100

int main(int argc, char** argv) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Calculate the size of the local subarray for each process
    int local_size = ARRAY_SIZE / size; 
    float* local_data = (float*)malloc(local_size * sizeof(float)); 

    // Initialize local data (replace with your actual data source)
    for (int i = 0; i < local_size; ++i) {
        local_data[i] = rank + i * size; // Example initialization
    }

    // Calculate the local sum
    float local_sum = 0.0;
    for (int i = 0; i < local_size; ++i) {
        local_sum += local_data[i];
    }

    // Reduce local sums to get the global sum
    float global_sum;
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Print the global sum (only by the root process)
    if (rank == 0) {
        printf("Sum of all elements: %f\n", global_sum);
    }

    free(local_data);
    MPI_Finalize();

    return 0;
}
