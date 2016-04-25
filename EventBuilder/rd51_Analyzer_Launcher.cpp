void rd51_Analyzer_Launcher(TString InputRecoFile, TString InputTrackerFile, TString OutputAnalyzerFile)
{
  gROOT->ProcessLine(".x Load_Analyzer.cpp");
  rd51_Analyzer(InputRecoFile,InputTrackerFile,OutputAnalyzerFile);
}

