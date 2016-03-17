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
	int source = 0;		/* rank of sender	*/
	int des;		/* rank of reciever	*/
	int tag = 0;		/* tag for messages	*/
	int index = 0;
	int num,i,cnt = 0,global,first,last, limit;
	
	MPI_Status status;	/* return status for 	*/
				/* recieve		*/

	/* Start up MPI */
	MPI_Init( &argc , &argv );

	/* Find out process rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	/* Find out number of process */
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	
	if(my_rank == 0)
	{
		printf("Enter a num: \n");
		scanf("%d",&num);
                printf ("Enter ur limit num:\n");
                scanf("%d",&limit);
	}
	
	/* send number from process 0 to each process and each process sends this number to other processes and so on */
	MPI_Bcast(&num, 1, MPI_INT, 0, MPI_COMM_WORLD);

	/* the beginning of the range */
	first = (my_rank * limit) / p;
	/* the end of the range */
	last = ( (my_rank + 1) * limit) / p;
	
	/* calculate factorial */
	for(i = first + 1 ; i <= last; i++)
		factorial *= i;

	/* but factoral into a golbal variable which only the root can see */ 
	MPI_Reduce(&factorial, &global, 1, MPI_INT, MPI_PROD, 0, MPI_COMM_WORLD);

	if(my_rank == 0)
		printf("\nFactorial %d is %d\n", num, global);

	/* shutdown MPI */
	MPI_Finalize();
	return 0;
}
