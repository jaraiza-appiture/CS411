#!/bin/sh

#To run this script, please use "sbatch -N<numberofnodes> <path>/sub.sh"

# setting the max wallclock time after which the job will be killed; 
# note: the format is hr:min:sec (default set here to 10 mins)
SBATCH --time=00:10:00


#MPI helloworld example - this line is a comment
#"np" stands for number of processes.
#this command will run the job on 8 processes.
mpicc -o proj_1_blocking proj_1_blocking.c -w
rm ./blocking_files/outAll.txt

# continue until $n equals 1024
# resource https://bash.cyberciti.biz/guide/While_loop
# Doing 20 tests per byte size sent
n=1
while [ $n -le 8192 ]
do
    # m=1
    # while [ $m -le 10]
    # do
    #     mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    #     m=$((m+1))
    # done
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt 
	mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt
    mpirun -np 2 ./proj_1_blocking $n >> ./blocking_files/outAll.txt 
	
    n=$(( n*2 ))	 # increments $n
done


# for ((i=1;i<=5;i++)); do
#     echo $i
# done
# you can add more lines of commands here, if you wish.

# i do not want to.
