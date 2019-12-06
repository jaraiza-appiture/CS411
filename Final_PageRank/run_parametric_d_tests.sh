#!/bin/sh

g++ -o pagerank -fopenmp main.cpp node.h node.cpp
rm results_paramteric_d.csv
echo "Running pagerank on Google..."
echo "D = 0.1..."
./pagerank web-Google_sorted.txt 500 0.1 8 >> results_paramteric_d.csv
echo "D = 0.3..."
./pagerank web-Google_sorted.txt 500 0.3 8 >> results_paramteric_d.csv
echo "D = 0.5..."
./pagerank web-Google_sorted.txt 500 0.5 8 >> results_paramteric_d.csv
echo "D = 0.7..."
./pagerank web-Google_sorted.txt 500 0.7 8 >> results_paramteric_d.csv
echo "D = 0.9..."
./pagerank web-Google_sorted.txt 500 0.9 8 >> results_paramteric_d.csv

echo "Running pagerank on BerkStan..."
echo "D = 0.1..."
./pagerank web-BerkStan_sorted.txt 500 0.1 8 >> results_paramteric_d.csv
echo "D = 0.3..."
./pagerank web-BerkStan_sorted.txt 500 0.3 8 >> results_paramteric_d.csv
echo "D = 0.5..."
./pagerank web-BerkStan_sorted.txt 500 0.5 8 >> results_paramteric_d.csv
echo "D = 0.7..."
./pagerank web-BerkStan_sorted.txt 500 0.7 8 >> results_paramteric_d.csv
echo "D = 0.9..."
./pagerank web-BerkStan_sorted.txt 500 0.9 8 >> results_paramteric_d.csv

echo "Running pagerank on NotreDame..."
echo "D = 0.1..."
./pagerank web-NotreDame_sorted.txt 500 0.1 8 >> results_paramteric_d.csv
echo "D = 0.3..."
./pagerank web-NotreDame_sorted.txt 500 0.3 8 >> results_paramteric_d.csv
echo "D = 0.5..."
./pagerank web-NotreDame_sorted.txt 500 0.5 8 >> results_paramteric_d.csv
echo "D = 0.7..."
./pagerank web-NotreDame_sorted.txt 500 0.7 8 >> results_paramteric_d.csv
echo "D = 0.9..."
./pagerank web-NotreDame_sorted.txt 500 0.9 8 >> results_paramteric_d.csv

echo "Running pagerank on Facebook..."
echo "D = 0.1..."
./pagerank facebook_combined.txt 500 0.1 8 >> results_paramteric_d.csv
echo "D = 0.3..."
./pagerank facebook_combined.txt 500 0.3 8 >> results_paramteric_d.csv
echo "D = 0.5..."
./pagerank facebook_combined.txt 500 0.5 8 >> results_paramteric_d.csv
echo "D = 0.7..."
./pagerank facebook_combined.txt 500 0.7 8 >> results_paramteric_d.csv
echo "D = 0.9..."
./pagerank facebook_combined.txt 500 0.9 8 >> results_paramteric_d.csv

