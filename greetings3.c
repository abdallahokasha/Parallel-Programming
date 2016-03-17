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
	char message[9] = "haitham";	/* storage for message	*/
	int index = 0;
	int j,i;
	int size;
	
	MPI_Status status;	/* return status for 	*/
				/* recieve		*/

	/* Start up MPI */
	MPI_Init( &argc , &argv );

	/* Find out process rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	/* Find out number of process */
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	
    /*the size of message for each process*/
	size = strlen(message) / (p - 1);
	
	if( my_rank != 0)
	{
	    int processSize;
		
		/*each process receives the message size*/
	    MPI_Recv(&processSize, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &status );
		
		char *processMassage = malloc( sizeof(char) * processSize);
		
		/*each process receives the message*/
		MPI_Recv(processMassage, processSize , MPI_CHAR, source, tag, MPI_COMM_WORLD, &status );
		
		for(j = 0; j < processSize; j++){
		
		/*each process converts the message to upper case*/
		  processMassage[j] = toupper(processMassage[j]);
		}
		
		/*each process sends the upper case message back to the source*/
		MPI_Send( processMassage, processSize, MPI_CHAR, source, tag, MPI_COMM_WORLD);	
		
	}else
	{
	    
		for( des = 1; des < p ; des++)
		{   
		
		    if(des == p - 1){
			
			   /*the last process takes the rest of the message*/
			   size = size + (strlen(message) % (p - 1));				
			}
			
			/*source sends the size of the message to each process*/
			MPI_Send( &size, 1, MPI_INT, des, tag, MPI_COMM_WORLD);
			
			/*source sends the message to each process*/
			MPI_Send(message + index, size, MPI_CHAR, des, tag, MPI_COMM_WORLD);
			printf("send message with lenght = %d and message = %.*s to process = %d\n",size, size, message + index, des);
			
			index += size;
		}
		
		size = strlen(message) / (p - 1);
		index = 0;
		printf("-----------------------------------------------------------------------\n");
		
		for( des = 1; des < p ; des++)
		{   
		   	
		    if(des == p - 1){
			   
			   size = size + (strlen(message) % (p - 1));				
			}
			
			char *receivedMessage = malloc( sizeof(char) * size);
			
			/*source receives the upper case message from each process*/
            MPI_Recv(receivedMessage, size , MPI_CHAR, des, tag, MPI_COMM_WORLD, &status );
		    printf("received message = %s from process = %d\n" , receivedMessage , des);
				
			for(j = index , i = 0; j < size + index; j++, i++){
			
		      /*source changes the lower case message to the upper case message*/
		      message[j] = receivedMessage[i];
		    }

			index += size;
		}
		printf("-----------------------------------------------------------------------\n");
		printf("the final received message = %s\n" , message);
	}

	/* shutdown MPI */
	MPI_Finalize();
	return 0;
}
