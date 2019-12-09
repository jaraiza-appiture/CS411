#!/bin/sh

g++ -o pagerank -fopenmp main.cpp node.h node.cpp
rm results_parametric_k.csv
echo "Running pagerank on Google..."
echo "K = 100..."
./pagerank web-Google_sorted.txt 100 0.1 8 >> results_parametric_k.csv
echo "K = 200..."
./pagerank web-Google_sorted.txt 200 0.1 8 >> results_parametric_k.csv
echo "K = 400..."
./pagerank web-Google_sorted.txt 400 0.1 8 >> results_parametric_k.csv
echo "K = 800..."
./pagerank web-Google_sorted.txt 800 0.1 8 >> results_parametric_k.csv
echo "K = 1600..."
./pagerank web-Google_sorted.txt 1600 0.1 8 >> results_parametric_k.csv
echo "K = 3200..."
./pagerank web-Google_sorted.txt 3200 0.1 8 >> results_parametric_k.csv

echo "Running pagerank on BerkStan..."
echo "K = 100..."
./pagerank web-BerkStan_sorted.txt 100 0.1 8 >> results_parametric_k.csv
echo "K = 200..."
./pagerank web-BerkStan_sorted.txt 200 0.1 8 >> results_parametric_k.csv
echo "K = 400..."
./pagerank web-BerkStan_sorted.txt 400 0.1 8 >> results_parametric_k.csv
echo "K = 800..."
./pagerank web-BerkStan_sorted.txt 800 0.1 8 >> results_parametric_k.csv
echo "K = 1600..."
./pagerank web-BerkStan_sorted.txt 1600 0.1 8 >> results_parametric_k.csv
echo "K = 3200..."
./pagerank web-BerkStan_sorted.txt 3200 0.1 8 >> results_parametric_k.csv

echo "Running pagerank on NotreDame..."
echo "K = 100..."
./pagerank web-NotreDame_sorted.txt 100 0.1 8 >> results_parametric_k.csv
echo "K = 200..."
./pagerank web-NotreDame_sorted.txt 200 0.1 8 >> results_parametric_k.csv
echo "K = 400..."
./pagerank web-NotreDame_sorted.txt 400 0.1 8 >> results_parametric_k.csv
echo "K = 800..."
./pagerank web-NotreDame_sorted.txt 800 0.1 8 >> results_parametric_k.csv
echo "K = 1600..."
./pagerank web-NotreDame_sorted.txt 1600 0.1 8 >> results_parametric_k.csv
echo "K = 3200..."
./pagerank web-NotreDame_sorted.txt 3200 0.1 8 >> results_parametric_k.csv

echo "Running pagerank on Facebook..."
echo "K = 100..."
./pagerank facebook_combined.txt 100 0.1 8 >> results_parametric_k.csv
echo "K = 200..."
./pagerank facebook_combined.txt 200 0.1 8 >> results_parametric_k.csv
echo "K = 400..."
./pagerank facebook_combined.txt 400 0.1 8 >> results_parametric_k.csv
echo "K = 800..."
./pagerank facebook_combined.txt 800 0.1 8 >> results_parametric_k.csv
echo "K = 1600..."
./pagerank facebook_combined.txt 1600 0.1 8 >> results_parametric_k.csv
echo "K = 3200..."
./pagerank facebook_combined.txt 3200 0.1 8 >> results_parametric_k.csv
