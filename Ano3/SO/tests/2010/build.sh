#!/usr/bin/env sh
for File in pp*.c
do
    cc -Wall -D_REENTRANT ${File} util.c -lpthread -o $(basename "$File" .c)
done
