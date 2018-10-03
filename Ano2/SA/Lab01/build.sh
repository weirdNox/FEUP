#!/usr/bin/env sh
cd $(dirname "$1")
filename=$(basename "$1")

flags="--verify"
if [ "$2" == "upload" ] ; then flags="--upload" ; fi

arduino $flags $filename
