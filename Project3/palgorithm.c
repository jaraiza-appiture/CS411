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
    int rank,procs, subprocs;
    int seed, A, B, n, Prime;
    // Init and setup calls
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&procs);
    subprocs = procs;

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

    if (procs >=8)
    {
        procs = 8;
    }
    Matrix *x_locals = (Matrix*)malloc(sizeof(Matrix) * n/procs);

    //initialze everythin
   // int x_locals[n/procs];     
    int i;
    //initialize all the xlocals to (A,0,B,1)
    for(i =0; i < n/procs; i++) {
        x_locals[i].M[0][0] = A;
        x_locals[i].M[0][1] = 0;
        x_locals[i].M[1][0] = B;
        x_locals[i].M[1][1] = 1;
//    	printMatrix(x_locals[i]);
	//printf ("\n");
    }
    

    Matrix local = {1,0,0,1};
    Matrix global;  // M^0   identity matrix
    //calculate M^n/p for all procs
    for(i =1; i < n/procs; i++) {
       x_locals[i] =  multiplySquareMatMod( x_locals[i], x_locals[i-1], Prime);
    }
    //get the last irem in x_local
    global =  x_locals[(n/procs)-1];
    printf("this is the final matrix\n");
    // printMatrix(global);

    //pass the global to ParallelPrefix
    ParallelPrefix( global, procs, rank, Prime, A, B);



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

    MPI_Finalize();

 return 0;

}
