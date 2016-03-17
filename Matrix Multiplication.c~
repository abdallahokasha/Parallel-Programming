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
	/* Start up MPI */
	int r1, c1, r2, c2, i, j, k, x, y, index, size;
	MPI_Init(&argc, &argv);

	/* Find out process rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	/* Find out number of process */
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	if (my_rank == 0) {

		/* Read input */
		printf("Please enter the dimensions of the first matrix\n");
		scanf("%d %d", &r1, &c1);
		printf("Please enter the dimensions of the second matrix\n");
		scanf("%d %d", &r2, &c2);
		/* Declare Matrix-1 */
		int** mat_1 = (int **) malloc(r1 * sizeof(int *));
		for (i = 0; i < r1; i++)
			mat_1[i] = (int*) malloc(c1 * sizeof(int));
		/* Declare matrix-2 */
		int** mat_2 = (int **) malloc(r2 * sizeof(int *));
		for (i = 0; i < r2; i++)
			mat_2[i] = (int *) malloc(c2 * sizeof(int));

		/* read first matrix */
		printf("Enter ur first matrix:\n");
		for (i = 0; i < r1; i++) {
			for (j = 0; j < c1; j++) {
				scanf("%d", &mat_1[i][j]);
			}
		}
		/* read first matrix */
		printf("Enter ur second matrix:\n");
		for (i = 0; i < r2; i++) {
			for (j = 0; j < c2; j++) {
				scanf("%d", &mat_2[i][j]);
			}
		}
		printf("Input : \n");
		printf("The first matrix \n");
		for (i = 0; i < r1; i++) {
			for (j = 0; j < c1; j++)
				printf("%d ", mat_1[i][j]);
			printf("\n");
		}
		printf("The second matrix \n");
		for (i = 0; i < r2; i++) {
			for (j = 0; j < c2; j++)
				printf("%d ", mat_2[i][j]);
			printf("\n");
		}
		/* initialize size */
		index = 0;
		size = r1 / (p - 1);
		/* check condition of multiplication*/
		if (c1 != r2)
			printf("these matrices can't be multiplied!\n");
		/* Sending... */
		for (dest = 1; dest < p; dest++) {
			if (dest == p - 1) {
				/* last process takes the rest of the matrix rows */
				size = size + (r1 % (p - 1));
			}
			/* send first matrix (sub) */
			x = size, y = c1;
			/* send the number of rows */
			MPI_Send(&x, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
			/*send the size of each row */
			MPI_Send(&y, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
			printf("size : ");
			printf("%d", size);
			printf("\n");
			int *row = (int *) malloc(c1 * sizeof(int));
			printf("Send rows :\n");
			for (i = index; i < index + size; i++) {
				for (j = 0; j < c1; j++) {
					row[j] = mat_1[i][j];
					printf("%d ", row[j]);
				}
				printf("\n");
				/* send row by row of first matrix (sub) */
				MPI_Send(row, c1, MPI_INT, dest, tag, MPI_COMM_WORLD);
			}
			/* send the second matrix */
			/* send the number of rows */
			MPI_Send(&r2, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
			/*send the size of each row */
			MPI_Send(&c2, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
			/* update row size */
			row = (int *) malloc(c2 * sizeof(int));

			for (i = 0; i < r2; i++) {
				for (j = 0; j < c2; j++) {
					row[j] = mat_2[i][j];
				}
				/* send row by row of second matrix */
				MPI_Send(row, c2, MPI_INT, dest, tag, MPI_COMM_WORLD);
			}
			index += size;
		}
		/* initialize size */
		index = 0;
		size = r1 / (p - 1);
		/* Receiving... */
		printf("=====================================\n");
		printf("Result Matrix:\n");
		for (dest = 1; dest < p; dest++) {
			if (dest == p - 1) {
				/* last process takes the rest of the matrix rows */
				size = size + (r1 % (p - 1));
			}
			for (i = index; i < index + size; i++) {
				int *row = (int *) malloc(c2 * sizeof(int));
				MPI_Recv(row, c2, MPI_INT, dest, tag, MPI_COMM_WORLD, &status);
				for (j = 0; j < c2; j++)
				printf("%d ", row[j]);
				printf("\n");
			}
			index += size;
		}
	} else if (my_rank != 0) {
		/* Receive number of row of first matrix */
		MPI_Recv(&x, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
		/* Receive size of each row in first matrix */
		MPI_Recv(&y, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);

		

		int** m1 = (int **) malloc(x * sizeof(int *));
		/* Receiving the first matrix */
		for (i = 0; i < x; i++)
			m1[i] = (int*) malloc(y * sizeof(int));
		//printf("Received rows:\n");
		for (i = 0; i < x; i++) {
			int *row = (int *) malloc(y * sizeof(int));
			MPI_Recv(row, y, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
			m1[i] = row;
			//for (j = 0; j < y; j++)
				//printf("%d ", row[j]);
			//printf("\n");
		}
		/* Receive number of row of second matrix */
		MPI_Recv(&r2, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
		/* Receive size of each row in second matrix */
		MPI_Recv(&c2, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);


		int** m2 = (int **) malloc(r2 * sizeof(int *));
		/* Receiving the Second matrix */
		for (i = 0; i < r2; i++)
			m2[i] = (int*) malloc(c2 * sizeof(int));

		for (i = 0; i < r2; i++) {
			int *row = (int *) malloc(c2 * sizeof(int));
			MPI_Recv(row, c2, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
			m2[i] = row;
		}
		/* Multiplication */
		int** m3 = (int **) malloc(x * sizeof(int *));
		/* Receiving the Second matrix */
		for (i = 0; i < x; i++)
			m3[i] = (int*) malloc(c2 * sizeof(int));
		
		
                /*
                printf("\n");
		printf("m1:\n");
		for (i = 0; i < x; i++) {
			for (j = 0; j < y; j++)
				printf("%d ", m1[i][j]);
			printf("\n");
		}
                printf("m2:\n");
                for (i = 0; i < r2; i++) {
			for (j = 0; j < c2; j++)
				printf("%d ", m2[i][j]);
			printf("\n");
		}
                */
		for (i = 0; i < x; i++) {
			for (j = 0; j < c2; j++) {
				m3[i][j] = 0;
				for (k = 0; k < r2; k++)
					m3[i][j] += (m1[i][k] * m2[k][j]);
				//printf("%d ", m3[i][j]);

			}
		}
		/* sending the result matrix */
		int *row = (int *) malloc(c2 * sizeof(int));
		for (i = 0; i < x; i++) {
			row = m3[i];
                        //for (j = 0 ; j < c2; j++)
                           //printf("%d ", row[j]);
			MPI_Send(row, c2, MPI_INT, 0, tag, MPI_COMM_WORLD);
		}
	}
	/* shutdown MPI */
	MPI_Finalize();
	return 0;
}
