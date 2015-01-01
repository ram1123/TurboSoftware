/*
 * =====================================================================================
 *
 *       Filename:  BeamProfile.C
 *
 *    Description:  This macro creates plots for beamprofile, x & y offset, Hit plots 
 *    		    for tracker and gems, space resolution for gems, correlation plots
 *    		    for between all trackers and gems
 *
 *        Version:  1.0
 *        Created:  Tuesday 11 November 2014 08:13:29  CET
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ramkrishna Sharma (Ram), ramkrishna.sharma71@gmail.com
 *      Edited by:  Ankita Mehta
 *   Organization:  University Of Delhi, Delhi, India & CERN
 *
 * =====================================================================================
 */


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

        TGaxis::SetMaxDigits(3);

  const Int_t NRGBs = 5;
  const Int_t NCont = 255;
  Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
  Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
  Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
  Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
  TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
  gStyle->SetNumberContours(NCont);

	std::vector<TFile*> InputFiles;
	InputFiles.clear();
	
	InputFiles.push_back(TFile::Open(RootFile));

	const Int_t NumOfFiles = InputFiles.size();
	cout<<"Num of FIles = "<<NumOfFiles<<endl;

	for(unsigned int j = 0; j < InputFiles.size(); ++j ) {
	TTree * tmpTree = (TTree*)InputFiles.at(j)->Get("rd51tbgeo");
	tmpTree->AddFriend("trackertree",RecoFile);       

	TCanvas *canvas_prof = new TCanvas("canvas_prof","canvas_prof",1);
        gStyle->SetCanvasDefH(800);                                                                                                            
        gStyle->SetCanvasDefW(700);
	
	canvas_prof->Divide(2,2);
	canvas_prof->cd(1);

	ofstream o_file2,o_file3;//,o_file3;
  	//o_file1.open("hits_details.txt",std::fstream::in | std::fstream::out | std::fstream::app);
  	o_file2.open("offset_details.txt",std::fstream::in | std::fstream::out | std::fstream::app);
  	o_file3.open("beam_profile_details.txt",std::fstream::in | std::fstream::out | std::fstream::app);

	o_file2<<"RunNo\t\tg2x\t\tg3x\t\t\tg2y\t\t\tg3y\t\t\tLC1\t\tLC2\t\tLC3"<<endl;
	////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//		BEAM PROFILE PLOTS
	////////////////////////////////////////////////////////////////////////////////////////////////////

        cmsprem = new TLatex(0,101,"CMS Preliminary");
        cmsprem->SetTextSize(0.04);
	
	canvas_prof_1->SetLogz();
	TH2F *hg1BeamProfile = new TH2F("hg1BeamProfile","Beam profile on Tracker 1", 10,0.,100.,10,0.,100.);
	//hg1BeamProfile->SetStats(0);
	hg1BeamProfile->GetZaxis()->SetRangeUser(0,450);
	tmpTree->Draw("g1ycl.geoposY:g1xcl.geoposX>>hg1BeamProfile","g1ycl@.GetEntries()==1 && g1xcl@.GetEntries()==1 && trackx.q>0 && tracky.q>0","colz");
	hg1BeamProfile->GetXaxis()->SetTitle("x position in mm");
	hg1BeamProfile->GetYaxis()->SetTitle("y position in mm");
        cmsprem->Draw();   


   // Highlight the maximum
   Int_t bin = hg1BeamProfile->GetMaximumBin();
   
   Int_t binx, biny, binz;
   hg1BeamProfile->GetBinXYZ(bin, binx, biny, binz);

                                                                                                                                               
   Double_t x1 = hg1BeamProfile->GetXaxis()->GetBinLowEdge(binx);
   Double_t x2 = hg1BeamProfile->GetXaxis()->GetBinUpEdge(binx);
   Double_t y1 = hg1BeamProfile->GetYaxis()->GetBinLowEdge(biny);
   Double_t y2 = hg1BeamProfile->GetYaxis()->GetBinUpEdge(biny);

   cout<<"x1 = "<<x1<<"\ty1 = "<<y1<<"\tx2 = "<<x2<<"\ty2 = "<<y2<<endl;
   TBox b(x1, y1, x2, y2);
   b.SetFillStyle(0);
   b.SetLineWidth(2);
   b.SetLineColor(kBlue);
   b.Draw();


	canvas_prof->cd(2);
	canvas_prof_2->SetLogz();
	TH2F *hg2BeamProfile = new TH2F("hg2BeamProfile","Beam profile on Tracker 2", 10,0.,100.,10,0.,100.);
	tmpTree->Draw("g2ycl.geoposY:g2xcl.geoposX>>hg2BeamProfile","g2ycl@.GetEntries()==1 && g2xcl@.GetEntries()==1 && trackx.q>0 && tracky.q>0","colz");
	hg2BeamProfile->GetXaxis()->SetTitle("x position in mm");
	hg2BeamProfile->GetYaxis()->SetTitle("y position in mm");
	
       cmsprem->Draw();   

   // Highlight the maximum
   Int_t bin = hg1BeamProfile->GetMaximumBin();
   
   Int_t binx, biny, binz;
   hg1BeamProfile->GetBinXYZ(bin, binx, biny, binz);
  
   cout<<"max bin number in X is "<<binx<<endl;
   cout<<"max bin number in Y is "<<binx<<endl;
   cout<<"max bin number in Z is "<<binx<<endl;
                                                                                                                                              
   Double_t x1 = hg1BeamProfile->GetXaxis()->GetBinLowEdge(binx);
   Double_t x2 = hg1BeamProfile->GetXaxis()->GetBinUpEdge(binx);
   Double_t y1 = hg1BeamProfile->GetYaxis()->GetBinLowEdge(biny);
   Double_t y2 = hg1BeamProfile->GetYaxis()->GetBinUpEdge(biny);

   cout<<" chk this x1 = "<<x1<<"\ty1 = "<<y1<<"\tx2 = "<<x2<<"\ty2 = "<<y2<<endl;
   TBox e(x1, y1, x2, y2);
   e.SetFillStyle(0);
   e.SetLineWidth(2);
   e.SetLineColor(kBlue);
   e.Draw();
	
	

	canvas_prof->cd(3);
	canvas_prof_3->SetLogz();
	TH2F *hg3BeamProfile = new TH2F("hg3BeamProfile","Beam profile on Tracker 3", 10,0.,100.,10,0.,100.);
	tmpTree->Draw("g3ycl.geoposY:g3xcl.geoposX>>hg3BeamProfile","g3ycl@.GetEntries()==1 && g3xcl@.GetEntries()==1 && trackx.q>0 && tracky.q>0","colz");
	hg3BeamProfile->GetXaxis()->SetTitle("x position in mm");
	hg3BeamProfile->GetYaxis()->SetTitle("y position in mm");
        cmsprem->Draw();   

   // Highlight the maximum
   Int_t bin = hg1BeamProfile->GetMaximumBin();
   
   Int_t binx, biny, binz;
   hg1BeamProfile->GetBinXYZ(bin, binx, biny, binz);

                                                                                                                                               
   Double_t x1 = hg1BeamProfile->GetXaxis()->GetBinLowEdge(binx);
   Double_t x2 = hg1BeamProfile->GetXaxis()->GetBinUpEdge(binx);
   Double_t y1 = hg1BeamProfile->GetYaxis()->GetBinLowEdge(biny);
   Double_t y2 = hg1BeamProfile->GetYaxis()->GetBinUpEdge(biny);

   cout<<"x1 = "<<x1<<"\ty1 = "<<y1<<"\tx2 = "<<x2<<"\ty2 = "<<y2<<endl;
   TBox c(x1, y1, x2, y2);
   c.SetFillStyle(0);
   c.SetLineWidth(2);
   c.SetLineColor(kBlue);
   c.Draw();

o_file3<<name<<"\t\t"<<hg1BeamProfile->GetXaxis()->GetBinCenter(binx)<<"\t\t"<<hg1BeamProfile->GetYaxis()->GetBinCenter(biny)<<endl;


	canvas_prof->SaveAs(Form("profile_plots_for_Trackers_Run%d.pdf",name));
	canvas_prof->Clear();

	delete gDirectory->FindObject("hg1BeamProfile");
	delete gDirectory->FindObject("hg2BeamProfile");
	delete gDirectory->FindObject("hg3BeamProfile");

	////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//		Hit Position  
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////
	canvas_prof->Divide(3,2);

	canvas_prof->cd(1);
	TH1F *g1x = new TH1F("g1x","Hit Position on tracker 1 (x)", 20, 0,100);
	tmpTree->Draw("g1xcl.geoposX>>g1x","trackx.q>0 && tracky.q>0");
	g1x->GetXaxis()->SetTitle("X position in mm");
	g1x->GetYaxis()->SetTitle("Number of Hits");

	canvas_prof->cd(2);
	TH1F *g2x = new TH1F("g2x","Hit Position on tracker 2 (x)", 20, 0,100);
	tmpTree->Draw("g2xcl.geoposX>>g2x","trackx.q>0 && tracky.q>0");
	g2x->GetXaxis()->SetTitle("X position in mm");
	g2x->GetYaxis()->SetTitle("Number of Hits");

	canvas_prof->cd(3);
	TH1F *g3x = new TH1F("g3x","Hit Position on tracker 3 (x)", 20, 0,100);
	tmpTree->Draw("g3xcl.geoposX>>g3x","trackx.q>0 && tracky.q>0");
	g3x->GetXaxis()->SetTitle("X position in mm");
	g3x->GetYaxis()->SetTitle("Number of Hits");

	canvas_prof->cd(4);
	TH1F *g1y = new TH1F("g1y","Hit Position on tracker 1 (y)", 20, 0,100);
	tmpTree->Draw("g1ycl.geoposY>>g1y","trackx.q>0 && tracky.q>0");
	g1y->GetXaxis()->SetTitle("Y position in mm");
	g1y->GetYaxis()->SetTitle("Number of Hits");

	canvas_prof->cd(5);
	TH1F *g2y = new TH1F("g2y","Hit Position on tracker 2 (y)", 20, 0,100);
	tmpTree->Draw("g2ycl.geoposY>>g2y","trackx.q>0 && tracky.q>0");
	g2y->GetXaxis()->SetTitle("Y position in mm");
	g2y->GetYaxis()->SetTitle("Number of Hits");

	canvas_prof->cd(6);
	TH1F *g3y = new TH1F("g3y","Hit Position on tracker 3 (x)", 20, 0,100);
	tmpTree->Draw("g3ycl.geoposY>>g3y","trackx.q>0 && tracky.q>0");
	g3y->GetXaxis()->SetTitle("Y position in mm");
	g3y->GetYaxis()->SetTitle("Number of Hits");

	canvas_prof->SaveAs(Form("Tracker_Hit_position_Run%d.pdf",name));
	canvas_prof->Clear();

	delete gDirectory->FindObject("g1x");
	delete gDirectory->FindObject("g1y");
	delete gDirectory->FindObject("g2x");
	delete gDirectory->FindObject("g2y");
	delete gDirectory->FindObject("g3x");
	delete gDirectory->FindObject("g3y");

	canvas_prof->Divide(2,2);

	canvas_prof->cd(1);
	TH1F *LC1 = new TH1F("LC1","Hit Position on GE11_1 (y)", 20, 0,100);
	tmpTree->Draw("sCMSNS2LC1.geoposY>>LC1","trackx.q>0 && tracky.q>0");
	LC1->GetXaxis()->SetTitle("Y position in mm");
	LC1->GetYaxis()->SetTitle("Number of Hits");

	canvas_prof->cd(2);
	TH1F *LC2 = new TH1F("LC2","Hit Position on GE11_2 (y)", 20, 0,100);
	tmpTree->Draw("sCMSNS2LC2.geoposY>>LC2","trackx.q>0 && tracky.q>0");
	LC2->GetXaxis()->SetTitle("Y position in mm");
	LC2->GetYaxis()->SetTitle("Number of Hits");

	canvas_prof->cd(3);
	TH1F *LC3 = new TH1F("LC3","Hit Position on GE11_3 (y)", 20, 0,100);
	tmpTree->Draw("sCMSNS2LC3.geoposY>>LC3","trackx.q>0 && tracky.q>0");
	LC3->GetXaxis()->SetTitle("Y position in mm");
	LC3->GetYaxis()->SetTitle("Number of Hits");

	canvas_prof->SaveAs(Form("GEM_Hit_position_Run%d.pdf",name));
	canvas_prof->Clear();

	delete gDirectory->FindObject("LC1");
	delete gDirectory->FindObject("LC2");
	delete gDirectory->FindObject("LC3");
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		Residual / Space Resolution Plots
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

	canvas_prof->Divide(2,2);

	canvas_prof->cd(1);
	TH1F *res1 = new TH1F("res1","Space Resolution for GE11_1",20,-30,40);
	tmpTree->Draw("tracky.m*1400.0+tracky.q-sCMSNS2LC1.geoposY>>res1","trackx.q>0 && tracky.q>0");
	res1->GetXaxis()->SetTitle("Space Resolution in mm");
	res1->GetYaxis()->SetTitle("Number of events");
	canvas_prof->cd(2);
	TH1F *res2 = new TH1F("res2","Space Resolution for GE11_2",20,-30,40);
	tmpTree->Draw("tracky.m*1580.0+tracky.q-sCMSNS2LC2.geoposY>>res2","trackx.q>0 && tracky.q>0");
	res2->GetXaxis()->SetTitle("Space Resolution in mm");
	res2->GetYaxis()->SetTitle("Number of events");
	canvas_prof->cd(3);
	TH1F *res3 = new TH1F("res3","Space Resolution for GE11_1",20,-30,40);
	tmpTree->Draw("tracky.m*1780.0+tracky.q-sCMSNS2LC3.geoposY>>res3","trackx.q>0 && tracky.q>0");
	res3->GetXaxis()->SetTitle("Space Resolution in mm");
	res3->GetYaxis()->SetTitle("Number of events");

	canvas_prof->SaveAs(Form("Space_Resolution_For_Run%d.pdf",name));
	canvas_prof->Clear();
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		Offset Plots
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	canvas_prof->Divide(2,1);

	canvas_prof->cd(1);
	TH1F *res4 = new TH1F("res4","Offset between g1x and g2x",20,-4,4);
	tmpTree->Draw("g1xcl.geoposX-g2xcl.geoposX>>res4","trackx.q>0 && tracky.q>0");
	res4->GetXaxis()->SetTitle("#Delta x in mm");
	res4->GetYaxis()->SetTitle("Number of entries");

	canvas_prof->cd(2);
	TH1F *res5 = new TH1F("res5","Offset between g1x and g3x",20,-4,4);
	tmpTree->Draw("g1xcl.geoposX-g3xcl.geoposX>>res5","trackx.q>0 && tracky.q>0");
	res5->GetXaxis()->SetTitle("#Delta x in mm");
	res5->GetYaxis()->SetTitle("Number of entries");

	o_file2<<name<<"\t\t"<<res4->GetMean()<<"\t\t"<<res5->GetMean();  
	canvas_prof->SaveAs(Form("X_Offset_For_Run%d.pdf",name));
	canvas_prof->Clear();

	canvas_prof->Divide(3,2);

	canvas_prof->cd(1);
	TH1F *res6 = new TH1F("res6","Offset between g1y and g1y",20,-4,4);
	tmpTree->Draw("g1ycl.geoposY-g1ycl.geoposY>>res6","trackx.q>0 && tracky.q>0");
	res6->GetXaxis()->SetTitle("#Delta y in mm");
	res6->GetYaxis()->SetTitle("Number of entries");

	canvas_prof->cd(2);
	TH1F *res7 = new TH1F("res7","Offset between g1y and g2y",20,-4,4);
	tmpTree->Draw("g1ycl.geoposY-g2ycl.geoposY>>res7","trackx.q>0 && tracky.q>0");
	res7->GetXaxis()->SetTitle("#Delta y in mm");
	res7->GetYaxis()->SetTitle("Number of entries");

	canvas_prof->cd(3);
	TH1F *res8 = new TH1F("res8","Offset between g1y and g3y",20,-4,4);
	tmpTree->Draw("g1ycl.geoposY-g3ycl.geoposY>>res8","trackx.q>0 && tracky.q>0");
	res8->GetXaxis()->SetTitle("#Delta y in mm");
	res8->GetYaxis()->SetTitle("Number of entries");

	canvas_prof->cd(4);
	TH1F *res9 = new TH1F("res9","Offset between g1y and LC1",20,-40,40);
	tmpTree->Draw("g1ycl.geoposY-sCMSNS2LC1.geoposY>>res9","trackx.q>0 && tracky.q>0");
	res9->GetXaxis()->SetTitle("#Delta y in mm");
	res9->GetYaxis()->SetTitle("Number of entries");

	canvas_prof->cd(5);
	TH1F *res19 = new TH1F("res19","Offset between g1y and LC2",20,-40,40);
	tmpTree->Draw("g1ycl.geoposY-sCMSNS2LC2.geoposY>>res19","trackx.q>0 && tracky.q>0");
	res19->GetXaxis()->SetTitle("#Delta y in mm");
	res19->GetYaxis()->SetTitle("Number of entries");

	canvas_prof->cd(6);
	TH1F *res10 = new TH1F("res10","Offset between g1y and LC3",20,-40,40);
	tmpTree->Draw("g1ycl.geoposY-sCMSNS2LC3.geoposY>>res10","trackx.q>0 && tracky.q>0");
	res10->GetXaxis()->SetTitle("#Delta y in mm");
	res10->GetYaxis()->SetTitle("Number of entries");

	o_file2<<name<<"\t\t"<<res7->GetMean()<<"\t\t"<<res8->GetMean()<<"\t\t"<<res9->GetMean()<<"\t\t"<<res19->GetMean()<<"\t\t"<<res10->GetMean()<<endl;
	
	canvas_prof->SaveAs(Form("Y_Offset_For_Run%d.pdf",name));
	canvas_prof->Clear();
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

gStyle->SetOptStat("ne");

o_file<<"NAME_OF_PROFILE_PLOT\t\t\tChi-sqr/NDF\tINTERCEPT(P0)\tINTERCEPT_ERROR\t\tSLOPE(P1)\tSLOPE_ERROR"<<endl;
for(Int_t i=0;i<nbranch;i++){
	k=i*4;
	Canvas[i] = new TCanvas(Form("Canvas%d",i));
	Canvas[i]->Divide(2,1);
	Canvas[i]->cd(1);

	hist[i] = new TH2F(TString("H_")+TString(fnames[i]),TString(bnames[i]),100,range[k],range[k+1],100,range[k+2],range[k+3]);
	tmpTree->Draw(TString(bnames[i])+TString(">>H_")+TString(fnames[i]),"trackx@.GetEntries()==1 && tracky@.GetEntries()==1 && trackx.q>0 && tracky.q>0 ","colz");

	hprofile[i] = new TProfile(TString("P_")+TString(fnames[i]),TString(bnames[i]),100,range[k],range[k+1],range[k+2],range[k+3]);
	tmpTree->Draw(TString(bnames[i])+TString(">>P_")+TString(fnames[i]),"trackx@.GetEntries()==1 && tracky@.GetEntries()==1 && trackx.q>0 && tracky.q>0 ");

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
	hist[i]->SetStats(1);
	hist[i]->Draw("colz");

	Canvas[i]->cd(2);
	hprofile[i]->Draw();


	function[i] = new TF1("f1","[0]+([1]*x)",fit_Low,fit_High);
	//if (i==8) function[i] = new TF1("f1","expo",fit_Low,fit_High);

	function[i]->SetParameters(1,1);

	hprofile[i]->Fit("f1");
	hprofile[i]->Draw();

	TLegend *legend2 = new TLegend (0.1,0.9,.6,0.8,"Linear Fit");
	legend2->SetTextSize(0.04);
	TF1 *fun=hprofile[i]->GetFunction("f1");
	cout<<"##############################################################"<<endl;
	cout<<"chi-sqr = "<<fun->GetChisquare()<<endl;
	cout<<"NDF = "<<fun->GetNDF()<<endl;
	o_file<<TString(fnames[i])<<"\t\t"<<setprecision(3)<<fixed<<fun->GetChisquare()/fun->GetNDF()<<"\t\t"<<fun->GetParameter(0)<<"\t\t"<<fun->GetParError(0)<<"\t\t\t"<<fun->GetParameter(1)<<"\t\t"<<fun->GetParError(1)<<endl; 
	cout<<"##############################################################"<<endl;
	sprintf(message,"#chi^{2}/NDF = %.3f",fun->GetChisquare()/fun->GetNDF());
	legend2->AddEntry(fun,message);
	sprintf(message,"p0 = %.3f #pm  %.3f",fun->GetParameter(0),fun->GetParError(0));
	legend2->AddEntry(fun,message);
	sprintf(message,"p1 = %.3f  #pm %.3f",fun->GetParameter(1),fun->GetParError(1));
	legend2->AddEntry(fun,message);
	legend2->Draw();




//	Canvas[i]->SaveAs("Correlation_"+TString(fnames[i])+".png");
//	Canvas[i]->SaveAs("Correlation_"+TString(fnames[i])+".pdf");
	Canvas[i]->SaveAs(Form("Correlation_%s_Run%d.pdf",fnames[i],name));

}

o_file.close();
o_file3.close();
o_file2.close();
	
	}
	}
