//Boys girls coach unit 3 using MPI

#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Create groups for boys and girls
    int color = rank % 2; // 0 for boys, 1 for girls
    MPI_Comm comm_boys, comm_girls;
    MPI_Comm_split(MPI_COMM_WORLD, color, rank, &comm_boys);

    // Head coach (rank 0) communicates with all players
    if (rank == 0) {
        char message[] = "Good luck to all!";
        MPI_Bcast(message, sizeof(message), MPI_CHAR, 0, MPI_COMM_WORLD);
        printf("Head Coach: Message sent to all players.\n");
    } else {
        char message[100];
        MPI_Bcast(message, 100, MPI_CHAR, 0, MPI_COMM_WORLD);
        printf("Player %d: Received message from coach: %s\n", rank, message);
    }

    // Head coach communicates with boys
    if (rank == 0) {
        char message[] = "Boys, focus on defense!";
        MPI_Bcast(message, sizeof(message), MPI_CHAR, 0, comm_boys);
        printf("Head Coach: Message sent to boys.\n");
    } else if (color == 0) { // Only boys receive this message
        char message[100];
        MPI_Bcast(message, 100, MPI_CHAR, 0, comm_boys);
        printf("Boy %d: Received message from coach: %s\n", rank, message);
    }

    // Head coach communicates with girls
    if (rank == 0) {
        char message[] = "Girls, work on your serve!";
        MPI_Bcast(message, sizeof(message), MPI_CHAR, 0, comm_girls);
        printf("Head Coach: Message sent to girls.\n");
    } else if (color == 1) { // Only girls receive this message
        char message[100];
        MPI_Bcast(message, 100, MPI_CHAR, 0, comm_girls);
        printf("Girl %d: Received message from coach: %s\n", rank, message);
    }

    MPI_Finalize();
    return 0;
}
