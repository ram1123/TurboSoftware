#include "TFile.h"
#include "TTree.h"

#include <iostream>

// you need to get this value from the one who created the "rd51tbgeo" TTree
#define _MAX_POSSIBLE_G1XCL_ 9999

int Correlation_Prob_troubleshoot()
{

       TGaxis::SetMaxDigits(3);
 
  const Int_t NRGBs = 5; 
  const Int_t NCont = 255; 
  Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
  Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
  Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
  Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
  TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
  gStyle->SetNumberContours(NCont);

  TFile *CRC = new TFile("/afs/cern.ch/user/r/rasharma/work/public/GEMTestBeam/TurboSoftware/EventBuilder/OutPutData/Run0411_Muon_10k_MSPL2_HVScan_710pt1_710pt1_710pt0_T20_T20_T20_Lat22/CRC-Run0411_Muon_10k_MSPL2_HVScan_710pt1_710pt1_710pt0_T20_T20_T20_Lat22-141011_013955-0.root","READ");
  if (!(CRC && CRC->IsOpen())) { delete CRC; return -1; }
  
  TTree *rd51tbgeo;
  CRC->GetObject("rd51tbgeo", rd51tbgeo);
  if (!rd51tbgeo) { delete CRC; return -2; }
  
  rd51tbgeo->SetMakeClass(1); // all branches in decomposed object mode
  rd51tbgeo->SetBranchStatus("*", 0); // disable all branches
  
  Int_t g1ycl_ = -1;
  rd51tbgeo->SetBranchStatus("g1ycl", 1); // activate "g1ycl"
  rd51tbgeo->SetBranchAddress("g1ycl", &g1ycl_);
  
  Float_t geoposY1[(_MAX_POSSIBLE_G1XCL_)];
  rd51tbgeo->SetBranchStatus("g1ycl.geoposY", 1); // activate "g1ycl.geoposY"
  rd51tbgeo->SetBranchAddress("g1ycl.geoposY", geoposY1);
  
  Int_t sCMSNS2LC1_ = -1;
  rd51tbgeo->SetBranchStatus("sCMSNS2LC1", 1); // activate "sCMSNS2LC1"
  rd51tbgeo->SetBranchAddress("sCMSNS2LC1", &sCMSNS2LC1_);
  
  Float_t geoposY[(_MAX_POSSIBLE_G1XCL_)];
  rd51tbgeo->SetBranchStatus("sCMSNS2LC1.geoposY", 1); // activate "g1ycl.geoposY"
  rd51tbgeo->SetBranchAddress("sCMSNS2LC1.geoposY", geoposY);
  
  
  Long64_t nevent = rd51tbgeo->GetEntries();
  
  std::cout << "####### nevent = " << nevent << std::endl;
  int count=0;
  double pi = 4.0*atan(1.0);
  double x0[11000],y0[11000];
  double x[11000],y[11000];

  TH2F *h2 = new TH2F("h2","",100,-60,60,100,-10,150);
  TH2F *h20 = new TH2F("h20","",100,-10,110,100,-10,110);
  TCanvas *Canvas1 = new TCanvas("c1236","Muon",200,10,800,700);

  double mean=0.;
  for (Long64_t i = 0; i < nevent; i++) {
    rd51tbgeo->GetEntry(i);
    
    //std::cout << "i = " << i << std::endl;
    //std::cout << "g1ycl_ = " << g1ycl_ << std::endl;
    for (Int_t j = 0; j < sCMSNS2LC1_; j++) {
//      std::cout << "geoposY[" << j <<  "] = " << geoposY[j] << std::endl;
    }
    if (g1ycl_ == 1 && sCMSNS2LC1_ == 1) 
    {
	x[i]=geoposY1[0]*cos(pi/4.0)-geoposY[0]*sin(pi/4.0);
	y[i]=geoposY1[0]*sin(pi/4.0)+geoposY[0]*cos(pi/4.0);
	x0[i]=geoposY1[0];
	y0[i]=geoposY[0];
    h2->Fill(x[i],y[i]);
    h20->Fill(x0[i],y0[i]);
    }
/*     else
 *     {
 * 	x[i]=-100.0;
 * 	y[i]=-100.0;
 *     }
 */
  }
  cout<<"mean = "<<mean<<endl;
  Canvas1->Divide(2,2);
  Canvas1->cd(1);
  h20->Draw("colz");
  h20->GetXaxis()->SetTitle("xaxis");
  Canvas1->cd(2);
  h2->Draw("colz");
  TH1D * projh2X = h2->ProjectionX();
  TH1D * projh2Y = h2->ProjectionY();
  Canvas1->cd(3);
  //h2->FitSlicesX();
  projh2X->Draw();
  Canvas1->cd(4);
  projh2Y->Draw();

  Canvas1->SaveAs("corr.pdf");

/* 
 *   gr = new TGraph(11000,x,y);
 *   gr->GetXaxis()->SetRangeUser(-60.,60.);
 *   gr->GetYaxis()->SetRangeUser(-10.,150.);
 *   gr->Draw("A*");
 *     
 */

  cout<<"count = "<<count<<endl;
  
  rd51tbgeo->ResetBranchAddresses(); // "detach" from local variables
  
  delete CRC; // it will automatically delete "rd51tbgeo", too
  return 0;
}
