#!/bin/sh
SBATCH --time=00:10:00
mpicc -o parallel parallel.c -lm
mpirun -np $n ./parallel 1 10 10 109 1 >> ./parallel.out

// n=$1
// i=$n
// while [ $i -le 1048576 ]
// do
//     i=$((i*2))
// done
