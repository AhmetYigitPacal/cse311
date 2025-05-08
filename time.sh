#!/bin/bash

ALGORITHMS=("bruteforce" "divideconquer" "strassens")

INPUT_SIZES=(4 8 16 32 64 128 256 512)

RUNS=10

RESULTS_FILE="times.csv"

echo "algorithm,input_size,run_index,time" > $RESULTS_FILE

for algo in "${ALGORITHMS[@]}"; do
    for size in "${INPUT_SIZES[@]}"; do
        for ((run=1; run<=$RUNS; run++)); do
            echo "Multiplying Matrices using $algo with input size $size (run $run) ..."
            
            touch tmp_time.txt

            /usr/bin/time -f "%e" -o tmp_time.txt make run-$algo-$size > /dev/null 2<&1
            
            time_elapsed=$(cat tmp_time.txt);
            
            echo -e "Time it took: $time_elapsed seconds\n"
            echo "$algo,$size,$run,$time_elapsed"  >> $RESULTS_FILE
        done
    done
done

rm tmp_time.txt

echo "All tests completed. Results saved to $RESULTS_FILE"

