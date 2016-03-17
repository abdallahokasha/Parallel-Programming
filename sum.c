#include <stdio.h>
#include <string.h>
#include "mpi.h"

int main(int argc , char * argv[])
{
	int my_rank;		/* rank of process	*/
	int p;			/* number of process	*/
	int source = 0;		/* rank of sender	*/
	int des;		/* rank of reciever	*/
	int tag = 0;		/* tag for messages	*/
	int numOfElements, size, *subArray, subSum = 0, totalSum = 0, *totalArray, *array,i;
	MPI_Status status;	/* return status for 	*/
				

	/* Start up MPI */
	MPI_Init( &argc , &argv );

	/* Find out process rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	/* Find out number of process */
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	
	if(my_rank == 0)
	{
		int input;
		
		printf("Enter the array size : ");
		scanf("%d", &size);
		array = malloc(size * sizeof(int));
		
		printf("Enter the array:\n");
		for(i = 0; i < size; i++){
			scanf("%d", &input);
			array[i] = input;
		}	
		
		numOfElements = size / p;
		totalArray = malloc(p * sizeof(int));
	}
	/*broadcast number of elements to each process */
	MPI_Bcast(&numOfElements, 1, MPI_INT, 0, MPI_COMM_WORLD);
	
	subArray = malloc(numOfElements * sizeof(int));
	/*send the first numOfElements from array to sybArray to process 0 and the second numOfElements to process 1 and so on */
	MPI_Scatter(array, numOfElements, MPI_INT, subArray, numOfElements, MPI_INT, source, MPI_COMM_WORLD);
	
	for(i = 0; i < numOfElements; i++)
		subSum += subArray[i];
	
	/*send the summation to the root and the root received all sums in total array */
	MPI_Gather (&subSum, 1, MPI_INT, totalArray, 1, MPI_INT, source, MPI_COMM_WORLD);

	if(my_rank == 0){
	
		for(i = 0;i < p;i++)
			totalSum += totalArray[i];
		
		for(i = p * numOfElements;i < size; i++)
			totalSum += array[i];
		
		printf("\ntotal sum = %d\n", totalSum);
	}
	/* shutdown MPI */
	MPI_Finalize();
	return 0;
}
