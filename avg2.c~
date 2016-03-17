/*
Parallel Programming
By : Abdallah Okasha
FCI-CU
*/
#include <stdio.h>
#include <string.h>
#include "mpi.h"

int main(int argc, char * argv[]) {

	int my_rank, p, des, source = 0, tag = 0, size;
	int i, j, k, subSize, subSum = 0, totalSum = 0, global = 0;
	int *sumsArray, *inputArray, *subArray;

	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	if (my_rank == 0) {
		printf("Enter your array size:\n");
		scanf("%d", &size);

		inputArray = malloc(sizeof(int) * size);
		printf("ENter array numbers:\n");
		for (i = 0; i < size; ++i) {
			scanf("%d", &inputArray[i]);
		}
		subSize = size / p;
		sumsArray = malloc(sizeof(int) * p);
	}
	MPI_Bcast(&subSize, 1, MPI_INT, 0, MPI_COMM_WORLD);

	subArray = malloc(sizeof(int) * subSize);
	MPI_Scatter(inputArray, subSize, MPI_INT, subArray, subSize, MPI_INT,
			source, MPI_COMM_WORLD);

	for (i = 0; i < subSize; ++i){
		subSum += subArray[i];
       printf("sub array %d ", subArray[i]);
         }
          
          printf("\n");
	MPI_Reduce(&subSum, &totalSum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	if (my_rank == 0) {
                   for (i = p * subSize; i < size; ++i)
			totalSum += inputArray[i];

		printf("Summation of all numbers in array = %d \n", totalSum);
	}
	MPI_Finalize();

	return 0;
}
