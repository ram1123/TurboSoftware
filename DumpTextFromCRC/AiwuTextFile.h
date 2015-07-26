//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Jul 25 19:58:13 2015 by ROOT version 6.04/00
// from TTree rd51tbgeo/RD51 test beam geometry
// found on file: CRC-Run0411_Muon_10k_MSPL2_HVScan_710pt1_710pt1_710pt0_T20_T20_T20_Lat22-141011_013955-0.root
//////////////////////////////////////////////////////////

#ifndef AiwuTextFile_h
#define AiwuTextFile_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "TClonesArray.h"

class AiwuTextFile {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.
   static const Int_t kMaxg1xcl = 12;
   static const Int_t kMaxg1ycl = 12;
   static const Int_t kMaxg2xcl = 15;
   static const Int_t kMaxg2ycl = 10;
   static const Int_t kMaxg3xcl = 9;
   static const Int_t kMaxg3ycl = 9;
   static const Int_t kMaxsCMSNS2LC1 = 9;
   static const Int_t kMaxsCMSNS2LC2 = 9;
   static const Int_t kMaxsCMSNS2LC2_R = 8;
   static const Int_t kMaxsCMSNS2LC2_L = 4;
   static const Int_t kMaxsCMSNS2LC3 = 13;

   // Declaration of leaf types
   Int_t           EventInfo_EventNumber;
   Int_t           EventInfo_TriggerNumber;
   Int_t           EventInfo_TimeStamp;
   Int_t           EventInfo_BunchCounter;
   Int_t           EventInfo_EventCounter;
   Int_t           g1xcl_;
   Int_t           g1xcl_ngeoch[kMaxg1xcl];   //[g1xcl_]
   Int_t          *g1xcl_geoch[kMaxg1xcl];   //[g1xcl_ngeoch]
   Float_t        *g1xcl_geoX[kMaxg1xcl];   //[g1xcl_ngeoch]
   Float_t        *g1xcl_geoY[kMaxg1xcl];   //[g1xcl_ngeoch]
   Float_t        *g1xcl_geoZ[kMaxg1xcl];   //[g1xcl_ngeoch]
   Float_t        *g1xcl_geoR[kMaxg1xcl];   //[g1xcl_ngeoch]
   Float_t        *g1xcl_geoPhi[kMaxg1xcl];   //[g1xcl_ngeoch]
   Float_t         g1xcl_geoposch[kMaxg1xcl];   //[g1xcl_]
   Float_t         g1xcl_geoposX[kMaxg1xcl];   //[g1xcl_]
   Float_t         g1xcl_geoposY[kMaxg1xcl];   //[g1xcl_]
   Float_t         g1xcl_geoposZ[kMaxg1xcl];   //[g1xcl_]
   Float_t         g1xcl_geoposR[kMaxg1xcl];   //[g1xcl_]
   Float_t         g1xcl_geoposPhi[kMaxg1xcl];   //[g1xcl_]
   Int_t           g1ycl_;
   Int_t           g1ycl_ngeoch[kMaxg1ycl];   //[g1ycl_]
   Int_t          *g1ycl_geoch[kMaxg1ycl];   //[g1ycl_ngeoch]
   Float_t        *g1ycl_geoX[kMaxg1ycl];   //[g1ycl_ngeoch]
   Float_t        *g1ycl_geoY[kMaxg1ycl];   //[g1ycl_ngeoch]
   Float_t        *g1ycl_geoZ[kMaxg1ycl];   //[g1ycl_ngeoch]
   Float_t        *g1ycl_geoR[kMaxg1ycl];   //[g1ycl_ngeoch]
   Float_t        *g1ycl_geoPhi[kMaxg1ycl];   //[g1ycl_ngeoch]
   Float_t         g1ycl_geoposch[kMaxg1ycl];   //[g1ycl_]
   Float_t         g1ycl_geoposX[kMaxg1ycl];   //[g1ycl_]
   Float_t         g1ycl_geoposY[kMaxg1ycl];   //[g1ycl_]
   Float_t         g1ycl_geoposZ[kMaxg1ycl];   //[g1ycl_]
   Float_t         g1ycl_geoposR[kMaxg1ycl];   //[g1ycl_]
   Float_t         g1ycl_geoposPhi[kMaxg1ycl];   //[g1ycl_]
   Int_t           g2xcl_;
   Int_t           g2xcl_ngeoch[kMaxg2xcl];   //[g2xcl_]
   Int_t          *g2xcl_geoch[kMaxg2xcl];   //[g2xcl_ngeoch]
   Float_t        *g2xcl_geoX[kMaxg2xcl];   //[g2xcl_ngeoch]
   Float_t        *g2xcl_geoY[kMaxg2xcl];   //[g2xcl_ngeoch]
   Float_t        *g2xcl_geoZ[kMaxg2xcl];   //[g2xcl_ngeoch]
   Float_t        *g2xcl_geoR[kMaxg2xcl];   //[g2xcl_ngeoch]
   Float_t        *g2xcl_geoPhi[kMaxg2xcl];   //[g2xcl_ngeoch]
   Float_t         g2xcl_geoposch[kMaxg2xcl];   //[g2xcl_]
   Float_t         g2xcl_geoposX[kMaxg2xcl];   //[g2xcl_]
   Float_t         g2xcl_geoposY[kMaxg2xcl];   //[g2xcl_]
   Float_t         g2xcl_geoposZ[kMaxg2xcl];   //[g2xcl_]
   Float_t         g2xcl_geoposR[kMaxg2xcl];   //[g2xcl_]
   Float_t         g2xcl_geoposPhi[kMaxg2xcl];   //[g2xcl_]
   Int_t           g2ycl_;
   Int_t           g2ycl_ngeoch[kMaxg2ycl];   //[g2ycl_]
   Int_t          *g2ycl_geoch[kMaxg2ycl];   //[g2ycl_ngeoch]
   Float_t        *g2ycl_geoX[kMaxg2ycl];   //[g2ycl_ngeoch]
   Float_t        *g2ycl_geoY[kMaxg2ycl];   //[g2ycl_ngeoch]
   Float_t        *g2ycl_geoZ[kMaxg2ycl];   //[g2ycl_ngeoch]
   Float_t        *g2ycl_geoR[kMaxg2ycl];   //[g2ycl_ngeoch]
   Float_t        *g2ycl_geoPhi[kMaxg2ycl];   //[g2ycl_ngeoch]
   Float_t         g2ycl_geoposch[kMaxg2ycl];   //[g2ycl_]
   Float_t         g2ycl_geoposX[kMaxg2ycl];   //[g2ycl_]
   Float_t         g2ycl_geoposY[kMaxg2ycl];   //[g2ycl_]
   Float_t         g2ycl_geoposZ[kMaxg2ycl];   //[g2ycl_]
   Float_t         g2ycl_geoposR[kMaxg2ycl];   //[g2ycl_]
   Float_t         g2ycl_geoposPhi[kMaxg2ycl];   //[g2ycl_]
   Int_t           g3xcl_;
   Int_t           g3xcl_ngeoch[kMaxg3xcl];   //[g3xcl_]
   Int_t          *g3xcl_geoch[kMaxg3xcl];   //[g3xcl_ngeoch]
   Float_t        *g3xcl_geoX[kMaxg3xcl];   //[g3xcl_ngeoch]
   Float_t        *g3xcl_geoY[kMaxg3xcl];   //[g3xcl_ngeoch]
   Float_t        *g3xcl_geoZ[kMaxg3xcl];   //[g3xcl_ngeoch]
   Float_t        *g3xcl_geoR[kMaxg3xcl];   //[g3xcl_ngeoch]
   Float_t        *g3xcl_geoPhi[kMaxg3xcl];   //[g3xcl_ngeoch]
   Float_t         g3xcl_geoposch[kMaxg3xcl];   //[g3xcl_]
   Float_t         g3xcl_geoposX[kMaxg3xcl];   //[g3xcl_]
   Float_t         g3xcl_geoposY[kMaxg3xcl];   //[g3xcl_]
   Float_t         g3xcl_geoposZ[kMaxg3xcl];   //[g3xcl_]
   Float_t         g3xcl_geoposR[kMaxg3xcl];   //[g3xcl_]
   Float_t         g3xcl_geoposPhi[kMaxg3xcl];   //[g3xcl_]
   Int_t           g3ycl_;
   Int_t           g3ycl_ngeoch[kMaxg3ycl];   //[g3ycl_]
   Int_t          *g3ycl_geoch[kMaxg3ycl];   //[g3ycl_ngeoch]
   Float_t        *g3ycl_geoX[kMaxg3ycl];   //[g3ycl_ngeoch]
   Float_t        *g3ycl_geoY[kMaxg3ycl];   //[g3ycl_ngeoch]
   Float_t        *g3ycl_geoZ[kMaxg3ycl];   //[g3ycl_ngeoch]
   Float_t        *g3ycl_geoR[kMaxg3ycl];   //[g3ycl_ngeoch]
   Float_t        *g3ycl_geoPhi[kMaxg3ycl];   //[g3ycl_ngeoch]
   Float_t         g3ycl_geoposch[kMaxg3ycl];   //[g3ycl_]
   Float_t         g3ycl_geoposX[kMaxg3ycl];   //[g3ycl_]
   Float_t         g3ycl_geoposY[kMaxg3ycl];   //[g3ycl_]
   Float_t         g3ycl_geoposZ[kMaxg3ycl];   //[g3ycl_]
   Float_t         g3ycl_geoposR[kMaxg3ycl];   //[g3ycl_]
   Float_t         g3ycl_geoposPhi[kMaxg3ycl];   //[g3ycl_]
   Int_t           sCMSNS2LC1_;
   Int_t           sCMSNS2LC1_ngeoch[kMaxsCMSNS2LC1];   //[sCMSNS2LC1_]
   Int_t          *sCMSNS2LC1_geoch[kMaxsCMSNS2LC1];   //[sCMSNS2LC1_ngeoch]
   Float_t        *sCMSNS2LC1_geoX[kMaxsCMSNS2LC1];   //[sCMSNS2LC1_ngeoch]
   Float_t        *sCMSNS2LC1_geoY[kMaxsCMSNS2LC1];   //[sCMSNS2LC1_ngeoch]
   Float_t        *sCMSNS2LC1_geoZ[kMaxsCMSNS2LC1];   //[sCMSNS2LC1_ngeoch]
   Float_t        *sCMSNS2LC1_geoR[kMaxsCMSNS2LC1];   //[sCMSNS2LC1_ngeoch]
   Float_t        *sCMSNS2LC1_geoPhi[kMaxsCMSNS2LC1];   //[sCMSNS2LC1_ngeoch]
   Float_t         sCMSNS2LC1_geoposch[kMaxsCMSNS2LC1];   //[sCMSNS2LC1_]
   Float_t         sCMSNS2LC1_geoposX[kMaxsCMSNS2LC1];   //[sCMSNS2LC1_]
   Float_t         sCMSNS2LC1_geoposY[kMaxsCMSNS2LC1];   //[sCMSNS2LC1_]
   Float_t         sCMSNS2LC1_geoposZ[kMaxsCMSNS2LC1];   //[sCMSNS2LC1_]
   Float_t         sCMSNS2LC1_geoposR[kMaxsCMSNS2LC1];   //[sCMSNS2LC1_]
   Float_t         sCMSNS2LC1_geoposPhi[kMaxsCMSNS2LC1];   //[sCMSNS2LC1_]
   Int_t           sCMSNS2LC2_;
   Int_t           sCMSNS2LC2_ngeoch[kMaxsCMSNS2LC2];   //[sCMSNS2LC2_]
   Int_t          *sCMSNS2LC2_geoch[kMaxsCMSNS2LC2];   //[sCMSNS2LC2_ngeoch]
   Float_t        *sCMSNS2LC2_geoX[kMaxsCMSNS2LC2];   //[sCMSNS2LC2_ngeoch]
   Float_t        *sCMSNS2LC2_geoY[kMaxsCMSNS2LC2];   //[sCMSNS2LC2_ngeoch]
   Float_t        *sCMSNS2LC2_geoZ[kMaxsCMSNS2LC2];   //[sCMSNS2LC2_ngeoch]
   Float_t        *sCMSNS2LC2_geoR[kMaxsCMSNS2LC2];   //[sCMSNS2LC2_ngeoch]
   Float_t        *sCMSNS2LC2_geoPhi[kMaxsCMSNS2LC2];   //[sCMSNS2LC2_ngeoch]
   Float_t         sCMSNS2LC2_geoposch[kMaxsCMSNS2LC2];   //[sCMSNS2LC2_]
   Float_t         sCMSNS2LC2_geoposX[kMaxsCMSNS2LC2];   //[sCMSNS2LC2_]
   Float_t         sCMSNS2LC2_geoposY[kMaxsCMSNS2LC2];   //[sCMSNS2LC2_]
   Float_t         sCMSNS2LC2_geoposZ[kMaxsCMSNS2LC2];   //[sCMSNS2LC2_]
   Float_t         sCMSNS2LC2_geoposR[kMaxsCMSNS2LC2];   //[sCMSNS2LC2_]
   Float_t         sCMSNS2LC2_geoposPhi[kMaxsCMSNS2LC2];   //[sCMSNS2LC2_]
   Int_t           sCMSNS2LC2_R_;
   Int_t           sCMSNS2LC2_R_ngeoch[kMaxsCMSNS2LC2_R];   //[sCMSNS2LC2_R_]
   Int_t          *sCMSNS2LC2_R_geoch[kMaxsCMSNS2LC2_R];   //[sCMSNS2LC2_R_ngeoch]
   Float_t        *sCMSNS2LC2_R_geoX[kMaxsCMSNS2LC2_R];   //[sCMSNS2LC2_R_ngeoch]
   Float_t        *sCMSNS2LC2_R_geoY[kMaxsCMSNS2LC2_R];   //[sCMSNS2LC2_R_ngeoch]
   Float_t        *sCMSNS2LC2_R_geoZ[kMaxsCMSNS2LC2_R];   //[sCMSNS2LC2_R_ngeoch]
   Float_t        *sCMSNS2LC2_R_geoR[kMaxsCMSNS2LC2_R];   //[sCMSNS2LC2_R_ngeoch]
   Float_t        *sCMSNS2LC2_R_geoPhi[kMaxsCMSNS2LC2_R];   //[sCMSNS2LC2_R_ngeoch]
   Float_t         sCMSNS2LC2_R_geoposch[kMaxsCMSNS2LC2_R];   //[sCMSNS2LC2_R_]
   Float_t         sCMSNS2LC2_R_geoposX[kMaxsCMSNS2LC2_R];   //[sCMSNS2LC2_R_]
   Float_t         sCMSNS2LC2_R_geoposY[kMaxsCMSNS2LC2_R];   //[sCMSNS2LC2_R_]
   Float_t         sCMSNS2LC2_R_geoposZ[kMaxsCMSNS2LC2_R];   //[sCMSNS2LC2_R_]
   Float_t         sCMSNS2LC2_R_geoposR[kMaxsCMSNS2LC2_R];   //[sCMSNS2LC2_R_]
   Float_t         sCMSNS2LC2_R_geoposPhi[kMaxsCMSNS2LC2_R];   //[sCMSNS2LC2_R_]
   Int_t           sCMSNS2LC2_L_;
   Int_t           sCMSNS2LC2_L_ngeoch[kMaxsCMSNS2LC2_L];   //[sCMSNS2LC2_L_]
   Int_t          *sCMSNS2LC2_L_geoch[kMaxsCMSNS2LC2_L];   //[sCMSNS2LC2_L_ngeoch]
   Float_t        *sCMSNS2LC2_L_geoX[kMaxsCMSNS2LC2_L];   //[sCMSNS2LC2_L_ngeoch]
   Float_t        *sCMSNS2LC2_L_geoY[kMaxsCMSNS2LC2_L];   //[sCMSNS2LC2_L_ngeoch]
   Float_t        *sCMSNS2LC2_L_geoZ[kMaxsCMSNS2LC2_L];   //[sCMSNS2LC2_L_ngeoch]
   Float_t        *sCMSNS2LC2_L_geoR[kMaxsCMSNS2LC2_L];   //[sCMSNS2LC2_L_ngeoch]
   Float_t        *sCMSNS2LC2_L_geoPhi[kMaxsCMSNS2LC2_L];   //[sCMSNS2LC2_L_ngeoch]
   Float_t         sCMSNS2LC2_L_geoposch[kMaxsCMSNS2LC2_L];   //[sCMSNS2LC2_L_]
   Float_t         sCMSNS2LC2_L_geoposX[kMaxsCMSNS2LC2_L];   //[sCMSNS2LC2_L_]
   Float_t         sCMSNS2LC2_L_geoposY[kMaxsCMSNS2LC2_L];   //[sCMSNS2LC2_L_]
   Float_t         sCMSNS2LC2_L_geoposZ[kMaxsCMSNS2LC2_L];   //[sCMSNS2LC2_L_]
   Float_t         sCMSNS2LC2_L_geoposR[kMaxsCMSNS2LC2_L];   //[sCMSNS2LC2_L_]
   Float_t         sCMSNS2LC2_L_geoposPhi[kMaxsCMSNS2LC2_L];   //[sCMSNS2LC2_L_]
   Int_t           sCMSNS2LC3_;
   Int_t           sCMSNS2LC3_ngeoch[kMaxsCMSNS2LC3];   //[sCMSNS2LC3_]
   Int_t          *sCMSNS2LC3_geoch[kMaxsCMSNS2LC3];   //[sCMSNS2LC3_ngeoch]
   Float_t        *sCMSNS2LC3_geoX[kMaxsCMSNS2LC3];   //[sCMSNS2LC3_ngeoch]
   Float_t        *sCMSNS2LC3_geoY[kMaxsCMSNS2LC3];   //[sCMSNS2LC3_ngeoch]
   Float_t        *sCMSNS2LC3_geoZ[kMaxsCMSNS2LC3];   //[sCMSNS2LC3_ngeoch]
   Float_t        *sCMSNS2LC3_geoR[kMaxsCMSNS2LC3];   //[sCMSNS2LC3_ngeoch]
   Float_t        *sCMSNS2LC3_geoPhi[kMaxsCMSNS2LC3];   //[sCMSNS2LC3_ngeoch]
   Float_t         sCMSNS2LC3_geoposch[kMaxsCMSNS2LC3];   //[sCMSNS2LC3_]
   Float_t         sCMSNS2LC3_geoposX[kMaxsCMSNS2LC3];   //[sCMSNS2LC3_]
   Float_t         sCMSNS2LC3_geoposY[kMaxsCMSNS2LC3];   //[sCMSNS2LC3_]
   Float_t         sCMSNS2LC3_geoposZ[kMaxsCMSNS2LC3];   //[sCMSNS2LC3_]
   Float_t         sCMSNS2LC3_geoposR[kMaxsCMSNS2LC3];   //[sCMSNS2LC3_]
   Float_t         sCMSNS2LC3_geoposPhi[kMaxsCMSNS2LC3];   //[sCMSNS2LC3_]

   // List of branches
   TBranch        *b_EventInfo;   //!
   TBranch        *b_g1xcl_;   //!
   TBranch        *b_g1xcl_ngeoch;   //!
   TBranch        *b_g1xcl_geoch;   //!
   TBranch        *b_g1xcl_geoX;   //!
   TBranch        *b_g1xcl_geoY;   //!
   TBranch        *b_g1xcl_geoZ;   //!
   TBranch        *b_g1xcl_geoR;   //!
   TBranch        *b_g1xcl_geoPhi;   //!
   TBranch        *b_g1xcl_geoposch;   //!
   TBranch        *b_g1xcl_geoposX;   //!
   TBranch        *b_g1xcl_geoposY;   //!
   TBranch        *b_g1xcl_geoposZ;   //!
   TBranch        *b_g1xcl_geoposR;   //!
   TBranch        *b_g1xcl_geoposPhi;   //!
   TBranch        *b_g1ycl_;   //!
   TBranch        *b_g1ycl_ngeoch;   //!
   TBranch        *b_g1ycl_geoch;   //!
   TBranch        *b_g1ycl_geoX;   //!
   TBranch        *b_g1ycl_geoY;   //!
   TBranch        *b_g1ycl_geoZ;   //!
   TBranch        *b_g1ycl_geoR;   //!
   TBranch        *b_g1ycl_geoPhi;   //!
   TBranch        *b_g1ycl_geoposch;   //!
   TBranch        *b_g1ycl_geoposX;   //!
   TBranch        *b_g1ycl_geoposY;   //!
   TBranch        *b_g1ycl_geoposZ;   //!
   TBranch        *b_g1ycl_geoposR;   //!
   TBranch        *b_g1ycl_geoposPhi;   //!
   TBranch        *b_g2xcl_;   //!
   TBranch        *b_g2xcl_ngeoch;   //!
   TBranch        *b_g2xcl_geoch;   //!
   TBranch        *b_g2xcl_geoX;   //!
   TBranch        *b_g2xcl_geoY;   //!
   TBranch        *b_g2xcl_geoZ;   //!
   TBranch        *b_g2xcl_geoR;   //!
   TBranch        *b_g2xcl_geoPhi;   //!
   TBranch        *b_g2xcl_geoposch;   //!
   TBranch        *b_g2xcl_geoposX;   //!
   TBranch        *b_g2xcl_geoposY;   //!
   TBranch        *b_g2xcl_geoposZ;   //!
   TBranch        *b_g2xcl_geoposR;   //!
   TBranch        *b_g2xcl_geoposPhi;   //!
   TBranch        *b_g2ycl_;   //!
   TBranch        *b_g2ycl_ngeoch;   //!
   TBranch        *b_g2ycl_geoch;   //!
   TBranch        *b_g2ycl_geoX;   //!
   TBranch        *b_g2ycl_geoY;   //!
   TBranch        *b_g2ycl_geoZ;   //!
   TBranch        *b_g2ycl_geoR;   //!
   TBranch        *b_g2ycl_geoPhi;   //!
   TBranch        *b_g2ycl_geoposch;   //!
   TBranch        *b_g2ycl_geoposX;   //!
   TBranch        *b_g2ycl_geoposY;   //!
   TBranch        *b_g2ycl_geoposZ;   //!
   TBranch        *b_g2ycl_geoposR;   //!
   TBranch        *b_g2ycl_geoposPhi;   //!
   TBranch        *b_g3xcl_;   //!
   TBranch        *b_g3xcl_ngeoch;   //!
   TBranch        *b_g3xcl_geoch;   //!
   TBranch        *b_g3xcl_geoX;   //!
   TBranch        *b_g3xcl_geoY;   //!
   TBranch        *b_g3xcl_geoZ;   //!
   TBranch        *b_g3xcl_geoR;   //!
   TBranch        *b_g3xcl_geoPhi;   //!
   TBranch        *b_g3xcl_geoposch;   //!
   TBranch        *b_g3xcl_geoposX;   //!
   TBranch        *b_g3xcl_geoposY;   //!
   TBranch        *b_g3xcl_geoposZ;   //!
   TBranch        *b_g3xcl_geoposR;   //!
   TBranch        *b_g3xcl_geoposPhi;   //!
   TBranch        *b_g3ycl_;   //!
   TBranch        *b_g3ycl_ngeoch;   //!
   TBranch        *b_g3ycl_geoch;   //!
   TBranch        *b_g3ycl_geoX;   //!
   TBranch        *b_g3ycl_geoY;   //!
   TBranch        *b_g3ycl_geoZ;   //!
   TBranch        *b_g3ycl_geoR;   //!
   TBranch        *b_g3ycl_geoPhi;   //!
   TBranch        *b_g3ycl_geoposch;   //!
   TBranch        *b_g3ycl_geoposX;   //!
   TBranch        *b_g3ycl_geoposY;   //!
   TBranch        *b_g3ycl_geoposZ;   //!
   TBranch        *b_g3ycl_geoposR;   //!
   TBranch        *b_g3ycl_geoposPhi;   //!
   TBranch        *b_sCMSNS2LC1_;   //!
   TBranch        *b_sCMSNS2LC1_ngeoch;   //!
   TBranch        *b_sCMSNS2LC1_geoch;   //!
   TBranch        *b_sCMSNS2LC1_geoX;   //!
   TBranch        *b_sCMSNS2LC1_geoY;   //!
   TBranch        *b_sCMSNS2LC1_geoZ;   //!
   TBranch        *b_sCMSNS2LC1_geoR;   //!
   TBranch        *b_sCMSNS2LC1_geoPhi;   //!
   TBranch        *b_sCMSNS2LC1_geoposch;   //!
   TBranch        *b_sCMSNS2LC1_geoposX;   //!
   TBranch        *b_sCMSNS2LC1_geoposY;   //!
   TBranch        *b_sCMSNS2LC1_geoposZ;   //!
   TBranch        *b_sCMSNS2LC1_geoposR;   //!
   TBranch        *b_sCMSNS2LC1_geoposPhi;   //!
   TBranch        *b_sCMSNS2LC2_;   //!
   TBranch        *b_sCMSNS2LC2_ngeoch;   //!
   TBranch        *b_sCMSNS2LC2_geoch;   //!
   TBranch        *b_sCMSNS2LC2_geoX;   //!
   TBranch        *b_sCMSNS2LC2_geoY;   //!
   TBranch        *b_sCMSNS2LC2_geoZ;   //!
   TBranch        *b_sCMSNS2LC2_geoR;   //!
   TBranch        *b_sCMSNS2LC2_geoPhi;   //!
   TBranch        *b_sCMSNS2LC2_geoposch;   //!
   TBranch        *b_sCMSNS2LC2_geoposX;   //!
   TBranch        *b_sCMSNS2LC2_geoposY;   //!
   TBranch        *b_sCMSNS2LC2_geoposZ;   //!
   TBranch        *b_sCMSNS2LC2_geoposR;   //!
   TBranch        *b_sCMSNS2LC2_geoposPhi;   //!
   TBranch        *b_sCMSNS2LC2_R_;   //!
   TBranch        *b_sCMSNS2LC2_R_ngeoch;   //!
   TBranch        *b_sCMSNS2LC2_R_geoch;   //!
   TBranch        *b_sCMSNS2LC2_R_geoX;   //!
   TBranch        *b_sCMSNS2LC2_R_geoY;   //!
   TBranch        *b_sCMSNS2LC2_R_geoZ;   //!
   TBranch        *b_sCMSNS2LC2_R_geoR;   //!
   TBranch        *b_sCMSNS2LC2_R_geoPhi;   //!
   TBranch        *b_sCMSNS2LC2_R_geoposch;   //!
   TBranch        *b_sCMSNS2LC2_R_geoposX;   //!
   TBranch        *b_sCMSNS2LC2_R_geoposY;   //!
   TBranch        *b_sCMSNS2LC2_R_geoposZ;   //!
   TBranch        *b_sCMSNS2LC2_R_geoposR;   //!
   TBranch        *b_sCMSNS2LC2_R_geoposPhi;   //!
   TBranch        *b_sCMSNS2LC2_L_;   //!
   TBranch        *b_sCMSNS2LC2_L_ngeoch;   //!
   TBranch        *b_sCMSNS2LC2_L_geoch;   //!
   TBranch        *b_sCMSNS2LC2_L_geoX;   //!
   TBranch        *b_sCMSNS2LC2_L_geoY;   //!
   TBranch        *b_sCMSNS2LC2_L_geoZ;   //!
   TBranch        *b_sCMSNS2LC2_L_geoR;   //!
   TBranch        *b_sCMSNS2LC2_L_geoPhi;   //!
   TBranch        *b_sCMSNS2LC2_L_geoposch;   //!
   TBranch        *b_sCMSNS2LC2_L_geoposX;   //!
   TBranch        *b_sCMSNS2LC2_L_geoposY;   //!
   TBranch        *b_sCMSNS2LC2_L_geoposZ;   //!
   TBranch        *b_sCMSNS2LC2_L_geoposR;   //!
   TBranch        *b_sCMSNS2LC2_L_geoposPhi;   //!
   TBranch        *b_sCMSNS2LC3_;   //!
   TBranch        *b_sCMSNS2LC3_ngeoch;   //!
   TBranch        *b_sCMSNS2LC3_geoch;   //!
   TBranch        *b_sCMSNS2LC3_geoX;   //!
   TBranch        *b_sCMSNS2LC3_geoY;   //!
   TBranch        *b_sCMSNS2LC3_geoZ;   //!
   TBranch        *b_sCMSNS2LC3_geoR;   //!
   TBranch        *b_sCMSNS2LC3_geoPhi;   //!
   TBranch        *b_sCMSNS2LC3_geoposch;   //!
   TBranch        *b_sCMSNS2LC3_geoposX;   //!
   TBranch        *b_sCMSNS2LC3_geoposY;   //!
   TBranch        *b_sCMSNS2LC3_geoposZ;   //!
   TBranch        *b_sCMSNS2LC3_geoposR;   //!
   TBranch        *b_sCMSNS2LC3_geoposPhi;   //!

   AiwuTextFile(TTree *tree=0);
   virtual ~AiwuTextFile();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef AiwuTextFile_cxx
AiwuTextFile::AiwuTextFile(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("CRC-Run0411_Muon_10k_MSPL2_HVScan_710pt1_710pt1_710pt0_T20_T20_T20_Lat22-141011_013955-0.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("CRC-Run0411_Muon_10k_MSPL2_HVScan_710pt1_710pt1_710pt0_T20_T20_T20_Lat22-141011_013955-0.root");
      }
      f->GetObject("rd51tbgeo",tree);

   }
   Init(tree);
}

AiwuTextFile::~AiwuTextFile()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t AiwuTextFile::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t AiwuTextFile::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void AiwuTextFile::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set array pointer
   for(int i=0; i<kMaxg1xcl; ++i) g1xcl_geoch[i] = 0;
   for(int i=0; i<kMaxg1xcl; ++i) g1xcl_geoX[i] = 0;
   for(int i=0; i<kMaxg1xcl; ++i) g1xcl_geoY[i] = 0;
   for(int i=0; i<kMaxg1xcl; ++i) g1xcl_geoZ[i] = 0;
   for(int i=0; i<kMaxg1xcl; ++i) g1xcl_geoR[i] = 0;
   for(int i=0; i<kMaxg1xcl; ++i) g1xcl_geoPhi[i] = 0;
   for(int i=0; i<kMaxg1ycl; ++i) g1ycl_geoch[i] = 0;
   for(int i=0; i<kMaxg1ycl; ++i) g1ycl_geoX[i] = 0;
   for(int i=0; i<kMaxg1ycl; ++i) g1ycl_geoY[i] = 0;
   for(int i=0; i<kMaxg1ycl; ++i) g1ycl_geoZ[i] = 0;
   for(int i=0; i<kMaxg1ycl; ++i) g1ycl_geoR[i] = 0;
   for(int i=0; i<kMaxg1ycl; ++i) g1ycl_geoPhi[i] = 0;
   for(int i=0; i<kMaxg2xcl; ++i) g2xcl_geoch[i] = 0;
   for(int i=0; i<kMaxg2xcl; ++i) g2xcl_geoX[i] = 0;
   for(int i=0; i<kMaxg2xcl; ++i) g2xcl_geoY[i] = 0;
   for(int i=0; i<kMaxg2xcl; ++i) g2xcl_geoZ[i] = 0;
   for(int i=0; i<kMaxg2xcl; ++i) g2xcl_geoR[i] = 0;
   for(int i=0; i<kMaxg2xcl; ++i) g2xcl_geoPhi[i] = 0;
   for(int i=0; i<kMaxg2ycl; ++i) g2ycl_geoch[i] = 0;
   for(int i=0; i<kMaxg2ycl; ++i) g2ycl_geoX[i] = 0;
   for(int i=0; i<kMaxg2ycl; ++i) g2ycl_geoY[i] = 0;
   for(int i=0; i<kMaxg2ycl; ++i) g2ycl_geoZ[i] = 0;
   for(int i=0; i<kMaxg2ycl; ++i) g2ycl_geoR[i] = 0;
   for(int i=0; i<kMaxg2ycl; ++i) g2ycl_geoPhi[i] = 0;
   for(int i=0; i<kMaxg3xcl; ++i) g3xcl_geoch[i] = 0;
   for(int i=0; i<kMaxg3xcl; ++i) g3xcl_geoX[i] = 0;
   for(int i=0; i<kMaxg3xcl; ++i) g3xcl_geoY[i] = 0;
   for(int i=0; i<kMaxg3xcl; ++i) g3xcl_geoZ[i] = 0;
   for(int i=0; i<kMaxg3xcl; ++i) g3xcl_geoR[i] = 0;
   for(int i=0; i<kMaxg3xcl; ++i) g3xcl_geoPhi[i] = 0;
   for(int i=0; i<kMaxg3ycl; ++i) g3ycl_geoch[i] = 0;
   for(int i=0; i<kMaxg3ycl; ++i) g3ycl_geoX[i] = 0;
   for(int i=0; i<kMaxg3ycl; ++i) g3ycl_geoY[i] = 0;
   for(int i=0; i<kMaxg3ycl; ++i) g3ycl_geoZ[i] = 0;
   for(int i=0; i<kMaxg3ycl; ++i) g3ycl_geoR[i] = 0;
   for(int i=0; i<kMaxg3ycl; ++i) g3ycl_geoPhi[i] = 0;
   for(int i=0; i<kMaxsCMSNS2LC1; ++i) sCMSNS2LC1_geoch[i] = 0;
   for(int i=0; i<kMaxsCMSNS2LC1; ++i) sCMSNS2LC1_geoX[i] = 0;
   for(int i=0; i<kMaxsCMSNS2LC1; ++i) sCMSNS2LC1_geoY[i] = 0;
   for(int i=0; i<kMaxsCMSNS2LC1; ++i) sCMSNS2LC1_geoZ[i] = 0;
   for(int i=0; i<kMaxsCMSNS2LC1; ++i) sCMSNS2LC1_geoR[i] = 0;
   for(int i=0; i<kMaxsCMSNS2LC1; ++i) sCMSNS2LC1_geoPhi[i] = 0;
   for(int i=0; i<kMaxsCMSNS2LC2; ++i) sCMSNS2LC2_geoch[i] = 0;
   for(int i=0; i<kMaxsCMSNS2LC2; ++i) sCMSNS2LC2_geoX[i] = 0;
   for(int i=0; i<kMaxsCMSNS2LC2; ++i) sCMSNS2LC2_geoY[i] = 0;
   for(int i=0; i<kMaxsCMSNS2LC2; ++i) sCMSNS2LC2_geoZ[i] = 0;
   for(int i=0; i<kMaxsCMSNS2LC2; ++i) sCMSNS2LC2_geoR[i] = 0;
   for(int i=0; i<kMaxsCMSNS2LC2; ++i) sCMSNS2LC2_geoPhi[i] = 0;
   for(int i=0; i<kMaxsCMSNS2LC2_R; ++i) sCMSNS2LC2_R_geoch[i] = 0;
   for(int i=0; i<kMaxsCMSNS2LC2_R; ++i) sCMSNS2LC2_R_geoX[i] = 0;
   for(int i=0; i<kMaxsCMSNS2LC2_R; ++i) sCMSNS2LC2_R_geoY[i] = 0;
   for(int i=0; i<kMaxsCMSNS2LC2_R; ++i) sCMSNS2LC2_R_geoZ[i] = 0;
   for(int i=0; i<kMaxsCMSNS2LC2_R; ++i) sCMSNS2LC2_R_geoR[i] = 0;
   for(int i=0; i<kMaxsCMSNS2LC2_R; ++i) sCMSNS2LC2_R_geoPhi[i] = 0;
   for(int i=0; i<kMaxsCMSNS2LC2_L; ++i) sCMSNS2LC2_L_geoch[i] = 0;
   for(int i=0; i<kMaxsCMSNS2LC2_L; ++i) sCMSNS2LC2_L_geoX[i] = 0;
   for(int i=0; i<kMaxsCMSNS2LC2_L; ++i) sCMSNS2LC2_L_geoY[i] = 0;
   for(int i=0; i<kMaxsCMSNS2LC2_L; ++i) sCMSNS2LC2_L_geoZ[i] = 0;
   for(int i=0; i<kMaxsCMSNS2LC2_L; ++i) sCMSNS2LC2_L_geoR[i] = 0;
   for(int i=0; i<kMaxsCMSNS2LC2_L; ++i) sCMSNS2LC2_L_geoPhi[i] = 0;
   for(int i=0; i<kMaxsCMSNS2LC3; ++i) sCMSNS2LC3_geoch[i] = 0;
   for(int i=0; i<kMaxsCMSNS2LC3; ++i) sCMSNS2LC3_geoX[i] = 0;
   for(int i=0; i<kMaxsCMSNS2LC3; ++i) sCMSNS2LC3_geoY[i] = 0;
   for(int i=0; i<kMaxsCMSNS2LC3; ++i) sCMSNS2LC3_geoZ[i] = 0;
   for(int i=0; i<kMaxsCMSNS2LC3; ++i) sCMSNS2LC3_geoR[i] = 0;
   for(int i=0; i<kMaxsCMSNS2LC3; ++i) sCMSNS2LC3_geoPhi[i] = 0;

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("EventInfo", &EventInfo_EventNumber, &b_EventInfo);
   fChain->SetBranchAddress("g1xcl", &g1xcl_, &b_g1xcl_);
   fChain->SetBranchAddress("g1xcl.ngeoch", g1xcl_ngeoch, &b_g1xcl_ngeoch);
   fChain->SetBranchAddress("g1xcl.geoch", g1xcl_geoch, &b_g1xcl_geoch);
   fChain->SetBranchAddress("g1xcl.geoX", g1xcl_geoX, &b_g1xcl_geoX);
   fChain->SetBranchAddress("g1xcl.geoY", g1xcl_geoY, &b_g1xcl_geoY);
   fChain->SetBranchAddress("g1xcl.geoZ", g1xcl_geoZ, &b_g1xcl_geoZ);
   fChain->SetBranchAddress("g1xcl.geoR", g1xcl_geoR, &b_g1xcl_geoR);
   fChain->SetBranchAddress("g1xcl.geoPhi", g1xcl_geoPhi, &b_g1xcl_geoPhi);
   fChain->SetBranchAddress("g1xcl.geoposch", g1xcl_geoposch, &b_g1xcl_geoposch);
   fChain->SetBranchAddress("g1xcl.geoposX", g1xcl_geoposX, &b_g1xcl_geoposX);
   fChain->SetBranchAddress("g1xcl.geoposY", g1xcl_geoposY, &b_g1xcl_geoposY);
   fChain->SetBranchAddress("g1xcl.geoposZ", g1xcl_geoposZ, &b_g1xcl_geoposZ);
   fChain->SetBranchAddress("g1xcl.geoposR", g1xcl_geoposR, &b_g1xcl_geoposR);
   fChain->SetBranchAddress("g1xcl.geoposPhi", g1xcl_geoposPhi, &b_g1xcl_geoposPhi);
   fChain->SetBranchAddress("g1ycl", &g1ycl_, &b_g1ycl_);
   fChain->SetBranchAddress("g1ycl.ngeoch", g1ycl_ngeoch, &b_g1ycl_ngeoch);
   fChain->SetBranchAddress("g1ycl.geoch", g1ycl_geoch, &b_g1ycl_geoch);
   fChain->SetBranchAddress("g1ycl.geoX", g1ycl_geoX, &b_g1ycl_geoX);
   fChain->SetBranchAddress("g1ycl.geoY", g1ycl_geoY, &b_g1ycl_geoY);
   fChain->SetBranchAddress("g1ycl.geoZ", g1ycl_geoZ, &b_g1ycl_geoZ);
   fChain->SetBranchAddress("g1ycl.geoR", g1ycl_geoR, &b_g1ycl_geoR);
   fChain->SetBranchAddress("g1ycl.geoPhi", g1ycl_geoPhi, &b_g1ycl_geoPhi);
   fChain->SetBranchAddress("g1ycl.geoposch", g1ycl_geoposch, &b_g1ycl_geoposch);
   fChain->SetBranchAddress("g1ycl.geoposX", g1ycl_geoposX, &b_g1ycl_geoposX);
   fChain->SetBranchAddress("g1ycl.geoposY", g1ycl_geoposY, &b_g1ycl_geoposY);
   fChain->SetBranchAddress("g1ycl.geoposZ", g1ycl_geoposZ, &b_g1ycl_geoposZ);
   fChain->SetBranchAddress("g1ycl.geoposR", g1ycl_geoposR, &b_g1ycl_geoposR);
   fChain->SetBranchAddress("g1ycl.geoposPhi", g1ycl_geoposPhi, &b_g1ycl_geoposPhi);
   fChain->SetBranchAddress("g2xcl", &g2xcl_, &b_g2xcl_);
   fChain->SetBranchAddress("g2xcl.ngeoch", g2xcl_ngeoch, &b_g2xcl_ngeoch);
   fChain->SetBranchAddress("g2xcl.geoch", g2xcl_geoch, &b_g2xcl_geoch);
   fChain->SetBranchAddress("g2xcl.geoX", g2xcl_geoX, &b_g2xcl_geoX);
   fChain->SetBranchAddress("g2xcl.geoY", g2xcl_geoY, &b_g2xcl_geoY);
   fChain->SetBranchAddress("g2xcl.geoZ", g2xcl_geoZ, &b_g2xcl_geoZ);
   fChain->SetBranchAddress("g2xcl.geoR", g2xcl_geoR, &b_g2xcl_geoR);
   fChain->SetBranchAddress("g2xcl.geoPhi", g2xcl_geoPhi, &b_g2xcl_geoPhi);
   fChain->SetBranchAddress("g2xcl.geoposch", g2xcl_geoposch, &b_g2xcl_geoposch);
   fChain->SetBranchAddress("g2xcl.geoposX", g2xcl_geoposX, &b_g2xcl_geoposX);
   fChain->SetBranchAddress("g2xcl.geoposY", g2xcl_geoposY, &b_g2xcl_geoposY);
   fChain->SetBranchAddress("g2xcl.geoposZ", g2xcl_geoposZ, &b_g2xcl_geoposZ);
   fChain->SetBranchAddress("g2xcl.geoposR", g2xcl_geoposR, &b_g2xcl_geoposR);
   fChain->SetBranchAddress("g2xcl.geoposPhi", g2xcl_geoposPhi, &b_g2xcl_geoposPhi);
   fChain->SetBranchAddress("g2ycl", &g2ycl_, &b_g2ycl_);
   fChain->SetBranchAddress("g2ycl.ngeoch", g2ycl_ngeoch, &b_g2ycl_ngeoch);
   fChain->SetBranchAddress("g2ycl.geoch", g2ycl_geoch, &b_g2ycl_geoch);
   fChain->SetBranchAddress("g2ycl.geoX", g2ycl_geoX, &b_g2ycl_geoX);
   fChain->SetBranchAddress("g2ycl.geoY", g2ycl_geoY, &b_g2ycl_geoY);
   fChain->SetBranchAddress("g2ycl.geoZ", g2ycl_geoZ, &b_g2ycl_geoZ);
   fChain->SetBranchAddress("g2ycl.geoR", g2ycl_geoR, &b_g2ycl_geoR);
   fChain->SetBranchAddress("g2ycl.geoPhi", g2ycl_geoPhi, &b_g2ycl_geoPhi);
   fChain->SetBranchAddress("g2ycl.geoposch", g2ycl_geoposch, &b_g2ycl_geoposch);
   fChain->SetBranchAddress("g2ycl.geoposX", g2ycl_geoposX, &b_g2ycl_geoposX);
   fChain->SetBranchAddress("g2ycl.geoposY", g2ycl_geoposY, &b_g2ycl_geoposY);
   fChain->SetBranchAddress("g2ycl.geoposZ", g2ycl_geoposZ, &b_g2ycl_geoposZ);
   fChain->SetBranchAddress("g2ycl.geoposR", g2ycl_geoposR, &b_g2ycl_geoposR);
   fChain->SetBranchAddress("g2ycl.geoposPhi", g2ycl_geoposPhi, &b_g2ycl_geoposPhi);
   fChain->SetBranchAddress("g3xcl", &g3xcl_, &b_g3xcl_);
   fChain->SetBranchAddress("g3xcl.ngeoch", g3xcl_ngeoch, &b_g3xcl_ngeoch);
   fChain->SetBranchAddress("g3xcl.geoch", g3xcl_geoch, &b_g3xcl_geoch);
   fChain->SetBranchAddress("g3xcl.geoX", g3xcl_geoX, &b_g3xcl_geoX);
   fChain->SetBranchAddress("g3xcl.geoY", g3xcl_geoY, &b_g3xcl_geoY);
   fChain->SetBranchAddress("g3xcl.geoZ", g3xcl_geoZ, &b_g3xcl_geoZ);
   fChain->SetBranchAddress("g3xcl.geoR", g3xcl_geoR, &b_g3xcl_geoR);
   fChain->SetBranchAddress("g3xcl.geoPhi", g3xcl_geoPhi, &b_g3xcl_geoPhi);
   fChain->SetBranchAddress("g3xcl.geoposch", g3xcl_geoposch, &b_g3xcl_geoposch);
   fChain->SetBranchAddress("g3xcl.geoposX", g3xcl_geoposX, &b_g3xcl_geoposX);
   fChain->SetBranchAddress("g3xcl.geoposY", g3xcl_geoposY, &b_g3xcl_geoposY);
   fChain->SetBranchAddress("g3xcl.geoposZ", g3xcl_geoposZ, &b_g3xcl_geoposZ);
   fChain->SetBranchAddress("g3xcl.geoposR", g3xcl_geoposR, &b_g3xcl_geoposR);
   fChain->SetBranchAddress("g3xcl.geoposPhi", g3xcl_geoposPhi, &b_g3xcl_geoposPhi);
   fChain->SetBranchAddress("g3ycl", &g3ycl_, &b_g3ycl_);
   fChain->SetBranchAddress("g3ycl.ngeoch", g3ycl_ngeoch, &b_g3ycl_ngeoch);
   fChain->SetBranchAddress("g3ycl.geoch", g3ycl_geoch, &b_g3ycl_geoch);
   fChain->SetBranchAddress("g3ycl.geoX", g3ycl_geoX, &b_g3ycl_geoX);
   fChain->SetBranchAddress("g3ycl.geoY", g3ycl_geoY, &b_g3ycl_geoY);
   fChain->SetBranchAddress("g3ycl.geoZ", g3ycl_geoZ, &b_g3ycl_geoZ);
   fChain->SetBranchAddress("g3ycl.geoR", g3ycl_geoR, &b_g3ycl_geoR);
   fChain->SetBranchAddress("g3ycl.geoPhi", g3ycl_geoPhi, &b_g3ycl_geoPhi);
   fChain->SetBranchAddress("g3ycl.geoposch", g3ycl_geoposch, &b_g3ycl_geoposch);
   fChain->SetBranchAddress("g3ycl.geoposX", g3ycl_geoposX, &b_g3ycl_geoposX);
   fChain->SetBranchAddress("g3ycl.geoposY", g3ycl_geoposY, &b_g3ycl_geoposY);
   fChain->SetBranchAddress("g3ycl.geoposZ", g3ycl_geoposZ, &b_g3ycl_geoposZ);
   fChain->SetBranchAddress("g3ycl.geoposR", g3ycl_geoposR, &b_g3ycl_geoposR);
   fChain->SetBranchAddress("g3ycl.geoposPhi", g3ycl_geoposPhi, &b_g3ycl_geoposPhi);
   fChain->SetBranchAddress("sCMSNS2LC1", &sCMSNS2LC1_, &b_sCMSNS2LC1_);
   fChain->SetBranchAddress("sCMSNS2LC1.ngeoch", sCMSNS2LC1_ngeoch, &b_sCMSNS2LC1_ngeoch);
   fChain->SetBranchAddress("sCMSNS2LC1.geoch", sCMSNS2LC1_geoch, &b_sCMSNS2LC1_geoch);
   fChain->SetBranchAddress("sCMSNS2LC1.geoX", sCMSNS2LC1_geoX, &b_sCMSNS2LC1_geoX);
   fChain->SetBranchAddress("sCMSNS2LC1.geoY", sCMSNS2LC1_geoY, &b_sCMSNS2LC1_geoY);
   fChain->SetBranchAddress("sCMSNS2LC1.geoZ", sCMSNS2LC1_geoZ, &b_sCMSNS2LC1_geoZ);
   fChain->SetBranchAddress("sCMSNS2LC1.geoR", sCMSNS2LC1_geoR, &b_sCMSNS2LC1_geoR);
   fChain->SetBranchAddress("sCMSNS2LC1.geoPhi", sCMSNS2LC1_geoPhi, &b_sCMSNS2LC1_geoPhi);
   fChain->SetBranchAddress("sCMSNS2LC1.geoposch", sCMSNS2LC1_geoposch, &b_sCMSNS2LC1_geoposch);
   fChain->SetBranchAddress("sCMSNS2LC1.geoposX", sCMSNS2LC1_geoposX, &b_sCMSNS2LC1_geoposX);
   fChain->SetBranchAddress("sCMSNS2LC1.geoposY", sCMSNS2LC1_geoposY, &b_sCMSNS2LC1_geoposY);
   fChain->SetBranchAddress("sCMSNS2LC1.geoposZ", sCMSNS2LC1_geoposZ, &b_sCMSNS2LC1_geoposZ);
   fChain->SetBranchAddress("sCMSNS2LC1.geoposR", sCMSNS2LC1_geoposR, &b_sCMSNS2LC1_geoposR);
   fChain->SetBranchAddress("sCMSNS2LC1.geoposPhi", sCMSNS2LC1_geoposPhi, &b_sCMSNS2LC1_geoposPhi);
   fChain->SetBranchAddress("sCMSNS2LC2", &sCMSNS2LC2_, &b_sCMSNS2LC2_);
   fChain->SetBranchAddress("sCMSNS2LC2.ngeoch", sCMSNS2LC2_ngeoch, &b_sCMSNS2LC2_ngeoch);
   fChain->SetBranchAddress("sCMSNS2LC2.geoch", sCMSNS2LC2_geoch, &b_sCMSNS2LC2_geoch);
   fChain->SetBranchAddress("sCMSNS2LC2.geoX", sCMSNS2LC2_geoX, &b_sCMSNS2LC2_geoX);
   fChain->SetBranchAddress("sCMSNS2LC2.geoY", sCMSNS2LC2_geoY, &b_sCMSNS2LC2_geoY);
   fChain->SetBranchAddress("sCMSNS2LC2.geoZ", sCMSNS2LC2_geoZ, &b_sCMSNS2LC2_geoZ);
   fChain->SetBranchAddress("sCMSNS2LC2.geoR", sCMSNS2LC2_geoR, &b_sCMSNS2LC2_geoR);
   fChain->SetBranchAddress("sCMSNS2LC2.geoPhi", sCMSNS2LC2_geoPhi, &b_sCMSNS2LC2_geoPhi);
   fChain->SetBranchAddress("sCMSNS2LC2.geoposch", sCMSNS2LC2_geoposch, &b_sCMSNS2LC2_geoposch);
   fChain->SetBranchAddress("sCMSNS2LC2.geoposX", sCMSNS2LC2_geoposX, &b_sCMSNS2LC2_geoposX);
   fChain->SetBranchAddress("sCMSNS2LC2.geoposY", sCMSNS2LC2_geoposY, &b_sCMSNS2LC2_geoposY);
   fChain->SetBranchAddress("sCMSNS2LC2.geoposZ", sCMSNS2LC2_geoposZ, &b_sCMSNS2LC2_geoposZ);
   fChain->SetBranchAddress("sCMSNS2LC2.geoposR", sCMSNS2LC2_geoposR, &b_sCMSNS2LC2_geoposR);
   fChain->SetBranchAddress("sCMSNS2LC2.geoposPhi", sCMSNS2LC2_geoposPhi, &b_sCMSNS2LC2_geoposPhi);
   fChain->SetBranchAddress("sCMSNS2LC2_R", &sCMSNS2LC2_R_, &b_sCMSNS2LC2_R_);
   fChain->SetBranchAddress("sCMSNS2LC2_R.ngeoch", sCMSNS2LC2_R_ngeoch, &b_sCMSNS2LC2_R_ngeoch);
   fChain->SetBranchAddress("sCMSNS2LC2_R.geoch", sCMSNS2LC2_R_geoch, &b_sCMSNS2LC2_R_geoch);
   fChain->SetBranchAddress("sCMSNS2LC2_R.geoX", sCMSNS2LC2_R_geoX, &b_sCMSNS2LC2_R_geoX);
   fChain->SetBranchAddress("sCMSNS2LC2_R.geoY", sCMSNS2LC2_R_geoY, &b_sCMSNS2LC2_R_geoY);
   fChain->SetBranchAddress("sCMSNS2LC2_R.geoZ", sCMSNS2LC2_R_geoZ, &b_sCMSNS2LC2_R_geoZ);
   fChain->SetBranchAddress("sCMSNS2LC2_R.geoR", sCMSNS2LC2_R_geoR, &b_sCMSNS2LC2_R_geoR);
   fChain->SetBranchAddress("sCMSNS2LC2_R.geoPhi", sCMSNS2LC2_R_geoPhi, &b_sCMSNS2LC2_R_geoPhi);
   fChain->SetBranchAddress("sCMSNS2LC2_R.geoposch", sCMSNS2LC2_R_geoposch, &b_sCMSNS2LC2_R_geoposch);
   fChain->SetBranchAddress("sCMSNS2LC2_R.geoposX", sCMSNS2LC2_R_geoposX, &b_sCMSNS2LC2_R_geoposX);
   fChain->SetBranchAddress("sCMSNS2LC2_R.geoposY", sCMSNS2LC2_R_geoposY, &b_sCMSNS2LC2_R_geoposY);
   fChain->SetBranchAddress("sCMSNS2LC2_R.geoposZ", sCMSNS2LC2_R_geoposZ, &b_sCMSNS2LC2_R_geoposZ);
   fChain->SetBranchAddress("sCMSNS2LC2_R.geoposR", sCMSNS2LC2_R_geoposR, &b_sCMSNS2LC2_R_geoposR);
   fChain->SetBranchAddress("sCMSNS2LC2_R.geoposPhi", sCMSNS2LC2_R_geoposPhi, &b_sCMSNS2LC2_R_geoposPhi);
   fChain->SetBranchAddress("sCMSNS2LC2_L", &sCMSNS2LC2_L_, &b_sCMSNS2LC2_L_);
   fChain->SetBranchAddress("sCMSNS2LC2_L.ngeoch", sCMSNS2LC2_L_ngeoch, &b_sCMSNS2LC2_L_ngeoch);
   fChain->SetBranchAddress("sCMSNS2LC2_L.geoch", sCMSNS2LC2_L_geoch, &b_sCMSNS2LC2_L_geoch);
   fChain->SetBranchAddress("sCMSNS2LC2_L.geoX", sCMSNS2LC2_L_geoX, &b_sCMSNS2LC2_L_geoX);
   fChain->SetBranchAddress("sCMSNS2LC2_L.geoY", sCMSNS2LC2_L_geoY, &b_sCMSNS2LC2_L_geoY);
   fChain->SetBranchAddress("sCMSNS2LC2_L.geoZ", sCMSNS2LC2_L_geoZ, &b_sCMSNS2LC2_L_geoZ);
   fChain->SetBranchAddress("sCMSNS2LC2_L.geoR", sCMSNS2LC2_L_geoR, &b_sCMSNS2LC2_L_geoR);
   fChain->SetBranchAddress("sCMSNS2LC2_L.geoPhi", sCMSNS2LC2_L_geoPhi, &b_sCMSNS2LC2_L_geoPhi);
   fChain->SetBranchAddress("sCMSNS2LC2_L.geoposch", sCMSNS2LC2_L_geoposch, &b_sCMSNS2LC2_L_geoposch);
   fChain->SetBranchAddress("sCMSNS2LC2_L.geoposX", sCMSNS2LC2_L_geoposX, &b_sCMSNS2LC2_L_geoposX);
   fChain->SetBranchAddress("sCMSNS2LC2_L.geoposY", sCMSNS2LC2_L_geoposY, &b_sCMSNS2LC2_L_geoposY);
   fChain->SetBranchAddress("sCMSNS2LC2_L.geoposZ", sCMSNS2LC2_L_geoposZ, &b_sCMSNS2LC2_L_geoposZ);
   fChain->SetBranchAddress("sCMSNS2LC2_L.geoposR", sCMSNS2LC2_L_geoposR, &b_sCMSNS2LC2_L_geoposR);
   fChain->SetBranchAddress("sCMSNS2LC2_L.geoposPhi", sCMSNS2LC2_L_geoposPhi, &b_sCMSNS2LC2_L_geoposPhi);
   fChain->SetBranchAddress("sCMSNS2LC3", &sCMSNS2LC3_, &b_sCMSNS2LC3_);
   fChain->SetBranchAddress("sCMSNS2LC3.ngeoch", sCMSNS2LC3_ngeoch, &b_sCMSNS2LC3_ngeoch);
   fChain->SetBranchAddress("sCMSNS2LC3.geoch", sCMSNS2LC3_geoch, &b_sCMSNS2LC3_geoch);
   fChain->SetBranchAddress("sCMSNS2LC3.geoX", sCMSNS2LC3_geoX, &b_sCMSNS2LC3_geoX);
   fChain->SetBranchAddress("sCMSNS2LC3.geoY", sCMSNS2LC3_geoY, &b_sCMSNS2LC3_geoY);
   fChain->SetBranchAddress("sCMSNS2LC3.geoZ", sCMSNS2LC3_geoZ, &b_sCMSNS2LC3_geoZ);
   fChain->SetBranchAddress("sCMSNS2LC3.geoR", sCMSNS2LC3_geoR, &b_sCMSNS2LC3_geoR);
   fChain->SetBranchAddress("sCMSNS2LC3.geoPhi", sCMSNS2LC3_geoPhi, &b_sCMSNS2LC3_geoPhi);
   fChain->SetBranchAddress("sCMSNS2LC3.geoposch", sCMSNS2LC3_geoposch, &b_sCMSNS2LC3_geoposch);
   fChain->SetBranchAddress("sCMSNS2LC3.geoposX", sCMSNS2LC3_geoposX, &b_sCMSNS2LC3_geoposX);
   fChain->SetBranchAddress("sCMSNS2LC3.geoposY", sCMSNS2LC3_geoposY, &b_sCMSNS2LC3_geoposY);
   fChain->SetBranchAddress("sCMSNS2LC3.geoposZ", sCMSNS2LC3_geoposZ, &b_sCMSNS2LC3_geoposZ);
   fChain->SetBranchAddress("sCMSNS2LC3.geoposR", sCMSNS2LC3_geoposR, &b_sCMSNS2LC3_geoposR);
   fChain->SetBranchAddress("sCMSNS2LC3.geoposPhi", sCMSNS2LC3_geoposPhi, &b_sCMSNS2LC3_geoposPhi);
   Notify();
}

Bool_t AiwuTextFile::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void AiwuTextFile::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t AiwuTextFile::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef AiwuTextFile_cxx
