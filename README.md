TurboSoftware
=============

Test Beam Data Analysis Software for Cosmic

To work on lxplus you need to use Root version 5.34.00. For that just source the below two lines.

	source /afs/cern.ch/sw/lcg/contrib/gcc/4.8/x86_64-slc6/setup.sh
	source /afs/cern.ch/sw/lcg/app/releases/ROOT/5.34.00/x86_64-slc6-gcc46-opt/root/bin/thisroot.sh

To clone this particular branch use :

	git clone git@github.com:ram1123/TurboSoftware.git
	git checkout May2016TestBeam

To Use this:

	$cd TurboSoftware/EventBuilder
	->Modify path of input data in line number 52
	$./RunTurbo.sh -r
	->First it will ask initial run number then put run number to be analyzed. 
	->Then it will ask final run number then just press ENTER.
	$cd ../ppt
	$./GetPlot.sh -r
	->When you run this command then you will get a pdf file named **ppt_R*_R*.tex**
	->This file contains all the basic plots that you need to see quickly, without alignment.
