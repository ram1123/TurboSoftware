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

void ClusterSize(TString RootFile, TString OutPutFileName, TString HistName)
{

	std::vector<TFile*> InputFiles;
	InputFiles.clear();
	
	InputFiles.push_back(TFile::Open(RootFile));

	const Int_t NumOfFiles = InputFiles.size();
	cout<<"Num of FIles = "<<NumOfFiles<<endl;

	ofstream o_file;
	o_file.open("Cluster_Size.txt", std::ios_base::app);
	//o_file.open(TString(OutPutFileName)+"_Cluster_Size.txt", std::ios_base::app);

	//TCut IfHitTrkGE11 = "GE11_IV@.GetEntries()==1 && g1xcl@.GetEntries()==1 && g2xcl@.GetEntries()==1 && g3xcl@.GetEntries()==1 && g1ycl@.GetEntries()==1 && g2ycl@.GetEntries()==1 && g3ycl@.GetEntries()==1";
	TCut IfHitTrkGE11 = "GE11_IV_GIF@.GetEntries()==1 && g1xcl@.GetEntries()==1 && g2xcl@.GetEntries()==1 && g3xcl@.GetEntries()==1 && g1ycl@.GetEntries()==1 && g2ycl@.GetEntries()==1 && g3ycl@.GetEntries()==1";

	TCut PosCut2080_g1x = "g1xcl.geoposX > 41.0 &&  g1xcl.geoposX <51.";
	TCut PosCut2080_g1y = "g1ycl.geoposY > 41.0 &&  g1ycl.geoposY <51.";
	TCut PosCut2080_g2x = "g2xcl.geoposX > 41.0 &&  g2xcl.geoposX <51.";
	TCut PosCut2080_g2y = "g2ycl.geoposY > 41.0 &&  g2ycl.geoposY <51.";
	TCut PosCut2080_g3x = "g3xcl.geoposX > 41.0 &&  g3xcl.geoposX <51.";
	TCut PosCut2080_g3y = "g3ycl.geoposY > 41.0 &&  g3ycl.geoposY <51.";
	
	TCut PosCut2080_g1 = PosCut2080_g1x && PosCut2080_g1y;
	TCut PosCut2080_g2 = PosCut2080_g2x && PosCut2080_g2y;
	TCut PosCut2080_g3 = PosCut2080_g3x && PosCut2080_g3y;

	TCut PosCut2080 = PosCut2080_g1 && PosCut2080_g2 && PosCut2080_g3 ;

	for(unsigned int j = 0; j < InputFiles.size(); ++j ) {
	TTree * tmpTree = (TTree*)InputFiles.at(j)->Get("rd51tbgeo");

	TCanvas *canvas_prof = new TCanvas("canvas_prof","canvas_prof",1);
        gStyle->SetCanvasDefH(800);                                                                                                            
        gStyle->SetCanvasDefW(700);
	gStyle->SetOptFit(1);

	canvas_prof->Divide(1,1);
	canvas_prof->cd(1);
	////////////////////////////////////////////////////////////////////////////////////////////////////
	//		Cluster Size PLOTS
	////////////////////////////////////////////////////////////////////////////////////////////////////
	
	HistName=HistName+" #mu A";
	TH1F *hClusterSize = new TH1F("hClusterSize",HistName, 100,0.,10.);

	hClusterSize->SetStats(1);
	hClusterSize->GetXaxis()->SetTitle("Cluster Size");
	hClusterSize->GetYaxis()->SetTitle("#Entries");
	//tmpTree->Draw("g1xcl.ngeoch>>hClusterSize","GE11_IV@.GetEntries()==1");
	//tmpTree->Draw("GE11_IV.ngeoch>>hClusterSize",IfHitTrkGE11 && PosCut2080);
	tmpTree->Draw("GE11_IV_GIF.ngeoch>>hClusterSize",IfHitTrkGE11 && PosCut2080);
	
	TF1 *f1 = new TF1("f1","[0]*TMath::Power(([1]/[2]),(x/[2]))*(TMath::Exp(-([1]/[2])))/TMath::Gamma((x/[2])+1)", 1, 10); 
	f1->SetParameters(hClusterSize->GetMaximum(), hClusterSize->GetMean(), hClusterSize->GetStdDev()); 
	f1->SetParLimits(0,200,480);
	f1->SetParLimits(1,1.55,1.99); 
//	f1->SetParLimits(2,.24,.29); 
//	hClusterSize->Fit("f1","R"); // Use option "R" = fit between "xmin" and "xmax" of the "f1"

	TF1 *f2 = new TF1("
	
	o_file<<OutPutFileName<<"\t"<<f1->GetParameter(1)<<"\t"<<f1->GetParError(1)<<endl;
	cout<<OutPutFileName<<"\t"<<f1->GetParameter(1)<<"\t"<<f1->GetParError(1)<<endl;
	//o_file<<OutPutFileName<<"\t"<<hClusterSize->GetMean()<<"\t"<<hClusterSize->GetStdDev()<<endl;

	canvas_prof->Update();
	canvas_prof->SaveAs("Test_ClusterSize.pdf");	
	canvas_prof->SaveAs(TString(OutPutFileName)+"_ClusterSize.pdf");	
	canvas_prof->SaveAs(TString(OutPutFileName)+"_ClusterSize.png");	
	}	// End of for loop
	o_file.close();
}	// End of main loop
