void rd51_EventBuilderVFAT_Launcher(TString DataFile, TString RootFile, int NumberOfEntries)
{
  gROOT->ProcessLine(".x Load_EventBuilderVFAT.cpp");
  rd51_EventBuilderVFAT(DataFile, RootFile, NumberOfEntries);
}
  
