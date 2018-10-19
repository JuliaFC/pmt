#!/bin/bash

files="5sheakespeare.txt"              

algo="boyer-moore"
wordlen=0
myspace=" "

patfile="pat.txt"
while IFS= read -r i 
do
			TIMEFORMAT=%R
			wordlen=${#i}			 
			echo -n $wordlen >> singleoutput.txt
			echo -n "$myspace" >> singleoutput.txt
      (time ./pmt -a $algo -c "$i" $files) 2>> singleoutput.txt
done < "$patfile"
exit 0

