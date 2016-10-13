#source rd51_SetEnvironment.sh
# Check for proper number of command line args.
# USESES: ./shrd51_EventBuilderVFAT.sh  <InputFilePath>   <OutputFilePath>   <NumberOfEvent (Optional)>
EXPECTED_ARGS_MIN=2
EXPECTED_ARGS_MAX=3

if [ $# -lt $EXPECTED_ARGS_MIN -o $# -gt $EXPECTED_ARGS_MAX ];
then
  echo ""
  echo "Usage:		./`basename $0` DirectoryWithDataFileIn NumberOfEvents(100k if omitted)"
  echo ""
  echo ""
  echo "Example(NumberOfEvents ):	./`basename $0` Data 10000"
  echo "Example(100K Ev-Default):	./`basename $0` Data"
  echo ""
  exit
fi

if [ $# -eq $EXPECTED_ARGS_MIN ]; then 
	NUMEVENTS=100000 
else
	NUMEVENTS=$3 
fi

if [ -d $2 ]; then
	echo "Directory $2 Exists......."
else
	mkdir $2
	echo "Directory $2 Created................."
fi
#echo "Ram==== $2"
#echo "Ram==== $(basename $1)"
#if [ -d "$2/$(basename $1)" ]; then
#	echo $2/$(basename $1)
#	echo "Directory OutPutData Exists....... Remove it..."
#	rm -r $2/$(basename $1)
#	mkdir $2/$(basename $1)
#	echo "Directory OutPutData Created................."
#else
#	mkdir $2/$(basename $1)
#	echo "Directory OutPutData Created................."
#fi


for DATAFILE in $(ls $1/CRC-Run*.dat); do
				#echo -e "\n"
				echo $DATAFILE
				#echo -e "\n" 
				ROOTFILE="$(basename $DATAFILE)"
				ROOTFILE=${ROOTFILE//.dat/.root}
				root -b -l -q 'rd51_EventBuilderVFAT_Launcher.cpp("'$DATAFILE'","'$2'/'$ROOTFILE'",'$NUMEVENTS')'
				#root -b -l -q 'rd51_EventBuilderVFAT_Launcher.cpp("'$DATAFILE'","'$2'/'$(basename $1)'/'$ROOTFILE'",'$NUMEVENTS')'
done;

