# Check for proper number of command line args.
HERE=$(pwd)
EXPECTED_ARGS_MIN=1
EXPECTED_ARGS_MAX=1

if [ $# -lt $EXPECTED_ARGS_MIN -o $# -gt $EXPECTED_ARGS_MAX ];
then
  echo ""
  echo "Usage:          ./`basename $0` Directory_With_File_That_Have_To_Be_Set_In_UNIX_format"
  echo ""
  echo "The following files will be modified: *.C, *.h, *.cpp, *.hpp, .sh, *.conf, *.dat, *.root"
  echo "All the files except .sh will be defined as not exeutable"
  exit
fi
DIR0=$1
chmod o-w $DIR0
################################################################################################
for DATAFILE in $(ls -d $DIR0/*); do 
	chmod o-w $DATAFILE 
	done;
for DATAFILE in $(ls $DIR0/*.sh); do 
	echo $DATAFILE
	vi -c ':set ff=unix' -c wq! $DATAFILE
	done;
for DATAFILE in $(ls $DIR0/*.conf); do
	echo $DATAFILE
	chmod ugo-x $DATAFILE 
        vi -c ':set ff=unix' -c wq! $DATAFILE
done;
for DATAFILE in $(ls $DIR0/*.hpp); do
	echo $DATAFILE
	chmod ugo-x $DATAFILE 
        vi -c ':set ff=unix' -c wq! $DATAFILE
done;
for DATAFILE in $(ls $DIR0/*.cpp); do
	echo $DATAFILE
	chmod ugo-x $DATAFILE 
        vi -c ':set ff=unix' -c wq! $DATAFILE
done;
for DATAFILE in $(ls $DIR0/*.C); do
	echo $DATAFILE
	chmod ugo-x $DATAFILE 
        vi -c ':set ff=unix' -c wq! $DATAFILE
done;
for DATAFILE in $(ls $DIR0/*.h); do
	echo $DATAFILE
	chmod ugo-x $DATAFILE 
        vi -c ':set ff=unix' -c wq! $DATAFILE
done;
for DATAFILE in $(ls $DIR0/*.root); do
	echo $DATAFILE
	chmod ugo-x $DATAFILE 
done;
for DATAFILE in $(ls $DIR0/*.dat); do
	echo $DATAFILE
	chmod ugo-x $DATAFILE 
done;
####################################################################################################
DIR0=$1"/*/"
################################################################################################
for DATAFILE in $(ls -d $DIR0/*); do 
	chmod o-w $DATAFILE 
	done;
for DATAFILE in $(ls $DIR0/*.sh); do 
	echo $DATAFILE
	vi -c ':set ff=unix' -c wq! $DATAFILE
	done;
for DATAFILE in $(ls $DIR0/*.conf); do
	echo $DATAFILE
	chmod ugo-x $DATAFILE 
        vi -c ':set ff=unix' -c wq! $DATAFILE
done;
for DATAFILE in $(ls $DIR0/*.hpp); do
	echo $DATAFILE
	chmod ugo-x $DATAFILE 
        vi -c ':set ff=unix' -c wq! $DATAFILE
done;
for DATAFILE in $(ls $DIR0/*.cpp); do
	echo $DATAFILE
	chmod ugo-x $DATAFILE 
        vi -c ':set ff=unix' -c wq! $DATAFILE
done;
for DATAFILE in $(ls $DIR0/*.C); do
	echo $DATAFILE
	chmod ugo-x $DATAFILE 
        vi -c ':set ff=unix' -c wq! $DATAFILE
done;
for DATAFILE in $(ls $DIR0/*.h); do
	echo $DATAFILE
	chmod ugo-x $DATAFILE 
        vi -c ':set ff=unix' -c wq! $DATAFILE
done;
for DATAFILE in $(ls $DIR0/*.root); do
	echo $DATAFILE
	chmod ugo-x $DATAFILE 
done;
for DATAFILE in $(ls $DIR0/*.dat); do
	echo $DATAFILE
	chmod ugo-x $DATAFILE 
done;
####################################################################################################
DIR0=$1"/*/*/"
################################################################################################
for DATAFILE in $(ls -d $DIR0/*); do 
	chmod o-w $DATAFILE 
	done;
for DATAFILE in $(ls $DIR0/*.sh); do 
	echo $DATAFILE
	vi -c ':set ff=unix' -c wq! $DATAFILE
	done;
for DATAFILE in $(ls $DIR0/*.conf); do
	echo $DATAFILE
	chmod ugo-x $DATAFILE 
        vi -c ':set ff=unix' -c wq! $DATAFILE
done;
for DATAFILE in $(ls $DIR0/*.hpp); do
	echo $DATAFILE
	chmod ugo-x $DATAFILE 
        vi -c ':set ff=unix' -c wq! $DATAFILE
done;
for DATAFILE in $(ls $DIR0/*.cpp); do
	echo $DATAFILE
	chmod ugo-x $DATAFILE 
        vi -c ':set ff=unix' -c wq! $DATAFILE
done;
for DATAFILE in $(ls $DIR0/*.C); do
	echo $DATAFILE
	chmod ugo-x $DATAFILE 
        vi -c ':set ff=unix' -c wq! $DATAFILE
done;
for DATAFILE in $(ls $DIR0/*.h); do
	echo $DATAFILE
	chmod ugo-x $DATAFILE 
        vi -c ':set ff=unix' -c wq! $DATAFILE
done;
for DATAFILE in $(ls $DIR0/*.root); do
	echo $DATAFILE
	chmod ugo-x $DATAFILE 
done;
for DATAFILE in $(ls $DIR0/*.dat); do
	echo $DATAFILE
	chmod ugo-x $DATAFILE 
done;
####################################################################################################
DIR0=$1"/*/*/*/"
################################################################################################
for DATAFILE in $(ls -d $DIR0/*); do 
	chmod o-w $DATAFILE 
	done;
for DATAFILE in $(ls $DIR0/*.sh); do 
	echo $DATAFILE
	vi -c ':set ff=unix' -c wq! $DATAFILE
	done;
for DATAFILE in $(ls $DIR0/*.conf); do
	echo $DATAFILE
	chmod ugo-x $DATAFILE 
        vi -c ':set ff=unix' -c wq! $DATAFILE
done;
for DATAFILE in $(ls $DIR0/*.hpp); do
	echo $DATAFILE
	chmod ugo-x $DATAFILE 
        vi -c ':set ff=unix' -c wq! $DATAFILE
done;
for DATAFILE in $(ls $DIR0/*.cpp); do
	echo $DATAFILE
	chmod ugo-x $DATAFILE 
        vi -c ':set ff=unix' -c wq! $DATAFILE
done;
for DATAFILE in $(ls $DIR0/*.C); do
	echo $DATAFILE
	chmod ugo-x $DATAFILE 
        vi -c ':set ff=unix' -c wq! $DATAFILE
done;
for DATAFILE in $(ls $DIR0/*.h); do
	echo $DATAFILE
	chmod ugo-x $DATAFILE 
        vi -c ':set ff=unix' -c wq! $DATAFILE
done;
for DATAFILE in $(ls $DIR0/*.root); do
	echo $DATAFILE
	chmod ugo-x $DATAFILE 
done;
for DATAFILE in $(ls $DIR0/*.dat); do
	echo $DATAFILE
	chmod ugo-x $DATAFILE 
done;
####################################################################################################
DIR0=$1"/*/*/*/*/"
################################################################################################
for DATAFILE in $(ls -d $DIR0/*); do 
	chmod o-w $DATAFILE 
	done;
for DATAFILE in $(ls $DIR0/*.sh); do 
	echo $DATAFILE
	vi -c ':set ff=unix' -c wq! $DATAFILE
	done;
for DATAFILE in $(ls $DIR0/*.conf); do
	echo $DATAFILE
	chmod ugo-x $DATAFILE 
        vi -c ':set ff=unix' -c wq! $DATAFILE
done;
for DATAFILE in $(ls $DIR0/*.hpp); do
	echo $DATAFILE
	chmod ugo-x $DATAFILE 
        vi -c ':set ff=unix' -c wq! $DATAFILE
done;
for DATAFILE in $(ls $DIR0/*.cpp); do
	echo $DATAFILE
	chmod ugo-x $DATAFILE 
        vi -c ':set ff=unix' -c wq! $DATAFILE
done;
for DATAFILE in $(ls $DIR0/*.C); do
	echo $DATAFILE
	chmod ugo-x $DATAFILE 
        vi -c ':set ff=unix' -c wq! $DATAFILE
done;
for DATAFILE in $(ls $DIR0/*.h); do
	echo $DATAFILE
	chmod ugo-x $DATAFILE 
        vi -c ':set ff=unix' -c wq! $DATAFILE
done;
for DATAFILE in $(ls $DIR0/*.root); do
	echo $DATAFILE
	chmod ugo-x $DATAFILE 
done;
for DATAFILE in $(ls $DIR0/*.dat); do
	echo $DATAFILE
	chmod ugo-x $DATAFILE 
done;
####################################################################################################
DIR0=$1"/*/*/*/*/*/"
################################################################################################
for DATAFILE in $(ls -d $DIR0/*); do 
	chmod o-w $DATAFILE 
	done;
for DATAFILE in $(ls $DIR0/*.sh); do 
	echo $DATAFILE
	vi -c ':set ff=unix' -c wq! $DATAFILE
	done;
for DATAFILE in $(ls $DIR0/*.conf); do
	echo $DATAFILE
	chmod ugo-x $DATAFILE 
        vi -c ':set ff=unix' -c wq! $DATAFILE
done;
for DATAFILE in $(ls $DIR0/*.hpp); do
	echo $DATAFILE
	chmod ugo-x $DATAFILE 
        vi -c ':set ff=unix' -c wq! $DATAFILE
done;
for DATAFILE in $(ls $DIR0/*.cpp); do
	echo $DATAFILE
	chmod ugo-x $DATAFILE 
        vi -c ':set ff=unix' -c wq! $DATAFILE
done;
for DATAFILE in $(ls $DIR0/*.C); do
	echo $DATAFILE
	chmod ugo-x $DATAFILE 
        vi -c ':set ff=unix' -c wq! $DATAFILE
done;
for DATAFILE in $(ls $DIR0/*.h); do
	echo $DATAFILE
	chmod ugo-x $DATAFILE 
        vi -c ':set ff=unix' -c wq! $DATAFILE
done;
for DATAFILE in $(ls $DIR0/*.root); do
	echo $DATAFILE
	chmod ugo-x $DATAFILE 
done;
for DATAFILE in $(ls $DIR0/*.dat); do
	echo $DATAFILE
	chmod ugo-x $DATAFILE 
done;
####################################################################################################
