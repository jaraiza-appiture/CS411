#!/bin/sh
#SBATCH --time=00:10:00
mpicc -o palgorithm palgorithm.c -lm
                     //  A   B     Prime seed n 
mpirun -np 2 ./palgorithm 2069 3069 9973 10 8 >> ./.out

// n=$1
// i=$n

// while [ $i -le 1048576 ]
// do
//                         //  A   B     Prime seed n 
//     mpirun -np $n ./parallel 127 2897 880681 1 $i >> ./.out
//     i=$((i*2))
// done
    // A = atoi(argv[1]);
    // B = atoi(argv[2]);
    // Prime = atoi(argv[3]);
    // seed = atoi(argv[4]);
    // n = atoi(argv[5]);
    //  A = 2069;
    // B = 3069;
    // Prime = 9973;
    // seed = 10;
    // n = 8;
