#!/bin/bash

echo "compiling .."
gcc -fopenmp -std=c99 assignment2_version1.c -o assigv1
gcc -fopenmp -std=c99 assignment2_version2.c -o assigv2

if [ $? -ne 0 ]; then
	echo "Compilation failed!"
	exit 1
fi

echo "Running version 1.."
./assigv1
echo "Running version 2.."
./assigv2
echo "Done."
