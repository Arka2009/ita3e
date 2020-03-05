#!/bin/bash


gcc matmul.c -o test
echo "Cycles for matmul" > matmul_cycles.txt
for cpu in $(seq 0 1 63); do
  echo "Pinned on CPU@${cpu}"
  perf stat -e cycles -r 10 taskset -c ${cpu} ./test
done
