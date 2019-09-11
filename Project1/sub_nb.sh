#!/bin/sh

#To run this script, please use "sbatch -N<numberofnodes> <path>/sub.sh"

# setting the max wallclock time after which the job will be killed; 
# note: the format is hr:min:sec (default set here to 10 mins)
SBATCH --time=00:10:00


#MPI helloworld example - this line is a comment
#"np" stands for number of processes.
#this command will run the job on 8 processes.
n=1

# continue until $n equals 1024
#resource https://bash.cyberciti.biz/guide/While_loop
while [ $n -le 1024 ]
do
	echo "Welcome $n times." > ./nonblocking_files/out$n.txt
    mpirun -np 2 ./proj_1_nonblocking $n > ./nonblocking_files/out$n.txt   
    mpirun -np 2 ./proj_1_nonblocking $n >> ./nonblocking_files/out$n.txt
    mpirun -np 2 ./proj_1_nonblocking $n >> ./nonblocking_files/out$n.txt
    mpirun -np 2 ./proj_1_nonblocking $n >> ./nonblocking_files/out$n.txt
    mpirun -np 2 ./proj_1_nonblocking $n >> ./nonblocking_files/out$n.txt
    mpirun -np 2 ./proj_1_nonblocking $n >> ./nonblocking_files/out$n.txt
    mpirun -np 2 ./proj_1_nonblocking $n >> ./nonblocking_files/out$n.txt
    mpirun -np 2 ./proj_1_nonblocking $n >> ./nonblocking_files/out$n.txt
    mpirun -np 2 ./proj_1_nonblocking $n >> ./nonblocking_files/out$n.txt
    mpirun -np 2 ./proj_1_nonblocking $n >> ./nonblocking_files/out$n.txt
	n=$(( n*2 ))	 # increments $n
done



# for ((i=1;i<=5;i++)); do
#     echo $i
# done
# you can add more lines of commands here, if you wish.

# i do not want to.
