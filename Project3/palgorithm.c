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

    char id[2] = "0";
    char filename[18] = "Results";
    id[0] += rank;
    strcat(filename, id);
    strcat(filename, ".txt");
    FILE * outfile = fopen(filename, "w");

    if (procs >=8)
    {
        procs = 8;
    }

    Matrix *M_arr = (Matrix*)malloc(sizeof(Matrix) * n/procs);

    int i;
    //initialize all the xlocals to (A,0,B,1)
    for(i =0; i < n/procs; i++) {
        M_arr[i].M[0][0] = A;
        M_arr[i].M[0][1] = 0;
        M_arr[i].M[1][0] = B;
        M_arr[i].M[1][1] = 1;
	//printf ("\n");
    }
    

    Matrix local = {1,0,0,1};
    Matrix global;  // M^0   identity matrix

    //calculate M^n/p for all procs
    for(i =1; i < n/procs; i++) {
       M_arr[i] =  multiplySquareMatMod( M_arr[i], M_arr[i-1], Prime);
    }
    //get the last irem in x_local
    global =  M_arr[(n/procs)-1];
    printf("this is the final matrix\n");

    //pass the global to ParallelPrefix
    Matrix offset;
    offset = ParallelPrefix( global, procs, rank, Prime, A, B);

    ///now that we have offset
    //we generate randomArr
    unsigned int M_randArr[1][2], x0_1[1][2];
    // final ouput 
    unsigned int *arr = malloc(sizeof(unsigned int) * n);
    // [x0  1] => x0 = seed and 1 stays same
    x0_1[0][0] = seed; x0_1[0][1] = 1;

    for ( i = 0; i < n / procs; i++) {
        //generate offset * M_arr[i]
        M_arr[i] = multiplySquareMatMod(M_arr[i], offset, Prime);
        //generate randArr
        multiplyRectMatMod(x0_1, M_arr[i],M_randArr, Prime);
    }
    //fprintf(outfile, "rank %d rand nums: \n", rank);
    for (int i = 0; i < n / p; i++) {
        fprintf(outfile, "%d\n", M_randArr[i]);
    }
    printf("\n");

    fclose(outfile);

	
    Matrix myMatrix = {A,0,B,1};
    int *arr = serial_matrix(n, A, B, Prime, seed);
    int *arr1 = serial_baseline(n, A, B, Prime, seed);

    char filename2[18] = "ResultsSerial.txt";
    outfile = fopen(filename2, "w");

    fprintf("This is serial_matrix\n");
    for (i =0; i< n; i++ )
    {
        fprintf(outfile, "%d\n", arr[i]);
    }
    fprintf("This is serial_baseline\n");
    
    for (i =0; i< n; i++ )
    {
        fprintf(outfile, "%d\n", arr1[i]);
    }
    fclose(outfile);
    MPI_Finalize();

 return 0;

}
