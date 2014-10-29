#include "TFile.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
void EFF(){
  gROOT->Reset();
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(1002210);
  gStyle->SetOptDate();

  float ZCTL = 4.89;
  float *ICTL;
  TString *filename;

/*
  Int_t NumberOfFiles = 7;  

  ICTL = new float[NumberOfFilesPerPoint*NumberOfPoints];
  filename = new TString[NumberOfFilesPerPoint*NumberOfPoints];


  filename[0]  = "AN-CRC-Run0035-3mmCTL-HVScanPt1--TRK4p3IC40-CTL3p10-T23p90-Ic40Is110-m4l15ThConf1-110925_224518-0.root";
  filename[1]  = "AN-CRC-Run0039-3mmCTL-HVScanPt2--TRK4p3IC40-CTL3p20-T24p05-Ic40Is110-m4l15ThConf1-110925_234040-0.root";
  filename[2]  = "AN-CRC-Run0043-3mmCTL-HVScanPt3--TRK4p3IC40-CTL3p30-T24p20-Ic40Is110-m4l15ThConf1-110926_032325-0.root";
  filename[3]  = "AN-CRC-Run0047-3mmCTL-HVScanPt4--TRK4p3IC40-CTL3p40-T24p30-Ic40Is110-m4l15ThConf1-110926_051939-0.root";
  filename[4]  = "AN-CRC-Run0051-3mmCTL-HVScanPt5--TRK4p3IC40-CTL3p45-T24p35-Ic40Is110-m4l15ThConf1-110926_063537-0.root";
  filename[5]  = "AN-CRC-Run0055-3mmCTL-HVScanPt6--TRK4p3IC40-CTL3p50-T24p40-Ic40Is110-m4l15ThConf1-110926_072507-0.root";
  filename[6]  = "AN-CRC-Run0059-3mmCTL-HVScanPt7--TRK4p3IC40-CTL3p55-T24p45-Ic40Is110-m4l15ThConf1-110926_093127-0.root";

  ICTL[0]  = 3100/ZCTL;
  ICTL[1]  = 3200/ZCTL;
  ICTL[2]  = 3300/ZCTL;
  ICTL[3]  = 3400/ZCTL;
  ICTL[4]  = 3450/ZCTL;
  ICTL[5] = 3500/ZCTL;
  ICTL[6] = 3550/ZCTL;
*/

  Int_t NumberOfFilesPerPoint = 2;  
  Int_t NumberOfPoints  = 7;

  ICTL = new float[NumberOfPoints];
  filename = new TString[NumberOfFilesPerPoint*NumberOfPoints];


  filename[0]  = "AN-CRC-Run0034-3mmCTL-HVScanPt1--TRK4p3IC40-CTL3p10-T23p90-Ic40Is110-m4l14ThConf1-110925_222150-0.root";
  filename[1]  = "AN-CRC-Run0035-3mmCTL-HVScanPt1--TRK4p3IC40-CTL3p10-T23p90-Ic40Is110-m4l15ThConf1-110925_224518-0.root";
  filename[2]  = "AN-CRC-Run0038-3mmCTL-HVScanPt2--TRK4p3IC40-CTL3p20-T24p05-Ic40Is110-m4l14ThConf1-110925_233133-0.root";
  filename[3]  = "AN-CRC-Run0039-3mmCTL-HVScanPt2--TRK4p3IC40-CTL3p20-T24p05-Ic40Is110-m4l15ThConf1-110925_234040-0.root";
  filename[4]  = "AN-CRC-Run0042-3mmCTL-HVScanPt3--TRK4p3IC40-CTL3p30-T24p20-Ic40Is110-m4l14ThConf1-110926_030150-0.root";
  filename[5]  = "AN-CRC-Run0043-3mmCTL-HVScanPt3--TRK4p3IC40-CTL3p30-T24p20-Ic40Is110-m4l15ThConf1-110926_032325-0.root";
  filename[6]  = "AN-CRC-Run0046-3mmCTL-HVScanPt4--TRK4p3IC40-CTL3p40-T24p30-Ic40Is110-m4l14ThConf1-110926_051003-0.root";
  filename[7]  = "AN-CRC-Run0047-3mmCTL-HVScanPt4--TRK4p3IC40-CTL3p40-T24p30-Ic40Is110-m4l15ThConf1-110926_051939-0.root";
  filename[8]  = "AN-CRC-Run0050-3mmCTL-HVScanPt5--TRK4p3IC40-CTL3p45-T24p35-Ic40Is110-m4l14ThConf1-110926_062456-0.root";
  filename[9]  = "AN-CRC-Run0051-3mmCTL-HVScanPt5--TRK4p3IC40-CTL3p45-T24p35-Ic40Is110-m4l15ThConf1-110926_063537-0.root";
  filename[10] = "AN-CRC-Run0054-3mmCTL-HVScanPt6--TRK4p3IC40-CTL3p50-T24p40-Ic40Is110-m4l14ThConf1-110926_071422-0.root";
  filename[11] = "AN-CRC-Run0055-3mmCTL-HVScanPt6--TRK4p3IC40-CTL3p50-T24p40-Ic40Is110-m4l15ThConf1-110926_072507-0.root";
  filename[12] = "AN-CRC-Run0058-3mmCTL-HVScanPt7--TRK4p3IC40-CTL3p55-T24p45-Ic40Is110-m4l14ThConf1-110926_092328-0.root";
  filename[13] = "AN-CRC-Run0059-3mmCTL-HVScanPt7--TRK4p3IC40-CTL3p55-T24p45-Ic40Is110-m4l15ThConf1-110926_093127-0.root";

  ICTL[0]  = 3100/ZCTL;
  ICTL[1]  = 3200/ZCTL;
  ICTL[2]  = 3300/ZCTL;
  ICTL[3]  = 3400/ZCTL;
  ICTL[4]  = 3450/ZCTL;
  ICTL[5] = 3500/ZCTL;
  ICTL[6] = 3550/ZCTL;

  float       *tmpCTLBottomLeftxcl_EFF;
  float       *tmpCTLBottomLeftxcl_EFFSTERR;
  float       *tmpCTLBottomLeftycl_EFF;
  float       *tmpCTLBottomLeftycl_EFFSTERR;
  float        *tmpCTLTopMiddlexcl_EFF;
  float        *tmpCTLTopMiddlexcl_EFFSTERR;
  float       *tmpCTLMiddleLeftycl_EFF;
  float       *tmpCTLMiddleLeftycl_EFFSTERR;
  float *tmpCTLSingleMiddleLeftycl_EFF;
  float *tmpCTLSingleMiddleLeftycl_EFFSTERR;

        tmpCTLBottomLeftxcl_EFF 	= new float[NumberOfFilesPerPoint*NumberOfPoints];
        tmpCTLBottomLeftxcl_EFFSTERR 	= new float[NumberOfFilesPerPoint*NumberOfPoints];
        tmpCTLBottomLeftycl_EFF 	= new float[NumberOfFilesPerPoint*NumberOfPoints];
        tmpCTLBottomLeftycl_EFFSTERR 	= new float[NumberOfFilesPerPoint*NumberOfPoints];
         tmpCTLTopMiddlexcl_EFF 	= new float[NumberOfFilesPerPoint*NumberOfPoints];
         tmpCTLTopMiddlexcl_EFFSTERR 	= new float[NumberOfFilesPerPoint*NumberOfPoints];
        tmpCTLMiddleLeftycl_EFF 	= new float[NumberOfFilesPerPoint*NumberOfPoints];
        tmpCTLMiddleLeftycl_EFFSTERR 	= new float[NumberOfFilesPerPoint*NumberOfPoints];
  tmpCTLSingleMiddleLeftycl_EFF 	= new float[NumberOfFilesPerPoint*NumberOfPoints];
  tmpCTLSingleMiddleLeftycl_EFFSTERR 	= new float[NumberOfFilesPerPoint*NumberOfPoints];

  float       *CTLBottomLeftxcl_EFF;
  float       *CTLBottomLeftxcl_EFFSTERR;
  float       *CTLBottomLeftycl_EFF;
  float       *CTLBottomLeftycl_EFFSTERR;
  float        *CTLTopMiddlexcl_EFF;
  float        *CTLTopMiddlexcl_EFFSTERR;
  float       *CTLMiddleLeftycl_EFF;
  float       *CTLMiddleLeftycl_EFFSTERR;
  float *CTLSingleMiddleLeftycl_EFF;
  float *CTLSingleMiddleLeftycl_EFFSTERR;

        CTLBottomLeftxcl_EFF 		= new float[NumberOfPoints];
        CTLBottomLeftxcl_EFFSTERR 	= new float[NumberOfPoints];
        CTLBottomLeftycl_EFF 		= new float[NumberOfPoints];
        CTLBottomLeftycl_EFFSTERR 	= new float[NumberOfPoints];
         CTLTopMiddlexcl_EFF 		= new float[NumberOfPoints];
         CTLTopMiddlexcl_EFFSTERR 	= new float[NumberOfPoints];
        CTLMiddleLeftycl_EFF 		= new float[NumberOfPoints];
        CTLMiddleLeftycl_EFFSTERR 	= new float[NumberOfPoints];
  CTLSingleMiddleLeftycl_EFF 		= new float[NumberOfPoints];
  CTLSingleMiddleLeftycl_EFFSTERR 	= new float[NumberOfPoints];


  for (Int_t i=0; i<NumberOfFilesPerPoint*NumberOfPoints; i++)
  {
  TFile *file = new TFile(filename[i]);
  TH1F *hCTLBottomLeftxcl_Eff; 		
  TH1F *hCTLBottomLeftycl_Eff; 		
  TH1F *hCTLTopMiddlexcl_Eff; 		
  TH1F *hCTLMiddleLeftycl_Eff; 		
  TH1F *hCTLSingleMiddleLeftycl_Eff; 	

  gDirectory->GetObject("hgCTLBottomLeftxcl_Eff;1",hCTLBottomLeftxcl_Eff);
  gDirectory->GetObject("hgCTLBottomLeftycl_Eff;1",hCTLBottomLeftycl_Eff);
  gDirectory->GetObject("hgCTLTopMiddlexcl_Eff;1",hCTLTopMiddlexcl_Eff);
  gDirectory->GetObject("hgCTLMiddleLeftycl_Eff;1",hCTLMiddleLeftycl_Eff);
  gDirectory->GetObject("hgCTLSingleMiddleLeftycl_Eff;1",hCTLSingleMiddleLeftycl_Eff);
        tmpCTLBottomLeftxcl_EFF[i] = (1-hCTLBottomLeftxcl_Eff->GetBinContent(1)/hCTLBottomLeftxcl_Eff->GetEntries());
        tmpCTLBottomLeftycl_EFF[i] = (1-hCTLBottomLeftycl_Eff->GetBinContent(1)/hCTLBottomLeftycl_Eff->GetEntries());
         tmpCTLTopMiddlexcl_EFF[i] = (1-hCTLTopMiddlexcl_Eff->GetBinContent(1)/hCTLTopMiddlexcl_Eff->GetEntries());
        tmpCTLMiddleLeftycl_EFF[i] = (1-hCTLMiddleLeftycl_Eff->GetBinContent(1)/hCTLMiddleLeftycl_Eff->GetEntries());
  tmpCTLSingleMiddleLeftycl_EFF[i] = (1-hCTLSingleMiddleLeftycl_Eff->GetBinContent(1)/hCTLSingleMiddleLeftycl_Eff->GetEntries());

        tmpCTLBottomLeftxcl_EFFSTERR[i] = TMath::Sqrt(tmpCTLBottomLeftxcl_EFF[i]*(1-tmpCTLBottomLeftxcl_EFF[i])/hCTLBottomLeftxcl_Eff->GetEntries());
        tmpCTLBottomLeftycl_EFFSTERR[i] = TMath::Sqrt(tmpCTLBottomLeftycl_EFF[i]*(1-tmpCTLBottomLeftycl_EFF[i])/hCTLBottomLeftycl_Eff->GetEntries());  		
         tmpCTLTopMiddlexcl_EFFSTERR[i] = TMath::Sqrt(tmpCTLTopMiddlexcl_EFF[i]*(1-tmpCTLTopMiddlexcl_EFF[i])/hCTLTopMiddlexcl_Eff->GetEntries());    		
        tmpCTLMiddleLeftycl_EFFSTERR[i] = TMath::Sqrt(tmpCTLMiddleLeftycl_EFF[i]*(1-tmpCTLMiddleLeftycl_EFF[i])/hCTLMiddleLeftycl_Eff->GetEntries());  		
  tmpCTLSingleMiddleLeftycl_EFFSTERR[i] = TMath::Sqrt(tmpCTLSingleMiddleLeftycl_EFF[i]*(1-tmpCTLSingleMiddleLeftycl_EFF[i])/hCTLSingleMiddleLeftycl_Eff->GetEntries());

  file->Close();
  delete file;
  }
  cout << "Data Read" << endl;

  for (Int_t j=0; j<NumberOfPoints; j++)
  {
	Int_t MaxIndexCTLBottomLeftxcl 		= j*NumberOfFilesPerPoint;
	Int_t MaxIndexCTLBottomLeftycl 		= j*NumberOfFilesPerPoint;
	Int_t MaxIndexCTLTopMiddlexcl 		= j*NumberOfFilesPerPoint;
	Int_t MaxIndexCTLMiddleLeftycl 		= j*NumberOfFilesPerPoint;
	Int_t MaxIndexCTLSingleMiddleLeftycl 	= j*NumberOfFilesPerPoint;

	for (Int_t i=j*NumberOfFilesPerPoint; i<(j+1)*NumberOfFilesPerPoint; i++)
	{
		if (tmpCTLBottomLeftxcl_EFF[i] > tmpCTLBottomLeftxcl_EFF[MaxIndexCTLBottomLeftxcl]) 			MaxIndexCTLBottomLeftxcl 	= i;
		if (tmpCTLBottomLeftycl_EFF[i] > tmpCTLBottomLeftycl_EFF[MaxIndexCTLBottomLeftycl])			MaxIndexCTLBottomLeftycl 	= i;
		if (tmpCTLTopMiddlexcl_EFF[i]  > tmpCTLTopMiddlexcl_EFF[MaxIndexCTLTopMiddlexcl]) 			MaxIndexCTLTopMiddlexcl		= i;
		if (tmpCTLMiddleLeftycl_EFF[i] >tmpCTLMiddleLeftycl_EFF[MaxIndexCTLMiddleLeftycl]) 			MaxIndexCTLMiddleLeftycl 	= i;
		if (tmpCTLSingleMiddleLeftycl_EFF[i]>tmpCTLSingleMiddleLeftycl_EFF[MaxIndexCTLSingleMiddleLeftycl]) 	MaxIndexCTLSingleMiddleLeftycl 	= i;
	}

        CTLBottomLeftxcl_EFF[j] 		=       tmpCTLBottomLeftxcl_EFF[MaxIndexCTLBottomLeftxcl 		]; 		
        CTLBottomLeftycl_EFF[j] 		=       tmpCTLBottomLeftycl_EFF[MaxIndexCTLBottomLeftycl 		]; 		
        CTLTopMiddlexcl_EFF[j] 			=        tmpCTLTopMiddlexcl_EFF[MaxIndexCTLTopMiddlexcl 		]; 		
        CTLMiddleLeftycl_EFF[j] 		=       tmpCTLMiddleLeftycl_EFF[MaxIndexCTLMiddleLeftycl 		]; 		
  	CTLSingleMiddleLeftycl_EFF[j] 		= tmpCTLSingleMiddleLeftycl_EFF[MaxIndexCTLSingleMiddleLeftycl 		]; 	

        CTLBottomLeftxcl_EFFSTERR[j] 		=       tmpCTLBottomLeftxcl_EFFSTERR[MaxIndexCTLBottomLeftxcl 		]; 		
        CTLBottomLeftycl_EFFSTERR[j] 		=       tmpCTLBottomLeftycl_EFFSTERR[MaxIndexCTLBottomLeftycl 		]; 		
        CTLTopMiddlexcl_EFFSTERR[j] 		=        tmpCTLTopMiddlexcl_EFFSTERR[MaxIndexCTLTopMiddlexcl 		]; 		
        CTLMiddleLeftycl_EFFSTERR[j] 		=       tmpCTLMiddleLeftycl_EFFSTERR[MaxIndexCTLMiddleLeftycl 		]; 		
  	CTLSingleMiddleLeftycl_EFFSTERR[j] 	= tmpCTLSingleMiddleLeftycl_EFFSTERR[MaxIndexCTLSingleMiddleLeftycl 	]; 	

        cout << "\nPoint["<<j<<"]:	MaxIndexCTLBottomLeftxcl = " 		<< MaxIndexCTLBottomLeftxcl 		<< endl;	
        cout << "Point["<<j<<"]:	MaxIndexCTLBottomLeftycl = " 		<< MaxIndexCTLBottomLeftycl 		<< endl;
        cout << "Point["<<j<<"]:	MaxIndexCTLTopMiddlexcl  = "		<< MaxIndexCTLTopMiddlexcl		<< endl;
        cout << "Point["<<j<<"]:	MaxIndexCTLMiddleLeftycl = " 		<< MaxIndexCTLMiddleLeftycl 		<< endl;
  	cout << "Point["<<j<<"]:	MaxIndexCTLSingleMiddleLeftycl = " 	<< MaxIndexCTLSingleMiddleLeftycl	<< "\n" << endl; 	
  }


  TFile *CTLEFFFile = new TFile("CTL-EFF.root", "RECREATE");

  TCanvas *cCTLBottomLeftxcl_EFF 	= new TCanvas("cCTLBottomLeftx","CTLBottomLeftx",500,400); 
  TGraphErrors *CTLBottomLeftxcl 	= new TGraphErrors(NumberOfPoints,(const Float_t*)ICTL,(const Float_t*)CTLBottomLeftxcl_EFF,(const Float_t*)0.,(const Float_t*)CTLBottomLeftxcl_EFFSTERR);
  CTLBottomLeftxcl->SetTitle("CTLBottomLeftxcl");
  CTLBottomLeftxcl->SetName("CTLBottomLeftxcl");
  CTLBottomLeftxcl->SetLineColor(2);
  CTLBottomLeftxcl->SetLineStyle(2);
  CTLBottomLeftxcl->SetLineWidth(2);
  CTLBottomLeftxcl->SetMarkerColor(2);
  CTLBottomLeftxcl->SetMarkerStyle(21);
  CTLBottomLeftxcl->GetYaxis()->SetRangeUser(0,1);
  cCTLBottomLeftxcl_EFF->cd();   
  CTLBottomLeftxcl->Draw("APL");    

  TCanvas *cCTLBottomLefty_EFF 		= new TCanvas("cCTLBottomLefty","CTLBottomLefty",500,400); 
  TGraphErrors *CTLBottomLeftycl 	= new TGraphErrors(NumberOfPoints,(const Float_t*)ICTL,(const Float_t*)CTLBottomLeftycl_EFF,(const Float_t*)0.,(const Float_t*)CTLBottomLeftycl_EFFSTERR);
  CTLBottomLeftycl->SetTitle("CTLBottomLeftycl");
  CTLBottomLeftycl->SetName("CTLBottomLeftycl");
  CTLBottomLeftycl->SetLineColor(38);
  CTLBottomLeftycl->SetLineStyle(5);
  CTLBottomLeftycl->SetLineWidth(2);
  CTLBottomLeftycl->SetMarkerColor(38);
  CTLBottomLeftycl->SetMarkerStyle(23);
  CTLBottomLeftycl->SetMarkerSize(1.3);
  CTLBottomLeftycl->GetYaxis()->SetRangeUser(0,1);
  cCTLBottomLefty_EFF->cd(); 	    
  CTLBottomLeftycl->Draw("APL");    

  TCanvas *cCTLTopMiddlex_EFF 		= new TCanvas("cCTLTopMiddlex","CTLTopMiddlex",500,400); 
  TGraphErrors *CTLTopMiddlexcl 	= new TGraphErrors(NumberOfPoints,(const Float_t*)ICTL,(const Float_t*)CTLTopMiddlexcl_EFF,(const Float_t*)0.,(const Float_t*)CTLTopMiddlexcl_EFFSTERR);
  CTLTopMiddlexcl->SetTitle("CTLTopMiddlexcl");
  CTLTopMiddlexcl->SetName("CTLTopMiddlexcl");
  CTLTopMiddlexcl->SetLineColor(30);
  CTLTopMiddlexcl->SetLineStyle(9);
  CTLTopMiddlexcl->SetLineWidth(2);
  CTLTopMiddlexcl->SetMarkerColor(30);
  CTLTopMiddlexcl->SetMarkerStyle(5);
  CTLTopMiddlexcl->SetMarkerSize(1.4);
  CTLTopMiddlexcl->GetYaxis()->SetRangeUser(0,1);
  cCTLTopMiddlex_EFF->cd(); 	    
  CTLTopMiddlexcl->Draw("APL");    

  TCanvas *cCTLMiddleLefty_EFF 		= new TCanvas("cCTLMiddleLefty","CTLMiddleLefty",500,400); 
  TGraphErrors *CTLMiddleLeftycl 	= new TGraphErrors(NumberOfPoints,(const Float_t*)ICTL,(const Float_t*)CTLMiddleLeftycl_EFF,(const Float_t*)0.,(const Float_t*)CTLMiddleLeftycl_EFFSTERR);
  CTLMiddleLeftycl->SetTitle("CTLMiddleLeftycl");
  CTLMiddleLeftycl->SetName("CTLMiddleLeftycl");
  CTLMiddleLeftycl->SetLineWidth(2);
  CTLMiddleLeftycl->SetMarkerStyle(4);
  CTLMiddleLeftycl->GetYaxis()->SetRangeUser(0,1);
  cCTLMiddleLefty_EFF->cd(); 	      
  CTLMiddleLeftycl->Draw("APL");    

  TCanvas *cCTLSingleMiddleLefty_EFF 	= new TCanvas("cCTLSingleMiddleLefty","CTLSingleMiddleLefty",500,400);
  TGraphErrors *CTLSingleMiddleLeftycl 	= new TGraphErrors(NumberOfPoints,(const Float_t*)ICTL,(const Float_t*)CTLSingleMiddleLeftycl_EFF,(const Float_t*)0.,(const Float_t*)CTLSingleMiddleLeftycl_EFFSTERR);
  CTLSingleMiddleLeftycl->SetTitle("CTLSingleMiddleLeftycl");
  CTLSingleMiddleLeftycl->SetName("CTLSingleMiddleLeftycl");
  CTLSingleMiddleLeftycl->SetLineColor(797);
  CTLSingleMiddleLeftycl->SetLineStyle(1);
  CTLSingleMiddleLeftycl->SetLineWidth(1);
  CTLSingleMiddleLeftycl->SetMarkerColor(797);
  CTLSingleMiddleLeftycl->SetMarkerSize(1.);
  CTLSingleMiddleLeftycl->SetMarkerStyle(7);
  CTLSingleMiddleLeftycl->GetYaxis()->SetRangeUser(0,1);
  cCTLSingleMiddleLefty_EFF->cd();
  CTLSingleMiddleLeftycl->Draw("APL");    

  cCTLBottomLeftxcl_EFF->Write();    
  cCTLBottomLefty_EFF->Write(); 	    
  cCTLTopMiddlex_EFF->Write(); 	    
  cCTLMiddleLefty_EFF->Write(); 	      
  cCTLSingleMiddleLefty_EFF->Write();

  CTLBottomLeftxcl->Write();    
  CTLBottomLeftycl->Write();    
  CTLTopMiddlexcl->Write();    
  CTLMiddleLeftycl->Write();    
  CTLSingleMiddleLeftycl->Write();    

  TCanvas *cCTLEFF 	= new TCanvas("cCTLEFF","CTLEFF",500,400); 
  cCTLEFF->cd();
  cCTLEFF->SetGridx(1);
  cCTLEFF->SetGridy(1);
  CTLBottomLeftxcl->SetTitle("CTL: High Voltage Efficiency Scan");    
  CTLBottomLeftxcl->Draw("APL");    
  CTLBottomLeftycl->Draw("SAME");    
  CTLTopMiddlexcl->Draw("SAME");    
  CTLMiddleLeftycl->Draw("SAME");    
  CTLSingleMiddleLeftycl->Draw("SAME");    
  cCTLEFF->Write();

  CTLEFFFile->Write();
  //CTLEFFFile->Close();
  //delete CTLEFFFile;
}
