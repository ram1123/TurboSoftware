# Reset                                                                                                                                        
Color_Off='\033[0m'       # Text Reset
# Regular Colors
Black='\033[0;30m'        # Black
Red='\033[0;31m'          # Red                                                                                                                
Green='\033[0;32m'        # Green
Yellow='\033[0;33m'       # Yellow
Blue='\033[0;34m'         # Blue
Purple='\033[0;35m'       # Purple
Cyan='\033[0;36m'         # Cyan
White='\033[0;37m'        # White


rm Cluster_Size.txt
#for f in /afs/cern.ch/user/r/rasharma/public/TurboSoftware/EventBuilder/OutPutData/Run*/; do
RunCounter=$1
FRunNo=$2

if [ "${FRunNo}" == "" ]; then
	FRunNo=$RunCounter
fi

if [ "$#" == "0" ]; then
	echo "Please enter at least one argument"
	exit 1
fi	

while [ $RunCounter -le $FRunNo ]
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
  echo $file
  for f in /home/ramkrishna/PhD_New_Dir_16July2016/GEM/GEM_TB/TB_2014/FNAL-Beam-Test-Scripts_2014_19Aug/Run${file}*/; do
	if [ ! -f $f/CRC*.root ]; then
		echo -e "${Red}No root file is present in $f${Color_Off}"
	else
		for R in $f/CRC*.root; do
			echo -e "\n${Green}Hist Name = $f${Color_Off}"
			HistName=$(basename $f)
			echo -e "Hist Name = $HistName"
			#HistName=${HistName#*_ASync_HVScan_}
			#HistName=${HistName#*_Async_HVScan_}
			#echo -e "Hist Name = $HistName"
			#HistName=${HistName%_0pt0*}
			#HistName=${HistName%_0_*}
			#HistName=${HistName%_*}
			echo -e "Hist Name = $HistName"
			echo "root -l -b -q ClusterSize.C\(\"$R\",\"$(basename $f)\",\"${HistName}\"\)"
			root -l -b -q ClusterSize_RooFit.C\(\"$R\",\"$(basename $f)\",\"${HistName}\"\) | tee ${HistName}.dat
			#root -l -b -q ClusterSize.C\(\"$R\",\"$(basename $f)\"\)
			#echo "$(basename $f)"
			sed -n '/=================================================/{p;}' ${HistName}.dat >> RunLog.dat
			sed -n '/=================================================/{n;n;p;}' ${HistName}.dat >> RunLog.dat
			sed -n '/=================================================/{n;n;n;p;}' ${HistName}.dat >> RunLog.dat
			sed -n '/=================================================/{n;n;n;n;p;}' ${HistName}.dat >> RunLog.dat
			sed -n '/=================================================/{n;n;n;n;p;}' ${HistName}.dat >> RunLog.dat
		done
	#exit 1
	fi
  done
  RunCounter=$[$RunCounter+1]
done
#rm Run*.pdf Run*.root Run*.png Run*.C
