SBATCH --time=00:10:00
g++ -o pagerank pagerank.c -w -lm -fopenmp
./pagerank 0.4 8 100 >> changeK.txt
