#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <math.h>
#include <assert.h>



struct drand48_data drand48_same_buffer;

double getRandDouble() {
    double num;
    drand48_r(&drand48_same_buffer, &num);
    return num;
}

double myPiEstimator(int n, int p) {


	// omp_set_num_threads(p);

	int i;
	int sum=0;
    double x_rand, y_rand;

	// #pragma omp parallel for shared(a,n) reduction(+:sum) 
	for(i=0;i<10;i++) {
        x_rand = getRandDouble();
        y_rand = getRandDouble();

		printf("x_rand=%2f, y_rand=%2f", x_rand, y_rand);

	}


}


int main(int argc, char *argv[])
{
	int i;
	int n;
    int p;
    myPiEstimator();
	if(argc<2) {
		printf("Usage: sumcomp {array size} [number of threads]\n");
		exit(1);
	}
	
	n = atoll(argv[1]);
	printf("Debug: array size = %d \n",n);

	if(argc==3) {
		p = atoi(argv[2]);
		assert(p>=1);
		printf("Debug: number of requested threads = %d\n",p);
	}

	omp_set_num_threads(p);

	#pragma omp parallel
	{
		assert(p==omp_get_num_threads());
		//printf("Debug: number of threads set = %d\n",omp_get_num_threads());

		int rank = omp_get_thread_num();
		printf("Rank=%d: my world has %d threads\n",rank,p);
	}  // end of my omp parallel region

	double time = omp_get_wtime();




	
	time = omp_get_wtime() - time;
	printf("Total time = %f seconds \n ", time);

	return 0;
}
