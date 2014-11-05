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
	gROOT->SetStyle("Plain");
    	gStyle->SetOptFit(1111);
        gStyle->SetOptStat(1111);
    	gStyle->SetPalette(1);        

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

//	canvas_prof->Divide(3,2);
//
//	canvas_prof->cd(1);
//	TH1F *g1x = new TH1F("g1x","Hit Position on tracker 1 (x)", 10, 0,100);
//	tmpTree->Draw("g1xcl.geoposX");
//	g1x->GetXaxis()->SetTitle("X position in mm");
//	g1x->GetYaxis()->SetTitle("Number of Hits");
//
//	canvas_prof->cd(2);
//	TH1F *g2x = new TH1F("g2x","Hit Position on tracker 2 (x)", 10, 0,100);
//	tmpTree->Draw("g2xcl.geoposX");
//	g2x->GetXaxis()->SetTitle("X position in mm");
//	g2x->GetYaxis()->SetTitle("Number of Hits");
//
//	canvas_prof->cd(3);
//	TH1F *g3x = new TH1F("g3x","Hit Position on tracker 3 (x)", 10, 0,100);
//	tmpTree->Draw("g3xcl.geoposX");
//	g3x->GetXaxis()->SetTitle("X position in mm");
//	g3x->GetYaxis()->SetTitle("Number of Hits");
//
//	canvas_prof->cd(4);
//	TH1F *g1y = new TH1F("g1y","Hit Position on tracker 1 (y)", 10, 0,100);
//	tmpTree->Draw("g1ycl.geoposY");
//	g1y->GetXaxis()->SetTitle("Y position in mm");
//	g1y->GetYaxis()->SetTitle("Number of Hits");
//
//	canvas_prof->cd(5);
//	TH1F *g2y = new TH1F("g2y","Hit Position on tracker 2 (y)", 10, 0,100);
//	tmpTree->Draw("g2ycl.geoposY");
//	g2y->GetXaxis()->SetTitle("Y position in mm");
//	g2y->GetYaxis()->SetTitle("Number of Hits");
//
//	canvas_prof->cd(6);
//	TH1F *g3y = new TH1F("g3y","Hit Position on tracker 3 (x)", 10, 0,100);
//	tmpTree->Draw("g3ycl.geoposY");
//	g3y->GetXaxis()->SetTitle("Y position in mm");
//	g3y->GetYaxis()->SetTitle("Number of Hits");
//
//	canvas_prof->SaveAs(Form("Tracker_Hit_position_%d.pdf",name));
//	canvas_prof->Clear();
//
//	delete gDirectory->FindObject("g1x");
//	delete gDirectory->FindObject("g1y");
//	delete gDirectory->FindObject("g2x");
//	delete gDirectory->FindObject("g2y");
//	delete gDirectory->FindObject("g3x");
//	delete gDirectory->FindObject("g3y");
//
//	canvas_prof->Divide(2,2);
//
//	canvas_prof->cd(1);
//	TH1F *LC1 = new TH1F("LC1","Hit Position on GE11_1 (x)", 10, 0,100);
//	tmpTree->Draw("sCMSNS2LC1.geoposX");
//	LC1->GetXaxis()->SetTitle("X position in mm");
//	LC1->GetYaxis()->SetTitle("Number of Hits");
//
//	canvas_prof->cd(2);
//	TH1F *LC2 = new TH1F("LC2","Hit Position on GE11_2 (x)", 10, 0,100);
//	tmpTree->Draw("sCMSNS2LC2.geoposX");
//	LC2->GetXaxis()->SetTitle("X position in mm");
//	LC2->GetYaxis()->SetTitle("Number of Hits");
//
//	canvas_prof->cd(3);
//	TH1F *LC3 = new TH1F("LC3","Hit Position on GE11_3 (x)", 10, 0,100);
//	tmpTree->Draw("sCMSNS2LC3.geoposX");
//	LC3->GetXaxis()->SetTitle("X position in mm");
//	LC3->GetYaxis()->SetTitle("Number of Hits");
//
//	canvas_prof->SaveAs(Form("GEM_Hit_position_%d.pdf",name));
//	canvas_prof->Clear();
//
//	delete gDirectory->FindObject("LC1");
//	delete gDirectory->FindObject("LC2");
//	delete gDirectory->FindObject("LC3");
        
//=========== ADDED BY PATRIZIA ================
        
//        canvas_prof->Divide(3,2);
//        
//        canvas_prof->cd(1);
//        TH2F *h4 = new TH2F("h4","X correlation g1vsg2",100,0,100,100,0,100);
//        tmpTree->Draw("g2xcl.geoposX:g1xcl.geoposX>>h4","trackx@.GetEntries()==1 && tracky@.GetEntries()==1 && trackx.q>0 && tracky.q>0","colz");
//        h4->GetYaxis()->SetTitle("g2xcl.geoposX");
//        h4->GetXaxis()->SetTitle("g1xcl.geoposX");
//        h4->GetYaxis()->SetTitleOffset(1.3);
//        
//        canvas_prof->cd(2);
//        TH2F *h5 = new TH2F("h5","X correlation g2vsg3",100,0,100,100,0,100);
//        tmpTree->Draw("g2xcl.geoposX:g3xcl.geoposX>>h5","trackx@.GetEntries()==1 && tracky@.GetEntries()==1 && trackx.q>0 && tracky.q>0","colz"); ////X
//        h5->GetYaxis()->SetTitle("g2xcl.geoposX");
//        h5->GetXaxis()->SetTitle("g3xcl.geoposX");
//        h5->GetYaxis()->SetTitleOffset(1.3);
//        
//        canvas_prof->cd(3);
//        TH2F *h6 = new TH2F("h6","X correlation g1vsg3",100,0,100,100,0,100);
//        tmpTree->Draw("g3xcl.geoposX:g1xcl.geoposX>>h6","trackx@.GetEntries()==1 && tracky@.GetEntries()==1 && trackx.q>0 && tracky.q>0","colz"); ////X
//        h6->GetYaxis()->SetTitle("g3xcl.geoposX");
//        h6->GetXaxis()->SetTitle("g1xcl.geoposX");
//        h6->GetYaxis()->SetTitleOffset(1.3);
//        
//        canvas_prof->cd(4);
//        TH2F *h7 = new TH2F("h7","Y correlation g1vsg2",100,0,100,100,0,100);
//        tmpTree->Draw("g2ycl.geoposY:g1ycl.geoposY>>h7","trackx@.GetEntries()==1 && tracky@.GetEntries()==1 && trackx.q>0 && tracky.q>0","colz"); ////X
//        h7->GetYaxis()->SetTitle("g2ycl.geoposY");
//        h7->GetXaxis()->SetTitle("g1ycl.geoposY");
//        h7->GetYaxis()->SetTitleOffset(1.3);
//        
//        canvas_prof->cd(5);
//        TH2F *h8 = new TH2F("h8","Y correlation g2vsg3",100,0,100,100,0,100);
//        tmpTree->Draw("g2ycl.geoposY:g3ycl.geoposY>>h8","trackx@.GetEntries()==1 && tracky@.GetEntries()==1 && trackx.q>0 && tracky.q>0","colz"); ////X
//        h8->GetYaxis()->SetTitle("g2ycl.geoposY");
//        h8->GetXaxis()->SetTitle("g3ycl.geoposY");
//        h8->GetYaxis()->SetTitleOffset(1.3);
//        
//        canvas_prof->cd(6);
//        TH2F *h9 = new TH2F("h9","Y correlation g1vsg3",100,0,100,100,0,100);
//        tmpTree->Draw("g3ycl.geoposY:g1ycl.geoposY>>h9","trackx@.GetEntries()==1 && tracky@.GetEntries()==1 && trackx.q>0 && tracky.q>0","colz"); ////X
//        h9->GetYaxis()->SetTitle("g3ycl.geoposY");
//        h9->GetXaxis()->SetTitle("g1ycl.geoposY");
//        h9->GetYaxis()->SetTitleOffset(1.3);
//        
//        canvas_prof->SaveAs(Form("Trackers_Y-Correlations_Run%d.pdf",name));
//        canvas_prof->Clear();
//        
//        delete gDirectory->FindObject("h4");
//        delete gDirectory->FindObject("h5");
//        delete gDirectory->FindObject("h6");
//        delete gDirectory->FindObject("h7");
//        delete gDirectory->FindObject("h8");
//        delete gDirectory->FindObject("h9");
        
        canvas_prof->Divide(3,2);
        
        canvas_prof->cd(1);
        TH2F *h4 = new TH2F("h4","Fit X correlation g1vsg2",100,0,100,100,0,100);
        tmpTree->Draw("g2xcl.geoposX:g1xcl.geoposX>>h4","trackx@.GetEntries()==1 && tracky@.GetEntries()==1 && trackx.q>0 && tracky.q>0","colz"); ////X
        TProfile *prof2a = h4->ProfileX();
        prof2a->Fit("pol1","","",30,90);
        pol1->SetLineColor(2);
        h4->GetYaxis()->SetTitle("g2xcl.geoposX");
        h4->GetXaxis()->SetTitle("g1xcl.geoposX");
        h4->GetYaxis()->SetTitleOffset(1.3);
        
        canvas_prof->cd(2);
        TH2F *h5 = new TH2F("h5","Fit X correlation g2vsg3",100,0,100,100,0,100);
        tmpTree->Draw("g2xcl.geoposX:g3xcl.geoposX>>h5","trackx@.GetEntries()==1 && tracky@.GetEntries()==1 && trackx.q>0 && tracky.q>0","colz"); ////X
        TProfile *prof2b = h5->ProfileX();
        prof2b->Fit("pol1","","",30,90);
        pol1->SetLineColor(2);
        h5->GetYaxis()->SetTitle("g2xcl.geoposX");
        h5->GetXaxis()->SetTitle("g3xcl.geoposX");
        h5->GetYaxis()->SetTitleOffset(1.3);
        
        canvas_prof->cd(3);
        TH2F *h6 = new TH2F("h6","Fit X correlation g1vsg3",100,0,100,100,0,100);
        tmpTree->Draw("g3xcl.geoposX:g1xcl.geoposX>>h6","trackx@.GetEntries()==1 && tracky@.GetEntries()==1 && trackx.q>0 && tracky.q>0","colz"); ////X
        TProfile *prof2c = h6->ProfileX();
        prof2c->Fit("pol1","","",30,90);
        pol1->SetLineColor(2);
        h6->GetYaxis()->SetTitle("g3xcl.geoposX");
        h6->GetXaxis()->SetTitle("g1xcl.geoposX");
        h6->GetYaxis()->SetTitleOffset(1.3);
        
        canvas_prof->cd(4);
        TH2F *h7 = new TH2F("h7","Fit Y correlation g1vsg2",100,0,100,100,0,100);
        tmpTree->Draw("g2ycl.geoposY:g1ycl.geoposY>>h7","trackx@.GetEntries()==1 && tracky@.GetEntries()==1 && trackx.q>0 && tracky.q>0","colz"); ////X
        TProfile *prof2d = h7->ProfileX();
        prof2d->Fit("pol1","","",30,90);
        pol1->SetLineColor(2);
        h7->GetYaxis()->SetTitle("g2ycl.geoposY");
        h7->GetXaxis()->SetTitle("g1ycl.geoposY");
        h7->GetYaxis()->SetTitleOffset(1.3);
        
        canvas_prof->cd(5);
        TH2F *h8 = new TH2F("h8","Fit Y correlation g2vsg3",100,0,100,100,0,100);
        tmpTree->Draw("g2ycl.geoposY:g3ycl.geoposY>>h8","trackx@.GetEntries()==1 && tracky@.GetEntries()==1 && trackx.q>0 && tracky.q>0","colz"); ////X
        TProfile *prof2e = h8->ProfileX();
        prof2e->Fit("pol1","","",30,90);
        pol1->SetLineColor(2);
        h8->GetYaxis()->SetTitle("g2ycl.geoposY");
        h8->GetXaxis()->SetTitle("g3ycl.geoposY");
        h8->GetYaxis()->SetTitleOffset(1.3);
        
        canvas_prof->cd(6);
        TH2F *h9 = new TH2F("h9","Fit Y correlation g1vsg3",100,0,100,100,0,100);
        tmpTree->Draw("g3ycl.geoposY:g1ycl.geoposY>>h9","trackx@.GetEntries()==1 && tracky@.GetEntries()==1 && trackx.q>0 && tracky.q>0","colz"); ////X
        TProfile *prof2f = h9->ProfileX();
        prof2f->Fit("pol1","","",30,90);
        pol1->SetLineColor(2);
        h9->GetYaxis()->SetTitle("g3ycl.geoposY");
        h9->GetXaxis()->SetTitle("g1ycl.geoposY");
        h9->GetYaxis()->SetTitleOffset(1.3);
        
        canvas_prof->SaveAs(Form("Fit_Trackers_XY-Correlations_Run%d.pdf",name));
        canvas_prof->Clear();
        
        delete gDirectory->FindObject("h4");
        delete gDirectory->FindObject("h5");
        delete gDirectory->FindObject("h6");
        delete gDirectory->FindObject("h7");
        delete gDirectory->FindObject("h8");
        delete gDirectory->FindObject("h9");
        
       

        canvas_prof->Divide(3,2);
        
        canvas_prof->cd(1);
        TH2F *h10 = new TH2F("h10","X correlation sCMSNS2LC1vsg1",100,0,100,100,0,100);
        tmpTree->Draw("sCMSNS2LC1.geoposX:g1xcl.geoposX >>h10","trackx@.GetEntries()==1 && tracky@.GetEntries()==1 && trackx.q>0 && tracky.q>0","colz"); ////X
        h10->GetYaxis()->SetTitle("sCMSNS2LC1.geoposX");
        h10->GetXaxis()->SetTitle("g1xcl.geoposX");
        h10->GetYaxis()->SetTitleOffset(1.3);
        
        canvas_prof->cd(2);
        TH2F *h11 = new TH2F("h11","X correlation sCMSNS2LC2vsg1",100,0,100,100,0,100);
        tmpTree->Draw("sCMSNS2LC2.geoposX:g1xcl.geoposX >>h11","trackx@.GetEntries()==1 && tracky@.GetEntries()==1 && trackx.q>0 && tracky.q>0","colz"); ////X
        h11->GetYaxis()->SetTitle("sCMSNS2LC2.geoposX");
        h11->GetXaxis()->SetTitle("g1xcl.geoposX");
        h11->GetYaxis()->SetTitleOffset(1.3);
        
        canvas_prof->cd(3);
        TH2F *h12 = new TH2F("h12","X correlation sCMSNS2LC3vsg1",100,0,100,100,0,100);
        tmpTree->Draw("sCMSNS2LC3.geoposX:g1xcl.geoposX >>h12","trackx@.GetEntries()==1 && tracky@.GetEntries()==1 && trackx.q>0 && tracky.q>0","colz"); ////X
        h12->GetYaxis()->SetTitle("sCMSNS2LC3.geoposX");
        h12->GetXaxis()->SetTitle("g1xcl.geoposX");
        h12->GetYaxis()->SetTitleOffset(1.3);
        
        canvas_prof->cd(4);
        TH2F *h10a = new TH2F("h10a","X correlation sCMSNS2LC1vsg1",100,0,100,100,0,100);
        tmpTree->Draw("sCMSNS2LC1.geoposX:g1xcl.geoposX >>h10a","trackx@.GetEntries()==1 && tracky@.GetEntries()==1 && trackx.q>0 && tracky.q>0","colz"); ////X
        ///use a TProfile to convert the 2-d to 1-d problem
        TProfile *prof2 = h10a->ProfileX();
        prof2->Fit("pol1","","",0,100);
        pol1->SetLineColor(2);
        
        canvas_prof->cd(5);
        TH2F *h11a = new TH2F("h11a","X correlation sCMSNS2LC2vsg1",100,0,100,100,0,100);
        tmpTree->Draw("sCMSNS2LC2.geoposX:g1xcl.geoposX >>h11a","trackx@.GetEntries()==1 && tracky@.GetEntries()==1 && trackx.q>0 && tracky.q>0","colz"); ////X
        ///use a TProfile to convert the 2-d to 1-d problem
        TProfile *prof3 = h11a->ProfileX();
        prof3->Fit("pol1","","",0,100);
        
        canvas_prof->cd(6);
        TH2F *h12a = new TH2F("h12a","X correlation sCMSNS2LC3vsg1",100,0,100,100,0,100);
        tmpTree->Draw("sCMSNS2LC3.geoposX:g1xcl.geoposX >>h12a","trackx@.GetEntries()==1 && tracky@.GetEntries()==1 && trackx.q>0 && tracky.q>0","colz"); ////X
        ///use a TProfile to convert the 2-d to 1-d problem
        TProfile *prof4 = h12a->ProfileX();
        prof4->Fit("pol1","","",0,100);

        
        canvas_prof->SaveAs(Form("GE11_Correlations_Run%d.pdf",name));
        canvas_prof->Clear();
        
        delete gDirectory->FindObject("h10");
        delete gDirectory->FindObject("h11");
        delete gDirectory->FindObject("h12");
	delete gDirectory->FindObject("h10a");
        delete gDirectory->FindObject("h11a");
        delete gDirectory->FindObject("h12a");

        
    
        
        
        canvas_prof->Divide(3,1);
        
        canvas_prof->cd(1);
        TH1F *h4a = new TH1F("h4a","X Offset sCMSNS2LC1 wrt g1",20,-25,15);
        tmpTree->Draw("sCMSNS2LC1.geoposX-g1xcl.geoposX>>h4a","trackx@.GetEntries()==1 && tracky@.GetEntries()==1 && trackx.q>0 && tracky.q>0","colz"); ////X
        h4a->Fit("gaus");
        gaus->SetLineColor(2);
        
        canvas_prof->cd(2);
        TH1F *h5a = new TH1F("h5a","X Offset sCMSNS2LC2 wrt g1",20,-25,15);
        tmpTree->Draw("sCMSNS2LC2.geoposX-g1xcl.geoposX>>h5a","trackx@.GetEntries()==1 && tracky@.GetEntries()==1 && trackx.q>0 && tracky.q>0","colz"); ////X
        h5a->Fit("gaus");
        gaus->SetLineColor(2);
        
        canvas_prof->cd(3);
        TH1F *h6a = new TH1F("h6a","X Offset sCMSNS2LC3 wrt g1",20,-25,15);
        tmpTree->Draw("sCMSNS2LC3.geoposX-g1xcl.geoposX>>h6a","trackx@.GetEntries()==1 && tracky@.GetEntries()==1 && trackx.q>0 && tracky.q>0","colz"); ////X
        h6a->Fit("gaus");
        gaus->SetLineColor(2);
        
        
        canvas_prof->SaveAs(Form("Offset_GE11_wrt_Tracker1_Run%d.pdf",name));
        canvas_prof->Clear();
        
        delete gDirectory->FindObject("h4a");
        delete gDirectory->FindObject("h5a");
        delete gDirectory->FindObject("h6a");
	}
	}
