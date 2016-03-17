/*
Parallel Programming
By : Abdallah Okasha
FCI-CU
*/
#include <stdio.h>
#include <string.h>
#include "mpi.h"

int main(int argc , char * argv[])
{
	int my_rank;	/* rank of process	*/
	int p;			/* number of process	*/
	int source;		/* rank of sender	*/
	int dest;		/* rank of reciever	*/
	int tag = 0;		/* tag for messages	*/
	char input_str[100];	/* storage for message	*/
	MPI_Status status;	/* return status for 	*/
						/* recieve		*/

	/* Start up MPI */
	MPI_Init( &argc , &argv );

	/* Find out process rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	/* Find out number of process */
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	if( my_rank != 0)
	{
		/* create message */
		dest = 0;
		int myPortion;
		MPI_Recv(&myPortion, 1, MPI_INT, dest, tag, MPI_COMM_WORLD, &status);
		MPI_Recv(input_str, myPortion, MPI_CHAR, dest, tag, MPI_COMM_WORLD, &status);
		int i;
		for(i=0; i<myPortion; i++)
			input_str[i] = toupper(input_str[i]);
		MPI_Send( input_str, myPortion, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
	}else
	{
		printf("Enter a string: ");
		scanf("%s", input_str);
		int length = strlen(input_str);
		int portion = length/(p-1);
		int currentPosition = 0;
		printf("Sending portions to slave processes ...");
		for( source = 1; source < p ; source++)
		{
			MPI_Send(&portion, 1, MPI_INT, source, tag, MPI_COMM_WORLD);
			MPI_Send(input_str+currentPosition, portion, MPI_CHAR, source, tag, MPI_COMM_WORLD);
			printf("\n\tProcess%d will convert chars [%d-%d]" , source, currentPosition, currentPosition+portion-1);
			currentPosition += portion;
		}
		
		printf("\n\nReceiving converted portions from slave processes ...");
		currentPosition = 0;
		for( source = 1; source < p ; source++)
		{
			MPI_Recv(input_str+currentPosition, portion, MPI_CHAR, source, tag, MPI_COMM_WORLD, &status);
			printf("\n\tProcess%d converted chars [%d-%d]" , source, currentPosition, currentPosition+portion-1);
			currentPosition += portion;
		}
		printf("\nString after conversion: %s\n", input_str);
	}

	/* shutdown MPI */
	MPI_Finalize();
	return 0;
}
