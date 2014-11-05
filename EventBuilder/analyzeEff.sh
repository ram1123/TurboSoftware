g++ -g -c `root-config --cflags` TestBeamAnalysis.C
g++ -g -o TestBeamAnalysis `root-config --glibs` TestBeamAnalysis.o
./TestBeamAnalysis
#root -l EffPlots.root
echo "Execute Command:"
echo "root -l EffPlots.root"
