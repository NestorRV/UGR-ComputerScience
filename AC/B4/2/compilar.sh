#!/bin/bash

gcc $1.c -o $1O0 -O0
gcc $1.c -o $1O2 -O2
gcc $1.c -o $1O3 -O3

gcc $1.c -o $1O0S -O0 -S
gcc $1.c -o $1O2S -O2 -S
gcc $1.c -o $1O3S -O3 -S
