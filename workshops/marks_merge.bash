#!/bin/bash

cat <(tail -n +2 "$1") <(tail -n +2 "$2") > numbers #starting with line 2 on both files, concatenate both files together
cut -d "," -f 1 numbers > n #cut everything after "," in numbers, and redirect to n
sort n | uniq > numbers #sort n, then pipe to uniq to filter out repetitions, then redirect to n
field1=$(cut -d "," -f 2 <(head -n 1 "$1")) #prac_mar
field1=${field1:0:${#field1}-1} #remove newline char from end of string
field2=$(cut -d "," -f 2 <(head -n 1 "$2")) #exam_mar
field2=${field2:0:${#field2}-1} #remove newline char from end of string
content="number,$field1,$field2" #content = "number, prac_mar, exam_mar"
content+=$'\r' #add newline char after header
while IFS= read -r line #IFS is field separator, -r ignores backslash \ characters so IFS is a failsafe for reading txt files
do
  value1="-" #default value is - (no mark)
  if [[ $(grep -c $line $1) -gt 0 ]] # if number of lines in first file is greater than 0
  then
    value1=$(grep $line $1) # look for number matching line in file 1 and set to value 1
    value1=${value1:${#line}+1}
  fi
  value2=$'- \r' # default value is - + newline
  if [[ $(grep -c $line $2) -gt 0 ]]
  then
    value2=$(grep $line $2)
    value2=${value2:${#line}+1}
    value2+=$'\r'
  fi
  content+="$line,$value1,$value2" # add values to content

done < numbers # read numbers
echo "$content" | tee output.txt # pipe output to log.txt
