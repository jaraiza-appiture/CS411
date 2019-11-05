#include <stdio.h>
#include <mpi.h>
#include <assert.h>
#include <sys/time.h>
#include <math.h>

typedef struct MatrixArray
{
    int M[2][2];
} MatrixArr;

void copymatrix(int src[2][2], int dest[2][2])
{
    int i = 0, j = 0;
    for(i = 0; i < 2; i++)
    {
        for(j = 0; j < 2; j++)
        {
            dest[i][j] = src[i][j];
        }
    }
}
void matrixMultiply(int my_local[2][2], int x_local[2][2], int final_local[2][2], int P)
{
    /**
    a = [a11 a12] b= [b11 b12]
        [a21 a22]    [b21 b22] 
    res  = [a11.b11 a11,b12]
           [a21.b21 a22.b22]
    **/
    int i = 0, j = 0, k = 0, sum = 0;
    int temp[2][2];
    for(i = 0; i < 2; i++)
    {
        for(j = 0; j < 2; j++)
        {
            for(k = 0; k < 2; k++)
            {
               sum = sum + my_local[k][i] * x_local[j][k];
            }
            final_local[j][i] = sum % P;
            print("%d", final_local[j][i])
            sum = 0;
        }
    }

    // for(i = 0; i < 2; i++)
    // {
    //     for(j = 0; j < 2; j++)
    //     {
    //         final_local[i][j] = temp[i][j];
    //     }
    // }
}
int getPartner(int tStep, int rank)
{
    int power = 1;
    power = power << tStep;
    int partner = rank ^ power;
    return partner;
}
void matrixOutputPar(int seed, int A, int B, int Aoff, int Boff, int P, int n, int rank)
{
    int M[2][2], M_next[2][2], x_iMat[2][2];
    int x_0Mat[2][2];
    int i = 1;
    M[0][0] = A;
    M[0][1] = B;
    M[1][0] = 0;
    M[1][1] = 1;
    M_next[0][0] = Aoff;
    M_next[0][1] = Boff;
    M_next[1][0] = 0;
    M_next[1][1] = 1;
    x_0Mat[0][0] = seed;
    x_0Mat[1][0] = 1;
    x_0Mat[0][1] = 0;
    x_0Mat[1][1] = 0;
    //if(rank == 0)
    //matrixMul(M_next, M, M_next, P);
    for(i = 0; i < n; i++)
    {
        matrixMul(x_0Mat, M_next, x_iMat, P);
        printf("%d x_%d = %d\n", rank, (rank*(n)) + i + 1, x_iMat[0][0]);
        matrixMul(M_next, M, M_next, P);
    }
}
//procs, number of ints, A, B, P, seed, Rank
void ParallelOutput(int seed, int A, int B, int P,  int n, int rank, int procs)
{
    //calculate the total arraysize  to n procs
    int arraySize = n/procs;

    MatrixArray *myMatrices = (MatrixArray*)malloc(sizeof(MatrixArray) * arraySize);
    int globalSum[2][2], localSum[2][2];
    int i = 0;
    int l[2][2], g[2][2], g_remote[2][2];
    int tStep = 0;

    MPI_Status status;
    int i = 0, partner;
    globalSum[0][0] = 1;
    globalSum[0][1] = 0;
    globalSum[1][0] = 0;
    globalSum[1][1] = 1;

    //copy the entire global to local in the beginning
    copymatrix(globalSum, localSum);

    //step load all the values 
    for(i = 0; i < arraySize; i++)
    {
        myMatrices[i].M[0][0] = A;
        myMatrices[i].M[0][1] = B;
        myMatrices[i].M[1][0] = 0;
        myMatrices[i].M[1][1] = 1;
        
        matrixMultiply(localSum, myMatrices[i].M, localSum, P);
        printf("i = %d %d %d %d %d\n", i, myMatrices[i].M[0][0], myMatrices[i].M[0][1], myMatrices[i].M[1][0], myMatrices[i].M[1][1]);
    }
    printf("rank = %d A = %d B = %d\n", rank, localSum[0][0], localSum[0][1]);


  
    l[0][0] = A;
    l[0][1] = B;
    l[1][0] = 0;
    l[1][1] = 1;
    copymatrix(localSum, g);

    for(tStep = 0; tStep < log2(procs); tStep++)
    {
        partner = getPartner(tStep, rank)
        //if rank > partner 
        if(rank > partner)
        {
            MPI_Send(&g[0][0],4,MPI_INT,partner,0,MPI_COMM_WORLD);
            MPI_Recv(&g_remote,4,MPI_INT,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
        }
        else
        {
            MPI_Recv(&g_remote,4,MPI_INT,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
            MPI_Send(&g[0][0],4,MPI_INT,partner,0,MPI_COMM_WORLD);
        }
        if(partner < rank)
        {
            //calculate l
            matrixMultiply(l, g_remote, l, P);
        }
        //calculate g
        matrixMultiply(g, g_remote, g, P);
    }
    copymatrix(l, localSum);
    
    matrixOutputPar(seed, A, B, localSum[0][0], localSum[0][1], P, arraySize, rank);


}

int main(int argc, char *argv[])
{
    int rank,p;
    int seed, A, B, n, Prime;
    // Init and setup calls
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&p);

    assert(argc == 6);

    seed = atoi(argv[1]);
    A = atoi(argv[2]);
    B = atoi(argv[3]);
    P = atoi(argv[4]);
    n = atoi(argv[5]);

    assert(n > (2 * p));
    assert(n%p == 0);
    ParallelOutput(seed, A, B, P, n, rank, p);


    MPI_Finalize();
}