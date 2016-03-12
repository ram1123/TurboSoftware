#include<iostream>
#include<vector>
#include<string>
#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TH2F.h"

int BeamProfile(TString RootFile,TString RecoFile, Int_t name)
{

        TGaxis::SetMaxDigits(3);

	std::vector<TFile*> InputFiles;
	InputFiles.clear();
	
	InputFiles.push_back(TFile::Open(RootFile));

	const Int_t NumOfFiles = InputFiles.size();
	cout<<"Num of FIles = "<<NumOfFiles<<endl;

	for(unsigned int j = 0; j < InputFiles.size(); ++j ) {
	TTree * tmpTree = (TTree*)InputFiles.at(j)->Get("rd51tbgeo");
	tmpTree->AddFriend("trackertree",RecoFile);
	}

	TCanvas *canvas = new TCanvas("canvas","canvas",1);
	gStyle->SetCanvasDefH(400);
	gStyle->SetCanvasDefW(600);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	//	BEAM PROFILE PLOTS
	////////////////////////////////////////////////////////////////////////////////////////////////////
	
	// Prefix
	//canvas->SetLogz();

	// Tracker 1
	TH2F *t1BeamProfile = new TH2F("t1BeamProfile","Beam profile on Tracker 1", 25,0.,100.,25,0.,100.);
	t1BeamProfile->SetStats(0);
	tmpTree->Draw("g1ycl.geoposY:g1xcl.geoposX>>t1BeamProfile","g1ycl@.GetEntries()==1 && g1xcl@.GetEntries()==1 && trackx.q>0 && tracky.q>0","colz");
	t1BeamProfile->GetXaxis()->SetTitle("x position in mm");
	t1BeamProfile->GetYaxis()->SetTitle("y position in mm");

	canvas->SaveAs(Form("Profile_Tracker1_Run%d.png",name));

	// Tracker 2

	TH2F *t2BeamProfile = new TH2F("t2BeamProfile","Beam profile on Tracker 2", 25,0.,100.,25,0.,100.);
	t2BeamProfile->SetStats(0);
	tmpTree->Draw("g2ycl.geoposY:g2xcl.geoposX>>t2BeamProfile","g2ycl@.GetEntries()==1 && g2xcl@.GetEntries()==1 && trackx.q>0 && tracky.q>0","colz");
	t2BeamProfile->GetXaxis()->SetTitle("x position in mm");
	t2BeamProfile->GetYaxis()->SetTitle("y position in mm");

	canvas->SaveAs(Form("Profile_Tracker2_Run%d.png",name));

	// B2B GEM
	
	TH2F *DetBeamProfile = new TH2F("DetBeamProfile","Beam profile on B2B GEM", 25,0.,100.,25,0.,100.);
	DetBeamProfile->SetStats(0);
	tmpTree->Draw("g3ycl.geoposY:g3xcl.geoposX>>DetBeamProfile","g3ycl@.GetEntries()==1 && g3xcl@.GetEntries()==1 && trackx.q>0 && tracky.q>0","colz");
	DetBeamProfile->GetXaxis()->SetTitle("x position in mm");
	DetBeamProfile->GetYaxis()->SetTitle("y position in mm");

	canvas->SaveAs(Form("Profile_B2B_Run%d.png",name)); 


	////////////////////////////////////////////////////////////////////////////////////////////////////
	//	EFFICIENCY
	////////////////////////////////////////////////////////////////////////////////////////////////////

	Int_t t1 = t1BeamProfile->GetEntries();
	Int_t t2 = t2BeamProfile->GetEntries();
	Int_t det = DetBeamProfile->GetEntries();

	cout << endl;
	cout << "Number of valid hits at Tracker 1: " << t1 << endl;
	cout << "Number of valid hits at Tracker 2: " << t2 << endl;
	cout << "Number of valid hits at B2B GEM  : " << det << endl;
	cout << endl;
	cout << "Efficiency: " << det/t1 << endl;
	cout << endl;
}
