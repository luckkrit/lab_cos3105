#!/bin/bash

export BONUS=0.2

gcc bonus.c -o bonus

mkdir -p results
for file in salary/*.txt; do
    filename=$(basename "$file" .txt)
    ./bonus < "$file" > "results/${filename}_result.txt"
    echo "Processed $file -> results/${filename}_result.txt (exit code: $?)"
done

echo "--- Summary ---"
total_employees=$(cat results/*.txt | wc -l)
echo "Total employees processed: $total_employees"