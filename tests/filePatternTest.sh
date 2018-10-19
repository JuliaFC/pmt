#!/bin/bash

files="5sheakespeare.txt"              
patfile="pat.txt"
declare -a words=("he" "she" "his" "hers")
algo="boyer-moore"

TIMEFORMAT=%R
(time ./pmt -a $algo -c -p $patfile $files) 2>> fileoutput.txt

exit 0

