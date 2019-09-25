#include <stdio.h>
#include <math.h>
#include <mpi.h> 
#include <assert.h>
#include <sys/time.h>

int generate_array(int size)
{
    //generate random int array of give size...
    //use malloc and find good rand function lib
    // or could have each process generate its own part if array too...
}

int operationSum(int array[])
{
    int length = sizeof(array)/sizeof(int);
    int sum = 0;
    for(int i = 0; i < length; i++)
    {
        sum = sum + array[i];
    }
    return sum;
}

int my_reduce(int rank, int procs, int array[])
{
    int buddy = 0, sum_buddy = 0;
    int sum = operationSum(array);
    int time_steps = (int)ceil(log2((double)procs)) -1;
    int t = 1, x = 0;
    MPI_Status status;

    for(int k = 0; k <= time_steps; k++)
    {
        buddy = rank ^ t; //XOR flipping operator
        t << 1; // double num

        if(buddy < rank)
        {
            MPI_Sendrecv(&sum, 1, MPI_INT, buddy, 0, &sum_buddy, 1, MPI_INT, buddy, 0, MPI_COMM_WORLD, &status);
            sum = sum + sum_buddy;
        }
        else
        {
            MPI_Send(&sum, 1, MPI_INT, buddy, 0, MPI_COMM_WORLD);
        }
        
    }

    if(rank == (p-1))
    {
        printf("[Proc %d] sum is %d", p, sum);
    }
}

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
	size = atoi(argv[1]);
   }
   assert(p >= 2);

    //Idea for sending array parts around, only one particular rank will send array parts
    // to the rest of the procs, will keep its own part.
    // then we begin.... this may not work..

   MPI_Finalize();
}
