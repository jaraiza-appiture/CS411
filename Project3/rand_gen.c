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

int *serial_baseline(int n, int A, int B, int P, int seed)
{
    int x_cur = 1, x_prev = 0;
    int *arr = malloc(sizeof(int) * n);
    arr[x_prev] = seed; // init x[0] with seed

    for(x_cur, x_prev; x_cur < n; x_cur++, x_prev++)
        arr[x_cur] = (arr[x_prev] + B) % P; // linear congruential generator

    return arr;
}

int **init_matrix(int rows, int columns)
{
    int i; 
    int **mat = (int **)malloc(rows * sizeof(int *)); 

    for (i=0; i < rows; i++)
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

int **init_M(int A, int B)
{
    int **M = init_matrix(2, 2);

    M[0][0] = A; M[0][1] = 0;
    M[1][0] = B; M[1][1] = 1;

    return M;
}

void mat_mul_mod_p(int **x, int r_x, int c_x, int **y, int r_y, int c_y, int **result, int P)
{
    int i, j, k;
    int **temp = init_matrix(r_x, c_y);

    for(i = 0; i<r_x; ++i)
    {
        for(j = 0; j<c_y; ++j)
        {
            temp[i][j] = 0;
            for(k = 0; k<c_x; ++k)
                temp[i][j] += x[i][k] * y[k][j];
        }
    }

    for(i = 0; i<r_x; ++i)
        for(j = 0; j<c_y; ++j)
            result[i][j] = temp[i][j] % P;

    dealloc_matrix(temp, r_x, c_y);
}

int * serial_matrix(int n, int A, int B, int P, int seed)
{
    int x_cur = 1, x_prev = 0, i;
    int **M = init_M(A, B), **M_next = init_M(A, B);
    int **xi_1 = init_matrix(1, 2), **x0_1 = init_matrix(1, 2);
    int *arr = malloc(sizeof(int) * n);
    
    x0_1[0][0] = seed, x0_1[0][1] = 1;
    arr[0] = seed;

    for(i = 1; i< n; i++)
    {
        mat_mul_mod_p(x0_1, 1, 2, M_next, 2, 2, xi_1, P);
        arr[i] = xi_1[0][0];
        mat_mul_mod_p(M_next, 2, 2, M, 2, 2, M_next, P);
    }
    
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
    // run parallel prefix
    MPI_Barrier(MPI_COMM_WORLD); // synchronize all procs before marking end time
    gettimeofday(&t2, NULL);
    int time_parallel_prefix = elapsedTime(t1, t2);
    
    if(rank == p-1)
    {
        // must assert rand gen arrays are same

        int i;
        printf("rand matrix arr: [");
        for(i = 0; i < n -1; i++)
            printf("%d, ", rand_arr_matrix[i]);
        printf("%d]\n", rand_arr_matrix[i]);


        printf("rand baseline arr: [");
        for(i = 0; i < n -1; i++)
            printf("%d, ", rand_arr_matrix[i]);
        printf("%d]\n", rand_arr_matrix[i]);

        // csv format output: time_serial_baseline, time_serial_matrix, time_parallel_prefix, num_procs, array_size, a, b, p, seed 
        printf("%d,%d,%d,%d,%d,%d,%d,%d,%d\n", time_serial_baseline,
                                               time_serial_matrix,
                                               time_parallel_prefix,
                                               p, n, A, B, P, seed);
    }

    MPI_Finalize();
}
