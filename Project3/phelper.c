typedef struct Matrix
{
    int M[2][2];
} Matrix;

void copyMatrix(int src[1][2], int dest[1][2])
{
    int i = 0, j = 0;
    for(i = 0; i < 1; i++)
    {
        for(j = 0; j < 2; j++)
        {
            dest[i][j] = src[i][j];
        }
    }
}


int printMatrix(Matrix M)
{
    int i=0, j=0;
    /**printf("M[0][0] = %d\n", M.M[0][0]);
    printf("M[0][1] = %d\n", M.M[0][1]);
    printf("M[1][0] = %d\n", M.M[1][0]);
    printf("M[1][1] = %d\n", M.M[1][1]);
    printf("\n");**/
    for (i = 0; i < 2; i++) {
        for(j = 0; j < 2; j++) {
             printf("  | %d  ", M.M[i][j]);
        }
         printf("|\n");
    }
   
}

int printMatrixInt(int M[2][2])
{
    int i=0, j=0;
    /**printf("M[0][0] = %d\n", M.M[0][0]);
    printf("M[0][1] = %d\n", M.M[0][1]);
    printf("M[1][0] = %d\n", M.M[1][0]);
    printf("M[1][1] = %d\n", M.M[1][1]);
    printf("\n");**/
   for (i = 0; i < 2; i++) {
        for(j = 0; j < 2; j++) {
            // printf("  | %d  ", M[i][j]);
        }
        // printf("|\n");
    }
   
}

void multiplyRectMatMod(int x0_1[1][2], Matrix M, int xi_1[1][2], int Prime)
{
    int i, j, k;
    int temp[1][2];

//    printf("this is multiplyRectMatMod Matroix\n");
    for(i = 0; i<1; i++)
    {
        for(j = 0; j<2; j++)
        {
            xi_1[i][j] = 0;
            for(k = 0; k<2; k++)
                xi_1[i][j] += x0_1[i][k] * M.M[k][j];
            xi_1[i][j] = xi_1[i][j] % Prime;
//           printf("|	%d ", xi_1[i][j]);
        }
  //       printf("|\n");
    }
    // copyMatrix(temp, xi_1);

}


int multiplySquareMat(int M[2][2], int N[2][2], int Res[2][2])
{
    int i = 0, j=0, k=0;    
    for (i = 0; i < 2; i++) {
        for(j = 0; j < 2; j++) {
            for(k = 0; k < 2; k++) {
                Res[i][j] += M[i][k] * N[k][j];
            }
            // printf("%d\n",Res[i][j]);
        }
    
}}

Matrix multiplySquareMatMod(Matrix M, Matrix M_next, int Prime)
{
    Matrix Res = { 0 };

    // printf("M = \n");
    // printMatrix(M);
    // printf("M_next = \n");
    // printMatrix(M_next);
    int i = 0, j=0,k=0;
    for (i = 0; i < 2; i++) {
        for(j = 0; j < 2; j++) {
            for(k = 0; k < 2; k++) {
                Res.M[i][j] += M.M[i][k] * M_next.M[k][j];
            }
            Res.M[i][j]= Res.M[i][j]% Prime;
            //  printf("%d\n",Res.M[i][j]);
        }
    }
    //  printf("Res = \n");
    //  printMatrix(Res);

    M_next = Res;
    return M_next;
    // copyMatrix(Res, M_next);

}
Matrix multiplySquareMatMod2(Matrix M1, Matrix M2, int Prime) {
    Matrix R;

    R.M[0][0] = M1.M[0][0] * M2.M[0][0] + M1.M[0][1] * M2.M[1][0];
    R.M[0][1] = M1.M[0][0] * M2.M[0][1] + M1.M[0][1] * M2.M[1][1];
    R.M[1][0] = M1.M[1][0] * M2.M[0][0] + M1.M[1][1] * M2.M[1][0];
    R.M[1][1] = M1.M[1][0] * M2.M[0][1] + M1.M[1][1] * M2.M[1][1];

    R.M[0][0] %=Prime;
    R.M[0][1] %=Prime;
    R.M[1][0] %=Prime;
    R.M[1][1] %=Prime;

    return R;
}
int getPartner(int tStep, int rank)
{
    int power = 1;
    power = power << tStep;
    int partner = rank ^ power;
    return partner;
}

// int *serial_matrix(int n, int A, int B, int P, int seed)
// {
//     int i;
//     Matrix M = { A, 0, B, 1 };
//     Matrix M_next = M;
    
//     //[xi   1] [x0    1]
//     int xi_1[1][2], x0_1[1][2];

//     // final ouput 
//     int *arr = malloc(sizeof(unsigned int) * n);
//     // [x0  1] => x0 = seed and 1 stays same
//     x0_1[0][0] = seed; x0_1[0][1] = 1;
//     // arr[0] <= seed
//     arr[0] = seed;

//     //go through all the inputs 
//     for(i = 1; i< n; i++)
//     {
//         // [xi  1] = [x0    1] x^   M_next
//         //should modify M_next
//         multiplyRectMatMod(x0_1, M_next, xi_1, P);
//         arr[i] = xi_1[0][0];
//         //printMatrix(M_next);
//         M_next = multiplySquareMatMod(M, M_next, P);
//         // printf("\t\ti = %d\n", i);
//     }
    
//     return arr;
// }
// int *serial_baseline(int n, int A, int B, int P, int seed)
// {
//     int x_cur = 1, x_prev = 0;
//     int *arr = malloc(sizeof(int) * n);
//     arr[x_prev] = seed; // init x[0] with seed

//     for(x_cur, x_prev; x_cur < n; x_cur++, x_prev++)
//         arr[x_cur] = ((arr[x_prev]*A) + B) % P; // linear congruential generator

//     return arr;
// }

Matrix ParallelPrefix(Matrix global, int procs, int rank, int Prime, int A, int B)
{
        //MPI reduce start
    int k;
    int t = 1;
    Matrix local = {1,0,0,1};
    int time_steps = (int)ceil(log2((double)procs)) -1;
    // printf ("timesteps are %d\n" , time_steps);
    for(k = 0; k <= time_steps; k++)
    {
	// printf ("\nk is : %d\n", k);
	    MPI_Status status;
        Matrix g_remote;
        int buddy = rank ^ t; // XOR flipping operator
        t = t << 1; // double num
	
        MPI_Sendrecv(&global.M, 4, MPI_INT, buddy, 0, &g_remote.M, 4, MPI_INT, buddy, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

        // printf("\nthe rank is %d", rank);
	    // printf("the buddy is %d", buddy);
	    if (buddy <rank)
	    {
//	        printf("\nbuddy is less than rank\n");
            local = multiplySquareMatMod(g_remote, local,Prime);
	    }
        //printf("\nthe rank is %d", rank);
        // printf("\nthis is the local\n");
        // printMatrix(local);

        global = multiplySquareMatMod(g_remote, global, Prime);
        // printf("\nthis is the global\n");
        // printMatrix(global);


    }
    return local;
}

int * parallel_matrix(int n, int A, int B, int Prime, int seed, int procs, int rank)
{
    Matrix *M_arr = (Matrix*)malloc(sizeof(Matrix) * (n/procs));
    int  *ouch_arr = (int*)malloc(sizeof(int)*(n/procs));
    int i;
    //initialize all the xlocals to (A,0,B,1)
    for(i =0; i < n/procs; i++) {
        M_arr[i].M[0][0] = A;
        M_arr[i].M[0][1] = 0;
        M_arr[i].M[1][0] = B;
        M_arr[i].M[1][1] = 1;
    }
    
    Matrix global;  

    //calculate M^n/p for all procs    
   if (rank ==0) 
	{
	M_arr[0].M[0][0]=1;
	M_arr[0].M[0][1]=0;
	M_arr[0].M[1][0]=0;
	M_arr[0].M[1][1]=1;
	}

    for(i =1; i < n/procs; i++) {
       M_arr[i] =  multiplySquareMatMod( M_arr[i], M_arr[i-1], Prime);
    }
    //get the last irem in M_arr M^n/p
    global =  M_arr[(n/procs)-1];

    //pass the global to ParallelPrefix
    Matrix offset;
    offset = ParallelPrefix( global, procs, rank, Prime, A, B);
   
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
	    // printf("After getting multiplied by offset\n");
	    // printMatrix(M_arr[i]);
        //generate random numbers => M_randArr has everything in the end
        multiplyRectMatMod(x0_1, M_arr[i], M_randArr, Prime);
        ouch_arr[i]  = M_randArr[0][0];
    }
    


 return ouch_arr;

}

