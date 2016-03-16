void rd51_Analyzer_Launcher(TString InputRecoFile, TString InputTrackerFile, TString OutputAnalyzerFile)
{
	gROOT->ProcessLine(".L rd51_Analyzer.C");
	rd51_Analyzer(InputRecoFile,InputTrackerFile,OutputAnalyzerFile);
}

