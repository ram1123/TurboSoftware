/*
 * =====================================================================================
 *
 *       Filename:  Hit_Information.C
 *
 *    Description:  This code creates a text file in which there is hit information 
 *    		    For trackers and GEM detectors
 *
 *        Version:  1.0
 *        Created:  Wednesday 28 January 2015 07:20:03  CET
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ramkrishna Sharma (Ram), ramkrishna.sharma71@gmail.com
 *   Organization:  University Of Delhi, Delhi, India
 *
 * =====================================================================================
 */

#include "TFile.h"
#include "TTree.h"
#include <vector>
#include <algorithm>
#include <math.h>
#include <iostream>
#include <fstream>

// need to get this value from  "rd51tbgeo" TTree; presetnly in our case in some run this is near 20k and in many cases its about 10k
#define _MAX_POSSIBLE_G1XCL_ 29999

int Hit_Information()
{
  TFile *CRC = new TFile("/afs/cern.ch/user/r/rasharma/work/public/GEMTestBeam/TurboSoftware/EventBuilder/OutPutData/Run0411_Muon_10k_MSPL2_HVScan_710pt1_710pt1_710pt0_T20_T20_T20_Lat22/CRC-Run0411_Muon_10k_MSPL2_HVScan_710pt1_710pt1_710pt0_T20_T20_T20_Lat22-141011_013955-0.root", "READ");
  if (!(CRC && CRC->IsOpen())) { delete CRC; return -1; }
  
  TTree *rd51tbgeo;
  CRC->GetObject("rd51tbgeo", rd51tbgeo);
  if (!rd51tbgeo) { delete CRC; return -2; }
  
  rd51tbgeo->SetMakeClass(1); // all branches in decomposed object mode
  rd51tbgeo->SetBranchStatus("*", 0); // disable all branches
  
  Int_t g1xcl_ = -1;
  rd51tbgeo->SetBranchStatus("g1xcl", 1); // activate "g1xcl"
  rd51tbgeo->SetBranchAddress("g1xcl", &g1xcl_);
  
  Float_t geoposX1[(_MAX_POSSIBLE_G1XCL_)];
  rd51tbgeo->SetBranchStatus("g1xcl.geoposX", 1); // activate "g1xcl.geoposX"
  rd51tbgeo->SetBranchAddress("g1xcl.geoposX", geoposX1);
  
  Int_t g2xcl_ = -1;
  rd51tbgeo->SetBranchStatus("g2xcl", 1); // activate "g1xcl"
  rd51tbgeo->SetBranchAddress("g2xcl", &g2xcl_);
  
  Float_t geoposX2[(_MAX_POSSIBLE_G1XCL_)];
  rd51tbgeo->SetBranchStatus("g2xcl.geoposX", 1); // activate "g1xcl.geoposX"
  rd51tbgeo->SetBranchAddress("g2xcl.geoposX", geoposX2);
  
  Int_t g3xcl_ = -1;
  rd51tbgeo->SetBranchStatus("g3xcl", 1); // activate "g1xcl"
  rd51tbgeo->SetBranchAddress("g3xcl", &g3xcl_);
  
  Float_t geoposX3[(_MAX_POSSIBLE_G1XCL_)];
  rd51tbgeo->SetBranchStatus("g3xcl.geoposX", 1); // activate "g1xcl.geoposX"
  rd51tbgeo->SetBranchAddress("g3xcl.geoposX", geoposX3);
  
  Int_t g1ycl_ = -1;
  rd51tbgeo->SetBranchStatus("g1ycl", 1); // activate "g1ycl"
  rd51tbgeo->SetBranchAddress("g1ycl", &g1ycl_);
  
  Float_t geoposY1[(_MAX_POSSIBLE_G1XCL_)];
  rd51tbgeo->SetBranchStatus("g1ycl.geoposY", 1); // activate "g1ycl.geoposY"
  rd51tbgeo->SetBranchAddress("g1ycl.geoposY", geoposY1);
  
  Int_t g2ycl_ = -1;
  rd51tbgeo->SetBranchStatus("g2ycl", 1); // activate "g1ycl"
  rd51tbgeo->SetBranchAddress("g2ycl", &g2ycl_);
  
  Float_t geoposY2[(_MAX_POSSIBLE_G1XCL_)];
  rd51tbgeo->SetBranchStatus("g2ycl.geoposY", 1); // activate "g1ycl.geoposY"
  rd51tbgeo->SetBranchAddress("g2ycl.geoposY", geoposY2);
  
  Int_t g3ycl_ = -1;
  rd51tbgeo->SetBranchStatus("g3ycl", 1); // activate "g1ycl"
  rd51tbgeo->SetBranchAddress("g3ycl", &g3ycl_);
  
  Float_t geoposY3[(_MAX_POSSIBLE_G1XCL_)];
  rd51tbgeo->SetBranchStatus("g3ycl.geoposY", 1); // activate "g1ycl.geoposY"
  rd51tbgeo->SetBranchAddress("g3ycl.geoposY", geoposY3);
  
  Int_t sCMSNS2LC1_ = -1;
  rd51tbgeo->SetBranchStatus("sCMSNS2LC1", 1); // activate "g1ycl"
  rd51tbgeo->SetBranchAddress("sCMSNS2LC1", &sCMSNS2LC1_);
  
  Float_t LC1geoposY[(_MAX_POSSIBLE_G1XCL_)];
  rd51tbgeo->SetBranchStatus("sCMSNS2LC1.geoposY", 1); // activate "g1ycl.geoposY"
  rd51tbgeo->SetBranchAddress("sCMSNS2LC1.geoposY", LC1geoposY);

  Int_t sCMSNS2LC2_ = -1;
  rd51tbgeo->SetBranchStatus("sCMSNS2LC2", 1); // activate "g1ycl"
  rd51tbgeo->SetBranchAddress("sCMSNS2LC2", &sCMSNS2LC2_);
  
  Float_t LC2geoposY[(_MAX_POSSIBLE_G1XCL_)];
  rd51tbgeo->SetBranchStatus("sCMSNS2LC2.geoposY", 1); // activate "g1ycl.geoposY"
  rd51tbgeo->SetBranchAddress("sCMSNS2LC2.geoposY", LC2geoposY);

  Int_t sCMSNS2LC3_ = -1;
  rd51tbgeo->SetBranchStatus("sCMSNS2LC3", 1); // activate "g1ycl"
  rd51tbgeo->SetBranchAddress("sCMSNS2LC3", &sCMSNS2LC3_);
  
  Float_t LC3geoposY[(_MAX_POSSIBLE_G1XCL_)];
  rd51tbgeo->SetBranchStatus("sCMSNS2LC3.geoposY", 1); // activate "g1ycl.geoposY"
  rd51tbgeo->SetBranchAddress("sCMSNS2LC3.geoposY", LC3geoposY);


  Long64_t nevent = rd51tbgeo->GetEntries();
  
  std::cout << "####### nevent = " << nevent << std::endl;
  
  // create a card
  std::ofstream file_out("Hit_Position_Info.txt");
  if (!file_out){
	std::cout << "error: Could not open the file Hit_Position_Info.txt" << std::endl;
  }
//  file_out.open("Hit_Position_Info.txt");
	file_out<<"\t| \t\tTrackers\t\t\t|\tGEM"<<std::endl;
	file_out<<"\t----------------------------------------------------------------------"<<std::endl;
	file_out<<"\tx\tx\tx\ty\ty\ty\ty\ty\ty"<<std::endl;
	file_out<<"Event No Trk1\tTrk2\tTrk3\tTrk1\tTrk2\tTrk3\tGEM1\tGEM2\tGEM3"<<std::endl;
	file_out<<"--------------------------------------------------------------------------------------"<<std::endl;
	file_out<<"--------------------------------------------------------------------------------------"<<std::endl;

bool hit;
std::cout<<"Want text file corresponding to only one hit or all: ";
std::cin>>hit;
//if(hit) std::cout<<"ramkrishna"<<std::endl;
//else std::cout<<"sharma"<<std::endl;
  for (Long64_t i = 0; i < nevent; i++) {
//  for (Long64_t i = 0; i < 3; i++) {
    rd51tbgeo->GetEntry(i);
    vector<Int_t> PosSort;
    PosSort.clear();
    PosSort.push_back(g1xcl_);
    PosSort.push_back(g2xcl_);
    PosSort.push_back(g3xcl_);
    PosSort.push_back(g1ycl_);
    PosSort.push_back(g2ycl_);
    PosSort.push_back(g3ycl_);
    PosSort.push_back(sCMSNS2LC1_);
    PosSort.push_back(sCMSNS2LC2_);
    PosSort.push_back(sCMSNS2LC3_);
    
    std::sort(PosSort.begin(), PosSort.end());
//    cout << "DEBUG after : a = (";
//      for (size_t k = 0; k != PosSort.size(); ++k) {
//       cout << PosSort.at(k);
//       if (k != (PosSort.size()-1))
//       cout << ", ";
//      } // for (i)
//        cout << ")" << endl;
//
//    cout<<"Last element = "<<PosSort.back()<<endl;
    if (hit)
    if ((g1xcl_==0 || g1xcl_>1)|| ( g2xcl_ == 0 || g2xcl_ >1) || (g3xcl_ == 0 || g3xcl_ >1)|| (g1ycl_==0 || g1ycl_>1)|| ( g2ycl_ == 0 || g2ycl_ >1) || (g3ycl_ == 0 || g3ycl_ >1)) continue;
        file_out<<i<<"\t";
    for (Int_t j=0; j<PosSort.back();j++){
    	if (j==0 && g1xcl_ == 0 ) file_out<<"--\t";
	else
    	if (g1xcl_ == 0 ) file_out<<"\t--\t";
	else {
		if (j==0 && g1xcl_ > j ) file_out<<geoposX1[j]<<"\t";
		else if (g1xcl_ > j ) file_out<<"\t"<<geoposX1[j]<<"\t";
		else file_out<<"\t--\t";
	}
    	if (g2xcl_ == 0 ) file_out<<"--\t";
	else {
		if (g2xcl_ > j ) file_out<<geoposX2[j]<<"\t";
		else file_out<<"--\t";
	}
    	if (g3xcl_ == 0 ) file_out<<"--\t";
	else {
		if (g3xcl_ > j ) file_out<<geoposX3[j]<<"\t";
		else file_out<<"--\t";
	}
    	if (g1ycl_ == 0 ) file_out<<"--\t";
	else {
		if (g1ycl_ > j ) file_out<<geoposY1[j]<<"\t";
		else file_out<<"--\t";
	}
    	if (g2ycl_ == 0 ) file_out<<"--\t";
	else {
		if (g2ycl_ > j ) file_out<<geoposY2[j]<<"\t";
		else file_out<<"--\t";
	}
    	if (g3ycl_ == 0 ) file_out<<"--\t";
	else {
		if (g3ycl_ > j ) file_out<<geoposY3[j]<<"\t";
		else file_out<<"--\t";
	}
    	if (sCMSNS2LC1_ == 0 ) file_out<<"--\t";
	else {
		if (sCMSNS2LC1_ > j ) file_out<<LC1geoposY[j]<<"\t";
		else file_out<<"--\t";
	}
    	if (sCMSNS2LC2_ == 0 ) file_out<<"--\t";
	else {
		if (sCMSNS2LC2_ > j ) file_out<<LC2geoposY[j]<<"\t";
		else file_out<<"--\t";
	}
    	if (sCMSNS2LC3_ == 0 ) file_out<<"--\t";
	else {
		if (sCMSNS2LC3_ > j ) file_out<<LC3geoposY[j]<<"\t";
		else file_out<<"\t--";
	}
	file_out<<std::endl;
    }
	file_out<<std::endl;
	file_out<<"--------------------------------------------------------------------------------------"<<std::endl;
/* 
    std::cout << "###################################################################### " << std::endl;
    std::cout << "i = " << i << std::endl;
    std::cout << "g1xcl_ = " << g1xcl_ << std::endl;
    for (Int_t j = 0; j < g1xcl_; j++) {
      std::cout << "geoposX1[" << i<<" , "<<j <<  "] = " << geoposX1[j] << std::endl;
    }
    std::cout << "g2xcl_ = " << g2xcl_ << std::endl;
    for (Int_t j = 0; j < g2xcl_; j++) {
      std::cout << "geoposX2[" << i<<" , "<<j <<  "] = " << geoposX2[j] << std::endl;
    }
    std::cout << "g3xcl_ = " << g3xcl_ << std::endl;
    for (Int_t j = 0; j < g3xcl_; j++) {
      std::cout << "geoposX3[" << i<<" , "<<j <<  "] = " << geoposX3[j] << std::endl;
    }
    std::cout << "g1ycl_ = " << g1ycl_ << std::endl;
    for (Int_t j = 0; j < g1ycl_; j++) {
      std::cout << "geoposY1[" << i<<" , "<<j <<  "] = " << geoposY1[j] << std::endl;
    }
    std::cout << "g2ycl_ = " << g2ycl_ << std::endl;
    for (Int_t j = 0; j < g2ycl_; j++) {
      std::cout << "geoposY2[" << i<<" , "<<j <<  "] = " << geoposY2[j] << std::endl;
    }
    std::cout << "g3ycl_ = " << g3ycl_ << std::endl;
    for (Int_t j = 0; j < g3ycl_; j++) {
      std::cout << "geoposY3[" << i<<" , "<<j <<  "] = " << geoposY3[j] << std::endl;
    }
    std::cout << "sCMSNS2LC1_ = " << sCMSNS2LC1_ << std::endl;
    for (Int_t j = 0; j < sCMSNS2LC1_; j++) {
      std::cout << "LC1geoposY[" << i<<" , "<<j <<  "] = " << LC1geoposY[j] << std::endl;
    }
    std::cout << "sCMSNS2LC2_ = " << sCMSNS2LC2_ << std::endl;
    for (Int_t j = 0; j < sCMSNS2LC2_; j++) {
      std::cout << "LC2geoposY[" << i<<" , "<<j <<  "] = " << LC2geoposY[j] << std::endl;
    }
    std::cout << "sCMSNS2LC3_ = " << sCMSNS2LC3_ << std::endl;
    for (Int_t j = 0; j < sCMSNS2LC3_; j++) {
      std::cout << "LC3geoposY[" << i<<" , "<<j <<  "] = " << LC3geoposY[j] << std::endl;
    }
  */	
   
  }
  
  rd51tbgeo->ResetBranchAddresses(); // "detach" from local variables
  
//  file_out.close();

  delete CRC; // it will automatically delete "rd51tbgeo", too
  return 0;
}
