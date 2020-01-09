#!/bin/bash

grep '<td>.*</td>' | #gets only words
sed 's/<td><\/td>//g' | #removes empty words
sed '/^\s*$/d' | #removes blank lines
sed -n '0~2p' |    #gets only hawaiian words
sed 's/<[^>]*>//g' | #removes all html tags
sed 's/^\s*//g;s/\s*$//g' | #removes leading and tailing spaces
sed 's/ /\n/g' |    #replaces spaces in words with new lines
sed "s/\`/\'/g" | #replaces ` with '
sed 's/,//g' | #gets rid of commas
tr [:upper:] [:lower:] | #converts upper to lower
tr -cs "pk\'mnwlhaeiou" '[\n*]' | #gets rid of words with non hawaiian chars
sort -u #sorts and removes duplicates
