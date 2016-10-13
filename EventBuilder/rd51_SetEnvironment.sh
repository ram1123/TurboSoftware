#unset ROOTSYS

#. /afs/cern.ch/sw/lcg/external/gcc/4.4.3/x86_64-slc5/setup.sh
#. /afs/cern.ch/sw/lcg/app/releases/ROOT/5.30.00/x86_64-slc5-gcc43-opt/root/bin/thisroot.sh
#. /usr/local/bin/thisroot.sh


echo""
echo "ROOT 5.34 from afs: $ROOTSYS"
echo""

HERE=$(pwd)
RD51DIR=$(pwd)
DIRNAME=$(basename $RD51DIR)
while [ "$DIRNAME" != "EventBuilder" -o "$DIRNAME" == "" ]; do
	echo "Looking for the right main directory. Now I'm in $DIRNAME"
	if [ "$DIRNAME" != "EventBuilder" ]; then
	cd ..
	RD51DIR=$(pwd)
	DIRNAME=$(basename $RD51DIR)
	fi
done

if [ "$DIRNAME" != "EventBuilder" ]; then
echo ""
echo "RD51MainDirectory Not Found"
echo ""
cd $HERE
exit
fi

RD51MainDirectory=$RD51DIR
export PATH=$PATH:$RD51MainDirectory
export PATH=$PATH:$RD51MainDirectory/Mapping
export PATH=$PATH:$RD51MainDirectory/Clustering
export PATH=$PATH:$RD51MainDirectory/Loaders
export PATH=$PATH:$RD51MainDirectory/Utilities

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$RD51MainDirectory
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$RD51MainDirectory/Mapping
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$RD51MainDirectory/Clustering
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$RD51MainDirectory/Loaders
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$RD51MainDirectory/Utilities

echo "RD51 Environment settings:"
echo "RD51MainDirectory=$RD51MainDirectory"

echo "PATH=$PATH" 
echo "LD_LIBRARY_PATH=$LD_LIBRARY_PATH" 
cd $HERE
