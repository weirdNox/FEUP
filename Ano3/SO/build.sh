#!/usr/bin/env bash
prevDir=$(pwd)
cd $(dirname "$1")
filename=$(basename "$1")
filename=${filename%.*}
gcc -I"$prevDir" -Wall -Wextra -lm -g "$1" -o "$filename"
