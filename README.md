#####Table Of Content
  * [How To Get Software](#how-to-get-software)
  * [How To Use](#how-to-use)
    * [Things to change in configuration file](#things-to-change-in-configuration-file)
    * [ReadOutType](#readouttype)
  * [Cluster Size Study](#cluster-size-study)
  * [Some Terminology used to save information in the tree](#some-terminology-used-to-save-information-in-the-tree)
  * [Definiton of Different Terms Used in Configuration File](#definiton-of-different-terms-used-in-configuration-file)


---
# How To Get Software

Test Beam Data Analysis Software

To clone this particular branch use :

	git clone -b Oct2016TestBeam https://github.com/ram1123/TurboSoftware.git

To work on lxplus you need to use Root version 5.34.00. For that just source the below two lines.

	source /afs/cern.ch/sw/lcg/contrib/gcc/4.8/x86_64-slc6/setup.sh
	source /afs/cern.ch/sw/lcg/app/releases/ROOT/5.34.00/x86_64-slc6-gcc46-opt/root/bin/thisroot.sh

# How To Use
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

## ReadOutType
Availabe readout types are 

	0:	X Strips with 400um pitch
	1:	Y Strips with 400um pitch
	2:	X Strips with 800um pitch
	3:	Y Strips with 800um pitch
	4:	Totem T2 Strips	// Not for us
	5:	Totem T2 Pads	// Not for us
	6:	Totem T1 LG		// Not for us
	8:	CMS 30x30		// Not for us
	9:	CMS GE1/1	(along X-axis)
	
Link of the file containing this information is [here][readouttype]. 

CMS GE1/1 readout mapping is [here][ge11mapping].

# Cluster Size Study

For this study there are three codes named

1. *RunClusterSize.sh* : This is script to run on many events. This takes eventbuilder output root file as input. So, you may need to change  path for the input directory.

2. *ClusterSize.C* : This is the main macro that extract cluster size information makes histogram for the same and fits it. So, along with plots it also gives you the text file where you can find the summary of clustersize for each run.

3. *Cluster_Size_vs_HV.C* : This codes just plots the cluster size vs HV.

# Some Terminology used to save information in the tree

* **g1**: 10x10 GEM detector, Used as first reference tracker.
* **g2**: 10x10 GEM detector, Used as second reference tracker.
* **g3**: 10x10 GEM detector, Used as third reference tracker.
* **LC1**: GE1/1-IV-GIF
* **LC2**: GE1/1-IV
* **LC3**: GE1/1-V
* **ngeoch**: Gives the number of Clsuters
* **geoch**: Gives the VFAT channel numbers fired on the tracker.
* **geoX**: Gives the fired position of channel on tracker (in mm).
* **geoposch**: Gives the cluster position in terms of channel number.
* **geoposX**: Gives the hit position in detectors in mm along X axis.

# Definiton of Different Terms Used in Configuration File

* **Chip ID** : This is the hardware ID for the different VFAT chips used in tracker or GEM.
* **Channels** : This is the number of channels in each chip. (which is 128 for the VFATs).
* **Detector ID** : This specify to which detector the chip are connected. The X and Y coordinates of the Trackers are considered as two different detectors. This ID will be used later to assign the VFAT channel status to a detector channel status. For Trackers it shoud be less than 21. If not then modify the loop if ( (ichip>= 0) && (chipdet[ichip]<21) ) in the file rd51_EventBuilderVFAT.C
* **Detector Name** : Name of detector
* **Detector Sector** : sector of detector
* **Chip Invert** : The Invert tell to the software how the VFATs channels are placed in the space (right-left, top-bottom). Looking at the chip from the top of the hybrid (with the chip in the bottom) the channel 0 is on the Left.
* **Chip Offset** :
* **Turbo ID** : Where the VFAT joined on Turbo, is it addedin master TURBO or in which slave?
* **Slot ID** : In which slot of TURBO the VFAT is connected?
* **xFlip and yFlip** : It just flips the VFAT information
* **Read Out Type** : This is basically the mapping of the particular detector. It is described briefly in section [ReadOutType](#readouttype).


---


[readouttype]: https://github.com/ram1123/TurboSoftware/blob/Oct2016TestBeam/EventBuilder/Mapping/ReadoutType.cpp

[ge11mapping]: https://github.com/ram1123/TurboSoftware/blob/Oct2016TestBeam/EventBuilder/Mapping/CmsMapping.cpp
