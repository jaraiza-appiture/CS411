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
    int i = 0;
    for(i = 0; i < size; i++)
    {
        arr[i] = rand()% 1001;
        // printf("%d\n", arr[i]);

    }

    return arr;
}

int operationSum(int array[], int size)
{

    int sum = 0, i = 0;
    for(i = 0; i < size; i++)
    {
        sum = sum + array[i];
    }
    return sum;
}

int operationMax(int array[], int size)
{

    int max = -1, i = 0;
    for(i = 0; i < size; i++)
    {
        if(max < array[i])
        {
            max = array[i];
        }
    }
    return max;
}
int MyNaive(int array[], int size, int rank, int procs)
{
    
    int buddy = 0, sum_buddy = 0;
    int sum = operationSum(array, size);
    int t = 1, x = 0, k = 0;
    MPI_Status status;

    
    if(rank > 0 )
    {
        MPI_Recv(&sum_buddy, 1, MPI_INT, rank-1, 0, MPI_COMM_WORLD, &status);
        sum = sum + sum_buddy ;
    }
    if (rank < (procs-1) )
    {
        MPI_Send(&sum, 1, MPI_INT, rank+1, 0, MPI_COMM_WORLD);
    }


    // if (rank == 0)
    // {
    //     MPI_Send(&sum,4,MPI_INT,rank + 1,0,MPI_COMM_WORLD);
    // }

    // if(rank > 0 && rank < procs-1 )
    // {
    //     MPI_Recv(&sum_buddy, 4, MPI_INT, rank-1, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
    //     sum = sum + sum_buddy ;
    //     MPI_Send(&sum,4,MPI_INT,rank + 1,0,MPI_COMM_WORLD);

    // }
    // if (rank == (procs-1) )
    // {
    //     MPI_Recv(&sum_buddy,4,MPI_INT,rank -1 ,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
    //     sum = sum + sum_buddy ;

    // }
    	
    // MPI_Finalize();


    return sum;
}

int MPILibReduce(int array[], int size, int rank, int procs)
{
    int buddy = 0, sum_buddy = 0;
    int sum = operationSum(array, size);
    int t = 1, x = 0, k = 0;
    MPI_Status status;
    int global_sum;
    MPI_Allreduce(&sum, &global_sum, 1,  MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    return global_sum;
}

int MyReduce(int array[], int size, int rank, int procs)
{
    int buddy = 0, sum_buddy = 0;
    int sum = operationSum(array, size);
    int time_steps = (int)ceil(log2((double)procs)) -1;
    int t = 1, k = 0;
    MPI_Status status;

    for(k = 0; k <= time_steps; k++)
    {
        buddy = rank ^ t; // XOR flipping operator
        t = t << 1; // double num

        MPI_Sendrecv(&sum, 1, MPI_INT, buddy, 0, &sum_buddy, 1, MPI_INT, buddy, 0, MPI_COMM_WORLD, &status);
        sum = sum + sum_buddy;
    }

    return sum;
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
    assert(p >= 1);
    
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
    int sum_my_reduce = MyReduce(sub_arr, items_per_proc, rank, p);
    MPI_Barrier(MPI_COMM_WORLD); // synchronize all procs before marking end time
    gettimeofday(&t2, NULL);
    int time_my_reduce = elapsedTime(t1, t2);

    MPI_Barrier(MPI_COMM_WORLD); // synchronize all procs before marking start time
    gettimeofday(&t1, NULL);
    int sum_my_naive = MyNaive(sub_arr, items_per_proc, rank, p);
    MPI_Barrier(MPI_COMM_WORLD); // synchronize all procs before marking end time
    gettimeofday(&t2, NULL);
    int time_my_naive = elapsedTime(t1, t2);

    MPI_Barrier(MPI_COMM_WORLD); // synchronize all procs before marking start time
    gettimeofday(&t1, NULL);
    int sum_mpi_reduce = MPILibReduce(sub_arr, items_per_proc, rank, p);
    MPI_Barrier(MPI_COMM_WORLD); // synchronize all procs before marking end time
    gettimeofday(&t2, NULL);
    int time_mpi_reduce = elapsedTime(t1, t2);
    

    if(rank == p-1)
    {
        // printf("sum_my_reduce   %d\n", sum_my_reduce);
        // printf("sum_my_naive    %d\n", sum_my_naive);
        // printf("sum_mpi_reduce  %d\n\n", sum_mpi_reduce);

        assert(sum_my_reduce == sum_my_naive);
        assert(sum_my_naive == sum_mpi_reduce);

        // my_reduce_time,my_naive_time,mpi_reduce_time,num_procs,array_size,sum 
        printf("%d,%d,%d,%d,%d,%d\n", time_my_reduce,time_my_naive, time_mpi_reduce, p, size, sum_my_naive);
    }

    MPI_Finalize();
}
