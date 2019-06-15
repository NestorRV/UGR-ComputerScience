#!/bin/bash

for ((N=1;N<5;N=N+1))
do
   export OMP_NUM_THREADS=$N
   ./9-pmv-OpenMP-a_O2 1000
done

for ((N=1;N<5;N=N+1))
do
   export OMP_NUM_THREADS=$N
   ./9-pmv-OpenMP-a_O2 100000
done
