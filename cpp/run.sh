#!/bin/bash

# Full file path as argument
fpath=$1

# Check if argument is provided
if [ -z "$fpath" ]; then
  echo "Usage: $0 <path-to-file>"
  exit 1
fi

# Extract filename without directory and extension
fname=$(basename "$fpath" .cpp)

# Build using make
make file="$fpath"

clear; clear;

# Run the output
./build/"$fname"
