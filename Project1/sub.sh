#!/bin/sh

#To run this script, please use "sbatch -N<numberofnodes> <path>/sub.sh"

# setting the max wallclock time after which the job will be killed; 
# note: the format is hr:min:sec (default set here to 10 mins)
SBATCH --time=00:10:00

for i in {1..1024..2}
    do
        mpirun -np 2 ./proj_1_blocking $i > out$i.txt
        for j in {1..9..1}
            do
                mpirun -np 2 ./proj_1_blocking $i >> out$i.txt
            done
    done