#include<iostream>
#include<vector>
#include<string>
#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TH2F.h"

//Settings:
bool SetLogscale = false;


int rd51_Analyzer(TString RootFile,TString RecoFile, TString OutputFile)
{
	TGaxis::SetMaxDigits(3);

	std::vector<TFile*> InputFiles;
	InputFiles.clear();
	
	InputFiles.push_back(TFile::Open(RootFile));

	const Int_t NumOfFiles = InputFiles.size();

	for(unsigned int j = 0; j < InputFiles.size(); ++j ) {
	TTree * tmpTree = (TTree*)InputFiles.at(j)->Get("rd51tbgeo");
	tmpTree->AddFriend("trackertree",RecoFile);
	}

	TFile Output(OutputFile,"recreate");
	TCanvas *canvas = new TCanvas();


	////////////////////////////////////////////////////////////////////////////////////////////////////
	//	BEAM PROFILE PLOTS
	////////////////////////////////////////////////////////////////////////////////////////////////////
	
	// Prefix
	if(SetLogscale) {
		canvas->SetLogz();
	}

	// Tracker 1
	TH2F *t1BeamProfile = new TH2F("t1BeamProfile","Beam profile on Tracker 1", 25,0.,100.,25,0.,100.);
	tmpTree->Draw("g1ycl.geoposY:g1xcl.geoposX>>t1BeamProfile","g1ycl@.GetEntries()==1 && g1xcl@.GetEntries()==1 && trackx.q>0 && tracky.q>0","colz");
	t1BeamProfile->SetStats(0);
	t1BeamProfile->GetXaxis()->SetTitle("x position in mm");
	t1BeamProfile->GetYaxis()->SetTitle("y position in mm");

	canvas->Write("t1BeamProfile");

	// Tracker 2

	TH2F *t2BeamProfile = new TH2F("t2BeamProfile","Beam profile on Tracker 2", 25,0.,100.,25,0.,100.);
	tmpTree->Draw("g2ycl.geoposY:g2xcl.geoposX>>t2BeamProfile","g2ycl@.GetEntries()==1 && g2xcl@.GetEntries()==1 && trackx.q>0 && tracky.q>0","colz");
	t2BeamProfile->SetStats(0);
	t2BeamProfile->GetXaxis()->SetTitle("x position in mm");
	t2BeamProfile->GetYaxis()->SetTitle("y position in mm");

	canvas->Write("t2BeamProfile");

	// B2B GEM
	
	TH2F *b2bBeamProfile = new TH2F("b2bBeamProfile","Beam profile on B2B GEM", 25,0.,100.,25,0.,100.);
	tmpTree->Draw("g3ycl.geoposY:g3xcl.geoposX>>b2bBeamProfile","g3ycl@.GetEntries()==1 && g3xcl@.GetEntries()==1 && trackx.q>0 && tracky.q>0","colz");;
	b2bBeamProfile->SetStats(0);
	b2bBeamProfile->GetXaxis()->SetTitle("x position in mm");
	b2bBeamProfile->GetYaxis()->SetTitle("y position in mm");

	canvas->Write("b2bBeamProfile");

	// FTM

/*	TH2F *ftmBeamProfile = new TH2F("ftmBeamProfile","Beam profile on FTM", 25,0.,100.,25,0.,100.);
	tmpTree->Draw("g4ycl.geoposY:g4xcl.geoposX>>ftmBeamProfile","g4ycl@.GetEntries()==1 && g4xcl@.GetEntries()==1 && trackx.q>0 && tracky.q>0","colz");
	ftmBeamProfile->SetStats(0);
	ftmBeamProfile->GetXaxis()->SetTitle("x position in mm");
	ftmBeamProfile->GetYaxis()->SetTitle("y position in mm");

	canvas->Write("ftmBeamProfile");	*/

	// Suffix
	canvas->Close();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	//	EFFICIENCY
	////////////////////////////////////////////////////////////////////////////////////////////////////

	// One expects that t1Entry == t2Entry
	Int_t t1Entry = t1BeamProfile->GetEntries();
	Int_t t2Entry = t2BeamProfile->GetEntries();

	if(t1Entry != t2Entry) {
		cout << endl;
		cout << "Valid hits of trackers to not match!" << endl;
		cout << endl;
	}
	else {
		Int_t b2bEntry = b2bBeamProfile->GetEntries();
		Double_t b2bEff = b2bBeamProfile->GetEntries() / t1BeamProfile->GetEntries();
/*		Int_t ftmEntry = ftmBeamProfile->GetEntries();
		Double_t ftmEff = ftmBeamProfile->GetEntries() / t1BeamProfile->GetEntries();	*/

		cout << endl;
		cout << "Number of valid hits at Trackers : " << t1Entry << endl;
		cout << "Number of valid hits at B2B GEM  : " << b2bEntry << endl;
		cout << "   > Efficiency B2B GEM          : " << b2bEff << endl;
/*		cout << "Number of valid hits at FTM      : " << ftmEntry << endl;
		cout << "   > Efficiency FTM              : " << ftmEff << endl;	*/
		cout << endl;
	}
}
