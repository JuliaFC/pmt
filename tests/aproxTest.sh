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
		for((err=0;err<$wordlen;++err)) do			
			echo -n $err >> wumanberoutput.txt
			echo -n "$myspace" >> wumanberoutput.txt
      (time ./pmt -a $algo -e $err -c "$i" $files) 2>> wumanberoutput.txt
		done
done < "$patfile"
exit 0

