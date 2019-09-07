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

   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   MPI_Comm_size(MPI_COMM_WORLD, &p);

   printf("my rank=%d\n", rank);
   printf("Rank=%d: number of processes =%d\n", rank, p);

   assert(p >= 2);

   if(rank == 1) {
	   	int size = 0;
		int i = 0;
		for (size = 1; size <= 1000; size = size*2 )
		{
			for (i = 0; i<10; i++)
			{
			char *my_char = malloc(sizeof(char) *(size));
			int dest = 0;
			gettimeofday(&t1, NULL);
			MPI_Send( my_char, size, MPI_CHAR, dest, 0, MPI_COMM_WORLD);
			gettimeofday(&t2, NULL);
			int tSend = (t2.tv_sec-t1.tv_sec)*10000 + (t2.tv_usec-t1.tv_usec);

			printf("Rank=%d: sent message %c to rank %d; Send time %d microseconds; size: %d\n", rank, my_char[0], dest, tSend, size);
			}
		}
   } else 
   if (rank == 0) {
	   int size = 0;
	   int i = 0;
	   // This is my code!!!!!
	   for(size = 1; size <= 1000; size = size * 2)
		{	
			for(i = 0; i < 10; i++)
			{
				char *y = malloc(sizeof(char)*(size));
				MPI_Status status;
				gettimeofday(&t1, NULL);
				MPI_Recv(y, size, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
				gettimeofday(&t2, NULL);
				int tRecv = (t2.tv_sec-t1.tv_sec)*10000 + (t2.tv_usec-t1.tv_usec);
				printf("Rank=%d: received message %d from rank %d; Recv time %d microseconds; size: %d\n",rank, y, status.MPI_SOURCE, tRecv, size);
			}
		}
   }

   MPI_Finalize();
}
