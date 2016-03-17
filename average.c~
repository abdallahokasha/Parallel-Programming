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
	int my_rank;		 /* rank of process	*/
	int p;			    /* number of process */
	int source = 0;	   /* rank of sender */
	int des;		  /* rank of reciever */
	int tag = 0;	 /* tag for messages */		
	
	/* storage for message	*/
	int index = 0;
	int j,i;
	int size;
	float sumAvg = 0;
	
	int inputArraySize = 0; /* the size of input array */
	
	MPI_Status status;	/* return status for 	*/
				/* recieve		*/

	/* Start up MPI */
	MPI_Init( &argc , &argv );

	/* Find out process rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	/* Find out number of process */
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	
        /*the size of sub array for each process*/
	size = inputArraySize / (p - 1);
	
	/* main (source) process */
	if ( my_rank == 0)
	{
		printf("Enter Array Size: \n");
		scanf("%d", &inputArraySize);
	
		float *inputArray = (float*)malloc( sizeof(float) * inputArraySize); /* the size of input array */
		printf("Enter Array: \n");
		for (i = 0; i < inputArraySize; ++i){
                 scanf("%f", &inputArray[i]);}
		size = inputArraySize / (p - 1);
		/* loop for sending to all other processes */
		for( des = 1; des < p ; des++)
		{   
		
		    if(des == p - 1){
			   /*the last process takes the rest of the array*/
			   size = size + (inputArraySize % (p - 1));				
			}
			
			/*source sends the size of the array to each process*/
			MPI_Send( &size, 1, MPI_INT, des, tag, MPI_COMM_WORLD);
			
			/*source sends the (sub)array to each process*/
			MPI_Send(inputArray + index, size, MPI_FLOAT, des, tag, MPI_COMM_WORLD);		
			/* Send the original (total) size of array */
                        MPI_Send(&inputArraySize, 1, MPI_INT, des, tag, MPI_COMM_WORLD);		
			
			index += size;
		}
		
		size = inputArraySize / (p - 1);
		index = 0;
		printf("===============================================================\n");
		
		/* loop for receiving to all other processes */
		for( des = 1; des < p ; des++)
		{   
		   	
		    if(des == p - 1){
			   size = size + (inputArraySize % (p - 1));				
			}
			
			//float *receivedArray = malloc( sizeof(float) * size);
			float recvAvg;
			
			/*source receives the sum from each process*/
                        MPI_Recv(&recvAvg, 1 , MPI_FLOAT, des, tag, MPI_COMM_WORLD, &status );
		    
			printf("the received average: %f\n", recvAvg);
		       /* sum of received averages */	
                       sumAvg += recvAvg;
		}
		printf("===============================================================\n");
		printf("the average of array = %f\n" , sumAvg);
	}
	/* all processes except main (source) process */
	else if( my_rank != 0)
	{
	        int processSize;
		
		/*each process receives the array size*/
	        MPI_Recv(&processSize, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &status );
		
		float *processArray = (float*)malloc( sizeof(float) * processSize);
		/*each process receives the array(sub)*/
		MPI_Recv(processArray, processSize , MPI_FLOAT, source, tag, MPI_COMM_WORLD, &status );
		
                /* Receive the original (total) size of array */
                MPI_Recv(&inputArraySize, 1 , MPI_INT, source, tag, MPI_COMM_WORLD, &status );
		
                float sum = 0;
		printf("received array: ");
                for(j = 0; j < processSize; j++){
		/* each process calculates sum of it's sub array */
		  sum += processArray[j] ;
                  printf("%f ", processArray[j]);
		}
                printf("\n");

		/* get average by dividing by the size of the input array */
		sum /= inputArraySize;//sum /= 5;
		printf ("SubAvg :%f", sum);
                printf("\n");
		/*each process sends the average of received array*/
		MPI_Send(&sum, 1, MPI_FLOAT, source, tag, MPI_COMM_WORLD);		
	}

	/* shutdown MPI */
	MPI_Finalize();
	return 0;
}
