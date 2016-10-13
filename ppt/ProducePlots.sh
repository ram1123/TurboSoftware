#!/bin/bash

#	-------------------------------------------------------------------
#
#	Shell program to This script runs form the script GetPlot.sh and it runs the macro BeamProfile.C
#
#	Author: 2014, Ramkrishna Sharma,,, <ramkrishna.sharma71@gmail.com>.
#

RunCounter=$1
while [ $RunCounter -le $2 ]
do
  if [[(($RunCounter -le 9))]]; then
 	file=000$RunCounter
  else
  if [[(($RunCounter -le 99))]]; then
	file=00$RunCounter
  else
  if [[(($RunCounter -le 999))]]; then
  	file=0$RunCounter
  else
	file=$RunCounter
  fi
  fi
  fi
  for Dir in $3/Run$file*
  do
     temp=$(echo $Dir | sed 's/.*Run//' | sed 's/.//5g')
     echo "RAMKRISHNA $temp"
     echo "RAMKRISHNA $RunCounter"
    # sleep 5
    # if [[ (($temp -ge $1)) && (($temp -le $2))]]; then
       for RootFile in $(ls $Dir/CRC-Run*.root); do
  	echo $RootFile
  	RecoFile=$(basename $RootFile)
  	RecoFile=${RootFile//CRC/RECO-CRC}
  	echo -e "\n\n\tName of ROOT files:\n"
  	echo -e "\n\n\t$RootFile"
  	echo -e "\n\n\t$RecoFile"
  	root -b -l -q 'BeamProfile.C("'$RootFile'","'$RecoFile'",'$RunCounter')'
       done
     #fi
  done   
  RunCounter=$[$RunCounter+1]
done 
