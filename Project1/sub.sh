#!/bin/sh

#To run this script, please use "sbatch -N<numberofnodes> <path>/sub.sh"

# setting the max wallclock time after which the job will be killed; 
# note: the format is hr:min:sec (default set here to 10 mins)
SBATCH --time=00:10:00


#MPI helloworld example - this line is a comment
#"np" stands for number of processes.
#this command will run the job on 8 processes.
for i in {1..12}
do
    mpirun -np 2 ./proj_1_blocking i > out$i.txt
    mpirun -np 2 ./proj_1_blocking i >> out$i.txt
    mpirun -np 2 ./proj_1_blocking i >> out$i.txt
    mpirun -np 2 ./proj_1_blocking i >> out$i.txt
    mpirun -np 2 ./proj_1_blocking i >> out$i.txt
    mpirun -np 2 ./proj_1_blocking i >> out$i.txt
    mpirun -np 2 ./proj_1_blocking i >> out$i.txt
    mpirun -np 2 ./proj_1_blocking i >> out$i.txt
    mpirun -np 2 ./proj_1_blocking i >> out$i.txt
    mpirun -np 2 ./proj_1_blocking i >> out$i.txt
done
# you can add more lines of commands here, if you wish.

# i do not want to.
