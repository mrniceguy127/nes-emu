#!/bin/sh

./prettify-matrix.py <<< $(cat "6502-instructions.csv" | awk -f "instruction-matrix-generator.awk")
