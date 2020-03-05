#!/bin/bash

clang -I. -O0 -g -c sum.c
clang -I. -O0 -g -c main.c
clang main.o sum.o -o test7
#clang -I. -O0 -g main.c sum.c -o test7