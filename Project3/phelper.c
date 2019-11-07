typedef struct Matrix
{
    unsigned int M[2][2];
} Matrix;

void copyMatrix(unsigned int src[1][2], unsigned int dest[1][2])
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
    printf("M[0][0] = %d\n", M.M[0][0]);
    printf("M[0][1] = %d\n", M.M[0][1]);
    printf("M[1][0] = %d\n", M.M[1][0]);
    printf("M[1][1] = %d\n", M.M[1][1]);
    printf("\n");
   /** for (i = 0; i < 2; i++) {
        for(j = 0; j < 2; j++) {
            printf("  | %d  ", M.M[i][j]);
        }
        printf("|\n");
    }
   **/
}
void multiplyRectMatMod(unsigned int x0_1[1][2], Matrix M, unsigned int xi_1[1][2], int Prime)
{
    int i, j, k;
    unsigned int temp[1][2];


    for(i = 0; i<1; i++)
    {
        for(j = 0; j<2; j++)
        {
            temp[i][j] = 0;
            for(k = 0; k<2; k++)
                temp[i][j] += x0_1[i][k] * M.M[k][j];
            temp[i][j] = temp[i][j] % Prime;
            // printf("%d ", temp[i][j]);
        }
        // printf("\n");
    }
    copyMatrix(temp, xi_1);
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

int *serial_matrix(int n, int A, int B, int P, int seed)
{
    int i;
    Matrix M = { A, 0, B, 1 };
    Matrix M_next = M;
    
    //[xi   1] [x0    1]
    unsigned int xi_1[1][2], x0_1[1][2];

    // final ouput 
    unsigned int *arr = malloc(sizeof(unsigned int) * n);
    // [x0  1] => x0 = seed and 1 stays same
    x0_1[0][0] = seed; x0_1[0][1] = 1;
    // arr[0] <= seed
    arr[0] = seed;

    //go through all the inputs 
    for(i = 1; i< n; i++)
    {
        // [xi  1] = [x0    1] x^   M_next
        //should modify M_next
        multiplyRectMatMod(x0_1, M_next, xi_1, P);
        arr[i] = xi_1[0][0];
        //printMatrix(M_next);
        M_next = multiplySquareMatMod(M, M_next, P);
        // printf("\t\ti = %d\n", i);
    }
    
    return arr;
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

int ParallelPrefix(Matrix global, int procs, int rank, int Prime, int A, int B)
{
        //MPI reduce start
    int k;
    int t = 1;
    Matrix local = {1,0,0,1};
    int time_steps = (int)ceil(log2((double)procs)) -1;
    printf ("timesteps are %d\n" , time_steps);
    for(k = 0; k <= time_steps; k++)
    {
	printf ("\nk is : %d\n", k);
	    MPI_Status status;
        Matrix g_remote;
        int buddy = rank ^ t; // XOR flipping operator
        t = t << 1; // double num
	
        MPI_Sendrecv(&global.M, 4, MPI_INT, buddy, 0, &g_remote.M, 4, MPI_INT, buddy, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

        printf("\nthe rank is %d", rank);
	    printf("the buddy is %d", buddy);
	    if (buddy <rank)
	    {
	        printf("\nbuddy is less than rank\n");
            local = multiplySquareMatMod(g_remote, local,Prime);
	    }
        //printf("\nthe rank is %d", rank);
        printf("\nthis is the local\n");
        printMatrix(local);

        global = multiplySquareMatMod(g_remote, global, Prime);
        printf("\nthis is the global\n");
        printMatrix(global);
        

    }


}

