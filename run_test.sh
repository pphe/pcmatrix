#!/bin/bash
echo "----------------------------------------------------------------------"
echo "Cleaning and remaking..."
echo "----------------------------------------------------------------------"
make clean && make
echo "----------------------------------------------------------------------"
echo

echo "----------------------------------------------------------------------"
echo "Running tests..."
echo "----------------------------------------------------------------------"
echo "Test counter module:"
./counter
echo

echo "Test matrix module:"
./matrix
echo

echo "Test prodcons module:"
./prodcons
echo

echo "Test pcMatrix program:"
for (( i = 1; i <= 100; i++ ))
do
	echo "Iteration #$i:"
	./pcMatrix
	echo
done
echo "----------------------------------------------------------------------"
echo
