#!/bin/bash

#	-------------------------------------------------------------------
#
#	Shell program to Run the full chain of TURBO software and creates the 
#	log file for each step. Also, this will save your data in the present 
#	directory. Also it will create a text file in which we can find the 
#	Efficiencies for various run..
#
#	Author: 2014, Ramkrishna Sharma,<ramkrishna.sharma71@gmail.com>; Brian Dorney, <brian.l.dorney@cern.ch>
#		
#	The structure of the program is created by a script prodived on LinuxCommand.org
#
#	Usage:
#
#		RunTurbo.sh [ -h | --help ] [-r]
#
#	Options:
#
#		-h, --help	Display this help message and exit.
#		-r              This option ask you to enter the two numbers: 	
#				1. First  : Initial Run Number
#				2. Second : Final Run Number
#		-l		This option ask you to enter the two numbers:
#				1. First : Initial Latency 
#				2. Second : Final Latency
#		-f		This option ask you to enter the Input Data directory path.
#				We can also set the default path at line number 44 in 
#				this script.
#		-e		This option will ask you which process you want to run.
#				Want to run full Turbo or only one out of 3 steps.
#
#
#	Revision History:
#
#	10/26/2014	File created based on the old script runfull_v9.sh
#	10/27/2014	Added option -e in the script and some default values.
#
#	-------------------------------------------------------------------


#	-------------------------------------------------------------------
#	Constants
#	-------------------------------------------------------------------
	
	# Should be changed by user according to their path
	PathOfInputData=/afs/cern.ch/work/p/pbarria/public/TB_H2_OCT_2014/beamdata
	
	# Some Default values
	IRunNo=1120
	FRunNo=1120
	ILat=10
	FLat=30
	run=0
	DeleteRootFile=0
	# Should Not be changed
	PathOfOutputData=$PWD
	CheckInteger='^[0-9]+$'
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
	local err_msg
	
	err_msg="${PROGNAME}: ${1}"
	echo -e "\n\n${err_msg}\n\n" >&2
	clean_up
	exit 1

#	echo "${PROGNAME}: ${1:-"Unknown Error. Please look above error carefully."}" >&2
#	clean_up
#	exit 1
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

function CheckOutPutDir
{

#	------------------------------------------------------------------------
#	It Checks IF the output data directory exists or not
#	No Arguments
#	------------------------------------------------------------------------
	if [ -d "OutPutData" ]; then
		echo "Directory OutPutData Exists......."
	else
		mkdir OutPutData
		echo "Directory OutPutData Created................."
	fi
	PathOfOutPutData=$PathOfOutputData/OutPutData
	return
}	# end of CheckOutPutDir

function DeleteIfFileExists
{

#	------------------------------------------------------------------------
#	It deletes a file if it exists
#		Arguments:
#			1	Name of File (required)
#	------------------------------------------------------------------------

	# Fatal error if required arguments are missing

	if [ "$1" = "" ]; then 
		error_exit "DeleteIfFileExists: missing argument 1"
	else
		rm $1
		echo "File ${1} deleted."
	fi

	return

}	# end of DeleteIfFileExists


function usage
{

#	-----------------------------------------------------------------------
#	Function to display usage message (does not exit)
#		No arguments
#	-----------------------------------------------------------------------

	echo "Usage: ${PROGNAME} [-h | --help] [-i] [-f]"
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
	This is a program to Run the full chain of TURBO software and creates the log file for each step. Also, this will save your data in the present directory. Also it will create a text file in which we can find the Efficiencies for various run..

	$(usage)

	Options:

	-h, --help	Display this help message and exit.
	-r              This option ask you to enter the two numbers: 	
			${tab}1. First  : Initial Run Number
			${tab}2. Second : Final Run Number
	-l		This option ask you to enter the two numbers:
			${tab}1. First : Initial Latency 
			${tab}2. Second : Final Latency
	-f		This option ask you to enter the Input Data directory path.
			${tab} We can also set the default path at line number 47 in 
			${tab} this script.
	-e		This option will ask you which process you want to run.
			${tab} Want to run full Turbo or only one out of 3 steps.
			${tab}Also, this will ask, whether you want to delete the 
			${tab}existing root files or not.
	-m		This option will mail yout the Efficiency txt file on the 
			${tab} email provided by you.
	
-EOF-
}

function ask_yes_no
{
	#####
	#	Function to ask a yes/no question
	#	Arguments:
	#		1	prompt string (optional)
	#####

	local yn=

	while [ "$yn" = "" ]; do
		echo -en "$1"
		read yn
		case $yn in
			y|Y)	yn=0 ;;
			n|N)	yn=1 ;;
			*)	yn=
				echo "Invalid response - please answer y or n"
				;;
		esac
	done
	return $yn
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

while getopts ":hrlfem" opt; do
	case $opt in
		r )	echo -n "Initial Run Number (IRunNo) = " 
			read IRunNo
			echo -n "Final Run Number (FRunNo) = " 
			read FRunNo
			if [ "$IRunNo" -gt "$FRunNo" ]; then 
				error_exit "Initial Run Number should be Less then or equal to Final Run Number"
			fi;;
		l )	echo -n "Initial Latency (ILat) = "
			read ILat
			echo -n "Final Latency (FLat) = "
			read FLat
			if [ "$ILat" -gt "$FLat" ]; then 
				error_exit "Initial Latency should be Less then or equal to Final Latency"
			fi;;
		f)	echo -n "Enter the Path of Data File : "
			read PathOfInputData;;
		e)	echo "To run full TURBO software Enter 0"
			echo "To run Only EventBuilder Enter 1"
			echo "To run Only TrackFinder Enter 2"
			echo -n "To run Only Analyzer Enter 3 : "
			read run	
			if [ "$run" == 0 -o "$run" == 1 ]; then
				if ask_yes_no "If Root File Exists in Output Directory. Want to Delete them??? [y/n] "; then
					DeleteRootFile=1
				fi
			fi;;
		m )	echo "The Efficiency txt file will be sent to your mail."			
			echo -n "Please enter your Email-Id : "
			read email
			mail=1;;
		h )	helptext
			graceful_exit ;;
		* )	usage
			clean_up
			exit 1
	esac
done


##### Main Logic #####
DeleteIfFileExists EfficiencyData_R${IRunNo}_R${FRunNo}.txt
echo -e  "FileName\t\t\t\t\t\t\t\t\t GE11_IV_GIF \t\t GE11_IV \t\t GE11_V" > EfficiencyData_R${IRunNo}_R${FRunNo}.txt

RunCounter=$IRunNo


while [ $RunCounter -le $FRunNo ]
do
  if [[(($RunCounter -le 9))]]; then
 	file=000$RunCounter
  else
  if [[(($RunCounter -le 99))]]; then
	file=00$RunCounter
  else
  if [[(($RunCounter -le 999))]]; then
  	file=0$RunCounter
  else
	file=$RunCounter
  fi
  fi
  fi

  # Copies the right configuration file for the present run
  if [ $RunCounter -le 103 ]; then
    cp Setting_EventBuilderVFAT_Run0103AndBelow.conf Setting_EventBuilderVFAT.conf
  else
  if [ $RunCounter -le 1117 ]; then
    cp Setting_EventBuilderVFAT_Run1117AndBelow.conf Setting_EventBuilderVFAT.conf
  else  
    cp Setting_EventBuilderVFAT_Run1118AndUp.conf Setting_EventBuilderVFAT.conf						         
  fi 
  fi
  for f in $PathOfInputData/Run$file* 	# Stores path of File in variable f
  do
  	cat Setting_EventBuilderVFAT.conf
	echo "Data File : ${f}"
	#./clean.sh
	#temp=$(echo $f | awk '{print substr($RunCounter,'$WhereIsRunNumber',4)}')
	temp=$(echo $f | sed 's/.*Run//' | sed 's/.//5g')	# This greps the number of run from the path.
								# Here sed command removes everything till *Run. and then
								# next sed command removes everything from 5th letter 
								# onwards. So, at last we left with only number
	if ! [[ $temp =~ $CheckInteger ]] ; then 
		echo -e "Path Of Input Directory : ${f}"
		echo -e "\n\n\t\t temp = ${temp} \n\n"
		echo "error: Not able to extract Run number. " >&2; 
		exit 1
	fi	
	CheckOutPutDir
	if [ "$run" == 0 -o "$run" == 1 ]; then
		if [ "$DeleteRootFile" == 1 ]; then
			echo -e "\n\n\tls  ${PathOfOutPutData}/$(basename $f)/*.root\n\n"
			rm $PathOfOutPutData/$(basename $f)/*.root
			echo -e "\n\n\t\tROOT FILE IS REMOVED\n\n\n"
		fi
		echo -e "\n\n\t\tEventBuilder started\n\n"
		echo -e "\n\n./shrd51_EventBuilderVFAT.sh ${f}  ${PathOfOutPutData} | tee ${PathOfOutPutData}/$(basename $f)/Run${temp}_EventBuilderVFAT.log\n\n"
		./shrd51_EventBuilderVFAT.sh $f  $PathOfOutPutData | tee $PathOfOutPutData/$(basename $f)/Run${temp}_EventBuilderVFAT.log
	fi
	if [ "$run" == 0 -o "$run" == 2 ]; then
		echo -e "\n\n\t\t TrackFinder started\n\n"
		echo -e "\n\n./shrd51_TrackFinder.sh ${PathOfOutPutData}/$(basename $f) | tee ${PathOfOutPutData}/$(basename $f)/Run${temp}_TrackFinder.log\n\n"
		./shrd51_TrackFinder.sh $PathOfOutPutData/$(basename $f) | tee $PathOfOutPutData/$(basename $f)/Run${temp}_TrackFinder.log
	fi
	if [ "$run" == 0 -o "$run" == 3 ]; then
		echo -e "\n\n\t\tAnalyzer Started\n\n"
		./shrd51_Analyzer.sh $PathOfOutPutData/$(basename $f) $temp | tee $PathOfOutPutData/$(basename $f)/Run${temp}_Analyzer.log
		echo -e "\n\n\t\tAnalyzer Done\n\n"
	fi

	LC1=$(sed -n '/Loading the trees.../{n;n;n;n;n;p;}'	$PathOfOutPutData/$(basename $f)/Run${temp}_Analyzer.log | awk '{print $1}')
	LC2=$(sed -n '/Loading the trees.../{n;n;n;n;p;  }' $PathOfOutPutData/$(basename $f)/Run${temp}_Analyzer.log | awk '{print $1}')
	LC3=$(sed -n '/Loading the trees.../{n;n;n;p;    }' $PathOfOutPutData/$(basename $f)/Run${temp}_Analyzer.log | awk '{print substr($1,5)}')  
	LC1_Err=$(sed -n '/Loading the trees.../{n;n;n;n;n;p;}' $PathOfOutPutData/$(basename $f)/Run${temp}_Analyzer.log | awk '{print $2}')
	LC2_Err=$(sed -n '/Loading the trees.../{n;n;n;n;p;  }' $PathOfOutPutData/$(basename $f)/Run${temp}_Analyzer.log | awk '{print $2}')
	LC3_Err=$(sed -n '/Loading the trees.../{n;n;n;p;    }' $PathOfOutPutData/$(basename $f)/Run${temp}_Analyzer.log | awk '{print $2}')  

	echo -e "$(basename $f)\t\t $LC1+/-$LC1_Err \t $LC2+/-$LC2_Err \t $LC3+/-$LC3_Err" >> EfficiencyData_R${IRunNo}_R${FRunNo}.txt
	RunCounter=$[$RunCounter+1]
  done
done


echo "file(s) of interest:" 

rm FilesToAnalyze.txt
echo "EfficiencyData_R${IRunNo}_R${FRunNo}.txt" >> FilesToAnalyze.txt


while [ $ILat -le $FLat ]
do
  rm EfficiencyData_R${IRunNo}_R${FRunNo}_Lat${ILat}.txt
  grep "Lat$ILat" EfficiencyData_R${IRunNo}_R${FRunNo}.txt >> EfficiencyData_R${IRunNo}_R${FRunNo}_Lat${ILat}.txt

  outputFile=EfficiencyData_R${IRunNo}_R${FRunNo}_Lat${ILat}.txt
  outputFile_short=EfficiencyData_R${IRunNo}_R${FRunNo}_Lat${ILat}.txt

  if [ $(stat -c%s "$outputFile") -le 46 ]; then
    rm $outputFile
  else
    echo "gedit $outputFile"
    echo "EfficiencyData_R${IRunNo}_R${FRunNo}_Lat${ILat}.txt" >> FilesToAnalyze.txt
  fi
  
  ILat=$[$ILat+1]
done

cp FilesToAnalyze.txt FilesToAnalyze_R${IRunNo}_R${FRunNo}.txt

if [ "$mail" == 1 ]; then
	echo "mailing the Efficiency files.... "
	mail -a EfficiencyData_R${IRunNo}_R${FRunNo}.txt  -s "Efficiency Data from RunNumber ${IRunNo} to ${FRunNo}" $email < message.log
	echo "mail sent"
fi	

echo "To Make Efficiency Curves Execute In Terminal:"
echo "./analyzeEff.sh"
graceful_exit
