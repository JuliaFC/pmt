#!/bin/bash

files="english50MB.txt"              

algo="wu-manber"
wordlen=0
myspace=" "
one=1
patfile="pat.txt"
while IFS= read -r i 
do
			TIMEFORMAT=%R
			wordlen=${#i}			 
			err=$((wordlen - one))
			echo -n $wordlen >> sellersoutput.txt
			echo -n "$myspace" >> sellersoutput.txt
      (time ./pmt -a $algo -e $err -c "$i" $files) 2>> sellersoutput.txt
done < "$patfile"
exit 0

