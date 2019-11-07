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
    
    Matrix global;  

    //calculate M^n/p for all procs
    for(i =1; i < n/procs; i++) {
       M_arr[i] =  multiplySquareMatMod( M_arr[i], M_arr[i-1], Prime);
    }
    //get the last irem in M_arr M^n/p
    global =  M_arr[(n/procs)-1];

    //pass the global to ParallelPrefix
    Matrix offset;
    offset = ParallelPrefix( global, procs, rank, Prime, A, B);
    printf("I am rank %d\n", rank);
    printf("I am offset\n");
    printMatrix(offset);

    
    ///now that we have offset
    //we generate randomArr
    int M_randArr[1][2], x0_1[1][2];
    // final ouput 
    // [x0  1] => x0 = seed and 1 stays same
    x0_1[0][0] = seed; x0_1[0][1] = 1;
    int j;
    for ( i = 0; i < n / procs; i++) {
        //generate offset * M_arr[i]
        M_arr[i] = multiplySquareMatMod(M_arr[i], offset, Prime);
	printf("After getting multiplied by offset\n");
	printMatrix(M_arr[i]);
        //generate random numbers => M_randArr has everything in the end
        multiplyRectMatMod(x0_1, M_arr[i], M_randArr, Prime);
        x0_1[0][0]  = M_randArr[0][0];
	x0_1[0][1] = M_randArr[0][1];
	
    }
    
    //fprintf(outfile, "rank %d rand nums: \n", rank);

    for (i = 0; i < n / procs; i++) {
        fprintf(outfile,"M_randArr[0][0]: at %d index is %d\n",i, M_randArr[0][0]);
        // fprintf(outfile,"M_randArr[0][1]: %d\n", M_randArr[0][1]);
    }
    printf("\n");

    fclose(outfile);
	
    Matrix myMatrix = {A,0,B,1};
    int *arr = serial_matrix(n, A, B, Prime, seed);
    int *arr1 = serial_baseline(n, A, B, Prime, seed);

    char filename2[18] = "ResultsSerial.txt";
    outfile = fopen(filename2, "w");

    
    for (i =0; i< n; i++ )
    {
        fprintf(outfile, "S_Matrix	%d\n", arr[i]);
    }   
   

    
    for (i =0; i< n; i++ )
    {
        fprintf(outfile, "S_Baseline	%d\n", arr1[i]);
    }
    fclose(outfile);
    MPI_Finalize();

 return 0;

}
