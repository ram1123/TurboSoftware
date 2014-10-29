source rd51_SetEnvironment.sh

# Check for proper number of command line args.

EXPECTED_ARGS_MIN=2
EXPECTED_ARGS_MAX=2

if [ $# -lt $EXPECTED_ARGS_MIN -o $# -gt $EXPECTED_ARGS_MAX ];
then
  echo ""
  echo "Usage:		./`basename $0` DirectoryWithFiles RunNumber"
  echo ""
  echo ""
  echo "Example:	./`basename $0`  ../Data 0099"
  echo ""
  exit
fi
echo ""
echo ""

for FILE in $(ls $1/CRC-Run*$2*.root); do
                                echo "$FILE"
done;



echo ""
echo ""
echo ""
for FILE in $(ls $1/CRC-Run*$2*.root); do
				ROOTFILE="$(basename $(ls $FILE))"
				RECOFILE="$(basename $(ls $FILE))"
				RECOFILE=${RECOFILE//CRC/RECO-CRC}
				ANFILE="$(basename $(ls $FILE))"
				ANFILE=${ANFILE//CRC/AN-CRC}
				#RECOFILE="$(basename $(ls $FILE) | replace CRC RECO-CRC)"
				#ANFILE="$(basename $(ls $FILE) | replace CRC AN-CRC)"
				echo ""
				echo ""
				echo "--------------------------------------------------------------------------------------------------------"
				echo ""
				echo "Event Builder File: $ROOTFILE"
				echo "Track Finder File: $RECOFILE"
				echo "ANALYSIS File: $ANFILE"
				echo ""
				echo "--------------------------------------------------------------------------------------------------------"
				echo ""
				echo ""

echo "Updating the Reco and Tracker Classes..."
./shrd51_ClassMaker_RecoTracker.sh $1/$ROOTFILE $1/$RECOFILE
echo ""
echo ""
echo ""
root -b -l -q 'rd51_Analyzer_Launcher.cpp("'$1'/'$ROOTFILE'","'$1'/'$RECOFILE'","'$1'/'$ANFILE'")'

done;
