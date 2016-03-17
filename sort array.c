#include <stdio.h>
#include <string.h>
#include "mpi.h"

int main(int argc, char * argv[]) {
	int my_rank; /* rank of process	*/
	int p; /* number of process	*/
	int dest; /* rank of reciever	*/
	int tag = 0; /* tag for messages	*/
	MPI_Status status; /* return status for 	*/

	int i, k, j, size, index;
	/* Start up MPI */
	MPI_Init(&argc, &argv);

	/* Find out process rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	/* Find out number of process */
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	if (my_rank == 0) {
		printf("Enter array size:\n");
		int arraySize;
		scanf("%d", &arraySize);
		printf("Enter array Elements:\n");
		int *arrayInput = (int *) malloc(sizeof(int) * arraySize);
		for (i = 0; i < arraySize; i++) {
			scanf("%d", &arrayInput[i]);
		}
		index = 0;
		size = arraySize / (p - 1);
		for (dest = 1; dest < p; dest++) {
			if (dest == p - 1) {
				size = size + (arraySize % (p - 1));
			}
			//printf("subArray:\n");
			MPI_Send(&size, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
			int *processArray = (int *) malloc(sizeof(int) * size);
			for (i = index, j = 0; i < index + size; i++, j++) {
				processArray[j] = arrayInput[i];
				//printf ("%d ", processArray[j]);
			}
			//printf("\n");
			MPI_Send(processArray, size, MPI_INT, dest, tag, MPI_COMM_WORLD);

			index += size;
		}
		index = 0;
		size = arraySize / (p - 1);
		int *arrays = (int *) malloc(sizeof(int) * arraySize);
		for (dest = 1; dest < p; dest++) {
			if (dest == p - 1) {
				size = size + (arraySize % (p - 1));
			}
			int *sortArray = (int *) malloc(sizeof(int) * size);
			MPI_Recv(sortArray, size, MPI_INT, dest, tag, MPI_COMM_WORLD,
					&status);
			printf("sorted array: \n");

			for (j = 0, k = index; j < size; j++, k++) {
				printf("%d ", sortArray[j]);
				arrays[k] = sortArray[j];
			}
			printf("\n");
			index += size;
		}
		printf("merged sub arrays:\n");
		for (i = 0; i < arraySize; i++) {
			printf("%d ", arrays[i]);
		}
		printf("\n");
		int flag = 0;
		while (!flag) {
			flag = 1;
			for (i = 0; i < arraySize - 1; i++) {
				if (arrays[i] > arrays[i + 1]) {
					int tmp;
					tmp = arrays[i + 1];
					arrays[i + 1] = arrays[i];
					arrays[i] = tmp;
					flag = 0;
				}
			}
		}
		printf("final sorted array:\n");
		for (i = 0; i < arraySize; i++) {
			printf("%d ", arrays[i]);
		}
		printf("\n");
	} else if (my_rank != 0) {
		int recvSize;
		MPI_Recv(&recvSize, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
		int *recvArray = (int *) malloc(sizeof(int) * recvSize);
		MPI_Recv(recvArray, recvSize, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
		int flag = 0;
		while (!flag) {
			flag = 1;
			for (i = 0; i < recvSize - 1; i++) {
				if (recvArray[i] > recvArray[i + 1]) {
					int tmp;
					tmp = recvArray[i + 1];
					recvArray[i + 1] = recvArray[i];
					recvArray[i] = tmp;
					flag = 0;
				}
			}
		}
		MPI_Send(recvArray, recvSize, MPI_INT, 0, tag, MPI_COMM_WORLD);
	}
	/* shutdown MPI */
	MPI_Finalize();
	return 0;
}
