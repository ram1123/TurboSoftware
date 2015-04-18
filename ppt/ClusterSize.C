/*
 * =====================================================================================
 *
 *       Filename:  ClusterSize.C
 *
 *    Description:  This code extracts the mean of each cluster for few runs and 
 *		    the information in a text file
 *
 *        Version:  1.0
 *        Created:  Sunday 19 April 2015 12:44:13  CEST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ramkrishna Sharma (Ram), ramkrishna.sharma71@gmail.com
 *   Organization:  CERN
 *
 * =====================================================================================
 */


#include "grain.h"
#include <iostream>

using namespace std;

int grain()
{
  ofstream myfile;
  TFile *T_AN60 = new TFile("AN-CRC-Run060_Icomp100_Th15_MSPL1_lat30-29_I687uA_I677uA_asynchrous-121114_060053-0.root ","READ");
  const Float_t current_59 = 677.0 ; 

 TCanvas *c1 = new TCanvas("c1","c1",1);
        c1->Divide(3,2);
const Int_t nbranch = 2;
char* branches[nbranch]={"hsCMSNS2LC2_CLS_Eff","hsCMSNS2LC2_CLS_Eff","hsCMSNS2LC1_CLS_Eff"};
//hsCMSNS2LC1_Residual_X hsCMSNS2LC2_Residual_X, hsCMSNS2LC1_Distance_Eff hsCMSNS2LC2_Distance_Eff hsCMSNS2LC2_CLS_Eff hsCMSNS2LC1_XY_Ineff hsCMSNS2LC2_XY_Ineff hsCMSNS2LC1_XY_Eff hsCMSNS2LC2_XY_Eff hsCMSNS2LC1_Eff hsCMSNS2LC2_Eff hsCMSNS2LC1_Residual_X  hsCMSNS2LC1_Distance_Eff  
for(int i=0;i<nbranch;i++)
{
  myfile.open ("Current_vs_ClusterSize_"+TString(branches[i])+".txt");

TH1F *HT60 = (TH1F*)T_AN60->Get(TString(branches[i]));
	c1->cd(1);
	HT60->SetAxisRange(0,10);
	HT60->GetXaxis()->SetTitle("Cluster Size");
	HT60->SetTitle("Cluster Size For Run 60");	
	myfile<<current_60<<"\t\t "<<HT60->GetMean(1)<<endl;
	cout<<current_60<<"\t\t "<<HT60->GetMean(1)<<endl;
	HT60->Draw();

c1->SaveAs(TString(branches[i])+".pdf");
myfile.close();
}
return 0;
}
