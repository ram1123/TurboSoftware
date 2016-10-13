#TurboSoftware

Test Beam Data Analysis Software

To clone this particular branch use :

	git clone -b Oct2016TestBeam https://github.com/ram1123/TurboSoftware.git

To work on lxplus you need to use Root version 5.34.00. For that just source the below two lines.

	source /afs/cern.ch/sw/lcg/contrib/gcc/4.8/x86_64-slc6/setup.sh
	source /afs/cern.ch/sw/lcg/app/releases/ROOT/5.34.00/x86_64-slc6-gcc46-opt/root/bin/thisroot.sh

##How To Use
Before use you need to *set the configuration files* as per the experimental setup. If the configuration file is set properly then use the script described below else set the configuration file. The description of configuration file is given in next section.

To analyze runs there is a script named **RunTurbo.sh**, which is placed in EventBuilder directory. To use this script there are several options which is given below:

	Usage: RunTurbo.sh [-h | --help] [-i] [-f]
	Options:
	
	-h, --help	Display this help message and exit.
	
	-r              This option ask you to enter the two numbers: 	
			1. First  : Initial Run Number
			2. Second : Final Run Number
	
	-l		This option ask you to enter the two numbers:
			1. First : Initial Latency 
			2. Second : Final Latency
	
	-f		This option ask you to enter the Input Data directory path.
			 We can also set the default path at line number 47 in 
			 this script.
	
	-e		This option will ask you which process you want to run.
			 Want to run full Turbo or only one out of 3 steps.
			 or want to get only Efficiency text file.
			Also, this will ask, whether you want to delete the 
			existing root files or not.
	
	-m		This option will mail yout the Efficiency txt file on the 
			 email provided by you.
	
	-i		This option will ask you and if you need text file from input
			directory or not? By default it takes input form the Output
			directory in EventBuilder Directory.
	

Also, there is one more script named **GetPlot.sh**, which is in ppt directory. Again, to use this script some of available options are:

	Usage: GetPlots.sh [-h | --help] [-r] [-p PathOfInputNtuples]
	
	Options:
	
	-h, --help	Display this help message and exit.
	-r              This option ask you to enter the two numbers: 	
			1. First  : Initial Run Number
			2. Second : Final Run Number
	-p  		Ask you to enter the path of Ntuples
	-g		Don't want to get ppt then use this option.
	-m		This option will mail yout the Efficiency txt file on the 
			 email provided by you.


Summary of how to use:

	cd TurboSoftware/EventBuilder
	./RunTurbo.sh -r	# This will give you root files
	cd ../ppt
	./GetPlot.sh -r		# This will give you plots from the root file created from RunTurbo.sh script.

Path of Input Data:

	To be updated...


## Things to change in configuration file
**Path of configuration files:** TurboSoftware/EventBuilder/ConfigFiles/

Things to note before modifying the configuration file:

1. What type of detectors readout we have?
	* If we have 10x10 GEM detector type readout then its readout type is 0 or 1. If readout has x-axis then the readout type should be 0 if it is y-axis then its readout type should be 1.
	* For GE11 type readout its value is 9. (Note that it has only 1-D readout)
2. Note the detector chip ID, turbo ID and slot ID.

Things to change in configuration file:

1. DetectorConfig _*.conf
	* List all the detectors used (follow the pattern) with its readout type.
	* Other possible changes may be for the variables TotChannels.
	* See all other parameters in the configure whose name is reflected by its name and if you need you can change others too.
2. VFATConfig_*.conf
	* Main parameter to edit is the ChipId, TurboId and SlotId.
	* Other important parameter is DetectorId. Value of this variable is taken from the previous config file.
3. OffsetFlip _EventBuilderVFAT_*.conf
	* Propagate the detectors information here as per pervious configuration file.	

# Cluster Size Study

For this study there are three codes named

1. *RunClusterSize.sh* : This is script to run on many events. This takes eventbuilder output root file as input. So, you may need to change  path for the input directory.

2. *ClusterSize.C* : This is the main macro that extract cluster size information makes histogram for the same and fits it. So, along with plots it also gives you the text file where you can find the summary of clustersize for each run.

3. *Cluster_Size_vs_HV.C* : This codes just plots the cluster size vs HV.
