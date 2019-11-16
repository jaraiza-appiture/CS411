
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <math.h>
#include <assert.h>

int p = 1;


long long double estimatePi(long long int n_darts)
{
	omp_set_num_threads(p);

	long long int i, fraction_in = 0;

    double rand_x, rand_y;
    struct drand48_data rand_buf;

	#pragma omp parallel for shared(n_darts) private(rand_buf, rand_x, rand_y, i) reduction(+:fraction_in)
	for(i = 0; i < n_darts; i++)
	{
		drand48_r(&rand_buf, &rand_x);
		drand48_r(&rand_buf, &rand_y);
		if(sqrt(pow(rand_x-0.5, 2) + pow(rand_y-0.5, 2)) <= 0.5)
			fraction_in++;
	}

	long long double pi = 4.0 * ((long long double)fraction_in/(long long double)n_darts);
	// printf("Fraction In: %d\n", fraction_in);
    // printf("N Darts: %d\n", n_darts);
    // printf("Pi = %f\n", pi);
	return pi;
}

int main(int argc, char *argv[])
{
	int i;
	long long int n;

	// loop {number of iterations} [number of threads]

	if(argc<2) {
		printf("Usage: pi_estimator n_samples num_threads\n");
		exit(1);
	}
	
    n = atoi(argv[1]);

	if(argc==3) {
		p = atoi(argv[2]);
		assert(p>=1);
	}

	omp_set_num_threads(p);

	#pragma omp parallel
	{
		assert(p==omp_get_num_threads());
		int rank = omp_get_thread_num();
	}

	double time = omp_get_wtime();

 	long long double pi = estimatePi(n);
	
	time = omp_get_wtime() - time;

	// pi,samples,threads,runtime
	printf("%0.20llf,%lld,%d,%f\n", pi, n, p, time);

	return 0;
}



