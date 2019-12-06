#!/bin/sh

g++ -o pagerank -fopenmp main.cpp node.h node.cpp
rm results_scaling.csv

echo "Running Pagerank on NotreDame..."
echo "K = 100 p = 1..."
./pagerank web-NotreDame_sorted.txt 100 0.1 1 >> results_scaling.csv
echo "K = 200 p = 1..."
./pagerank web-NotreDame_sorted.txt 200 0.1 1 >> results_scaling.csv
echo "K = 400 p = 1..."
./pagerank web-NotreDame_sorted.txt 400 0.1 1 >> results_scaling.csv
echo "K = 800 p = 1..."
./pagerank web-NotreDame_sorted.txt 800 0.1 1 >> results_scaling.csv
echo "K = 1600 p = 1..."
./pagerank web-NotreDame_sorted.txt 1600 0.1 1 >> results_scaling.csv
echo "K = 3200 p = 1..."
./pagerank web-NotreDame_sorted.txt 3200 0.1 1 >> results_scaling.csv

echo "K = 100 p = 2..."
./pagerank web-NotreDame_sorted.txt 100 0.1 2 >> results_scaling.csv
echo "K = 200 p = 2..."
./pagerank web-NotreDame_sorted.txt 200 0.1 2 >> results_scaling.csv
echo "K = 400 p = 2..."
./pagerank web-NotreDame_sorted.txt 400 0.1 2 >> results_scaling.csv
echo "K = 800 p = 2..."
./pagerank web-NotreDame_sorted.txt 800 0.1 2 >> results_scaling.csv
echo "K = 1600 p = 2..."
./pagerank web-NotreDame_sorted.txt 1600 0.1 2 >> results_scaling.csv
echo "K = 3200 p = 2..."
./pagerank web-NotreDame_sorted.txt 3200 0.1 2 >> results_scaling.csv

echo "K = 100 p = 4..."
./pagerank web-NotreDame_sorted.txt 100 0.1 4 >> results_scaling.csv
echo "K = 200 p = 4..."
./pagerank web-NotreDame_sorted.txt 200 0.1 4 >> results_scaling.csv
echo "K = 400 p = 4..."
./pagerank web-NotreDame_sorted.txt 400 0.1 4 >> results_scaling.csv
echo "K = 800 p = 4..."
./pagerank web-NotreDame_sorted.txt 800 0.1 4 >> results_scaling.csv
echo "K = 1600 p = 4..."
./pagerank web-NotreDame_sorted.txt 1600 0.1 4 >> results_scaling.csv
echo "K = 3200 p = 4..."
./pagerank web-NotreDame_sorted.txt 3200 0.1 4 >> results_scaling.csv

echo "K = 100 p = 8..."
./pagerank web-NotreDame_sorted.txt 100 0.1 8 >> results_scaling.csv
echo "K = 200 p = 8..."
./pagerank web-NotreDame_sorted.txt 200 0.1 8 >> results_scaling.csv
echo "K = 400 p = 8..."
./pagerank web-NotreDame_sorted.txt 400 0.1 8 >> results_scaling.csv
echo "K = 800 p = 8..."
./pagerank web-NotreDame_sorted.txt 800 0.1 8 >> results_scaling.csv
echo "K = 1600 p = 8..."
./pagerank web-NotreDame_sorted.txt 1600 0.1 8 >> results_scaling.csv
echo "K = 3200 p = 8..."
./pagerank web-NotreDame_sorted.txt 3200 0.1 8 >> results_scaling.csv
