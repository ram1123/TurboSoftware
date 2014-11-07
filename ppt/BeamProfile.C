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
	
	canvas_prof->SaveAs(Form("profile_plots_for_Trackers_%d_Rot.pdf",name));
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

	canvas_prof->SaveAs(Form("Tracker_Hit_position_%d_Rot.pdf",name));
	canvas_prof->Clear();

	delete gDirectory->FindObject("g1x");
	delete gDirectory->FindObject("g1y");
	delete gDirectory->FindObject("g2x");
	delete gDirectory->FindObject("g2y");
	delete gDirectory->FindObject("g3x");
	delete gDirectory->FindObject("g3y");

	canvas_prof->Divide(2,2);

	canvas_prof->cd(1);
	TH1F *LC1 = new TH1F("LC1","Hit Position on GE11_1 (y)", 10, 0,100);
	tmpTree->Draw("sCMSNS2LC1.geoposY");
	LC1->GetXaxis()->SetTitle("Y position in mm");
	LC1->GetYaxis()->SetTitle("Number of Hits");

	canvas_prof->cd(2);
	TH1F *LC2 = new TH1F("LC2","Hit Position on GE11_2 (y)", 10, 0,100);
	tmpTree->Draw("sCMSNS2LC2.geoposY");
	LC2->GetXaxis()->SetTitle("Y position in mm");
	LC2->GetYaxis()->SetTitle("Number of Hits");

	canvas_prof->cd(3);
	TH1F *LC3 = new TH1F("LC3","Hit Position on GE11_3 (y)", 10, 0,100);
	tmpTree->Draw("sCMSNS2LC3.geoposY");
	LC3->GetXaxis()->SetTitle("Y position in mm");
	LC3->GetYaxis()->SetTitle("Number of Hits");

	canvas_prof->SaveAs(Form("GEM_Hit_position_%d_Rot.pdf",name));
	canvas_prof->Clear();

	delete gDirectory->FindObject("LC1");
	delete gDirectory->FindObject("LC2");
	delete gDirectory->FindObject("LC3");
        
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		CORRELATION PLOTS
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
const Int_t nbranch = 12;
char *bnames[nbranch]={	"g1xcl.geoposX:g1xcl.geoposX",	"g1xcl.geoposX:g2xcl.geoposX",	"g1xcl.geoposX:g3xcl.geoposX",
			"g1ycl.geoposY:g1ycl.geoposY",	"g1ycl.geoposY:g2ycl.geoposY",	"g1ycl.geoposY:g3ycl.geoposY",
			"g1ycl.geoposY:sCMSNS2LC1.geoposY",	"g1ycl.geoposY:sCMSNS2LC2.geoposY",
			"g1xcl.geoposX:sCMSNS2LC1.geoposY",	"g1xcl.geoposX:sCMSNS2LC2.geoposY",
			"g1ycl.geoposY:sCMSNS2LC3.geoposY",	"g1xcl.geoposX:sCMSNS2LC3.geoposY"};

char *fnames[nbranch] = {"g1x_geoposX_vs_g1x_geoposX",	"g1x_geoposX_vs_g2x_geoposX",	"g1x_geoposX_vs_g3x_geoposX",
			"g1y_geoposY_vs_g1y_geoposY",	"g1y_geoposY_vs_g2y_geoposY",	"g1y_geoposY_vs_g3y_geoposY",
			"g1y_geoposY_vs_sCMSLC1_geoposY",	"g1y_geoposY_vs_sCMSLC2_geoposY",
			"g1x_geoposX_vs_sCMSLC1_geoposY",	"g1x_geoposX_vs_sCMSLC2_geoposY",
			"g1y_geoposY_vs_sCMSLC3_geoposY",	"g1x_geoposX_vs_sCMSLC3_geoposY"};
const Float_t range[4*nbranch] ={0,100,0,100,		-10,110,-10,110,		-10,110,-10,110,
				0,100,0,100,		-10,110,-10,110,		-10,110,-10,110,
				-10,110,-10,110,		-10,110,-10,110,
				-10,110,-10,110,		-10,110,-10,110,
				-10,110,-10,110,		-10,110,-10,110};

TH2F * hist[nbranch];
TProfile * hprofile[nbranch];
TCanvas *Canvas[nbranch];
TF1 *function[nbranch];

Char_t message[80];
vector<int> vecm,vecn; 
Double_t fit_Low, fit_High;
Int_t k=0;

ofstream o_file;
o_file.open("fit_detail.txt");

o_file<<"NAME_OF_PROFILE_PLOT\t\t\tChi-sqr/NDF\tINTERCEPT(P0)\tINTERCEPT_ERROR\t\tSLOPE(P1)\tSLOPE_ERROR"<<endl;
for(Int_t i=0;i<nbranch;i++){
	k=i*4;
	Canvas[i] = new TCanvas(Form("Canvas%d",i));
	Canvas[i]->Divide(2,1);
	Canvas[i]->cd(1);

	hist[i] = new TH2F("H_"+TString(fnames[i]),TString(bnames[i]),100,range[k],range[k+1],100,range[k+2],range[k+3]);
	tmpTree->Draw(TString(bnames[i])+">>H_"+TString(fnames[i]),"trackx@.GetEntries()==1 && tracky@.GetEntries()==1 && trackx.q>0 && tracky.q>0","colz");

	hprofile[i] = new TProfile("P_"+TString(fnames[i]),TString(bnames[i]),100,range[k],range[k+1],range[k+2],range[k+3]);
	tmpTree->Draw(TString(bnames[i])+">>P_"+TString(fnames[i]),"trackx@.GetEntries()==1 && tracky@.GetEntries()==1 && trackx.q>0 && tracky.q>0");

	for (int m=0; m<100; m++)
	for (int n=0; n<100; n++)
	{
		if (hist[i]->GetBinContent(m,n)>0) 
		{
			vecm.push_back(m); vecn.push_back(n);
		}
	}	
	fit_Low = hist[i]->GetXaxis()->GetBinCenter(vecm.front()-1);
	fit_High = hist[i]->GetXaxis()->GetBinCenter(vecm.back()+1);
	vecn.clear();	vecm.clear();		// clear the vector

	hprofile[i]->GetXaxis()->SetRangeUser(fit_Low,fit_High);
//	hprofile[i]->SetMinimum(fit_Low);
	hprofile[i]->SetStats(0);
	hist[i]->SetStats(0);
	hist[i]->Draw();

	Canvas[i]->cd(2);
	hprofile[i]->Draw();


	function[i] = new TF1("f1","[0]+([1]*x)",fit_Low,fit_High);
	//if (i==8) function[i] = new TF1("f1","expo",fit_Low,fit_High);

	function[i]->SetParameters(1,1);

	hprofile[i]->Fit("f1");
	hprofile[i]->Draw();

	TLegend *legend2 = new TLegend (0.3,0.9,.7,0.7,"Linear Fit");
	TF1 *fun=hprofile[i]->GetFunction("f1");
	cout<<"##############################################################"<<endl;
	cout<<"chi-sqr = "<<fun->GetChisquare()<<endl;
	cout<<"NDF = "<<fun->GetNDF()<<endl;
	o_file<<TString(fnames[i])<<"\t\t"<<setprecision(3)<<fixed<<fun->GetChisquare()/fun->GetNDF()<<"\t\t"<<fun->GetParameter(0)<<"\t\t"<<fun->GetParError(0)<<"\t\t\t"<<fun->GetParameter(1)<<"\t\t"<<fun->GetParError(1)<<endl; 
	cout<<"##############################################################"<<endl;
	sprintf(message,"Total : #chi^{2}/NDF = %.2d",fun->GetChisquare()/fun->GetNDF());
	legend2->AddEntry(fun,message);
	sprintf(message,"p0 = %.3f #pm  %.3f",fun->GetParameter(0),fun->GetParError(0));
	legend2->AddEntry(fun,message);
	sprintf(message,"p1 = %.3f  #pm %.3f",fun->GetParameter(1),fun->GetParError(1));
	legend2->AddEntry(fun,message);
	legend2->Draw();




//	Canvas[i]->SaveAs("Correlation_"+TString(fnames[i])+".png");
//	Canvas[i]->SaveAs("Correlation_"+TString(fnames[i])+"_Rot.pdf");
	Canvas[i]->SaveAs(Form("Correlation_%s_Run%d_Rot.pdf",fnames[i],name));

}

//o_file.close();
	
	}
	}
