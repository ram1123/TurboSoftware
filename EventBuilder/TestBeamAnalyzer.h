//
//  TestBeamAnalyzer.h
//  
//
//  Created by Brian L Dorney on 14/10/14.
//
//

#ifndef _TestBeamAnalyzer_h
#define _TestBeamAnalyzer_h

//C++ Includes
#include <algorithm>
#include <cmath>
//#include <ctgmath>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <vector>

//My Includes

//ROOT Includes
#include "TROOT.h"
#include "TAxis.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TFile.h"
#include "TGraphErrors.h"
#include "TH1.h"
#include "TH1F.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TMultiGraph.h"
#include "TPaveText.h"
#include "Rtypes.h"

using namespace std;
//using namespace ROOT;

class TestBeamAnalyzer {
public:
	//Contrustor
	TestBeamAnalyzer();                                     //Default Contrustuctor
    
    //Struct containing TDC info
    struct TDCMeasurements{
        bool fitPerformed;
        
        float nEvt;
        float raw_Mean;
        float raw_MeanErr;
        float raw_RMS;
        float raw_RMSErr;
        
        std::vector<std::map<string, float> > peakInfo;
        
        TF1 *timeResFit;
        TH1F *timeResHisto;
    };
    
    //Structure containing detector info; each RunParam object has a map of these objects!
    struct DetInfo{
        float current;      //Current supplied to HV divider
        float current_sigma;//Current Uncertainty
        
        float eff;          //Efficiency
        float eff_sigma;    //Efficiency Uncertainty
        
        float gain;         //Gain
        float gain_sigma;   //Gain Uncertainty
        
        int icomp;
        int latency;        //Latency
        int pulseLen;       //Length of the Mono-stable pulse
        int thresh;         //Threshold
        
        string name;        //Name of the Detector
        
        TDCMeasurements TDC;
    };
    
    //Comparison operator for std::map<string,X> for non-standard X
    struct cmp_str{
        bool operator()(const string &a, const string &b) const
        {
            return a.compare(b) < 0;
        }
    };
    
    //Comparison operator for std::map<float,X> for non-standard X
    struct cmp_flt{
        bool operator() (const float &a, const float &b) const
        {
            return (a > b);
        }
    };
    
    //Comparison operator for std::map<int,InfoPerLat>
    struct cmp_int{
        bool operator() (const int &a, const int &b) const
        {
            return (a > b);
        }
    };
    
    //Structure containing Run Parameters
    struct RunParam{
        int delay;
        
        int numRun;
        int numEvt;
        
        string beamType;
        string trigMode;
        
        std::map<std::string, DetInfo> detectors;
    };
    
	//Setters - Methods that Set Something
    //------------------------------------------------------------------------------------------------------------------------------------------
	virtual void setFilesEff(string inputFile, string inputFile_LatSpecific);
    virtual void setFilesEff(string inputFile, std::vector<string> inputFile_LatSpecific);
    virtual void setFilesTDC(string inputFile){fileName_TDC_Master = inputFile; return;} //File Format expects tab delimited list, each line should be "<Root File Name> <Channel Mapping File Name>"
    
    //virtual void setRunParams();                                                              //Get's the run parameters for all stored runs
    virtual void setRunParamEff(string input, std::vector<std::pair<float,float> > vec_eff);      //Get's teh run parameters for a specific run
    virtual void setRunParamTDC(string input, std::vector<TH1F*> inputHistos);
    
    virtual void setTDCAutoRangingFit(bool inputOption){ fitTDC_AutoRanging = inputOption; return;}
    virtual void setTDCFitOption(string inputOption){ fitTDC_Option = inputOption; return;}
    virtual void setTDCMapping(string inputFile);
    virtual void setTDCMeasurement(string inputFile);
    virtual void setTDCNoiseThreshold(float inputThresh){ noiseThresh_TDC = inputThresh; return;}
    virtual void setTDCRebinFactor(int input){ rebinFactor_TDC = input; return;}
    
    
	//Getters - Methods that Get Something
    //------------------------------------------------------------------------------------------------------------------------------------------
    virtual int getCyclicMarkerStyle(int input){return ( (input % 4) + 20);};  //Ensures marker style cycles through filled circle, square, triangle, and inverted triangle
    virtual int getCyclicColor(int input);                                  //Ensures color cycles.
    
    virtual string getParsedDetName(string input);
    virtual std::vector<std::string> getParsedFileName(string input);       //for an underscore delimited string input it returns a vector of strings in between the underscores.
    
    RunParam getRun(string input);
    
    virtual std::string getString(int input);       //Converts input into string data type using stringstream
    virtual std::string getString(float input);     //As Above
    
	//Analyzers
    //------------------------------------------------------------------------------------------------------------------------------------------
    virtual void analyzeRunsEff();
    virtual void analyzeRunsTDC();
    
    //Makers
    //------------------------------------------------------------------------------------------------------------------------------------------
    virtual void makeDetLogEff();
    virtual void makeDetLogTDC();
    
    virtual void makeHistogramsEff();
    virtual void makeHistogramsEff(string input, string option);
    
    //virtual void makeHistogramsTDC();
    virtual void makeHistogramsTDC(string input, string option);
    
    //Misc
    //------------------------------------------------------------------------------------------------------------------------------------------
    virtual void recursivePeakFinder(std::map<string,float> &peakInfo, TH1 *histo, bool shiftRight);
    
    //Write Root Files
    //------------------------------------------------------------------------------------------------------------------------------------------
    virtual void writeEffHistograms2File(string input, string option);
    
private:
    
	//Data Members
    bool detNamesSet;
    bool fitTDC_AutoRanging;
    bool meas_TDC_ClockScan;
    bool meas_TDC_TimeRes;
    
    float noiseThresh_TDC;
    
    int rebinFactor_TDC;
    
    std::map<int,string> chanMap_TDC; //Map of the TDC Channels
    
    string fileName_Eff_Master;
    string fileName_TDC_Master;
    string fitTDC_Option;
    
    string peakKey_Delta;   //Key For peakInfo Maps Referencing Peak "Delta"
    string peakKey_Int;     //Key For peakInfo Maps Referencing Peak "Integral"
    string peakKey_LwrBd;   //Key For peakInfo Maps Referencing Peak "LowerBound"
    string peakKey_Pos;     //Key For peakInfo Maps Referencing Peak "Position"
    string peakKey_PosTime; //Key for peakInfo Maps Referencing Peak "TemporalPos"
    string peakKey_UprBd;   //Key for peakInfo Maps Referencing Peak "UpperBound"
    
    std::vector<string> files_Eff_LatSpecific;
    
    std::vector<string> vec_detNames;                   //Vector of the names of the detectors under study
    std::vector<RunParam> vec_RunParam;                 //Vector of Run Parameters for a Given Latency
    std::vector<std::vector<RunParam> > vec_AllRunParams; //Vector of all Runs, all Latencies
    
    //Parameter Types Accepted
    struct ParamType{
        string beam_el, beam_mu, beam_pi;
        string delay;
        string evt1, evt2;
        string IComp1, IComp2;
        string lat;
        string MSPL;
        string point;
        string run;
        string TDC;
        string TDC_ClockScan;
        string TDC_Run;
        string TDC_TimeRes;
        string thresh;
        string trigMode_Async1, trigMode_Async2;
        string trigMode_Sync1, trigMode_Sync2;
        string microAmps;
    } paramType;
    
    //Container Storing Relevant Info for each delay value
    struct InfoPerDelay{ //struct InforPerDelay
        float nEvt;         //Integral Considered of Histogram Taken at this delay
        
        int latency;
        int pulseLen;
        int run_final;
        int run_initial;
        int thresh;
        
        string beamType;
        
        vector<float> currScan;
        vector<float> effs;
        vector<float> sigma_effs;
        vector<bool> vec_fitPerformed;
        vector<float> vec_rawRMS;
        vector<float> vec_rawRMSErr;    //Error on the Numeric Estimation of the RMS
        vector<float> vec_rawMeans;
        vector<float> vec_rawMeansErr;  //Error on the Numeric Estimation of the Mean (different from RMS and std. dev.)
        vector<float> vec_totalTrigs;
        
        vector<vector<std::map<string, float> > > vec_allPeakInfo;
        
        //Root Members
        TCanvas *canvas_MaxTrigEff_v_Curr;
        
        TGraphErrors *graph_MaxTrigEff_v_Curr;
        
        TLatex *texInfo_run;
        TLatex *texInfo_beam;
        TLatex *texInfo_pulseLen;
        TLatex *texInfo_delay;
        TLatex *texInfo_thresh;
        TLatex *texInfo_lat;
        
        vector<TF1*> vec_timeResFits;
        vector<TH1F*> vec_timeResHistos;        //Fitted Histograms
        vector<TH1F*> vec_timeResHistoOverFits;  //Ratio of Histogram Divided by Fit at Bin Midpoint
    }; //End struct InforPerDelay
    
    //Container Storing Relevant info for each latency value
    struct InfoPerLat{ //struct InfoPerLat
        int delay;
        int pulseLen;
        int run_final;
        int run_initial;
        int thresh;
        
        string beamType;
        
        vector<float> currScan;
        vector<float> effs;
        vector<float> sigma_effs;
        vector<float> vec_rawRMS;
        vector<float> vec_rawMeans;
        vector<float> vec_totalTrigs;
        
        vector<TF1*> vec_timeResFits;
        
        vector<vector<std::map<string, float> > > vec_allPeakInfo;
        
        //Root Members
        TGraphErrors *graph_DetEff_v_Curr;
        
        TCanvas *canvas_DetEff_v_Curr;
        
        TLatex *texInfo_beam;
        TLatex *texInfo_delay;
        TLatex *texInfo_lat;
        TLatex *texInfo_pulseLen;
        TLatex *texInfo_run;
        TLatex *texInfo_thresh;
        
        TLegend *leg_Info;
    }; //End struct InfoPerLat
    
    //Container Storing Relevant Info for each Detector
    struct DetResults{
        bool infoMatch_Lat;     //Flag that evaluates to False if delay, beamType, or pulseLen are not the same for each run considered
        bool infoMatch_DLY;     //Flag that evaluates to False if latency, beamType or pulseLen are not the same for each run considered
        
        float max_eff;      //Maximum Efficiency
        
        int delay;
        int latAtMaxEff;    //Latency Value max_eff is at
        int pulseLen;
        int run_final;
        int run_initial;
        int thresh;
        
        string beamType;
        
        std::map<int,InfoPerDelay,cmp_int> Scan_DLY;
        std::map<int,InfoPerLat,cmp_int> Scan_Lat;
        
        TGraphErrors *graph_MaxTrigEff_v_Delay;
        TGraphErrors *graph_RMS_TimeRes_v_Curr; //Time Resolution Calculated from Histogram RMS
        TGraphErrors *graph_Fit_TimeRes_v_Curr; //Time Resolution Calculated from Gaussian Fits
        TGraphErrors *graph_Fit_normChi2_v_Curr;//Normalized Chi^2 value for each Gaussian Fit
        
        TCanvas *canvas_DetEff_v_Curr;
        TCanvas *canvas_MaxTrigEff_v_Delay;
        TCanvas *canvas_Fit_normChi2_v_Curr;
        TCanvas *canvas_Fit_TimeRes_v_Curr;
        TCanvas *canvas_FitnRMS_TimeRes_v_Curr;
        TCanvas *canvas_RMS_TimeRes_v_Curr;
        
        TLatex *texInfo_beam;
        TLatex *texInfo_delay;
        TLatex *texInfo_lat;
        TLatex *texInfo_pulseLen;
        TLatex *texInfo_name;
        TLatex *texInfo_run;
        TLatex *texInfo_thresh;
        
        TLegend *leg_Info;
        
        TMultiGraph *mGraph_AllLatPlots;
    }; //End struct DetResults
    
    std::map<string,DetResults,cmp_str> results;
    
    struct ComparisonResults{
        bool infoMatch_Lat;     //Flag that evaluates to False if delay, beamType, or pulseLen are not the same for each curve considered
        bool infoMatch_DLY;     //Flag that evaluates to False if latency, beamType, or pulseLen are not the same for each curve considered
        
        int delay;
        int pulseLen;
        int run_final;
        int run_initial;
        int thresh;
        
        string beamType;
        
        //TCanvas's
        TCanvas *canvas_AllDet_DetEff_v_Curr;   //Comparison of the Efficiency Curves from All Detectors
        TCanvas *canvas_AllDet_MaxTrigEff_v_Curr;
        TCanvas *canvas_AllDet_MaxTrigEff_v_Delay;
        TCanvas *canvas_AllDet_TimeResFit_v_Curr;
        TCanvas *canvas_AllDet_TimeResRMS_v_Curr;
        
        map<int, map<float, TCanvas*, cmp_flt>, cmp_int > map_canvas_AllDet_ClkCyl;
        
        //TDirectory's
        map<int, map<float,TDirectory*, cmp_flt>, cmp_int > map_dir_Curr_Parent_DLY;
        map<int, TDirectory*, cmp_int> map_dir_DLY_Parent_Comp;
        
        //TGraph's
        
        //TH1's
        
        //TLatex's
        TLatex *texInfo_beam;
        TLatex *texInfo_delay;
        TLatex *texInfo_pulseLen;
        TLatex *texInfo_run;
        TLatex *texInfo_thresh;
        
        //TLegend's
        TLegend *leg_AllDet_DetEff;
        TLegend *leg_AllDet_MaxTrigEff_v_Curr;
        TLegend *leg_AllDet_MaxTrigEff_v_Delay;
        TLegend *leg_AllDet_TimeRes;
        
        map<int, TLegend*, cmp_int> map_leg_AllDet_ClkCyl;
        
        //TMultiGraph's
        TMultiGraph *mGraph_AllDet_DetEff_v_Curr;
        TMultiGraph *mGraph_AllDet_MaxTrigEff_v_Curr;
        TMultiGraph *mGraph_AllDet_MaxTrigEff_v_Delay;
        TMultiGraph *mGraph_AllDet_TimeResFit_v_Curr;
        TMultiGraph *mGraph_AllDet_TimeResRMS_v_Curr;
    } comparison;
}; //End Class Declaration TestBeamAnalyzer

#endif
