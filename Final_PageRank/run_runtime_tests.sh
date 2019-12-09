#!/bin/sh

g++ -o pagerank -fopenmp main.cpp node.h node.cpp
rm results_runtime.csv
echo "Running pagerank on Google..."
echo "1 threads..."
./pagerank web-Google_sorted.txt 500 0.1 1 >> results_runtime.csv
echo "2 threads..."
./pagerank web-Google_sorted.txt 500 0.1 2 >> results_runtime.csv
echo "4 threads..."
./pagerank web-Google_sorted.txt 500 0.1 4 >> results_runtime.csv
echo "8 threads..."
./pagerank web-Google_sorted.txt 500 0.1 8 >> results_runtime.csv

echo "Running pagerank on BerkStan..."
echo "1 threads..."
./pagerank web-BerkStan_sorted.txt 500 0.1 1 >> results_runtime.csv
echo "2 threads..."
./pagerank web-BerkStan_sorted.txt 500 0.1 2 >> results_runtime.csv
echo "4 threads..."
./pagerank web-BerkStan_sorted.txt 500 0.1 4 >> results_runtime.csv
echo "8 threads..."
./pagerank web-BerkStan_sorted.txt 500 0.1 8 >> results_runtime.csv

echo "Running pagerank on NotreDame..."
echo "1 threads..."
./pagerank web-NotreDame_sorted.txt 500 0.1 1 >> results_runtime.csv
echo "2 threads..."
./pagerank web-NotreDame_sorted.txt 500 0.1 2 >> results_runtime.csv
echo "4 threads..."
./pagerank web-NotreDame_sorted.txt 500 0.1 4 >> results_runtime.csv
echo "8 threads..."
./pagerank web-NotreDame_sorted.txt 500 0.1 8 >> results_runtime.csv

echo "Running pagerank on Facebook..."
echo "1 threads..."
./pagerank facebook_combined.txt 500 0.1 1 >> results_runtime.csv
echo "2 threads..."
./pagerank facebook_combined.txt 500 0.1 2 >> results_runtime.csv
echo "4 threads..."
./pagerank facebook_combined.txt 500 0.1 4 >> results_runtime.csv
echo "8 threads..."
./pagerank facebook_combined.txt 500 0.1 8 >> results_runtime.csv
