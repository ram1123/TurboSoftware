source rd51_SetEnvironment.sh

# Check for proper number of command line args.

EXPECTED_ARGS_MIN=1
EXPECTED_ARGS_MAX=1

if [ $# -lt $EXPECTED_ARGS_MIN -o $# -gt $EXPECTED_ARGS_MAX ];
then
  echo ""
  echo "Usage:          ./`basename $0` DirectoryWithBuildedROOTFileIn"
  echo ""
  echo ""
  echo "Example:       ./`basename $0` Data"
  echo ""
  exit
fi

rm -v -f rd51_EventBuilder_Class.*
for ROOTFILE in $(ls $1/CRC-Run*.root); do
				RECOFILE="$(basename $(ls $ROOTFILE))"
				RECOFILE=${ROOTFILE//CRC/RECO-CRC}
				#RECOFILE="$(basename $(ls $ROOTFILE) | replace CRC RECO-CRC)"
				echo "InputFile: "$ROOTFILE " OutputFile: "$RECOFILE
      				root -b -l -q 'rd51_TrackFinder_Launcher.cpp("'$ROOTFILE'","'$RECOFILE'")'
      				#root -b -l -q 'rd51_TrackFinder_Launcher.cpp("'$ROOTFILE'","'$1'/'$RECOFILE'")'
				echo -e "\n"
done;
