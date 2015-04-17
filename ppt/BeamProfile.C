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

int BeamProfile(TString RootFile,TString RecoFile, Int_t name, Int_t Plot)
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
	//cout<<"Num of FIles = "<<NumOfFiles<<endl;

	for(unsigned int j = 0; j < InputFiles.size(); ++j ) {
	TTree * tmpTree = (TTree*)InputFiles.at(j)->Get("rd51tbgeo");
	tmpTree->AddFriend("trackertree",RecoFile);       

	TCanvas *canvas_prof = new TCanvas("canvas_prof","canvas_prof",1);
        gStyle->SetCanvasDefH(800);                                                                                                            
        gStyle->SetCanvasDefW(700);
//	gStyle->SetTitleAlign(33);
	

	ofstream o_file2,o_file3;//,o_file3;
  	//o_file1.open("hits_details.txt",std::fstream::in | std::fstream::out | std::fstream::app);
  	//o_file2.open("offset_details.txt",std::fstream::in | std::fstream::out | std::fstream::app);
  	//o_file3.open("beam_profile_details.txt",std::fstream::in | std::fstream::out | std::fstream::app);
  	o_file2.open(Form("offset_details_%d.txt",name));
  	o_file3.open(Form("beam_profile_details_%d.txt",name));

	o_file2<<"RunNo\tg2x\tg3x\tg23x\tg2y\tg3y\tg23y\tLC1\tLC2\tLC3"<<endl;

	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//		BEAM PROFILE PLOTS
	////////////////////////////////////////////////////////////////////////////////////////////////////

        cmsprem = new TLatex(0,101,"CMS Preliminary");
        cmsprem->SetTextSize(0.04);
	
	//gStyle->SetOptStat("ne");
	gStyle->SetOptStat(1111);

	//int Plot = 0;
	if (Plot){
	canvas_prof->Divide(2,2);
	canvas_prof->cd(1);
	}
	else
	{
	canvas_prof->Divide(1,1);
	canvas_prof->cd(1);
	}
	canvas_prof_1->SetLogz();
	TH2F *BeamProfile_Tracker_1 = new TH2F("BeamProfile_Tracker_1","", 32,0.,100.,32,0.,100.);
	//Profile_Tracker_1->SetStats(0);
	BeamProfile_Tracker_1->GetZaxis()->SetRangeUser(0,450);
	tmpTree->Draw("g1ycl.geoposY:g1xcl.geoposX>>BeamProfile_Tracker_1","g1ycl@.GetEntries()==1 && g1xcl@.GetEntries()==1 && trackx.q>0 && tracky.q>0","colz");
	BeamProfile_Tracker_1->GetXaxis()->SetTitle("x position in mm");
	BeamProfile_Tracker_1->GetYaxis()->SetTitle("y position in mm");
	canvas_prof_1->Modified(); canvas_prof_1->Update();
	TPaveStats *stats =(TPaveStats*)canvas_prof_1->GetPrimitive("stats");
	stats->SetName("BeamBeamProfile_Tracker_1");
	stats->SetX1NDC(.6);//0.7
	stats->SetX2NDC(0.9);//0.9
	stats->SetY1NDC(.95);
	stats->SetY2NDC(.85);
	stats->SetTextColor(1);
        cmsprem->Draw();   
	

   // Highlight the maximum
   Int_t bin = BeamProfile_Tracker_1->GetMaximumBin();
   
   Int_t binx, biny, binz;
   BeamProfile_Tracker_1->GetBinXYZ(bin, binx, biny, binz);

                                                                                                                                               
   Double_t x1 = BeamProfile_Tracker_1->GetXaxis()->GetBinLowEdge(binx);
   Double_t x2 = BeamProfile_Tracker_1->GetXaxis()->GetBinUpEdge(binx);
   Double_t y1 = BeamProfile_Tracker_1->GetYaxis()->GetBinLowEdge(biny);
   Double_t y2 = BeamProfile_Tracker_1->GetYaxis()->GetBinUpEdge(biny);

   //cout<<"x1 = "<<x1<<"\ty1 = "<<y1<<"\tx2 = "<<x2<<"\ty2 = "<<y2<<endl;
   TBox b(x1, y1, x2, y2);
   b.SetFillStyle(0);
   b.SetLineWidth(2);
   b.SetLineColor(kBlue);
   b.Draw();

	if (!Plot){
	canvas_prof->SaveAs(Form("Plots/pdf/%d/profile_plots_for_First_Tracker_Run%d.pdf",name,name));
	canvas_prof->SaveAs(Form("Plots/gif/%d/profile_plots_for_First_Tracker_Run%d.gif",name,name));
	canvas_prof->SaveAs(Form("Plots/C/%d/profile_plots_for_First_Tracker_Run%d.C",name,name));
	canvas_prof->Clear();
	}

	if (Plot){
	canvas_prof->cd(2);
	canvas_prof_2->SetLogz();
	}
	else
	{
	canvas_prof->Divide(1,1);
	canvas_prof->cd(1);
	canvas_prof_1->SetLogz();
	}
	TH2F *BeamProfile_Tracker_2 = new TH2F("BeamProfile_Tracker_2","", 32,0.,100.,32,0.,100.);
	BeamProfile_Tracker_2->GetZaxis()->SetRangeUser(0,450);
	tmpTree->Draw("g2ycl.geoposY:g2xcl.geoposX>>BeamProfile_Tracker_2","g2ycl@.GetEntries()==1 && g2xcl@.GetEntries()==1 && trackx.q>0 && tracky.q>0","colz");
	BeamProfile_Tracker_2->GetXaxis()->SetTitle("x position in mm");
	BeamProfile_Tracker_2->GetYaxis()->SetTitle("y position in mm");
	if (Plot)
	{
	canvas_prof_2->Modified(); canvas_prof_2->Update();
	TPaveStats *stats =(TPaveStats*)canvas_prof_2->GetPrimitive("stats");
	}
	else
	{
	canvas_prof_1->Modified(); canvas_prof_1->Update();
	TPaveStats *stats =(TPaveStats*)canvas_prof_1->GetPrimitive("stats");
	}
	stats->SetName("BeamProfile_Tracker_2");
	stats->SetX1NDC(.6);
	stats->SetX2NDC(.9);
	stats->SetY1NDC(.95);
	stats->SetY2NDC(.85);
	stats->SetTextColor(1);
	
       cmsprem->Draw();   

   // Highlight the maximum
   Int_t bin = BeamProfile_Tracker_2->GetMaximumBin();
   
   Int_t binx, biny, binz;
   BeamProfile_Tracker_2->GetBinXYZ(bin, binx, biny, binz);
  
   //cout<<"max bin number in X is "<<binx<<endl;
   //cout<<"max bin number in Y is "<<binx<<endl;
   //cout<<"max bin number in Z is "<<binx<<endl;
                                                                                                                                              
   Double_t x1 = BeamProfile_Tracker_2->GetXaxis()->GetBinLowEdge(binx);
   Double_t x2 = BeamProfile_Tracker_2->GetXaxis()->GetBinUpEdge(binx);
   Double_t y1 = BeamProfile_Tracker_2->GetYaxis()->GetBinLowEdge(biny);
   Double_t y2 = BeamProfile_Tracker_2->GetYaxis()->GetBinUpEdge(biny);

   //cout<<" chk this x1 = "<<x1<<"\ty1 = "<<y1<<"\tx2 = "<<x2<<"\ty2 = "<<y2<<endl;
   TBox e(x1, y1, x2, y2);
   e.SetFillStyle(0);
   e.SetLineWidth(2);
   e.SetLineColor(kBlue);
   e.Draw();
	
	
	if (!Plot){
	canvas_prof->SaveAs(Form("Plots/pdf/%d/profile_plots_for_Second_Tracker_Run%d.pdf",name,name));
	canvas_prof->SaveAs(Form("Plots/gif/%d/profile_plots_for_Second_Tracker_Run%d.gif",name,name));
	canvas_prof->SaveAs(Form("Plots/C/%d/profile_plots_for_Second_Tracker_Run%d.C",name,name));
	canvas_prof->Clear();
	}

	if (Plot)
	{
	canvas_prof->cd(3);
	canvas_prof_3->SetLogz();
	}
	else
	{
	canvas_prof->Divide(1,1);
	canvas_prof->cd(1);
	canvas_prof_1->SetLogz();
	}
	TH2F *BeamProfile_Tracker_3 = new TH2F("BeamProfile_Tracker_3","", 32,0.,100.,32,0.,100.);
	BeamProfile_Tracker_3->GetZaxis()->SetRangeUser(0,450);
	tmpTree->Draw("g3ycl.geoposY:g3xcl.geoposX>>BeamProfile_Tracker_3","g3ycl@.GetEntries()==1 && g3xcl@.GetEntries()==1 && trackx.q>0 && tracky.q>0","colz");
	BeamProfile_Tracker_3->GetXaxis()->SetTitle("x position in mm");
	BeamProfile_Tracker_3->GetYaxis()->SetTitle("y position in mm");
	if (Plot)
	{
	canvas_prof_3->Modified(); canvas_prof_3->Update();
	TPaveStats *stats =(TPaveStats*)canvas_prof_3->GetPrimitive("stats");
	}
	else
	{
	canvas_prof_1->Modified(); canvas_prof_1->Update();
	TPaveStats *stats =(TPaveStats*)canvas_prof_1->GetPrimitive("stats");
	}
	stats->SetName("BeamProfile_Tracker_3");
	stats->SetX1NDC(.6);
	stats->SetX2NDC(.9);
	stats->SetY1NDC(.95);
	stats->SetY2NDC(.85);
	stats->SetTextColor(1);
        cmsprem->Draw();   

   // Highlight the maximum
   Int_t bin = BeamProfile_Tracker_3->GetMaximumBin();
   
   Int_t binx, biny, binz;
   BeamProfile_Tracker_3->GetBinXYZ(bin, binx, biny, binz);

                                                                                                                                               
   Double_t x1 = BeamProfile_Tracker_3->GetXaxis()->GetBinLowEdge(binx);
   Double_t x2 = BeamProfile_Tracker_3->GetXaxis()->GetBinUpEdge(binx);
   Double_t y1 = BeamProfile_Tracker_3->GetYaxis()->GetBinLowEdge(biny);
   Double_t y2 = BeamProfile_Tracker_3->GetYaxis()->GetBinUpEdge(biny);

   //cout<<"x1 = "<<x1<<"\ty1 = "<<y1<<"\tx2 = "<<x2<<"\ty2 = "<<y2<<endl;
   TBox c(x1, y1, x2, y2);
   c.SetFillStyle(0);
   c.SetLineWidth(2);
   c.SetLineColor(kBlue);
   c.Draw();
	if (!Plot){
	canvas_prof->SaveAs(Form("Plots/pdf/%d/profile_plots_for_Third_Tracker_Run%d.pdf",name,name));
	canvas_prof->SaveAs(Form("Plots/gif/%d/profile_plots_for_Third_Tracker_Run%d.gif",name,name));
	canvas_prof->SaveAs(Form("Plots/C/%d/profile_plots_for_Third_Tracker_Run%d.C",name,name));
	canvas_prof->Clear();
	}

o_file3<<name<<"\t("<<BeamProfile_Tracker_1->GetXaxis()->GetBinCenter(binx)<<","<<BeamProfile_Tracker_1->GetYaxis()->GetBinCenter(biny)<<")\t("<<BeamProfile_Tracker_2->GetXaxis()->GetBinCenter(binx)<<","<<BeamProfile_Tracker_2->GetYaxis()->GetBinCenter(biny)<<")\t("<<BeamProfile_Tracker_3->GetXaxis()->GetBinCenter(binx)<<","<<BeamProfile_Tracker_3->GetYaxis()->GetBinCenter(biny)<<")"<<endl;

	if (Plot){
	canvas_prof->SaveAs(Form("Plots/pdf/%d/profile_plots_for_Trackers_Run%d.pdf",name,name));
	canvas_prof->Clear();
	}
	delete gDirectory->FindObject("BeamProfile_Tracker_1");
	delete gDirectory->FindObject("BeamProfile_Tracker_2");
	delete gDirectory->FindObject("BeamProfile_Tracker_3");

	////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//		Hit Position  
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////
	canvas_prof->Divide(3,2);
        cmsprem = new TLatex(0,141,"CMS Preliminary");
        cmsprem->SetTextSize(0.04);

	canvas_prof->cd(1);
	TH1F *X_Hit_Trk_1 = new TH1F("X_Hit_Trk_1","", 128, 0,100);
	tmpTree->Draw("g1xcl.geoposX>>X_Hit_Trk_1","trackx@.GetEntries()==1 && tracky@.GetEntries()==1 && trackx.q>0 && tracky.q>0");
	X_Hit_Trk_1->GetXaxis()->SetTitle("X position in mm");
	X_Hit_Trk_1->GetYaxis()->SetTitle("Number of Hits");
	X_Hit_Trk_1->GetYaxis()->SetRangeUser(0,140);
//	X_Hit_Trk_1->GetXaxis()->SetTitleOffset(2.2);
	canvas_prof_1->Modified(); canvas_prof_1->Update();
	TPaveStats *stats =(TPaveStats*)canvas_prof_1->GetPrimitive("stats");
	stats->SetName("X_Hit_Trk_1");
	stats->SetX1NDC(.65);
	stats->SetX2NDC(.95); //0.9
	stats->SetY1NDC(.975);
	stats->SetY2NDC(.75);
	stats->SetTextColor(1);
	cmsprem->Draw();

	canvas_prof->cd(2);
	TH1F *X_Hit_Trk_2 = new TH1F("X_Hit_Trk_2","", 128, 0,100);
	tmpTree->Draw("g2xcl.geoposX>>X_Hit_Trk_2","trackx@.GetEntries()==1 && tracky@.GetEntries()==1 && trackx.q>0 && tracky.q>0");
	X_Hit_Trk_2->GetXaxis()->SetTitle("X position in mm");
	X_Hit_Trk_2->GetYaxis()->SetTitle("Number of Hits");
	X_Hit_Trk_2->GetYaxis()->SetRangeUser(0,140);
	canvas_prof_2->Modified(); canvas_prof_2->Update();
	TPaveStats *stats =(TPaveStats*)canvas_prof_2->GetPrimitive("stats");
	stats->SetName("X_Hit_Trk_2");
	stats->SetX1NDC(.65);
	stats->SetX2NDC(.95);
	stats->SetY1NDC(.975);
	stats->SetY2NDC(.75);
	stats->SetTextColor(1);
	cmsprem->Draw();

	canvas_prof->cd(3);
	TH1F *X_Hit_Trk_3 = new TH1F("X_Hit_Trk_3","", 128, 0,100);
	tmpTree->Draw("g3xcl.geoposX>>X_Hit_Trk_3","trackx@.GetEntries()==1 && tracky@.GetEntries()==1 && trackx.q>0 && tracky.q>0");
	X_Hit_Trk_3->GetXaxis()->SetTitle("X position in mm");
	X_Hit_Trk_3->GetYaxis()->SetTitle("Number of Hits");
	X_Hit_Trk_3->GetYaxis()->SetRangeUser(0,140);
	canvas_prof_3->Modified(); canvas_prof_3->Update();
	TPaveStats *stats =(TPaveStats*)canvas_prof_3->GetPrimitive("stats");
	stats->SetName("X_Hit_Trk_3");
	stats->SetX1NDC(.65);
	stats->SetX2NDC(.95);
	stats->SetY1NDC(.975);
	stats->SetY2NDC(.75);
	stats->SetTextColor(1);
	cmsprem->Draw();

        cmsprem = new TLatex(0,251,"CMS Preliminary");
        cmsprem->SetTextSize(0.04);

	canvas_prof->cd(4);
	TH1F *Y_Hit_Trk_1 = new TH1F("Y_Hit_Trk_1","", 128, 0,100);
	tmpTree->Draw("g1ycl.geoposY>>Y_Hit_Trk_1","trackx@.GetEntries()==1 && tracky@.GetEntries()==1 && trackx.q>0 && tracky.q>0");
	Y_Hit_Trk_1->GetXaxis()->SetTitle("Y position in mm");
	Y_Hit_Trk_1->GetYaxis()->SetTitle("Number of Hits");
	Y_Hit_Trk_1->GetYaxis()->SetRangeUser(0,250);
	canvas_prof_4->Modified(); canvas_prof_4->Update();
	TPaveStats *stats =(TPaveStats*)canvas_prof_4->GetPrimitive("stats");
	stats->SetName("Y_Hit_Trk_1");
	stats->SetX1NDC(.65);
	stats->SetX2NDC(.95);
	stats->SetY1NDC(.975);
	stats->SetY2NDC(.75);
	stats->SetTextColor(1);
	cmsprem->Draw();

	canvas_prof->cd(5);
	TH1F *Y_Hit_Trk_2 = new TH1F("Y_Hit_Trk_2","", 128, 0,100);
	tmpTree->Draw("g2ycl.geoposY>>Y_Hit_Trk_2","trackx@.GetEntries()==1 && tracky@.GetEntries()==1 && trackx.q>0 && tracky.q>0");
	Y_Hit_Trk_2->GetXaxis()->SetTitle("Y position in mm");
	Y_Hit_Trk_2->GetYaxis()->SetTitle("Number of Hits");
	Y_Hit_Trk_2->GetYaxis()->SetRangeUser(0,250);
	canvas_prof_5->Modified(); canvas_prof_5->Update();
	TPaveStats *stats =(TPaveStats*)canvas_prof_5->GetPrimitive("stats");
	stats->SetName("Y_Hit_Trk_2");
	stats->SetX1NDC(.65);
	stats->SetX2NDC(.95);
	stats->SetY1NDC(.975);
	stats->SetY2NDC(.75);
	stats->SetTextColor(1);
	cmsprem->Draw();

	canvas_prof->cd(6);
	TH1F *Y_Hit_Trk_3 = new TH1F("Y_Hit_Trk_3","", 128, 0,100);
	tmpTree->Draw("g3ycl.geoposY>>Y_Hit_Trk_3","trackx@.GetEntries()==1 && tracky@.GetEntries()==1 && trackx.q>0 && tracky.q>0");
	Y_Hit_Trk_3->GetXaxis()->SetTitle("Y position in mm");
	Y_Hit_Trk_3->GetYaxis()->SetTitle("Number of Hits");
	Y_Hit_Trk_3->GetYaxis()->SetRangeUser(0,250);
	canvas_prof_6->Modified(); canvas_prof_6->Update();
	TPaveStats *stats =(TPaveStats*)canvas_prof_6->GetPrimitive("stats");
	stats->SetName("Y_Hit_Trk_3");
	stats->SetX1NDC(.65);
	stats->SetX2NDC(.95);
	stats->SetY1NDC(.975);
	stats->SetY2NDC(.75);
	stats->SetTextColor(1);
	cmsprem->Draw();

	canvas_prof->SaveAs(Form("Plots/pdf/%d/Tracker_Hit_position_Run%d.pdf",name,name));
	canvas_prof->Clear();

	delete gDirectory->FindObject("X_Hit_Trk_1");
	delete gDirectory->FindObject("Y_Hit_Trk_1");
	delete gDirectory->FindObject("X_Hit_Trk_2");
	delete gDirectory->FindObject("Y_Hit_Trk_2");
	delete gDirectory->FindObject("X_Hit_Trk_3");
	delete gDirectory->FindObject("Y_Hit_Trk_3");

	canvas_prof->Divide(2,2);

        cmsprem = new TLatex(0,191,"CMS Preliminary");
        cmsprem->SetTextSize(0.04);


	canvas_prof->cd(1);
	TH1F *Y_Hit_GE11_IV_GIF = new TH1F("Y_Hit_GE11_IV_GIF","", 128, 0,100);
	tmpTree->Draw("sCMSNS2LC1.geoposY>>Y_Hit_GE11_IV_GIF","trackx@.GetEntries()==1 && tracky@.GetEntries()==1 && trackx.q>0 && tracky.q>0");
	Y_Hit_GE11_IV_GIF->GetXaxis()->SetTitle("Y position in mm");
	Y_Hit_GE11_IV_GIF->GetYaxis()->SetTitle("Number of Hits");
	Y_Hit_GE11_IV_GIF->GetYaxis()->SetRangeUser(0,190);
	canvas_prof_1->Modified(); canvas_prof_1->Update();
	TPaveStats *stats =(TPaveStats*)canvas_prof_1->GetPrimitive("stats");
	stats->SetName("Y_Hit_GE11_IV_GIF");
	stats->SetX1NDC(.65);
	stats->SetX2NDC(.9);
	stats->SetY1NDC(.975);
	stats->SetY2NDC(.75);
	stats->SetTextColor(1);
	cmsprem->Draw();

	canvas_prof->cd(2);
	TH1F *Y_Hit_GE11_IV = new TH1F("Y_Hit_GE11_IV","", 128, 0,100);
	tmpTree->Draw("sCMSNS2LC2.geoposY>>Y_Hit_GE11_IV","trackx@.GetEntries()==1 && tracky@.GetEntries()==1 && trackx.q>0 && tracky.q>0");
	Y_Hit_GE11_IV->GetXaxis()->SetTitle("Y position in mm");
	Y_Hit_GE11_IV->GetYaxis()->SetTitle("Number of Hits");
	Y_Hit_GE11_IV->GetYaxis()->SetRangeUser(0,190);
	canvas_prof_2->Modified(); canvas_prof_2->Update();
	TPaveStats *stats =(TPaveStats*)canvas_prof_2->GetPrimitive("stats");
	stats->SetName("Y_Hit_GE11_IV");
	stats->SetX1NDC(.65);
	stats->SetX2NDC(.9);
	stats->SetY1NDC(.975);
	stats->SetY2NDC(.75);
	stats->SetTextColor(1);
	cmsprem->Draw();

	canvas_prof->cd(3);
	TH1F *Y_Hit_GE11_V = new TH1F("Y_Hit_GE11_V","", 128, 0,100);
	tmpTree->Draw("sCMSNS2LC3.geoposY>>Y_Hit_GE11_V","trackx@.GetEntries()==1 && tracky@.GetEntries()==1 && trackx.q>0 && tracky.q>0");
	Y_Hit_GE11_V->GetXaxis()->SetTitle("Y position in mm");
	Y_Hit_GE11_V->GetYaxis()->SetTitle("Number of Hits");
	Y_Hit_GE11_V->GetYaxis()->SetRangeUser(0,190);
	canvas_prof_3->Modified(); canvas_prof_3->Update();
	TPaveStats *stats =(TPaveStats*)canvas_prof_3->GetPrimitive("stats");
	stats->SetName("Y_Hit_GE11_V");
	stats->SetX1NDC(.65);
	stats->SetX2NDC(.9);
	stats->SetY1NDC(.975);
	stats->SetY2NDC(.75);
	stats->SetTextColor(1);
	cmsprem->Draw();

	canvas_prof->SaveAs(Form("Plots/pdf/%d/GEM_Hit_position_Run%d.pdf",name,name));
	canvas_prof->Clear();

	delete gDirectory->FindObject("Y_Hit_GE11_IV_GIF");
	delete gDirectory->FindObject("Y_Hit_GE11_IV");
	delete gDirectory->FindObject("Y_Hit_GE11_V");
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		Residual / Space Resolution Plots
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

	canvas_prof->Divide(2,2);

	canvas_prof->cd(1);
	TH1F *GE11_IV_GIF = new TH1F("GE11_IV_GIF","Space Resolution",50,-30,40);
	tmpTree->Draw("tracky.m*1400.0+tracky.q-sCMSNS2LC1.geoposY>>GE11_IV_GIF","trackx@.GetEntries()==1 && tracky@.GetEntries()==1 && trackx.q>0 && tracky.q>0");
	GE11_IV_GIF->GetXaxis()->SetTitle("Space Resolution in mm");
	GE11_IV_GIF->GetYaxis()->SetTitle("Number of events");
	//GE11_IV_GIF->GetYaxis()->SetRangeUser(0,190);
//	GE11_IV_GIF->CenterTitle();
	canvas_prof_1->Modified(); canvas_prof_1->Update();
	TPaveStats *stats =(TPaveStats*)canvas_prof_1->GetPrimitive("stats");
	stats->SetName("GE11_IV_GIF");
	stats->SetX1NDC(.65);
	stats->SetX2NDC(.9);
	stats->SetY1NDC(.975);
	stats->SetY2NDC(.75);
	stats->SetTextColor(1);
	TPaveStats *title =(TPaveStats*)canvas_prof_1->GetPrimitive("title");
	title->SetX1NDC(.35);
	title->SetX2NDC(.65);
	title->SetY1NDC(.9);
	title->SetY2NDC(.975);
	title->SetTextColor(1);
//	cmsprem->Draw();

	canvas_prof->cd(2);
	TH1F *GE11_IV = new TH1F("GE11_IV","Space Resolution",50,-30,40);
	tmpTree->Draw("tracky.m*1580.0+tracky.q-sCMSNS2LC2.geoposY>>GE11_IV","trackx@.GetEntries()==1 && tracky@.GetEntries()==1 && trackx.q>0 && tracky.q>0");
	GE11_IV->GetXaxis()->SetTitle("Space Resolution in mm");
	GE11_IV->GetYaxis()->SetTitle("Number of events");
	canvas_prof_2->Modified(); canvas_prof_2->Update();
	TPaveStats *stats =(TPaveStats*)canvas_prof_2->GetPrimitive("stats");
	stats->SetName("GE11_IV");
	stats->SetX1NDC(.65);
	stats->SetX2NDC(.9);
	stats->SetY1NDC(.975);
	stats->SetY2NDC(.75);
	stats->SetTextColor(1);
	TPaveStats *title =(TPaveStats*)canvas_prof_2->GetPrimitive("title");
	title->SetX1NDC(.35);
	title->SetX2NDC(.65);
	title->SetY1NDC(.9);
	title->SetY2NDC(.975);
	title->SetTextColor(1);
//	cmsprem->Draw();

	canvas_prof->cd(3);
	TH1F *GE11_V = new TH1F("GE11_V","Space Resolution",50,-30,40);
	tmpTree->Draw("tracky.m*1780.0+tracky.q-sCMSNS2LC3.geoposY>>GE11_V","trackx@.GetEntries()==1 && tracky@.GetEntries()==1 && trackx.q>0 && tracky.q>0");
	GE11_V->GetXaxis()->SetTitle("Space Resolution in mm");
	GE11_V->GetYaxis()->SetTitle("Number of events");
	canvas_prof_3->Modified(); canvas_prof_3->Update();
	TPaveStats *stats =(TPaveStats*)canvas_prof_3->GetPrimitive("stats");
	stats->SetName("GE11_V");
	stats->SetX1NDC(.65);
	stats->SetX2NDC(.9);
	stats->SetY1NDC(.975);
	stats->SetY2NDC(.75);
	stats->SetTextColor(1);
	TPaveStats *title =(TPaveStats*)canvas_prof_3->GetPrimitive("title");
	title->SetX1NDC(.35);
	title->SetX2NDC(.65);
	title->SetY1NDC(.9);
	title->SetY2NDC(.975);
	title->SetTextColor(1);
	//cmsprem->Draw();

	canvas_prof->SaveAs(Form("Plots/pdf/%d/Space_Resolution_For_Run%d.pdf",name,name));
	canvas_prof->Clear();
	delete gDirectory->FindObject("GE11_IV_GIF");
	delete gDirectory->FindObject("GE11_IV");
	delete gDirectory->FindObject("GE11_V");
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		Offset Plots
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	canvas_prof->Divide(2,2);


	canvas_prof->cd(1);
	TH1F *Trk1_Trk2 = new TH1F("Trk1_Trk2","X - Offset",40,-4,4);
	tmpTree->Draw("g1xcl.geoposX-g2xcl.geoposX>>Trk1_Trk2","trackx@.GetEntries()==1 && tracky@.GetEntries()==1 && trackx.q>0 && tracky.q>0 && trackx.chi2<20 && tracky.chi2<20");
	Trk1_Trk2->GetXaxis()->SetTitle("#Delta x in mm");
	Trk1_Trk2->GetYaxis()->SetTitle("Number of entries");
	canvas_prof_1->Modified(); canvas_prof_1->Update();
	TPaveStats *stats =(TPaveStats*)canvas_prof_1->GetPrimitive("stats");
	stats->SetName("Trk1_Trk2");
	stats->SetX1NDC(.65);
	stats->SetX2NDC(.95);
	stats->SetY1NDC(.975);
	stats->SetY2NDC(.75);
	stats->SetTextColor(1);
	TPaveStats *title =(TPaveStats*)canvas_prof_1->GetPrimitive("title");
	title->SetX1NDC(.35);
	title->SetX2NDC(.65);
	title->SetY1NDC(.9);
	title->SetY2NDC(.975);
	title->SetTextColor(1);

	canvas_prof->cd(2);
	TH1F *Trk1_Trk3 = new TH1F("Trk1_Trk3","X - Offset",50,-4,4);
	tmpTree->Draw("g1xcl.geoposX-g3xcl.geoposX>>Trk1_Trk3","trackx@.GetEntries()==1 && tracky@.GetEntries()==1 && trackx.q>0 && tracky.q>0");
	Trk1_Trk3->GetXaxis()->SetTitle("#Delta x in mm");
	Trk1_Trk3->GetYaxis()->SetTitle("Number of entries");
	canvas_prof_2->Modified(); canvas_prof_2->Update();
	TPaveStats *stats =(TPaveStats*)canvas_prof_2->GetPrimitive("stats");
	stats->SetName("Trk1_Trk3");
	stats->SetX1NDC(.65);
	stats->SetX2NDC(.95);
	stats->SetY1NDC(.975);
	stats->SetY2NDC(.75);
	stats->SetTextColor(1);
	TPaveStats *title =(TPaveStats*)canvas_prof_2->GetPrimitive("title");
	title->SetX1NDC(.35);
	title->SetX2NDC(.65);
	title->SetY1NDC(.9);
	title->SetY2NDC(.975);
	title->SetTextColor(1);

	canvas_prof->cd(3);
	TH1F *Trk2_Trk3 = new TH1F("Trk2_Trk3","X - Offset",50,-4,4);
	tmpTree->Draw("g2xcl.geoposX-g3xcl.geoposX>>Trk2_Trk3","trackx@.GetEntries()==1 && tracky@.GetEntries()==1 && trackx.q>0 && tracky.q>0");
	Trk2_Trk3->GetXaxis()->SetTitle("#Delta x in mm");
	Trk2_Trk3->GetYaxis()->SetTitle("Number of entries");
	canvas_prof_3->Modified(); canvas_prof_3->Update();
	TPaveStats *stats =(TPaveStats*)canvas_prof_3->GetPrimitive("stats");
	stats->SetName("Trk2_Trk3");
	stats->SetX1NDC(.65);
	stats->SetX2NDC(.95);
	stats->SetY1NDC(.975);
	stats->SetY2NDC(.75);
	stats->SetTextColor(1);
	TPaveStats *title =(TPaveStats*)canvas_prof_3->GetPrimitive("title");
	title->SetX1NDC(.35);
	title->SetX2NDC(.65);
	title->SetY1NDC(.9);
	title->SetY2NDC(.975);
	title->SetTextColor(1);

	o_file2<<name<<"\t"<<Trk1_Trk2->GetMean()<<"\t"<<Trk1_Trk3->GetMean()<<"\t"<<Trk2_Trk3->GetMean();  
	canvas_prof->SaveAs(Form("Plots/pdf/%d/X_Offset_For_Run%d.pdf",name,name));
	canvas_prof->Clear();

	delete gDirectory->FindObject("Trk1_Trk2");
	delete gDirectory->FindObject("Trk1_Trk3");
	delete gDirectory->FindObject("Trk2_Trk3");

	canvas_prof->Divide(3,2);

	canvas_prof->cd(1);
	TH1F *Trk1_Trk2 = new TH1F("Trk1_Trk2","Y - Offset",50,-4,4);
	tmpTree->Draw("g1ycl.geoposY-g2ycl.geoposY>>Trk1_Trk2","trackx@.GetEntries()==1 && tracky@.GetEntries()==1 && trackx.q>0 && tracky.q>0");
	Trk1_Trk2->GetXaxis()->SetTitle("#Delta y in mm");
	Trk1_Trk2->GetYaxis()->SetTitle("Number of entries");
	canvas_prof_1->Modified(); canvas_prof_1->Update();
	TPaveStats *stats =(TPaveStats*)canvas_prof_1->GetPrimitive("stats");
	stats->SetName("Trk1_Trk2");
	stats->SetX1NDC(.65);
	stats->SetX2NDC(.95);
	stats->SetY1NDC(.975);
	stats->SetY2NDC(.75);
	stats->SetTextColor(1);
	TPaveStats *title =(TPaveStats*)canvas_prof_1->GetPrimitive("title");
	title->SetX1NDC(.35);
	title->SetX2NDC(.65);
	title->SetY1NDC(.9);
	title->SetY2NDC(.975);
	title->SetTextColor(1);

	canvas_prof->cd(2);
	TH1F *Trk1_Trk3 = new TH1F("Trk1_Trk3","Y - Offset",50,-4,4);
	tmpTree->Draw("g1ycl.geoposY-g3ycl.geoposY>>Trk1_Trk3","trackx@.GetEntries()==1 && tracky@.GetEntries()==1 && trackx.q>0 && tracky.q>0");
	Trk1_Trk3->GetXaxis()->SetTitle("#Delta y in mm");
	Trk1_Trk3->GetYaxis()->SetTitle("Number of entries");
	canvas_prof_2->Modified(); canvas_prof_2->Update();
	TPaveStats *stats =(TPaveStats*)canvas_prof_2->GetPrimitive("stats");
	stats->SetName("Trk1_Trk3");
	stats->SetX1NDC(.65);
	stats->SetX2NDC(.95);
	stats->SetY1NDC(.975);
	stats->SetY2NDC(.75);
	stats->SetTextColor(1);
	TPaveStats *title =(TPaveStats*)canvas_prof_2->GetPrimitive("title");
	title->SetX1NDC(.35);
	title->SetX2NDC(.65);
	title->SetY1NDC(.9);
	title->SetY2NDC(.975);
	title->SetTextColor(1);

	canvas_prof->cd(3);
	TH1F *Trk2_Trk3 = new TH1F("Trk2_Trk3","Y - Offset",50,-4,4);
	tmpTree->Draw("g2ycl.geoposY-g3ycl.geoposY>>Trk2_Trk3","trackx@.GetEntries()==1 && tracky@.GetEntries()==1 && trackx.q>0 && tracky.q>0");
	Trk2_Trk3->GetXaxis()->SetTitle("#Delta y in mm");
	Trk2_Trk3->GetYaxis()->SetTitle("Number of entries");
	canvas_prof_3->Modified(); canvas_prof_3->Update();
	TPaveStats *stats =(TPaveStats*)canvas_prof_3->GetPrimitive("stats");
	stats->SetName("Trk2_Trk3");
	stats->SetX1NDC(.65);
	stats->SetX2NDC(.95);
	stats->SetY1NDC(.975);
	stats->SetY2NDC(.75);
	stats->SetTextColor(1);
	TPaveStats *title =(TPaveStats*)canvas_prof_3->GetPrimitive("title");
	title->SetX1NDC(.35);
	title->SetX2NDC(.65);
	title->SetY1NDC(.9);
	title->SetY2NDC(.975);
	title->SetTextColor(1);


	canvas_prof->cd(4);
	TH1F *Trk1_GE11_IV_GIF = new TH1F("Trk1_GE11_IV_GIF","Y - Offset",50,-20,20);
	tmpTree->Draw("g1ycl.geoposY-sCMSNS2LC1.geoposY>>Trk1_GE11_IV_GIF","trackx@.GetEntries()==1 && tracky@.GetEntries()==1 && trackx.q>0 && tracky.q>0 && trackx.chi2<20 && tracky.chi2<20");
	Trk1_GE11_IV_GIF->GetXaxis()->SetTitle("#Delta y in mm");
	Trk1_GE11_IV_GIF->GetYaxis()->SetTitle("Number of entries");
	canvas_prof_4->Modified(); canvas_prof_4->Update();
	TPaveStats *stats =(TPaveStats*)canvas_prof_4->GetPrimitive("stats");
	stats->SetName("Trk1_GE11_IV_GIF");
	stats->SetX1NDC(.65);
	stats->SetX2NDC(.95);
	stats->SetY1NDC(.975);
	stats->SetY2NDC(.75);
	stats->SetTextColor(1);
	TPaveStats *title =(TPaveStats*)canvas_prof_4->GetPrimitive("title");
	title->SetX1NDC(.35);
	title->SetX2NDC(.65);
	title->SetY1NDC(.9);
	title->SetY2NDC(.975);
	title->SetTextColor(1);

	canvas_prof->cd(5);
	TH1F *Trk1_GE11_IV = new TH1F("Trk1_GE11_IV","Y - Offset",50,-20,20);
	tmpTree->Draw("g1ycl.geoposY-sCMSNS2LC2.geoposY>>Trk1_GE11_IV","trackx@.GetEntries()==1 && tracky@.GetEntries()==1 && trackx.q>0 && tracky.q>0");
	Trk1_GE11_IV->GetXaxis()->SetTitle("#Delta y in mm");
	Trk1_GE11_IV->GetYaxis()->SetTitle("Number of entries");
	canvas_prof_5->Modified(); canvas_prof_5->Update();
	TPaveStats *stats =(TPaveStats*)canvas_prof_5->GetPrimitive("stats");
	stats->SetName("Trk1_GE11_IV");
	stats->SetX1NDC(.65);
	stats->SetX2NDC(.95);
	stats->SetY1NDC(.975);
	stats->SetY2NDC(.75);
	stats->SetTextColor(1);
	TPaveStats *title =(TPaveStats*)canvas_prof_5->GetPrimitive("title");
	title->SetX1NDC(.35);
	title->SetX2NDC(.65);
	title->SetY1NDC(.9);
	title->SetY2NDC(.975);
	title->SetTextColor(1);

	canvas_prof->cd(6);
	TH1F *Trk1_GE11_V = new TH1F("Trk1_GE11_V","Y - Offset",50,-20,20);
	tmpTree->Draw("g1ycl.geoposY-sCMSNS2LC3.geoposY>>Trk1_GE11_V","trackx@.GetEntries()==1 && tracky@.GetEntries()==1 && trackx.q>0 && tracky.q>0");
	Trk1_GE11_V->GetXaxis()->SetTitle("#Delta y in mm");
	Trk1_GE11_V->GetYaxis()->SetTitle("Number of entries");
	canvas_prof_6->Modified(); canvas_prof_6->Update();
	TPaveStats *stats =(TPaveStats*)canvas_prof_6->GetPrimitive("stats");
	stats->SetName("Trk1_GE11_V");
	stats->SetX1NDC(.65);
	stats->SetX2NDC(.95);
	stats->SetY1NDC(.975);
	stats->SetY2NDC(.75);
	stats->SetTextColor(1);
	TPaveStats *title =(TPaveStats*)canvas_prof_3->GetPrimitive("title");
	title->SetX1NDC(.35);
	title->SetX2NDC(.65);
	title->SetY1NDC(.9);
	title->SetY2NDC(.975);
	title->SetTextColor(1);

	o_file2<<"\t"<<Trk2_Trk3->GetMean()<<"\t"<<Trk1_Trk2->GetMean()<<"\t"<<Trk1_Trk3->GetMean()<<"\t"<<Trk1_GE11_IV_GIF->GetMean()<<"\t"<<Trk1_GE11_IV->GetMean()<<"\t"<<Trk1_GE11_V->GetMean()<<endl;
	
	canvas_prof->SaveAs(Form("Plots/pdf/%d/Y_Offset_For_Run%d.pdf",name,name));
	canvas_prof->Clear();

	delete gDirectory->FindObject("Trk1_Trk2");
	delete gDirectory->FindObject("Trk1_Trk3");
	delete gDirectory->FindObject("Trk2_Trk3");
	delete gDirectory->FindObject("Trk1_GE11_IV_GIF");
	delete gDirectory->FindObject("Trk1_GE11_IV");
	delete gDirectory->FindObject("Trk1_GE11_V");


	canvas_prof->Divide(3,1);

	canvas_prof->cd(1);
	TH1F *Offset1 = new TH1F("Offset1","Offset between GE11_IV_GI and GE11_IV",50,-20,20);
	tmpTree->Draw("sCMSNS2LC1.geoposY-sCMSNS2LC2.geoposY>>Offset1","trackx@.GetEntries()==1 && tracky@.GetEntries()==1 && trackx.q>0 && tracky.q>0");
	Offset1->GetXaxis()->SetTitle("#Delta y in mm");
	Offset1->GetYaxis()->SetTitle("Number of entries");
        canvas_prof_1->Modified(); canvas_prof_1->Update();
	TPaveStats *stats =(TPaveStats*)canvas_prof_1->GetPrimitive("stats");
        stats->SetName("Offset1");
        stats->SetX1NDC(.70);
        stats->SetX2NDC(0.95);
        stats->SetY1NDC(.95);
        stats->SetY2NDC(.85);
        stats->SetTextColor(1);
	

	canvas_prof->cd(2);
	TH1F *Offset2 = new TH1F("Offset2","Offset between GE11_IV_GIF and GE11_V",50,-20,20);
	tmpTree->Draw("sCMSNS2LC1.geoposY-sCMSNS2LC3.geoposY>>Offset2","trackx@.GetEntries()==1 && tracky@.GetEntries()==1 && trackx.q>0 && tracky.q>0");
	Offset2->GetXaxis()->SetTitle("#Delta y in mm");
	Offset2->GetYaxis()->SetTitle("Number of entries");
        canvas_prof_2->Modified(); canvas_prof_2->Update();
	TPaveStats *stats =(TPaveStats*)canvas_prof_2->GetPrimitive("stats");
        stats->SetName("Offset2");
        stats->SetX1NDC(.70);
        stats->SetX2NDC(0.95);
        stats->SetY1NDC(.95);
        stats->SetY2NDC(.85);
	stats->SetTextColor(1);

	canvas_prof->cd(3);
	TH1F *Offset3 = new TH1F("Offset3","Offset between GE11_IV and GE11_V",50,-20,20);
	tmpTree->Draw("sCMSNS2LC2.geoposY-sCMSNS2LC3.geoposY>>Offset3","trackx@.GetEntries()==1 && tracky@.GetEntries()==1 && trackx.q>0 && tracky.q>0");
	Offset3->GetXaxis()->SetTitle("#Delta y in mm");
	Offset3->GetYaxis()->SetTitle("Number of entries");
	canvas_prof_3->Modified(); canvas_prof_3->Update();
        TPaveStats *stats =(TPaveStats*)canvas_prof_3->GetPrimitive("stats");
        stats->SetName("Offset2");
        stats->SetX1NDC(.70);
        stats->SetX2NDC(0.95);
        stats->SetY1NDC(.95);
        stats->SetY2NDC(.85);
        stats->SetTextColor(1);

	canvas_prof->SaveAs(Form("Plots/pdf/%d/GEM_Offsets_For_Run%d.pdf",name,name));
	canvas_prof->Clear();

	delete gDirectory->FindObject("Offset1");
	delete gDirectory->FindObject("Offset2");
	delete gDirectory->FindObject("Offset3");
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		CORRELATION PLOTS
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
const Int_t nbranch = 12;
char *bnames[nbranch]={	"g2xcl.geoposX:g1xcl.geoposX",	"g2ycl.geoposY:g1ycl.geoposY",  
			"g3xcl.geoposX:g1xcl.geoposX",	"g3ycl.geoposY:g1ycl.geoposY",	
			"sCMSNS2LC1.geoposY:g1ycl.geoposY",	"sCMSNS2LC2.geoposY:g1ycl.geoposY",
			"sCMSNS2LC3.geoposY:g1ycl.geoposY",	

			"g3ycl.geoposY:g2ycl.geoposY",	"g3xcl.geoposX:g2xcl.geoposX",
			//"sCMSNS2LC1.geoposY:g1xcl.geoposX",	"sCMSNS2LC2.geoposY:g1xcl.geoposX",
			//"sCMSNS2LC3.geoposY:g1xcl.geoposX",	

			"sCMSNS2LC2.geoposY:sCMSNS2LC1.geoposY",	"sCMSNS2LC3.geoposY:sCMSNS2LC1.geoposY",
			"sCMSNS2LC3.geoposY:sCMSNS2LC2.geoposY",
			};

char *fnames[nbranch] = {"Trk1_X_vs_Trk2_X",	"Trk1_Y_vs_Trk2_Y",
			"Trk1_X_vs_Trk3_X",	"Trk1_Y_vs_Trk3_Y",
			"Trk1_Y_vs_GE11_IV_GIF",	"Trk1_Y_vs_GE11_IV",
			"Trk1_Y_vs_GE11_V",		
			
			"Trk2_Y_vs_Trk3_Y",	"Trk2_X_vs_Trk3_X",
			//"Trk1_X_vs_GE11_IV_GIF",	"Trk1_X_vs_GE11_IV",
			//"Trk1_X_vs_GE11_V",

			"GE11_IV_GIF_vs_GE11_IV",	"GE11_IV_GIF_vs_GE11_V",
			"GE11_IV_vs_GE11_V"
			};

char *xyAxisName[2*nbranch] =	{"Tracker1 X-Hit Position (mm)",	   "Tracker2 X-Hit Position (mm)",	"Tracker1 Y-Hit Position (mm)",     "Tracker2 Y-Hit Position (mm)",
				"Tracker1 X-Hit Position (mm)",     "Tracker3 X-Hit Position (mm)",	"Tracker1 Y-Hit Position (mm)",     "Tracker3 Y-Hit Position (mm)",
				"Tracker1 Y-Hit Position (mm)",     "GE11_IV_GIF Y-Hit Position (mm)",	"Tracker1 Y-Hit Position (mm)",     "GE11_IV Y-Hit Position (mm)",
				"Tracker1 Y-Hit Position (mm)",     "GE11_V Y-Hit Position (mm)",

				"Tracker2 Y-Hit Position (mm)",     "Tracker3 Y-Hit Position (mm)",	"Tracker2 X-Hit Position (mm)",     "Tracker3 X-Hit Position (mm)",
			//	"Tracker1 X-Hit Position (mm)",     "GE11_IV_GIF Y-Hit Position (mm)",	"Tracker1 X-Hit Position (mm)",     "GE11_IV Y-Hit Position (mm)",
			//	"Tracker1 X-Hit Position (mm)",     "GE11_V Y-Hit Position (mm)",

				"GE11_IV_GIF Y-Hit Position (mm)",     "GE11_IV Y-Hit Position (mm)",	"GE11_IV_GIF Y-Hit Position (mm)",     "GE11_V Y-Hit Position (mm)",
				"GE11_IV Y-Hit Position (mm)",     "GE11_V Y-Hit Position (mm)"
				};
const Float_t range[4*nbranch] ={0,100,0,100,		0,100,0,100,		
				0,100,0,100,		0,100,0,100,		
				0,100,0,100,		0,100,0,100,
				0,100,0,100,		
				
				0,100,0,100,		0,100,0,100,		
			//	0,100,0,100,		0,100,0,100,		
			//	0,100,0,100,

				0,100,0,100,            0,100,0,100,
				0,100,0,100
				};

TH2F * hist[nbranch];
TProfile * hprofile[nbranch];
bool CanOldNew = 1;
#if CanOldNew
	TCanvas *Canvas[nbranch];
#else
	cout<<"Canvas is defined already"<<endl;
#endif
TF1 *function[nbranch];

Char_t message[80];
vector<int> vecm,vecn; 
Double_t fit_Low, fit_High;
Int_t k=0;
Int_t l=0;

ofstream o_file;
o_file.open(Form("fit_detail_%d.txt",name));

gStyle->SetOptStat("ne");

o_file<<"NAME_OF_PROFILE_PLOT\tChi2/NDF\tINT.(P0)\tINT.ERR.\tSLOPE(P1)\tSLOPE_ERROR"<<endl;
for(Int_t i=0;i<nbranch;i++){
	k=i*4;
	l=i*2;
	#if CanOldNew
		Canvas[i] = new TCanvas(Form("Canvas%d",i));
		Canvas[i]->Divide(2,1);
		Canvas[i]->cd(1);
	#else
		#ifndef canvas_proff
			canvas_proff = new TCanvas("canvas_proff","canvas_proff",1);
			cout<<"Not defined : Canvas is defined ramkrishna"<<endl;
		#else
			cout<<"Canvas is defined ramkrishna"<<endl;
		#endif
		canvas_proff->Divide(2,1);
		canvas_proff->cd(1);
	#endif

	hist[i] = new TH2F(TString("H_")+TString(fnames[i]),"",100,range[k],range[k+1],100,range[k+2],range[k+3]);
	tmpTree->Draw(TString(bnames[i])+TString(">>H_")+TString(fnames[i]),"","colz");
	printf("correl factor = %g\n",hist[i]->GetCorrelationFactor());
	hist[i]->GetXaxis()->SetTitle(xyAxisName[l]);
	hist[i]->GetYaxis()->SetTitle(xyAxisName[l+1]);
	#if CanOldNew
		cout<<"nope....................."<<endl;
		//Canvas[i]->Modified(); Canvas[i]->Update();
		//TPaveStats *stats =(TPaveStats*)Canvas[i]->GetPrimitive("stats");
		////stats->SetName(TString(fnames[i]));
		//stats->SetX1NDC(.65);
		//stats->SetX2NDC(.9);
		//stats->SetY1NDC(.975);
		//stats->SetY2NDC(.75);
		//stats->SetTextColor(1);
		//TPaveStats *title =(TPaveStats*)Canvas[i]->GetPrimitive("title");
		//title->SetX1NDC(.35);
		//title->SetX2NDC(.65);
		//title->SetY1NDC(.9);
		//title->SetY2NDC(.975);
		//title->SetTextColor(1);
	#else
		canvas_proff_1->Modified(); canvas_proff_1->Update();
		TPaveStats *stats =(TPaveStats*)canvas_proff_1->GetPrimitive("stats");
		stats->SetName(TString(fnames[i]));
		stats->SetX1NDC(.65);
		stats->SetX2NDC(.9);
		stats->SetY1NDC(.975);
		stats->SetY2NDC(.75);
		stats->SetTextColor(1);
		TPaveStats *title =(TPaveStats*)canvas_proff_1->GetPrimitive("title");
		title->SetX1NDC(.35);
		title->SetX2NDC(.65);
		title->SetY1NDC(.9);
		title->SetY2NDC(.975);
		title->SetTextColor(1);
	#endif

	hprofile[i] = new TProfile(TString("P_")+TString(fnames[i]),"",100,range[k],range[k+1],range[k+2],range[k+3]);
	tmpTree->Draw(TString(bnames[i])+TString(">>P_")+TString(fnames[i]),"trackx@.GetEntries()==1 && tracky@.GetEntries()==1 ");
	hprofile[i]->GetXaxis()->SetTitle(xyAxisName[l]);
	hprofile[i]->GetYaxis()->SetTitle(xyAxisName[l+1]);

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

	//hprofile[i]->GetXaxis()->SetRangeUser(fit_Low,fit_High);
	hprofile[i]->GetXaxis()->SetRangeUser(0,100);
//	hprofile[i]->SetMinimum(fit_Low);
	hprofile[i]->SetStats(0);
	hist[i]->SetStats(0);
	hist[i]->Draw("colz");

	#if CanOldNew
		Canvas[i]->cd(2);
	#else
		canvas_proff->cd(2);
	#endif

	hprofile[i]->Draw();

	function[i] = new TF1("f1","[0]+([1]*x)",fit_Low,fit_High);
	//if (i==8) function[i] = new TF1("f1","expo",fit_Low,fit_High);

	function[i]->SetParameters(1,1);

	hprofile[i]->Fit("f1","Q");
	hprofile[i]->Draw();

	TLegend *legend2 = new TLegend (0.1,0.9,.6,0.8,"Linear Fit");
	legend2->SetTextSize(0.04);
	TF1 *fun=hprofile[i]->GetFunction("f1");
	//cout<<"##############################################################"<<endl;
	//cout<<"chi-sqr = "<<fun->GetChisquare()<<endl;
	//cout<<"NDF = "<<fun->GetNDF()<<endl;
	o_file<<TString(fnames[i])<<"\t"<<setprecision(3)<<fixed<<fun->GetChisquare()/fun->GetNDF()<<"\t"<<fun->GetParameter(0)<<"\t"<<fun->GetParError(0)<<"\t"<<fun->GetParameter(1)<<"\t"<<fun->GetParError(1)<<endl; 
	//cout<<"##############################################################"<<endl;
	sprintf(message,"Entry = %i ",hist[i]->GetEntries());
	legend2->AddEntry(fun,message);
	sprintf(message,"#chi^{2}/NDF = %.3f",fun->GetChisquare()/fun->GetNDF());
	legend2->AddEntry(fun,message);
	sprintf(message,"p0 = %.3f #pm  %.3f",fun->GetParameter(0),fun->GetParError(0));
	legend2->AddEntry(fun,message);
	sprintf(message,"p1 = %.3f  #pm %.3f",fun->GetParameter(1),fun->GetParError(1));
	legend2->AddEntry(fun,message);
	legend2->Draw();



	#if CanOldNew
		//	Canvas[i]->SaveAs("Correlation_"+TString(fnames[i])+".png");
		//	Canvas[i]->SaveAs("Correlation_"+TString(fnames[i])+".pdf");
		Canvas[i]->SaveAs(Form("Plots/pdf/%d/Correlation_%s_Run%d.pdf",name,fnames[i],name));
	#else
		canvas_proff->SaveAs(Form("Plots/pdf/%d/Correlation_%s_Run%d.pdf",name,fnames[i],name));
		cout<<"Delete the canvas"<<endl;
		canvas_proff->Clear();
		cout<<"Delete the canvas"<<endl;
	#endif
		cout<<"Deleting  the histograms"<<endl;
	//delete gDirectory->FindObject(hprofile[i]);
	//delete gDirectory->FindObject(hist[i]);
		cout<<"Deleting the histograms"<<endl;

	
}

o_file.close();
o_file3.close();
o_file2.close();
	
	}
	}
