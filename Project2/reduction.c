#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h> 
#include <assert.h>
#include <sys/time.h>

int elapsedTime(struct timeval t1, struct timeval t2)
{
    // returns elapsed time in microseconds
    return (t2.tv_sec-t1.tv_sec)*10000 + (t2.tv_usec-t1.tv_usec);
}

int *GenerateArray(int size)
{
    int *arr = malloc(sizeof(int)*size);

    for(int i=0; i < size; i++)
    {
        arr[i] = rand();
    }

    return arr;
}

int operationSum(int array[], int size)
{

    int sum = 0;
    for(int i = 0; i < size; i++)
    {
        sum = sum + array[i];
    }
    return sum;
}

int MyReduce(int array[], int size, int rank, int procs)
{
    int buddy = 0, sum_buddy = 0;
    int sum = operationSum(array, size);
    int time_steps = (int)ceil(log2((double)procs)) -1;
    int t = 1, x = 0;
    MPI_Status status;

    for(int k = 0; k <= time_steps; k++)
    {
        buddy = rank ^ t; // XOR flipping operator
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
    int *arr, size = 0, root = 0;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    if(argc >= 1)
    {
        size = atoi(argv[1]);
    }
    assert(p >= 2);
    
    time_t t;
    srand((unsigned)time(&t));
    
    
    if(rank == root) // make array of given size
    {
        arr = GenerateArray(size);
    }

    int items_per_proc = size / p;
    
    int * sub_arr = malloc(sizeof(int) * items_per_proc);

    MPI_Scatter(arr, items_per_proc, MPI_INT, sub_arr, items_per_proc, MPI_INT, root, MPI_COMM_WORLD);
    
    MPI_Barrier(MPI_COMM_WORLD); // synchronize all procs before marking start time
    gettimeofday(&t1, NULL);
    MyReduce(sub_arr, items_per_proc, rank, p);
    MPI_Barrier(MPI_COMM_WORLD); // synchronize all procs before marking end time
    gettimeofday(&t2, NULL);
    int time_reduce = elapsedTime(t1, t2);

    if(rank == root)
    {
        // time of execution,num procs,array size 
        printf("%d,%d,%d\n", time_reduce, p, size);
    }

    MPI_Finalize();
}
