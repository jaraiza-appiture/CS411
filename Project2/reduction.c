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
    printf("array generated: ");
    for(i = 0; i < size; i++)
    {
        arr[i] = rand() % 1001;
        printf("%d ", arr[i]);
    }
    printf("\n");

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
        t << 1; // double num

        if(buddy < rank)
        {
            MPI_Sendrecv(&sum, 1, MPI_INT, buddy, 0, &sum_buddy, 1, MPI_INT, buddy, 0, MPI_COMM_WORLD, &status);
            sum = sum + sum_buddy;
            printf("Proc: %d Sum: %d Sum_buddy: %d\n", rank, sum, sum_buddy);
        }
        else
        {
            MPI_Send(&sum, 1, MPI_INT, buddy, 0, MPI_COMM_WORLD);
        }
    }

    // if(rank == (procs-1))
    // {
    //     printf("[Proc %d] sum is %d", rank, sum);
    // }
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
    assert(p >= 2);
    
    time_t t;
    srand((unsigned)time(&t));
    
    if(rank == root) // make array of given size
    {
        arr = GenerateArray(size);
    }

    int items_per_proc = size / p;
    printf("items per proc: %d\n", items_per_proc);
    int * sub_arr = malloc(sizeof(int) * items_per_proc);

    MPI_Scatter(arr, items_per_proc, MPI_INT, sub_arr, items_per_proc, MPI_INT, root, MPI_COMM_WORLD);
    int i = 0;
    printf("Proc: %d\n",rank);
    for(i =0 ; i < items_per_proc; i++)
    {
        printf("%d ",sub_arr[i]);
    }
    printf("\n");
    MPI_Barrier(MPI_COMM_WORLD); // synchronize all procs before marking start time
    gettimeofday(&t1, NULL);
    int sum = MyReduce(sub_arr, items_per_proc, rank, p);
    MPI_Barrier(MPI_COMM_WORLD); // synchronize all procs before marking end time
    gettimeofday(&t2, NULL);
    int time_reduce = elapsedTime(t1, t2);

    if(rank == root)
    {
        // time of execution,num procs,array size 
        printf("%d,%d,%d,%d\n", time_reduce, p, size, sum);
    }

    MPI_Finalize();
}
