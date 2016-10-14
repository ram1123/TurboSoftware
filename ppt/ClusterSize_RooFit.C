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

#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooGaussian.h"
#include "RooPlot.h"
#include "TH1D.h"
#include "TRandom.h"
using namespace RooFit ;

void ClusterSize_RooFit(TString RootFile, TString OutPutFileName, TString HistName)
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

	TCut PosCut2080_g1x = "g1xcl.geoposX > 0.0 &&  g1xcl.geoposX <100.0";
	TCut PosCut2080_g1y = "g1ycl.geoposY > 0.0 &&  g1ycl.geoposY <100.0";
	TCut PosCut2080_g2x = "g2xcl.geoposX > 0.0 &&  g2xcl.geoposX <100.0";
	TCut PosCut2080_g2y = "g2ycl.geoposY > 0.0 &&  g2ycl.geoposY <100.0";
	TCut PosCut2080_g3x = "g3xcl.geoposX > 0.0 &&  g3xcl.geoposX <100.0";
	TCut PosCut2080_g3y = "g3ycl.geoposY > 0.0 &&  g3ycl.geoposY <100.0";
	
	TCut PosCut2080_g1 = PosCut2080_g1x && PosCut2080_g1y;
	TCut PosCut2080_g2 = PosCut2080_g2x && PosCut2080_g2y;
	TCut PosCut2080_g3 = PosCut2080_g3x && PosCut2080_g3y;

	cout<<"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;;
	cout<<"		PRINT CUT VALUES			"<<endl;
	cout<<"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
	cout<<"PosCut2080_g1x = "<<PosCut2080_g1x<<endl;
	cout<<"PosCut2080_g2x = "<<PosCut2080_g2x<<endl;
	cout<<"PosCut2080_g3x = "<<PosCut2080_g3x<<endl;
	cout<<"PosCut2080_g1y = "<<PosCut2080_g1y<<endl;
	cout<<"PosCut2080_g2y = "<<PosCut2080_g2y<<endl;
	cout<<"PosCut2080_g3y = "<<PosCut2080_g3y<<endl;
	cout<<"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
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
	TH1F *hClusterSize = new TH1F("hClusterSize",HistName, 10,0.,10.);

	hClusterSize->SetStats(1);
	hClusterSize->GetXaxis()->SetTitle("Cluster Size");
	hClusterSize->GetYaxis()->SetTitle("#Entries");
	//tmpTree->Draw("g1xcl.ngeoch>>hClusterSize","GE11_IV@.GetEntries()==1");
	//tmpTree->Draw("GE11_IV.ngeoch>>hClusterSize",IfHitTrkGE11 && PosCut2080);
	tmpTree->Draw("GE11_IV_GIF.ngeoch>>hClusterSize",IfHitTrkGE11 && PosCut2080);

	// Declare observable x
	#if 1
		RooRealVar x("x","Cluster Size",1,5) ;
	#else
		RooRealVar x("x","Cluster Size",1,10) ;
	#endif
	// Create a binned dataset that imports contents of TH1 and associates its contents to observable 'x'
	RooDataHist dh("dh","dh",x,Import(*hClusterSize));

	// P l o t   a n d   f i t   a   R o o D a t a H i s t
	// ---------------------------------------------------

	// Make plot of binned dataset showing Poisson error bars (RooFit default)
	RooPlot* frame = x.frame(Title(HistName)) ;
	dh.plotOn(frame) ;

	// Fit a Gaussian p.d.f to the data
	//RooRealVar norm("norm","norm",hClusterSize->GetMaximum(),"norm") ;
	RooRealVar norm("norm","norm",10,1,2500,"norm") ;
	RooRealVar mean("mean","mean",hClusterSize->GetMean(),1,6,"Mean") ;
	RooRealVar sigma("sigma","sigma",hClusterSize->GetStdDev(),0,3,"Sigma") ;

	//norm.setConstant(kTRUE);

	#if 1
	//RooGaussian langaus("langaus","gauss",x,mean,sigma) ;
	//RooLandau langaus("langaus","landau",x, mean,sigma);
	//RooGenericPdf langaus("langaus","gauss","norm*TMath::Power(mean,x)*(TMath::Exp(-mean))/TMath::Gamma(x+1)",RooArgList(x,norm,mean));
	RooGenericPdf langaus("langaus","gauss","norm*TMath::Power((mean/sigma),(x/sigma))*(TMath::Exp(-(mean/sigma)))/TMath::Gamma((x/sigma)+1)",RooArgList(x,norm,mean,sigma));
	//RooGenericPdf langaus("langaus","gauss","norm*exp(-(x-mean)*(x-mean)/(2*sigma*sigma))",RooArgList(x,norm,mean,sigma));
	#else
	RooGaussian gauss("gauss","gauss",x,mean,sigma) ;
	//RooGenericPdf gauss("gauss","gauss","norm*TMath::Exp(-1.0*(x-mean)*(x-mean)/(2*sigma*sigma))",RooArgList(x,norm,mean,sigma));
	RooLandau landau("landau","landau",x, mean,sigma);

	//RooRealVar f("f","fraction of gm1",0.4);
	RooRealVar f("f","fraction of gm1",0.7,0.0,1.0);
	//f.setRange(0.1,1.0);
	RooAddModel langaus("langaus","gauss+landau",RooArgList(gauss,landau),f);
	#endif

	langaus.fitTo(dh);
	langaus.plotOn(frame);

	//mean.Print();
	//sigma.Print();
	// Print parameters of the fit
	RooArgSet* paramSet = langaus.getParameters(dh);

	cout<<"=================================================\n"<<endl;
	cout<<OutPutFileName<<endl;
	paramSet->Print("v");
	cout<<"\n=================================================\n\n"<<endl;

	frame->Draw();
	canvas_prof->Update();
	canvas_prof->SaveAs("Test_ClusterSize.pdf");	
	canvas_prof->SaveAs(TString(OutPutFileName)+"_ClusterSize.pdf");	
	canvas_prof->SaveAs(TString(OutPutFileName)+"_ClusterSize.png");	
	}	// End of for loop
	o_file.close();
}	// End of main loop
