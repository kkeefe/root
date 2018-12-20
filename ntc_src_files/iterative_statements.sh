#!/bin/bash

# #extremely simple version of variable declaration:
# five=5
# echo $five

# this fills filename with the file names with each of the file types ending in the listed postfixes.
# variable filling and declaration
filename=$(ls *.cpp *.c *.sh)
echo $filename

# #note that this has the same output as filename.. thus, filling it as above creates a single element array
# echo ${filename[0]}

# the for statement
# #however this will iterate over each of the values in $filename as if they're independent objects in the array
# for i in ${filename[@]}
# do
#     echo "ni hao"
# done

#an exampe of iterating through a filled variable and comparing to find a specific string name
for i in $filename
do
    if [ "$i" != "test.sh"  ]
    then
	echo "ni hao two"
    else
	echo "ni hao three"
    fi
done

# #an exampe of iterating through a filled variable and comparing to find a specific string ending
# for i in $filename
# do
#     if [[ "$i" = *".sh" ]] #note that this comparison doesn't work without the double brackets.. ;works equally well with single =, veresus double ==
#     then
# 	echo "match"
#     else
# 	echo "no match"
#     fi
# done

# #an exampe of a case-if statement checking values #this could also be used to store count values for the cases..
# for i in $filename
# do
#     case "$i" in
# 	*".sh")
# 	    echo "shell file"
# 	    ;;
# 	*".cpp")
# 	    echo "cpp file "
# 	    ;;
# 	*".c")
# 	    echo "C root file "
# 	    ;;
#     esac
# done

#the while statement
#observe that let is required to indicate that this is a arithmatic variable..
let var_count=0;
let var_count=var_count+1;

echo $var_count

#alternatively one could use the following..

# var_count=0;
# while [ $var_count -lt 5 ]
# do
#     $var_count+=$var_count + 1
#     echo $var_count
# done

#the until statement
