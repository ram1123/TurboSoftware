#To run this we need to give two arguments first should be data path and 2nd should be run number
if [ "$#" -ne 2 ]; then
        echo "Usage: You need to give two arguments: First : Path of Data Second : Run number" >&2
	exit 1
fi
./shrd51_EventBuilderVFAT.sh $1 
./shrd51_TrackFinder.sh $1
./shrd51_Analyzer.sh $1 $2
