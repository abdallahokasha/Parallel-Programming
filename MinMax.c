/*
Parallel Programming
By : Abdallah Okasha
FCI-CU
*/
#include <stdio.h>
#include <string.h>
#include "mpi.h"

int main(int argc, char * argv[]) {
	int my_rank; /* rank of process	*/
	int p; /* number of process	*/
	int dest; /* rank of reciever	*/
	int tag = 0; /* tag for messages	*/
	MPI_Status status; /* return status for 	*/
	/* recieve		*/
	int size;
	int i, j, k;
	int min = 100000000;
	int max = -10000000;
	int index = 0;
        int fmin = 100000000, fmax = -10000000;
	/* Start up MPI */
	MPI_Init(&argc, &argv);

	/* Find out process rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	/* Find out number of process */
	MPI_Comm_size(MPI_COMM_WORLD, &p);
        int *inputArray = (int *) malloc(sizeof(int) * 100);
	if (my_rank == 0) {
		int min = 100000000;
		int max = -100000000;
		printf("Enter ur Array size :\n");
		int arraySize;
		scanf("%d", &arraySize);
		int *inputArray = (int *) malloc(sizeof(int) * arraySize);
		printf("Enter ur array elements:\n");
		for (i = 0; i < arraySize; i++)
			scanf("%d", &inputArray[i]);

		 size = arraySize / (p - 1);

		for (dest = 1; dest < p; dest++) {
			if (dest == p - 1) {
				size = size + (arraySize % (p - 1));
			}
			MPI_Send(&size, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);

			int *processArray = (int *) malloc(sizeof(int) * size);
			for (i = index, j = 0; i < index + size; j++, i++)
				processArray[j] = inputArray[i];

			MPI_Send(processArray, size, MPI_INT, dest, tag, MPI_COMM_WORLD);
			MPI_Send(&min, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
			MPI_Send(&max, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);

			index += size;
		}
		int fmin = 100000000, fmax = -10000000;
		for (dest = 1; dest < p; dest++) {
			MPI_Recv(&min, 1, MPI_INT, dest, tag, MPI_COMM_WORLD, &status);
			MPI_Recv(&max, 1, MPI_INT, dest, tag, MPI_COMM_WORLD, &status);
			if (min < fmin)
				fmin = min;
			if (max > fmax)
				fmax = max;
		}
		printf("min Element of array: %d \n", fmin);
		printf("max Element of array: %d \n", fmax);

	} else if (my_rank != 0) {
    
		int processSize;
		MPI_Recv(&processSize, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);

		int *receivedArray = (int *) malloc(sizeof(int) * processSize);
		MPI_Recv(receivedArray, processSize, MPI_INT, 0, tag, MPI_COMM_WORLD,
				&status);
		MPI_Recv(&min, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
		MPI_Recv(&max, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);

		for (i = 0; i < processSize; i++) {
                 //printf("%d " , receivedArray[i]);
			if (receivedArray[i] < min)
				min = receivedArray[i];
			if (receivedArray[i] > max)
				max = receivedArray[i];
		}
                printf("\n");
		MPI_Send(&min, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
		MPI_Send(&max, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
	}
	/* shutdown MPI */
	MPI_Finalize();
	return 0;
}
