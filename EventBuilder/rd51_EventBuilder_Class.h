//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Nov  5 16:34:50 2014 by ROOT version 5.34/20
// from TTree rd51tbgeo/RD51 test beam geometry
// found on file: /afs/cern.ch/user/r/rasharma/work/TurboSoftware/EventBuilder/OutPutData/Run0411_Muon_10k_MSPL2_HVScan_710pt1_710pt1_710pt0_T20_T20_T20_Lat22/CRC-Run0411_Muon_10k_MSPL2_HVScan_710pt1_710pt1_710pt0_T20_T20_T20_Lat22-141011_013955-0.root
//////////////////////////////////////////////////////////

#ifndef rd51_EventBuilder_Class_h
#define rd51_EventBuilder_Class_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>

// Header file for the classes stored in the TTree if any.
#include <TClonesArray.h>
#include "/afs/cern.ch/work/r/rasharma/TurboSoftware/EventBuilder/./Clustering/GeoDataArray_T.hpp"
#include "/afs/cern.ch/work/r/rasharma/TurboSoftware/EventBuilder/./Clustering/GeoDataArray_T.hpp"

// Fixed size dimensions of array or collections stored in the TTree if any.
   const Int_t kMaxg1xcl = 12;
   const Int_t kMaxg1ycl = 12;
   const Int_t kMaxg2xcl = 10;
   const Int_t kMaxg2ycl = 15;
   const Int_t kMaxg3xcl = 9;
   const Int_t kMaxg3ycl = 9;
   const Int_t kMaxg4xcl = 1;
   const Int_t kMaxg4ycl = 1;
   const Int_t kMaxgCMSLGcl = 1;
   const Int_t kMaxg1T2Padscl = 1;
   const Int_t kMaxg2T2Padscl = 1;
   const Int_t kMaxg1T2Stripscl = 1;
   const Int_t kMaxg2T2Stripscl = 1;
   const Int_t kMaxgCTLBottomLeftxcl = 1;
   const Int_t kMaxgCTLBottomLeftycl = 1;
   const Int_t kMaxgCTLMiddleLeftycl = 1;
   const Int_t kMaxgCTLTopLeftxcl = 1;
   const Int_t kMaxgCTLTopLeftycl = 1;
   const Int_t kMaxgCTLTopMiddlexcl = 1;
   const Int_t kMaxgCTLTopRightxcl = 1;
   const Int_t kMaxgCTLTopRightycl = 1;
   const Int_t kMaxsCMSNS2LC1 = 9;
   const Int_t kMaxsCMSNS2LC2 = 9;
   const Int_t kMaxsCMSNS2LC2_R = 8;
   const Int_t kMaxsCMSNS2LC2_L = 4;
   const Int_t kMaxsCMSNS2LC3 = 13;

class rd51_EventBuilder_Class : public TSelector {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain

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
   Int_t           g4xcl_;
   Int_t           g4xcl_ngeoch[kMaxg4xcl];   //[g4xcl_]
   Int_t          *g4xcl_geoch[kMaxg4xcl];   //[g4xcl_ngeoch]
   Float_t        *g4xcl_geoX[kMaxg4xcl];   //[g4xcl_ngeoch]
   Float_t        *g4xcl_geoY[kMaxg4xcl];   //[g4xcl_ngeoch]
   Float_t        *g4xcl_geoZ[kMaxg4xcl];   //[g4xcl_ngeoch]
   Float_t        *g4xcl_geoR[kMaxg4xcl];   //[g4xcl_ngeoch]
   Float_t        *g4xcl_geoPhi[kMaxg4xcl];   //[g4xcl_ngeoch]
   Float_t         g4xcl_geoposch[kMaxg4xcl];   //[g4xcl_]
   Float_t         g4xcl_geoposX[kMaxg4xcl];   //[g4xcl_]
   Float_t         g4xcl_geoposY[kMaxg4xcl];   //[g4xcl_]
   Float_t         g4xcl_geoposZ[kMaxg4xcl];   //[g4xcl_]
   Float_t         g4xcl_geoposR[kMaxg4xcl];   //[g4xcl_]
   Float_t         g4xcl_geoposPhi[kMaxg4xcl];   //[g4xcl_]
   Int_t           g4ycl_;
   Int_t           g4ycl_ngeoch[kMaxg4ycl];   //[g4ycl_]
   Int_t          *g4ycl_geoch[kMaxg4ycl];   //[g4ycl_ngeoch]
   Float_t        *g4ycl_geoX[kMaxg4ycl];   //[g4ycl_ngeoch]
   Float_t        *g4ycl_geoY[kMaxg4ycl];   //[g4ycl_ngeoch]
   Float_t        *g4ycl_geoZ[kMaxg4ycl];   //[g4ycl_ngeoch]
   Float_t        *g4ycl_geoR[kMaxg4ycl];   //[g4ycl_ngeoch]
   Float_t        *g4ycl_geoPhi[kMaxg4ycl];   //[g4ycl_ngeoch]
   Float_t         g4ycl_geoposch[kMaxg4ycl];   //[g4ycl_]
   Float_t         g4ycl_geoposX[kMaxg4ycl];   //[g4ycl_]
   Float_t         g4ycl_geoposY[kMaxg4ycl];   //[g4ycl_]
   Float_t         g4ycl_geoposZ[kMaxg4ycl];   //[g4ycl_]
   Float_t         g4ycl_geoposR[kMaxg4ycl];   //[g4ycl_]
   Float_t         g4ycl_geoposPhi[kMaxg4ycl];   //[g4ycl_]
   Int_t           gCMSLGcl_;
   Int_t           gCMSLGcl_ngeoch[kMaxgCMSLGcl];   //[gCMSLGcl_]
   Int_t          *gCMSLGcl_geoch[kMaxgCMSLGcl];   //[gCMSLGcl_ngeoch]
   Float_t        *gCMSLGcl_geoX[kMaxgCMSLGcl];   //[gCMSLGcl_ngeoch]
   Float_t        *gCMSLGcl_geoY[kMaxgCMSLGcl];   //[gCMSLGcl_ngeoch]
   Float_t        *gCMSLGcl_geoZ[kMaxgCMSLGcl];   //[gCMSLGcl_ngeoch]
   Float_t        *gCMSLGcl_geoR[kMaxgCMSLGcl];   //[gCMSLGcl_ngeoch]
   Float_t        *gCMSLGcl_geoPhi[kMaxgCMSLGcl];   //[gCMSLGcl_ngeoch]
   Float_t         gCMSLGcl_geoposch[kMaxgCMSLGcl];   //[gCMSLGcl_]
   Float_t         gCMSLGcl_geoposX[kMaxgCMSLGcl];   //[gCMSLGcl_]
   Float_t         gCMSLGcl_geoposY[kMaxgCMSLGcl];   //[gCMSLGcl_]
   Float_t         gCMSLGcl_geoposZ[kMaxgCMSLGcl];   //[gCMSLGcl_]
   Float_t         gCMSLGcl_geoposR[kMaxgCMSLGcl];   //[gCMSLGcl_]
   Float_t         gCMSLGcl_geoposPhi[kMaxgCMSLGcl];   //[gCMSLGcl_]
   Int_t           g1T2Padscl_;
   Int_t           g1T2Padscl_ngeoch[kMaxg1T2Padscl];   //[g1T2Padscl_]
   Int_t          *g1T2Padscl_geoch[kMaxg1T2Padscl];   //[g1T2Padscl_ngeoch]
   Float_t        *g1T2Padscl_geoX[kMaxg1T2Padscl];   //[g1T2Padscl_ngeoch]
   Float_t        *g1T2Padscl_geoY[kMaxg1T2Padscl];   //[g1T2Padscl_ngeoch]
   Float_t        *g1T2Padscl_geoZ[kMaxg1T2Padscl];   //[g1T2Padscl_ngeoch]
   Float_t        *g1T2Padscl_geoR[kMaxg1T2Padscl];   //[g1T2Padscl_ngeoch]
   Float_t        *g1T2Padscl_geoPhi[kMaxg1T2Padscl];   //[g1T2Padscl_ngeoch]
   Float_t         g1T2Padscl_geoposch[kMaxg1T2Padscl];   //[g1T2Padscl_]
   Float_t         g1T2Padscl_geoposX[kMaxg1T2Padscl];   //[g1T2Padscl_]
   Float_t         g1T2Padscl_geoposY[kMaxg1T2Padscl];   //[g1T2Padscl_]
   Float_t         g1T2Padscl_geoposZ[kMaxg1T2Padscl];   //[g1T2Padscl_]
   Float_t         g1T2Padscl_geoposR[kMaxg1T2Padscl];   //[g1T2Padscl_]
   Float_t         g1T2Padscl_geoposPhi[kMaxg1T2Padscl];   //[g1T2Padscl_]
   Int_t           g2T2Padscl_;
   Int_t           g2T2Padscl_ngeoch[kMaxg2T2Padscl];   //[g2T2Padscl_]
   Int_t          *g2T2Padscl_geoch[kMaxg2T2Padscl];   //[g2T2Padscl_ngeoch]
   Float_t        *g2T2Padscl_geoX[kMaxg2T2Padscl];   //[g2T2Padscl_ngeoch]
   Float_t        *g2T2Padscl_geoY[kMaxg2T2Padscl];   //[g2T2Padscl_ngeoch]
   Float_t        *g2T2Padscl_geoZ[kMaxg2T2Padscl];   //[g2T2Padscl_ngeoch]
   Float_t        *g2T2Padscl_geoR[kMaxg2T2Padscl];   //[g2T2Padscl_ngeoch]
   Float_t        *g2T2Padscl_geoPhi[kMaxg2T2Padscl];   //[g2T2Padscl_ngeoch]
   Float_t         g2T2Padscl_geoposch[kMaxg2T2Padscl];   //[g2T2Padscl_]
   Float_t         g2T2Padscl_geoposX[kMaxg2T2Padscl];   //[g2T2Padscl_]
   Float_t         g2T2Padscl_geoposY[kMaxg2T2Padscl];   //[g2T2Padscl_]
   Float_t         g2T2Padscl_geoposZ[kMaxg2T2Padscl];   //[g2T2Padscl_]
   Float_t         g2T2Padscl_geoposR[kMaxg2T2Padscl];   //[g2T2Padscl_]
   Float_t         g2T2Padscl_geoposPhi[kMaxg2T2Padscl];   //[g2T2Padscl_]
   Int_t           g1T2Stripscl_;
   Int_t           g1T2Stripscl_ngeoch[kMaxg1T2Stripscl];   //[g1T2Stripscl_]
   Int_t          *g1T2Stripscl_geoch[kMaxg1T2Stripscl];   //[g1T2Stripscl_ngeoch]
   Float_t        *g1T2Stripscl_geoX[kMaxg1T2Stripscl];   //[g1T2Stripscl_ngeoch]
   Float_t        *g1T2Stripscl_geoY[kMaxg1T2Stripscl];   //[g1T2Stripscl_ngeoch]
   Float_t        *g1T2Stripscl_geoZ[kMaxg1T2Stripscl];   //[g1T2Stripscl_ngeoch]
   Float_t        *g1T2Stripscl_geoR[kMaxg1T2Stripscl];   //[g1T2Stripscl_ngeoch]
   Float_t        *g1T2Stripscl_geoPhi[kMaxg1T2Stripscl];   //[g1T2Stripscl_ngeoch]
   Float_t         g1T2Stripscl_geoposch[kMaxg1T2Stripscl];   //[g1T2Stripscl_]
   Float_t         g1T2Stripscl_geoposX[kMaxg1T2Stripscl];   //[g1T2Stripscl_]
   Float_t         g1T2Stripscl_geoposY[kMaxg1T2Stripscl];   //[g1T2Stripscl_]
   Float_t         g1T2Stripscl_geoposZ[kMaxg1T2Stripscl];   //[g1T2Stripscl_]
   Float_t         g1T2Stripscl_geoposR[kMaxg1T2Stripscl];   //[g1T2Stripscl_]
   Float_t         g1T2Stripscl_geoposPhi[kMaxg1T2Stripscl];   //[g1T2Stripscl_]
   Int_t           g2T2Stripscl_;
   Int_t           g2T2Stripscl_ngeoch[kMaxg2T2Stripscl];   //[g2T2Stripscl_]
   Int_t          *g2T2Stripscl_geoch[kMaxg2T2Stripscl];   //[g2T2Stripscl_ngeoch]
   Float_t        *g2T2Stripscl_geoX[kMaxg2T2Stripscl];   //[g2T2Stripscl_ngeoch]
   Float_t        *g2T2Stripscl_geoY[kMaxg2T2Stripscl];   //[g2T2Stripscl_ngeoch]
   Float_t        *g2T2Stripscl_geoZ[kMaxg2T2Stripscl];   //[g2T2Stripscl_ngeoch]
   Float_t        *g2T2Stripscl_geoR[kMaxg2T2Stripscl];   //[g2T2Stripscl_ngeoch]
   Float_t        *g2T2Stripscl_geoPhi[kMaxg2T2Stripscl];   //[g2T2Stripscl_ngeoch]
   Float_t         g2T2Stripscl_geoposch[kMaxg2T2Stripscl];   //[g2T2Stripscl_]
   Float_t         g2T2Stripscl_geoposX[kMaxg2T2Stripscl];   //[g2T2Stripscl_]
   Float_t         g2T2Stripscl_geoposY[kMaxg2T2Stripscl];   //[g2T2Stripscl_]
   Float_t         g2T2Stripscl_geoposZ[kMaxg2T2Stripscl];   //[g2T2Stripscl_]
   Float_t         g2T2Stripscl_geoposR[kMaxg2T2Stripscl];   //[g2T2Stripscl_]
   Float_t         g2T2Stripscl_geoposPhi[kMaxg2T2Stripscl];   //[g2T2Stripscl_]
   Int_t           gCTLBottomLeftxcl_;
   Int_t           gCTLBottomLeftxcl_ngeoch[kMaxgCTLBottomLeftxcl];   //[gCTLBottomLeftxcl_]
   Int_t          *gCTLBottomLeftxcl_geoch[kMaxgCTLBottomLeftxcl];   //[gCTLBottomLeftxcl_ngeoch]
   Float_t        *gCTLBottomLeftxcl_geoX[kMaxgCTLBottomLeftxcl];   //[gCTLBottomLeftxcl_ngeoch]
   Float_t        *gCTLBottomLeftxcl_geoY[kMaxgCTLBottomLeftxcl];   //[gCTLBottomLeftxcl_ngeoch]
   Float_t        *gCTLBottomLeftxcl_geoZ[kMaxgCTLBottomLeftxcl];   //[gCTLBottomLeftxcl_ngeoch]
   Float_t        *gCTLBottomLeftxcl_geoR[kMaxgCTLBottomLeftxcl];   //[gCTLBottomLeftxcl_ngeoch]
   Float_t        *gCTLBottomLeftxcl_geoPhi[kMaxgCTLBottomLeftxcl];   //[gCTLBottomLeftxcl_ngeoch]
   Float_t         gCTLBottomLeftxcl_geoposch[kMaxgCTLBottomLeftxcl];   //[gCTLBottomLeftxcl_]
   Float_t         gCTLBottomLeftxcl_geoposX[kMaxgCTLBottomLeftxcl];   //[gCTLBottomLeftxcl_]
   Float_t         gCTLBottomLeftxcl_geoposY[kMaxgCTLBottomLeftxcl];   //[gCTLBottomLeftxcl_]
   Float_t         gCTLBottomLeftxcl_geoposZ[kMaxgCTLBottomLeftxcl];   //[gCTLBottomLeftxcl_]
   Float_t         gCTLBottomLeftxcl_geoposR[kMaxgCTLBottomLeftxcl];   //[gCTLBottomLeftxcl_]
   Float_t         gCTLBottomLeftxcl_geoposPhi[kMaxgCTLBottomLeftxcl];   //[gCTLBottomLeftxcl_]
   Int_t           gCTLBottomLeftycl_;
   Int_t           gCTLBottomLeftycl_ngeoch[kMaxgCTLBottomLeftycl];   //[gCTLBottomLeftycl_]
   Int_t          *gCTLBottomLeftycl_geoch[kMaxgCTLBottomLeftycl];   //[gCTLBottomLeftycl_ngeoch]
   Float_t        *gCTLBottomLeftycl_geoX[kMaxgCTLBottomLeftycl];   //[gCTLBottomLeftycl_ngeoch]
   Float_t        *gCTLBottomLeftycl_geoY[kMaxgCTLBottomLeftycl];   //[gCTLBottomLeftycl_ngeoch]
   Float_t        *gCTLBottomLeftycl_geoZ[kMaxgCTLBottomLeftycl];   //[gCTLBottomLeftycl_ngeoch]
   Float_t        *gCTLBottomLeftycl_geoR[kMaxgCTLBottomLeftycl];   //[gCTLBottomLeftycl_ngeoch]
   Float_t        *gCTLBottomLeftycl_geoPhi[kMaxgCTLBottomLeftycl];   //[gCTLBottomLeftycl_ngeoch]
   Float_t         gCTLBottomLeftycl_geoposch[kMaxgCTLBottomLeftycl];   //[gCTLBottomLeftycl_]
   Float_t         gCTLBottomLeftycl_geoposX[kMaxgCTLBottomLeftycl];   //[gCTLBottomLeftycl_]
   Float_t         gCTLBottomLeftycl_geoposY[kMaxgCTLBottomLeftycl];   //[gCTLBottomLeftycl_]
   Float_t         gCTLBottomLeftycl_geoposZ[kMaxgCTLBottomLeftycl];   //[gCTLBottomLeftycl_]
   Float_t         gCTLBottomLeftycl_geoposR[kMaxgCTLBottomLeftycl];   //[gCTLBottomLeftycl_]
   Float_t         gCTLBottomLeftycl_geoposPhi[kMaxgCTLBottomLeftycl];   //[gCTLBottomLeftycl_]
   Int_t           gCTLMiddleLeftycl_;
   Int_t           gCTLMiddleLeftycl_ngeoch[kMaxgCTLMiddleLeftycl];   //[gCTLMiddleLeftycl_]
   Int_t          *gCTLMiddleLeftycl_geoch[kMaxgCTLMiddleLeftycl];   //[gCTLMiddleLeftycl_ngeoch]
   Float_t        *gCTLMiddleLeftycl_geoX[kMaxgCTLMiddleLeftycl];   //[gCTLMiddleLeftycl_ngeoch]
   Float_t        *gCTLMiddleLeftycl_geoY[kMaxgCTLMiddleLeftycl];   //[gCTLMiddleLeftycl_ngeoch]
   Float_t        *gCTLMiddleLeftycl_geoZ[kMaxgCTLMiddleLeftycl];   //[gCTLMiddleLeftycl_ngeoch]
   Float_t        *gCTLMiddleLeftycl_geoR[kMaxgCTLMiddleLeftycl];   //[gCTLMiddleLeftycl_ngeoch]
   Float_t        *gCTLMiddleLeftycl_geoPhi[kMaxgCTLMiddleLeftycl];   //[gCTLMiddleLeftycl_ngeoch]
   Float_t         gCTLMiddleLeftycl_geoposch[kMaxgCTLMiddleLeftycl];   //[gCTLMiddleLeftycl_]
   Float_t         gCTLMiddleLeftycl_geoposX[kMaxgCTLMiddleLeftycl];   //[gCTLMiddleLeftycl_]
   Float_t         gCTLMiddleLeftycl_geoposY[kMaxgCTLMiddleLeftycl];   //[gCTLMiddleLeftycl_]
   Float_t         gCTLMiddleLeftycl_geoposZ[kMaxgCTLMiddleLeftycl];   //[gCTLMiddleLeftycl_]
   Float_t         gCTLMiddleLeftycl_geoposR[kMaxgCTLMiddleLeftycl];   //[gCTLMiddleLeftycl_]
   Float_t         gCTLMiddleLeftycl_geoposPhi[kMaxgCTLMiddleLeftycl];   //[gCTLMiddleLeftycl_]
   Int_t           gCTLTopLeftxcl_;
   Int_t           gCTLTopLeftxcl_ngeoch[kMaxgCTLTopLeftxcl];   //[gCTLTopLeftxcl_]
   Int_t          *gCTLTopLeftxcl_geoch[kMaxgCTLTopLeftxcl];   //[gCTLTopLeftxcl_ngeoch]
   Float_t        *gCTLTopLeftxcl_geoX[kMaxgCTLTopLeftxcl];   //[gCTLTopLeftxcl_ngeoch]
   Float_t        *gCTLTopLeftxcl_geoY[kMaxgCTLTopLeftxcl];   //[gCTLTopLeftxcl_ngeoch]
   Float_t        *gCTLTopLeftxcl_geoZ[kMaxgCTLTopLeftxcl];   //[gCTLTopLeftxcl_ngeoch]
   Float_t        *gCTLTopLeftxcl_geoR[kMaxgCTLTopLeftxcl];   //[gCTLTopLeftxcl_ngeoch]
   Float_t        *gCTLTopLeftxcl_geoPhi[kMaxgCTLTopLeftxcl];   //[gCTLTopLeftxcl_ngeoch]
   Float_t         gCTLTopLeftxcl_geoposch[kMaxgCTLTopLeftxcl];   //[gCTLTopLeftxcl_]
   Float_t         gCTLTopLeftxcl_geoposX[kMaxgCTLTopLeftxcl];   //[gCTLTopLeftxcl_]
   Float_t         gCTLTopLeftxcl_geoposY[kMaxgCTLTopLeftxcl];   //[gCTLTopLeftxcl_]
   Float_t         gCTLTopLeftxcl_geoposZ[kMaxgCTLTopLeftxcl];   //[gCTLTopLeftxcl_]
   Float_t         gCTLTopLeftxcl_geoposR[kMaxgCTLTopLeftxcl];   //[gCTLTopLeftxcl_]
   Float_t         gCTLTopLeftxcl_geoposPhi[kMaxgCTLTopLeftxcl];   //[gCTLTopLeftxcl_]
   Int_t           gCTLTopLeftycl_;
   Int_t           gCTLTopLeftycl_ngeoch[kMaxgCTLTopLeftycl];   //[gCTLTopLeftycl_]
   Int_t          *gCTLTopLeftycl_geoch[kMaxgCTLTopLeftycl];   //[gCTLTopLeftycl_ngeoch]
   Float_t        *gCTLTopLeftycl_geoX[kMaxgCTLTopLeftycl];   //[gCTLTopLeftycl_ngeoch]
   Float_t        *gCTLTopLeftycl_geoY[kMaxgCTLTopLeftycl];   //[gCTLTopLeftycl_ngeoch]
   Float_t        *gCTLTopLeftycl_geoZ[kMaxgCTLTopLeftycl];   //[gCTLTopLeftycl_ngeoch]
   Float_t        *gCTLTopLeftycl_geoR[kMaxgCTLTopLeftycl];   //[gCTLTopLeftycl_ngeoch]
   Float_t        *gCTLTopLeftycl_geoPhi[kMaxgCTLTopLeftycl];   //[gCTLTopLeftycl_ngeoch]
   Float_t         gCTLTopLeftycl_geoposch[kMaxgCTLTopLeftycl];   //[gCTLTopLeftycl_]
   Float_t         gCTLTopLeftycl_geoposX[kMaxgCTLTopLeftycl];   //[gCTLTopLeftycl_]
   Float_t         gCTLTopLeftycl_geoposY[kMaxgCTLTopLeftycl];   //[gCTLTopLeftycl_]
   Float_t         gCTLTopLeftycl_geoposZ[kMaxgCTLTopLeftycl];   //[gCTLTopLeftycl_]
   Float_t         gCTLTopLeftycl_geoposR[kMaxgCTLTopLeftycl];   //[gCTLTopLeftycl_]
   Float_t         gCTLTopLeftycl_geoposPhi[kMaxgCTLTopLeftycl];   //[gCTLTopLeftycl_]
   Int_t           gCTLTopMiddlexcl_;
   Int_t           gCTLTopMiddlexcl_ngeoch[kMaxgCTLTopMiddlexcl];   //[gCTLTopMiddlexcl_]
   Int_t          *gCTLTopMiddlexcl_geoch[kMaxgCTLTopMiddlexcl];   //[gCTLTopMiddlexcl_ngeoch]
   Float_t        *gCTLTopMiddlexcl_geoX[kMaxgCTLTopMiddlexcl];   //[gCTLTopMiddlexcl_ngeoch]
   Float_t        *gCTLTopMiddlexcl_geoY[kMaxgCTLTopMiddlexcl];   //[gCTLTopMiddlexcl_ngeoch]
   Float_t        *gCTLTopMiddlexcl_geoZ[kMaxgCTLTopMiddlexcl];   //[gCTLTopMiddlexcl_ngeoch]
   Float_t        *gCTLTopMiddlexcl_geoR[kMaxgCTLTopMiddlexcl];   //[gCTLTopMiddlexcl_ngeoch]
   Float_t        *gCTLTopMiddlexcl_geoPhi[kMaxgCTLTopMiddlexcl];   //[gCTLTopMiddlexcl_ngeoch]
   Float_t         gCTLTopMiddlexcl_geoposch[kMaxgCTLTopMiddlexcl];   //[gCTLTopMiddlexcl_]
   Float_t         gCTLTopMiddlexcl_geoposX[kMaxgCTLTopMiddlexcl];   //[gCTLTopMiddlexcl_]
   Float_t         gCTLTopMiddlexcl_geoposY[kMaxgCTLTopMiddlexcl];   //[gCTLTopMiddlexcl_]
   Float_t         gCTLTopMiddlexcl_geoposZ[kMaxgCTLTopMiddlexcl];   //[gCTLTopMiddlexcl_]
   Float_t         gCTLTopMiddlexcl_geoposR[kMaxgCTLTopMiddlexcl];   //[gCTLTopMiddlexcl_]
   Float_t         gCTLTopMiddlexcl_geoposPhi[kMaxgCTLTopMiddlexcl];   //[gCTLTopMiddlexcl_]
   Int_t           gCTLTopRightxcl_;
   Int_t           gCTLTopRightxcl_ngeoch[kMaxgCTLTopRightxcl];   //[gCTLTopRightxcl_]
   Int_t          *gCTLTopRightxcl_geoch[kMaxgCTLTopRightxcl];   //[gCTLTopRightxcl_ngeoch]
   Float_t        *gCTLTopRightxcl_geoX[kMaxgCTLTopRightxcl];   //[gCTLTopRightxcl_ngeoch]
   Float_t        *gCTLTopRightxcl_geoY[kMaxgCTLTopRightxcl];   //[gCTLTopRightxcl_ngeoch]
   Float_t        *gCTLTopRightxcl_geoZ[kMaxgCTLTopRightxcl];   //[gCTLTopRightxcl_ngeoch]
   Float_t        *gCTLTopRightxcl_geoR[kMaxgCTLTopRightxcl];   //[gCTLTopRightxcl_ngeoch]
   Float_t        *gCTLTopRightxcl_geoPhi[kMaxgCTLTopRightxcl];   //[gCTLTopRightxcl_ngeoch]
   Float_t         gCTLTopRightxcl_geoposch[kMaxgCTLTopRightxcl];   //[gCTLTopRightxcl_]
   Float_t         gCTLTopRightxcl_geoposX[kMaxgCTLTopRightxcl];   //[gCTLTopRightxcl_]
   Float_t         gCTLTopRightxcl_geoposY[kMaxgCTLTopRightxcl];   //[gCTLTopRightxcl_]
   Float_t         gCTLTopRightxcl_geoposZ[kMaxgCTLTopRightxcl];   //[gCTLTopRightxcl_]
   Float_t         gCTLTopRightxcl_geoposR[kMaxgCTLTopRightxcl];   //[gCTLTopRightxcl_]
   Float_t         gCTLTopRightxcl_geoposPhi[kMaxgCTLTopRightxcl];   //[gCTLTopRightxcl_]
   Int_t           gCTLTopRightycl_;
   Int_t           gCTLTopRightycl_ngeoch[kMaxgCTLTopRightycl];   //[gCTLTopRightycl_]
   Int_t          *gCTLTopRightycl_geoch[kMaxgCTLTopRightycl];   //[gCTLTopRightycl_ngeoch]
   Float_t        *gCTLTopRightycl_geoX[kMaxgCTLTopRightycl];   //[gCTLTopRightycl_ngeoch]
   Float_t        *gCTLTopRightycl_geoY[kMaxgCTLTopRightycl];   //[gCTLTopRightycl_ngeoch]
   Float_t        *gCTLTopRightycl_geoZ[kMaxgCTLTopRightycl];   //[gCTLTopRightycl_ngeoch]
   Float_t        *gCTLTopRightycl_geoR[kMaxgCTLTopRightycl];   //[gCTLTopRightycl_ngeoch]
   Float_t        *gCTLTopRightycl_geoPhi[kMaxgCTLTopRightycl];   //[gCTLTopRightycl_ngeoch]
   Float_t         gCTLTopRightycl_geoposch[kMaxgCTLTopRightycl];   //[gCTLTopRightycl_]
   Float_t         gCTLTopRightycl_geoposX[kMaxgCTLTopRightycl];   //[gCTLTopRightycl_]
   Float_t         gCTLTopRightycl_geoposY[kMaxgCTLTopRightycl];   //[gCTLTopRightycl_]
   Float_t         gCTLTopRightycl_geoposZ[kMaxgCTLTopRightycl];   //[gCTLTopRightycl_]
   Float_t         gCTLTopRightycl_geoposR[kMaxgCTLTopRightycl];   //[gCTLTopRightycl_]
   Float_t         gCTLTopRightycl_geoposPhi[kMaxgCTLTopRightycl];   //[gCTLTopRightycl_]
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
   TBranch        *b_g4xcl_;   //!
   TBranch        *b_g4xcl_ngeoch;   //!
   TBranch        *b_g4xcl_geoch;   //!
   TBranch        *b_g4xcl_geoX;   //!
   TBranch        *b_g4xcl_geoY;   //!
   TBranch        *b_g4xcl_geoZ;   //!
   TBranch        *b_g4xcl_geoR;   //!
   TBranch        *b_g4xcl_geoPhi;   //!
   TBranch        *b_g4xcl_geoposch;   //!
   TBranch        *b_g4xcl_geoposX;   //!
   TBranch        *b_g4xcl_geoposY;   //!
   TBranch        *b_g4xcl_geoposZ;   //!
   TBranch        *b_g4xcl_geoposR;   //!
   TBranch        *b_g4xcl_geoposPhi;   //!
   TBranch        *b_g4ycl_;   //!
   TBranch        *b_g4ycl_ngeoch;   //!
   TBranch        *b_g4ycl_geoch;   //!
   TBranch        *b_g4ycl_geoX;   //!
   TBranch        *b_g4ycl_geoY;   //!
   TBranch        *b_g4ycl_geoZ;   //!
   TBranch        *b_g4ycl_geoR;   //!
   TBranch        *b_g4ycl_geoPhi;   //!
   TBranch        *b_g4ycl_geoposch;   //!
   TBranch        *b_g4ycl_geoposX;   //!
   TBranch        *b_g4ycl_geoposY;   //!
   TBranch        *b_g4ycl_geoposZ;   //!
   TBranch        *b_g4ycl_geoposR;   //!
   TBranch        *b_g4ycl_geoposPhi;   //!
   TBranch        *b_gCMSLGcl_;   //!
   TBranch        *b_gCMSLGcl_ngeoch;   //!
   TBranch        *b_gCMSLGcl_geoch;   //!
   TBranch        *b_gCMSLGcl_geoX;   //!
   TBranch        *b_gCMSLGcl_geoY;   //!
   TBranch        *b_gCMSLGcl_geoZ;   //!
   TBranch        *b_gCMSLGcl_geoR;   //!
   TBranch        *b_gCMSLGcl_geoPhi;   //!
   TBranch        *b_gCMSLGcl_geoposch;   //!
   TBranch        *b_gCMSLGcl_geoposX;   //!
   TBranch        *b_gCMSLGcl_geoposY;   //!
   TBranch        *b_gCMSLGcl_geoposZ;   //!
   TBranch        *b_gCMSLGcl_geoposR;   //!
   TBranch        *b_gCMSLGcl_geoposPhi;   //!
   TBranch        *b_g1T2Padscl_;   //!
   TBranch        *b_g1T2Padscl_ngeoch;   //!
   TBranch        *b_g1T2Padscl_geoch;   //!
   TBranch        *b_g1T2Padscl_geoX;   //!
   TBranch        *b_g1T2Padscl_geoY;   //!
   TBranch        *b_g1T2Padscl_geoZ;   //!
   TBranch        *b_g1T2Padscl_geoR;   //!
   TBranch        *b_g1T2Padscl_geoPhi;   //!
   TBranch        *b_g1T2Padscl_geoposch;   //!
   TBranch        *b_g1T2Padscl_geoposX;   //!
   TBranch        *b_g1T2Padscl_geoposY;   //!
   TBranch        *b_g1T2Padscl_geoposZ;   //!
   TBranch        *b_g1T2Padscl_geoposR;   //!
   TBranch        *b_g1T2Padscl_geoposPhi;   //!
   TBranch        *b_g2T2Padscl_;   //!
   TBranch        *b_g2T2Padscl_ngeoch;   //!
   TBranch        *b_g2T2Padscl_geoch;   //!
   TBranch        *b_g2T2Padscl_geoX;   //!
   TBranch        *b_g2T2Padscl_geoY;   //!
   TBranch        *b_g2T2Padscl_geoZ;   //!
   TBranch        *b_g2T2Padscl_geoR;   //!
   TBranch        *b_g2T2Padscl_geoPhi;   //!
   TBranch        *b_g2T2Padscl_geoposch;   //!
   TBranch        *b_g2T2Padscl_geoposX;   //!
   TBranch        *b_g2T2Padscl_geoposY;   //!
   TBranch        *b_g2T2Padscl_geoposZ;   //!
   TBranch        *b_g2T2Padscl_geoposR;   //!
   TBranch        *b_g2T2Padscl_geoposPhi;   //!
   TBranch        *b_g1T2Stripscl_;   //!
   TBranch        *b_g1T2Stripscl_ngeoch;   //!
   TBranch        *b_g1T2Stripscl_geoch;   //!
   TBranch        *b_g1T2Stripscl_geoX;   //!
   TBranch        *b_g1T2Stripscl_geoY;   //!
   TBranch        *b_g1T2Stripscl_geoZ;   //!
   TBranch        *b_g1T2Stripscl_geoR;   //!
   TBranch        *b_g1T2Stripscl_geoPhi;   //!
   TBranch        *b_g1T2Stripscl_geoposch;   //!
   TBranch        *b_g1T2Stripscl_geoposX;   //!
   TBranch        *b_g1T2Stripscl_geoposY;   //!
   TBranch        *b_g1T2Stripscl_geoposZ;   //!
   TBranch        *b_g1T2Stripscl_geoposR;   //!
   TBranch        *b_g1T2Stripscl_geoposPhi;   //!
   TBranch        *b_g2T2Stripscl_;   //!
   TBranch        *b_g2T2Stripscl_ngeoch;   //!
   TBranch        *b_g2T2Stripscl_geoch;   //!
   TBranch        *b_g2T2Stripscl_geoX;   //!
   TBranch        *b_g2T2Stripscl_geoY;   //!
   TBranch        *b_g2T2Stripscl_geoZ;   //!
   TBranch        *b_g2T2Stripscl_geoR;   //!
   TBranch        *b_g2T2Stripscl_geoPhi;   //!
   TBranch        *b_g2T2Stripscl_geoposch;   //!
   TBranch        *b_g2T2Stripscl_geoposX;   //!
   TBranch        *b_g2T2Stripscl_geoposY;   //!
   TBranch        *b_g2T2Stripscl_geoposZ;   //!
   TBranch        *b_g2T2Stripscl_geoposR;   //!
   TBranch        *b_g2T2Stripscl_geoposPhi;   //!
   TBranch        *b_gCTLBottomLeftxcl_;   //!
   TBranch        *b_gCTLBottomLeftxcl_ngeoch;   //!
   TBranch        *b_gCTLBottomLeftxcl_geoch;   //!
   TBranch        *b_gCTLBottomLeftxcl_geoX;   //!
   TBranch        *b_gCTLBottomLeftxcl_geoY;   //!
   TBranch        *b_gCTLBottomLeftxcl_geoZ;   //!
   TBranch        *b_gCTLBottomLeftxcl_geoR;   //!
   TBranch        *b_gCTLBottomLeftxcl_geoPhi;   //!
   TBranch        *b_gCTLBottomLeftxcl_geoposch;   //!
   TBranch        *b_gCTLBottomLeftxcl_geoposX;   //!
   TBranch        *b_gCTLBottomLeftxcl_geoposY;   //!
   TBranch        *b_gCTLBottomLeftxcl_geoposZ;   //!
   TBranch        *b_gCTLBottomLeftxcl_geoposR;   //!
   TBranch        *b_gCTLBottomLeftxcl_geoposPhi;   //!
   TBranch        *b_gCTLBottomLeftycl_;   //!
   TBranch        *b_gCTLBottomLeftycl_ngeoch;   //!
   TBranch        *b_gCTLBottomLeftycl_geoch;   //!
   TBranch        *b_gCTLBottomLeftycl_geoX;   //!
   TBranch        *b_gCTLBottomLeftycl_geoY;   //!
   TBranch        *b_gCTLBottomLeftycl_geoZ;   //!
   TBranch        *b_gCTLBottomLeftycl_geoR;   //!
   TBranch        *b_gCTLBottomLeftycl_geoPhi;   //!
   TBranch        *b_gCTLBottomLeftycl_geoposch;   //!
   TBranch        *b_gCTLBottomLeftycl_geoposX;   //!
   TBranch        *b_gCTLBottomLeftycl_geoposY;   //!
   TBranch        *b_gCTLBottomLeftycl_geoposZ;   //!
   TBranch        *b_gCTLBottomLeftycl_geoposR;   //!
   TBranch        *b_gCTLBottomLeftycl_geoposPhi;   //!
   TBranch        *b_gCTLMiddleLeftycl_;   //!
   TBranch        *b_gCTLMiddleLeftycl_ngeoch;   //!
   TBranch        *b_gCTLMiddleLeftycl_geoch;   //!
   TBranch        *b_gCTLMiddleLeftycl_geoX;   //!
   TBranch        *b_gCTLMiddleLeftycl_geoY;   //!
   TBranch        *b_gCTLMiddleLeftycl_geoZ;   //!
   TBranch        *b_gCTLMiddleLeftycl_geoR;   //!
   TBranch        *b_gCTLMiddleLeftycl_geoPhi;   //!
   TBranch        *b_gCTLMiddleLeftycl_geoposch;   //!
   TBranch        *b_gCTLMiddleLeftycl_geoposX;   //!
   TBranch        *b_gCTLMiddleLeftycl_geoposY;   //!
   TBranch        *b_gCTLMiddleLeftycl_geoposZ;   //!
   TBranch        *b_gCTLMiddleLeftycl_geoposR;   //!
   TBranch        *b_gCTLMiddleLeftycl_geoposPhi;   //!
   TBranch        *b_gCTLTopLeftxcl_;   //!
   TBranch        *b_gCTLTopLeftxcl_ngeoch;   //!
   TBranch        *b_gCTLTopLeftxcl_geoch;   //!
   TBranch        *b_gCTLTopLeftxcl_geoX;   //!
   TBranch        *b_gCTLTopLeftxcl_geoY;   //!
   TBranch        *b_gCTLTopLeftxcl_geoZ;   //!
   TBranch        *b_gCTLTopLeftxcl_geoR;   //!
   TBranch        *b_gCTLTopLeftxcl_geoPhi;   //!
   TBranch        *b_gCTLTopLeftxcl_geoposch;   //!
   TBranch        *b_gCTLTopLeftxcl_geoposX;   //!
   TBranch        *b_gCTLTopLeftxcl_geoposY;   //!
   TBranch        *b_gCTLTopLeftxcl_geoposZ;   //!
   TBranch        *b_gCTLTopLeftxcl_geoposR;   //!
   TBranch        *b_gCTLTopLeftxcl_geoposPhi;   //!
   TBranch        *b_gCTLTopLeftycl_;   //!
   TBranch        *b_gCTLTopLeftycl_ngeoch;   //!
   TBranch        *b_gCTLTopLeftycl_geoch;   //!
   TBranch        *b_gCTLTopLeftycl_geoX;   //!
   TBranch        *b_gCTLTopLeftycl_geoY;   //!
   TBranch        *b_gCTLTopLeftycl_geoZ;   //!
   TBranch        *b_gCTLTopLeftycl_geoR;   //!
   TBranch        *b_gCTLTopLeftycl_geoPhi;   //!
   TBranch        *b_gCTLTopLeftycl_geoposch;   //!
   TBranch        *b_gCTLTopLeftycl_geoposX;   //!
   TBranch        *b_gCTLTopLeftycl_geoposY;   //!
   TBranch        *b_gCTLTopLeftycl_geoposZ;   //!
   TBranch        *b_gCTLTopLeftycl_geoposR;   //!
   TBranch        *b_gCTLTopLeftycl_geoposPhi;   //!
   TBranch        *b_gCTLTopMiddlexcl_;   //!
   TBranch        *b_gCTLTopMiddlexcl_ngeoch;   //!
   TBranch        *b_gCTLTopMiddlexcl_geoch;   //!
   TBranch        *b_gCTLTopMiddlexcl_geoX;   //!
   TBranch        *b_gCTLTopMiddlexcl_geoY;   //!
   TBranch        *b_gCTLTopMiddlexcl_geoZ;   //!
   TBranch        *b_gCTLTopMiddlexcl_geoR;   //!
   TBranch        *b_gCTLTopMiddlexcl_geoPhi;   //!
   TBranch        *b_gCTLTopMiddlexcl_geoposch;   //!
   TBranch        *b_gCTLTopMiddlexcl_geoposX;   //!
   TBranch        *b_gCTLTopMiddlexcl_geoposY;   //!
   TBranch        *b_gCTLTopMiddlexcl_geoposZ;   //!
   TBranch        *b_gCTLTopMiddlexcl_geoposR;   //!
   TBranch        *b_gCTLTopMiddlexcl_geoposPhi;   //!
   TBranch        *b_gCTLTopRightxcl_;   //!
   TBranch        *b_gCTLTopRightxcl_ngeoch;   //!
   TBranch        *b_gCTLTopRightxcl_geoch;   //!
   TBranch        *b_gCTLTopRightxcl_geoX;   //!
   TBranch        *b_gCTLTopRightxcl_geoY;   //!
   TBranch        *b_gCTLTopRightxcl_geoZ;   //!
   TBranch        *b_gCTLTopRightxcl_geoR;   //!
   TBranch        *b_gCTLTopRightxcl_geoPhi;   //!
   TBranch        *b_gCTLTopRightxcl_geoposch;   //!
   TBranch        *b_gCTLTopRightxcl_geoposX;   //!
   TBranch        *b_gCTLTopRightxcl_geoposY;   //!
   TBranch        *b_gCTLTopRightxcl_geoposZ;   //!
   TBranch        *b_gCTLTopRightxcl_geoposR;   //!
   TBranch        *b_gCTLTopRightxcl_geoposPhi;   //!
   TBranch        *b_gCTLTopRightycl_;   //!
   TBranch        *b_gCTLTopRightycl_ngeoch;   //!
   TBranch        *b_gCTLTopRightycl_geoch;   //!
   TBranch        *b_gCTLTopRightycl_geoX;   //!
   TBranch        *b_gCTLTopRightycl_geoY;   //!
   TBranch        *b_gCTLTopRightycl_geoZ;   //!
   TBranch        *b_gCTLTopRightycl_geoR;   //!
   TBranch        *b_gCTLTopRightycl_geoPhi;   //!
   TBranch        *b_gCTLTopRightycl_geoposch;   //!
   TBranch        *b_gCTLTopRightycl_geoposX;   //!
   TBranch        *b_gCTLTopRightycl_geoposY;   //!
   TBranch        *b_gCTLTopRightycl_geoposZ;   //!
   TBranch        *b_gCTLTopRightycl_geoposR;   //!
   TBranch        *b_gCTLTopRightycl_geoposPhi;   //!
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

   rd51_EventBuilder_Class(TTree * /*tree*/ =0) : fChain(0) { }
   virtual ~rd51_EventBuilder_Class() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();

   ClassDef(rd51_EventBuilder_Class,0);
};

#endif

#ifdef rd51_EventBuilder_Class_cxx
void rd51_EventBuilder_Class::Init(TTree *tree)
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
   for(int i=0; i<kMaxg4xcl; ++i) g4xcl_geoch[i] = 0;
   for(int i=0; i<kMaxg4xcl; ++i) g4xcl_geoX[i] = 0;
   for(int i=0; i<kMaxg4xcl; ++i) g4xcl_geoY[i] = 0;
   for(int i=0; i<kMaxg4xcl; ++i) g4xcl_geoZ[i] = 0;
   for(int i=0; i<kMaxg4xcl; ++i) g4xcl_geoR[i] = 0;
   for(int i=0; i<kMaxg4xcl; ++i) g4xcl_geoPhi[i] = 0;
   for(int i=0; i<kMaxg4ycl; ++i) g4ycl_geoch[i] = 0;
   for(int i=0; i<kMaxg4ycl; ++i) g4ycl_geoX[i] = 0;
   for(int i=0; i<kMaxg4ycl; ++i) g4ycl_geoY[i] = 0;
   for(int i=0; i<kMaxg4ycl; ++i) g4ycl_geoZ[i] = 0;
   for(int i=0; i<kMaxg4ycl; ++i) g4ycl_geoR[i] = 0;
   for(int i=0; i<kMaxg4ycl; ++i) g4ycl_geoPhi[i] = 0;
   for(int i=0; i<kMaxgCMSLGcl; ++i) gCMSLGcl_geoch[i] = 0;
   for(int i=0; i<kMaxgCMSLGcl; ++i) gCMSLGcl_geoX[i] = 0;
   for(int i=0; i<kMaxgCMSLGcl; ++i) gCMSLGcl_geoY[i] = 0;
   for(int i=0; i<kMaxgCMSLGcl; ++i) gCMSLGcl_geoZ[i] = 0;
   for(int i=0; i<kMaxgCMSLGcl; ++i) gCMSLGcl_geoR[i] = 0;
   for(int i=0; i<kMaxgCMSLGcl; ++i) gCMSLGcl_geoPhi[i] = 0;
   for(int i=0; i<kMaxg1T2Padscl; ++i) g1T2Padscl_geoch[i] = 0;
   for(int i=0; i<kMaxg1T2Padscl; ++i) g1T2Padscl_geoX[i] = 0;
   for(int i=0; i<kMaxg1T2Padscl; ++i) g1T2Padscl_geoY[i] = 0;
   for(int i=0; i<kMaxg1T2Padscl; ++i) g1T2Padscl_geoZ[i] = 0;
   for(int i=0; i<kMaxg1T2Padscl; ++i) g1T2Padscl_geoR[i] = 0;
   for(int i=0; i<kMaxg1T2Padscl; ++i) g1T2Padscl_geoPhi[i] = 0;
   for(int i=0; i<kMaxg2T2Padscl; ++i) g2T2Padscl_geoch[i] = 0;
   for(int i=0; i<kMaxg2T2Padscl; ++i) g2T2Padscl_geoX[i] = 0;
   for(int i=0; i<kMaxg2T2Padscl; ++i) g2T2Padscl_geoY[i] = 0;
   for(int i=0; i<kMaxg2T2Padscl; ++i) g2T2Padscl_geoZ[i] = 0;
   for(int i=0; i<kMaxg2T2Padscl; ++i) g2T2Padscl_geoR[i] = 0;
   for(int i=0; i<kMaxg2T2Padscl; ++i) g2T2Padscl_geoPhi[i] = 0;
   for(int i=0; i<kMaxg1T2Stripscl; ++i) g1T2Stripscl_geoch[i] = 0;
   for(int i=0; i<kMaxg1T2Stripscl; ++i) g1T2Stripscl_geoX[i] = 0;
   for(int i=0; i<kMaxg1T2Stripscl; ++i) g1T2Stripscl_geoY[i] = 0;
   for(int i=0; i<kMaxg1T2Stripscl; ++i) g1T2Stripscl_geoZ[i] = 0;
   for(int i=0; i<kMaxg1T2Stripscl; ++i) g1T2Stripscl_geoR[i] = 0;
   for(int i=0; i<kMaxg1T2Stripscl; ++i) g1T2Stripscl_geoPhi[i] = 0;
   for(int i=0; i<kMaxg2T2Stripscl; ++i) g2T2Stripscl_geoch[i] = 0;
   for(int i=0; i<kMaxg2T2Stripscl; ++i) g2T2Stripscl_geoX[i] = 0;
   for(int i=0; i<kMaxg2T2Stripscl; ++i) g2T2Stripscl_geoY[i] = 0;
   for(int i=0; i<kMaxg2T2Stripscl; ++i) g2T2Stripscl_geoZ[i] = 0;
   for(int i=0; i<kMaxg2T2Stripscl; ++i) g2T2Stripscl_geoR[i] = 0;
   for(int i=0; i<kMaxg2T2Stripscl; ++i) g2T2Stripscl_geoPhi[i] = 0;
   for(int i=0; i<kMaxgCTLBottomLeftxcl; ++i) gCTLBottomLeftxcl_geoch[i] = 0;
   for(int i=0; i<kMaxgCTLBottomLeftxcl; ++i) gCTLBottomLeftxcl_geoX[i] = 0;
   for(int i=0; i<kMaxgCTLBottomLeftxcl; ++i) gCTLBottomLeftxcl_geoY[i] = 0;
   for(int i=0; i<kMaxgCTLBottomLeftxcl; ++i) gCTLBottomLeftxcl_geoZ[i] = 0;
   for(int i=0; i<kMaxgCTLBottomLeftxcl; ++i) gCTLBottomLeftxcl_geoR[i] = 0;
   for(int i=0; i<kMaxgCTLBottomLeftxcl; ++i) gCTLBottomLeftxcl_geoPhi[i] = 0;
   for(int i=0; i<kMaxgCTLBottomLeftycl; ++i) gCTLBottomLeftycl_geoch[i] = 0;
   for(int i=0; i<kMaxgCTLBottomLeftycl; ++i) gCTLBottomLeftycl_geoX[i] = 0;
   for(int i=0; i<kMaxgCTLBottomLeftycl; ++i) gCTLBottomLeftycl_geoY[i] = 0;
   for(int i=0; i<kMaxgCTLBottomLeftycl; ++i) gCTLBottomLeftycl_geoZ[i] = 0;
   for(int i=0; i<kMaxgCTLBottomLeftycl; ++i) gCTLBottomLeftycl_geoR[i] = 0;
   for(int i=0; i<kMaxgCTLBottomLeftycl; ++i) gCTLBottomLeftycl_geoPhi[i] = 0;
   for(int i=0; i<kMaxgCTLMiddleLeftycl; ++i) gCTLMiddleLeftycl_geoch[i] = 0;
   for(int i=0; i<kMaxgCTLMiddleLeftycl; ++i) gCTLMiddleLeftycl_geoX[i] = 0;
   for(int i=0; i<kMaxgCTLMiddleLeftycl; ++i) gCTLMiddleLeftycl_geoY[i] = 0;
   for(int i=0; i<kMaxgCTLMiddleLeftycl; ++i) gCTLMiddleLeftycl_geoZ[i] = 0;
   for(int i=0; i<kMaxgCTLMiddleLeftycl; ++i) gCTLMiddleLeftycl_geoR[i] = 0;
   for(int i=0; i<kMaxgCTLMiddleLeftycl; ++i) gCTLMiddleLeftycl_geoPhi[i] = 0;
   for(int i=0; i<kMaxgCTLTopLeftxcl; ++i) gCTLTopLeftxcl_geoch[i] = 0;
   for(int i=0; i<kMaxgCTLTopLeftxcl; ++i) gCTLTopLeftxcl_geoX[i] = 0;
   for(int i=0; i<kMaxgCTLTopLeftxcl; ++i) gCTLTopLeftxcl_geoY[i] = 0;
   for(int i=0; i<kMaxgCTLTopLeftxcl; ++i) gCTLTopLeftxcl_geoZ[i] = 0;
   for(int i=0; i<kMaxgCTLTopLeftxcl; ++i) gCTLTopLeftxcl_geoR[i] = 0;
   for(int i=0; i<kMaxgCTLTopLeftxcl; ++i) gCTLTopLeftxcl_geoPhi[i] = 0;
   for(int i=0; i<kMaxgCTLTopLeftycl; ++i) gCTLTopLeftycl_geoch[i] = 0;
   for(int i=0; i<kMaxgCTLTopLeftycl; ++i) gCTLTopLeftycl_geoX[i] = 0;
   for(int i=0; i<kMaxgCTLTopLeftycl; ++i) gCTLTopLeftycl_geoY[i] = 0;
   for(int i=0; i<kMaxgCTLTopLeftycl; ++i) gCTLTopLeftycl_geoZ[i] = 0;
   for(int i=0; i<kMaxgCTLTopLeftycl; ++i) gCTLTopLeftycl_geoR[i] = 0;
   for(int i=0; i<kMaxgCTLTopLeftycl; ++i) gCTLTopLeftycl_geoPhi[i] = 0;
   for(int i=0; i<kMaxgCTLTopMiddlexcl; ++i) gCTLTopMiddlexcl_geoch[i] = 0;
   for(int i=0; i<kMaxgCTLTopMiddlexcl; ++i) gCTLTopMiddlexcl_geoX[i] = 0;
   for(int i=0; i<kMaxgCTLTopMiddlexcl; ++i) gCTLTopMiddlexcl_geoY[i] = 0;
   for(int i=0; i<kMaxgCTLTopMiddlexcl; ++i) gCTLTopMiddlexcl_geoZ[i] = 0;
   for(int i=0; i<kMaxgCTLTopMiddlexcl; ++i) gCTLTopMiddlexcl_geoR[i] = 0;
   for(int i=0; i<kMaxgCTLTopMiddlexcl; ++i) gCTLTopMiddlexcl_geoPhi[i] = 0;
   for(int i=0; i<kMaxgCTLTopRightxcl; ++i) gCTLTopRightxcl_geoch[i] = 0;
   for(int i=0; i<kMaxgCTLTopRightxcl; ++i) gCTLTopRightxcl_geoX[i] = 0;
   for(int i=0; i<kMaxgCTLTopRightxcl; ++i) gCTLTopRightxcl_geoY[i] = 0;
   for(int i=0; i<kMaxgCTLTopRightxcl; ++i) gCTLTopRightxcl_geoZ[i] = 0;
   for(int i=0; i<kMaxgCTLTopRightxcl; ++i) gCTLTopRightxcl_geoR[i] = 0;
   for(int i=0; i<kMaxgCTLTopRightxcl; ++i) gCTLTopRightxcl_geoPhi[i] = 0;
   for(int i=0; i<kMaxgCTLTopRightycl; ++i) gCTLTopRightycl_geoch[i] = 0;
   for(int i=0; i<kMaxgCTLTopRightycl; ++i) gCTLTopRightycl_geoX[i] = 0;
   for(int i=0; i<kMaxgCTLTopRightycl; ++i) gCTLTopRightycl_geoY[i] = 0;
   for(int i=0; i<kMaxgCTLTopRightycl; ++i) gCTLTopRightycl_geoZ[i] = 0;
   for(int i=0; i<kMaxgCTLTopRightycl; ++i) gCTLTopRightycl_geoR[i] = 0;
   for(int i=0; i<kMaxgCTLTopRightycl; ++i) gCTLTopRightycl_geoPhi[i] = 0;
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
   fChain->SetBranchAddress("g4xcl", &g4xcl_, &b_g4xcl_);
   fChain->SetBranchAddress("g4xcl.ngeoch", &g4xcl_ngeoch, &b_g4xcl_ngeoch);
   fChain->SetBranchAddress("g4xcl.geoch", &g4xcl_geoch, &b_g4xcl_geoch);
   fChain->SetBranchAddress("g4xcl.geoX", &g4xcl_geoX, &b_g4xcl_geoX);
   fChain->SetBranchAddress("g4xcl.geoY", &g4xcl_geoY, &b_g4xcl_geoY);
   fChain->SetBranchAddress("g4xcl.geoZ", &g4xcl_geoZ, &b_g4xcl_geoZ);
   fChain->SetBranchAddress("g4xcl.geoR", &g4xcl_geoR, &b_g4xcl_geoR);
   fChain->SetBranchAddress("g4xcl.geoPhi", &g4xcl_geoPhi, &b_g4xcl_geoPhi);
   fChain->SetBranchAddress("g4xcl.geoposch", &g4xcl_geoposch, &b_g4xcl_geoposch);
   fChain->SetBranchAddress("g4xcl.geoposX", &g4xcl_geoposX, &b_g4xcl_geoposX);
   fChain->SetBranchAddress("g4xcl.geoposY", &g4xcl_geoposY, &b_g4xcl_geoposY);
   fChain->SetBranchAddress("g4xcl.geoposZ", &g4xcl_geoposZ, &b_g4xcl_geoposZ);
   fChain->SetBranchAddress("g4xcl.geoposR", &g4xcl_geoposR, &b_g4xcl_geoposR);
   fChain->SetBranchAddress("g4xcl.geoposPhi", &g4xcl_geoposPhi, &b_g4xcl_geoposPhi);
   fChain->SetBranchAddress("g4ycl", &g4ycl_, &b_g4ycl_);
   fChain->SetBranchAddress("g4ycl.ngeoch", &g4ycl_ngeoch, &b_g4ycl_ngeoch);
   fChain->SetBranchAddress("g4ycl.geoch", &g4ycl_geoch, &b_g4ycl_geoch);
   fChain->SetBranchAddress("g4ycl.geoX", &g4ycl_geoX, &b_g4ycl_geoX);
   fChain->SetBranchAddress("g4ycl.geoY", &g4ycl_geoY, &b_g4ycl_geoY);
   fChain->SetBranchAddress("g4ycl.geoZ", &g4ycl_geoZ, &b_g4ycl_geoZ);
   fChain->SetBranchAddress("g4ycl.geoR", &g4ycl_geoR, &b_g4ycl_geoR);
   fChain->SetBranchAddress("g4ycl.geoPhi", &g4ycl_geoPhi, &b_g4ycl_geoPhi);
   fChain->SetBranchAddress("g4ycl.geoposch", &g4ycl_geoposch, &b_g4ycl_geoposch);
   fChain->SetBranchAddress("g4ycl.geoposX", &g4ycl_geoposX, &b_g4ycl_geoposX);
   fChain->SetBranchAddress("g4ycl.geoposY", &g4ycl_geoposY, &b_g4ycl_geoposY);
   fChain->SetBranchAddress("g4ycl.geoposZ", &g4ycl_geoposZ, &b_g4ycl_geoposZ);
   fChain->SetBranchAddress("g4ycl.geoposR", &g4ycl_geoposR, &b_g4ycl_geoposR);
   fChain->SetBranchAddress("g4ycl.geoposPhi", &g4ycl_geoposPhi, &b_g4ycl_geoposPhi);
   fChain->SetBranchAddress("gCMSLGcl", &gCMSLGcl_, &b_gCMSLGcl_);
   fChain->SetBranchAddress("gCMSLGcl.ngeoch", &gCMSLGcl_ngeoch, &b_gCMSLGcl_ngeoch);
   fChain->SetBranchAddress("gCMSLGcl.geoch", &gCMSLGcl_geoch, &b_gCMSLGcl_geoch);
   fChain->SetBranchAddress("gCMSLGcl.geoX", &gCMSLGcl_geoX, &b_gCMSLGcl_geoX);
   fChain->SetBranchAddress("gCMSLGcl.geoY", &gCMSLGcl_geoY, &b_gCMSLGcl_geoY);
   fChain->SetBranchAddress("gCMSLGcl.geoZ", &gCMSLGcl_geoZ, &b_gCMSLGcl_geoZ);
   fChain->SetBranchAddress("gCMSLGcl.geoR", &gCMSLGcl_geoR, &b_gCMSLGcl_geoR);
   fChain->SetBranchAddress("gCMSLGcl.geoPhi", &gCMSLGcl_geoPhi, &b_gCMSLGcl_geoPhi);
   fChain->SetBranchAddress("gCMSLGcl.geoposch", &gCMSLGcl_geoposch, &b_gCMSLGcl_geoposch);
   fChain->SetBranchAddress("gCMSLGcl.geoposX", &gCMSLGcl_geoposX, &b_gCMSLGcl_geoposX);
   fChain->SetBranchAddress("gCMSLGcl.geoposY", &gCMSLGcl_geoposY, &b_gCMSLGcl_geoposY);
   fChain->SetBranchAddress("gCMSLGcl.geoposZ", &gCMSLGcl_geoposZ, &b_gCMSLGcl_geoposZ);
   fChain->SetBranchAddress("gCMSLGcl.geoposR", &gCMSLGcl_geoposR, &b_gCMSLGcl_geoposR);
   fChain->SetBranchAddress("gCMSLGcl.geoposPhi", &gCMSLGcl_geoposPhi, &b_gCMSLGcl_geoposPhi);
   fChain->SetBranchAddress("g1T2Padscl", &g1T2Padscl_, &b_g1T2Padscl_);
   fChain->SetBranchAddress("g1T2Padscl.ngeoch", &g1T2Padscl_ngeoch, &b_g1T2Padscl_ngeoch);
   fChain->SetBranchAddress("g1T2Padscl.geoch", &g1T2Padscl_geoch, &b_g1T2Padscl_geoch);
   fChain->SetBranchAddress("g1T2Padscl.geoX", &g1T2Padscl_geoX, &b_g1T2Padscl_geoX);
   fChain->SetBranchAddress("g1T2Padscl.geoY", &g1T2Padscl_geoY, &b_g1T2Padscl_geoY);
   fChain->SetBranchAddress("g1T2Padscl.geoZ", &g1T2Padscl_geoZ, &b_g1T2Padscl_geoZ);
   fChain->SetBranchAddress("g1T2Padscl.geoR", &g1T2Padscl_geoR, &b_g1T2Padscl_geoR);
   fChain->SetBranchAddress("g1T2Padscl.geoPhi", &g1T2Padscl_geoPhi, &b_g1T2Padscl_geoPhi);
   fChain->SetBranchAddress("g1T2Padscl.geoposch", &g1T2Padscl_geoposch, &b_g1T2Padscl_geoposch);
   fChain->SetBranchAddress("g1T2Padscl.geoposX", &g1T2Padscl_geoposX, &b_g1T2Padscl_geoposX);
   fChain->SetBranchAddress("g1T2Padscl.geoposY", &g1T2Padscl_geoposY, &b_g1T2Padscl_geoposY);
   fChain->SetBranchAddress("g1T2Padscl.geoposZ", &g1T2Padscl_geoposZ, &b_g1T2Padscl_geoposZ);
   fChain->SetBranchAddress("g1T2Padscl.geoposR", &g1T2Padscl_geoposR, &b_g1T2Padscl_geoposR);
   fChain->SetBranchAddress("g1T2Padscl.geoposPhi", &g1T2Padscl_geoposPhi, &b_g1T2Padscl_geoposPhi);
   fChain->SetBranchAddress("g2T2Padscl", &g2T2Padscl_, &b_g2T2Padscl_);
   fChain->SetBranchAddress("g2T2Padscl.ngeoch", &g2T2Padscl_ngeoch, &b_g2T2Padscl_ngeoch);
   fChain->SetBranchAddress("g2T2Padscl.geoch", &g2T2Padscl_geoch, &b_g2T2Padscl_geoch);
   fChain->SetBranchAddress("g2T2Padscl.geoX", &g2T2Padscl_geoX, &b_g2T2Padscl_geoX);
   fChain->SetBranchAddress("g2T2Padscl.geoY", &g2T2Padscl_geoY, &b_g2T2Padscl_geoY);
   fChain->SetBranchAddress("g2T2Padscl.geoZ", &g2T2Padscl_geoZ, &b_g2T2Padscl_geoZ);
   fChain->SetBranchAddress("g2T2Padscl.geoR", &g2T2Padscl_geoR, &b_g2T2Padscl_geoR);
   fChain->SetBranchAddress("g2T2Padscl.geoPhi", &g2T2Padscl_geoPhi, &b_g2T2Padscl_geoPhi);
   fChain->SetBranchAddress("g2T2Padscl.geoposch", &g2T2Padscl_geoposch, &b_g2T2Padscl_geoposch);
   fChain->SetBranchAddress("g2T2Padscl.geoposX", &g2T2Padscl_geoposX, &b_g2T2Padscl_geoposX);
   fChain->SetBranchAddress("g2T2Padscl.geoposY", &g2T2Padscl_geoposY, &b_g2T2Padscl_geoposY);
   fChain->SetBranchAddress("g2T2Padscl.geoposZ", &g2T2Padscl_geoposZ, &b_g2T2Padscl_geoposZ);
   fChain->SetBranchAddress("g2T2Padscl.geoposR", &g2T2Padscl_geoposR, &b_g2T2Padscl_geoposR);
   fChain->SetBranchAddress("g2T2Padscl.geoposPhi", &g2T2Padscl_geoposPhi, &b_g2T2Padscl_geoposPhi);
   fChain->SetBranchAddress("g1T2Stripscl", &g1T2Stripscl_, &b_g1T2Stripscl_);
   fChain->SetBranchAddress("g1T2Stripscl.ngeoch", &g1T2Stripscl_ngeoch, &b_g1T2Stripscl_ngeoch);
   fChain->SetBranchAddress("g1T2Stripscl.geoch", &g1T2Stripscl_geoch, &b_g1T2Stripscl_geoch);
   fChain->SetBranchAddress("g1T2Stripscl.geoX", &g1T2Stripscl_geoX, &b_g1T2Stripscl_geoX);
   fChain->SetBranchAddress("g1T2Stripscl.geoY", &g1T2Stripscl_geoY, &b_g1T2Stripscl_geoY);
   fChain->SetBranchAddress("g1T2Stripscl.geoZ", &g1T2Stripscl_geoZ, &b_g1T2Stripscl_geoZ);
   fChain->SetBranchAddress("g1T2Stripscl.geoR", &g1T2Stripscl_geoR, &b_g1T2Stripscl_geoR);
   fChain->SetBranchAddress("g1T2Stripscl.geoPhi", &g1T2Stripscl_geoPhi, &b_g1T2Stripscl_geoPhi);
   fChain->SetBranchAddress("g1T2Stripscl.geoposch", &g1T2Stripscl_geoposch, &b_g1T2Stripscl_geoposch);
   fChain->SetBranchAddress("g1T2Stripscl.geoposX", &g1T2Stripscl_geoposX, &b_g1T2Stripscl_geoposX);
   fChain->SetBranchAddress("g1T2Stripscl.geoposY", &g1T2Stripscl_geoposY, &b_g1T2Stripscl_geoposY);
   fChain->SetBranchAddress("g1T2Stripscl.geoposZ", &g1T2Stripscl_geoposZ, &b_g1T2Stripscl_geoposZ);
   fChain->SetBranchAddress("g1T2Stripscl.geoposR", &g1T2Stripscl_geoposR, &b_g1T2Stripscl_geoposR);
   fChain->SetBranchAddress("g1T2Stripscl.geoposPhi", &g1T2Stripscl_geoposPhi, &b_g1T2Stripscl_geoposPhi);
   fChain->SetBranchAddress("g2T2Stripscl", &g2T2Stripscl_, &b_g2T2Stripscl_);
   fChain->SetBranchAddress("g2T2Stripscl.ngeoch", &g2T2Stripscl_ngeoch, &b_g2T2Stripscl_ngeoch);
   fChain->SetBranchAddress("g2T2Stripscl.geoch", &g2T2Stripscl_geoch, &b_g2T2Stripscl_geoch);
   fChain->SetBranchAddress("g2T2Stripscl.geoX", &g2T2Stripscl_geoX, &b_g2T2Stripscl_geoX);
   fChain->SetBranchAddress("g2T2Stripscl.geoY", &g2T2Stripscl_geoY, &b_g2T2Stripscl_geoY);
   fChain->SetBranchAddress("g2T2Stripscl.geoZ", &g2T2Stripscl_geoZ, &b_g2T2Stripscl_geoZ);
   fChain->SetBranchAddress("g2T2Stripscl.geoR", &g2T2Stripscl_geoR, &b_g2T2Stripscl_geoR);
   fChain->SetBranchAddress("g2T2Stripscl.geoPhi", &g2T2Stripscl_geoPhi, &b_g2T2Stripscl_geoPhi);
   fChain->SetBranchAddress("g2T2Stripscl.geoposch", &g2T2Stripscl_geoposch, &b_g2T2Stripscl_geoposch);
   fChain->SetBranchAddress("g2T2Stripscl.geoposX", &g2T2Stripscl_geoposX, &b_g2T2Stripscl_geoposX);
   fChain->SetBranchAddress("g2T2Stripscl.geoposY", &g2T2Stripscl_geoposY, &b_g2T2Stripscl_geoposY);
   fChain->SetBranchAddress("g2T2Stripscl.geoposZ", &g2T2Stripscl_geoposZ, &b_g2T2Stripscl_geoposZ);
   fChain->SetBranchAddress("g2T2Stripscl.geoposR", &g2T2Stripscl_geoposR, &b_g2T2Stripscl_geoposR);
   fChain->SetBranchAddress("g2T2Stripscl.geoposPhi", &g2T2Stripscl_geoposPhi, &b_g2T2Stripscl_geoposPhi);
   fChain->SetBranchAddress("gCTLBottomLeftxcl", &gCTLBottomLeftxcl_, &b_gCTLBottomLeftxcl_);
   fChain->SetBranchAddress("gCTLBottomLeftxcl.ngeoch", &gCTLBottomLeftxcl_ngeoch, &b_gCTLBottomLeftxcl_ngeoch);
   fChain->SetBranchAddress("gCTLBottomLeftxcl.geoch", &gCTLBottomLeftxcl_geoch, &b_gCTLBottomLeftxcl_geoch);
   fChain->SetBranchAddress("gCTLBottomLeftxcl.geoX", &gCTLBottomLeftxcl_geoX, &b_gCTLBottomLeftxcl_geoX);
   fChain->SetBranchAddress("gCTLBottomLeftxcl.geoY", &gCTLBottomLeftxcl_geoY, &b_gCTLBottomLeftxcl_geoY);
   fChain->SetBranchAddress("gCTLBottomLeftxcl.geoZ", &gCTLBottomLeftxcl_geoZ, &b_gCTLBottomLeftxcl_geoZ);
   fChain->SetBranchAddress("gCTLBottomLeftxcl.geoR", &gCTLBottomLeftxcl_geoR, &b_gCTLBottomLeftxcl_geoR);
   fChain->SetBranchAddress("gCTLBottomLeftxcl.geoPhi", &gCTLBottomLeftxcl_geoPhi, &b_gCTLBottomLeftxcl_geoPhi);
   fChain->SetBranchAddress("gCTLBottomLeftxcl.geoposch", &gCTLBottomLeftxcl_geoposch, &b_gCTLBottomLeftxcl_geoposch);
   fChain->SetBranchAddress("gCTLBottomLeftxcl.geoposX", &gCTLBottomLeftxcl_geoposX, &b_gCTLBottomLeftxcl_geoposX);
   fChain->SetBranchAddress("gCTLBottomLeftxcl.geoposY", &gCTLBottomLeftxcl_geoposY, &b_gCTLBottomLeftxcl_geoposY);
   fChain->SetBranchAddress("gCTLBottomLeftxcl.geoposZ", &gCTLBottomLeftxcl_geoposZ, &b_gCTLBottomLeftxcl_geoposZ);
   fChain->SetBranchAddress("gCTLBottomLeftxcl.geoposR", &gCTLBottomLeftxcl_geoposR, &b_gCTLBottomLeftxcl_geoposR);
   fChain->SetBranchAddress("gCTLBottomLeftxcl.geoposPhi", &gCTLBottomLeftxcl_geoposPhi, &b_gCTLBottomLeftxcl_geoposPhi);
   fChain->SetBranchAddress("gCTLBottomLeftycl", &gCTLBottomLeftycl_, &b_gCTLBottomLeftycl_);
   fChain->SetBranchAddress("gCTLBottomLeftycl.ngeoch", &gCTLBottomLeftycl_ngeoch, &b_gCTLBottomLeftycl_ngeoch);
   fChain->SetBranchAddress("gCTLBottomLeftycl.geoch", &gCTLBottomLeftycl_geoch, &b_gCTLBottomLeftycl_geoch);
   fChain->SetBranchAddress("gCTLBottomLeftycl.geoX", &gCTLBottomLeftycl_geoX, &b_gCTLBottomLeftycl_geoX);
   fChain->SetBranchAddress("gCTLBottomLeftycl.geoY", &gCTLBottomLeftycl_geoY, &b_gCTLBottomLeftycl_geoY);
   fChain->SetBranchAddress("gCTLBottomLeftycl.geoZ", &gCTLBottomLeftycl_geoZ, &b_gCTLBottomLeftycl_geoZ);
   fChain->SetBranchAddress("gCTLBottomLeftycl.geoR", &gCTLBottomLeftycl_geoR, &b_gCTLBottomLeftycl_geoR);
   fChain->SetBranchAddress("gCTLBottomLeftycl.geoPhi", &gCTLBottomLeftycl_geoPhi, &b_gCTLBottomLeftycl_geoPhi);
   fChain->SetBranchAddress("gCTLBottomLeftycl.geoposch", &gCTLBottomLeftycl_geoposch, &b_gCTLBottomLeftycl_geoposch);
   fChain->SetBranchAddress("gCTLBottomLeftycl.geoposX", &gCTLBottomLeftycl_geoposX, &b_gCTLBottomLeftycl_geoposX);
   fChain->SetBranchAddress("gCTLBottomLeftycl.geoposY", &gCTLBottomLeftycl_geoposY, &b_gCTLBottomLeftycl_geoposY);
   fChain->SetBranchAddress("gCTLBottomLeftycl.geoposZ", &gCTLBottomLeftycl_geoposZ, &b_gCTLBottomLeftycl_geoposZ);
   fChain->SetBranchAddress("gCTLBottomLeftycl.geoposR", &gCTLBottomLeftycl_geoposR, &b_gCTLBottomLeftycl_geoposR);
   fChain->SetBranchAddress("gCTLBottomLeftycl.geoposPhi", &gCTLBottomLeftycl_geoposPhi, &b_gCTLBottomLeftycl_geoposPhi);
   fChain->SetBranchAddress("gCTLMiddleLeftycl", &gCTLMiddleLeftycl_, &b_gCTLMiddleLeftycl_);
   fChain->SetBranchAddress("gCTLMiddleLeftycl.ngeoch", &gCTLMiddleLeftycl_ngeoch, &b_gCTLMiddleLeftycl_ngeoch);
   fChain->SetBranchAddress("gCTLMiddleLeftycl.geoch", &gCTLMiddleLeftycl_geoch, &b_gCTLMiddleLeftycl_geoch);
   fChain->SetBranchAddress("gCTLMiddleLeftycl.geoX", &gCTLMiddleLeftycl_geoX, &b_gCTLMiddleLeftycl_geoX);
   fChain->SetBranchAddress("gCTLMiddleLeftycl.geoY", &gCTLMiddleLeftycl_geoY, &b_gCTLMiddleLeftycl_geoY);
   fChain->SetBranchAddress("gCTLMiddleLeftycl.geoZ", &gCTLMiddleLeftycl_geoZ, &b_gCTLMiddleLeftycl_geoZ);
   fChain->SetBranchAddress("gCTLMiddleLeftycl.geoR", &gCTLMiddleLeftycl_geoR, &b_gCTLMiddleLeftycl_geoR);
   fChain->SetBranchAddress("gCTLMiddleLeftycl.geoPhi", &gCTLMiddleLeftycl_geoPhi, &b_gCTLMiddleLeftycl_geoPhi);
   fChain->SetBranchAddress("gCTLMiddleLeftycl.geoposch", &gCTLMiddleLeftycl_geoposch, &b_gCTLMiddleLeftycl_geoposch);
   fChain->SetBranchAddress("gCTLMiddleLeftycl.geoposX", &gCTLMiddleLeftycl_geoposX, &b_gCTLMiddleLeftycl_geoposX);
   fChain->SetBranchAddress("gCTLMiddleLeftycl.geoposY", &gCTLMiddleLeftycl_geoposY, &b_gCTLMiddleLeftycl_geoposY);
   fChain->SetBranchAddress("gCTLMiddleLeftycl.geoposZ", &gCTLMiddleLeftycl_geoposZ, &b_gCTLMiddleLeftycl_geoposZ);
   fChain->SetBranchAddress("gCTLMiddleLeftycl.geoposR", &gCTLMiddleLeftycl_geoposR, &b_gCTLMiddleLeftycl_geoposR);
   fChain->SetBranchAddress("gCTLMiddleLeftycl.geoposPhi", &gCTLMiddleLeftycl_geoposPhi, &b_gCTLMiddleLeftycl_geoposPhi);
   fChain->SetBranchAddress("gCTLTopLeftxcl", &gCTLTopLeftxcl_, &b_gCTLTopLeftxcl_);
   fChain->SetBranchAddress("gCTLTopLeftxcl.ngeoch", &gCTLTopLeftxcl_ngeoch, &b_gCTLTopLeftxcl_ngeoch);
   fChain->SetBranchAddress("gCTLTopLeftxcl.geoch", &gCTLTopLeftxcl_geoch, &b_gCTLTopLeftxcl_geoch);
   fChain->SetBranchAddress("gCTLTopLeftxcl.geoX", &gCTLTopLeftxcl_geoX, &b_gCTLTopLeftxcl_geoX);
   fChain->SetBranchAddress("gCTLTopLeftxcl.geoY", &gCTLTopLeftxcl_geoY, &b_gCTLTopLeftxcl_geoY);
   fChain->SetBranchAddress("gCTLTopLeftxcl.geoZ", &gCTLTopLeftxcl_geoZ, &b_gCTLTopLeftxcl_geoZ);
   fChain->SetBranchAddress("gCTLTopLeftxcl.geoR", &gCTLTopLeftxcl_geoR, &b_gCTLTopLeftxcl_geoR);
   fChain->SetBranchAddress("gCTLTopLeftxcl.geoPhi", &gCTLTopLeftxcl_geoPhi, &b_gCTLTopLeftxcl_geoPhi);
   fChain->SetBranchAddress("gCTLTopLeftxcl.geoposch", &gCTLTopLeftxcl_geoposch, &b_gCTLTopLeftxcl_geoposch);
   fChain->SetBranchAddress("gCTLTopLeftxcl.geoposX", &gCTLTopLeftxcl_geoposX, &b_gCTLTopLeftxcl_geoposX);
   fChain->SetBranchAddress("gCTLTopLeftxcl.geoposY", &gCTLTopLeftxcl_geoposY, &b_gCTLTopLeftxcl_geoposY);
   fChain->SetBranchAddress("gCTLTopLeftxcl.geoposZ", &gCTLTopLeftxcl_geoposZ, &b_gCTLTopLeftxcl_geoposZ);
   fChain->SetBranchAddress("gCTLTopLeftxcl.geoposR", &gCTLTopLeftxcl_geoposR, &b_gCTLTopLeftxcl_geoposR);
   fChain->SetBranchAddress("gCTLTopLeftxcl.geoposPhi", &gCTLTopLeftxcl_geoposPhi, &b_gCTLTopLeftxcl_geoposPhi);
   fChain->SetBranchAddress("gCTLTopLeftycl", &gCTLTopLeftycl_, &b_gCTLTopLeftycl_);
   fChain->SetBranchAddress("gCTLTopLeftycl.ngeoch", &gCTLTopLeftycl_ngeoch, &b_gCTLTopLeftycl_ngeoch);
   fChain->SetBranchAddress("gCTLTopLeftycl.geoch", &gCTLTopLeftycl_geoch, &b_gCTLTopLeftycl_geoch);
   fChain->SetBranchAddress("gCTLTopLeftycl.geoX", &gCTLTopLeftycl_geoX, &b_gCTLTopLeftycl_geoX);
   fChain->SetBranchAddress("gCTLTopLeftycl.geoY", &gCTLTopLeftycl_geoY, &b_gCTLTopLeftycl_geoY);
   fChain->SetBranchAddress("gCTLTopLeftycl.geoZ", &gCTLTopLeftycl_geoZ, &b_gCTLTopLeftycl_geoZ);
   fChain->SetBranchAddress("gCTLTopLeftycl.geoR", &gCTLTopLeftycl_geoR, &b_gCTLTopLeftycl_geoR);
   fChain->SetBranchAddress("gCTLTopLeftycl.geoPhi", &gCTLTopLeftycl_geoPhi, &b_gCTLTopLeftycl_geoPhi);
   fChain->SetBranchAddress("gCTLTopLeftycl.geoposch", &gCTLTopLeftycl_geoposch, &b_gCTLTopLeftycl_geoposch);
   fChain->SetBranchAddress("gCTLTopLeftycl.geoposX", &gCTLTopLeftycl_geoposX, &b_gCTLTopLeftycl_geoposX);
   fChain->SetBranchAddress("gCTLTopLeftycl.geoposY", &gCTLTopLeftycl_geoposY, &b_gCTLTopLeftycl_geoposY);
   fChain->SetBranchAddress("gCTLTopLeftycl.geoposZ", &gCTLTopLeftycl_geoposZ, &b_gCTLTopLeftycl_geoposZ);
   fChain->SetBranchAddress("gCTLTopLeftycl.geoposR", &gCTLTopLeftycl_geoposR, &b_gCTLTopLeftycl_geoposR);
   fChain->SetBranchAddress("gCTLTopLeftycl.geoposPhi", &gCTLTopLeftycl_geoposPhi, &b_gCTLTopLeftycl_geoposPhi);
   fChain->SetBranchAddress("gCTLTopMiddlexcl", &gCTLTopMiddlexcl_, &b_gCTLTopMiddlexcl_);
   fChain->SetBranchAddress("gCTLTopMiddlexcl.ngeoch", &gCTLTopMiddlexcl_ngeoch, &b_gCTLTopMiddlexcl_ngeoch);
   fChain->SetBranchAddress("gCTLTopMiddlexcl.geoch", &gCTLTopMiddlexcl_geoch, &b_gCTLTopMiddlexcl_geoch);
   fChain->SetBranchAddress("gCTLTopMiddlexcl.geoX", &gCTLTopMiddlexcl_geoX, &b_gCTLTopMiddlexcl_geoX);
   fChain->SetBranchAddress("gCTLTopMiddlexcl.geoY", &gCTLTopMiddlexcl_geoY, &b_gCTLTopMiddlexcl_geoY);
   fChain->SetBranchAddress("gCTLTopMiddlexcl.geoZ", &gCTLTopMiddlexcl_geoZ, &b_gCTLTopMiddlexcl_geoZ);
   fChain->SetBranchAddress("gCTLTopMiddlexcl.geoR", &gCTLTopMiddlexcl_geoR, &b_gCTLTopMiddlexcl_geoR);
   fChain->SetBranchAddress("gCTLTopMiddlexcl.geoPhi", &gCTLTopMiddlexcl_geoPhi, &b_gCTLTopMiddlexcl_geoPhi);
   fChain->SetBranchAddress("gCTLTopMiddlexcl.geoposch", &gCTLTopMiddlexcl_geoposch, &b_gCTLTopMiddlexcl_geoposch);
   fChain->SetBranchAddress("gCTLTopMiddlexcl.geoposX", &gCTLTopMiddlexcl_geoposX, &b_gCTLTopMiddlexcl_geoposX);
   fChain->SetBranchAddress("gCTLTopMiddlexcl.geoposY", &gCTLTopMiddlexcl_geoposY, &b_gCTLTopMiddlexcl_geoposY);
   fChain->SetBranchAddress("gCTLTopMiddlexcl.geoposZ", &gCTLTopMiddlexcl_geoposZ, &b_gCTLTopMiddlexcl_geoposZ);
   fChain->SetBranchAddress("gCTLTopMiddlexcl.geoposR", &gCTLTopMiddlexcl_geoposR, &b_gCTLTopMiddlexcl_geoposR);
   fChain->SetBranchAddress("gCTLTopMiddlexcl.geoposPhi", &gCTLTopMiddlexcl_geoposPhi, &b_gCTLTopMiddlexcl_geoposPhi);
   fChain->SetBranchAddress("gCTLTopRightxcl", &gCTLTopRightxcl_, &b_gCTLTopRightxcl_);
   fChain->SetBranchAddress("gCTLTopRightxcl.ngeoch", &gCTLTopRightxcl_ngeoch, &b_gCTLTopRightxcl_ngeoch);
   fChain->SetBranchAddress("gCTLTopRightxcl.geoch", &gCTLTopRightxcl_geoch, &b_gCTLTopRightxcl_geoch);
   fChain->SetBranchAddress("gCTLTopRightxcl.geoX", &gCTLTopRightxcl_geoX, &b_gCTLTopRightxcl_geoX);
   fChain->SetBranchAddress("gCTLTopRightxcl.geoY", &gCTLTopRightxcl_geoY, &b_gCTLTopRightxcl_geoY);
   fChain->SetBranchAddress("gCTLTopRightxcl.geoZ", &gCTLTopRightxcl_geoZ, &b_gCTLTopRightxcl_geoZ);
   fChain->SetBranchAddress("gCTLTopRightxcl.geoR", &gCTLTopRightxcl_geoR, &b_gCTLTopRightxcl_geoR);
   fChain->SetBranchAddress("gCTLTopRightxcl.geoPhi", &gCTLTopRightxcl_geoPhi, &b_gCTLTopRightxcl_geoPhi);
   fChain->SetBranchAddress("gCTLTopRightxcl.geoposch", &gCTLTopRightxcl_geoposch, &b_gCTLTopRightxcl_geoposch);
   fChain->SetBranchAddress("gCTLTopRightxcl.geoposX", &gCTLTopRightxcl_geoposX, &b_gCTLTopRightxcl_geoposX);
   fChain->SetBranchAddress("gCTLTopRightxcl.geoposY", &gCTLTopRightxcl_geoposY, &b_gCTLTopRightxcl_geoposY);
   fChain->SetBranchAddress("gCTLTopRightxcl.geoposZ", &gCTLTopRightxcl_geoposZ, &b_gCTLTopRightxcl_geoposZ);
   fChain->SetBranchAddress("gCTLTopRightxcl.geoposR", &gCTLTopRightxcl_geoposR, &b_gCTLTopRightxcl_geoposR);
   fChain->SetBranchAddress("gCTLTopRightxcl.geoposPhi", &gCTLTopRightxcl_geoposPhi, &b_gCTLTopRightxcl_geoposPhi);
   fChain->SetBranchAddress("gCTLTopRightycl", &gCTLTopRightycl_, &b_gCTLTopRightycl_);
   fChain->SetBranchAddress("gCTLTopRightycl.ngeoch", &gCTLTopRightycl_ngeoch, &b_gCTLTopRightycl_ngeoch);
   fChain->SetBranchAddress("gCTLTopRightycl.geoch", &gCTLTopRightycl_geoch, &b_gCTLTopRightycl_geoch);
   fChain->SetBranchAddress("gCTLTopRightycl.geoX", &gCTLTopRightycl_geoX, &b_gCTLTopRightycl_geoX);
   fChain->SetBranchAddress("gCTLTopRightycl.geoY", &gCTLTopRightycl_geoY, &b_gCTLTopRightycl_geoY);
   fChain->SetBranchAddress("gCTLTopRightycl.geoZ", &gCTLTopRightycl_geoZ, &b_gCTLTopRightycl_geoZ);
   fChain->SetBranchAddress("gCTLTopRightycl.geoR", &gCTLTopRightycl_geoR, &b_gCTLTopRightycl_geoR);
   fChain->SetBranchAddress("gCTLTopRightycl.geoPhi", &gCTLTopRightycl_geoPhi, &b_gCTLTopRightycl_geoPhi);
   fChain->SetBranchAddress("gCTLTopRightycl.geoposch", &gCTLTopRightycl_geoposch, &b_gCTLTopRightycl_geoposch);
   fChain->SetBranchAddress("gCTLTopRightycl.geoposX", &gCTLTopRightycl_geoposX, &b_gCTLTopRightycl_geoposX);
   fChain->SetBranchAddress("gCTLTopRightycl.geoposY", &gCTLTopRightycl_geoposY, &b_gCTLTopRightycl_geoposY);
   fChain->SetBranchAddress("gCTLTopRightycl.geoposZ", &gCTLTopRightycl_geoposZ, &b_gCTLTopRightycl_geoposZ);
   fChain->SetBranchAddress("gCTLTopRightycl.geoposR", &gCTLTopRightycl_geoposR, &b_gCTLTopRightycl_geoposR);
   fChain->SetBranchAddress("gCTLTopRightycl.geoposPhi", &gCTLTopRightycl_geoposPhi, &b_gCTLTopRightycl_geoposPhi);
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
}

Bool_t rd51_EventBuilder_Class::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef rd51_EventBuilder_Class_cxx
