#!/bin/bash

rm spikes.txt
rm nbSpikes.txt

cmake .
make
./unittest
./neuron

python graph.py
