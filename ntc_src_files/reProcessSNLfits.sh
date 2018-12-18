#!/bin/bash

#This is a tool for obtaining final result test from a one set-up acquisition. Uses all the files in  this folder, so please don't get ride of any of them.

#cd /home/kevinkeefe/Documents/ntc_data/Tool4AnalysisCutted/Temporalfolder
#rm -rf *
cd /home/kevinkeefe/Documents/ntc_data/Tool4AnalysisCutted

EJ200=(2018_08_27_Sr90_EJ200B_1.root 2018_08_28_Sr90_EJ200C_1.root 2018_08_28_Sr90_EJ200D_1.root 2018_08_27_Sr90_EJ200A_1.root)
#EJ204=(2018_10_09_Sr90_EJ204-A.root 2018_10_09_Cs137_EJ204-A.root 2018_10_10_Cs137_EJ204-A_excSiGrs.root 2018_10_10_EJ204-A_excSiGrs.root)
EJ204=(2018_08_28_Sr90_EJ204C_1.root 2018_08_27_Sr90_EJ204A_1.root 2018_08_27_Sr90_EJ204B_1.root 2018_08_28_Sr90_EJ204D_1.root)
EJ230=(2018_08_27_Sr90_EJ230A_1.root 2018_08_28_Sr90_EJ230B_1.root 2018_08_28_Sr90_EJ230C_1.root 2018_08_28_Sr90_EJ230D_1.root)
EJ276=(2018_08_27_Sr90_EJ276A_1.root 2018_08_28_Sr90_EJ276B_1.root 2018_08_28_Sr90_EJ276C_1.root 2018_08_28_Sr90_EJ276D_1.root)
EJ200Teflon=(2018_09_07_Sr90_EJ200D_Teflon_1.root)
EJ204Teflon=(2018_09_07_Sr90_EJ204D_Teflon_1.root)
EJ230Teflon=(2018_09_07_Sr90_EJ230D_Teflon_1.root)
EJ276Teflon=(2018_09_07_Sr90_EJ276C_Teflon_1.root)
EJ200ESR=(2018_08_29_Sr90_EJ200C_ESR1_1.root 2018_08_29_Sr90_EJ200D_ESR1_1.root)
EJ204ESR=(2018_08_28_Sr90_EJ204C_ESR_1.root 2018_08_28_Sr90_EJ204C_ESR2_1.root 2018_08_28_Sr90_EJ204C_ESR3_1.root 2018_08_29_Sr90_EJ204D_ESR1_1.root)
EJ230ESR=(2018_08_29_Sr90_EJ230B_ESR1_1.root 2018_08_29_Sr90_EJ230B_ESR1_2.root 2018_08_29_Sr90_EJ230D_ESR1_1.root)
EJ276ESR=(2018_08_30_Sr90_EJ276B_ESR1_1.root 2018_08_30_Sr90_EJ276C_ESR1_1.root)

b=""
a=""

echo "Wait a moment please.....Generating the executables...."
make
fileName=""
for fileName in "${EJ200[@]}" "${EJ200Teflon[@]}" "${EJ200ESR[@]}" "${EJ204[@]}" "${EJ204Teflon[@]}" "${EJ204ESR[@]}" "${EJ230[@]}"  "${EJ230Teflon[@]}"  "${EJ230ESR[@]}";
do

#"${EJ200Teflon[@]}" "${EJ204Teflon[@]}"; do

#"${EJ276[@]}" "${EJ276Teflon[@]}"  "${EJ204[@]}"  "${EJ276ESR[@]}"; do
# "${EJ204[@]}"  "${EJ200[@]}"    "${EJ204Teflon[@]}"     "${EJ204ESR[@]}" "${EJ230ESR[@]}" "${EJ230Teflon[@]}""${EJ200Teflon[@]}" "${EJ200ESR[@]}""${EJ204[@]}"; do


#
# "${EJ276Teflon[@]}" "${EJ276[@]}" 
 
FINDME=$fileName
FOUND1=`echo ${EJ200[*]} | grep "$FINDME"`
if [ "${FOUND1}" != "" ]; then
  echo Array contains: $FINDME
a=0.0101034
#a=40.28
b=0.0152201
fi

FOUND2=`echo ${EJ204[*]} | grep "$FINDME"`
if [ "${FOUND2}" != "" ]; then
  echo Array contains: $FINDME
a=0.00877591
b=-0.0135142
fi

FOUND3=`echo ${EJ230[*]} | grep "$FINDME"`
if [ "${FOUND3}" != "" ]; then
  echo Array contains: $FINDME
a=0.0104311
b=0.0136448
fi

FOUND4=`echo ${EJ276[*]} | grep "$FINDME"`
if [ "${FOUND4}" != "" ]; then
  echo Array contains: $FINDME
fi

FOUND11=`echo ${EJ200Teflon[*]} | grep "$FINDME"`
if [ "${FOUND11}" != "" ]; then
  echo Array contains: $FINDME
a=0.0111456
b=-0.00374667
fi

FOUND21=`echo ${EJ204Teflon[*]} | grep "$FINDME"`
if [ "${FOUND21}" != "" ]; then
  echo Array contains: $FINDME
a=0.00915007
b=0.00715449
fi

FOUND31=`echo ${EJ230Teflon[*]} | grep "$FINDME"`
if [ "${FOUND31}" != "" ]; then
  echo Array contains: $FINDME
a=0.0117096
b=0.0265059
fi

FOUND41=`echo ${EJ276Teflon[*]} | grep "$FINDME"`
if [ "${FOUND41}" != "" ]; then
  echo Array contains: $FINDME
fi

FOUND12=`echo ${EJ200ESR[*]} | grep "$FINDME"`
if [ "${FOUND12}" != "" ]; then
  echo Array contains: $FINDME
a=0.00731252
b=0.00741033
fi

FOUND22=`echo ${EJ204ESR[*]} | grep "$FINDME"`
if [ "${FOUND22}" != "" ]; then
  echo Array contains: $FINDME
a=0.00624948
b=0.00610325
fi

FOUND32=`echo ${EJ230ESR[*]} | grep "$FINDME"`
if [ "${FOUND32}" != "" ]; then
  echo Array contains: $FINDME
a=0.0085709
b=0.0101548
fi

FOUND42=`echo ${EJ276ESR[*]} | grep "$FINDME"`
if [ "${FOUND42}" != "" ]; then
  echo Array contains: $FINDME
a=0.0112494
b=-0.0399353
fi


rootName="${fileName##*/}"
rootName=${fileName%.*}
rootName=$rootName.root

fileName="${fileName##*/}"
fileName=${fileName%.*}
echo $fileName

Folder="Folder$fileName"
echo "Creating $Folder"

cd /home/kevinkeefe/Documents/ntc_data/Tool4Analysis-wTime/rootFiles
cp $rootName /home/kevinkeefe/Documents/ntc_data/Tool4AnalysisCutted
cd /home/kevinkeefe/Documents/ntc_data/Tool4AnalysisCutted


mkdir $Folder
mkdir plots

rm -rf $Folder/plots

./NTuples-improveCuttedSNLnumbers $rootName tempNtuple.root $a $b

rm $rootName

echo "Generating histograms..."
root -b -q HDAuto.c 


mv plots $Folder
mv *.dat $Folder
mv *.png $Folder

mv tempNtuple.root $Folder
#rm tempNtuple.root

cp allFinalCurves1.c $Folder
cd $Folder
root -b -q allFinalCurves1.c
cd /home/kevinkeefe/Documents/ntc_data/Tool4AnalysisCutted
rm -rf plots 

echo "Compressing the output file..."
tar -cvf $Folder.tar.gz $Folder --exclude=$Folder/*.dat --exclude=plots --exclude=*.c --exclude=*.root --exclude=*.pdf

mv $Folder.tar.gz /home/kevinkeefe/Documents/ntc_data/Tool4AnalysisCutted/Temporalfolder
#mv $Folder $filePath/
#mv $Folder.tar.gz $filePath/

done

#cd /home/kevinkeefe/Documents/ntc_data/Tool4Analysis/Temporalfolder


echo "File processed succeed, time to check your result plots!"
echo ".......and........"
echo "May the force be with you!"
exit





done 
exit
