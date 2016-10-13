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

int ClusterSize(TString RootFile, TString OutPutFileName)
{

	std::vector<TFile*> InputFiles;
	InputFiles.clear();
	
	InputFiles.push_back(TFile::Open(RootFile));

	const Int_t NumOfFiles = InputFiles.size();
	cout<<"Num of FIles = "<<NumOfFiles<<endl;

	ofstream o_file;
	o_file.open("Cluster_Size.txt", std::ios_base::app);
	//o_file.open(TString(OutPutFileName)+"_Cluster_Size.txt", std::ios_base::app);
  

	for(unsigned int j = 0; j < InputFiles.size(); ++j ) {
	TTree * tmpTree = (TTree*)InputFiles.at(j)->Get("rd51tbgeo");

	TCanvas *canvas_prof = new TCanvas("canvas_prof","canvas_prof",1);
        gStyle->SetCanvasDefH(800);                                                                                                            
        gStyle->SetCanvasDefW(700);
	gStyle->SetOptFit(1);

	canvas_prof->Divide(1,1);
	canvas_prof->cd(1);
	////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//		Cluster Size PLOTS
	////////////////////////////////////////////////////////////////////////////////////////////////////
	
	TH1F *hClusterSize = new TH1F("hClusterSize","Cluster size for GE1/1", 10,0.,10.);
		hClusterSize->SetStats(1);
		tmpTree->Draw("g1ycl.ngeoch>>hClusterSize","g1ycl@.GetEntries()==1 && g1xcl@.GetEntries()==1");
		hClusterSize->GetXaxis()->SetTitle("Cluster Size");
		hClusterSize->GetYaxis()->SetTitle("#Entries");
		//TF1 *f1 = new TF1("f1","[0]*TMath::Power(([1]),(x))*(TMath::Exp(-([1])))/TMath::Gamma((x)+1)", 0, 10); // "xmin" = 0, "xmax" = 10
		TF1 *f1 = new TF1("f1","[0]*TMath::Power(([1]/[2]),(x/[2]))*(TMath::Exp(-([1]/[2])))/TMath::Gamma((x/[2])+1)", 0, 10); 
		f1->SetParameters(hClusterSize->GetMaximum(), hClusterSize->GetMean(), 1); 
		hClusterSize->Fit("f1"); // Use option "R" = fit between "xmin" and "xmax" of the "f1"

		//hClusterSize->Fit("landau");
		cout<<"\n\n========================="<<endl;
		cout<<OutPutFileName<<"\t"<<(f1->GetParameter(1))/(f1->GetParameter(2))<<"\t"<<sqrt((f1->GetParameter(1))/(f1->GetParameter(2)))<<endl;
		//o_file<<OutPutFileName<<"\t"<<(f1->GetParameter(1))/(f1->GetParameter(2))<<"\t"<<sqrt((f1->GetParameter(1))/(f1->GetParameter(2)))<<endl;
		//o_file<<OutPutFileName<<"\t"<<f1->GetParameter(1)<<"\t"<<sqrt(f1->GetParameter(1))<<endl;
		o_file<<OutPutFileName<<"\t"<<f1->GetParameter(1)<<"\t"<<f1->GetParError(1)<<endl;
		canvas_prof->SaveAs(TString(OutPutFileName)+"_ClusterSize.pdf");	
		canvas_prof->SaveAs(TString(OutPutFileName)+"_ClusterSize.png");	
		canvas_prof->SaveAs(TString(OutPutFileName)+"_ClusterSize.C");	
		canvas_prof->SaveAs(TString(OutPutFileName)+"_ClusterSize.root");	

	
	}	// End of for loop
	o_file.close();
}	// End of main loop
