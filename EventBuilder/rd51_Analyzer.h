#ifndef rd51_Analyzer_h
#define rd51_Analyzer_h

#include <stdlib.h>
#include "Riostream.h"
#include <iostream>
#include <string>
#include <TStyle.h>
#include <TROOT.h>
#include "TApplication.h"
#include "TTree.h"
#include "TBranch.h"
#include "TGraphErrors.h"
#include <TVector.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TMath.h>
#include "Class_Reco.h"
#include "Class_Tracker.h"
#include "Loaders/LoaderSettings_Analyzer.hpp"
#include "Loaders/LoaderOffsetAndCoverage_Analyzer.hpp"
#include "Utilities/ColoredMessages.hpp"

class rd51_Analyzer {
    public :
    
    // External Settings
    
    void LoadSettings();
    
    LoaderSettings_Analyzer* rd51analyzer_LoaderSettings;
    //TString rd51analyzer_settingfilename;
    
    string 	rd51analyzer_OffsetFile			;
    int 		rd51analyzer_Verbose			;
    int 		rd51analyzer_EffCalculatorVerbose	;
    int 		rd51analyzer_EnableCoverage		;
    int 		rd51analyzer_Cut_Verbose		;
    int 		rd51analyzer_Cut_Chi2Value              ;
    Float_t 	rd51analyzer_Cut_ResidualValue          ;
    int 		rd51analyzer_Cut_NumberOfTracks         ; 
    bool		rd51analyzer_Cut_SingleXYTrackRequest  	;
    bool         rd51analyzer_EfficiencyRadiusScan       ;
    Float_t        rd51analyzer_EfficiencyRadiusMin        ;
    Float_t        rd51analyzer_EfficiencyRadiusMax        ;
    Float_t        rd51analyzer_EfficiencyRadiusStep       ;
    
    
    
    // Offset
    void LoadOffsetAndCoverage(int verbose);
    
    LoaderOffsetAndCoverage_Analyzer* rd51analyzer_LoaderOffsetAndCoverage;
    
    double *DUT_offsetX      ;
    double *DUT_offsetY      ;
    double *DUT_offsetZ      ;
    double *DUT_trkoffsetX   ;
    double *DUT_trkoffsetY   ;
    double *DUT_MinX         ;
    double *DUT_MaxX         ;
    double *DUT_MinY         ;
    double *DUT_MaxY         ;
    double *DUT_MinR         ;
    double *DUT_MaxR         ;
    double *DUT_MinPhi       ;
    double *DUT_MaxPhi       ;
    double *DUT_effRad       ;
    
    // Reco Classes and Trees
    Class_Reco 		*rd51reco;
    TTree 		*rd51reco_tree;
    
    // Tarcker Classes and Trees
    Class_Tracker 	*rd51tracker;
    TTree 		*rd51tracker_tree;
    
    
    // rd51_Analyzer
    rd51_Analyzer(TString reco_filename, TString tracker_filename, TString analyzer_filename);
    virtual 	 ~rd51_Analyzer() { }
    
    // Event Selection
    bool ProcessTheEntry(int processedentry, int verbose);
    
    // Efficiency Calculator
    int Calc_g3xcl_Eff(int verbose);
    int Calc_g3ycl_Eff(int verbose);
    
    //Efficiency Radius Scan
    void InitializeEfficiencyRadiusScan(int verbose);
    void ProcessEfficiencyRadiusScan(int verbose);
    void DeleteEfficiencyRadiusScan(int verbose);
    
    int ERSSteps;
    
    Float_t                 *ERSRad;
    
    Float_t  g3xcl_ERSEntries;
    Float_t  g3ycl_ERSEntries;
    
    Float_t  *g3xcl_ERSIneff;
    Float_t  *g3ycl_ERSIneff;
    
    Float_t  *g3xcl_ERSErr;
    Float_t  *g3ycl_ERSErr;
    
    TGraphErrors *g3xcl_ERSIneffGraph;
    TGraphErrors *g3ycl_ERSIneffGraph;

    // Histograms
    void HistoDefine(int verbose);
    void HistoWrite(int verbose);
    void HistoDelete(int verbose);
      
    TH1F *hg3xcl_Eff                ;
    TH2F *hg3xcl_XY_Eff             ;
    TH2F *hg3xcl_XY_Ineff           ;
    TH2F *hg3xcl_XY_Noise           ;
    TH1F *hg3xcl_CLS_Eff            ;
    TH1F *hg3xcl_CLS_Noise          ;
    TH1F *hg3xcl_Distance_Eff       ;
    TH1F *hg3xcl_Distance_Noise     ;
    TH1F *hg3xcl_Residual_X         ;
    
    TH1F *hg3ycl_Eff                ;
    TH2F *hg3ycl_XY_Eff             ;
    TH2F *hg3ycl_XY_Ineff           ;
    TH2F *hg3ycl_XY_Noise           ;
    TH1F *hg3ycl_CLS_Eff            ;
    TH1F *hg3ycl_CLS_Noise          ;
    TH1F *hg3ycl_Distance_Eff       ;
    TH1F *hg3ycl_Distance_Noise     ;
    TH1F *hg3ycl_Residual_X         ;

    ClassDef(rd51_Analyzer,1);
};

#endif

#ifdef rd51_Analyzer_cxx

#endif // #ifdef rd51_Analyzer_cxx
