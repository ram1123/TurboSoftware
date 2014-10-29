//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Aug  4 15:29:16 2010 by ROOT version 5.26/00b
// from TTree rd51tb/RD51 test beam
// found on file: Events_built.root
//////////////////////////////////////////////////////////

#ifndef rd51_TrackFinder_h
#define rd51_TrackFinder_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TApplication.h>
#include <TSelector.h>
#include <TClonesArray.h>
#include <TF3.h>
#include <TH3.h>
#include <string>
#include <map>
#include "rd51_EventBuilder_Class.h"
#include "Loaders/LoaderSettings_TrackFinder.hpp"
#include "Loaders/LoaderOffset.hpp"
#include "Clustering/DataArray_T.hpp"
#include "Clustering/GeoDataArray_T.hpp"
#include "Utilities/ColoredMessages.hpp"



class rd51_TrackFinder : public rd51_EventBuilder_Class {
public :
  
  rd51_TrackFinder(TTree * /*tree*/ =0)
    : trackfinderfile(0), trackertree(0), LoaderSettings(0), rd51_TrackFinder_LoaderOffset(0)  
  { }
  
  virtual ~rd51_TrackFinder() { }
  
  virtual void    Begin(TTree *tree);
  virtual Bool_t  Process(Long64_t entry);
  virtual void    Terminate();

  string rd51_TrackFinder_TrackerOffsetFile;
  TString settingfilename;
  TString trackfinderfilename;
  TFile* trackfinderfile;
  TTree* trackertree;
  LoaderSettings_TrackFinder* LoaderSettings;
  LoaderOffset* rd51_TrackFinder_LoaderOffset;

  int ntotalentries;

  int rd51_TrackFinder_Verbose;
  int rd51_TrackFinder_TrackVerbose;
  int rd51_TrackFinder_OffsetVerbose;

//------------------------------------------------------------
// Trakers:
//------------------------------------------------------------

  // X Projection
  Int_t g1xNCl;
  Int_t g2xNCl;
  Int_t g3xNCl;
  Int_t g4xNCl;
   
  // Hit multiplicity calculation and related variables
  int g1xhm;
  int g2xhm;
  int g3xhm;
  int g4xhm;

  // Y Projection
  Int_t g1yNCl;
  Int_t g2yNCl;
  Int_t g3yNCl;
  Int_t g4yNCl;

  // Hit multiplicity calculation and related variables
  int g1yhm;
  int g2yhm;
  int g3yhm;
  int g4yhm;
//------------------------------------------------------------

//------------------------------------------------------------
// Offset Loaded Before Tracking
// -----------------------------------------------------------
        double deltax1;
        double deltax2;
        double deltax3;
        double deltax4;

        double deltay1;
        double deltay2;
        double deltay3;
        double deltay4;

        double deltaz1;
        double deltaz2;
        double deltaz3;
        double deltaz4;
// -----------------------------------------------------------
      
   
//------------------------------------------------------------
// Tracks 
//------------------------------------------------------------

  //Track recostruction algorithm and related variables

  // X Projection
  int FindTracksXProj(Int_t verbose=0);
  static const Int_t maxnumoftracks = 1;
  int ntotalXtracks;
  int NXTracks;
  TClonesArray *XTracksVect;  // for the moment only one track
  Double32_t residualX[5]; // element 1,2,3 and 4 is the residual of each
  // station, while element 0 is the SQUARED
  // ROOT OF THE SQUARED SUM of them. Be
  // careful: it is not the RMS, because it is
  // not divided by the number of elements!
   
  // Y Projection
  int FindTracksYProj(Int_t verbose=0);
  int ntotalYtracks;
  int NYTracks;
  TClonesArray *YTracksVect;  // for the moment only one track
  Double32_t residualY[5]; // element 1,2,3 and 4 is the residual of each
  // station, while element 0 is the SQUARED
  // ROOT OF THE SQUARED SUM of them. Be
  // careful: it is not the RMS, because it is
  // not divided by the number of elements
//------------------------------------------------------------


//     std::map<std::string,double> options_map; 
//     int LoadOptions(TString options);

  ClassDef(rd51_TrackFinder,0);
};

#endif

#ifdef rd51_TrackFinder_cxx

#endif // #ifdef rd51_TrackFinder_cxx
