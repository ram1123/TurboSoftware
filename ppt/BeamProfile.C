#include<iostream>
#include<vector>
#include<string>
#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TH2F.h"

int BeamProfile(TString RootFile, TString RecoFile, Int_t name)
{

	std::vector<TFile*> InputFiles;
	InputFiles.clear();
	
	InputFiles.push_back(TFile::Open(RootFile));

	const Int_t NumOfFiles = InputFiles.size();
	cout<<"Num of FIles = "<<NumOfFiles<<endl;

	for(unsigned int j = 0; j < InputFiles.size(); ++j ) {
	TTree * tmpTree = (TTree*)InputFiles.at(j)->Get("rd51tbgeo");
	tmpTree->AddFriend("trackertree",RecoFile);

	TCanvas *canvas_prof = new TCanvas("canvas_prof","canvas_prof",1);
	canvas_prof->Divide(2,2);
	cout<<"###################"<<endl;
	canvas_prof->cd(1);
	
	TH2F *hg1BeamProfile = new TH2F("hg1BeamProfile","Beam profile on Tracker 1", 10,0.,100.,10,0.,100.);
	tmpTree->Draw("g1ycl.geoposY:g1xcl.geoposX>>hg1BeamProfile","g1ycl@.GetEntries()==1 && g1xcl@.GetEntries()==1","colz");
	hg1BeamProfile->GetXaxis()->SetTitle("x position in mm");
	hg1BeamProfile->GetYaxis()->SetTitle("y position in mm");

	canvas_prof->cd(2);
	TH2F *hg2BeamProfile = new TH2F("hg2BeamProfile","Beam profile on Tracker 2", 10,0.,100.,10,0.,100.);
	tmpTree->Draw("g2ycl.geoposY:g2xcl.geoposX>>hg2BeamProfile","g2ycl@.GetEntries()==1 && g2xcl@.GetEntries()==1","colz");
	hg2BeamProfile->GetXaxis()->SetTitle("x position in mm");
	hg2BeamProfile->GetYaxis()->SetTitle("y position in mm");
	
	canvas_prof->cd(3);
	TH2F *hg3BeamProfile = new TH2F("hg3BeamProfile","Beam profile on Tracker 3", 10,0.,100.,10,0.,100.);
	tmpTree->Draw("g3ycl.geoposY:g3xcl.geoposX>>hg3BeamProfile","g3ycl@.GetEntries()==1 && g3xcl@.GetEntries()==1","colz");
	hg3BeamProfile->GetXaxis()->SetTitle("x position in mm");
	hg3BeamProfile->GetYaxis()->SetTitle("y position in mm");
	
	canvas_prof->SaveAs(Form("profile_plots_for_Trackers_%d.pdf",name));
	canvas_prof->Clear();

	delete gDirectory->FindObject("hg1BeamProfile");
	delete gDirectory->FindObject("hg2BeamProfile");
	delete gDirectory->FindObject("hg3BeamProfile");

	canvas_prof->Divide(3,2);

	canvas_prof->cd(1);
	TH1F *g1x = new TH1F("g1x","Hit Position on tracker 1 (x)", 10, 0,100);
	tmpTree->Draw("g1xcl.geoposX");
	g1x->GetXaxis()->SetTitle("X position in mm");
	g1x->GetYaxis()->SetTitle("Number of Hits");

	canvas_prof->cd(2);
	TH1F *g2x = new TH1F("g2x","Hit Position on tracker 2 (x)", 10, 0,100);
	tmpTree->Draw("g2xcl.geoposX");
	g2x->GetXaxis()->SetTitle("X position in mm");
	g2x->GetYaxis()->SetTitle("Number of Hits");

	canvas_prof->cd(3);
	TH1F *g3x = new TH1F("g3x","Hit Position on tracker 3 (x)", 10, 0,100);
	tmpTree->Draw("g3xcl.geoposX");
	g3x->GetXaxis()->SetTitle("X position in mm");
	g3x->GetYaxis()->SetTitle("Number of Hits");

	canvas_prof->cd(4);
	TH1F *g1y = new TH1F("g1y","Hit Position on tracker 1 (y)", 10, 0,100);
	tmpTree->Draw("g1ycl.geoposY");
	g1y->GetXaxis()->SetTitle("Y position in mm");
	g1y->GetYaxis()->SetTitle("Number of Hits");

	canvas_prof->cd(5);
	TH1F *g2y = new TH1F("g2y","Hit Position on tracker 2 (y)", 10, 0,100);
	tmpTree->Draw("g2ycl.geoposY");
	g2y->GetXaxis()->SetTitle("Y position in mm");
	g2y->GetYaxis()->SetTitle("Number of Hits");

	canvas_prof->cd(6);
	TH1F *g3y = new TH1F("g3y","Hit Position on tracker 3 (x)", 10, 0,100);
	tmpTree->Draw("g3ycl.geoposY");
	g3y->GetXaxis()->SetTitle("Y position in mm");
	g3y->GetYaxis()->SetTitle("Number of Hits");

	canvas_prof->SaveAs(Form("Tracker_Hit_position_%d.pdf",name));
	canvas_prof->Clear();

	delete gDirectory->FindObject("g1x");
	delete gDirectory->FindObject("g1y");
	delete gDirectory->FindObject("g2x");
	delete gDirectory->FindObject("g2y");
	delete gDirectory->FindObject("g3x");
	delete gDirectory->FindObject("g3y");

	canvas_prof->Divide(2,2);

	canvas_prof->cd(1);
	TH1F *LC1 = new TH1F("LC1","Hit Position on GE11_1 (x)", 10, 0,100);
	tmpTree->Draw("sCMSNS2LC1.geoposX");
	LC1->GetXaxis()->SetTitle("X position in mm");
	LC1->GetYaxis()->SetTitle("Number of Hits");

	canvas_prof->cd(2);
	TH1F *LC2 = new TH1F("LC2","Hit Position on GE11_2 (x)", 10, 0,100);
	tmpTree->Draw("sCMSNS2LC2.geoposX");
	LC2->GetXaxis()->SetTitle("X position in mm");
	LC2->GetYaxis()->SetTitle("Number of Hits");

	canvas_prof->cd(3);
	TH1F *LC3 = new TH1F("LC3","Hit Position on GE11_3 (x)", 10, 0,100);
	tmpTree->Draw("sCMSNS2LC3.geoposX");
	LC3->GetXaxis()->SetTitle("X position in mm");
	LC3->GetYaxis()->SetTitle("Number of Hits");

	canvas_prof->SaveAs(Form("GEM_Hit_position_%d.pdf",name));
	canvas_prof->Clear();

	delete gDirectory->FindObject("LC1");
	delete gDirectory->FindObject("LC2");
	delete gDirectory->FindObject("LC3");
	}
	}

