#include <stdio.h>
#include <mpi.h> 
#include <assert.h>
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "phelper.c"



int main(int argc, char *argv[])
{

    // Step 1:
    int rank,procs;
    int seed, A, B, n, Prime;
    // Init and setup calls
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&procs);

    // assert(argc == 6);
    // A = 2069;
    // B = 3069;
    // Prime = 9973;
    // seed = 10;
    // n = 8;
    A = atoi(argv[1]);
    B = atoi(argv[2]);
    Prime = atoi(argv[3]);
    seed = atoi(argv[4]);
    n = atoi(argv[5]);

    Matrix m_local = { A, 0, B, 1 };
    Matrix iden_local = { 1, 0, 0, 1 };
    //initialze everythin
    int x_local[n/p] = {0};     
    int i;
    //initialize all the xlocals
    for(i =0; i < n/procs; i++) {
        xlocals[i] = m_local.M;
        printMatrix(x_locals[i]);
    }
    
    // myMatrix = {{A,0},{B,1}};
    // int *arr = serial_matrix(n, A, B, Prime, seed);
    // int *arr1 = serial_baseline(n, A, B, Prime, seed);


    // for (int i =0; i< n; i++ )
    // {
    //     printf("%d  ", arr[i]);
    // }
    // printf("\n");
    // for (int i =0; i< n; i++ )
    // {
    //     printf("%d  ", arr1[i]);
    // }


 return 0;

}
