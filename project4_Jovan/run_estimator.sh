#!/bin/sh

#To run this script, please use "sbatch -N<numberofnodes> <path>/sub.sh"

# setting the max wallclock time after which the job will be killed; 
# note: the format is hr:min:sec (default set here to 10 mins)
SBATCH --time=00:10:00

gcc -o pi_estimator -fopenmp pi_estimator.c -w -lm
# rm results.csv

./pi_estimator 1000000000 1 >> results_test_speed_up.txt
./pi_estimator 1000000000 2 >> results_test_speed_up.txt
./pi_estimator 1000000000 4 >> results_test_speed_up.txt
./pi_estimator 1000000000 8 >> results_test_speed_up.txt

./pi_estimator 125000000 1 >> results_test_precision.txt
./pi_estimator 250000000 2 >> results_test_precision.txt
./pi_estimator 500000000 4 >> results_test_precision.txt
./pi_estimator 1000000000 8 >> results_test_precision.txt
./pi_estimator 2000000000 16 >> results_test_precision.txt
./pi_estimator 4000000000 32 >> results_test_precision.txt


