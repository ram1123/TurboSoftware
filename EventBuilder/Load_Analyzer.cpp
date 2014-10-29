{
  gROOT->Reset();
  gSystem->AddIncludePath("-I$PATH");
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(1002210);
  gStyle->SetOptDate();
  gROOT->ProcessLine(".L Class_Reco.C+");
  gROOT->ProcessLine(".L Class_Tracker.C+");
  gROOT->ProcessLine(".L Loaders/LoaderSettings_Analyzer.cpp+");
  gROOT->ProcessLine(".L Loaders/LoaderOffsetAndCoverage_Analyzer.cpp+");
  gROOT->ProcessLine(".L rd51_Analyzer.C+");
}
