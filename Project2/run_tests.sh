#!/bin/sh

#To run this script, please use "sbatch -N<numberofnodes> <path>/sub.sh"

# setting the max wallclock time after which the job will be killed; 
# note: the format is hr:min:sec (default set here to 10 mins)
SBATCH --time=00:10:00


#MPI helloworld example - this line is a comment
#"np" stands for number of processes.
#this command will run the job on 8 processes.
mpicc -o reduction reduction.c -w -lm
rm results.csv
n=1000
while [ $n -le 1000000 ]
do
    mpirun -np 1 ./reduction $n >> results.csv 
    mpirun -np 2 ./reduction $n >> results.csv        
    mpirun -np 4 ./reduction $n >> results.csv        
    mpirun -np 8 ./reduction $n >> results.csv        
    mpirun -np 16 ./reduction $n >> results.csv        
    mpirun -np 32 ./reduction $n >> results.csv        
    mpirun -np 64 ./reduction $n >> results.csv        
    n=$(( n*2 ))     # increments $n
done
