source rd51_SetEnvironment.sh
rm -v -f Class_Reco*.*
rm -v -f Class_Tracker*.*
root -b -l -q 'ClassMaker_RecoTracker.cpp("'$1'","'$2'")'
