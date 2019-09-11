/*	Cpt S 411, Introduction to Parallel Computing
 *	School of Electrical Engineering and Computer Science
 *	
 *	Example code
 *	Send receive test:
 *   	rank 1 sends to rank 0 (all other ranks sit idle)
 *   	For timing use of C gettimeofday() is recommended.
 * */


#include <stdio.h>
#include <mpi.h> 
#include <assert.h>
#include <sys/time.h>

int main(int argc,char *argv[])
{

   int rank, p;
   struct timeval t1, t2;
   int size = 0;
   
   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   MPI_Comm_size(MPI_COMM_WORLD, &p);
   

   if(argc >= 1)
   { 
	// printf("Argv[1]: %s", argv[1]);
	size = atoi(argv[1]);
   }
   printf("\n");
   assert(p >= 2);

   if(rank == 1) {
	int i = 0;
	char *my_char = malloc(sizeof(char) *(size));
				for(i = 0; i < size; i++)
				{
		my_char[i] = 'T';
	}
	int dest = 0;
	gettimeofday(&t1, NULL);
	MPI_Send( my_char, size, MPI_CHAR, dest, 0, MPI_COMM_WORLD);
	gettimeofday(&t2, NULL);
	int tSend = (t2.tv_sec-t1.tv_sec)*10000 + (t2.tv_usec-t1.tv_usec);

	printf("Rank=%d: sent message %c to rank %d; Send time %d microseconds; size: %d\n", rank, my_char[0], dest, tSend, size);
   } 
   else 
   if (rank == 0) {
        char *y = malloc(sizeof(char)*(size));
        MPI_Status status;
        MPI_Request request;

        gettimeofday(&t1, NULL);
        MPI_Irecv(y, size, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &request);
        gettimeofday(&t2, NULL);
        int tRecv = (t2.tv_sec-t1.tv_sec)*10000 + (t2.tv_usec-t1.tv_usec);
        printf("Rank=%d: received message %c from rank %d; Recv time %d microseconds; size: %d\n",rank, y[0], status.MPI_SOURCE, tRecv, size);
        MPI_Wait(&request, &status);

   }
   MPI_Finalize();
}
