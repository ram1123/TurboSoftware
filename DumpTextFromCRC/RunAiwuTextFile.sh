IRunNo=$1
FRunNo=$2
RunCounter=$IRunNo
PathOfInputData=/afs/cern.ch/work/p/pbarria/public/TB_H2_OCT_2014/beamdata
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
    for f in $PathOfInputData/Run$file*/CRC*.root; do
    	#perl -spe 's/CRC-Run0411_Muon_10k_MSPL2_HVScan_710pt1_710pt1_710pt0_T20_T20_T20_Lat22-141011_013955-0.root/$a/' < 
	#echo ${PathOfInputData}$(basename $f)/CRC-$(basename $f)-0.root
	echo $f
	sed -i "s?CRC-Run0411_Muon_10k_MSPL2_HVScan_710pt1_710pt1_710pt0_T20_T20_T20_Lat22-141011_013955-0.root?${f}?g" AiwuTextFile.h
    done
    ((++RunCounter))
done

