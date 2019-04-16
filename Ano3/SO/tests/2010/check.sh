#! /bin/bash

FILES="ppa.c ppb.c ppc.c ppd.c ppe.c ppf.c ppg.c"

for file in $FILES
do
    echo -n "Checking ${file} ..."
    if [ -e $file ]
    then
       echo "present"
    else
       echo "MISSING"
    fi
done