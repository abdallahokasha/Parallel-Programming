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
	int my_rank;		/* rank of process	*/
	int p;			/* number of process	*/
	int dest;		/* rank of reciever	*/
	int tag = 0;		/* tag for messages	*/
	char message[100];	/* storage for message	*/
	MPI_Status status;	/* return status for 	*/
				/* recieve		*/
	int num = 5;
	/* Start up MPI */
	MPI_Init( &argc , &argv );

	/* Find out process rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	/* Find out number of process */
	MPI_Comm_size(MPI_COMM_WORLD, &p);
    
	int i, j, array_size;
	printf ("Enter ur msg size \n");
	scanf("%d", &array_size);
	char *input_array = malloc( sizeof(char) * array_size);
	
	if( my_rank == 0)
	{
		fsor( dest = 1; dest < p ; dest++)
		{
		    /*process 0 send 5 to all other processes*/
		    MPI_Send( &num, array_size, MPI_INT, dest, tag, MPI_COMM_WORLD);
		    printf("send to %d\n",dest);
		}
		
		for( dest = 1; dest < p ; dest++)
		{
		    /*process 0 receives num from all other processes */
			MPI_Recv(&input_array , array_size, MPI_CHAR, dest, tag, MPI_COMM_WORLD, &status );
			printf("process number %d sent %d\n" , dest , input_array);
		}
	}
	else
	{
		    /*other processes receive 5 and add it's rank to it*/
			MPI_Recv(&input_array, array_size, MPI_CHAR, 0, tag, MPI_COMM_WORLD, &status );
	  		//printf("%d is received\n" ,  source);
		    //num = num + my_rank;
			/*other processes send the result to process 0*/
			MPI_Send( &input_array, array_size, MPI_CHAR, 0, tag, MPI_COMM_WORLD);
			for(i = 0; i < 10000000; i++)
			printf("Hi\n");
	}

	/* shutdown MPI */
	MPI_Finalize();
	return 0;
}
