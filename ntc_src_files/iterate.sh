#!/bin/bash

# this fills filename with the file names with each of the file types ending in the listed postfixes.
# variable filling and declaration
filename=$(ls *Angle*.root)
echo $filename

# #note that this has the same output as filename.. thus, filling it as above creates a single element array
# echo ${filename[0]}

#an exampe of a case-if statement checking values #this could also be used to store count values for the cases..
for i in $filename
do
    case "$i" in
	*".root")
	    echo "root file: $i"
	    #this passes the i arguement to the root command..
	    root -b -l -q $i Analysis.C
	    #place the newly created png file with the appropriate name..
	    mv ntup.png ./png_files/$i.png 
	    ;;
    esac
done

# move some stuff to the desktop that you just created..
cp ./png_files/*.png /mnt/c/Users/kkeefe/Desktop/pngfile/

