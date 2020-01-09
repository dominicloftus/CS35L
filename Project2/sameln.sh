\#!/bin/bash

d=$1

dir=`ls -A $d | sort`

declare -a farray

let count=0

orig="$IFS"
IFS=$'\n'


for fg in $dir
do
    if [ -L "$d/$fg" ] || [ -d "$d/$fg" ]
    then
	continue
    elif [ ! -f "$d/$fg" ]
    then
	continue
    elif [ ! -r "$d/$fg" ]
    then
	echo "$fg read permission denied"
	continue
    fi
    farray[$count]="$d/$fg"
    let count=count+1
done

for (( i=0; i < $count; i++ ))
do
    for (( j=i+1; j<$count; j++ ))
    do
	cmp -s "${farray[$i]}" "${farray[$j]}"
	if [ $? -eq 0 ]
	then
	    echo "${farray[$i]} ${farray[$j]}"
	    if [[ ${farray[$i]} == \.* ]]
	    then
		ln -fP "${farray[$i]}" "${farray[$j]}"
		farray[$j]=farray[$i]
	    elif [[ ${farray[$j]} == \.* ]]
	    then
		ln -fP "${farray[$j]}" "${farray[$i]}"
		farray[$i]=farray[$j]
	    else
		ln -fP "${farray[$i]}" "${farray[$j]}"
		farray[$j]=farray[$i]
	    fi
	fi
    done
done

	    
		





    
