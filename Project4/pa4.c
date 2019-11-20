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

int dartInCircle(double x_rand, double y_rand)
{
    double sq_x_rand = (x_rand) * (x_rand);
    double sq_y_rand  = (y_rand) * (y_rand);

    double result = sqrt(sq_x_rand + sq_y_rand);
    //printf("result %f \n", result);
    if (result <= 1.0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
    
}
double myPiEstimator(int n, int p) {


	omp_set_num_threads(p);

	double total_hits=0;
    double x_rand, y_rand;
    int i;
	#pragma omp parallel for  reduction(+:total_hits) private (i, x_rand, y_rand)
	for(i=0; i<n; i++) {

        struct drand48_data *drand48_same_buffer;
        int rank = omp_get_thread_num(); 
        int seed = rank +1;
        seed =seed *i;
        //to initilize the struct
        srand48_r(seed, &drand48_same_buffer);
        drand48_r(&drand48_same_buffer, &x_rand);
        drand48_r(&drand48_same_buffer, &y_rand);
		// printf("x_rand=%2f\ny_rand=%2f\n", x_rand, y_rand);
        if (dartInCircle(x_rand, y_rand) == 1)
        {
            total_hits +=1;
        }

	}
        printf("total_hits %f", total_hits);

    return 4.0*(double)total_hits / (double)n;


}


int main(int argc, char *argv[])
{
	int i;
	int n;
    int p;
	if(argc<2) {
		printf("Usage: sumcomp {array size} [number of threads]\n");
		exit(1);
	}
	
	n = atoll(argv[1]);
	// printf("Debug: array size = %d \n",n);

	if(argc==3) {
		p = atoi(argv[2]);
		assert(p>=1);
		printf("number of requested threads = %d\n",p);
        printf("number of requested n = %d\n",n);

	}


	double time = omp_get_wtime();


    printf("pi value %f \n\n", myPiEstimator(n,p));

	
	time = omp_get_wtime() - time;
	printf("Total time = %f seconds \n ", time);

	return 0;
}
