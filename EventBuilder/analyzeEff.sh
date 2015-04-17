#usage: ./analyzeEff.sh <InitialRun#> <FinalRun#>

cp FilesToAnalyze/Eff/FilesToAnalyze_R$1_R$2.txt FilesToAnalyze.txt

#sh -c "ulimit -s 32768"
#sh "ulimit -c unlimited"
g++ -g -c `root-config --cflags --glibs --libs` TestBeamAnalysis.C
g++ -g -o TestBeamAnalysis `root-config --cflags --glibs --libs` TestBeamAnalysis.o
./TestBeamAnalysis

cp EffPlots.root EffPlots_R$1_R$2.root

echo "Execute Command:"
echo "root -l EffPlots_R$1_R$2.root"
