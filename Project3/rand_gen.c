#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
#include <assert.h>
#include <sys/time.h>
#include "phelper.c"

int elapsedTime(struct timeval t1, struct timeval t2)
{
    // returns elapsed time in microseconds
    return (t2.tv_sec-t1.tv_sec)*10000 + (t2.tv_usec-t1.tv_usec);
}

int *serial_baseline(int n, int A, int B, int P, int seed)
{
    int x_cur = 1, x_prev = 0;
    int *arr = malloc(sizeof(int) * n);
    arr[x_prev] = seed; // init x[0] with seed

    for(x_cur, x_prev; x_cur < n; x_cur++, x_prev++)
        arr[x_cur] = ((arr[x_prev]*A) + B) % P; // linear congruential generator

    return arr;
}

int **init_matrix(int rows, int columns)
{
    int i; 
    int **mat = (int **)malloc(rows * sizeof(int *)); 

    for (i = 0; i < rows; i++)
         mat[i] = (int *)malloc(columns * sizeof(int));
    
    return mat;
}

void dealloc_matrix(int **mat, int rows, int columns)
{
    int i;

    for(i = 0; i < rows; i++)
        free(mat[i]);
    free(mat);
}

void init_M(int M[2][2], int A, int B)
{
    M[0][0] = A; M[0][1] = 0;
    M[1][0] = B; M[1][1] = 1;
}

void mat_mul_x0_M_x1_p(int x0[1][2], int M[2][2], int x1[1][2], int P)
{
    int i, j, k;
    int temp[1][2];

    for(i = 0; i<1; i++)
    {
        for(j = 0; j<2; j++)
        {
            temp[i][j] = 0;
            for(k = 0; k<2; k++)
                temp[i][j] += x0[i][k] * M[k][j];
        }
    }

    for(i = 0; i<1; i++)
    {
        for(j = 0; j<2; j++)
        {
            x1[i][j] = temp[i][j] % P;
        }
    }
}


void mat_mul_M_next_M_p(int M_next[2][2], int M[2][2], int P)
{
    int i, j, k;
    int temp[2][2];

    for(i = 0; i<2; i++)
    {
        for(j = 0; j<2; j++)
        {
            temp[i][j] = 0;
            for(k = 0; k<2; k++)
                temp[i][j] += M_next[i][k] * M[k][j];
        }
        
    }

    for(i = 0; i<2; i++)
    {
        for(j = 0; j<2; j++)
        {
            
            M_next[i][j] = temp[i][j] % P;
            
        }
    }
}

int *serial_matrix(int n, int A, int B, int P, int seed)
{
    int i;
    int M[2][2], M_next[2][2];
    init_M(M, A, B);
    init_M(M_next, A, B);
    int xi_1[1][2], x0_1[1][2];
    int *arr = malloc(sizeof(int) * n);
    
    x0_1[0][0] = seed; x0_1[0][1] = 1;
    arr[0] = seed;

    for(i = 1; i< n; i++)
    {
        mat_mul_x0_M_x1_p(x0_1, M_next, xi_1, P);
        arr[i] = xi_1[0][0];
        // x0_1[0][0] = xi_1[0][0];
        mat_mul_M_next_M_p(M_next, M, P);
    }
    
    return arr;
}

int test_serial_baseline()
{
    int n = 5;
    int A = 3;
    int B = 6;
    int P = 9967;
    int seed = 42;
    int test_arr[5] = {42, 132, 402, 1212, 3642}; 
    int * rand_arr = serial_baseline(n,A,B,P,seed);
    
    int i = 0;
    for(i = 0; i < 5; i++)
        assert(rand_arr[i] == test_arr[i]);
    
}

int test_serial_matrix()
{
    int n = 5;
    int A = 3;
    int B = 6;
    int P = 9967;
    int seed = 42;
    int test_arr[5] = {42, 132, 402, 1212, 3642}; 
    int * rand_arr = serial_matrix(n,A,B,P,seed);
    
    int i = 0;
    for(i = 0; i < 5; i++)
        assert(rand_arr[i] == test_arr[i]);
    
}

int test_parallel_matrix()
{
    int n = 6;
    int A = 3;
    int B = 6;
    int P = 9967;
    int seed = 42;
    int procs = 1;
    int rank = 0;
    int test_arr[6] = {42, 132, 402, 1212, 3642, 965}; 
    int * rand_arr = parallel_matrix(n,A,B,P,seed,procs,rank);
    
    int i = 0;
    for(i = 0; i < 6; i++)
        assert(rand_arr[i] == test_arr[i]);
}


int main(int argc,char *argv[])
{
    int rank, p;
    struct timeval t1, t2;
    int debug = 1;
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
    assert(p >= 1);
    
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
    int * rand_arr_matrix = serial_matrix(n, A, B, P, seed);
    MPI_Barrier(MPI_COMM_WORLD); // synchronize all procs before marking end time
    gettimeofday(&t2, NULL);
    int time_serial_matrix = elapsedTime(t1, t2);

    MPI_Barrier(MPI_COMM_WORLD); // synchronize all procs before marking start time
    gettimeofday(&t1, NULL);
    int * rand_arr_parallel = parallel_matrix(n, A, B, P, seed, p,rank);
    MPI_Barrier(MPI_COMM_WORLD); // synchronize all procs before marking end time
    gettimeofday(&t2, NULL);
    int time_parallel_prefix = elapsedTime(t1, t2);
    
    // correctness testing
    int i = 0, j = 0;
    int start_index = rank * nums_per_proc;
    // int end_index = start_index + nums_per_proc;
    for(j = start_index, i = 0; i < nums_per_proc; j++, i++)
    {
        assert(rand_arr_baseline[j] == rand_arr_parallel[i]);
        assert(rand_arr_baseline[j] == rand_arr_matrix[j]);
    }

    if(rank == p-1)
    {
        if(debug)
        {   if(n > 1000){ j = 1000; }
            else{ j = n;}
            
            printf("Rand Arr: [ ");

            for(i = 0; i < j; i++)
            {
                printf("%d ", rand_arr_baseline[i]);
            }

            printf("]\n");

            printf("Serial Baseline Time: %d\n", time_serial_baseline);
            printf("Serial Matrix Time: %d\n", time_serial_matrix);
            printf("Parallel Prefix Time: %d\n", time_parallel_prefix);
        }
        else
        {
            // csv format output: time_serial_baseline, time_serial_matrix, time_parallel_prefix, num_procs, array_size, a, b, p, seed 
            printf("%d,%d,%d,%d,%d,%d,%d,%d,%d\n", time_serial_baseline,
                                               time_serial_matrix,
                                               time_parallel_prefix,
                                               p, n, A, B, P, seed);
        }
    }

    MPI_Finalize();
}
