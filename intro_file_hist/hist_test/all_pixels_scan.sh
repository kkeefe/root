#!/bin/bash

# this fills $filename with the the files ending in the listed post fixes
# variable filling and declaration
filename=$(ls *.txt)
echo $filename

#an exampe of a case-if statement checking values #this could also be used to store count values for the cases..
for i in $filename
do
    #if you want to erase all of the first lines of a file perform:
    #tail -n +2 $filename > "tmp.txt" && mv "tmp.txt" $filename

    case "$i" in
	*".txt") #for any file that is a txt file
	    echo "creating root file from: $i"
	    #this passes the i arguement to the root command..
        #want to run: "create_root.cc(\"file_name\")"
	    root -l -q -b "create_root.cc(\"$i\")"
	    ;;
    esac
done

## script to run the iterate function over all of the different root files in a particular directory..
# rootname=$(ls *.root)
# echo $rootname
# #an exampe of a case-if statement checking values #this could also be used to store count values for the cases..
# for i in $rootname
# do
#     case "$i" in
# 	*".root") #for any file that is a root file
# 	    echo "creating root file from: $i"
# 	    #this passes the i arguement to the root command..
#         #want to run: "create_root.cc(\"file_name\")"
# 	    root -l -q -b "fill_hist_from_file.cc(\"$i\")"
# 	    ;;
#     esac
# done