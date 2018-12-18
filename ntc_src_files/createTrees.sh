 #!/bin/bash

cd /home/kevinkeefe/Documents/ntc_data/Tool4Analysis-wTime
make
fileName=""
for fileName in  2018_12_11_Sr90_tranloc_ch1_2.txt;

do

rootName="${fileName##*/}"
rootName=${fileName%.*}
rootName=$rootName.root

echo "creating temporal root file wich contains the data...."
./createTreeData $fileName $rootName

fileName="${fileName##*/}"
fileName=${fileName%.*}
echo $fileName

cp $rootName /home/kevinkeefe/Documents/ntc_data/Tool4Analysis-wTime/rootFiles
cd /home/kevinkeefe/Documents/ntc_data/Tool4Analysis-wTime

echo "Done for $rootName"
done
echo "Good look!!!"

exit
