#!/bin/sh

# SBATCH --time=00:10:00

gcc -o pa4 pa4.c -w -lm -fopenmp

./pa4 1000000000 1 >> result_speedup.txt
./pa4 1000000000 2 >> result_speedup.txt
./pa4 1000000000 4 >> result_speedup.txt
./pa4 1000000000 8 >> result_speedup.txt

./pa4 100000000 1 >> result_precision.txt
./pa4 200000000 2 >> result_precision.txt
./pa4 400000000 4 >> result_precision.txt
./pa4 800000000 8 >> result_precision.txt
./pa4 1000000000 10 >> result_precision.txt
