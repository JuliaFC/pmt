#!/bin/bash

files="english1024MB.txt"              

wordlen=0
myspace=" "

patfile="pat.txt"
while IFS= read -r i 
do
			TIMEFORMAT=%R
			wordlen=${#i}			 
			echo -n $wordlen >> singlegrepoutput.txt
			echo -n "$myspace" >> singlegrepoutput.txt
      (time grep "$i" -c $files) 2>> singlegrepoutput.txt
done < "$patfile"
exit 0

