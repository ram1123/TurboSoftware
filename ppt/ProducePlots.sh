#!/bin/bash

#	-------------------------------------------------------------------
#
#	Shell program to This script runs form the script GetPlot.sh and it runs the macro BeamProfile.C
#
#	Author: 2014, Ramkrishna Sharma,,, <ramkrishna.sharma71@gmail.com>.
#

function make_dir
{

	if [ -d "${1}" ]; then
		echo "Directory ${1} Exists......."
	else
		mkdir ${1}
		echo "Directory ${1} Created................."
	fi
}


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
  fi		# 999
  fi		# 99
  fi		# 9
	make_dir "Plots"
	make_dir "Plots/pdf"
	make_dir "Plots/pdf/${RunCounter}"
	make_dir "Plots/gif"
	make_dir "Plots/gif/${RunCounter}"
	make_dir "Plots/C"
	make_dir "Plots/C/${RunCounter}"
	make_dir "LogFiles/${RunCounter}"

##	if [ -f "ClusterSize_${1}_${2}.txt" ]; then
##		rm ClusterSize_${1}_${2}.txt
##	fi

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
  	ANFile=${RootFile//CRC/AN-CRC}
  	echo -e "\n\n\tName of ROOT files:\n"
  	echo -e "\n\n\t$RootFile"
  	echo -e "\n\n\t$RecoFile"
  	echo -e "\n\n\t$ANFile"
  	root -b -l -q 'BeamProfile.C("'$RootFile'","'$RecoFile'","'$ANFile'",'$RunCounter','$4')'
	echo -e "\n\n\n####################################################\n\n\n"
	cat Current_vs_ClusterSize.txt
	cat Current_vs_ClusterSize.txt >> ClusterSize_${1}_${2}.txt
	echo -e "\n\n\n####################################################\n\n\n"
       done
     #fi
  done   
  RunCounter=$[$RunCounter+1]
done 
