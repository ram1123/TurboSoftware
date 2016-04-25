#include "TString.h"

void script()
{
TString CRC("CRC.root");
TString RECO("RECO.root");
TString AN("AN.root");

gROOT->ProcessLine(".L analyzer.C");
BeamProfile(CRC,RECO,AN);
}
