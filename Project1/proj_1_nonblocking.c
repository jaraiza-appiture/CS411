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

   assert(p >= 2);

   if(rank == 1) {
	int i = 0;
	char *my_char = malloc(sizeof(char) *(size));
	// 			for(i = 0; i < size; i++)
	// 			{
	// 	my_char[i] = 'T'; // change this to use memset
	// }
	int dest = 0;
	gettimeofday(&t1, NULL);
	MPI_Send( my_char, size, MPI_CHAR, dest, 0, MPI_COMM_WORLD);
	gettimeofday(&t2, NULL);
	int timeSend = (t2.tv_sec-t1.tv_sec)*10000 + (t2.tv_usec-t1.tv_usec);
   //rank,send_time(microseconds),size(bytes)
	printf("%d,%d,%d\n", rank, timeSend, size);
   } 
   else 
   if (rank == 0) {
        char *y = malloc(sizeof(char)*(size));
        MPI_Status status;
        MPI_Request request;

        gettimeofday(&t1, NULL);
        //MPI RECV == MPI IRECEIVE AND MPI WAIT == MPI IRECIEVE AND MPI TEST IN WHILE LOOP 
        MPI_Irecv(y, size, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &request);
        MPI_Wait(&request, &status);
        gettimeofday(&t2, NULL); // need to poll test for msg in while loop
        int timeRecv = (t2.tv_sec-t1.tv_sec)*10000 + (t2.tv_usec-t1.tv_usec);
        //rank,recv_time(microseconds),size(bytes)
        printf("%d,%d,%d\n",rank, timeRecv, size);
        

   }
   MPI_Finalize();
}
