#include "TFile.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
void CLS(){
  gROOT->Reset();
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(1002210);
  gStyle->SetOptDate();

  float ZCTL = 4.89;
  float *ICTL;
  TString *filename;

  ICTL = new float[14];
  filename = new TString[14];

  float       *CTLBottomLeftxcl_CLSMEAN;
  float       *CTLBottomLeftxcl_CLS_RMS;
  float       *CTLBottomLeftycl_CLSMEAN;
  float       *CTLBottomLeftycl_CLS_RMS;
  float        *CTLTopMiddlexcl_CLSMEAN;
  float        *CTLTopMiddlexcl_CLS_RMS;
  float       *CTLMiddleLeftycl_CLSMEAN;
  float       *CTLMiddleLeftycl_CLS_RMS;
  float *CTLSingleMiddleLeftycl_CLSMEAN;
  float *CTLSingleMiddleLeftycl_CLS_RMS;

        CTLBottomLeftxcl_CLSMEAN = new float[14];
        CTLBottomLeftxcl_CLS_RMS = new float[14];
        CTLBottomLeftycl_CLSMEAN = new float[14];
        CTLBottomLeftycl_CLS_RMS = new float[14];
         CTLTopMiddlexcl_CLSMEAN = new float[14];
         CTLTopMiddlexcl_CLS_RMS = new float[14];
        CTLMiddleLeftycl_CLSMEAN = new float[14];
        CTLMiddleLeftycl_CLS_RMS = new float[14];
  CTLSingleMiddleLeftycl_CLSMEAN = new float[14];
  CTLSingleMiddleLeftycl_CLS_RMS = new float[14];


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
  ICTL[1]  = 3100/ZCTL;
  ICTL[2]  = 3200/ZCTL;
  ICTL[3]  = 3200/ZCTL;
  ICTL[4]  = 3300/ZCTL;
  ICTL[5]  = 3300/ZCTL;
  ICTL[6]  = 3400/ZCTL;
  ICTL[7]  = 3400/ZCTL;
  ICTL[8]  = 3450/ZCTL;
  ICTL[9]  = 3450/ZCTL;
  ICTL[10] = 3500/ZCTL;
  ICTL[11] = 3500/ZCTL;
  ICTL[12] = 3550/ZCTL;
  ICTL[13] = 3550/ZCTL;


  for (Int_t i=0; i<14; i++)
  {
  TFile *file = new TFile(filename[i]);
  TH1F *hCTLBottomLeftxcl_CLS_Eff; 		
  TH1F *hCTLBottomLeftycl_CLS_Eff; 		
  TH1F *hCTLTopMiddlexcl_CLS_Eff; 		
  TH1F *hCTLMiddleLeftycl_CLS_Eff; 		
  TH1F *hCTLSingleMiddleLeftycl_CLS_Eff; 	

  gDirectory->GetObject("hgCTLBottomLeftxcl_CLS_Eff;1",hCTLBottomLeftxcl_CLS_Eff);
  gDirectory->GetObject("hgCTLBottomLeftycl_CLS_Eff;1",hCTLBottomLeftycl_CLS_Eff);
  gDirectory->GetObject("hgCTLTopMiddlexcl_CLS_Eff;1",hCTLTopMiddlexcl_CLS_Eff);
  gDirectory->GetObject("hgCTLMiddleLeftycl_CLS_Eff;1",hCTLMiddleLeftycl_CLS_Eff);
  gDirectory->GetObject("hgCTLSingleMiddleLeftycl_CLS_Eff;1",hCTLSingleMiddleLeftycl_CLS_Eff);
        CTLBottomLeftxcl_CLSMEAN[i]    	= hCTLBottomLeftxcl_CLS_Eff->GetMean();
        CTLBottomLeftxcl_CLS_RMS[i]    	= hCTLBottomLeftxcl_CLS_Eff->GetRMS();
        CTLBottomLeftycl_CLSMEAN[i]    	= hCTLBottomLeftycl_CLS_Eff->GetMean();
        CTLBottomLeftycl_CLS_RMS[i]    	= hCTLBottomLeftycl_CLS_Eff->GetRMS();
         CTLTopMiddlexcl_CLSMEAN[i]    	= hCTLTopMiddlexcl_CLS_Eff->GetMean();
         CTLTopMiddlexcl_CLS_RMS[i]    	= hCTLTopMiddlexcl_CLS_Eff->GetRMS();
        CTLMiddleLeftycl_CLSMEAN[i]    	= hCTLMiddleLeftycl_CLS_Eff->GetMean();
        CTLMiddleLeftycl_CLS_RMS[i]    	= hCTLMiddleLeftycl_CLS_Eff->GetRMS();
  CTLSingleMiddleLeftycl_CLSMEAN[i]    	= hCTLSingleMiddleLeftycl_CLS_Eff->GetMean();
  CTLSingleMiddleLeftycl_CLS_RMS[i]    	= hCTLSingleMiddleLeftycl_CLS_Eff->GetRMS();

  //delete hCTLBottomLeftxcl_CLS_Eff; 		
  //delete hCTLBottomLeftycl_CLS_Eff; 		
  //delete hCTLTopMiddlexcl_CLS_Eff; 		
  //delete hCTLMiddleLeftycl_CLS_Eff; 		
  //delete hCTLSingleMiddleLeftycl_CLS_Eff; 	
  file->Close();
  delete file;



  }

  TFile *CTLCLSFile = new TFile("CTL-CLS.root", "RECREATE");

  TCanvas *cCTLBottomLeftxcl_CLS 	= new TCanvas("cCTLBottomLeftx","CTLBottomLeftx",500,400); 
  TGraphErrors *CTLBottomLeftxcl 	= new TGraphErrors(14,(const Float_t*)ICTL,(const Float_t*)CTLBottomLeftxcl_CLSMEAN,(const Float_t*)0.,(const Float_t*)CTLBottomLeftxcl_CLS_RMS);
  CTLBottomLeftxcl->SetTitle("CTLBottomLeftxcl");
  CTLBottomLeftxcl->SetName("CTLBottomLeftxcl");
  CTLBottomLeftxcl->SetMarkerStyle(25);
  CTLBottomLeftxcl->GetYaxis()->SetRangeUser(0,5);
  cCTLBottomLeftxcl_CLS->cd();   
  CTLBottomLeftxcl->Draw("AP");    

  TCanvas *cCTLBottomLefty_CLS 		= new TCanvas("cCTLBottomLefty","CTLBottomLefty",500,400); 
  TGraphErrors *CTLBottomLeftycl 	= new TGraphErrors(14,(const Float_t*)ICTL,(const Float_t*)CTLBottomLeftycl_CLSMEAN,(const Float_t*)0.,(const Float_t*)CTLBottomLeftycl_CLS_RMS);
  CTLBottomLeftycl->SetTitle("CTLBottomLeftycl");
  CTLBottomLeftycl->SetName("CTLBottomLeftycl");
  CTLBottomLeftycl->SetMarkerStyle(25);
  CTLBottomLeftycl->GetYaxis()->SetRangeUser(0,5);
  cCTLBottomLefty_CLS->cd(); 	    
  CTLBottomLeftycl->Draw("AP");    

  TCanvas *cCTLTopMiddlex_CLS 		= new TCanvas("cCTLTopMiddlex","CTLTopMiddlex",500,400); 
  TGraphErrors *CTLTopMiddlexcl 	= new TGraphErrors(14,(const Float_t*)ICTL,(const Float_t*)CTLTopMiddlexcl_CLSMEAN,(const Float_t*)0.,(const Float_t*)CTLTopMiddlexcl_CLS_RMS);
  CTLTopMiddlexcl->SetTitle("CTLTopMiddlexcl");
  CTLTopMiddlexcl->SetName("CTLTopMiddlexcl");
  CTLTopMiddlexcl->SetMarkerStyle(25);
  CTLTopMiddlexcl->GetYaxis()->SetRangeUser(0,5);
  cCTLTopMiddlex_CLS->cd(); 	    
  CTLTopMiddlexcl->Draw("AP");    

  TCanvas *cCTLMiddleLefty_CLS 		= new TCanvas("cCTLMiddleLefty","CTLMiddleLefty",500,400); 
  TGraphErrors *CTLMiddleLeftycl 	= new TGraphErrors(14,(const Float_t*)ICTL,(const Float_t*)CTLMiddleLeftycl_CLSMEAN,(const Float_t*)0.,(const Float_t*)CTLMiddleLeftycl_CLS_RMS);
  CTLMiddleLeftycl->SetTitle("CTLMiddleLeftycl");
  CTLMiddleLeftycl->SetName("CTLMiddleLeftycl");
  CTLMiddleLeftycl->SetMarkerStyle(25);
  CTLMiddleLeftycl->GetYaxis()->SetRangeUser(0,5);
  cCTLMiddleLefty_CLS->cd(); 	      
  CTLMiddleLeftycl->Draw("AP");    

  TCanvas *cCTLSingleMiddleLefty_CLS 	= new TCanvas("cCTLSingleMiddleLefty","CTLSingleMiddleLefty",500,400);
  TGraphErrors *CTLSingleMiddleLeftycl 	= new TGraphErrors(14,(const Float_t*)ICTL,(const Float_t*)CTLSingleMiddleLeftycl_CLSMEAN,(const Float_t*)0.,(const Float_t*)CTLSingleMiddleLeftycl_CLS_RMS);
  CTLSingleMiddleLeftycl->SetTitle("CTLSingleMiddleLeftycl");
  CTLSingleMiddleLeftycl->SetName("CTLSingleMiddleLeftycl");
  CTLSingleMiddleLeftycl->SetMarkerStyle(25);
  CTLSingleMiddleLeftycl->GetYaxis()->SetRangeUser(0,5);
  cCTLSingleMiddleLefty_CLS->cd();
  CTLSingleMiddleLeftycl->Draw("AP");    

  cCTLBottomLeftxcl_CLS->Write();    
  cCTLBottomLefty_CLS->Write(); 	    
  cCTLTopMiddlex_CLS->Write(); 	    
  cCTLMiddleLefty_CLS->Write(); 	      
  cCTLSingleMiddleLefty_CLS->Write();

  CTLBottomLeftxcl->Write();    
  CTLBottomLeftycl->Write();    
  CTLTopMiddlexcl->Write();    
  CTLMiddleLeftycl->Write();    
  CTLSingleMiddleLeftycl->Write();    

  CTLCLSFile->Write();
  //CTLCLSFile->Close();
  //delete CTLCLSFile;
}
