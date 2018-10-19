#!/bin/bash

files="5sheakespeare.txt"              
echo $files >> timebm.txt
declare -a words=("he" "she" "his" "hers")
algo="boyer-moore"

for i in ${words[@]}; do
			 echo "word:" $i >> output.txt
			TIMEFORMAT=%R
      (time ./pmt -a $algo -c $i $files) 2>> output.txt

done
exit 0

