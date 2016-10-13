TurboSoftware
=============

Test Beam Data Analysis Software

To clone this particular branch use :

	git clone -b Oct2016TestBeam https://github.com/ram1123/TurboSoftware.git

To work on lxplus you need to use Root version 5.34.00. For that just source the below two lines.

	source /afs/cern.ch/sw/lcg/contrib/gcc/4.8/x86_64-slc6/setup.sh
	source /afs/cern.ch/sw/lcg/app/releases/ROOT/5.34.00/x86_64-slc6-gcc46-opt/root/bin/thisroot.sh

How To Use:

	cd TurboSoftware/EventBuilder
	./RunTurbo.sh -r
	cd ../ppt
	./GetPlot.sh -r

Path of Input Data:

	To be updated...

	

# Cluster Size Study

For this study there are three codes named

1. *RunClusterSize.sh* : This is script to run on many events. This takes eventbuilder output root file as input. So, you may need to change  path for the input directory.

2. *ClusterSize.C* : This is the main macro that extract cluster size information makes histogram for the same and fits it. So, along with plots it also gives you the text file where you can find the summary of clustersize for each run.

3. *Cluster_Size_vs_HV.C* : This codes just plots the cluster size vs HV.
