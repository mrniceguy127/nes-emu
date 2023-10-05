#!/bin/bash

./prettify-matrix.py <<< $(cat "6502-instructions.csv" | awk -F "instruction-matrix-generator.awk")
