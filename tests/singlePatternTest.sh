#!/bin/bash

files="english1024MB.txt"              

read algo
ext="output.txt"
wordlen=0
myspace=" "
one=1
patfile="pat.txt"
while IFS= read -r i 
do
			TIMEFORMAT=%R
			wordlen=${#i}			 
			echo -n $wordlen >> "$algo$ext"
			echo -n "$myspace" >> "$algo$ext"
      (time ./pmt -a $algo -c "$i" $files) 2>> "$algo$ext"
done < "$patfile"
exit 0

