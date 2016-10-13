void rd51_TrackFinder_Launcher(TString InputRootFile, TString Options = "RecoRoot", Int_t TotalEntries = 0, Int_t FirstEntry = 0)
{
gROOT->ProcessLine(".x Load_TrackFinder.cpp");
TFile file0(InputRootFile); 
rd51tbgeo->MakeSelector("rd51_EventBuilder_Class");
gROOT->ProcessLine(".L rd51_EventBuilder_Class.C++");
rd51tbgeo->Process("rd51_TrackFinder.C+", Options);
}
