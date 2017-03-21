#!/usr/bin/env bash
cd "$(dirname "$0")"
clang -Wall -lm -g vetor-teste.c vetorg.c vetor.c -o vetor-teste
