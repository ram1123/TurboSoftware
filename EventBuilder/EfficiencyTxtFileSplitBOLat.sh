IRunNo=$1
FRunNo=$2
ILat=15
FLat=30

echo "file(s) of interest:" 

rm FilesToAnalyze.txt
echo "EfficiencyData_R${IRunNo}_R${FRunNo}.txt" >> FilesToAnalyze.txt


while [ $ILat -le $FLat ]
do
  rm EfficiencyData_R${IRunNo}_R${FRunNo}_Lat${ILat}.txt
  grep "Lat$ILat" EfficiencyData_R${IRunNo}_R${FRunNo}.txt >> EfficiencyData_R${IRunNo}_R${FRunNo}_Lat${ILat}.txt

  outputFile=EfficiencyData_R${IRunNo}_R${FRunNo}_Lat${ILat}.txt
  outputFile_short=EfficiencyData_R${IRunNo}_R${FRunNo}_Lat${ILat}.txt

  if [ $(stat -c%s "$outputFile") -le 46 ]; then
    rm $outputFile
  else
    echo "gedit $outputFile"
    echo "EfficiencyData_R${IRunNo}_R${FRunNo}_Lat${ILat}.txt" >> FilesToAnalyze.txt
  fi
  
  ILat=$[$ILat+1]
done

cp FilesToAnalyze.txt FilesToAnalyze_R${IRunNo}_R${FRunNo}.txt

echo "To Make Efficiency Curves Execute In Terminal:"
echo "./analyzeEff.sh"
