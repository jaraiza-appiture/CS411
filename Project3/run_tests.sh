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
n=16                    #A  B  P          seed

while [ $n -le 1048000 ]    
do
    mpirun -np 1 ./rand_gen $n 5 9 9967 42 >> results.csv
    n=$(( n*2 ))     # increments $n
done
