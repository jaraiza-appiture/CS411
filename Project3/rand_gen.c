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

int * serial_baseline(int n, int A, int B, int P, int seed)
{
    int x_cur = 1, x_prev = 0;
    int * arr = malloc(sizeof(int) * n);
    arr[x_prev] = seed; // init x[0] with seed

    for(x_cur, x_prev; x_cur < n; x_cur++, x_prev++)
        arr[x_cur] = (arr[x_prev] + B) % P; // linear congruential generator

    return arr;
}

int * serial_matrix(int n, int A, int B, int P, int seed)
{
    int x_cur = 1, x_prev = 0;
    int * arr = malloc(sizeof(int) * n);
    arr[x_prev] = seed; // init x[0] with seed

    for(x_cur, x_prev; x_cur < n; x_cur++, x_prev++)
        arr[x_cur] = (arr[x_prev] + B) % P; // linear congruential generator
    
    return arr;
}

int main(int argc,char *argv[])
{
    int rank, p;
    struct timeval t1, t2;
    int n = 0, A = 0, B = 0, P = 0, seed = 0, root = 0;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    if(argc >= 6)
    {
        n = atoi(argv[1]);
        A = atoi(argv[2]);
        B = atoi(argv[3]);
        P = atoi(argv[4]);
        seed = atoi(argv[5]);
    }
    assert(p >= 2);
    
    time_t t;
    srand((unsigned)time(&t));

    int nums_per_proc = n / p;

    MPI_Barrier(MPI_COMM_WORLD); // synchronize all procs before marking start time
    gettimeofday(&t1, NULL);
    int * rand_arr_baseline = serial_baseline(n, A, B, P, seed);
    MPI_Barrier(MPI_COMM_WORLD); // synchronize all procs before marking end time
    gettimeofday(&t2, NULL);
    int time_serial_baseline = elapsedTime(t1, t2);

    MPI_Barrier(MPI_COMM_WORLD); // synchronize all procs before marking start time
    gettimeofday(&t1, NULL);
    // run serial matrix
    MPI_Barrier(MPI_COMM_WORLD); // synchronize all procs before marking end time
    gettimeofday(&t2, NULL);
    int time_serial_matrix = elapsedTime(t1, t2);

    MPI_Barrier(MPI_COMM_WORLD); // synchronize all procs before marking start time
    gettimeofday(&t1, NULL);
    // run parallel prefix
    MPI_Barrier(MPI_COMM_WORLD); // synchronize all procs before marking end time
    gettimeofday(&t2, NULL);
    int time_parallel_prefix = elapsedTime(t1, t2);
    
    if(rank == p-1)
    {
        // must assert rand gen arrays are same

        int i;
        printf("rand arr: [");
        for(i = 0; i < n -1; i++)
            printf("%d, ", rand_arr_baseline[i]);
        printf("%d]\n", rand_arr_baseline[i]);

        // csv format output: time_serial_baseline, time_serial_matrix, time_parallel_prefix, num_procs, array_size, a, b, p, seed 
        printf("%d,%d,%d,%d,%d,%d,%d,%d,%d\n", time_serial_baseline,
                                               time_serial_matrix,
                                               time_parallel_prefix,
                                               p, n, A, B, P, seed);
    }

    MPI_Finalize();
}
