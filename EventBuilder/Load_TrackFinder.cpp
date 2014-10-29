{
  gROOT->Reset();
  gSystem->AddIncludePath("-I$PATH");
  gInterpreter->AddIncludePath("$PATH");
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(1002210);
  gStyle->SetOptDate();
  gROOT->ProcessLine(".L Loaders/LoaderSettings_TrackFinder.cpp+");
  gROOT->ProcessLine(".L Loaders/LoaderOffset.cpp+");
  gROOT->ProcessLine(".L Clustering/Config.cpp+");
  gROOT->ProcessLine(".L Mapping/TotemT2.cpp+");
  gROOT->ProcessLine(".L Mapping/TotemT1LG.cpp+");
  gROOT->ProcessLine(".L Mapping/ReadoutType.cpp+");
  gROOT->ProcessLine(".L Clustering/DataArray_T.cpp+");
  gROOT->ProcessLine(".L Clustering/GeoDataArray_T.cpp+");
 //gROOT->ProcessLine(".L rd51_EventBuilderVFAT.C+");
}
  
