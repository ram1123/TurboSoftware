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
    
    //Structure containing detector info; each RunParam object has a map of these objects!
    struct DetInfo{
        float current;      //Current supplied to HV divider
        float current_sigma;//Current Uncertainty
        
        float eff;          //Efficiency
        float eff_sigma;    //Efficiency Uncertainty
        
        float gain;         //Gain
        float gain_sigma;   //Gain Uncertainty
        
        int latency;        //Latency
        int pulseLen;       //Length of the Mono-stable pulse
        int thresh;         //Threshold
        
        string name;        //Name of the Detector
    };
    
    //Comparison operator for std::map<string,DetInfo> and std::map<string,DetResults>
    struct cmp_str{
        bool operator()(const string &a, const string &b) const
        {
            return a.length() > b.length();
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
        
        std::map<std::string, DetInfo> detectors;
    };
    
	//Setters - Methods that Set Something
    //------------------------------------------------------------------------------------------------------------------------------------------
	virtual void setEffFiles(string inputFile, string inputFile_LatSpecific);
    virtual void setEffFiles(string inputFile, std::vector<string> inputFile_LatSpecific);
    
    virtual void setTDCFiles(string inputFile){fileName_TDC_Master = inputFile; return;} //File Format expects tab delimited list, each line should be "<Root File Name> <Channel Mapping File Name>"
    
    virtual void setTDCMapping(string inputFile);
    
    //virtual void setRunParams();                                                              //Get's the run parameters for all stored runs
    virtual void setRunParam(string input, std::vector<std::pair<float,float> > vec_eff);      //Get's teh run parameters for a specific run
    
    //virtual void setCanvasStyle(TCanvas &canvas);
    
	//Getters - Methods that Get Something
    //------------------------------------------------------------------------------------------------------------------------------------------
    virtual std::string getString(int input);       //Converts input into string data type using stringstream
    virtual std::string getString(float input);     //As Above
    
    virtual int getCyclicMarkerStyle(int input){return (input % 4) + 20;};  //Ensures marker style cycles through filled circle, square, triangle, and inverted triangle
    virtual int getCyclicColor(int input);                                  //Ensures color cycles.
    
	//Analyzers
    //------------------------------------------------------------------------------------------------------------------------------------------
    virtual void analyzeEffRuns();
    virtual void analyzeTDCRuns();
    
    //Makers
    //------------------------------------------------------------------------------------------------------------------------------------------
    virtual void makeDetLog();
    
    virtual void makeEffHistograms();
    virtual void makeEffHistograms(string input, string option);
    
    //Misc
    //------------------------------------------------------------------------------------------------------------------------------------------
    virtual void recursivePeakFinder(std::map<string,float> &peakInfo, TH1 *histo, bool shiftRight);
    
    //Write Root Files
    //------------------------------------------------------------------------------------------------------------------------------------------
    virtual void writeEffHistograms2File(string input, string option);
    
private:
    
	//Data Members
    bool detNamesSet;
    
    std::map<int,string> chanMap_TDC; //Map of the TDC Channels
    
    string fileName_Eff_Master;
    string fileName_TDC_Master;
    
    std::vector<string> files_Eff_LatSpecific;
    
    std::vector<string> vec_detNames;                   //Vector of the names of the detectors under study
    std::vector<RunParam> vec_RunParam;                 //Vector of Run Parameters for a Given Latency
    std::vector<std::vector<RunParam> > vec_AllRunParams; //Vector of all Runs, all Latencies
    
    //Parameter Types Accepted
    struct ParamType{
        string beam_mu, beam_pi, beam_el;
        string delay;
        string evt1, evt2;
        string lat;
        string MSPL;
        string point;
        string run;
        string thresh;
    } paramType;
    
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
        
        TGraphErrors *graph_DetEff_v_Curr;
        
        TCanvas *canvas_DetEff_v_Curr;
        
        TLatex *texInfo_run;
        TLatex *texInfo_beam;
        TLatex *texInfo_pulseLen;
        TLatex *texInfo_delay;
        TLatex *texInfo_thresh;
        TLatex *texInfo_lat;
        
        TLegend *leg_Info;
    }; //End struct InfoPerLat
    
    //Container Storing Relevant Info for each Detector
    struct DetResults{
        bool infoMatch;     //Flag that evaluates to False if delay, beamType, or pulseLen are not the same for each run considered
        
        float max_eff;      //Maximum Efficiency
        
        int delay;
        int latAtMaxEff;    //Latency Value max_eff is at
        int pulseLen;
        int run_final;
        int run_initial;
        
        string beamType;
        
        std::map<int,InfoPerLat,cmp_int> latScan;
        
        TCanvas *canvas_DetEff_v_Curr;
        
        TLatex *texInfo_run;
        TLatex *texInfo_beam;
        TLatex *texInfo_pulseLen;
        TLatex *texInfo_delay;
        TLatex *texInfo_thresh;
        TLatex *texInfo_lat;
        
        TLegend *leg_Info;
        
        TMultiGraph *mGraph_AllLatPlots;
    }; //End struct DetResults
    
    std::map<string,DetResults,cmp_str> results;
    
    struct ComparisonResults{
        bool infoMatch;     //Flag that evaluates to False if delay, beamType, or pulseLen are not the same for each curve considered
        
        int delay;
        int pulseLen;
        int run_final;
        int run_initial;
        
        string beamType;
        
        //TCanvas's
        TCanvas *canvas_AllDet_DetEff_v_Curr;   //Comparison of the Efficiency Curves from All Detectors
        
        //TGraph's
        
        //TLatex's
        TLatex *texInfo_beam;
        TLatex *texInfo_delay;
        TLatex *texInfo_pulseLen;
        TLatex *texInfo_run;
        
        //TLegend's
        TLegend *leg_AllDet_DetEff;
        
        //TMultiGraph's
        TMultiGraph *mGraph_AllDet_DetEff_v_Curr;
    } comparison;
}; //End Class Declaration TestBeamAnalyzer

#endif
