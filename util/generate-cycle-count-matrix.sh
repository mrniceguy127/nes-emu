#!/bin/bash

./prettify-cycle-count-matrix.py <<< $(cat "6502-instructions.csv" | awk -f "expected-cycle-count-generator.awk")
