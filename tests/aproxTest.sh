#!/bin/bash

files="english100MB.txt"              

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
		#for((err=0;err<$wordlen;err++)) do
			err=$((wordlen-one))
			echo -n $err >> "$algo$ext"
			echo -n "$myspace" >> "$algo$ext"
      (time ./pmt -a $algo -e $err -c "$i" $files) 2>> "$algo$ext"
		#done
done < "$patfile"
exit 0

