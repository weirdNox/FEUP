#!/usr/bin/env bash
cd $(dirname "$1")
filename=$(basename "$1")
filename=${filename%.*}
gcc -Wall -Wextra -lm -g "$1" -o "$filename"
