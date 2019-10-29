#!/bin/sh

#To run this script, please use "sbatch -N<numberofnodes> <path>/sub.sh"

# setting the max wallclock time after which the job will be killed; 
# note: the format is hr:min:sec (default set here to 10 mins)
SBATCH --time=00:10:00


#MPI helloworld example - this line is a comment
#"np" stands for number of processes.
#this command will run the job on 8 processes.
mpicc -o rand_gen rand_gen.c -w -lm
rm results.csv
n=1000
mpirun -np 1 ./rand_gen 10 49 21 9999999967 42 >> results.csv        

# while [ $n -le 2048000 ]    
# do
#     mpirun -np 1 ./reduction $n >> results.csv
    
#     n=$(( n*2 ))     # increments $n
# done
