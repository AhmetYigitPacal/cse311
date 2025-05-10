#!/bin/bash

ALGORITHMS=("bruteforce" "divideconquer" "strassens")
INPUT_SIZES=(4 8 16 32 64 128 256 512)
RUNS=5

rm times.csv

for ((size=2; size<=1024; size*=2)); do
  for ((run=1; run<=$RUNS; run++)); do
    make run-bruteforce-$size
    echo ""
  done
done

for ((size=2; size<=512; size*=2)); do
  for ((run=1; run<=$RUNS; run++)); do
    make run-divideconquer-$size
    echo ""
  done
done

for ((size=2; size<=512; size*=2)); do
  for ((run=1; run<=$RUNS; run++)); do
    make run-strassens-$size
    echo ""
  done
done

echo "Finished timing algorithms. Results written to times.csv"
