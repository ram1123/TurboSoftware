#include "TString.h"

void script()
{
TString CRC("CRC-Run0003_backtoback_newdata3_newHV-160125_173510-0.root");
TString RECO("RECO-CRC-Run0003_backtoback_newdata3_newHV-160125_173510-0.root");
Int_t name = 3;

gROOT->ProcessLine(".L Analyzer.C");
BeamProfile(CRC,RECO,name);
}
