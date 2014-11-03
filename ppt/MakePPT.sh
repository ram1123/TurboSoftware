#!/bin/bash

#	-------------------------------------------------------------------
#
#	Shell program to Make the pdf presentation using latex.
#
#	Author: 2014, Ramkrishna Sharma,,, <ramkrishna.sharma71@gmail.com>.
#	
#	The structure of the program is created by a script prodived on LinuxCommand.org
#
#	Usage:
#
#		MakePPT.sh [ -h | --help ] [-n OutPutFileName] [-f FigureType]
#
#	Options:
#
#		-h, --help		Display this help message and exit.
#		-n  OutPutFileName	Name of Output File name
#		-f  FigureType  	Type Of figure file
#
#
#	Revision History:
#
#	10/28/2014	File created by new_script ver. 2.1.0
#
#	-------------------------------------------------------------------


#	-------------------------------------------------------------------
#	Constants
#	-------------------------------------------------------------------

	PROGNAME=$(basename $0)
	VERSION="0.0.1"


	FigureType=pdf
	OutPutFileName=ppt_test



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
	#rm $1.tex
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
	#echo "${PROGNAME}: ${1:-"Unknown Error"}" >&2
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

	echo "Usage: ${PROGNAME} [-h | --help] [-n OutPutFileName] [-f FigureType]"
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
	This is a program to Make the pdf presentation using latex.

	$(usage)

	Options:

	-h, --help		Display this help message and exit.
	-n  OutPutFileName	Name of Output File name
	-f  FigureType  	Type Of figure file

	
	
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

while getopts ":hn:f:" opt; do
	case $opt in
		n )	echo "Name of Output File name - argument = $OPTARG" 
			OutPutFileName=$OPTARG
			if [ "$OutPutFileName" == test -o "$OutPutFileName" == fig ]; then
				error_exit "Output File Name should not be fig or test."
			fi
			echo $OutPutFileName;;
		f )	echo "Type Of figure file - argument = $OPTARG" 
			FigureType=$OPTARG
			echo $FigureType;;
		h )	helptext
			graceful_exit ;;
		* )	usage
			clean_up
			exit 1
	esac
done


##### Main Logic #####

cp test.tex $OutPutFileName.tex	
count=1
for f in *.${FigureType}; do
    filename=$(basename  "$f")
    filename=${filename%.*}
    filename=${filename//_/ }
    echo $filename
    echo $f
    perl -spe 's/intime_mean_pu.pdf/$a/;
    s/TitleFrame/$b/' < fig.tex -- -a="$f" -b="$filename" > "fig_$count.tex"

    sed -i "/Pointer-rk/r fig_$count.tex" "$OutPutFileName.tex"
    ((++count))
done
pdflatex $OutPutFileName.tex
pdflatex $OutPutFileName.tex
gnome-open $OutPutFileName.pdf
rm fig_*.tex  $OutPutFileName.toc $OutPutFileName.snm $OutPutFileName.out $OutPutFileName.nav $OutPutFileName.aux $OutPutFileName.log
echo "Finished."

graceful_exit
