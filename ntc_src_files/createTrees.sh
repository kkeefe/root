 #!/bin/bash

# go the directory where the ntc data text files are stored..

echo "make sure you performed make on your new files.."

cd ~/Documents/ntc_data_files/

fileName=""
for fileName in  2018_12_13_Sr90_tranloc_ch1_2_3_4_OR.txt 2018_12_13_Sr90_Tranloc_abridged_reverse_Ch1_2_3_4_OR.txt;

do
rootName="${fileName##*/}"
rootName=${fileName%.*}
rootName=$rootName.root

echo "creating temporal root file wich contains the data...."
pwd
~/Documents/root/ntc_src_files/createTreeData $fileName $rootName

fileName="${fileName##*/}"
fileName=${fileName%.*}
echo $fileName

cp $rootName ~/Documents/ntc_data_files/Tool4Analysis-wTime/rootFiles
cd ~/Documents/ntc_data_files/Tool4Analysis-wTime

echo "Done for $rootName"
done
echo "Good look!!!"

exit
