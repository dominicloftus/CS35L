#!/bin/bash

grep '<td>.\{1,\}<\/td>' | \
sed -n '1~2!p' - | \
tr "A-Z\`" "a-z\'" | \
sed 's/<td>//g;s/<\/td>//g;s/<u>//g;s/<\/u>//g' | \
sed "s/^\s*//g" | \
sed -E "s/,\s|\s/\n/g" | \
grep "^[pk\' mnwlhaeiou]\{1,\}$"
sort -u
