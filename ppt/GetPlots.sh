#!/bin/bash

#	-------------------------------------------------------------------
#
#	Shell program to This script runs the code on Ntuple (if it exists) and then puts the created plot in the ppt..
#
#	Author: 2014, Ramkrishna Sharma,,, <ramkrishna.sharma71@gmail.com>.
#
#	The structure of the program is created by a script prodived on LinuxCommand.org
#
#	Usage:
#
#		GetPlots.sh [ -h | --help ] [-r] [-p PathOfInputNtuples]
#
#	Options:
#
#		-h, --help	Display this help message and exit.
#		-r              Asks the initial and final run number over which we need plots. If we want plots only for one run then just put initial and final run number same.
#		-p  PathOfInputNtuplesAsks the path of Ntuples.
#
#
#	Revision History:
#
#	11/03/2014	File created by new_script ver. 2.1.0
#
#	-------------------------------------------------------------------


#	-------------------------------------------------------------------
#	Constants
#	-------------------------------------------------------------------

	#PathOfInputNtuple=/afs/cern.ch/work/p/pbarria/public/TB_H2_OCT_2014/beamdata
	#PathOfInputNtuple=/afs/cern.ch/work/t/tmaersch/public/H2Oct14_Ntuples_Pitch08
	#PathOfInputNtuple=/afs/cern.ch/user/r/rasharma/work/public/GEMTestBeam/TurboSoftware/EventBuilder/OutPutData
	#PathOfInputNtuple=/afs/cern.ch/user/r/rasharma/work/public/GEMTestBeam/Ntuples/H4NovDec14_Ntuples_Rotation_Pitch08
	PathOfInputNtuple=../EventBuilder/OutPutData

	getppt=1
	mail=0
	PROGNAME=$(basename $0)
	VERSION="0.0.1"

	


#	-------------------------------------------------------------------
#	Functions
#	-------------------------------------------------------------------


function clean_up
{

#	-----------------------------------------------------------------------
#	Function to remove temporary files and other housekeeping
#		No arguments
#	-----------------------------------------------------------------------

	rm -f ${TEMP_FILE1}
}


function error_exit
{

#	-----------------------------------------------------------------------
#	Function for exit due to fatal program error
#		Accepts 1 argument:
#			string containing descriptive error message
#	-----------------------------------------------------------------------


	echo "${PROGNAME}: ${1:-"Unknown Error"}" >&2
	clean_up
	exit 1
}


function graceful_exit
{

#	-----------------------------------------------------------------------
#	Function called for a graceful exit
#		No arguments
#	-----------------------------------------------------------------------

	clean_up
	exit
}


function signal_exit
{

#	-----------------------------------------------------------------------
#	Function to handle termination signals
#		Accepts 1 argument:
#			signal_spec
#	-----------------------------------------------------------------------

	case $1 in
		INT)	echo "$PROGNAME: Program aborted by user" >&2
			clean_up
			exit
			;;
		TERM)	echo "$PROGNAME: Program terminated" >&2
			clean_up
			exit
			;;
		*)	error_exit "$PROGNAME: Terminating on unknown signal"
			;;
	esac
}


function make_temp_files
{

#	-----------------------------------------------------------------------
#	Function to create temporary files
#		No arguments
#	-----------------------------------------------------------------------

	# Use user's local tmp directory if it exists

	if [ -d ~/tmp ]; then
		TEMP_DIR=~/tmp
	else
		TEMP_DIR=/tmp
	fi

	# Temp file for this script, using paranoid method of creation to
	# insure that file name is not predictable.  This is for security to
	# avoid "tmp race" attacks.  If more files are needed, create using
	# the same form.

	TEMP_FILE1=$(mktemp -q "${TEMP_DIR}/${PROGNAME}.$$.XXXXXX")
	if [ "$TEMP_FILE1" = "" ]; then
		error_exit "cannot create temp file!"
	fi
}


function usage
{

#	-----------------------------------------------------------------------
#	Function to display usage message (does not exit)
#		No arguments
#	-----------------------------------------------------------------------

	echo "Usage: ${PROGNAME} [-h | --help] [-r] [-p PathOfInputNtuples]"
}


function helptext
{

#	-----------------------------------------------------------------------
#	Function to display help message for program
#		No arguments
#	-----------------------------------------------------------------------

	local tab=$(echo -en "\t\t")

	cat <<- -EOF-

	${PROGNAME} ver. ${VERSION}
	This is a program to This script runs the code on Ntuple (if it exists) and then puts the created plot in the ppt..

	$(usage)

	Options:

	-h, --help	Display this help message and exit.
	-r              This option ask you to enter the two numbers: 	
			${tab}1. First  : Initial Run Number
			${tab}2. Second : Final Run Number
	-p  		Ask you to enter the path of Ntuples
	-g		Don't want to get ppt then use this option.
	-m		This option will mail yout the Efficiency txt file on the 
			${tab} email provided by you.


	
	
-EOF-
}


#	-------------------------------------------------------------------
#	Program starts here
#	-------------------------------------------------------------------

##### Initialization And Setup #####

# Set file creation mask so that all files are created with 600 permissions.

umask 066


# Trap TERM, HUP, and INT signals and properly exit

trap "signal_exit TERM" TERM HUP
trap "signal_exit INT"  INT

# Create temporary file(s)

make_temp_files


##### Command Line Processing #####

if [ "$1" = "--help" ]; then
	helptext
	graceful_exit
fi

while getopts ":hrpgm" opt; do
	case $opt in
		r )	echo "Enter Run number between 33 and 1587."
			echo -n "Initial Run Number (IRunNo) = " 
			read IRunNo
			if [ "$IRunNo" -lt 33 ]; then
				error_exit "Minimum allowed Run Number is 33."
			fi
			echo -n "Final Run Number (FRunNo) = " 
			read FRunNo
			if [ "$FRunNo" == "" ]; then
				FRunNo=$IRunNo
			fi
			if [ "$IRunNo" -gt "$FRunNo" ]; then 
				error_exit "Initial Run Number should be Less then or equal to Final Run Number"
			fi
			echo -n "Do you need each plots on single canvas (N0(0)/Yes(1)) Default(0) :" 
			read Plot
			if [ "$Plot" == "" ]; then
				Plot=0
			fi;;
		p )	echo -n "Enter path of Ntuples : " 
			read PathOfInputNtuple
			if [ ! -f $PathOfInputNtuple ]; then
				error_exit "Path ${PathOfInputNtuple} does not exits"
			fi;;
		m )	echo "The ppt file will be sent to the mail that you will provide."			
			echo -n "Please enter Email-Id : "
			read email
			mail=1;;
		g )	getppt=0;;
		h )	helptext
			graceful_exit ;;
		* )	usage
			clean_up
			exit 1
	esac
done


##### Main Logic #####
if [ "$#" == "0" ]; then
	helptext
	error_exit "Please enter atleast one arguments from above."
fi
# CREATE A BACKUP DIRECTORY IF NOT EXISTS. THEN REMOVE SOME OF UNWNATED THINGS AND KEEP SOME USEFUL THINGS IN BACKUP DIRECTORY.
	if [ -d "Backup" ]; then
		echo "Directory Backup Exists......."
	else
		mkdir Backup
		echo "Directory Backup Created................."
	fi
	if ls *.pdf; then 
	        mv *.pdf Backup/
	fi
	if ls *.txt; then 
	        mv *.txt Backup/
	fi
	if ls ppt*.tex; then 
	        rm ppt*.tex
	fi
############################################################################################
#
#	To run remotely uncomment below lines
#
#	sshpass -p testbeamuser scp  BeamProfile.C ProducePlots.sh user@cms904fast:/home/user/TempPlotsShifter/
#	sshpass -p testbeamuser ssh  user@cms904fast "cd /home/user/TempPlotsShifter; ls *.pdf; rm *.pdf; ./ProducePlots.sh $1 $2"
#
############################################################################################


./ProducePlots.sh $IRunNo $FRunNo  $PathOfInputNtuple $Plot	 # comment this line for remote uses
	if [ "$?" = "0" ]; then
		echo "File processed on remote mechine"
	else
		echo -e "\n\nFile Could not be processed. Please see error above carefully and run again...............\n\n\n" 1>&2
		exit 1
	fi
	echo "Now file copying in your PC"


# BELOW PATCH HELPS TO MAKE PPT
cp test.tex ppt_R${IRunNo}_R${FRunNo}.tex	# $1 reads the 1st argument
	count=1
	for f in *.pdf; do
	    filename=$(basename  "$f")
	    filename=${filename%.*}
	    filename=${filename//_/ }
	    echo $filename
	    echo $f
	    perl -spe 's/intime_mean_pu.pdf/$a/;s/TitleFrame/$b/' < fig.tex -- -a="$f" -b="$filename" > "fig_${count}.tex"
	    sed -i "/Pointer-rk/r fig_${count}.tex" "ppt_R${IRunNo}_R${FRunNo}.tex"
	    ((++count))
	done
#	awk '{print $1}' EfficiencyData_R$1_R$2.txt > tmp.txt
#	awk '{print $2}' EfficiencyData_R$1_R$2.txt >> tmp.txt
#	awk '{print $3}' EfficiencyData_R$1_R$2.txt >> tmp.txt
#	awk '{print $4}' EfficiencyData_R$1_R$2.txt >> tmp.txt
#	sed -i "/begin{verbatim}/r tmp.txt" "ppt_R$1_R$2.tex"
	
if [ "$getppt" == "1" ]; then
	pdflatex ppt_R${IRunNo}_R${FRunNo}.tex
	pdflatex ppt_R${IRunNo}_R${FRunNo}.tex
	#rm ppt_R${IRunNo}_R${FRunNo}.tex
	rm fig_*.tex  ppt_R${IRunNo}_R${FRunNo}.toc ppt_R${IRunNo}_R${FRunNo}.snm ppt_R${IRunNo}_R${FRunNo}.out ppt_R${IRunNo}_R${FRunNo}.nav ppt_R${IRunNo}_R${FRunNo}.aux ppt_R${IRunNo}_R${FRunNo}.log
	#gnome-open ppt_R${IRunNo}_R${FRunNo}.pdf 
fi	


if [ "$mail" == 1 ]; then
cat<<EOF >message.log
Hi $(basename $email),
This mail is sent automatically sent from the script ${0}.
EOF
echo "mailing the ppt file.... "
mail -a ppt_R${IRunNo}_R${FRunNo}.pdf  -s "ppt file from RunNumber ${IRunNo} to ${FRunNo}" $email < message.log
echo "mail sent"
fi	
echo "Finished."
graceful_exit

