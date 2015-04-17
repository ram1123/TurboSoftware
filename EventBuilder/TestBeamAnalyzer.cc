//
//  TestBeamAnalyzer.cc
//  
//
//  Created by Brian L Dorney on 14/10/14.
//
//

#include "TestBeamAnalyzer.h"

//Constructors
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------

//Default Constructor
TestBeamAnalyzer::TestBeamAnalyzer(){
    //Set Run Settings
    paramType.beam_el       = "El";
    paramType.beam_mu       = "Muon";
    paramType.beam_pi       = "Pion";
    
    paramType.delay         = "DLY";
    
    paramType.evt1          = "k";
    paramType.evt2          = "K";
    
    paramType.IComp1        = "IComp";
    paramType.IComp2        = "ICOMP";
    
    paramType.lat           = "Lat";
    
    paramType.MSPL          = "MSPL";
    
    paramType.point         = "pt";
    
    paramType.run           = "Run";
    
    paramType.TDC           = "TDC";
    paramType.TDC_Run       = "TDCRun";
    paramType.TDC_ClockScan = "ClockScan";
    paramType.TDC_TimeRes   = "TimeRes";
    
    paramType.thresh        = "T";
    
    paramType.microAmps     = "uA";
    
    //Draw fits to efficiency curves?
    drawFit                 = true;
    
    //Flag Detector Names as Not Set
    detNamesSet             = false;
    
    //Type of Measurement for TDC
    meas_TDC_ClockScan      = false;
    meas_TDC_TimeRes        = false;
    
    //Sets the equivalent resistance of the HV Divider
    fREquiv = (1.125e6 + 563e3 + 438e3 + 550e3 + 875e3 + 525e3 + 625e3 );
    
    //Noise Threshold for TDC measurements
    noiseThresh_TDC         = 0.;
    
    //Rebin Factor for TDC Histograms (to Offset finite statistics)
    rebinFactor_TDC         = 1;
    
    //Initialize Fit Setup for Async TDC Fits
    fitEff_Formula          = "(1+exp([0]*(x+[1])))^(-1)";
    fitEff_Option           = "R";
    
    fitTDC_AutoRanging      = false;
    fitTDC_Option           = "R";
    
    //Setup Conversion from VFAT Units to Real Units
    fVFAT_thresh2fC         = 0.08;
    
    //Initialize Key Holders for peakInfo Map
    peakKey_Delta           = "Delta";
    peakKey_Int             = "Integral";
    peakKey_LwrBd           = "LowerBound";
    peakKey_Pos             = "Position";
    peakKey_PosTime         = "TemporalPos";
    peakKey_UprBd           = "UpperBound";
    
    //Intialize Comparison
    comparison.infoMatch_Lat= true;
    comparison.infoMatch_DLY= true;
    
    comparison.run_initial  = 60000;
    comparison.run_final    = 0;
    
    comparison.canvas_AllDet_DetEff_v_Curr = new TCanvas("Plot_AllDet_DetEff_v_Curr","AllDet_DetEff_v_Curr",700,700);
    comparison.canvas_AllDet_DetEff_v_HVDrift = new TCanvas("Plot_AllDet_DetEff_v_HVDrift","AllDet_DetEff_v_HVDrift",700,700);
    
    comparison.canvas_AllDet_MaxTrigEff_v_Curr = new TCanvas("Plot_AllDet_MaxTrigEff_v_Curr","AllDet_MaxTrigEff_v_Curr",700,700);
    comparison.canvas_AllDet_MaxTrigEff_v_Delay = new TCanvas("Plot_AllDet_MaxTrigEff_v_Delay","AllDet_MaxTrigEff_v_Delay",700,700);
    comparison.canvas_AllDet_TimeResFit_v_Curr = new TCanvas("Plot_AllDet_TimeResFit_v_Curr","AllDet_TimeResFit_v_Curr",700,700);
    comparison.canvas_AllDet_TimeResRMS_v_Curr = new TCanvas("Plot_AllDet_TimeResRMS_v_Curr","AllDet_TimeResRMS_v_Curr",700,700);
    
    comparison.texInfo_beam     = new TLatex();  comparison.texInfo_beam->SetTextSize(0.03);
    comparison.texInfo_delay    = new TLatex();  comparison.texInfo_delay->SetTextSize(0.03);
    comparison.texInfo_pulseLen = new TLatex();  comparison.texInfo_pulseLen->SetTextSize(0.03);
    comparison.texInfo_run      = new TLatex();  comparison.texInfo_run->SetTextSize(0.03);
    comparison.texInfo_thresh   = new TLatex();  comparison.texInfo_thresh->SetTextSize(0.03);
    
    comparison.mGraph_AllDet_DetEff_v_Curr = new TMultiGraph("MultiGraph_AllDet_DetEff_v_Curr"," ;Current Supplied to HV Divider #left(#muA#right);Efficiency");
    comparison.mGraph_AllDet_DetEff_v_HVDrift = new TMultiGraph("MultiGraph_AllDet_DetEff_v_HVDrift"," ;HV_{Drift} #left(V#right);Efficiency");
    
    comparison.mGraph_AllDet_MaxTrigEff_v_Curr = new TMultiGraph("MultiGraph_AllDet_MaxTrigEff_v_Curr", " ;Current Supplied to HV Divider #left(#muA#right);Efficiency to Trigger in One Clock Cycle");
    comparison.mGraph_AllDet_MaxTrigEff_v_Delay = new TMultiGraph("MultiGraph_AllDet_MaxTrigEff_v_Delay", " ;Added Delay #left(ns#right);Efficiency to Trigger in One Clock Cycle");
    comparison.mGraph_AllDet_TimeResFit_v_Curr = new TMultiGraph("MultiGraph_AllDet_TimeResFit_v_Curr"," ;Current Supplied to HV Divider #left(#muA#right);Time Resolution #sigma_{#font[12]{t}}^{Fit} #left(ns#right)");
    comparison.mGraph_AllDet_TimeResRMS_v_Curr = new TMultiGraph("MultiGraph_AllDet_TimeResRMS_v_Curr"," ;Current Supplied to HV Divider #left(#muA#right);Time Resolution #sigma_{#font[12]{t}}^{RMS} #left(ns#right)");
} //End Default Constructor

//Setters
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//Sets the name of the text files containing the efficiency values
void TestBeamAnalyzer::setFilesEff(string inputFile, string inputFile_LatSpecific){
    fileName_Eff_Master     = inputFile;
    files_Eff_LatSpecific.push_back(inputFile_LatSpecific);
    return;
} //End setFilesEff

//Sets the name of the text files containing the efficiency values
void TestBeamAnalyzer::setFilesEff(string inputFile, std::vector<string> inputFile_LatSpecific){
    fileName_Eff_Master     = inputFile;
    files_Eff_LatSpecific   = inputFile_LatSpecific;
    return;
} //End setFilesEff

//Given an input string, this returns an initialized Run with all parameters set!
TestBeamAnalyzer::RunParam TestBeamAnalyzer::getRun(string input){
    //Variable Declaration
    bool found_numRun, found_beamType, found_numEvt, found_pulseLen, found_trigMode, found_delay, found_current, found_thresh, found_latency, found_icomp;
    
    DetInfo gem;
    
    float current = 0.;
    
    TestBeamAnalyzer::RunParam ret_Run;
    
    vector<float> vec_current;
    vector<float> vec_thresh;
    
    vector<int> vec_lat;
    vector<int> vec_pulseLen;
    vector<int> vec_icomp;
    
    //Debugging
    //cout<<"TestBeamAnalyzer::getRun - No Fault 0" << endl;
    
    vector<string> vec_params = getParsedFileName(input);
    
    //Initialize
    gem.latency     = -1;
    ret_Run.delay   = -1;
    
    found_numRun = found_beamType = found_numEvt = found_pulseLen = found_trigMode = found_delay = found_current = found_thresh = found_latency = found_icomp = false;
    
    //Debugging
    //cout<<"TestBeamAnalyzer::getRun - No Fault 1" << endl;
    
    //Determine what stored parameters are
    for (unsigned int i=0; i < vec_params.size(); i++) { //Loop Over Identified Parameters
        //Debugging
        //cout<<"vec_params["<<i<<"] = " << vec_params[i]<<endl;
        
        //Evaluate by size of vec_params[i]
        if (vec_params[i].length() >= 10 ) { //Case: length >= 10 and not considered above
            //TDC Run Number
            if( vec_params[i].compare(0,6,paramType.TDC_Run) == 0 ){                                                            //TDC Run Number
                if( vec_params[i].compare(6,2,"00") == 0 ){
                    ret_Run.numRun = atoi( (vec_params[i].substr(8,2)).c_str() );
                }
                else if( vec_params[i].compare(6,1,"0") == 0 ){
                    ret_Run.numRun = atoi( (vec_params[i].substr(7,3)).c_str() );
                }
                else{
                    ret_Run.numRun = atoi( (vec_params[i].substr(6,4)).c_str() );
                }
                
                found_numRun = true;
            } //End Case: TDC Run Number
        } //End Case: length >= 10 and not considered above
        else if (vec_params[i].length() >= 8 ) { //Case: length >= 8 and not considered above
            if(vec_params[i].compare(0,5,paramType.IComp1) == 0 || vec_params[i].compare(0,5,paramType.IComp2) == 0){ //Case: IComp (3-Digit)
                vec_icomp.push_back( atoi(vec_params[i].substr(5,3).c_str() ) );
                
                found_icomp = true;
            } //End Case: IComp (3-Digit)
        } //End Case: length >= 8 and not considered above
        else if (vec_params[i].length() >= 7 ) { //Case: length >= 7 and not considered above
            //Run Number
            if( vec_params[i].compare(0,3,paramType.run) == 0 ){                                                            //Run Number
                if( vec_params[i].compare(3,1,"00") == 0 ){
                    ret_Run.numRun = atoi( (vec_params[i].substr(5,2)).c_str() );
                }
                else if( vec_params[i].compare(3,1,"0") == 0 ){
                    ret_Run.numRun = atoi( (vec_params[i].substr(4,3)).c_str() );
                }
                else{
                    ret_Run.numRun = atoi( (vec_params[i].substr(3,4)).c_str() );
                }
                
                found_numRun = true;
            } //End Case: Run Number
            else if( vec_params[i].compare(0,3,paramType.delay) == 0 ){                                                     //Delay
                ret_Run.delay = atoi( (vec_params[i].substr(3,2)).c_str() );
                
                found_delay = true;
            } //End Case: Delay
            else if(vec_params[i].compare(0,5,paramType.IComp1) == 0 || vec_params[i].compare(0,5,paramType.IComp2) == 0){ //Case: IComp (2-Digit)
                vec_icomp.push_back( atoi(vec_params[i].substr(5,2).c_str() ) );
                
                found_icomp = true;
            } //End Case: IComp (2-Digit)
        } //End Case: length >= 7 and not considered above
        else if (vec_params[i].length() >= 6 ) {
            if(vec_params[i].compare(3,2,paramType.point)==0 ){ //Case: Current (user uses XXXptXuA format)
                current = atof( (vec_params[i].substr(0,3)).c_str() )
                + atof( (vec_params[i].substr(5,1)).c_str() ) / 10.;
                
                vec_current.push_back(current);
                
                found_current = true;
            } ///End Case: Current (user uses XXXptXuA format)
        } //End Case: length >= 6 and not considered above
        else if (vec_params[i].length() >= 5 ) { //Case: length >= 5 and not considered above
            if( vec_params[i].compare(0,4,paramType.MSPL) == 0 ){                                                      //Mono-stable Pulse Length
                vec_pulseLen.push_back( atoi( (vec_params[i].substr(4,1)).c_str() ) );
                
                found_pulseLen = true;
            } //End Case: Mono-stable Pulse Length
            else if( vec_params[i].compare(0,5,paramType.trigMode_Async1) == 0 || vec_params[i].compare(0,5,paramType.trigMode_Async2) == 0 ){ //Case: Trigger Mode - Async
                ret_Run.trigMode = vec_params[i];
                
                found_trigMode = true;
            } //End Case: Trigger Mode - Async
            else if(vec_params[i].compare(3,2,paramType.microAmps)==0){ //Case: Current (user used XXXuA format)
                current = atof( (vec_params[i].substr(0,3)).c_str() );
                
                vec_current.push_back(current);
                
                found_current = true;
            } ///End Case: Case: Current (user used XXXuA format)
            else if( vec_params[i].compare(0,3,paramType.lat) == 0 ){                                                       //Latency
                vec_lat.push_back( atoi( (vec_params[i].substr(3,vec_params[i].length()-3)).c_str() ) );
                
                found_latency = true;
            } //End Case: Latency
            else if( vec_params[i].compare(0,4,paramType.beam_mu) == 0 ){ //Case: Beam Type - Muon
                ret_Run.beamType = vec_params[i];
                
                found_beamType = true;
            } //End Case: Beam Type - Muon
            else if( vec_params[i].compare(0,4,paramType.beam_pi) == 0 ){ //Case: Beam Type - Pion
                ret_Run.beamType = vec_params[i];
                
                found_beamType = true;
            } //End Case: Beam Type - Pion
        } //End Case: length >= 5 and not considered above
        else if (vec_params[i].length() >= 4 ) { //Case: length >= 4 and not considered above
            if( vec_params[i].compare(0,4,paramType.beam_mu) == 0 ){ //Case: Beam Type - Muon
                ret_Run.beamType = vec_params[i];
                
                found_beamType = true;
            } //End Case: Beam Type - Muon
            else if( vec_params[i].compare(0,4,paramType.beam_pi) == 0 ){ //Case: Beam Type - Pion
                ret_Run.beamType = vec_params[i];
                
                found_beamType = true;
            } //End Case: Beam Type - Pion
            else if( vec_params[i].compare(0,4,paramType.trigMode_Sync1) == 0 || vec_params[i].compare(0,4,paramType.trigMode_Sync2) == 0 ){ //Case: Trigger Mode - Sync
                ret_Run.trigMode = vec_params[i];
                
                found_trigMode = true;
            } //End Case: Trigger Mode - Sync
            else if(vec_params[i].compare(3,1,paramType.evt1) == 0 || vec_params[i].compare(3,1,paramType.evt2) == 0){    //Event Number (3-Digit)
                ret_Run.numEvt = atoi( (vec_params[i].substr(0,3)).c_str() ) * 1000;
                
                found_numEvt = true;
            } //End Case: Event Number (3-Digit)
        } //End Case: length >= 4 and not considered above
        else if (vec_params[i].length() >= 3 ) { //Case: length >= 3 and not considered above
            if(vec_params[i].compare(2,1,paramType.evt1) == 0 || vec_params[i].compare(2,1,paramType.evt2) == 0){    //Event Number (2-Digit)
                ret_Run.numEvt = atoi( (vec_params[i].substr(0,2)).c_str() ) * 1000;
                
                found_numEvt = true;
            } //End Case: Event Number (2-Digit)
            else if( vec_params[i].compare(0,1,paramType.thresh)==0 && !(vec_params[i].compare(0,3,paramType.TDC)==0) ){ //Case: Threshold (2-Digit)
                vec_thresh.push_back( atof( (vec_params[i].substr(1,vec_params[i].length()-1)).c_str() ) * fVFAT_thresh2fC);
                
                found_thresh = true;
            } //End Case: Threshold (2-Digit)
        } //End Case: length >= 3 and not considered above
        else if (vec_params[i].length() >= 2 ) { //Case: length >= 2 and not considered above
            if( vec_params[i].compare(0,2,paramType.beam_el) == 0 ){ //Case: Beam Type - Electron
                ret_Run.beamType = "Electron";
                
                found_beamType = true;
            } //End Case: Beam Type - Electron
            else if( vec_params[i].compare(0,1,paramType.thresh)==0 && !(vec_params[i].compare(0,3,paramType.TDC.substr(0,2))==0) ){ //Case: Threshold (1-Digit)
                vec_thresh.push_back( atof( (vec_params[i].substr(1,1)).c_str() ) * fVFAT_thresh2fC );
                
                found_thresh = true;
            } //End Case: Threshold (1-Digit)
            if(vec_params[i].compare(1,1,paramType.evt1) == 0 || vec_params[i].compare(1,1,paramType.evt2) == 0){    //Event Number (2-Digit)
                ret_Run.numEvt = atoi( (vec_params[i].substr(0,1)).c_str() ) * 1000;
                
                found_numEvt = true;
            } //End Case: Event Number (2-Digit)
        } //End Case: length >= 2 and not considered above
        else { //Case: Unrecognized Parameter
            //cout<<"Case: Unknown"<<endl;
            //cout<<"Parameter = " << param << " Not Recognized" << endl;
        } //End Case: Unrecognized Parameter
    } //End Loop Over Identified Parameters
    
    //Ask the user for unfound parameters
    //if (!found_beamType) {<#statements#>}
    
    //Debugging
    //cout<<"TestBeamAnalyzer::getRun - No Fault 2" << endl;
    
    //cout<<"vec_current.size() = " << vec_current.size() << endl;
    //cout<<"vec_lat.size() = " << vec_lat.size() << endl;
    //cout<<"vec_pulseLen.size() = " << vec_pulseLen.size() << endl;
    //cout<<"vec_thresh.size() = " << vec_thresh.size() << endl;
    
    //Assign the detector specific parameters to the detector structure map
    //It is understood that vec_detNames has the same ordering as what appears in the file name
    //If the size of vec_detNames and the vectors containing the identified parameters are not the same
    //then all detectors will be assigned the same parameters (at index 0) for a given parameter.
    //i.e. if vec_thresh.size() == 2 and vec_detNames == 3 then all detectors are assigned vec_thresh[0]
    for(unsigned int i=0; i<vec_detNames.size(); i++){ //Loop Over vec_detNames
        //Debugging
        //cout<<"======================================================="<<endl;
        //cout<<"vec_detNames["<<i<<"] = " << vec_detNames[i] << endl;
        
        //Debugging
        //cout<<"TestBeamAnalyzer::getRun - No Fault 2_a" << endl;
        
        //Set the values
        if(vec_detNames.size() == vec_current.size() ){ gem.current     = vec_current[i]; }
        else{                                           gem.current     = vec_current[0]; }
        
        if(vec_icomp.size() == 0 ){                     gem.icomp = -1;}
        else if(vec_detNames.size()==vec_icomp.size()){ gem.icomp = vec_icomp[i];}
        else{                                           gem.icomp = vec_icomp[0];}
        
        //Debugging
        //cout<<"TestBeamAnalyzer::getRun - No Fault 2_b" << endl;
        if(vec_lat.size() == 0){                        gem.latency     = -1;}
        else if(vec_detNames.size() == vec_lat.size() ){gem.latency     = vec_lat[i]; }
        else{                                           gem.latency     = vec_lat[0]; }
        
        //Debugging
        //cout<<"TestBeamAnalyzer::getRun - No Fault 2_c" << endl;
        
        if(vec_detNames.size() == vec_pulseLen.size() ){gem.pulseLen    = vec_pulseLen[i]; }
        else{                                           gem.pulseLen    = vec_pulseLen[0]; }
        
        //Debugging
        //cout<<"TestBeamAnalyzer::getRun - No Fault 2_d" << endl;
        
        if(vec_thresh.size() == 0){                     gem.thresh      = -1;}
        else if(vec_detNames.size()==vec_thresh.size()){gem.thresh      = vec_thresh[i]; }
        else{                                           gem.thresh      = vec_thresh[0]; }
        
        //Debugging
        //cout<<"TestBeamAnalyzer::getRun - No Fault 2_e" << endl;
        
        //Set the name
        gem.name        = vec_detNames[i];
        
        //Debugging
        //cout<<"TestBeamAnalyzer::getRun - No Fault 2_f" << endl;
        
        ret_Run.detectors[vec_detNames[i]] = gem;
    } //End Loop Over vec_detNames
    
    //Debugging
    //cout<<"TestBeamAnalyzer::getRun - No Fault End" << endl;
    
    return ret_Run;
} //End TestBeamAnalyzer::RunParam()

//This method scans an input string to determine the parameters of the run.
//The string is the file name of the data
//vec_eff is a vector of pairs where the first member of the pair is the efficiency value and the second member is the statistical uncertainty
void TestBeamAnalyzer::setRunParamEff(string input, std::vector<std::pair<float,float> > vec_eff){
    //Variable Declaration
    DetInfo gem;
    
    TestBeamAnalyzer::RunParam specificRunParam = getRun(input);
    
    //Debugging
    //cout<<"TestBeamAnalyzer::setRunParamEff - No Fault 2" << endl;
    //cout<<"TestBeamAnalyzer::setRunParamEff - specificRunParam.beamType = " << specificRunParam.beamType << endl;
    
    //Assign the detector specific parameters to the detector structure map
    //It is understood that vec_detNames has the same ordering as what appears in the file name
    //If the size of vec_detNames and the vectors containing the identified parameters are not the same
    //then all detectors will be assigned the same parameters (at index 0) for a given parameter.
    //i.e. if vec_thresh.size() == 2 and vec_detNames == 3 then all detectors are assigned vec_thresh[0]
    for(unsigned int i=0; i<vec_detNames.size(); i++){ //Loop Over vec_detNames
        //Debugging
        //cout<<"======================================================="<<endl;
        //cout<<"vec_detNames["<<i<<"] = " << vec_detNames[i] << endl;
        
        //Set the values not set in getRun()
        (specificRunParam.detectors[vec_detNames[i]]).eff       = vec_eff[i].first;             //cout<<"eff = " << vec_eff[i].first << "+/-" << vec_eff[i].second << endl;
        (specificRunParam.detectors[vec_detNames[i]]).eff_sigma = vec_eff[i].second;
        
        //For Easy Access (yes I know this uses memory unnecessarily...)
        gem = specificRunParam.detectors[vec_detNames[i]];
        
        if( results.count(vec_detNames[i]) > 0 ){ //Case: Detector Exists
            if (results[vec_detNames[i]].Scan_Lat.count(gem.latency) > 0 ) { //Case: Latency for this Detector Exists
                //No delay consistency check; this is allowed to change
                
                //Check Consistency of MSPL
                if(results[vec_detNames[i]].Scan_Lat[gem.latency].pulseLen != gem.pulseLen){ //Case: MSPL Check
                    cout<<"=======================MSPL Check======================="<<endl;
                    cout<<"Warning Pulse Length Changed Mid Run"<<endl;
                    cout<<"Detector = " << vec_detNames[i] << " Latency = " << gem.latency << endl;
                    cout<<"Expect MSPL = " << results[vec_detNames[i]].Scan_Lat[gem.latency].pulseLen << " Current MSPL = " << gem.pulseLen << endl;
                    cout<<"PLEASE CROSS CHECK RUN: " << specificRunParam.numRun << endl;
                    
                    results[vec_detNames[i]].infoMatch_Lat = false;
                } //End Case: MSPL Check
                
                //Check to see if the minimum run number for this latency value is set correctly
                if(specificRunParam.numRun < results[vec_detNames[i]].Scan_Lat[gem.latency].run_initial){ //Case: Initial Run Check
                    results[vec_detNames[i]].Scan_Lat[gem.latency].run_initial = specificRunParam.numRun;
                } //End Case: Initial Run Check
                
                //Check to see if the maximum run number for this latency value is set correctly
                if(specificRunParam.numRun > results[vec_detNames[i]].Scan_Lat[gem.latency].run_final){ //Case: Final Run Check
                    results[vec_detNames[i]].Scan_Lat[gem.latency].run_final = specificRunParam.numRun;
                } //End Case: Final Run Check
                
                //Check Consistency of Threshold
                if(results[vec_detNames[i]].Scan_Lat[gem.latency].thresh != gem.thresh){ //Case: Threshold Check
                    cout<<"=======================Thresh Check======================="<<endl;
                    cout<<"Warning Threshold Changed Mid Run"<<endl;
                    cout<<"Detector = " << vec_detNames[i] << " Latency = " << gem.latency << endl;
                    cout<<"Expect Thresh = " << results[vec_detNames[i]].Scan_Lat[gem.latency].thresh << " Current Thresh = " << gem.thresh << endl;
                    cout<<"PLEASE CROSS CHECK RUN: " << specificRunParam.numRun << endl;
                    
                    results[vec_detNames[i]].infoMatch_Lat = false;
                } //End Case: Threshold Check
                
                //Check Consistency of Beam Type
                if(results[vec_detNames[i]].Scan_Lat[gem.latency].beamType != specificRunParam.beamType){ //Case: BeamType Check
                    cout<<"=======================Beam Check======================="<<endl;
                    cout<<"Warning Beam Type Changed Mid Run"<<endl;
                    cout<<"Detector = " << vec_detNames[i] << " Latency = " << gem.latency << endl;
                    cout<<"Expect Beam = " << results[vec_detNames[i]].Scan_Lat[gem.latency].beamType << " Current Beam = " << specificRunParam.beamType << endl;
                    cout<<"PLEASE CROSS CHECK RUN: " << specificRunParam.numRun << endl;
                    
                    results[vec_detNames[i]].infoMatch_Lat = false;
                } //End Case: MSPL Check
                
                //Store Data
                results[vec_detNames[i]].Scan_Lat[gem.latency].currScan.push_back(gem.current);
                results[vec_detNames[i]].Scan_Lat[gem.latency].effs.push_back(gem.eff);
                results[vec_detNames[i]].Scan_Lat[gem.latency].sigma_effs.push_back(gem.eff_sigma);
            } //End Case: Latency for this Detector Exists
            else{ //Case: Latency for this Detector Does Not Exist
                InfoPerLat firstLatOccurence;
                
                firstLatOccurence.delay         = specificRunParam.delay;
                firstLatOccurence.pulseLen      = gem.pulseLen;
                firstLatOccurence.run_initial   = specificRunParam.numRun;
                firstLatOccurence.run_final     = 0;
                firstLatOccurence.thresh        = gem.thresh;
                
                firstLatOccurence.beamType      = specificRunParam.beamType;
                
                firstLatOccurence.currScan.push_back(gem.current);
                firstLatOccurence.effs.push_back(gem.eff);
                firstLatOccurence.sigma_effs.push_back(gem.eff_sigma);
                
                //Check that Info Matches Previous Information
                if (firstLatOccurence.delay != results[vec_detNames[i]].delay
                    || firstLatOccurence.pulseLen != results[vec_detNames[i]].pulseLen
                    || firstLatOccurence.beamType != results[vec_detNames[i]].beamType) { //Case: Check Info Matches for all latency curves for this detector match!
                    
                    cout<<"Warning Information Changed Mid Run for Detector " << vec_detNames[i] <<endl;
                    cout<<"Pulse Length, Trigger Mode/Delay, or Beam Type does not match Expectation"<<endl;
                    cout<<"Please Cross-check input runs"<<endl;
                    cout<<"PLEASE CROSS CHECK RUN: " << specificRunParam.numRun << endl;
                    
                    results[vec_detNames[i]].infoMatch_Lat = false;
                } //End Case: Check Info Matches for all latency curves for this detector match!
                
                results[vec_detNames[i]].Scan_Lat[gem.latency] = firstLatOccurence;
            } //End Case: Latency for this Detector Does Not Exist
        } //End Case: Detector Exists
        else{ //Case: Detector Does Not Exist
            DetResults firstDetOccurrence;
            InfoPerLat firstLatOccurence;
            
            //Set Parameters for Info Per Lat
            firstLatOccurence.delay         = specificRunParam.delay;
            firstLatOccurence.pulseLen      = gem.pulseLen;
            firstLatOccurence.run_initial   = specificRunParam.numRun;
            firstLatOccurence.run_final     = 0;
            firstLatOccurence.thresh        = gem.thresh;
            
            firstLatOccurence.beamType      = specificRunParam.beamType;
            
            firstLatOccurence.currScan.push_back(gem.current);
            firstLatOccurence.effs.push_back(gem.eff);
            firstLatOccurence.sigma_effs.push_back(gem.eff_sigma);
            
            //Put Info Per Lat into info per detector
            firstDetOccurrence.Scan_Lat[gem.latency] = firstLatOccurence;
            
            //store delay, pulseLen, and beamType (This is for Easier Access to the Information)
            firstDetOccurrence.infoMatch_Lat= true; //Initialize to true, only after looking at the others will we know this should be false
            firstDetOccurrence.delay        = specificRunParam.delay;
            firstDetOccurrence.pulseLen     = gem.pulseLen;
            firstDetOccurrence.beamType     = specificRunParam.beamType;
            firstDetOccurrence.thresh       = gem.thresh;
            
            //Put Info Per Detector into results
            results[vec_detNames[i]] = firstDetOccurrence;
        } //End Case: Detector Not Exist
    } //End Loop Over vec_detNames
    
    //Debugging
    //cout<<"TestBeamAnalyzer::setRunParamEff - No Fault 3" << endl;
    
    //Store This Run
    vec_RunParam.push_back(specificRunParam);
    
    //Debugging
    //cout<<"TestBeamAnalyzer::setRunParamEff - No Fault End" << endl;
    
    return;
} //End TestBeamAnalyzer::setRunParamEff()

void TestBeamAnalyzer::setRunParamTDC(string input, vector<TH1F*> inputHistos){
    //Variable Declaration
    DetInfo gem;
    
    float histoIntegral;
    
    std::map<string,float> peakInfo; //Only Need this for Clock Scan
    
    TestBeamAnalyzer::RunParam specificRunParam = getRun(input);
    
    vector<std::map<string,float> > allPeaks;
    
    //Debugging
    //cout<<"TestBeamAnalyzer::setRunParamTDC() - No Fault 1"<<endl;
    
    //Consistency Check
    if (inputHistos.size() != vec_detNames.size() ) { //Consistency Check
        cout<<"====================================================================="<<endl;
        cout<<"Identified " << vec_detNames.size() << " Detectors"<<endl;
        cout<<"But Only Found " << inputHistos.size() << " Histograms"<<endl;
        cout<<"Exiting, Please Check Your Input Files"<<endl;
        cout<<"====================================================================="<<endl;
        
        return;
    } //End Consistency Check
    
    //Debugging
    //cout<<"TestBeamAnalyzer::setRunParamTDC() - No Fault 2"<<endl;
    
    //Perform Measurement
    if (meas_TDC_ClockScan) { //Case: Clock Scan
        
        //Debugging
        //cout<<"TestBeamAnalyzer::setRunParamTDC() - No Fault 2_a"<<endl;
        
        //Loop Over Input Histograms
        for (unsigned int i=0; i < inputHistos.size(); i++) { //Loop Over Input Histograms
            //Debugging
            //cout<<"TestBeamAnalyzer::setRunParamTDC() - No Fault 2_a_i"<<endl;
            
            //Reset Histogram Integral
            histoIntegral = 0;
            
            //Debugging
            //cout<<"====================================================================================================================="<<endl;
            //cout<<inputHistos[i]->GetName()<<endl;
            
            //Setup For Starting Peak (i.e. Maximum Peak)
            peakInfo[peakKey_Pos]    = (float) inputHistos[i]->GetMaximumBin();
            peakInfo[peakKey_Int]    = 0.;
            peakInfo[peakKey_Delta]  = 0.;
            
            //Debugging
            //cout<<"TestBeamAnalyzer::setRunParamTDC() - No Fault 2_a_ii"<<endl;
            
            //Get the Maximum Peak
            recursivePeakFinder(peakInfo, inputHistos[i], true);
            
            //Store the maximum peak if it is above the noise (should be...)
            if ( peakInfo[peakKey_Int] > noiseThresh_TDC ) { //Case: Peak Above Noise
                //Store Temporal Position
                peakInfo[peakKey_PosTime] = inputHistos[i]->GetBinLowEdge(peakInfo[peakKey_Pos]);
                
                //Add To Considered Integral Of Histogram
                histoIntegral += peakInfo[peakKey_Int];
                
                //Store Peak Info
                allPeaks.push_back(peakInfo);
            } //End Case: Peak Above Noise
            
            //Debugging
            //cout<<"TestBeamAnalyzer::setRunParamTDC() - No Fault 2_a_iii"<<endl;
            
            //Get All Lower Peaks - Lower in Time
            do {
                //Debugging
                //cout<<"Start Loop: peakInfo['Position'] = " << peakInfo[peakKey_Pos] << endl;
                
                //Return Members to Initial Position;
                peakInfo[peakKey_Pos] -= floor(10/rebinFactor_TDC); //If user rebins histogram we have to account for this in the expected distance between peaks
                peakInfo[peakKey_Int]  = 0.;
                peakInfo[peakKey_Delta]     = 0.;
                
                //Debugging
                //cout<<"Shift: peakInfo['Position'] = " << peakInfo[peakKey_Pos] << endl;
                
                //Find Peak
                recursivePeakFinder(peakInfo, inputHistos[i], false);
                
                //Debugging
                //cout<<"Post RPF: peakInfo['Position'] = " << peakInfo[peakKey_Pos] << endl;
                //cout<<"Post RPF: peakInfo['Integral'] = " << peakInfo[peakKey_Int] << endl;
                
                //Store Peak if Above Noise
                if ( peakInfo[peakKey_Int] > noiseThresh_TDC ) { //Case: Peak Above Noise
                    //Store Temporal Position
                    peakInfo[peakKey_PosTime] = inputHistos[i]->GetBinLowEdge(peakInfo[peakKey_Pos]);
                    
                    //Add To Considered Integral Of Histogram
                    histoIntegral += peakInfo[peakKey_Int];
                    
                    //Store Peak Info
                    allPeaks.push_back(peakInfo);
                } //End Case: Peak Above Noise
            } while( peakInfo[peakKey_Int] > -1 );
            
            //Debugging
            //cout<<"TestBeamAnalyzer::setRunParamTDC() - No Fault 2_a_iv"<<endl;
            
            //Reset Starting Position to Max Peak
            peakInfo[peakKey_Pos]    = (float) inputHistos[i]->GetMaximumBin();
            peakInfo[peakKey_Int]  = 0.;
            peakInfo[peakKey_Delta]     = 0.;
            
            //Debugging
            //cout<<"TestBeamAnalyzer::setRunParamTDC() - No Fault 2_a_v"<<endl;
            
            //Get All Lower Peaks - Higher in Time
            do {
                //Return Members to Initial Position;
                peakInfo[peakKey_Pos] += floor(10/rebinFactor_TDC); //If user rebins histogram we have to account for this in the expected distance between peaks
                peakInfo[peakKey_Int]  = 0.;
                peakInfo[peakKey_Delta]     = 0.;
                
                //Find Peak
                recursivePeakFinder(peakInfo, inputHistos[i], true);
                
                //Store Peak If Above the Noise
                if ( peakInfo[peakKey_Int] > noiseThresh_TDC ) { //Case: Peak Above Noise
                    //Store Temporal Position
                    peakInfo[peakKey_PosTime] = inputHistos[i]->GetBinLowEdge(peakInfo[peakKey_Pos]);
                    
                    //Add To Considered Integral Of Histogram
                    histoIntegral += peakInfo[peakKey_Int];
                    
                    //Store Peak Info
                    allPeaks.push_back(peakInfo);
                } //End Case: Peak Above Noise
            } while( peakInfo[peakKey_Int] > -1 );
            
            //Debugging
            //cout<<"TestBeamAnalyzer::setRunParamTDC() - No Fault 2_a_vi"<<endl;
            
            //Debugging
            /*cout<<"Pos\tInt\tDelta"<<endl;
            for (unsigned int j=0; j<allPeaks.size(); j++) { //Loop Over All Peaks
                cout<<(allPeaks[j])["Position"]<<"\t"<<(allPeaks[j])["Integral"]<<"\t"<<(allPeaks[j])["Delta"]<<endl;
            } //End Loop Over All Peaks
            */
            
            //Debugging
            //cout<<"TestBeamAnalyzer::setRunParamTDC() - No Fault 2_a_vii"<<endl;
            
            //Store Peak Info In this Detector
            specificRunParam.detectors[vec_detNames[i]].TDC.nEvt    = histoIntegral;
            specificRunParam.detectors[vec_detNames[i]].TDC.peakInfo= allPeaks;
            specificRunParam.detectors[vec_detNames[i]].TDC.timeResHisto = (TH1F*)inputHistos[i]->Clone(Form("%s_ClkCyl_Histo_%s_R%s", vec_detNames[i].c_str(), getString( floor(specificRunParam.detectors[vec_detNames[i]].current) ).c_str(), getString(specificRunParam.numRun).c_str() ) );
            
            //Debugging
            //cout<<"TestBeamAnalyzer::setRunParamTDC() - No Fault 2_a_viii"<<endl;
            
            //clear peak info
            allPeaks.clear();
            peakInfo.clear();   //Clear This because Upper & Lower Bounds are not reset w/in this method
        } //End Loop Over Input Histograms
        
    } //End Case: Clock Scan
    else if (meas_TDC_TimeRes) { //Case: Time Resolution
        //Loop Over Input Histograms
        for (unsigned int i=0; i < inputHistos.size(); i++) { //Loop Over inputHistos
            //Setup for Starting Peak (Hopefully the only peak O_o)
            peakInfo[peakKey_Pos]    = (float) inputHistos[i]->GetMaximumBin();
            peakInfo[peakKey_Int]    = 0.;
            peakInfo[peakKey_Delta]  = 0.;
            
            //Dunno how well this will work, I designed recursivePeakFinder to work for very narrow well defined peaks...
            //Maybe we will need to rebin the histogram for this to work properly? Leave this out for now
            //inputHistos[i]->Rebin(2);
            
            //Get the Maximum Peak
            recursivePeakFinder(peakInfo, inputHistos[i], true);
            if (peakInfo[peakKey_Int] > noiseThresh_TDC) { //Case: Peak Found!
                //Store Temporal Position
                peakInfo[peakKey_PosTime] = inputHistos[i]->GetBinLowEdge(peakInfo[peakKey_Pos]);
                
                //Debugging
                //cout<<"Peak Info - "<< inputHistos[i]->GetName() <<endl;
                //cout<<"=========================================================================="<<endl;
                //cout<<"PkPos_LB\tPkPos_Mid\tPkPos_UP\tPkInt"<<endl;
                //cout<<peakInfo[peakKey_LwrBd]<<"\t"<<peakInfo[peakKey_PosTime]<<"\t"<<peakInfo[peakKey_UprBd]<<"\t"<<peakInfo[peakKey_Int]<<endl;
                
                //Prepare peakInfo for storage
                allPeaks.push_back(peakInfo);
                
                //Set Range on Histogram
                inputHistos[i]->GetXaxis()->SetRangeUser( peakInfo[peakKey_LwrBd], peakInfo[peakKey_UprBd] );
                
                //Prepare Fit - Before Deconvolution
                //could have put "gaus" instead of formula, but ROOT and C++ sometimes don't get along for preset things like this
                TF1 *fit_Gaus = new TF1("fit_Gaus","[0]*exp(-0.5*((x-[1])/[2])**2)",0,1000);
                
                fit_Gaus->SetParameter(1, inputHistos[i]->GetMean() ); //Initial Guess - Mean
                fit_Gaus->SetParameter(2, inputHistos[i]->GetRMS() ); //Initial Guess - Sigma
                
                //Fit Histogram
                if (fitTDC_AutoRanging) { //Case: Fit Range Automatically Determined
                    inputHistos[i]->Fit(fit_Gaus,fitTDC_Option.c_str(),"",inputHistos[i]->GetMean() - 2 * inputHistos[i]->GetRMS(),inputHistos[i]->GetMean() + 2 * inputHistos[i]->GetRMS() );
                } //End Case: Fit Range Automatically Determined
                else{ //Case: Fit Using Fully Histogram Range
                    inputHistos[i]->Fit(fit_Gaus, fitTDC_Option.c_str() );
                } //End Case: Fit Using Fully Histogram Range
                
                //Store Information - Before Deconvolution
                specificRunParam.detectors[vec_detNames[i]].TDC.fitPerformed= true;
                
                specificRunParam.detectors[vec_detNames[i]].TDC.raw_Mean    = inputHistos[i]->GetMean();
                specificRunParam.detectors[vec_detNames[i]].TDC.raw_MeanErr = inputHistos[i]->GetMeanError();
                specificRunParam.detectors[vec_detNames[i]].TDC.raw_RMS     = inputHistos[i]->GetRMS();
                specificRunParam.detectors[vec_detNames[i]].TDC.raw_RMSErr  = inputHistos[i]->GetRMSError();
                specificRunParam.detectors[vec_detNames[i]].TDC.peakInfo    = allPeaks;
                
                specificRunParam.detectors[vec_detNames[i]].TDC.timeResFit = (TF1*) fit_Gaus->Clone(Form("%s_TimeRes_Fit_%s_R%s", vec_detNames[i].c_str(), getString( floor(specificRunParam.detectors[vec_detNames[i]].current) ).c_str(), getString(specificRunParam.numRun).c_str() ) );
                specificRunParam.detectors[vec_detNames[i]].TDC.timeResHisto = (TH1F*)inputHistos[i]->Clone(Form("%s_TimeRes_Histo_%s_R%s", vec_detNames[i].c_str(), getString( floor(specificRunParam.detectors[vec_detNames[i]].current) ).c_str(), getString(specificRunParam.numRun).c_str() ) );
                
                //Prepare Fit - Convoluted Result, Allows direct access to deconvoluted time resp w/o deconvolution.
                TF1 *func_Erf_Convo = new TF1("func_Erf_Convo","[2]*[0]*sqrt(TMath::Pi()/2.)*(TMath::Erf( (12.5 + (x-[3])) / ([0] * sqrt(2.) ) ) - TMath::Erf( ((x-[3]) - 12.5) / ([0] * sqrt(2.) ) ) )",0,1000);
                
                func_Erf_Convo->SetParameter(0, inputHistos[i]->GetRMS() );
                //func_Erf_Convo->SetParameter(1, fClkLengthOver2);
                func_Erf_Convo->SetParameter(2, inputHistos[i]->GetMaximum() );
                func_Erf_Convo->SetParameter(3, inputHistos[i]->GetMean() );
                
                //For now use it EXACTLY like we did for the model
                inputHistos[i]->Fit(func_Erf_Convo,"N","",inputHistos[i]->GetMean() - 4. * inputHistos[i]->GetRMS(), inputHistos[i]->GetMean() + 4. * inputHistos[i]->GetRMS() );
                
                //Store Information - Deconvolution
                specificRunParam.detectors[vec_detNames[i]].TDCDeconvo.fitPerformed= true;
                
                specificRunParam.detectors[vec_detNames[i]].TDCDeconvo.raw_Mean    = inputHistos[i]->GetMean();
                specificRunParam.detectors[vec_detNames[i]].TDCDeconvo.raw_MeanErr = inputHistos[i]->GetMeanError();
                specificRunParam.detectors[vec_detNames[i]].TDCDeconvo.raw_RMS     = func_TimeResp_ConvoToPure->Eval(inputHistos[i]->GetRMS() );
                //specificRunParam.detectors[vec_detNames[i]].TDCDeconvo.raw_RMSErr  = inputHistos[i]->GetRMSError();
                specificRunParam.detectors[vec_detNames[i]].TDCDeconvo.raw_RMSErr  = 0; //Set For Now
                
                specificRunParam.detectors[vec_detNames[i]].TDCDeconvo.timeResFit = (TF1*) func_Erf_Convo->Clone(Form("%s_TimeRes_Fit_Deconvo_%s_R%s", vec_detNames[i].c_str(), getString( floor(specificRunParam.detectors[vec_detNames[i]].current) ).c_str(), getString(specificRunParam.numRun).c_str() ) );
            } //End Case: Peak Found!
            else{ //Case: Peak Not Found or Below the Noise
                //Store Information (Non Fit Specific) - Before Deconvolution
                specificRunParam.detectors[vec_detNames[i]].TDC.fitPerformed= false;
                
                specificRunParam.detectors[vec_detNames[i]].TDC.raw_Mean    = inputHistos[i]->GetMean();
                specificRunParam.detectors[vec_detNames[i]].TDC.raw_MeanErr = inputHistos[i]->GetMeanError();
                specificRunParam.detectors[vec_detNames[i]].TDC.raw_RMS     = inputHistos[i]->GetRMS();
                specificRunParam.detectors[vec_detNames[i]].TDC.raw_RMSErr  = inputHistos[i]->GetRMSError();
                
                specificRunParam.detectors[vec_detNames[i]].TDC.timeResHisto = (TH1F*)inputHistos[i]->Clone(Form("%s_TimeRes_Histo_%s_R%s", vec_detNames[i].c_str(), getString( floor(specificRunParam.detectors[vec_detNames[i]].current) ).c_str(), getString(specificRunParam.numRun).c_str() ) );
                
                //Store Information (Non Fit Specific) - Deconvolution
                specificRunParam.detectors[vec_detNames[i]].TDCDeconvo.fitPerformed= false;
                
                specificRunParam.detectors[vec_detNames[i]].TDCDeconvo.raw_Mean    = inputHistos[i]->GetMean();
                specificRunParam.detectors[vec_detNames[i]].TDCDeconvo.raw_MeanErr = inputHistos[i]->GetMeanError();
                specificRunParam.detectors[vec_detNames[i]].TDCDeconvo.raw_RMS     = func_TimeResp_ConvoToPure->Eval(inputHistos[i]->GetRMS() );
                //specificRunParam.detectors[vec_detNames[i]].TDCDeconvo.raw_RMSErr  = inputHistos[i]->GetRMSError();
                specificRunParam.detectors[vec_detNames[i]].TDCDeconvo.raw_RMSErr  = 0; //Set For Now
            } //End Case: Peak Not Found or Below the Noise
         
            //clear peak info
            allPeaks.clear();
            peakInfo.clear();   //Clear This because Upper & Lower Bounds are not reset w/in this method
         } //End Loop Over inputHistos
    } //End Case: Time Resolution
    
    //Debugging
    //cout<<"TestBeamAnalyzer::setRunParamTDC() - No Fault 3"<<endl;
    
    //cout<<"BEGIN DETECTOR ASSIGNMENT"<<endl;
    for(unsigned int i=0; i<inputHistos.size(); i++){ //Loop Over inputHistos
        //Debugging
        /*cout<<"======================================================="<<endl;
        cout<<"Results Info So Far"<<endl;
        for (map<string,DetResults,cmp_str>::iterator resIter = results.begin(); resIter != results.end(); resIter++) {
            cout<<"results.first = " << (*resIter).first << endl;
        }
        cout<<"vec_detNames["<<i<<"] = " << vec_detNames[i] << endl;
        cout<<"results.size() = " << results.size() << endl;
        cout<<"results.count("<<vec_detNames[i]<<") = " << results.count(vec_detNames[i]) << endl;
        */
        
        //For Easy Access (yes I know this uses memory unnecessarily...)
        gem = specificRunParam.detectors[vec_detNames[i]];
        
        //===========================================================================================
        //NOTE: Latency is Meaningless Now; We are working w/the TDC.  Here Latency Will Be Set To -1
        //===========================================================================================
        
        if( results.count(vec_detNames[i]) > 0 ){ //Case: Detector Exists
            if (results[vec_detNames[i]].Scan_DLY.count(specificRunParam.delay) > 0 ) { //Case: Delay for this Detector Exists
                //No delay consistency check; this is allowed to change
                
                //Check Consistency of Latency
                if(results[vec_detNames[i]].Scan_DLY[specificRunParam.delay].latency != gem.latency){ //Case: Latency Check
                    cout<<"=======================Latency Check======================="<<endl;
                    cout<<"Warning Latency Changed Mid Run"<<endl;
                    cout<<"Detector = " << vec_detNames[i] << " Delay = " << specificRunParam.delay << endl;
                    cout<<"Expect Latency = " << results[vec_detNames[i]].Scan_DLY[specificRunParam.delay].latency << " Current Latency = " << gem.latency << endl;
                    
                    results[vec_detNames[i]].infoMatch_DLY = false;
                } //End Case: Latency Check
                
                //Check Consistency of MSPL
                if(results[vec_detNames[i]].Scan_DLY[specificRunParam.delay].pulseLen != gem.pulseLen){ //Case: MSPL Check
                    cout<<"=======================MSPL Check======================="<<endl;
                    cout<<"Warning Pulse Length Changed Mid Run"<<endl;
                    cout<<"Detector = " << vec_detNames[i] << " Delay = " << specificRunParam.delay << endl;
                    cout<<"Expect MSPL = " << results[vec_detNames[i]].Scan_DLY[specificRunParam.delay].pulseLen << " Current MSPL = " << gem.pulseLen << endl;
                    
                    results[vec_detNames[i]].infoMatch_DLY = false;
                } //End Case: MSPL Check
                
                //Check to see if the minimum run number for this delay value is set correctly
                if(specificRunParam.numRun <= results[vec_detNames[i]].Scan_DLY[specificRunParam.delay].run_initial){ //Case: Initial Run Check
                    results[vec_detNames[i]].Scan_DLY[specificRunParam.delay].run_initial = specificRunParam.numRun;
                } //End Case: Initial Run Check
                
                //Check to see if the maximum run number for this delay value is set correctly
                if(specificRunParam.numRun >= results[vec_detNames[i]].Scan_DLY[specificRunParam.delay].run_final){ //Case: Final Run Check
                    results[vec_detNames[i]].Scan_DLY[specificRunParam.delay].run_final = specificRunParam.numRun;
                } //End Case: Final Run Check
                
                //Check Consistency of Threshold
                if(results[vec_detNames[i]].Scan_DLY[specificRunParam.delay].thresh != gem.thresh){ //Case: Threshold Check
                    cout<<"=======================Thresh Check======================="<<endl;
                    cout<<"Warning Threshold Changed Mid Run"<<endl;
                    cout<<"Detector = " << vec_detNames[i] << " Delay = " << specificRunParam.delay << endl;
                    cout<<"Expect Thresh = " << results[vec_detNames[i]].Scan_DLY[specificRunParam.delay].thresh << " Current Thresh = " << gem.thresh << endl;
                    
                    results[vec_detNames[i]].infoMatch_DLY = false;
                } //End Case: Threshold Check
                
                //Check Consistency of Beam Type
                if(results[vec_detNames[i]].Scan_DLY[specificRunParam.delay].beamType != specificRunParam.beamType){ //Case: BeamType Check
                    cout<<"=======================Beam Check======================="<<endl;
                    cout<<"Warning Beam Type Changed Mid Run"<<endl;
                    cout<<"Detector = " << vec_detNames[i] << " Delay = " << specificRunParam.delay << endl;
                    cout<<"Expect Beam = " << results[vec_detNames[i]].Scan_DLY[specificRunParam.delay].beamType << " Current Beam = " << specificRunParam.beamType << endl;
                    
                    results[vec_detNames[i]].infoMatch_DLY = false;
                } //End Case: BeamType Check
                
                //Store Data
                results[vec_detNames[i]].Scan_DLY[specificRunParam.delay].currScan.push_back(gem.current);
                if(meas_TDC_ClockScan){ //Case: Clock Scan
                    //results[vec_detNames[i]].Scan_DLY[specificRunParam.delay].vec_totalTrigs.push_back(gem.TDC.nEvt);
                    results[vec_detNames[i]].Scan_DLY[specificRunParam.delay].vec_totalTrigs.push_back(specificRunParam.numEvt);
                    results[vec_detNames[i]].Scan_DLY[specificRunParam.delay].vec_allPeakInfo.push_back(gem.TDC.peakInfo);
                    results[vec_detNames[i]].Scan_DLY[specificRunParam.delay].vec_timeResHistos.push_back(gem.TDC.timeResHisto); //This now stores more than just time res
                    
                    //Cyclic Storage
                    //results[vec_detNames[i]].Scan_DLY[specificRunParam.delay+25].vec_totalTrigs.push_back(gem.TDC.nEvt);
                    //results[vec_detNames[i]].Scan_DLY[specificRunParam.delay+25].vec_totalTrigs.push_back(specificRunParam.numEvt);
                    //results[vec_detNames[i]].Scan_DLY[specificRunParam.delay+25].vec_allPeakInfo.push_back(gem.TDC.peakInfo);
                    //results[vec_detNames[i]].Scan_DLY[specificRunParam.delay+25].vec_timeResHistos.push_back(gem.TDC.timeResHisto); //This now stores more than just time res
                } //End Case: Clock Scan
                if(meas_TDC_TimeRes) { //Case: Time Resolution
                    //Before Deconvolution
                    results[vec_detNames[i]].Scan_DLY[specificRunParam.delay].vec_allPeakInfo.push_back(gem.TDC.peakInfo);
                    results[vec_detNames[i]].Scan_DLY[specificRunParam.delay].vec_fitPerformed.push_back(gem.TDC.fitPerformed);
                    results[vec_detNames[i]].Scan_DLY[specificRunParam.delay].vec_rawRMS.push_back(gem.TDC.raw_RMS);
                    results[vec_detNames[i]].Scan_DLY[specificRunParam.delay].vec_rawRMSErr.push_back(gem.TDC.raw_RMSErr);
                    results[vec_detNames[i]].Scan_DLY[specificRunParam.delay].vec_rawMeans.push_back(gem.TDC.raw_Mean);
                    results[vec_detNames[i]].Scan_DLY[specificRunParam.delay].vec_rawMeansErr.push_back(gem.TDC.raw_MeanErr);
                    results[vec_detNames[i]].Scan_DLY[specificRunParam.delay].vec_timeResFits.push_back(gem.TDC.timeResFit);
                    results[vec_detNames[i]].Scan_DLY[specificRunParam.delay].vec_timeResHistos.push_back(gem.TDC.timeResHisto);
                    
                    //After Deconvolution
                    results[vec_detNames[i]].Scan_DLY[specificRunParam.delay].vec_fitPerformed_Deconvo.push_back(gem.TDCDeconvo.fitPerformed);
                    results[vec_detNames[i]].Scan_DLY[specificRunParam.delay].vec_rawRMS_Deconvo.push_back(gem.TDCDeconvo.raw_RMS);
                    results[vec_detNames[i]].Scan_DLY[specificRunParam.delay].vec_rawRMSErr_Deconvo.push_back(gem.TDCDeconvo.raw_RMSErr);
                    results[vec_detNames[i]].Scan_DLY[specificRunParam.delay].vec_timeResFits_Deconvo.push_back(gem.TDCDeconvo.timeResFit);
                } //End Case: Time Resolution
            } //End Case: Delay for this Detector Exists
            else{ //Case: Delay for this Detector Does Not Exist
                InfoPerDelay firstDelayOccurence;
                
                firstDelayOccurence.latency     = gem.latency;
                firstDelayOccurence.pulseLen    = gem.pulseLen;
                firstDelayOccurence.run_initial = specificRunParam.numRun;
                //firstDelayOccurence.run_final   = 0;
                firstDelayOccurence.run_final   = specificRunParam.numRun; //Hope this is sorted out above
                firstDelayOccurence.thresh      = gem.thresh;
                
                firstDelayOccurence.beamType    = specificRunParam.beamType;
                
                firstDelayOccurence.currScan.push_back(gem.current);
                if(meas_TDC_ClockScan){ //Case: Clock Scan
                    //firstDelayOccurence.vec_totalTrigs.push_back(gem.TDC.nEvt);
                    firstDelayOccurence.vec_totalTrigs.push_back(specificRunParam.numEvt);
                    firstDelayOccurence.vec_allPeakInfo.push_back(gem.TDC.peakInfo);
                    firstDelayOccurence.vec_timeResHistos.push_back(gem.TDC.timeResHisto); //This now stores more than just time res
                } //End Case: Clock Scan
                if(meas_TDC_TimeRes){ //Case: Time Resolution
                    //Before Deconvolution
                    firstDelayOccurence.vec_allPeakInfo.push_back(gem.TDC.peakInfo);
                    firstDelayOccurence.vec_fitPerformed.push_back(gem.TDC.fitPerformed);
                    firstDelayOccurence.vec_rawRMS.push_back(gem.TDC.raw_RMS);
                    firstDelayOccurence.vec_rawRMSErr.push_back(gem.TDC.raw_RMSErr);
                    firstDelayOccurence.vec_rawMeans.push_back(gem.TDC.raw_Mean);
                    firstDelayOccurence.vec_rawMeansErr.push_back(gem.TDC.raw_MeanErr);
                    firstDelayOccurence.vec_timeResFits.push_back(gem.TDC.timeResFit);
                    firstDelayOccurence.vec_timeResHistos.push_back(gem.TDC.timeResHisto);
                    
                    //After Deconvolution
                    firstDelayOccurence.vec_fitPerformed_Deconvo.push_back(gem.TDCDeconvo.fitPerformed);
                    firstDelayOccurence.vec_rawRMS_Deconvo.push_back(gem.TDCDeconvo.raw_RMS);
                    firstDelayOccurence.vec_rawRMSErr_Deconvo.push_back(gem.TDCDeconvo.raw_RMSErr);
                    firstDelayOccurence.vec_timeResFits_Deconvo.push_back(gem.TDCDeconvo.timeResFit);
                } //End Case: Time Resolution
                
                //Check that Info Matches Previous Information
                if (firstDelayOccurence.pulseLen != results[vec_detNames[i]].pulseLen
                    || firstDelayOccurence.beamType != results[vec_detNames[i]].beamType
                    || firstDelayOccurence.thresh != results[vec_detNames[i]].thresh) { //Case: Check Info Matches for all latency curves for this detector match!
                    if (firstDelayOccurence.pulseLen != results[vec_detNames[i]].pulseLen) { //Case: MSPL Check
                        cout<<"=======================MSPL Check======================="<<endl;
                        cout<<"Warning Information Changed Mid Run"<<endl;
                        cout<<"Detector = " << vec_detNames[i] << " Delay = " << specificRunParam.delay << endl;
                        cout<<"Expect MSPL = " << results[vec_detNames[i]].pulseLen << " Current MSPL = " << firstDelayOccurence.pulseLen << endl;
                    } //End Case: MSPL Check
                    if (firstDelayOccurence.thresh != results[vec_detNames[i]].thresh) { //Case: Thresh Check
                        cout<<"=======================Thresh Check======================="<<endl;
                        cout<<"Warning Information Changed Mid Run"<<endl;
                        cout<<"Detector = " << vec_detNames[i] << " Delay = " << specificRunParam.delay << endl;
                        cout<<"Expect Thresh = " << results[vec_detNames[i]].thresh << " Current Thresh = " << firstDelayOccurence.thresh << endl;
                    } //End Case: Thresh Check
                    if (firstDelayOccurence.beamType != results[vec_detNames[i]].beamType) { //Case: Beam Check
                        cout<<"=======================Beam Check======================="<<endl;
                        cout<<"Warning Information Changed Mid Run"<<endl;
                        cout<<"Detector = " << vec_detNames[i] << " Delay = " << specificRunParam.delay << endl;
                        cout<<"Expect Beam = " << results[vec_detNames[i]].beamType << " Current Beam = " << firstDelayOccurence.beamType << endl;
                    } //End Case: Beam Check
                    
                    cout<<"Please Cross-check input runs"<<endl;
                    
                    results[vec_detNames[i]].infoMatch_DLY = false;
                } //End Case: Check Info Matches for all latency curves for this detector match!
                
                results[vec_detNames[i]].Scan_DLY[specificRunParam.delay] = firstDelayOccurence;
                
                //Cyclic Storage
                //results[vec_detNames[i]].Scan_DLY[specificRunParam.delay+25] = firstDelayOccurence;
            } //End Case: Latency for this Detector Does Not Exist
        } //End Case: Detector Exists
        else{ //Case: Detector Does Not Exist
            DetResults   firstDetOccurrence;
            InfoPerDelay firstDelayOccurence;
            
            //Set Parameters for Info Per Delay
            firstDelayOccurence.latency     = gem.latency;
            firstDelayOccurence.pulseLen    = gem.pulseLen;
            firstDelayOccurence.run_initial = specificRunParam.numRun;
            //firstDelayOccurence.run_final   = 0;
            firstDelayOccurence.run_final   = specificRunParam.numRun; //Hope this is sorted out above
            firstDelayOccurence.thresh      = gem.thresh;
            
            firstDelayOccurence.beamType    = specificRunParam.beamType;
            
            firstDelayOccurence.currScan.push_back(gem.current);
            if(meas_TDC_ClockScan){ //Case: Clock Scan
                //firstDelayOccurence.vec_totalTrigs.push_back(gem.TDC.nEvt);
                firstDelayOccurence.vec_totalTrigs.push_back(specificRunParam.numEvt);
                firstDelayOccurence.vec_allPeakInfo.push_back(gem.TDC.peakInfo);
                firstDelayOccurence.vec_timeResHistos.push_back(gem.TDC.timeResHisto); //This now stores more than time res
            } //End Case: Clock Scan
            if(meas_TDC_TimeRes){ //Case: Time Resolution
                //Before Deconvolution
                firstDelayOccurence.vec_allPeakInfo.push_back(gem.TDC.peakInfo);
                firstDelayOccurence.vec_fitPerformed.push_back(gem.TDC.fitPerformed);
                firstDelayOccurence.vec_rawRMS.push_back(gem.TDC.raw_RMS);
                firstDelayOccurence.vec_rawRMSErr.push_back(gem.TDC.raw_RMSErr);
                firstDelayOccurence.vec_rawMeans.push_back(gem.TDC.raw_Mean);
                firstDelayOccurence.vec_rawMeansErr.push_back(gem.TDC.raw_MeanErr);
                firstDelayOccurence.vec_timeResFits.push_back(gem.TDC.timeResFit);
                firstDelayOccurence.vec_timeResHistos.push_back(gem.TDC.timeResHisto);
                
                //After Deconvolution
                firstDelayOccurence.vec_fitPerformed_Deconvo.push_back(gem.TDCDeconvo.fitPerformed);
                firstDelayOccurence.vec_rawRMS_Deconvo.push_back(gem.TDCDeconvo.raw_RMS);
                firstDelayOccurence.vec_rawRMSErr_Deconvo.push_back(gem.TDCDeconvo.raw_RMSErr);
                firstDelayOccurence.vec_timeResFits_Deconvo.push_back(gem.TDCDeconvo.timeResFit);
            } //End Case: Time Resolution
            
            //Put Info Per Delay into info per detector
            firstDetOccurrence.Scan_DLY[specificRunParam.delay] = firstDelayOccurence;
            
            //Cyclic Storage
            //firstDetOccurrence.Scan_DLY[specificRunParam.delay+25] = firstDelayOccurence;
            
            //store delay, pulseLen, and beamType (This is for Easier Access to the Information)
            firstDetOccurrence.infoMatch_DLY= true; //Initialize to true, only after looking at the others will we know this should be false
            firstDetOccurrence.delay        = specificRunParam.delay;
            firstDetOccurrence.pulseLen     = gem.pulseLen;
            firstDetOccurrence.beamType     = specificRunParam.beamType;
            
            //Put Info Per Detector into results
            results[vec_detNames[i]] = firstDetOccurrence;
            //results[inputHistos[i]->GetName()] = firstDetOccurrence;
        } //End Case: Detector Not Exist
    } //End Loop Over vec_detNames
    
    //Debugging
    //cout<<"TestBeamAnalyzer::setRunParamTDC() - No Fault 4"<<endl;
    
    //Store This Run
    vec_RunParam.push_back(specificRunParam);
    
    //Debugging
    //cout<<"TestBeamAnalyzer::setRunParamTDC() - No Fault End"<<endl;
    
    return;
} //End TestBeamAnalyzer::setRunParamTDC()

//Sets the channel map of the TDC
void TestBeamAnalyzer::setTDCMapping(string inputFile){
    //Variable Declaration
    ifstream mapFile;
    
    string chan_idx, chan_name, line;
    
    mapFile.open( inputFile.c_str() );
    
    if (mapFile.good() ) { //Case: File Opened Successfully
        chanMap_TDC.clear();
    } //End Case: File Opened Successfully
    else{ //Case: File Open Fail!!!
        cout<<"TDC Mapping File " << inputFile << " failed to open"<<endl;
        cout<<"Using Last Known Mapping!!!" <<endl;
        cout<<"Note this could cause unexpected behavior/crash" <<endl;
        
        return;
    } //End Case: File Open Fail!!!
    
    std::getline(mapFile, line); //Dummy header, go past it
    
    //Debugging
    //cout<<"Ch_idx\tCh_Name"<<endl;
    
    //Set Channels
    while (mapFile >> chan_idx >> chan_name ) { //Loop Over File
        //Debugging
        //cout<<chan_idx<<"\t"<<chan_name<<endl;
        
        //Set Channels
        chanMap_TDC[ atoi( chan_idx.c_str() ) ] = chan_name;
    } //End Loop Over File
    
    mapFile.close();
    
    return;
} //End TestBeamAnalyzer::setTDCMapping()

//Sets the measurement the TDC data is being used to perform
void TestBeamAnalyzer::setTDCMeasurement(string inputFile){
    //Variable Declaration
    ifstream measureFile;
    
    string header;
    string axisText, identifier, runType;
    
    //Open the File
    measureFile.open( inputFile.c_str() );
    
    //Go Past Comments Section
    do {
        getline(measureFile, header);
        
        //Have Comments Ended?
        if( header.compare(0,1,"#") != 0 ) break;
    } while ( header.compare(0,1,"#") == 0);
    
    //Set Measurement (Functionality to be implemented later)
    /*while (measureFile >> axisText >> identifier >> runType ) {
        
    } //End Loop Through Measurement Setup
    */
    
    //Set Measurement Flags (to be removed once above functionality is implemented)
    measureFile >> axisText >> identifier >> runType;
    if (runType.compare(paramType.TDC_ClockScan) == 0)  meas_TDC_ClockScan  = true;
    if (runType.compare(paramType.TDC_TimeRes) == 0 )   meas_TDC_TimeRes    = true;
    
    //Close the File
    measureFile.close();
    
    return;
} //End TestBeamAnalyzer::setTDCMeasurement()

//Getters
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
int TestBeamAnalyzer::getCyclicColor(int input){
    int ret_color;
    
    switch (input % 7) {
        case 0:     ret_color = kBlack;     break;
        case 1:     ret_color = kRed+1;     break;
        case 2:     ret_color = kGreen+1;   break;
        case 3:     ret_color = kBlue+1;    break;
        case 4:     ret_color = kMagenta+1; break;
        case 5:     ret_color = kYellow+2;  break;
        case 6:     ret_color = kOrange+7;  break;
        default:
            break;
    }
    
    return ret_color;
} //End TestBeamAnalyzer::getCyclicColor()

//Changes as an example: GE11_IV_GIF into GE1/1-IV-GIF
string TestBeamAnalyzer::getParsedDetName(string input){
    //Variable Declaration
    string ret_name = "";
    
    vector<string> parsedName = getParsedFileName(input);
    
    for (unsigned int i=0; i < parsedName.size(); i++) { //Loop Over parsedName
        if (parsedName[i].length() >= 4 ) { //Case: i^th member has length >=4
            if(parsedName[i].compare(0,4,"GE11") == 0 ){ //Case: GE11
                ret_name = parsedName[i].substr(0,3) + "/" + parsedName[i].substr(3,1);
            } //End Case: GE11
        } //End Case: i^th member has length >=4
        else if(ret_name.length() > 0){ //Case: ret_name has already been setup
            ret_name = ret_name + "-" + parsedName[i];
        } //End Case: ret_name has already been setup
    } //End Loop Over parsedName
    
    return ret_name;
} //End TestBeamAnalyzer::getParsedDetName()

//For an underscore delimited string input returns a vector of strings whose elements are the strings in between the underscores
vector<string> TestBeamAnalyzer::getParsedFileName(string input){
    //Variable Declaration
    bool exitFlag       = false;
    
    int posLast         = 0;
    int posUnderscore1  = 0;
    
    string param        = "";
    string underscore   = "_";
    
    vector<string> ret_strings;
    
    //Go through the input file name
    //Treat the underscores as deliminators; find the relevant parameters of the run
    //Store them in ret_strings, return to user
    do {
        //Debugging
        //cout<<"TestBeamAnalyzer::getParsedFileName - No Fault 1_a" << endl;
        //cout<<"============================================" << endl;
        //Find Underscores
        posUnderscore1 = input.find(underscore, 0);
        
        //Set the Loop to Exit if an underscore is not found after position of the last underscore
        //Then set posUnderscore1 = input.length() so it takes the last part of the input string into consideration
        if(posUnderscore1 == std::string::npos){ //Case: Exit Flag = true
            exitFlag=true;
            posUnderscore1 = input.length();
        } //End Case: Exit Flag = true
        
        //Store this parameter
        param = input.substr(posLast,posUnderscore1);
        if(!exitFlag) input = input.substr(posUnderscore1+1,input.length()-posUnderscore1);
        
        ret_strings.push_back(param);
    } while (!exitFlag);
    
    return ret_strings;
} //End TestBeamAnalyzer::getParsedFileName()

//Give an integer input and get a string output
std::string TestBeamAnalyzer::getString(int input){
    stringstream stream;
    stream<<input;
    return stream.str();
} //End TestBeamAnalyzer::getString()

//Give an float input and get a string output
std::string TestBeamAnalyzer::getString(float input){
    stringstream stream;
    stream<<input;
    return stream.str();
} //End TestBeamAnalyzer::getString()

//Analyzers
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------

//Analyze Eff Data
//Stores the data in vec_AllRunParams
void TestBeamAnalyzer::analyzeRunsEff(){
    //Variable Declaration
    float eff, eff_sigma;
    
    ifstream masterEffFile;
    ifstream latSpecificFile;
    
    std::pair<float, float> effAndError;
    
    string fileInput;
    string runName, eff1, eff2, eff3;
    
    vector<std::pair<float, float> > vec_eff;
    
    //Debugging
    //cout<<"TestBeamAnalyzer::analyzeRunsEff() - No Fault 1"<<endl;
    
    //Wipe All Previous Runs
    vec_RunParam.clear();
    vec_AllRunParams.clear();
    
    //Open Master Files
    masterEffFile.open( fileName_Eff_Master.c_str() );
    
    //Set Detector Names
    if(!detNamesSet){ //Check if Names Have Been Set
        masterEffFile>>fileInput;                                       //First one should be worthless ("Reads FileName")
        masterEffFile>>fileInput;   vec_detNames.push_back(fileInput);  //1sr Detector Name
        masterEffFile>>fileInput;   vec_detNames.push_back(fileInput);  //2nd Detector Name
        masterEffFile>>fileInput;   vec_detNames.push_back(fileInput);  //3rd Detector Name
        
        detNamesSet = true;
    } //End Check if Names Have Been Set
    
    //Close Master File, no longer needed
    masterEffFile.close();
    
    //Debugging
    //cout<<"TestBeamAnalyzer::analyzeRunsEff() - No Fault 2"<<endl;
    
    //Analyze Latency Specific Runs
    for(unsigned int i=0; i<files_Eff_LatSpecific.size(); i++){ //Loop Over Latency Specific Files
        //Debugging
        //cout<<"TestBeamAnalyzer::analyzeRunsEff() - No Fault 2_a"<<endl;
        
        latSpecificFile.open( files_Eff_LatSpecific[i].c_str() );
        
        //Debugging
        //cout<<"Latency File I Opened = " << files_Eff_LatSpecific[i] << endl;
        //cout<<"TestBeamAnalyzer::analyzeRunsEff() - No Fault 2_b"<<endl;
        
        while( latSpecificFile >> runName >> eff1 >> eff2 >> eff3){ //Loop Over latSpecificFile
            //Debugging
            //cout<<"TestBeamAnalyzer::analyzeRunsEff() - No Fault 2_b_i"<<endl;
            //cout<<"runName = " << runName << endl;
            
            //Does the user want to comment out this run?
            if (runName.compare(0,1,"#" ) == 0 ) continue;
            
            //Null Efficiency?
            if( eff1.length() < 13 || eff2.length() < 13 || eff3.length() < 13 ){ //Check Expected Input?
                cout<<"============PROBLEM============"<<endl;
                cout<<"Eff Input Not As Expected!!!!"<<endl;
                cout<<"runName = " << runName << endl;
                cout<<"eff1 = " << eff1 << endl;
                cout<<"eff2 = " << eff2 << endl;
                cout<<"eff3 = " << eff3 << endl;
                cout<<"=======SKIPPING THIS RUN======="<<endl;
                continue;
            } //End Check Expected Input?
            
            //Set efficiencies Efficiency
            effAndError = std::make_pair( atof( (eff1.substr(0,5)).c_str() ),atof( (eff1.substr(8,5)).c_str() ) );      vec_eff.push_back(effAndError);
            effAndError = std::make_pair( atof( (eff2.substr(0,5)).c_str() ),atof( (eff2.substr(8,5)).c_str() ) );      vec_eff.push_back(effAndError);
            effAndError = std::make_pair( atof( (eff3.substr(0,5)).c_str() ),atof( (eff3.substr(8,5)).c_str() ) );      vec_eff.push_back(effAndError);
            
            //Debugging
            //cout<<"TestBeamAnalyzer::analyzeRunsEff() - No Fault 2_b_ii"<<endl;
            
            //Determine Run Parameters from File Name
            setRunParamEff(runName, vec_eff);
            
            //Debugging
            //cout<<"TestBeamAnalyzer::analyzeRunsEff() - No Fault 2_b_iii"<<endl;
            
            //Wipe vec_eff for next run
            vec_eff.clear();
            
            //Debugging
            //cout<<"TestBeamAnalyzer::analyzeRunsEff() - No Fault 2_b_iv - LOOP"<<endl;
        } //End Loop Over latSpecificFile
        
        //Debugging
        //cout<<"TestBeamAnalyzer::analyzeRunsEff() - No Fault 2_c"<<endl;
        
        //Close the file so we can open the next one successfully
        latSpecificFile.close();
        
        //Debugging
        //cout<<"TestBeamAnalyzer::analyzeRunsEff() - No Fault 2_d"<<endl;
        
        //Store all runs at the i^th Latency value
        vec_AllRunParams.push_back(vec_RunParam);
        
        //Wipe the runs to reset for the next latency value
        vec_RunParam.clear();
        
        //Debugging
        //cout<<"TestBeamAnalyzer::analyzeRunsEff() - No Fault 2_e - LOOP"<<endl;
    } //End Loop Over Latency Specific Files
    
    //Debugging
    //cout<<"TestBeamAnalyzer::analyzeRunsEff() - No Fault End"<<endl;
    
    return;
} //End TestBeamAnalyzer::analyzeRunsEff()

//Analyzes TDC Data
//Stores the data in vec_RunParam
void TestBeamAnalyzer::analyzeRunsTDC(){
    //Variable Declaration
    ifstream masterTDCFile;
    
    string fileName_ROOT, fileName_Mapping, fileName_Measurement;
    string name_histo = "TDC_Ch";

    //TFile *data_TDC = new TFile();
    //TFile *data_TDC = new TFile( fileName_ROOT.c_str(), "READ","",1 );
    
    vector<TH1F *> inputHistos;
    
    //Clear Detector Names, if Any
    vec_detNames.clear();
    
    //Wipe All Previous Runs
    vec_RunParam.clear();
    vec_AllRunParams.clear();
    
    //Open the Master File Name
    masterTDCFile.open( fileName_TDC_Master.c_str() );
    
    while ( masterTDCFile>>fileName_ROOT>>fileName_Mapping>>fileName_Measurement ) { //Loop Over Input File
        //Does the user want to comment out this run?
        if (fileName_ROOT.compare(0,1,"#" ) == 0 ) continue;
        
        //Debugging
        cout<<"Opening = " << fileName_ROOT.c_str() << endl;
        
        //Load the Root File for this Run
        TFile *data_TDC = new TFile( fileName_ROOT.c_str(), "READ","",1 );
        
        //Debugging
        //cout<<"Opening = " << fileName_Mapping.c_str() << endl;
        
        //Load the mapping for this Run
        setTDCMapping(fileName_Mapping);
        
        //Get the histograms defined in the mapping
        for (std::map<int,string>::iterator chanIter = chanMap_TDC.begin(); chanIter != chanMap_TDC.end(); chanIter++) { //Loop Over Mapped Channels
            //Load Histogram
            TH1F *temp_TDC_histo = new TH1F(*((TH1F*)data_TDC->Get( ( name_histo + getString( (*chanIter).first )  ).c_str() )));
            
            //Set The Errors on the vec_timeResHistos
            //But only do this for meas_TDC_TimeRes as it could impact the fit results
            if (meas_TDC_TimeRes) { //Case: meas_TDC_TimeRes
                for (unsigned int j=1; j< (temp_TDC_histo->GetNbinsX()+1); j++) {
                    temp_TDC_histo->SetBinError(j,sqrt( temp_TDC_histo->GetBinContent(j) ) );
                }
                temp_TDC_histo->Sumw2();
            } //End Case: meas_TDC_TimeRes
            
            //User may choose to offset finite statistics
            if (rebinFactor_TDC > 1) {temp_TDC_histo->Rebin(rebinFactor_TDC);}
            
            //Debugging
            //cout<<"Loading Histogram " << name_histo + getString( (*chanIter).first ) << endl;
            
            //Set the Name of the histogram you just added
            temp_TDC_histo->SetName( ( (*chanIter).second ).c_str() );
            
            //Put a Histogram in the vector
            inputHistos.push_back(temp_TDC_histo);
            
            //Set the Name of the histogram you just added
            //(inputHistos.end())->SetName( ( (*chanIter).second ).c_str() );
            //In principle I should do this *before* adding it to the vector...
            //inputHistos[inputHistos.size()-1]->SetName( ( (*chanIter).second ).c_str() );
            
            //Store the Name - Note Histogram Name and Detector Names are now linked!
            vec_detNames.push_back( (*chanIter).second );
        } //End Loop Over Mapped Channels
        
        setTDCMeasurement(fileName_Measurement);
        
        //Analyze Run
        //This could be made more efficient?
        if(meas_TDC_ClockScan){ //Case: Measurement - Clock Scan
            setRunParamTDC(fileName_ROOT, inputHistos);
        } //End Case: Measurement - Clock Scan
        else if(meas_TDC_TimeRes){ //Case: Measurement - Time Resolution
            setRunParamTDC(fileName_ROOT, inputHistos);
        } //End Case: Measurement - Time Resolution
        else{ //Case: Measurement - Unknown
            cout<<"==============================================================="<<endl;
            cout<<"Measurement File: " << fileName_Measurement << endl;
            cout<<"Your Requested Measurement is NOT Understood"<<endl;
            cout<<"Please Check The Above File and Run This Code Again"<<endl;
            cout<<"==============================================================="<<endl;
            
            break;
        } //End Case: Measurement - Unknown
        
        //Close Files
        //data_TDC->Close(); //Uncommenting this causes crash...in makeHistogramsTDC() when attempting to manipulate histograms O_o; suspect root's call of TAxis::GetParent() when doing TH1::GetYaxis()::SetRangeUser();  Call of GetYaxis() suceeds;  Crash in SetRangeUser due to believed GetParent() Call
        
        //Delete Unnecessary Pointers
        //delete data_TDC; //Uncommenting this causes crash...in makeHistogramsTDC() when attempting to manipulate histograms o_O; suspect root's call of TAxis::GetParent() when doing TH1::GetYaxis()::SetRangeUser();  Call of GetYaxis() suceeds;  Crash in SetRangeUser due to believed GetParent() Call
        
        //Clear Vectors
        inputHistos.clear();
        vec_detNames.clear();
    } //End Loop Over Input File
    
    return;
} //End TestBeamAnalyzer::analyzeRunsTDC()

//Makers
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
void TestBeamAnalyzer::makeDetLogEff(){
    //Variable Declaration
    std::vector<std::vector<RunParam> >::iterator latIter;
    std::map<string,DetResults,cmp_str>::iterator detIter;
    
    cout<<"results.size() = " << results.size() << endl;
    
    for(detIter = results.begin(); detIter != results.end(); detIter++){ //Loop Over Detectors
        map<int,InfoPerLat,cmp_int>::iterator latIter = ((*detIter).second).Scan_Lat.begin();
        
        cout<< (*detIter).first <<endl;
        cout<<"==========================================================================="<<endl;
        cout<<"Run\tBeam\tDLY\tMSPL\tThresh\tLat\tCurrent\tEff"<<endl;
        
        for(latIter; latIter!=((*detIter).second).Scan_Lat.end(); latIter++){ //Loop Over Latencies for Each Detector
            for(unsigned int i=0;i<((*latIter).second).currScan.size(); i++){ //Loop Over Eff Data
                if (i==0) { //Case: Initial Run
                    cout<<((*latIter).second).run_initial<<"\t";
                } //End Case: Initial Run
                else if (i == ( ((*latIter).second).currScan.size() - 1 ) ){ //Case: Final Run
                    cout<<((*latIter).second).run_final<<"\t";
                } //End Case: Final Run
                else{ //Case: All Other Runs
                    cout<<"-\t";
                } //End CAse: All Other Runs
                
                cout<<((*latIter).second).beamType<<"\t"<<((*latIter).second).delay<<"\t"<<((*latIter).second).pulseLen<<"\t"<<((*latIter).second).thresh<<"\t";
                cout<<(*latIter).first<<"\t"<<((*latIter).second).currScan[i]<<"\t"<<((*latIter).second).effs[i]<<"\t+/-"<<((*latIter).second).sigma_effs[i]<<endl;
            } //End Loop Over Eff Data
            
            cout<<"----------------------------------End Lat----------------------------------"<<endl;
        } //End Loop Over Latencies for Each Detector
    } //End Loop Over Detectors
    
    return;
} //End TestBeamAnalyzer::makeDetLog()

void TestBeamAnalyzer::makeDetLogTDC(){
    //Variable Declaration
    std::map<string,DetResults,cmp_str>::iterator detIter;
    
    cout<<"results.size() = " << results.size() << endl;
    
    //Here we output a separate table per detector
    for(detIter = results.begin(); detIter != results.end(); detIter++){ //Loop Over Detectors
        int maxNumPeaks = 0;
        
        map<int,InfoPerDelay,cmp_int>::iterator dlyIter;
        
        cout<< (*detIter).first <<endl;
        cout<<"==========================================================================="<<endl;
        cout<<"Run\tBeam\tDLY\tMSPL\tThresh\tLat\tCurrent\t";  //Common Output
        if(meas_TDC_ClockScan)  cout<<"N_Peaks\t";
        if(meas_TDC_TimeRes)    cout<<"Histo_Mean\tHisto_RMS\tN_Peaks\t";
        
        //Determine the Maximum Number of Peaks Present For this Detector's Data
        for(dlyIter=((*detIter).second).Scan_DLY.begin(); dlyIter!=((*detIter).second).Scan_DLY.end(); dlyIter++){ //Loop Over Delays for Each Detector
            
            for(unsigned int i=0; i<((*dlyIter).second).vec_allPeakInfo.size(); i++) { //Loop Over vec_allPeakInfo
                //Debugging
                //cout<<"vec_allPeakInfo.size() = "<<((*dlyIter).second).vec_allPeakInfo.size() << " vec_allPeakInfo["<< i << "].size() = " << ((*dlyIter).second).vec_allPeakInfo[i].size() << endl;
                
                if (((*dlyIter).second).vec_allPeakInfo[i].size() > maxNumPeaks) maxNumPeaks = ((*dlyIter).second).vec_allPeakInfo[i].size();
            } //End Loop Over vec_allPeakInfo
        } //End Loop Over Delays for This Detector
        
        //Now That we have Determined the Maximum Number Of Peaks for this detector continue to output the table
        for(dlyIter=((*detIter).second).Scan_DLY.begin(); dlyIter!=((*detIter).second).Scan_DLY.end(); dlyIter++){ //Loop Over Delays for This Detector
            
            //Setup the Table To be Prepared for the Maximum Number of Peaks
            if (dlyIter == ((*detIter).second).Scan_DLY.begin() ) { //Case: First Time
                //for(int i=0; i<maxNumPeaks; i++){cout<<"PkPos_"<<i<<"\tPkInt_"<<i<<"\t";}
                for(int i=0; i<maxNumPeaks; i++){cout<<"PkInt_"<<i<<"\t";}
                
                //Setup the table for Time Resolution
                if (meas_TDC_TimeRes) {
                    cout<<"Time_Res\tChi2\tnDoF"<<endl;
                }
                else{
                    cout<<endl;
                }
            } //End Case: First Time
            
            //Loop Over Currents!
            for(unsigned int i=0;i<((*dlyIter).second).currScan.size(); i++){ //Loop Over Data
                //Output Run Range
                if (i==0) { //Case: Initial Run
                    cout<<((*dlyIter).second).run_initial<<"\t";
                } //End Case: Initial Run
                else if (i == ( ((*dlyIter).second).currScan.size() - 1 ) ){ //Case: Final Run
                    cout<<((*dlyIter).second).run_final<<"\t";
                } //End Case: Final Run
                else{ //Case: All Other Runs
                    cout<<"-\t";
                } //End CAse: All Other Runs
                
                //cout<<"Run\tBeam\tDLY\tMSPL\tThresh\tLat\tCurrent\t";  //Common Output
                //if(meas_TDC_ClockScan)  cout<<"N_Peaks\t";
                //if(meas_TDC_TimeRes)    cout<<"Histo_Mean\tHisto_RMS\tN_Peaks\t";
                
                //Output Common Info
                cout<<((*dlyIter).second).beamType<<"\t";
                cout<<(*dlyIter).first<<"\t";
                cout<<((*dlyIter).second).pulseLen<<"\t";
                cout<<((*dlyIter).second).thresh<<"\t";
                cout<<((*dlyIter).second).latency<<"\t";
                cout<<((*dlyIter).second).currScan[i]<<"\t";
                
                if (meas_TDC_ClockScan) { //Case: Clock Scan
                    cout<<((*dlyIter).second).vec_allPeakInfo[i].size()<<"\t";
                } //End Case: Clock Scan
                
                if( meas_TDC_TimeRes) { //Case: Time Resolution
                    cout<<((*dlyIter).second).vec_rawMeans[i]<<"\t"<<((*dlyIter).second).vec_rawRMS[i]<<"\t";
                    cout<<((*dlyIter).second).vec_allPeakInfo[i].size()<<"\t";
                } //End Case: Time Resolution
                
                //Output the Peak Info for all Peaks Present
                if (((*dlyIter).second).vec_allPeakInfo.size() > 0) { //Case: Peaks Present
                    vector<map<string,float> >::iterator pkIter;
                    
                    for (pkIter = ((*dlyIter).second).vec_allPeakInfo[i].begin(); pkIter != ((*dlyIter).second).vec_allPeakInfo[i].end(); pkIter++) { //Loop Over Peaks Per This Gain
                        //cout<< (*pkIter)[peakKey_PosTime] << "\t" << (*pkIter)[peakKey_Int] <<"\t";
                        cout<< (*pkIter)[peakKey_Int] <<"\t";
                    } //End Loop Over Peaks Per This Gain
                } //End Case: Peaks Present
                else{
                    cout<<"-\t";
                }
                
                if ( meas_TDC_TimeRes ) { //Case: Time Resolution Data Present!!!
                    if (((*dlyIter).second).vec_fitPerformed[i] == true && ((*dlyIter).second).vec_timeResFits.size() > 0) { //Case: Peak Above the Noise!!!
                        cout<<((*dlyIter).second).vec_timeResFits[i]->GetParameter(2)<<"\t"<<((*dlyIter).second).vec_timeResFits[i]->GetChisquare()<<"\t"<<((*dlyIter).second).vec_timeResFits[i]->GetNDF()<<endl;
                    } //End Case: Peak Above the Noise!!!
                    else{ //Case: Peak Below the Noise or Not Found
                        cout<<"-\t-\t-"<<endl;
                    } //End Case: Peak Below the Noise or Not Found
                } //End Case: Time Resolution Data Present!!!
                else{ //Case: No Time Resolution Data Present!!!
                    cout<<endl;
                } //End Case: No Time Resolution Data Present!!!
                
            } //End Loop Over Eff Data
        } //End Loop Over Delays for This Detector
    } //End Loop Over Detectors
    
    return;
} //End TestBeamAnalyzer::makeDetLog()

void TestBeamAnalyzer::makeHistogramsEff(){
    //Variable Declaration
    float paintPos_X = 1e5;
    
    std::vector<std::vector<RunParam> >::iterator latIter;
    std::map<string,DetResults,cmp_str>::iterator detIter;
    
    //Debugging
    cout<<"Info from Run Log"<<endl;
    cout<<"==========================================================================="<<endl;
    cout<<"Run\tBeam\tEvt\tMSPL\tDLY\tMSPL1\tT1\tCurr1\tEff1\tMSPL2\tT2\tCurr2\tEff2\tMSPL3\tT3\tCurr3\tEff3\tLat"<<endl;
    
    //Loop Over Runs
    for(latIter = vec_AllRunParams.begin(); latIter != vec_AllRunParams.end(); latIter++){
        std::vector<RunParam> runsAtLatX = (*latIter);
        
        for(unsigned int i=0; i<runsAtLatX.size(); i++){
            std::map<std::string, DetInfo>::iterator detectorsInRun;
            
            cout<<runsAtLatX[i].numRun << "\t";
            cout<<runsAtLatX[i].beamType << "\t";
            cout<<runsAtLatX[i].numEvt << "\t";
            
            for(detectorsInRun = runsAtLatX[i].detectors.begin(); detectorsInRun != runsAtLatX[i].detectors.end(); detectorsInRun++){ //Loop Over Detectors In Run
                DetInfo gem = (*detectorsInRun).second;
                
                cout<<gem.pulseLen << "\t";
                cout<<gem.thresh << "\t";
                cout<<gem.current << "\t";
                cout<<gem.eff << "\t";
                
            } //End Loop Over Detectors In Run
            cout<<endl;
        } //End Loop Over runs at latency corresponding to latIter
    } //End Loop Over Latencies Considered
    
    cout<<"Det Log"<<endl;
    cout<<"==========================================================================="<<endl;
    cout<<"Det Name\tRun_i\tRun_f\tBeam\tDLY\tMSPL\tThresh\tLat\tCurrent\tEff"<<endl;
    for(detIter = results.begin(); detIter != results.end(); detIter++){ //Loop Over Detectors
        map<int,InfoPerLat,cmp_int>::iterator latIter;
        
        //Determine initial & final run number
        //Yes We need to Loop Over Latencies in a separate occassion
        //Need to prep run numbers before plotting
        ((*detIter).second).run_initial = 60000;
        ((*detIter).second).run_final   = 0;
        for (latIter=((*detIter).second).Scan_Lat.begin(); latIter!=((*detIter).second).Scan_Lat.end(); latIter++) {
            if ( ((*detIter).second).run_initial > ((*latIter).second).run_initial )    ((*detIter).second).run_initial    = ((*latIter).second).run_initial;
            if ( ((*detIter).second).run_final   < ((*latIter).second).run_final )      ((*detIter).second).run_final      = ((*latIter).second).run_final;
        } //End Loop Over Latencies
        
        //Initialize the canvas - All Latencies
        ((*detIter).second).canvas_DetEff_v_Curr = new TCanvas(
            Form("Plot_%s_LatAll_DetEff_v_Curr_R%s_R%s",((*detIter).first).c_str(), getString( ((*detIter).second).run_initial ).c_str(), getString( ((*detIter).second).run_final ).c_str() ),
            Form("%s_LatAll_DetEff_v_Curr_%s_%s",((*detIter).first).c_str(), getString( ((*detIter).second).run_initial ).c_str(), getString( ((*detIter).second).run_final ).c_str() ),
            700,700);
        
        for(latIter=((*detIter).second).Scan_Lat.begin(); latIter!=((*detIter).second).Scan_Lat.end(); latIter++){ //Loop Over Latencies for Each Detector
            //Initialize Histogram
            ((*latIter).second).graph_DetEff_v_Curr = new TGraphErrors( ((*latIter).second).currScan.size() );
            
            ((*latIter).second).graph_DetEff_v_Curr->SetName(Form("%s_Lat%s_DetEff_v_Curr_R%s_R%s", ((*detIter).first).c_str(), (getString((*latIter).first ) ).c_str(), getString( ((*detIter).second).run_initial ).c_str(), getString( ((*detIter).second).run_final ).c_str() ) );
            
            for(unsigned int i=0;i<((*latIter).second).currScan.size(); i++){ //Loop Over Eff Data
                cout<<(*detIter).first<<"\t";
                
                if (i==0) { //Case: Initial Run
                    cout<<((*latIter).second).run_initial<<"\t";
                } //End Case: Initial Run
                else if (i == ( ((*latIter).second).currScan.size() - 1 ) ){ //Case: Final Run
                    cout<<((*latIter).second).run_final<<"\t";
                } //End Case: Final Run
                else{ //Case: All Other Runs
                    cout<<"-\t";
                } //End CAse: All Other Runs
                
                cout<<((*latIter).second).beamType<<"\t"<<((*latIter).second).delay<<"\t"<<((*latIter).second).pulseLen<<"\t"<<((*latIter).second).thresh<<"\t";
                cout<<(*latIter).first<<"\t"<<((*latIter).second).currScan[i]<<"\t"<<((*latIter).second).effs[i]<<"\t+/-"<<((*latIter).second).sigma_effs[i]<<endl;
                
                //Set TGraphError Points
                ((*latIter).second).graph_DetEff_v_Curr->SetPoint(i,((*latIter).second).currScan[i],((*latIter).second).effs[i]);
                ((*latIter).second).graph_DetEff_v_Curr->SetPointError(i,0,((*latIter).second).sigma_effs[i]);
            } //End Loop Over Eff Data
            
            //Plot The Curve
            //======================================================
            //Initialize the canvas - Single Latency
            ((*latIter).second).canvas_DetEff_v_Curr = new TCanvas(
                Form("Plot_%s_Lat%s_DetEff_v_Curr_R%s_R%s",((*detIter).first).c_str(), (getString((*latIter).first)).c_str(), getString( ((*detIter).second).run_initial ).c_str(), getString( ((*detIter).second).run_final ).c_str() ),
                Form("%s_Lat%s_DetEff_v_Curr_R%s_R%s",((*detIter).first).c_str(), (getString((*latIter).first)).c_str(), getString( ((*detIter).second).run_initial ).c_str(), getString( ((*detIter).second).run_final ).c_str() ),
                700,700);
            
            //Determine Paint Position
            for (unsigned int i=0; i < ((*latIter).second).currScan.size(); i++) {
                if ( ((*latIter).second).currScan[i] < paintPos_X ) { paintPos_X = ((*latIter).second).currScan[i]; }
            }
            //Note the commented section below doesn't work if the runs are not taken in either increasing or decreasing order
            /*if(((*latIter).second).currScan[0] > ((*latIter).second).currScan.back()){ //Case: 0^th Member Highest Point
                paintPos_X = ((*latIter).second).currScan.back();
            } //End Case: 0^th Member Highest Point
            else{ //Case: Last Member Highest Point
                paintPos_X = ((*latIter).second).currScan[0];
            } //End Case: Last Member Highest Point
            */
            
            //Go To Active Canvas
            ((*latIter).second).canvas_DetEff_v_Curr->cd();
            ((*latIter).second).canvas_DetEff_v_Curr->SetTicky();
            ((*latIter).second).canvas_DetEff_v_Curr->SetTickx();
            ((*latIter).second).graph_DetEff_v_Curr->GetYaxis()->SetRangeUser(0.,1.);
            ((*latIter).second).graph_DetEff_v_Curr->Draw();
            
            //Set Info
            ((*latIter).second).texInfo_run         = new TLatex();     ((*latIter).second).texInfo_run->SetTextSize(0.03);
            ((*latIter).second).texInfo_beam        = new TLatex();     ((*latIter).second).texInfo_beam->SetTextSize(0.03);
            ((*latIter).second).texInfo_pulseLen    = new TLatex();     ((*latIter).second).texInfo_pulseLen->SetTextSize(0.03);
            ((*latIter).second).texInfo_delay       = new TLatex();     ((*latIter).second).texInfo_delay->SetTextSize(0.03);
            ((*latIter).second).texInfo_thresh      = new TLatex();     ((*latIter).second).texInfo_thresh->SetTextSize(0.03);
            ((*latIter).second).texInfo_lat         = new TLatex();     ((*latIter).second).texInfo_lat->SetTextSize(0.03);
            
            ((*latIter).second).texInfo_run->DrawLatex(paintPos_X, 0.9,Form("Runs %s - %s",(getString(((*latIter).second).run_initial)).c_str(),(getString(((*latIter).second).run_final)).c_str() ) );
            ((*latIter).second).texInfo_beam->DrawLatex(paintPos_X,0.85,Form("Beam: %s",((*latIter).second).beamType.c_str()));
            ((*latIter).second).texInfo_pulseLen->DrawLatex(paintPos_X,0.8,Form("MSPL%s",(getString(((*latIter).second).pulseLen)).c_str()));
            
            if(((*latIter).second).delay > -1){ //Case: Sync Mode
                ((*latIter).second).texInfo_delay->DrawLatex(paintPos_X,0.75,Form("Sync. Mode; DLY = %sns",(getString(((*latIter).second).delay)).c_str()));
            } //End Case: Sync Mode
            else{ //Case: Async Mode
                ((*latIter).second).texInfo_delay->DrawLatex(paintPos_X,0.75,"Async. Mode");
            } //End Case: Async Mode
            
            ((*latIter).second).texInfo_thresh->DrawLatex(paintPos_X,0.7,Form("VFAT Thresh. = %s fC",(getString(((*latIter).second).thresh).c_str())));
            ((*latIter).second).texInfo_lat->DrawLatex(paintPos_X,0.65,Form("VFAT Lat. = %s",(getString(((*latIter).first)).c_str())));
            
        } //End Loop Over Latencies for Each Detector
    } //End Loop Over Detectors
    
    return;
} //End TestBeamAnalyzer::makeHistogramsEff()

//Makes the Histograms and simultaneously writes them
void TestBeamAnalyzer::makeHistogramsEff(string input, string option){
    //Variable Declaration
    float paintPos_X = 1e5;
    float fHVDrift  = 0.;
    
    std::map<string,DetResults,cmp_str>::iterator detIter;
    
    string tempHistoName = "";
    
    TDirectory *dir_Detectors;
    
    TFile *TFOutput = new TFile(input.c_str(), option.c_str(), "", 1);
    
    TLatex *cmsPrelim = new TLatex(); cmsPrelim->SetTextSize(0.03);
    
    //string info_run, info_beam, info_pulseLen, info_delay, info_thresh, info_lat;
    
    //Debugging
    cout<<"TestBeamAnalyzer::makeHistogramsEff - No Fault 1" <<endl;
    
    //Check if File Exists Already
    if( option.compare("RECREATE") == 0 || option.compare("CREATE") == 0){ //Case: TFOutput Does Not Exist, Create File Structure
        dir_Detectors = TFOutput->mkdir("Detectors");
    } //End Case: TFOutput Does Not Exist, Create File Structure
    else{ //Case: TFOutput Exists, get Previously Created File Structure
        if ( TFOutput->GetDirectory("Detectors", false, "GetDirectory") == 0) {
            dir_Detectors = TFOutput->mkdir("Detectors");
        }
        else{
            dir_Detectors = TFOutput->GetDirectory("Detectors", false, "GetDirectory");
        }
    } //End Case: TFOutput Exists, get Previously Created File Structure
    
    //Debugging
    cout<<"TestBeamAnalyzer::makeHistogramsEff - No Fault 2" <<endl;
    
    //Setup Legend - All Detectors
    comparison.leg_AllDet_DetEff = new TLegend(0.15,0.55-0.05*(float)results.size(),0.45,0.60);
    comparison.leg_AllDet_DetEff->SetFillColor(kWhite);
    comparison.leg_AllDet_DetEff->SetLineColor(kWhite);
    
    for(detIter = results.begin(); detIter != results.end(); detIter++){ //Loop Over Detectors
        //Debugging
        cout<<"TestBeamAnalyzer::makeHistogramsEff - No Fault 2_a" <<endl;
        
        cout<<"((*detIter).first).c_str() = " << ((*detIter).first).c_str() << endl;
        TDirectory *dir_ThisDet = dir_Detectors->mkdir( ((*detIter).first).c_str() );
        
        map<int,InfoPerLat,cmp_int>::iterator latIter;
        
        //Determine initial & final run number
        //Yes We need to Loop Over Latencies in a separate occassion
        //Need to prep run numbers before plotting
        ((*detIter).second).run_initial = 60000;
        ((*detIter).second).run_final   = 0;
        for (latIter=((*detIter).second).Scan_Lat.begin(); latIter!=((*detIter).second).Scan_Lat.end(); latIter++) {
            if ( ((*detIter).second).run_initial > ((*latIter).second).run_initial )    ((*detIter).second).run_initial    = ((*latIter).second).run_initial;
            if ( ((*detIter).second).run_final   < ((*latIter).second).run_final )      ((*detIter).second).run_final      = ((*latIter).second).run_final;
        } //End Loop Over Latencies
        
        //Initialize the MultiGraph - All Latencies
        ((*detIter).second).mGraph_AllLatPlots = new TMultiGraph(
            Form("MultiGraph_%s_LatAll_DetEff_v_Curr_R%s_R%s",((*detIter).first).c_str(), getString( ((*detIter).second).run_initial ).c_str(), getString( ((*detIter).second).run_final ).c_str() ),
            " ;Current Supplied to HV Divider #left(#muA#right); Efficiency");
        
        ((*detIter).second).mGraph_AllLatPlots_HVDrift = new TMultiGraph(
            Form("MultiGraph_%s_LatAll_DetEff_v_HVDrift_R%s_R%s",((*detIter).first).c_str(), getString( ((*detIter).second).run_initial ).c_str(), getString( ((*detIter).second).run_final ).c_str() ),
            " ;HV_{Drift} #left(V#right); Efficiency");
        
        //Initialize the canvas - All Latencies
        ((*detIter).second).canvas_DetEff_v_Curr = new TCanvas(
            Form("Plot_%s_LatAll_DetEff_v_Curr_R%s_R%s",((*detIter).first).c_str(), getString( ((*detIter).second).run_initial ).c_str(), getString( ((*detIter).second).run_final ).c_str() ),
            Form("%s_LatAll_DetEff_v_Curr_R%s_R%s",((*detIter).first).c_str(), getString( ((*detIter).second).run_initial ).c_str(), getString( ((*detIter).second).run_final ).c_str() ),
            700,700);
        
        ((*detIter).second).canvas_DetEff_v_HVDrift = new TCanvas(
            Form("Plot_%s_LatAll_DetEff_v_HVDrift_R%s_R%s",((*detIter).first).c_str(), getString( ((*detIter).second).run_initial ).c_str(), getString( ((*detIter).second).run_final ).c_str() ),
            Form("%s_LatAll_DetEff_v_HVDrift_R%s_R%s",((*detIter).first).c_str(), getString( ((*detIter).second).run_initial ).c_str(), getString( ((*detIter).second).run_final ).c_str() ),
            700,700);
        
        //Setup Legend - All Latencies
        TLegend *leg_DetEff_AllLat = new TLegend(0.15,0.55-0.05*(float)((*detIter).second).Scan_Lat.size(),0.35,0.60);
        leg_DetEff_AllLat->SetLineColor(0);
        leg_DetEff_AllLat->SetFillColor(0);
        
        //Set Max Eff to Zero For this detector
        ((*detIter).second).max_eff = 0.;
        
        //Debugging
        cout<<"TestBeamAnalyzer::makeHistogramsEff - No Fault 2_b" <<endl;
        
        for(latIter=((*detIter).second).Scan_Lat.begin(); latIter!=((*detIter).second).Scan_Lat.end(); latIter++){ //Loop Over Latencies for Each Detector
            //Debugging
            cout<<"TestBeamAnalyzer::makeHistogramsEff - No Fault 2_b_i" <<endl;
            
            //Initialize TGraphErrors
            ((*latIter).second).graph_DetEff_v_Curr = new TGraphErrors( ((*latIter).second).currScan.size() );
            ((*latIter).second).graph_DetEff_v_Curr->SetName(Form("%s_Lat%s_DetEff_v_Curr_R%s_R%s", ((*detIter).first).c_str(), (getString((*latIter).first ) ).c_str(), getString( ((*detIter).second).run_initial ).c_str(), getString( ((*detIter).second).run_final ).c_str() ) );
            
            //Initialize TGraphErrors
            ((*latIter).second).graph_DetEff_v_HVDrift = new TGraphErrors( ((*latIter).second).currScan.size() );
            ((*latIter).second).graph_DetEff_v_HVDrift->SetName(Form("%s_Lat%s_DetEff_v_HVDrift_R%s_R%s", ((*detIter).first).c_str(), (getString((*latIter).first ) ).c_str(), getString( ((*detIter).second).run_initial ).c_str(), getString( ((*detIter).second).run_final ).c_str() ) );
            
            //Set Efficiencies
            for(unsigned int i=0;i<((*latIter).second).currScan.size(); i++){ //Loop Over Eff Data
                //Determine Paint Position
                if ( ((*latIter).second).currScan[i] < paintPos_X ) { paintPos_X = ((*latIter).second).currScan[i]; }
                
                //Set TGraphError Points - Versus Current
                ((*latIter).second).graph_DetEff_v_Curr->SetPoint(i,((*latIter).second).currScan[i],((*latIter).second).effs[i]);
                ((*latIter).second).graph_DetEff_v_Curr->SetPointError(i,0,((*latIter).second).sigma_effs[i]);
                
                //Set TGraphError Points - Versus HVDrift
                fHVDrift = ((*latIter).second).currScan[i] * 1e-6 * fREquiv;
                ((*latIter).second).graph_DetEff_v_HVDrift->SetPoint(i,fHVDrift,((*latIter).second).effs[i]);
                ((*latIter).second).graph_DetEff_v_HVDrift->SetPointError(i,0,((*latIter).second).sigma_effs[i]);
                
                //Log Which Latency Value Produces Eff Plateau (Crude Method to determine this)
                if ( ((*latIter).second).effs[i] > ((*detIter).second).max_eff ) { //Check of Max Eff
                    ((*detIter).second).max_eff     = ((*latIter).second).effs[i];
                    ((*detIter).second).latAtMaxEff = (*latIter).first;
                } //End Check of Max Eff
            } //End Loop Over Eff Data
            
            //Debugging
            cout<<"TestBeamAnalyzer::makeHistogramsEff - No Fault 2_b_ii" <<endl;
            
            //Fit The Curve - One Latency (Current)
            //======================================================
            TGraphErrors *tempEffCurve_Curr = (TGraphErrors *) ((*latIter).second).graph_DetEff_v_Curr->Clone("tempEffCurve_Curr");
            
            ((*latIter).second).fit_DetEff_v_Curr = new TF1(Form("Fit_%s_Lat%s_DetEff_v_Curr_R%s_R%s",((*detIter).first).c_str(), (getString((*latIter).first)).c_str(), getString( ((*detIter).second).run_initial ).c_str(), getString( ((*detIter).second).run_final ).c_str()  ), fitEff_Formula.c_str(), *std::min_element(((*latIter).second).currScan.begin(),((*latIter).second).currScan.end() ), *std::max_element(((*latIter).second).currScan.begin(),((*latIter).second).currScan.end() ) );
            
            tempEffCurve_Curr->Fit(((*latIter).second).fit_DetEff_v_Curr, fitEff_Option.c_str() );
            
            //Debugging
            cout<<"TestBeamAnalyzer::makeHistogramsEff - No Fault 2_b_ii_1" <<endl;
            
            //Plot The Curve - One Latency (Current)
            //======================================================
            //Initialize the canvas - Single Latency
            TCanvas *canvas_DetEff_v_Curr = new TCanvas(
                Form("Plot_%s_Lat%s_DetEff_v_Curr_R%s_R%s",((*detIter).first).c_str(), (getString((*latIter).first)).c_str(), getString( ((*detIter).second).run_initial ).c_str(), getString( ((*detIter).second).run_final ).c_str() ),
                Form("%s_Lat%s_DetEff_v_Curr_R%s_R%s",((*detIter).first).c_str(), (getString((*latIter).first)).c_str(), getString( ((*detIter).second).run_initial ).c_str(), getString( ((*detIter).second).run_final ).c_str() ),
                700,700);
            
            //Debugging
            cout<<"TestBeamAnalyzer::makeHistogramsEff - No Fault 2_b_ii_2" <<endl;
            
            //Determine Paint Position
            //for (unsigned int i=0; i < ((*latIter).second).currScan.size(); i++) {
            //if ( ((*latIter).second).currScan[i] < paintPos_X ) { paintPos_X = ((*latIter).second).currScan[i]; }
            //}
            //Note the commented section below doesn't work if the runs are not taken in either increasing or decreasing order
            /*if(((*latIter).second).currScan[0] > ((*latIter).second).currScan.back()){ //Case: 0^th Member Highest Point
             paintPos_X = ((*latIter).second).currScan.back();
             } //End Case: 0^th Member Highest Point
             else{ //Case: Last Member Highest Point
             paintPos_X = ((*latIter).second).currScan[0];
             } //End Case: Last Member Highest Point
             */
            
            //Set Style of Canvas
            //setCanvasStyle(((*latIter).second).canvas_DetEff_v_Curr);
            
            //Go To Active Canvas & Draw Plot
            canvas_DetEff_v_Curr->cd();
            canvas_DetEff_v_Curr->SetTicky();
            canvas_DetEff_v_Curr->SetTickx();
            ((*latIter).second).graph_DetEff_v_Curr->SetTitle("");
            ((*latIter).second).graph_DetEff_v_Curr->GetYaxis()->SetRangeUser(0.,1.);
            ((*latIter).second).graph_DetEff_v_Curr->GetYaxis()->SetDecimals(true);
            ((*latIter).second).graph_DetEff_v_Curr->GetYaxis()->SetTitle("Efficiency");
            ((*latIter).second).graph_DetEff_v_Curr->GetYaxis()->SetTitleOffset(1.20);
            ((*latIter).second).graph_DetEff_v_Curr->GetXaxis()->SetTitle("Current Supplied to HV Divider #left(#muA#right)");
            ((*latIter).second).graph_DetEff_v_Curr->GetXaxis()->SetTitleOffset(1.10);
            ((*latIter).second).graph_DetEff_v_Curr->SetMarkerStyle(21);
            ((*latIter).second).graph_DetEff_v_Curr->SetMarkerSize(1.);
            ((*latIter).second).graph_DetEff_v_Curr->SetLineWidth(2.);
            ((*latIter).second).graph_DetEff_v_Curr->Draw("ap");
            if (drawFit) ((*latIter).second).fit_DetEff_v_Curr->Draw("same");
            
            //Debugging
            cout<<"TestBeamAnalyzer::makeHistogramsEff - No Fault 2_b_ii_3" <<endl;
            
            //Draw Legend - SingleLat
            //TLegend *leg_DetEff_SingleLat = new TLegend(0.15,0.55,0.35,0.60);
            TLegend *leg_DetEff_SingleLat = new TLegend(0.15,0.50,0.35,0.60);
            leg_DetEff_SingleLat->SetLineColor(0);
            leg_DetEff_SingleLat->SetFillColor(0);
            leg_DetEff_SingleLat->AddEntry(((*latIter).second).graph_DetEff_v_Curr, getParsedDetName( ((*detIter).first) ).c_str(),"LP");
            if (drawFit) leg_DetEff_SingleLat->AddEntry(((*latIter).second).fit_DetEff_v_Curr, "Fit", "L");
            leg_DetEff_SingleLat->Draw("same");
            
            //Debugging
            cout<<"TestBeamAnalyzer::makeHistogramsEff - No Fault 2_b_ii_4" <<endl;
            
            //Draw Info Panel
            ((*latIter).second).texInfo_run         = new TLatex();     ((*latIter).second).texInfo_run->SetTextSize(0.03);
            ((*latIter).second).texInfo_beam        = new TLatex();     ((*latIter).second).texInfo_beam->SetTextSize(0.03);
            ((*latIter).second).texInfo_pulseLen    = new TLatex();     ((*latIter).second).texInfo_pulseLen->SetTextSize(0.03);
            ((*latIter).second).texInfo_delay       = new TLatex();     ((*latIter).second).texInfo_delay->SetTextSize(0.03);
            ((*latIter).second).texInfo_thresh      = new TLatex();     ((*latIter).second).texInfo_thresh->SetTextSize(0.03);
            ((*latIter).second).texInfo_lat         = new TLatex();     ((*latIter).second).texInfo_lat->SetTextSize(0.03);
            
            cmsPrelim->DrawLatex(paintPos_X-5,1.01,"CMS Preliminary");
            
            ((*latIter).second).texInfo_run->DrawLatex(paintPos_X, 0.9,Form("Runs %s - %s",(getString(((*latIter).second).run_initial)).c_str(),(getString(((*latIter).second).run_final)).c_str() ) );
            ((*latIter).second).texInfo_beam->DrawLatex(paintPos_X,0.85,Form("Beam: %s",((*latIter).second).beamType.c_str()));
            ((*latIter).second).texInfo_pulseLen->DrawLatex(paintPos_X,0.8,Form("MSPL%s",(getString(((*latIter).second).pulseLen)).c_str()));
            
            if(((*latIter).second).delay > 0){ //Case: Sync Mode
                ((*latIter).second).texInfo_delay->DrawLatex(paintPos_X,0.75,Form("Sync. Mode; DLY = %sns",(getString(((*latIter).second).delay)).c_str()));
            } //End Case: Sync Mode
            else{ //Case: Async Mode
                ((*latIter).second).texInfo_delay->DrawLatex(paintPos_X,0.75,"Async. Mode");
            } //End Case: Async Mode
            
            ((*latIter).second).texInfo_thresh->DrawLatex(paintPos_X,0.7,Form("VFAT Thresh. = %s fC",(getString(((*latIter).second).thresh).c_str())));
            ((*latIter).second).texInfo_lat->DrawLatex(paintPos_X,0.65,Form("VFAT Lat. = %s",(getString(((*latIter).first)).c_str())));
            
            //Debugging
            cout<<"TestBeamAnalyzer::makeHistogramsEff - No Fault 2_b_ii_5" <<endl;
            
            //Write
            cout<<"ptr ref dir_ThisDet = " << dir_ThisDet << endl;
            
            TDirectory *dir_ThisLat = dir_ThisDet->mkdir( Form("Lat%s", (getString((*latIter).first)).c_str()) );
            
            TDirectory *dir_Fits        = dir_ThisLat->mkdir("Fits");
            TDirectory *dir_Plots       = dir_ThisLat->mkdir("PremadePlots");
            TDirectory *dir_RawGraphs   = dir_ThisLat->mkdir("RawGraphs");
            
            dir_Fits->cd();
            cout<<"ptr ref ((*latIter).second).fit_DetEff_v_Curr = " << ((*latIter).second).fit_DetEff_v_Curr << endl;
            ((*latIter).second).fit_DetEff_v_Curr->Write();
            
            dir_Plots->cd();
            cout<<"ptr ref canvas_DetEff_v_Curr = " << canvas_DetEff_v_Curr << endl;
            canvas_DetEff_v_Curr->Write();
            
            dir_RawGraphs->cd();
            cout<<"ptr ref ((*latIter).second).graph_DetEff_v_Curr = " << ((*latIter).second).graph_DetEff_v_Curr << endl;
            ((*latIter).second).graph_DetEff_v_Curr->Write();
            
            //Debugging
            cout<<"TestBeamAnalyzer::makeHistogramsEff - No Fault 2_b_ii_6" <<endl;
            
            //Fit The Curve - One Latency (HVDrift)
            //======================================================
            TGraphErrors *tempEffCurve_HVDrift = (TGraphErrors *) ((*latIter).second).graph_DetEff_v_HVDrift->Clone("tempEffCurve_HVDrift");
            
            ((*latIter).second).fit_DetEff_v_HVDrift = new TF1(Form("Fit_%s_Lat%s_DetEff_v_HVDrift_R%s_R%s",((*detIter).first).c_str(), (getString((*latIter).first)).c_str(), getString( ((*detIter).second).run_initial ).c_str(), getString( ((*detIter).second).run_final ).c_str()  ), fitEff_Formula.c_str(), 0, 5000. );
            
            tempEffCurve_HVDrift->Fit(((*latIter).second).fit_DetEff_v_HVDrift, fitEff_Option.c_str() );
            
            //Plot The Curve - One Latency (HVDrift)
            //======================================================
            //Initialize the canvas - Single Latency
            TCanvas *canvas_DetEff_v_HVDrift = new TCanvas(
                Form("Plot_%s_Lat%s_DetEff_v_HVDrift_R%s_R%s",((*detIter).first).c_str(), (getString((*latIter).first)).c_str(), getString( ((*detIter).second).run_initial ).c_str(), getString( ((*detIter).second).run_final ).c_str() ),
                Form("%s_Lat%s_DetEff_v_HVDrift_R%s_R%s",((*detIter).first).c_str(), (getString((*latIter).first)).c_str(), getString( ((*detIter).second).run_initial ).c_str(), getString( ((*detIter).second).run_final ).c_str() ),
                700,700);
            
            //Go To Active Canvas & Draw Plot
            canvas_DetEff_v_HVDrift->cd();
            canvas_DetEff_v_HVDrift->SetTicky();
            canvas_DetEff_v_HVDrift->SetTickx();
            ((*latIter).second).graph_DetEff_v_HVDrift->SetTitle("");
            ((*latIter).second).graph_DetEff_v_HVDrift->GetYaxis()->SetRangeUser(0.,1.);
            ((*latIter).second).graph_DetEff_v_HVDrift->GetYaxis()->SetDecimals(true);
            ((*latIter).second).graph_DetEff_v_HVDrift->GetYaxis()->SetTitle("Efficiency");
            ((*latIter).second).graph_DetEff_v_HVDrift->GetYaxis()->SetTitleOffset(1.20);
            ((*latIter).second).graph_DetEff_v_HVDrift->GetXaxis()->SetTitle("HV_{Drift} #left(V#right)");
            ((*latIter).second).graph_DetEff_v_HVDrift->GetXaxis()->SetTitleOffset(1.10);
            ((*latIter).second).graph_DetEff_v_HVDrift->SetMarkerStyle(21);
            ((*latIter).second).graph_DetEff_v_HVDrift->SetMarkerSize(1.);
            ((*latIter).second).graph_DetEff_v_HVDrift->SetLineWidth(2.);
            ((*latIter).second).graph_DetEff_v_HVDrift->Draw("ap");
            if (drawFit) ((*latIter).second).fit_DetEff_v_HVDrift->Draw("same");
            
            //Draw Legend - SingleLat
            leg_DetEff_SingleLat->Draw("same");
            
            //Debugging
            cout<<"TestBeamAnalyzer::makeHistogramsEff - No Fault 2_b_ii_7" <<endl;
            
            //Draw Info Panel
            ((*latIter).second).texInfo_run         = new TLatex();     ((*latIter).second).texInfo_run->SetTextSize(0.03);
            ((*latIter).second).texInfo_beam        = new TLatex();     ((*latIter).second).texInfo_beam->SetTextSize(0.03);
            ((*latIter).second).texInfo_pulseLen    = new TLatex();     ((*latIter).second).texInfo_pulseLen->SetTextSize(0.03);
            ((*latIter).second).texInfo_delay       = new TLatex();     ((*latIter).second).texInfo_delay->SetTextSize(0.03);
            ((*latIter).second).texInfo_thresh      = new TLatex();     ((*latIter).second).texInfo_thresh->SetTextSize(0.03);
            ((*latIter).second).texInfo_lat         = new TLatex();     ((*latIter).second).texInfo_lat->SetTextSize(0.03);
            
            cmsPrelim->DrawLatex( (paintPos_X-5) * 1e-6 * fREquiv,1.01,"CMS Preliminary");
            
            ((*latIter).second).texInfo_run->DrawLatex(paintPos_X * 1e-6 * fREquiv, 0.9,Form("Runs %s - %s",(getString(((*latIter).second).run_initial)).c_str(),(getString(((*latIter).second).run_final)).c_str() ) );
            ((*latIter).second).texInfo_beam->DrawLatex(paintPos_X * 1e-6 * fREquiv,0.85,Form("Beam: %s",((*latIter).second).beamType.c_str()));
            ((*latIter).second).texInfo_pulseLen->DrawLatex(paintPos_X * 1e-6 * fREquiv,0.8,Form("MSPL%s",(getString(((*latIter).second).pulseLen)).c_str()));
            
            if(((*latIter).second).delay > 0){ //Case: Sync Mode
                ((*latIter).second).texInfo_delay->DrawLatex(paintPos_X * 1e-6 * fREquiv,0.75,Form("Sync. Mode; DLY = %sns",(getString(((*latIter).second).delay)).c_str()));
            } //End Case: Sync Mode
            else{ //Case: Async Mode
                ((*latIter).second).texInfo_delay->DrawLatex(paintPos_X * 1e-6 * fREquiv,0.75,"Async. Mode");
            } //End Case: Async Mode
            
            ((*latIter).second).texInfo_thresh->DrawLatex(paintPos_X * 1e-6 * fREquiv,0.7,Form("VFAT Thresh. = %s fC",(getString(((*latIter).second).thresh).c_str())));
            ((*latIter).second).texInfo_lat->DrawLatex(paintPos_X * 1e-6 * fREquiv,0.65,Form("VFAT Lat. = %s",(getString(((*latIter).first)).c_str())));
            
            //Write
            dir_Fits->cd();
            ((*latIter).second).fit_DetEff_v_HVDrift->Write();
            
            dir_Plots->cd();
            canvas_DetEff_v_HVDrift->Write();
            
            dir_RawGraphs->cd();
            ((*latIter).second).graph_DetEff_v_HVDrift->Write();
            
            //Debugging
            cout<<"TestBeamAnalyzer::makeHistogramsEff - No Fault 2_b_iii" <<endl;
            
            //Store the Curves - All Latencies for One Detector
            //======================================================
            //Set the Style (Current)
            ((*latIter).second).graph_DetEff_v_Curr->SetMarkerStyle( getCyclicMarkerStyle(std::distance(((*detIter).second).Scan_Lat.begin(),latIter) + 2 * std::distance(results.begin(),detIter) ) );
            ((*latIter).second).graph_DetEff_v_Curr->SetMarkerColor( getCyclicColor(std::distance(((*detIter).second).Scan_Lat.begin(),latIter) + 2 * std::distance(results.begin(),detIter) ) );
            ((*latIter).second).graph_DetEff_v_Curr->SetLineColor( getCyclicColor(std::distance(((*detIter).second).Scan_Lat.begin(),latIter) + 2 * std::distance(results.begin(),detIter) ) );
            ((*latIter).second).fit_DetEff_v_Curr->SetLineColor( getCyclicColor(std::distance(((*detIter).second).Scan_Lat.begin(),latIter) + 2 * std::distance(results.begin(),detIter) ) );
            
            //Set the Style (HVDrift)
            ((*latIter).second).graph_DetEff_v_HVDrift->SetMarkerStyle( getCyclicMarkerStyle(std::distance(((*detIter).second).Scan_Lat.begin(),latIter) + 2 * std::distance(results.begin(),detIter) ) );
            ((*latIter).second).graph_DetEff_v_HVDrift->SetMarkerColor( getCyclicColor(std::distance(((*detIter).second).Scan_Lat.begin(),latIter) + 2 * std::distance(results.begin(),detIter) ) );
            ((*latIter).second).graph_DetEff_v_HVDrift->SetLineColor( getCyclicColor(std::distance(((*detIter).second).Scan_Lat.begin(),latIter) + 2 * std::distance(results.begin(),detIter) ) );
            ((*latIter).second).fit_DetEff_v_HVDrift->SetLineColor( getCyclicColor(std::distance(((*detIter).second).Scan_Lat.begin(),latIter) + 2 * std::distance(results.begin(),detIter) ) );
            
            //Store in MultiGraph (Current)
            ((*detIter).second).mGraph_AllLatPlots->Add(((*latIter).second).graph_DetEff_v_Curr, "P");
            
            //Store in MultiGraph (HVDrift)
            ((*detIter).second).mGraph_AllLatPlots_HVDrift->Add(((*latIter).second).graph_DetEff_v_HVDrift, "P");
            
            //Setup Legend
            leg_DetEff_AllLat->AddEntry(((*latIter).second).graph_DetEff_v_Curr, Form("Latency %s", (getString((*latIter).first)).c_str() ), "LP" );
            
            //Debugging
            cout<<"TestBeamAnalyzer::makeHistogramsEff - No Fault 2_b_iv - LOOP" <<endl;
        } //End Loop Over Latencies for Each Detector
        
        //Debugging
        cout<<"TestBeamAnalyzer::makeHistogramsEff - No Fault 2_c" <<endl;
        
        //Store the Curves - Max Efficiency for Each Detector
        for(latIter = ((*detIter).second).Scan_Lat.begin(); latIter != ((*detIter).second).Scan_Lat.end(); latIter++ ){ //Loop Over Latencies
            if ( (*latIter).first == ((*detIter).second).latAtMaxEff ) { //Case: Max Found!
                //Add Distribution to Multi-Graph, it has the Eff Plateau for this Detector
                comparison.mGraph_AllDet_DetEff_v_Curr->Add(((*latIter).second).graph_DetEff_v_Curr, "P");
                
                //Add Distribtuion to Legend, it has the Eff Plateau for this Detector
                comparison.leg_AllDet_DetEff->AddEntry(((*latIter).second).graph_DetEff_v_Curr, Form("Latency %s: %s", (getString((*latIter).first)).c_str(), getParsedDetName( (*detIter).first ).c_str() ), "LP" );
                
                //Store Run Range of Comparison
                if (comparison.run_final   < ((*latIter).second).run_final  ) comparison.run_final   = ((*latIter).second).run_final;
                if (comparison.run_initial > ((*latIter).second).run_initial) comparison.run_initial = ((*latIter).second).run_initial;
                
                //Store Parameters for Info Panel
                if ( detIter == results.begin() ) { //Case: First Detector
                    //The below line is set in the constructor already
                    //comparison.infoMatch_Lat= true; //Set to True, we won't know if it should be false until we look at the others
                    
                    //Take from latIter to avoid potential propagation errors
                    comparison.delay        = ((*latIter).second).delay;
                    comparison.pulseLen     = ((*latIter).second).pulseLen;
                    comparison.beamType     = ((*latIter).second).beamType;
                } //End Case: First Detector
                /*
                else{ //Case: All Other Detectors
                    //Check to make sure information matches what we set for first detector
                    if (comparison.delay != ((*latIter).second).delay
                        || comparison.pulseLen != ((*latIter).second).pulseLen
                        || comparison.beamType != ((*latIter).second).beamType) { //Case: Detector Does Not Match Other Detector(s)
                        
                        cout<<"Warning Information Changed Mid Run When making ALL DETECTOR comparison using detector " << (*detIter).first <<endl;
                        cout<<"Pulse Length, Trigger Mode/Delay, or Beam Type does not match Expectation"<<endl;
                        cout<<"Please Cross-check input runs"<<endl;
                        
                        //Now set infoMatch to false
                        comparison.infoMatch_Lat = false;
                    } //End Case: Detector Does Not Match Other Detector(s)
                } //End Case: All Other Detectors
                */
            } //End Case: Max Found!
        } //End Loop Over Latencies
        
        //Plot The Curve - All Latencies for One Detector (Current)
        //======================================================
        //Switch to the canvas - All Latencies
        ((*detIter).second).canvas_DetEff_v_Curr->cd();
        ((*detIter).second).canvas_DetEff_v_Curr->SetTicky();
        ((*detIter).second).canvas_DetEff_v_Curr->SetTickx();
        ((*detIter).second).mGraph_AllLatPlots->Draw("a");  //Do this the first time to make TMultiGraph::GetHistogram() for this object valid
        ((*detIter).second).mGraph_AllLatPlots->GetHistogram()->SetTitleOffset(1.20,"Y");
        ((*detIter).second).mGraph_AllLatPlots->GetHistogram()->GetYaxis()->SetRangeUser(0.,1.);
        ((*detIter).second).mGraph_AllLatPlots->GetHistogram()->GetYaxis()->SetDecimals(true);
        ((*detIter).second).mGraph_AllLatPlots->GetHistogram()->SetTitleOffset(1.10,"X");
        ((*detIter).second).mGraph_AllLatPlots->Draw("a");  //Do this the second time to draw again the plot with the above formatting
        
        //Draw Legend
        leg_DetEff_AllLat->Draw("same");
        
        //Draw Info Panel
        ((*detIter).second).texInfo_run         = new TLatex();     ((*detIter).second).texInfo_run->SetTextSize(0.03);
        ((*detIter).second).texInfo_beam        = new TLatex();     ((*detIter).second).texInfo_beam->SetTextSize(0.03);
        ((*detIter).second).texInfo_name        = new TLatex();     ((*detIter).second).texInfo_name->SetTextSize(0.03);
        ((*detIter).second).texInfo_pulseLen    = new TLatex();     ((*detIter).second).texInfo_pulseLen->SetTextSize(0.03);
        ((*detIter).second).texInfo_delay       = new TLatex();     ((*detIter).second).texInfo_delay->SetTextSize(0.03);
        ((*detIter).second).texInfo_thresh      = new TLatex();     ((*detIter).second).texInfo_thresh->SetTextSize(0.03);
        
        cmsPrelim->DrawLatex(paintPos_X-5,1.01,"CMS Preliminary");
        
        ((*detIter).second).texInfo_name->DrawLatex(paintPos_X, 0.95, getParsedDetName((*detIter).first).c_str() );
        ((*detIter).second).texInfo_run->DrawLatex(paintPos_X, 0.9,Form("Runs %s - %s",(getString(((*detIter).second).run_initial)).c_str(),(getString(((*detIter).second).run_final)).c_str() ) );
        
        if( ((*detIter).second).infoMatch_Lat){ //Case: Info Same For All Latency Values
            ((*detIter).second).texInfo_beam->DrawLatex(paintPos_X,0.85,Form("Beam: %s",((*detIter).second).beamType.c_str()));
            ((*detIter).second).texInfo_pulseLen->DrawLatex(paintPos_X,0.8,Form("MSPL%s",(getString(((*detIter).second).pulseLen)).c_str()));
            
            if(((*detIter).second).delay > 0){ //Case: Sync Mode
                ((*detIter).second).texInfo_delay->DrawLatex(paintPos_X,0.75,Form("Sync. Mode; DLY = %sns",(getString(((*detIter).second).delay)).c_str()));
            } //End Case: Sync Mode
            else{ //Case: Async Mode
                ((*detIter).second).texInfo_delay->DrawLatex(paintPos_X,0.75,"Async. Mode");
            } //End Case: Async Mode
            
            ((*detIter).second).texInfo_thresh->DrawLatex(paintPos_X,0.7,Form("VFAT Thresh. = %s fC",(getString(((*detIter).second).thresh).c_str())));
        } //End Case: Info Same For All Latency Values
        
        //Debugging
        cout<<"TestBeamAnalyzer::makeHistogramsEff - No Fault 2_d" <<endl;
        
        //Write
        dir_ThisDet->cd();
        ((*detIter).second).mGraph_AllLatPlots->Write();
        ((*detIter).second).canvas_DetEff_v_Curr->Write();
        
        //Plot The Curve - All Latencies for One Detector (HVDrift)
        //======================================================
        //Switch to the canvas - All Latencies
        ((*detIter).second).canvas_DetEff_v_HVDrift->cd();
        ((*detIter).second).canvas_DetEff_v_HVDrift->SetTicky();
        ((*detIter).second).canvas_DetEff_v_HVDrift->SetTickx();
        ((*detIter).second).mGraph_AllLatPlots_HVDrift->Draw("a");  //Do this the first time to make TMultiGraph::GetHistogram() for this object valid
        ((*detIter).second).mGraph_AllLatPlots_HVDrift->GetHistogram()->SetTitleOffset(1.20,"Y");
        ((*detIter).second).mGraph_AllLatPlots_HVDrift->GetHistogram()->GetYaxis()->SetRangeUser(0.,1.);
        ((*detIter).second).mGraph_AllLatPlots_HVDrift->GetHistogram()->GetYaxis()->SetDecimals(true);
        ((*detIter).second).mGraph_AllLatPlots_HVDrift->GetHistogram()->SetTitleOffset(1.10,"X");
        ((*detIter).second).mGraph_AllLatPlots_HVDrift->Draw("a");  //Do this the second time to draw again the plot with the above formatting
        
        //Draw Legend
        leg_DetEff_AllLat->Draw("same");
        
        //Draw Info Panel
        ((*detIter).second).texInfo_run         = new TLatex();     ((*detIter).second).texInfo_run->SetTextSize(0.03);
        ((*detIter).second).texInfo_beam        = new TLatex();     ((*detIter).second).texInfo_beam->SetTextSize(0.03);
        ((*detIter).second).texInfo_name        = new TLatex();     ((*detIter).second).texInfo_name->SetTextSize(0.03);
        ((*detIter).second).texInfo_pulseLen    = new TLatex();     ((*detIter).second).texInfo_pulseLen->SetTextSize(0.03);
        ((*detIter).second).texInfo_delay       = new TLatex();     ((*detIter).second).texInfo_delay->SetTextSize(0.03);
        ((*detIter).second).texInfo_thresh      = new TLatex();     ((*detIter).second).texInfo_thresh->SetTextSize(0.03);
        
        cmsPrelim->DrawLatex( (paintPos_X-5) * 1e-6 * fREquiv,1.01,"CMS Preliminary");
        
        ((*detIter).second).texInfo_name->DrawLatex(paintPos_X * 1e-6 * fREquiv, 0.95, getParsedDetName((*detIter).first).c_str() );
        ((*detIter).second).texInfo_run->DrawLatex(paintPos_X * 1e-6 * fREquiv, 0.9,Form("Runs %s - %s",(getString(((*detIter).second).run_initial)).c_str(),(getString(((*detIter).second).run_final)).c_str() ) );
        
        if( ((*detIter).second).infoMatch_Lat){ //Case: Info Same For All Latency Values
            ((*detIter).second).texInfo_beam->DrawLatex(paintPos_X * 1e-6 * fREquiv,0.85,Form("Beam: %s",((*detIter).second).beamType.c_str()));
            ((*detIter).second).texInfo_pulseLen->DrawLatex(paintPos_X * 1e-6 * fREquiv,0.8,Form("MSPL%s",(getString(((*detIter).second).pulseLen)).c_str()));
            
            if(((*detIter).second).delay > 0){ //Case: Sync Mode
                ((*detIter).second).texInfo_delay->DrawLatex(paintPos_X * 1e-6 * fREquiv,0.75,Form("Sync. Mode; DLY = %sns",(getString(((*detIter).second).delay)).c_str()));
            } //End Case: Sync Mode
            else{ //Case: Async Mode
                ((*detIter).second).texInfo_delay->DrawLatex(paintPos_X * 1e-6 * fREquiv,0.75,"Async. Mode");
            } //End Case: Async Mode
            
            ((*detIter).second).texInfo_thresh->DrawLatex(paintPos_X * 1e-6 * fREquiv,0.7,Form("VFAT Thresh. = %s fC",(getString(((*detIter).second).thresh).c_str())));
        } //End Case: Info Same For All Latency Values
        
        //Debugging
        cout<<"TestBeamAnalyzer::makeHistogramsEff - No Fault 2_d" <<endl;
        
        //Write
        dir_ThisDet->cd();
        ((*detIter).second).mGraph_AllLatPlots_HVDrift->Write();
        ((*detIter).second).canvas_DetEff_v_HVDrift->Write();
        
        //Check to see if info matches across runs
        if(!((*detIter).second).infoMatch_Lat) comparison.infoMatch_Lat = ((*detIter).second).infoMatch_Lat;
        
        //Debugging
        cout<<"TestBeamAnalyzer::makeHistogramsEff - No Fault 2_e - LOOP" <<endl;
    } //End Loop Over Detectors
    
    //Plot The Curve - Highest Efficiencies for Each Detector (Current)
    //======================================================
    //Append The Name to Include The Runs!
    tempHistoName = ((string)comparison.canvas_AllDet_DetEff_v_Curr->GetName() ) + "_R" + getString( comparison.run_initial ) + "_R" + getString( comparison.run_final );
    comparison.canvas_AllDet_DetEff_v_Curr->SetName(tempHistoName.c_str() );
    
    //Go To Active Canvas & Draw Plot
    comparison.canvas_AllDet_DetEff_v_Curr->cd();
    comparison.canvas_AllDet_DetEff_v_Curr->SetTicky();
    comparison.canvas_AllDet_DetEff_v_Curr->SetTickx();
    comparison.mGraph_AllDet_DetEff_v_Curr->Draw("a");  //Do this the first time to make TMultiGraph::GetHistogram() for this object valid
    
    //Prevents Weird ROOT Shenanigans
    if (comparison.mGraph_AllDet_DetEff_v_Curr->GetHistogram() ) { //Case: Valid Pointer To Histogram
        comparison.mGraph_AllDet_DetEff_v_Curr->GetHistogram()->SetTitleOffset(1.20,"Y");
        comparison.mGraph_AllDet_DetEff_v_Curr->GetHistogram()->GetYaxis()->SetRangeUser(0.,1.);
        comparison.mGraph_AllDet_DetEff_v_Curr->GetHistogram()->GetYaxis()->SetDecimals(true);
        comparison.mGraph_AllDet_DetEff_v_Curr->GetHistogram()->SetTitleOffset(1.10,"X");
        comparison.mGraph_AllDet_DetEff_v_Curr->Draw("a");  //Do this the second time to draw again the plot with the above formatting
        
        //Plot Fit
        if (drawFit) { //Case: Draw Fit
            for (unsigned int i=0; i < vec_detNames.size(); i++) { //Loop Over vec_detNames
                results[vec_detNames[i]].Scan_Lat[results[vec_detNames[i]].latAtMaxEff].fit_DetEff_v_Curr->Draw("same");
            } //End Loop Over vec_detNames
        } //End Case: Draw Fit
    } //End Case: Valid Pointer To Histogram
    else { //Case: No Valid Pointer To Histogram, CHEAT!
        float minCurr = (*min_element( results[vec_detNames[0]].Scan_Lat[results[vec_detNames[0]].latAtMaxEff].currScan.begin(), results[vec_detNames[0]].Scan_Lat[results[vec_detNames[0]].latAtMaxEff].currScan.end() ) );
        float maxCurr = (*max_element( results[vec_detNames[0]].Scan_Lat[results[vec_detNames[0]].latAtMaxEff].currScan.begin(), results[vec_detNames[0]].Scan_Lat[results[vec_detNames[0]].latAtMaxEff].currScan.end() ) );
        
        //Ensure minCurr is a whole number divisible by 10
        if ( ( ( (int)floor(minCurr) ) % 10 ) == 0 ) {
            minCurr = floor(minCurr) - 10;
        }
        else{
            minCurr = floor(minCurr) - ( ( (int) floor(minCurr) ) % 10 );
        }
        
        //Ensure maxCurr is a whole number divisible by 10
        if ( ( ( (int)ceil(maxCurr) ) % 10 ) == 0 ) {
            maxCurr = ceil(maxCurr) + 10;
        }
        else {
            maxCurr = ceil(maxCurr) + (10 - ( (int) ceil(maxCurr) ) % 10 );
        }
        
        TH1F *tempHisto = new TH1F("tempHisto","",maxCurr-minCurr,minCurr,maxCurr);
        tempHisto->SetStats(false);
        tempHisto->SetTitleOffset(1.20,"Y");
        tempHisto->SetTitleOffset(1.10,"X");
        tempHisto->GetYaxis()->SetDecimals(true);
        tempHisto->GetYaxis()->SetRangeUser(0.,1.);
        tempHisto->GetYaxis()->SetTitle("Efficiency");
        tempHisto->GetXaxis()->SetTitle("Current Supplied to HV Divider #left(#muA#right)");
        tempHisto->GetXaxis()->SetLabelOffset(0.012);
        tempHisto->Draw();
        //comparison.mGraph_AllDet_DetEff_v_Curr->Draw("sameP");  //Do this the second time to draw again the plot with the above formatting
        
        //This hack is so dumb...The statements under the if portion work perfectly for me on lxplus; but they do not work on cms904fast and cause a crash...suspect differing versions of ROOT
        for (unsigned int i=0; i < vec_detNames.size(); i++) { //Loop Over vec_detNames
            results[vec_detNames[i]].Scan_Lat[results[vec_detNames[i]].latAtMaxEff].graph_DetEff_v_Curr->Draw("sameP");
            
            if (drawFit) results[vec_detNames[i]].Scan_Lat[results[vec_detNames[i]].latAtMaxEff].fit_DetEff_v_Curr->Draw("same");
        } //End Loop Over vec_detNames
    } //End Case: No Valid Pointer To Histogram, CHEAT!
    
    //comparison.mGraph_AllDet_DetEff_v_Curr->Draw("a");  //Do this the second time to draw again the plot with the above formatting
    
    //Draw Legend
    comparison.leg_AllDet_DetEff->Draw("same");
    
    //Draw Info Panel
    cmsPrelim->DrawLatex(paintPos_X-5,1.01,"CMS Preliminary");
    
    comparison.texInfo_run->DrawLatex(paintPos_X, 0.9,Form("Runs %s - %s",(getString(comparison.run_initial)).c_str(),(getString(comparison.run_final)).c_str() ) );
    
    if( comparison.infoMatch_Lat){ //Case: Info Same For All Latency Values
        comparison.texInfo_beam->DrawLatex(paintPos_X,0.85,Form("Beam: %s",comparison.beamType.c_str()));
        comparison.texInfo_pulseLen->DrawLatex(paintPos_X,0.8,Form("MSPL%s",(getString(comparison.pulseLen)).c_str()));
        
        if( comparison.delay > 0){ //Case: Sync Mode
            comparison.texInfo_delay->DrawLatex(paintPos_X,0.75,Form("Sync. Mode; DLY = %sns",(getString(comparison.delay)).c_str()));
        } //End Case: Sync Mode
        else{ //Case: Async Mode
            comparison.texInfo_delay->DrawLatex(paintPos_X,0.75,"Async. Mode");
        } //End Case: Async Mode
    } //End Case: Info Same For All Latency Values
    
    //Write
    TDirectory *dir_Comp = dir_Detectors->mkdir("Comparison");  dir_Comp->cd();
    
    comparison.mGraph_AllDet_DetEff_v_Curr->Write();
    comparison.canvas_AllDet_DetEff_v_Curr->Write();
    
    //Plot The Curve - Highest Efficiencies for Each Detector (HVDrift)
    //======================================================
    //Append The Name to Include The Runs!
    tempHistoName = ((string)comparison.canvas_AllDet_DetEff_v_HVDrift->GetName() ) + "_R" + getString( comparison.run_initial ) + "_R" + getString( comparison.run_final );
    comparison.canvas_AllDet_DetEff_v_HVDrift->SetName(tempHistoName.c_str() );
    
    //Go To Active Canvas & Draw Plot
    comparison.canvas_AllDet_DetEff_v_HVDrift->cd();
    comparison.canvas_AllDet_DetEff_v_HVDrift->SetTicky();
    comparison.canvas_AllDet_DetEff_v_HVDrift->SetTickx();
    comparison.mGraph_AllDet_DetEff_v_HVDrift->Draw("a");  //Do this the first time to make TMultiGraph::GetHistogram() for this object valid
    
    //Prevents Weird ROOT Shenanigans
    if (comparison.mGraph_AllDet_DetEff_v_HVDrift->GetHistogram() ) { //Case: Valid Pointer To Histogram
        comparison.mGraph_AllDet_DetEff_v_HVDrift->GetHistogram()->SetTitleOffset(1.20,"Y");
        comparison.mGraph_AllDet_DetEff_v_HVDrift->GetHistogram()->GetYaxis()->SetRangeUser(0.,1.);
        comparison.mGraph_AllDet_DetEff_v_HVDrift->GetHistogram()->GetYaxis()->SetDecimals(true);
        comparison.mGraph_AllDet_DetEff_v_HVDrift->GetHistogram()->SetTitleOffset(1.10,"X");
        comparison.mGraph_AllDet_DetEff_v_HVDrift->Draw("a");  //Do this the second time to draw again the plot with the above formatting
        
        //Plot Fits
        if (drawFit) { //Case: Draw Fit
            for (unsigned int i=0; i < vec_detNames.size(); i++) { //Loop Over vec_detNames
                results[vec_detNames[i]].Scan_Lat[results[vec_detNames[i]].latAtMaxEff].fit_DetEff_v_HVDrift->Draw("same");
            } //End Loop Over vec_detNames
        } //End Case: Draw Fit
    } //End Case: Valid Pointer To Histogram
    else { //Case: No Valid Pointer To Histogram, CHEAT!
        float minCurr = (*min_element( results[vec_detNames[0]].Scan_Lat[results[vec_detNames[0]].latAtMaxEff].currScan.begin(), results[vec_detNames[0]].Scan_Lat[results[vec_detNames[0]].latAtMaxEff].currScan.end() ) );
        float maxCurr = (*max_element( results[vec_detNames[0]].Scan_Lat[results[vec_detNames[0]].latAtMaxEff].currScan.begin(), results[vec_detNames[0]].Scan_Lat[results[vec_detNames[0]].latAtMaxEff].currScan.end() ) );
        
        //Convert to HVDrift
        float minHVDrift = minCurr * 1e-6 * fREquiv;
        float maxHVDrift = maxCurr * 1e-6 * fREquiv;
        
        //Ensure minHVDrift is a whole number divisible by 100
        if ( ( ( (int)floor(minHVDrift) ) % 100 ) == 0 ) {
            minHVDrift = floor(minHVDrift) - 100;
        }
        else{
            minHVDrift = floor(minHVDrift) - ( ( (int) floor(minHVDrift) ) % 100 );
        }
        
        //Ensure maxHVDrift is a whole number divisible by 100
        if ( ( ( (int)ceil(maxHVDrift) ) % 100 ) == 0 ) {
            maxHVDrift = ceil(maxHVDrift) + 100;
        }
        else {
            maxHVDrift = ceil(maxHVDrift) + (100 - ( (int) ceil(maxHVDrift) ) % 100 );
        }
        
        TH1F *tempHisto_HV = new TH1F("tempHisto_HV","",maxHVDrift-minHVDrift,minHVDrift,maxHVDrift);
        tempHisto_HV->SetStats(false);
        tempHisto_HV->SetTitleOffset(1.20,"Y");
        tempHisto_HV->SetTitleOffset(1.10,"X");
        tempHisto_HV->GetYaxis()->SetDecimals(true);
        tempHisto_HV->GetYaxis()->SetRangeUser(0.,1.);
        tempHisto_HV->GetYaxis()->SetTitle("Efficiency");
        tempHisto_HV->GetXaxis()->SetTitle("HV_{Drift} #left(V#right)");
        tempHisto_HV->GetXaxis()->SetLabelOffset(0.012);
        tempHisto_HV->Draw();
        
        //This hack is so dumb...The statements under the if portion work perfectly for me on lxplus; but they do not work on cms904fast and cause a crash...suspect differing versions of ROOT
        for (unsigned int i=0; i < vec_detNames.size(); i++) { //Loop Over vec_detNames
            results[vec_detNames[i]].Scan_Lat[results[vec_detNames[i]].latAtMaxEff].graph_DetEff_v_HVDrift->Draw("sameP");
            
            if (drawFit) results[vec_detNames[i]].Scan_Lat[results[vec_detNames[i]].latAtMaxEff].fit_DetEff_v_HVDrift->Draw("same");
        } //End Loop Over vec_detNames
    } //End Case: No Valid Pointer To Histogram, CHEAT!
    
    //Draw Legend
    comparison.leg_AllDet_DetEff->Draw("same");
    
    //Draw Info Panel
    cmsPrelim->DrawLatex( (paintPos_X-5) * 1e-6 * fREquiv,1.01,"CMS Preliminary");
    
    comparison.texInfo_run->DrawLatex(paintPos_X * 1e-6 * fREquiv, 0.9,Form("Runs %s - %s",(getString(comparison.run_initial)).c_str(),(getString(comparison.run_final)).c_str() ) );
    
    if( comparison.infoMatch_Lat){ //Case: Info Same For All Latency Values
        comparison.texInfo_beam->DrawLatex(paintPos_X * 1e-6 * fREquiv,0.85,Form("Beam: %s",comparison.beamType.c_str()));
        comparison.texInfo_pulseLen->DrawLatex(paintPos_X * 1e-6 * fREquiv,0.8,Form("MSPL%s",(getString(comparison.pulseLen)).c_str()));
        
        if( comparison.delay > 0){ //Case: Sync Mode
            comparison.texInfo_delay->DrawLatex(paintPos_X * 1e-6 * fREquiv,0.75,Form("Sync. Mode; DLY = %sns",(getString(comparison.delay)).c_str()));
        } //End Case: Sync Mode
        else{ //Case: Async Mode
            comparison.texInfo_delay->DrawLatex(paintPos_X * 1e-6 * fREquiv,0.75,"Async. Mode");
        } //End Case: Async Mode
    } //End Case: Info Same For All Latency Values
    
    //Write
    dir_Comp->cd();
    
    comparison.mGraph_AllDet_DetEff_v_HVDrift->Write();
    comparison.canvas_AllDet_DetEff_v_HVDrift->Write();
    
    //Debugging
    cout<<"TestBeamAnalyzer::makeHistogramsEff - No Fault End" <<endl;
    
    return;
} //End TestBeamAnalyzer::makeHistogramsEff()

void TestBeamAnalyzer::makeHistogramsTDC(string input, string option){
    //Variable Declaration
    float curr_max      = 0;
    
    float fHVDrift      = 0;
    
    float maxPeakInt    = 0;
    
    float paintPos_Curr = 1e5;
    float paintPos_Dly  = 1e5;
    //float paintPos_Time = 1e5;
    float paintPos_Time = 10;
    
    std::map<string,DetResults,cmp_str>::iterator detIter;
    
    string tempHistoName = "";
    
    TDirectory *dir_Detectors;
    TDirectory *dir_Comp;
    
    TFile *TFOutput = new TFile(input.c_str(), option.c_str(), "", 1);
    
    TLatex *cmsPrelim = new TLatex(); cmsPrelim->SetTextSize(0.03);
    
    //Debugging
    //cout<<"TestBeamAnalyzer::makeHistogramsTDC() - No Fault 1" << endl;
    
    //Check if File Exists Already
    if (option.compare("RECREATE") == 0 || option.compare("CREATE") == 0 ) { //Case: TFOutput Does Not Exist, Create File Structure
        dir_Detectors   = TFOutput->mkdir("Detectors");
            dir_Comp    = dir_Detectors->mkdir("Comparison");
    } //End Case: TFOutput Does Not Exist, Create File Structure
    else{ //Case: TFOutput Exists, get Previously Created File Structure
        if ( TFOutput->GetDirectory("Detectors", false, "GetDirectory") == 0) { //Case: Base File Structure Found
            dir_Detectors   = TFOutput->mkdir("Detectors");
                dir_Comp    = dir_Detectors->mkdir("Comparison");
        } //End Case: Base File Structure Found
        else{ //Case: Base File Structure Not Found
            dir_Detectors   = TFOutput->GetDirectory("Detectors", false, "GetDirectory");
                dir_Comp    = dir_Detectors->GetDirectory("Comparison", false, "GetDirectory");
        } //End Case: Base File Structure Not Found
    } //End Case: TFOutput Exists, get Previously Created File Structure
    
    //Debugging
    //cout<<"TestBeamAnalyzer::makeHistogramsTDC() - No Fault 2" << endl;
    
    //Setup Legend - All Detectors
    comparison.leg_AllDet_MaxTrigEff_v_Curr = new TLegend(0.15,0.55-0.05*(float)results.size(),0.45,0.60);
    comparison.leg_AllDet_MaxTrigEff_v_Curr->SetFillColor(kWhite);
    comparison.leg_AllDet_MaxTrigEff_v_Curr->SetLineColor(kWhite);
    
    //comparison.leg_AllDet_MaxTrigEff_v_Delay = new TLegend(0.15,0.55-0.05*(float)results.size(),0.45,0.60);
    comparison.leg_AllDet_MaxTrigEff_v_Delay = new TLegend(0.55,0.4-0.05*(float)results.size(),0.85,0.45);
    comparison.leg_AllDet_MaxTrigEff_v_Delay->SetFillColor(kWhite);
    comparison.leg_AllDet_MaxTrigEff_v_Delay->SetLineColor(kWhite);
    
    comparison.leg_AllDet_TimeRes = new TLegend(0.15,0.55-0.05*(float)results.size(),0.45,0.60);
    comparison.leg_AllDet_TimeRes->SetFillColor(kWhite);
    comparison.leg_AllDet_TimeRes->SetLineColor(kWhite);
    
    //Debugging
    //cout<<"TestBeamAnalyzer::makeHistogramsTDC() - No Fault 3" << endl;
    
    for (detIter = results.begin(); detIter != results.end(); detIter++) { //Loop Over Detectors
        //Debugging
        //cout<<"TestBeamAnalyzer::makeHistogramsTDC() - No Fault 3_a" << endl;
        
        TDirectory *dir_ThisDet = dir_Detectors->mkdir( ( (*detIter).first).c_str() );
        
        map<int,InfoPerDelay,cmp_int>::iterator dlyIter;
        
        //Determine initial run number, final run number, and paintPos_Dly
        //Yes We need to Loop Over Delyas in a separate occassion
        //Need to prep run numbers before plotting
        ((*detIter).second).run_initial = 60000;
        ((*detIter).second).run_final   = 0;
        for (dlyIter=((*detIter).second).Scan_DLY.begin(); dlyIter!=((*detIter).second).Scan_DLY.end(); dlyIter++) {
            //Set the Run Range
            if ( ((*detIter).second).run_initial > ((*dlyIter).second).run_initial )    ((*detIter).second).run_initial    = ((*dlyIter).second).run_initial;
            if ( ((*detIter).second).run_final   < ((*dlyIter).second).run_final )      ((*detIter).second).run_final      = ((*dlyIter).second).run_final;
            
            //Set the Delay
            if (paintPos_Dly > (*dlyIter).first) {paintPos_Dly = (*dlyIter).first;}
        } //End Loop Over Delays
        
        //Debugging
        //cout<<"TestBeamAnalyzer::makeHistogramsTDC() - No Fault 3_b" << endl;
        
        //Initialize graph_MaxTrigEff_v_Delay
        ((*detIter).second).graph_MaxTrigEff_v_Delay = new TGraphErrors( ( (*detIter).second).Scan_DLY.size() );
        ((*detIter).second).graph_MaxTrigEff_v_Delay->SetName(Form("%s_MaxTrigEff_v_Delay_R%s_R%s", ((*detIter).first).c_str(), getString( ((*detIter).second).run_initial ).c_str(), getString( ((*detIter).second).run_final ).c_str() ) );
        
        //Initialize canvas_MaxTrigEff_v_Delay
        ((*detIter).second).canvas_MaxTrigEff_v_Delay = new TCanvas(
            Form("Plot_%s_MaxTrigEff_v_Delay_R%s_R%s", ((*detIter).first).c_str(), getString( ((*detIter).second).run_initial ).c_str(), getString( ((*detIter).second).run_final ).c_str() ),
            Form("%s_MaxTrigEff_v_Delay_R%s_R%s",  ((*detIter).first).c_str(), getString( ((*detIter).second).run_initial ).c_str(), getString( ((*detIter).second).run_final ).c_str() ),
            700,700);
        
        //Setup Legend - All Delays
        TLegend *leg_MaxTrigEff_v_Delay = new TLegend(0.15,0.55,0.35,0.60);
        leg_MaxTrigEff_v_Delay->SetLineColor(0);
        leg_MaxTrigEff_v_Delay->SetFillColor(0);
        
        //Debugging
        //cout<<"TestBeamAnalyzer::makeHistogramsTDC() - No Fault 3_c" << endl;
        
        for (dlyIter = ((*detIter).second).Scan_DLY.begin(); dlyIter != ((*detIter).second).Scan_DLY.end(); dlyIter++) { //Loop Over Delays
            
            //Debugging
            //cout<<"TestBeamAnalyzer::makeHistogramsTDC() - No Fault 3_c_i" << endl;
            
            if (meas_TDC_ClockScan) { // Case: meas_TDC_ClockScan
                //Initialize TGraphErrors for This Delay
                ((*dlyIter).second).graph_MaxTrigEff_v_Curr = new TGraphErrors( ( (*dlyIter).second).currScan.size() );
                
                ((*dlyIter).second).graph_MaxTrigEff_v_Curr->SetName(Form("%s_DLY%s_MaxTrigEff_v_Curr_R%s_R%s", ((*detIter).first).c_str(), (getString((*dlyIter).first ) ).c_str(), getString( ((*detIter).second).run_initial ).c_str(), getString( ((*detIter).second).run_final ).c_str() ) );
                
                //Loop Over Currents
                for (unsigned int i=0; i < ((*dlyIter).second).currScan.size(); i++) { //Loop Over Currents For This Delay
                    //Determine Paint Position
                    if ( ((*dlyIter).second).currScan[i] < paintPos_Curr ) { paintPos_Curr = ((*dlyIter).second).currScan[i]; }
                    
                    //Reset Max Peak Int for this Current
                    maxPeakInt = 0;
                    
                    //Get the Peaks for this Current Value!
                    vector<std::map<string,float> >::iterator pkIter = ((*dlyIter).second).vec_allPeakInfo[i].begin();
                    
                    //Loop Over The Peaks for This Current!
                    for (pkIter; pkIter != ((*dlyIter).second).vec_allPeakInfo[i].end(); pkIter++) { //Loop Over Peaks For This Current!
                        if ( maxPeakInt < (*pkIter)[peakKey_Int] ) {
                            maxPeakInt = (*pkIter)[peakKey_Int];
                        }
                    } //End Loop Over Peaks For This Current!
                    
                    //Set Efficiency
                    //float efficiency = maxPeakInt / ((*dlyIter).second).vec_totalTrigs[i];
                    float efficiency = maxPeakInt / ((*dlyIter).second).vec_totalTrigs[i];
                    
                    //Set TGraphError Points - Independent Variable Imon
                    ((*dlyIter).second).graph_MaxTrigEff_v_Curr->SetPoint(i,((*dlyIter).second).currScan[i], efficiency);
                    ((*dlyIter).second).graph_MaxTrigEff_v_Curr->SetPointError(i, 0, sqrt( ( efficiency * (1-efficiency) ) / ((*dlyIter).second).vec_totalTrigs[i] ) );
                    
                    //Set TGraphError Points - Independent Variable Delay
                    if ( ((*dlyIter).second).currScan.size() == 1 ) { //Case: Only One Current Value
                        ((*detIter).second).graph_MaxTrigEff_v_Delay->SetPoint(std::distance( ((*detIter).second).Scan_DLY.begin(), dlyIter), (*dlyIter).first, efficiency );
                        ((*detIter).second).graph_MaxTrigEff_v_Delay->SetPointError(std::distance( ((*detIter).second).Scan_DLY.begin(), dlyIter), 0, sqrt( ( efficiency * (1-efficiency) ) / ((*dlyIter).second).vec_totalTrigs[i] ) );
                    } //End Case: Only One Current Value
                    
                    //Store the Clock Cycle Histograms
                    if (comparison.map_canvas_AllDet_ClkCyl.count( (*dlyIter).first ) > 0 ) { //Case: Delay Exists Already
                        if ( (comparison.map_canvas_AllDet_ClkCyl[(*dlyIter).first]).count( ( (*dlyIter).second).currScan[i] ) > 0 ) { //Case: Current Exists Already
                            //Change the active canvas
                            ((comparison.map_canvas_AllDet_ClkCyl[(*dlyIter).first])[((*dlyIter).second).currScan[i]])->cd();
                            
                            //Draw Histogram
                            ((*dlyIter).second).vec_timeResHistos[i]->SetLineColor(getCyclicColor(std::distance(results.begin(), detIter ) ) );
                            ((*dlyIter).second).vec_timeResHistos[i]->SetFillColor(getCyclicColor(std::distance(results.begin(), detIter ) ) );
                            ((*dlyIter).second).vec_timeResHistos[i]->Draw("same hist");
                            
                            //Add to Legend
                            if (i==0) {
                                (comparison.map_leg_AllDet_ClkCyl[(*dlyIter).first])->AddEntry(((*dlyIter).second).vec_timeResHistos[i], getParsedDetName( (*detIter).first ).c_str(), "F");
                            }
                            
                            //Change the active directory
                            ((comparison.map_dir_Curr_Parent_DLY[(*dlyIter).first])[((*dlyIter).second).currScan[i]])->cd();
                            
                            //Write to Root File
                            ((*dlyIter).second).vec_timeResHistos[i]->Write();
                        } //End Case: Current Exists Already
                        else{ //Case: Current Does Not Exist
                            TCanvas *canvas_AllDet_ClkCyl = new TCanvas(
                                Form("Plot_AllDet_ClkCyl_%suA_%sns", getString(((*dlyIter).second).currScan[i]).c_str(), getString((*dlyIter).first).c_str() ),
                                Form("Plot_AllDet_ClkCyl_%suA_%sns", getString(((*dlyIter).second).currScan[i]).c_str(), getString((*dlyIter).first).c_str() ),
                                700,700);
                            
                            //Draw Histogram
                            canvas_AllDet_ClkCyl->cd();
                            canvas_AllDet_ClkCyl->SetTicky();
                            canvas_AllDet_ClkCyl->SetTickx();
                            ((*dlyIter).second).vec_timeResHistos[i]->SetLineColor(getCyclicColor(std::distance(results.begin(), detIter ) ) );
                            ((*dlyIter).second).vec_timeResHistos[i]->SetFillColor(getCyclicColor(std::distance(results.begin(), detIter ) ) );
                            ((*dlyIter).second).vec_timeResHistos[i]->Draw("hist");
                            
                            //Add to Legend
                            //if (i==0) {
                              //  <#statements#>
                            //}
                            
                            //Store canvas into map structure
                            (comparison.map_canvas_AllDet_ClkCyl[(*dlyIter).first])[((*dlyIter).second).currScan[i]] = canvas_AllDet_ClkCyl;
                            
                            //Write to Root File
                            TDirectory *dir_Comp_DLY_Curr = (comparison.map_dir_DLY_Parent_Comp[(*dlyIter).first])->mkdir( getString( ((*dlyIter).second).currScan[i] ).c_str() );
                            
                            dir_Comp_DLY_Curr->cd();
                            ((*dlyIter).second).vec_timeResHistos[i]->Write();
                            
                            //Store directory into map structure
                            (comparison.map_dir_Curr_Parent_DLY[(*dlyIter).first])[((*dlyIter).second).currScan[i]] = dir_Comp_DLY_Curr;
                            
                            //Delete unnecessary pointers (maybe this causes a seg-fault?)
                            //delete canvas_AllDet_ClkCyl;
                            //delete dir_Comp_DLY_Curr;
                        } //End Case: Current Does Not Exist
                    } //End Case: Delay Exists Already
                    else{ //Case: Delay Does Not Exist
                        //Make a Canvas
                        TCanvas *canvas_AllDet_ClkCyl = new TCanvas(
                            Form("Plot_AllDet_ClkCyl_%suA_%sns", getString(((*dlyIter).second).currScan[i]).c_str(), getString((*dlyIter).first).c_str() ),
                            Form("Plot_AllDet_ClkCyl_%suA_%sns", getString(((*dlyIter).second).currScan[i]).c_str(), getString((*dlyIter).first).c_str() ),
                            700,700);
                        
                        //Draw Histogram
                        canvas_AllDet_ClkCyl->cd();
                        canvas_AllDet_ClkCyl->SetLogy();
                        canvas_AllDet_ClkCyl->SetTicky();
                        canvas_AllDet_ClkCyl->SetTickx();
                        ((*dlyIter).second).vec_timeResHistos[i]->SetLineColor(getCyclicColor(std::distance(results.begin(), detIter ) ) );
                        ((*dlyIter).second).vec_timeResHistos[i]->SetFillColor(getCyclicColor(std::distance(results.begin(), detIter ) ) );
                        ((*dlyIter).second).vec_timeResHistos[i]->SetTitle("");
                        ((*dlyIter).second).vec_timeResHistos[i]->SetStats(false);
                        ((*dlyIter).second).vec_timeResHistos[i]->GetYaxis()->SetRangeUser(2e-1,1e4);
                        ((*dlyIter).second).vec_timeResHistos[i]->Draw("hist");
                        
                        //Add to Legend (Draw Later)
                        if (i==0) { //Only do this at the starting current, re-use legend for all other currents
                            //Make the TLegend
                            TLegend *leg_AllDet_ClkCyl = new TLegend(0.15,0.55 - 0.05*(float)results.size(),0.45,0.60);
                            leg_AllDet_ClkCyl->SetFillColor(kWhite);
                            leg_AllDet_ClkCyl->SetLineColor(kWhite);
                            
                            //Store the Histogram
                            leg_AllDet_ClkCyl->AddEntry(((*dlyIter).second).vec_timeResHistos[i], getParsedDetName( (*detIter).first ).c_str(), "F");
                            
                            //Store the TLegend in map structure
                            comparison.map_leg_AllDet_ClkCyl[(*dlyIter).first] = leg_AllDet_ClkCyl;
                            
                            //Delete unnecessary pointers (maybe this causes a seg-fault?)
                            //delete leg_AllDet_ClkCyl;
                        } //End Making Legend
                        
                        //Store canvas into map structure
                        map<float, TCanvas*, cmp_flt> map_curr_2_canvas;
                        map_curr_2_canvas[((*dlyIter).second).currScan[i]] = canvas_AllDet_ClkCyl;
                        
                        comparison.map_canvas_AllDet_ClkCyl[(*dlyIter).first] = map_curr_2_canvas;
                        
                        //Write to Root File
                        TDirectory *dir_Comp_DLY            = dir_Comp->mkdir( getString( (*dlyIter).first ).c_str() );
                            TDirectory *dir_Comp_DLY_Curr   = dir_Comp_DLY->mkdir( getString( ((*dlyIter).second).currScan[i] ).c_str() );
                        
                        dir_Comp_DLY_Curr->cd();
                        ((*dlyIter).second).vec_timeResHistos[i]->Write();
                        
                        //Store directories into map structure
                        map<float, TDirectory*, cmp_flt> map_curr_2_dir;
                        map_curr_2_dir[((*dlyIter).second).currScan[i]] = dir_Comp_DLY_Curr;
                        
                        comparison.map_dir_Curr_Parent_DLY[(*dlyIter).first] = map_curr_2_dir;
                        comparison.map_dir_DLY_Parent_Comp[(*dlyIter).first] = dir_Comp_DLY;
                        
                        //Delete unnecessary pointers (maybe this causes a seg-fault?)
                        //delete canvas_AllDet_ClkCyl;
                        //delete dir_Comp_DLY;
                        //delete dir_Comp_DLY_Curr;
                    } //End Case: Delay Does Not Exist
                } //End Loop Over Currents For This Delay
                
                //Plot The Curve - One Delay : Max Trig Eff vs Imon
                //======================================================
                //Initialize the canvas - single delay
                ((*dlyIter).second).canvas_MaxTrigEff_v_Curr = new TCanvas(
                    Form("Plot_%s_DLY%s_MaxTrigEff_v_Curr_R%s_R%s",((*detIter).first).c_str(), getString( (*dlyIter).first).c_str(), getString( ((*detIter).second).run_initial ).c_str(), getString( ((*detIter).second).run_final ).c_str() ),
                    Form("%s_DLY%s_MaxTrigEff_v_Curr_R%s_R%s",((*detIter).first).c_str(), (getString((*dlyIter).first)).c_str(), getString( ((*detIter).second).run_initial ).c_str(), getString( ((*detIter).second).run_final ).c_str() ),
                    700,700);
                
                //Determine Paint Position
                /*for (unsigned int i=0; i < ((*dlyIter).second).currScan.size(); i++) {
                    if ( ((*dlyIter).second).currScan[i] < paintPos_Curr ) { paintPos_Curr = ((*dlyIter).second).currScan[i]; }
                }*/
                //Note the commented section below doesn't work if the runs are not taken in either increasing or decreasing order
                /*if(((*dlyIter).second).currScan[0] > ((*dlyIter).second).currScan.back()){ //Case: 0^th Member Highest Point
                 paintPos_Curr = ((*dlyIter).second).currScan.back();
                 } //End Case: 0^th Member Highest Point
                 else{ //Case: Last Member Highest Point
                 paintPos_Curr = ((*dlyIter).second).currScan[0];
                 } //End Case: Last Member Highest Point
                 */
                
                //Go To Active Canvas & Draw Plot
                ((*dlyIter).second).canvas_MaxTrigEff_v_Curr->cd();
                ((*dlyIter).second).canvas_MaxTrigEff_v_Curr->SetTicky();
                ((*dlyIter).second).canvas_MaxTrigEff_v_Curr->SetTickx();
                ((*dlyIter).second).graph_MaxTrigEff_v_Curr->SetTitle("");
                ((*dlyIter).second).graph_MaxTrigEff_v_Curr->GetYaxis()->SetRangeUser(0.,1.);
                ((*dlyIter).second).graph_MaxTrigEff_v_Curr->GetYaxis()->SetDecimals(true);
                ((*dlyIter).second).graph_MaxTrigEff_v_Curr->GetYaxis()->SetTitle("Efficiency to Trigger in One Clock Cylce");
                ((*dlyIter).second).graph_MaxTrigEff_v_Curr->GetYaxis()->SetTitleOffset(1.20);
                ((*dlyIter).second).graph_MaxTrigEff_v_Curr->GetXaxis()->SetTitle("Current Supplied to HV Divider #left(#muA#right)");
                ((*dlyIter).second).graph_MaxTrigEff_v_Curr->GetXaxis()->SetTitleOffset(1.10);
                ((*dlyIter).second).graph_MaxTrigEff_v_Curr->SetMarkerStyle(21);
                ((*dlyIter).second).graph_MaxTrigEff_v_Curr->SetMarkerSize(1.);
                ((*dlyIter).second).graph_MaxTrigEff_v_Curr->SetLineWidth(2.);
                ((*dlyIter).second).graph_MaxTrigEff_v_Curr->Draw("ap");
                
                //Draw Legend - SingleLat
                TLegend *leg_MaxTrigEff_SingleDLY = new TLegend(0.15,0.55,0.35,0.60);
                leg_MaxTrigEff_SingleDLY->SetLineColor(0);
                leg_MaxTrigEff_SingleDLY->SetFillColor(0);
                leg_MaxTrigEff_SingleDLY->AddEntry(((*dlyIter).second).graph_MaxTrigEff_v_Curr,((*detIter).first).c_str(),"LP");
                leg_MaxTrigEff_SingleDLY->Draw("same");
                
                //Draw Info Panel
                ((*dlyIter).second).texInfo_run         = new TLatex();     ((*dlyIter).second).texInfo_run->SetTextSize(0.03);
                ((*dlyIter).second).texInfo_beam        = new TLatex();     ((*dlyIter).second).texInfo_beam->SetTextSize(0.03);
                ((*dlyIter).second).texInfo_pulseLen    = new TLatex();     ((*dlyIter).second).texInfo_pulseLen->SetTextSize(0.03);
                ((*dlyIter).second).texInfo_delay       = new TLatex();     ((*dlyIter).second).texInfo_delay->SetTextSize(0.03);
                ((*dlyIter).second).texInfo_thresh      = new TLatex();     ((*dlyIter).second).texInfo_thresh->SetTextSize(0.03);
                
                cmsPrelim->DrawLatex(paintPos_Curr-10,1.01,"CMS Preliminary");
                
                ((*dlyIter).second).texInfo_run->DrawLatex(paintPos_Curr, 0.9,Form("Runs %s - %s",(getString(((*dlyIter).second).run_initial)).c_str(),(getString(((*dlyIter).second).run_final)).c_str() ) );
                
                if ( ((*detIter).second).infoMatch_DLY ) { //Case: Info Matches
                    ((*dlyIter).second).texInfo_beam->DrawLatex(paintPos_Curr,0.85,Form("Beam: %s",((*dlyIter).second).beamType.c_str()));
                    ((*dlyIter).second).texInfo_pulseLen->DrawLatex(paintPos_Curr,0.8,Form("MSPL%s",(getString(((*dlyIter).second).pulseLen)).c_str()));
                    ((*dlyIter).second).texInfo_delay->DrawLatex(paintPos_Curr,0.75,Form("Sync. Mode; DLY = %sns",(getString((*dlyIter).first).c_str())));
                    ((*dlyIter).second).texInfo_thresh->DrawLatex(paintPos_Curr,0.7,Form("VFAT Thresh. = %s fC",(getString(((*dlyIter).second).thresh).c_str())));
                } //End Case: Info Matches
                
                //Write
                TDirectory *dir_ThisDly = dir_ThisDet->mkdir( Form("DLY%s", (getString((*dlyIter).first)).c_str()) );
                
                TDirectory *dir_RawGraphs   = dir_ThisDly->mkdir("RawGraphs");
                TDirectory *dir_Plots       = dir_ThisDly->mkdir("PremadePlots");
                
                dir_RawGraphs->cd();
                ((*dlyIter).second).graph_MaxTrigEff_v_Curr->Write();
                
                dir_Plots->cd();
                ((*dlyIter).second).canvas_MaxTrigEff_v_Curr->Write();
                
                //Store the Curves - All Detectors
                //======================================================
                //Set the Style
                ((*dlyIter).second).graph_MaxTrigEff_v_Curr->SetMarkerStyle( getCyclicMarkerStyle(std::distance(((*detIter).second).Scan_DLY.begin(),dlyIter) + 2 * std::distance(results.begin(),detIter) ) );
                ((*dlyIter).second).graph_MaxTrigEff_v_Curr->SetMarkerColor( getCyclicColor(std::distance(((*detIter).second).Scan_DLY.begin(),dlyIter) + 2 * std::distance(results.begin(),detIter) ) );
                ((*dlyIter).second).graph_MaxTrigEff_v_Curr->SetLineColor( getCyclicColor(std::distance(((*detIter).second).Scan_DLY.begin(),dlyIter) + 2 * std::distance(results.begin(),detIter) ) );
                //((*dlyIter).second).graph_MaxTrigEff_v_Curr->SetMarkerStyle( getCyclicMarkerStyle(std::distance(((*detIter).second).Scan_DLY.begin(),dlyIter) ) );
                //((*dlyIter).second).graph_MaxTrigEff_v_Curr->SetMarkerColor( getCyclicColor(std::distance(((*detIter).second).Scan_DLY.begin(),dlyIter) ) );
                //((*dlyIter).second).graph_MaxTrigEff_v_Curr->SetLineColor( getCyclicColor(std::distance(((*detIter).second).Scan_DLY.begin(),dlyIter) ) );
                
                //Store in MultiGraph
                comparison.mGraph_AllDet_MaxTrigEff_v_Curr->Add(((*dlyIter).second).graph_MaxTrigEff_v_Curr, "P" );
                
                //Setup Legend
                comparison.leg_AllDet_MaxTrigEff_v_Curr->AddEntry(((*dlyIter).second).graph_MaxTrigEff_v_Curr, getParsedDetName( (*detIter).first ).c_str(), "LP" ); //Note we expect only one of these curves per detector, so that' swhy we use (*detIter).first here
            } //End Case: meas_TDC_ClockScan
            
            //Debugging
            //cout<<"TestBeamAnalyzer::makeHistogramsTDC() - No Fault 3_c_ii" << endl;
            
            if (meas_TDC_TimeRes) { //Case: meas_TDC_TimeRes
                //Debugging
                //cout<<"TestBeamAnalyzer::makeHistogramsTDC() - No Fault 3_c_ii_1" << endl;
                
                //Initialize TGraphErrors for This Delay - Time Resolution from RMS
                ((*detIter).second).graph_RMS_TimeRes_v_Curr = new TGraphErrors( ( (*dlyIter).second).currScan.size() );
                ((*detIter).second).graph_RMS_TimeRes_v_HVDrift = new TGraphErrors( ( (*dlyIter).second).currScan.size() );
                
                ((*detIter).second).graph_RMS_Deconvo_TimeRes_v_Curr = new TGraphErrors( ( (*dlyIter).second).currScan.size() );
                ((*detIter).second).graph_RMS_Deconvo_TimeRes_v_HVDrift = new TGraphErrors( ( (*dlyIter).second).currScan.size() );
                
                ((*detIter).second).graph_RMS_TimeRes_v_Curr->SetName(Form("%s_RMS_TimeRes_v_Curr_R%s_R%s", ((*detIter).first).c_str(), getString( ((*detIter).second).run_initial ).c_str(), getString( ((*detIter).second).run_final ).c_str() ) );
                ((*detIter).second).graph_RMS_TimeRes_v_HVDrift->SetName(Form("%s_RMS_TimeRes_v_HVDrift_R%s_R%s", ((*detIter).first).c_str(), getString( ((*detIter).second).run_initial ).c_str(), getString( ((*detIter).second).run_final ).c_str() ) );
                
                ((*detIter).second).graph_RMS_Deconvo_TimeRes_v_Curr->SetName(Form("%s_RMS_Deconvo_TimeRes_v_Curr_R%s_R%s", ((*detIter).first).c_str(), getString( ((*detIter).second).run_initial ).c_str(), getString( ((*detIter).second).run_final ).c_str() ) );
                ((*detIter).second).graph_RMS_Deconvo_TimeRes_v_HVDrift->SetName(Form("%s_RMS_Deconvo_TimeRes_v_HVDrift_R%s_R%s", ((*detIter).first).c_str(), getString( ((*detIter).second).run_initial ).c_str(), getString( ((*detIter).second).run_final ).c_str() ) );
                
                //Initialize TGraphErrors for This Delay - Time Resolution from Fit
                ((*detIter).second).graph_Fit_TimeRes_v_Curr = new TGraphErrors( ( (*dlyIter).second).currScan.size() );
                ((*detIter).second).graph_Fit_TimeRes_v_HVDrift = new TGraphErrors( ( (*dlyIter).second).currScan.size() );
                
                ((*detIter).second).graph_Fit_Deconvo_TimeRes_v_Curr = new TGraphErrors( ( (*dlyIter).second).currScan.size() );
                ((*detIter).second).graph_Fit_Deconvo_TimeRes_v_HVDrift = new TGraphErrors( ( (*dlyIter).second).currScan.size() );
                
                ((*detIter).second).graph_Fit_TimeRes_v_Curr->SetName(Form("%s_Fit_TimeRes_v_Curr_R%s_R%s", ((*detIter).first).c_str(), getString( ((*detIter).second).run_initial ).c_str(), getString( ((*detIter).second).run_final ).c_str() ) );
                ((*detIter).second).graph_Fit_TimeRes_v_HVDrift->SetName(Form("%s_Fit_TimeRes_v_HVDrift_R%s_R%s", ((*detIter).first).c_str(), getString( ((*detIter).second).run_initial ).c_str(), getString( ((*detIter).second).run_final ).c_str() ) );
                
                ((*detIter).second).graph_Fit_Deconvo_TimeRes_v_Curr->SetName(Form("%s_Fit_Deconvo_TimeRes_v_Curr_R%s_R%s", ((*detIter).first).c_str(), getString( ((*detIter).second).run_initial ).c_str(), getString( ((*detIter).second).run_final ).c_str() ) );
                ((*detIter).second).graph_Fit_Deconvo_TimeRes_v_HVDrift->SetName(Form("%s_Fit_Deconvo_TimeRes_v_HVDrift_R%s_R%s", ((*detIter).first).c_str(), getString( ((*detIter).second).run_initial ).c_str(), getString( ((*detIter).second).run_final ).c_str() ) );
                
                //Initialize TGraphErrors for This Delay - Chi^2 / NDF
                ((*detIter).second).graph_Fit_normChi2_v_Curr = new TGraphErrors( ( (*dlyIter).second).currScan.size() );
                ((*detIter).second).graph_Fit_normChi2_v_HVDrift = new TGraphErrors( ( (*dlyIter).second).currScan.size() );
                
                ((*detIter).second).graph_Fit_Deconvo_normChi2_v_Curr = new TGraphErrors( ( (*dlyIter).second).currScan.size() );
                ((*detIter).second).graph_Fit_Deconvo_normChi2_v_HVDrift = new TGraphErrors( ( (*dlyIter).second).currScan.size() );
                
                ((*detIter).second).graph_Fit_normChi2_v_Curr->SetName(Form("%s_Fit_normChi2_v_Curr_R%s_R%s", ((*detIter).first).c_str(), getString( ((*detIter).second).run_initial ).c_str(), getString( ((*detIter).second).run_final ).c_str() ) );
                ((*detIter).second).graph_Fit_normChi2_v_HVDrift->SetName(Form("%s_Fit_normChi2_v_HVDrift_R%s_R%s", ((*detIter).first).c_str(), getString( ((*detIter).second).run_initial ).c_str(), getString( ((*detIter).second).run_final ).c_str() ) );
                
                ((*detIter).second).graph_Fit_Deconvo_normChi2_v_Curr->SetName(Form("%s_Fit_Deconvo_normChi2_v_Curr_R%s_R%s", ((*detIter).first).c_str(), getString( ((*detIter).second).run_initial ).c_str(), getString( ((*detIter).second).run_final ).c_str() ) );
                ((*detIter).second).graph_Fit_Deconvo_normChi2_v_HVDrift->SetName(Form("%s_Fit_Deconvo_normChi2_v_HVDrift_R%s_R%s", ((*detIter).first).c_str(), getString( ((*detIter).second).run_initial ).c_str(), getString( ((*detIter).second).run_final ).c_str() ) );
                
                //Debugging
                //cout<<"TestBeamAnalyzer::makeHistogramsTDC() - No Fault 3_c_ii_2" << endl;
                
                //Loop Over Currents
                for (unsigned int i=0; i < ((*dlyIter).second).currScan.size(); i++) { //Loop Over Currents
                    //Determine HV_Drift
                    fHVDrift = ((*dlyIter).second).currScan[i] * 1e-6 * fREquiv;
                    
                    //Determine Paint Position - Current
                    if ( ((*dlyIter).second).currScan[i] < paintPos_Curr ) { paintPos_Curr = ((*dlyIter).second).currScan[i]; }
                    
                    //Determine Max Current
                    if ( ((*dlyIter).second).currScan[i] > curr_max ) {curr_max = ((*dlyIter).second).currScan[i];}
                    
                    //Create the Directory
                    TDirectory *dir_ThisCurr = dir_ThisDet->mkdir( getString( floor(((*dlyIter).second).currScan[i]) ).c_str() );
                    
                    //Debugging
                    //cout<<"TestBeamAnalyzer::makeHistogramsTDC() - No Fault 3_c_ii_2_a" << endl;
                    
                    //Set Time Resolution - RMS
                    ((*detIter).second).graph_RMS_TimeRes_v_Curr->SetPoint(i,((*dlyIter).second).currScan[i], ((*dlyIter).second).vec_rawRMS[i] );
                    ((*detIter).second).graph_RMS_TimeRes_v_Curr->SetPointError(i,0, ((*dlyIter).second).vec_rawRMSErr[i] );
                    
                    ((*detIter).second).graph_RMS_TimeRes_v_HVDrift->SetPoint(i,fHVDrift, ((*dlyIter).second).vec_rawRMS[i] );
                    ((*detIter).second).graph_RMS_TimeRes_v_Curr->SetPointError(i,0, ((*dlyIter).second).vec_rawRMSErr[i] );
                    
                    ((*detIter).second).graph_RMS_Deconvo_TimeRes_v_Curr->SetPoint(i,((*dlyIter).second).currScan[i], ((*dlyIter).second).vec_rawRMS_Deconvo[i] );
                    ((*detIter).second).graph_RMS_Deconvo_TimeRes_v_Curr->SetPointError(i,0, ((*dlyIter).second).vec_rawRMSErr_Deconvo[i] );
                    
                    ((*detIter).second).graph_RMS_Deconvo_TimeRes_v_HVDrift->SetPoint(i,fHVDrift, ((*dlyIter).second).vec_rawRMS_Deconvo[i] );
                    ((*detIter).second).graph_RMS_Deconvo_TimeRes_v_Curr->SetPointError(i,0, ((*dlyIter).second).vec_rawRMSErr_Deconvo[i] );
                    
                    //Debugging
                    //cout<<"TestBeamAnalyzer::makeHistogramsTDC() - No Fault 3_c_ii_2_b" << endl;
                    
                    //Check if Fit Performed - Before Deconvolution
                    if (((*dlyIter).second).vec_fitPerformed[i]) { //Case: i^th Peak Above the Noise
                        //Determine Paint Position - Time
                        //If the Fit was not performed this was initialized to 10
                        //Note the histogram should not be zoomed if the fit was not performed
                        paintPos_Time = (*((*dlyIter).second).vec_allPeakInfo[i].begin())[peakKey_LwrBd];
                        
                        //Set Time Resolution - Fit
                        ((*detIter).second).graph_Fit_TimeRes_v_Curr->SetPoint(i,((*dlyIter).second).currScan[i], ((*dlyIter).second).vec_timeResFits[i]->GetParameter(2) );
                        ((*detIter).second).graph_Fit_TimeRes_v_Curr->SetPointError(i,0, ((*dlyIter).second).vec_timeResFits[i]->GetParError(2) );
                        
                        ((*detIter).second).graph_Fit_TimeRes_v_HVDrift->SetPoint(i,fHVDrift, ((*dlyIter).second).vec_timeResFits[i]->GetParameter(2) );
                        ((*detIter).second).graph_Fit_TimeRes_v_HVDrift->SetPointError(i,0, ((*dlyIter).second).vec_timeResFits[i]->GetParError(2) );
                        
                        //Set Fit Chi^2 / nDoF
                        ((*detIter).second).graph_Fit_normChi2_v_Curr->SetPoint(i,((*dlyIter).second).currScan[i], ((*dlyIter).second).vec_timeResFits[i]->GetChisquare() / ((*dlyIter).second).vec_timeResFits[i]->GetNDF() );
                        //((*detIter).second).graph_Fit_TimeRes_v_Curr->SetPointError(i,0, ??? );
                        
                        ((*detIter).second).graph_Fit_normChi2_v_HVDrift->SetPoint(i,fHVDrift, ((*dlyIter).second).vec_timeResFits[i]->GetChisquare() / ((*dlyIter).second).vec_timeResFits[i]->GetNDF() );
                        //((*detIter).second).graph_Fit_TimeRes_v_HVDrift->SetPointError(i,0, ??? );
                        
                        //Set Data/Fit Ratio
                        tempHistoName = ((string)((*dlyIter).second).vec_timeResHistos[i]->GetName()) + "_Ratio";
                        TH1F *temp_TDC_histo = (TH1F*) ((*dlyIter).second).vec_timeResHistos[i]->Clone( tempHistoName.c_str() );
                        temp_TDC_histo->Divide(((*dlyIter).second).vec_timeResFits[i], 1.);
                        ((*dlyIter).second).vec_timeResHistoOverFits.push_back(temp_TDC_histo);
                        
                        //Plot Data Over Fit
                        TCanvas *canvas_TimeResPlotRatio = new TCanvas(
                            Form("Plot_%s_TimeRes_Ratio_%s", ((*dlyIter).second).vec_timeResHistos[i]->GetName(), getString( floor(((*dlyIter).second).currScan[i]) ).c_str() ),
                            Form("%s Time Res. Data/Fit for Current: %suA", ((*dlyIter).second).vec_timeResHistos[i]->GetName(), getString( floor(((*dlyIter).second).currScan[i]) ).c_str() ),
                            700,350);
                        
                        canvas_TimeResPlotRatio->cd();
                        canvas_TimeResPlotRatio->SetTicky();
                        canvas_TimeResPlotRatio->SetTickx();
                        //((*dlyIter).second).vec_timeResHistoOverFits[i]->SetMarkerStyle(21);
                        //((*dlyIter).second).vec_timeResHistoOverFits[i]->SetMarkerSize(1.);
                        //((*dlyIter).second).vec_timeResHistoOverFits[i]->SetLineWidth(2.);
                        //((*dlyIter).second).vec_timeResHistoOverFits[i]->GetYaxis()->SetRangeUser(0,2.);
                        //((*dlyIter).second).vec_timeResHistoOverFits[i]->Draw("E1");
                        
                        temp_TDC_histo->SetMarkerStyle(21);
                        temp_TDC_histo->SetMarkerSize(1.);
                        temp_TDC_histo->SetLineWidth(2.);
                        temp_TDC_histo->GetYaxis()->SetRangeUser(0,2.);
                        temp_TDC_histo->Draw("E1");
                        
                        cmsPrelim->DrawLatex(paintPos_Time,2.02,"CMS Preliminary");
                        
                        //Write
                        dir_ThisCurr->cd();
                        
                        //((*dlyIter).second).vec_timeResHistoOverFits[i]->Write();
                        temp_TDC_histo->Write();
                        
                        canvas_TimeResPlotRatio->Write();
                        
                        //Delete Pointer
                        delete canvas_TimeResPlotRatio;
                        delete temp_TDC_histo;
                    } //End Case: i^th Peak Above the Noise
                    
                    //Check if Fit Performed - After Deconvolution
                    if (((*dlyIter).second).vec_fitPerformed_Deconvo[i]) { //Case: i^th Peak Above the Noise
                        //Set Time Resolution - Fit
                        ((*detIter).second).graph_Fit_Deconvo_TimeRes_v_Curr->SetPoint(i,((*dlyIter).second).currScan[i], ((*dlyIter).second).vec_timeResFits_Deconvo[i]->GetParameter(0) );
                        ((*detIter).second).graph_Fit_Deconvo_TimeRes_v_Curr->SetPointError(i,0, ((*dlyIter).second).vec_timeResFits_Deconvo[i]->GetParError(0) );
                        
                        ((*detIter).second).graph_Fit_Deconvo_TimeRes_v_HVDrift->SetPoint(i,fHVDrift, ((*dlyIter).second).vec_timeResFits_Deconvo[i]->GetParameter(0) );
                        ((*detIter).second).graph_Fit_Deconvo_TimeRes_v_HVDrift->SetPointError(i,0, ((*dlyIter).second).vec_timeResFits_Deconvo[i]->GetParError(0) );
                        
                        //Set Fit Chi^2 / nDoF
                        ((*detIter).second).graph_Fit_Deconvo_normChi2_v_Curr->SetPoint(i,((*dlyIter).second).currScan[i], ((*dlyIter).second).vec_timeResFits_Deconvo[i]->GetChisquare() / ((*dlyIter).second).vec_timeResFits_Deconvo[i]->GetNDF() );
                        //((*detIter).second).graph_Fit_Deconvo_TimeRes_v_Curr->SetPointError(i,0, ??? );
                        
                        ((*detIter).second).graph_Fit_Deconvo_normChi2_v_HVDrift->SetPoint(i,fHVDrift, ((*dlyIter).second).vec_timeResFits_Deconvo[i]->GetChisquare() / ((*dlyIter).second).vec_timeResFits_Deconvo[i]->GetNDF() );
                        //((*detIter).second).graph_Fit_Deconvo_TimeRes_v_HVDrift->SetPointError(i,0, ??? );
                        
                        //Set Data/Fit Ratio
                        tempHistoName = ((string)((*dlyIter).second).vec_timeResHistos[i]->GetName()) + "_Deconvo_Ratio";
                        TH1F *temp_TDC_histo_Deconvo = (TH1F*) ((*dlyIter).second).vec_timeResHistos[i]->Clone( tempHistoName.c_str() );
                        temp_TDC_histo_Deconvo->Divide(((*dlyIter).second).vec_timeResFits_Deconvo[i], 1.);
                        ((*dlyIter).second).vec_timeResHistoOverFits_Deconvo.push_back(temp_TDC_histo_Deconvo);
                        
                        //Plot Data Over Fit
                        TCanvas *canvas_TimeResPlotRatio_Deconvo = new TCanvas(
                            Form("Plot_%s_TimeRes_Deconvo_Ratio_%s", ((*dlyIter).second).vec_timeResHistos[i]->GetName(), getString( floor(((*dlyIter).second).currScan[i]) ).c_str() ),
                            Form("%s Time Res. Data/Fit (Deconvo) for Current: %suA", ((*dlyIter).second).vec_timeResHistos[i]->GetName(), getString( floor(((*dlyIter).second).currScan[i]) ).c_str() ),
                            700,350);
                        
                        canvas_TimeResPlotRatio_Deconvo->cd();
                        canvas_TimeResPlotRatio_Deconvo->SetTicky();
                        canvas_TimeResPlotRatio_Deconvo->SetTickx();
                        //((*dlyIter).second).vec_timeResHistoOverFits[i]->SetMarkerStyle(21);
                        //((*dlyIter).second).vec_timeResHistoOverFits[i]->SetMarkerSize(1.);
                        //((*dlyIter).second).vec_timeResHistoOverFits[i]->SetLineWidth(2.);
                        //((*dlyIter).second).vec_timeResHistoOverFits[i]->GetYaxis()->SetRangeUser(0,2.);
                        //((*dlyIter).second).vec_timeResHistoOverFits[i]->Draw("E1");
                        
                        temp_TDC_histo_Deconvo->SetMarkerStyle(21);
                        temp_TDC_histo_Deconvo->SetMarkerSize(1.);
                        temp_TDC_histo_Deconvo->SetLineWidth(2.);
                        temp_TDC_histo_Deconvo->GetYaxis()->SetRangeUser(0,2.);
                        temp_TDC_histo_Deconvo->Draw("E1");
                        
                        cmsPrelim->DrawLatex(paintPos_Time,2.02,"CMS Preliminary");
                        
                        //Write
                        dir_ThisCurr->cd();
                        
                        //((*dlyIter).second).vec_timeResHistoOverFits[i]->Write();
                        temp_TDC_histo_Deconvo->Write();
                        
                        canvas_TimeResPlotRatio_Deconvo->Write();
                        
                        //Delete Pointer
                        delete canvas_TimeResPlotRatio_Deconvo;
                        delete temp_TDC_histo_Deconvo;
                    } //End Case: i^th Peak Above the Noise
                    
                    //Debugging
                    //cout<<"TestBeamAnalyzer::makeHistogramsTDC() - No Fault 3_c_ii_2_c" << endl;
                    
                    //Debugging
                    //cout<<"TestBeamAnalyzer::makeHistogramsTDC() - No Fault 3_c_ii_2_d" << endl;
                    
                    //Debugging
                    //cout<<"TestBeamAnalyzer::makeHistogramsTDC() - No Fault 3_c_ii_2_e" << endl;
                    
                    //Plot Histo and Fit
                    TCanvas *canvas_TimeResPlot = new TCanvas(
                        Form("Plot_%s_TimeRes_Histo_%s", ((*dlyIter).second).vec_timeResHistos[i]->GetName(), getString( floor(((*dlyIter).second).currScan[i]) ).c_str() ),
                        Form("%s Time Resolution for Current: %suA", ((*dlyIter).second).vec_timeResHistos[i]->GetName(), getString( floor(((*dlyIter).second).currScan[i]) ).c_str() ),
                        700,700);
                    
                    //Debugging
                    //cout<<"TestBeamAnalyzer::makeHistogramsTDC() - No Fault 3_c_ii_2_e_i" << endl;
                    
                    //Debugging
                    //cout<<"((*dlyIter).second).vec_timeResHistos[i] = " << ((*dlyIter).second).vec_timeResHistos[i] << endl;
                    //cout<<"((*dlyIter).second).vec_timeResFits[i] = " << ((*dlyIter).second).vec_timeResFits[i] << endl;
                    
                    //Debugging
                    //cout<<"TestBeamAnalyzer::makeHistogramsTDC() - No Fault 3_c_ii_2_e_ii" << endl;
                    
                    canvas_TimeResPlot->cd();
                    canvas_TimeResPlot->SetTicky();
                    canvas_TimeResPlot->SetTickx();
                    canvas_TimeResPlot->SetLeftMargin(0.15);
                    ((*dlyIter).second).vec_timeResHistos[i]->SetMarkerStyle(21);
                    ((*dlyIter).second).vec_timeResHistos[i]->SetMarkerSize(1.);
                    ((*dlyIter).second).vec_timeResHistos[i]->SetLineWidth(2.);
                    ((*dlyIter).second).vec_timeResHistos[i]->SetTitle("");
                    ((*dlyIter).second).vec_timeResHistos[i]->Draw("a"); //Now Y-Axis exists in C++ land?
                    ((*dlyIter).second).vec_timeResHistos[i]->SetTitleOffset(1.45,"Y");
                    ((*dlyIter).second).vec_timeResHistos[i]->GetYaxis()->SetRangeUser(1,1000);
                    ((*dlyIter).second).vec_timeResHistos[i]->Draw("E1");
                    
                    //Debugging
                    //cout<<"TestBeamAnalyzer::makeHistogramsTDC() - No Fault 3_c_ii_2_e_iii" << endl;
                    
                    if (((*dlyIter).second).vec_fitPerformed[i]) { //Case: i^th Peak Above the Noise
                        ((*dlyIter).second).vec_timeResFits[i]->SetLineWidth(2.);
                        ((*dlyIter).second).vec_timeResFits[i]->SetLineColor(kRed);
                        ((*dlyIter).second).vec_timeResFits[i]->Draw("same");
                    } //End Case: i^th Peak Above the Noise
                    
                    //Debugging
                    //cout<<"TestBeamAnalyzer::makeHistogramsTDC() - No Fault 3_c_ii_2_e_iv" << endl;
                    
                    TLegend *leg_timeResFit_Single = new TLegend(0.15,0.50,0.4,0.60);
                    leg_timeResFit_Single->SetLineColor(kWhite);
                    leg_timeResFit_Single->SetFillColor(kWhite);
                    leg_timeResFit_Single->AddEntry(((*dlyIter).second).vec_timeResHistos[i], "Data","LP");
                    if(((*dlyIter).second).vec_fitPerformed[i])leg_timeResFit_Single->AddEntry(((*dlyIter).second).vec_timeResFits[i], "Fit","L");
                    leg_timeResFit_Single->Draw("same");
                    
                    cmsPrelim->DrawLatex(paintPos_Time,1010,"CMS Preliminary");
                    
                    TLatex *texInfo_beam        = new TLatex();     texInfo_beam->SetTextSize(0.03);
                    TLatex *texInfo_current     = new TLatex();     texInfo_current->SetTextSize(0.03);
                    TLatex *texInfo_pulseLen    = new TLatex();     texInfo_pulseLen->SetTextSize(0.03);
                    TLatex *texInfo_run         = new TLatex();     texInfo_run->SetTextSize(0.03);
                    TLatex *texInfo_thresh      = new TLatex();     texInfo_thresh->SetTextSize(0.03);
                    
                    texInfo_run->DrawLatex(paintPos_Time, 900, Form("Runs %s - %s",(getString(((*dlyIter).second).run_initial)).c_str(),(getString(((*dlyIter).second).run_final)).c_str() ) );
                    texInfo_beam->DrawLatex(paintPos_Time, 850, Form("Beam: %s",((*dlyIter).second).beamType.c_str() ) );
                    texInfo_pulseLen->DrawLatex(paintPos_Time, 800,Form("MSPL%s",(getString(((*dlyIter).second).pulseLen)).c_str()));
                    
                    //Debugging
                    //cout<<"TestBeamAnalyzer::makeHistogramsTDC() - No Fault 3_c_ii_2_f" << endl;
                    
                    //Debugging
                    //cout<<"TestBeamAnalyzer::makeHistogramsTDC() - No Fault 3_c_ii_2_g" << endl;
                    
                    //Write
                    dir_ThisCurr->cd();
                    
                    ((*dlyIter).second).vec_timeResHistos[i]->Write();
                    
                    if (((*dlyIter).second).vec_fitPerformed[i]) { //Case: i^th Peak Above the Noise
                        ((*dlyIter).second).vec_timeResFits[i]->Write();
                    } //End Case: i^th Peak Above the Noise
                    
                    if (((*dlyIter).second).vec_fitPerformed_Deconvo[i]) { //Case: i^th Peak Above the Noise
                        ((*dlyIter).second).vec_timeResFits_Deconvo[i]->Write();
                    } //End Case: i^th Peak Above the Noise
                    
                    canvas_TimeResPlot->Write();
                    
                    //Debugging
                    //cout<<"TestBeamAnalyzer::makeHistogramsTDC() - No Fault 3_c_ii_2_h" << endl;
                    
                    //Delete pointers
                    delete canvas_TimeResPlot;
                    delete leg_timeResFit_Single;
                } //End Loop Over Currents
                
                //Debugging
                //cout<<"TestBeamAnalyzer::makeHistogramsTDC() - No Fault 3_c_ii_3" << endl;
                
                //Initialize TLatex members for InfoPanel For All Plots
                ((*dlyIter).second).texInfo_run         = new TLatex();     ((*dlyIter).second).texInfo_run->SetTextSize(0.03);
                ((*dlyIter).second).texInfo_beam        = new TLatex();     ((*dlyIter).second).texInfo_beam->SetTextSize(0.03);
                ((*dlyIter).second).texInfo_pulseLen    = new TLatex();     ((*dlyIter).second).texInfo_pulseLen->SetTextSize(0.03);
                ((*dlyIter).second).texInfo_delay       = new TLatex();     ((*dlyIter).second).texInfo_delay->SetTextSize(0.03);
                ((*dlyIter).second).texInfo_thresh      = new TLatex();     ((*dlyIter).second).texInfo_thresh->SetTextSize(0.03);
                
                //Plot The Curve - One Delay : Histo RMS vs Imon
                //======================================================
                //Initialize the canvas - single delay
                ((*detIter).second).canvas_RMS_TimeRes_v_Curr = new TCanvas(
                    Form("Plot_%s_Async_RMS_TimeRes_v_Curr_R%s_R%s",((*detIter).first).c_str(), getString( ((*detIter).second).run_initial ).c_str(), getString( ((*detIter).second).run_final ).c_str() ),
                    Form("%s_Async_RMS_TimeRes_v_Curr_R%s_R%s",((*detIter).first).c_str(), getString( ((*detIter).second).run_initial ).c_str(), getString( ((*detIter).second).run_final ).c_str() ),
                    700,700);
                
                //Go To Active Canvas & Draw Plot
                ((*detIter).second).canvas_RMS_TimeRes_v_Curr->cd();
                ((*detIter).second).canvas_RMS_TimeRes_v_Curr->SetGridy();
                ((*detIter).second).canvas_RMS_TimeRes_v_Curr->SetTickx();
                ((*detIter).second).canvas_RMS_TimeRes_v_Curr->SetTicky();
                ((*detIter).second).graph_RMS_TimeRes_v_Curr->SetTitle("");
                ((*detIter).second).graph_RMS_TimeRes_v_Curr->GetYaxis()->SetRangeUser(5,25);
                ((*detIter).second).graph_RMS_TimeRes_v_Curr->GetYaxis()->SetTitle("Time Resolution #sigma_{#font[12]{t}}^{RMS} #left(ns#right)");
                ((*detIter).second).graph_RMS_TimeRes_v_Curr->GetYaxis()->SetTitleOffset(1.20);
                ((*detIter).second).graph_RMS_TimeRes_v_Curr->GetXaxis()->SetRangeUser(paintPos_Curr-10,curr_max+10);
                ((*detIter).second).graph_RMS_TimeRes_v_Curr->GetXaxis()->SetTitle("Current Supplied to HV Divider #left(#muA#right)");
                ((*detIter).second).graph_RMS_TimeRes_v_Curr->GetXaxis()->SetTitleOffset(1.10);
                ((*detIter).second).graph_RMS_TimeRes_v_Curr->SetMarkerStyle(21);
                ((*detIter).second).graph_RMS_TimeRes_v_Curr->SetMarkerSize(1.);
                ((*detIter).second).graph_RMS_TimeRes_v_Curr->SetLineWidth(2.);
                ((*detIter).second).graph_RMS_TimeRes_v_Curr->Draw("AP");
                
                //Draw Legend
                //TLegend *leg_RMS_TimeRes = new TLegend(0.15,100./700.,0.45,150./700.);
                TLegend *leg_RMS_TimeRes = new TLegend(0.15,110./700.,0.42,160./700.);
                leg_RMS_TimeRes->SetLineColor(0);
                leg_RMS_TimeRes->SetFillColor(0);
                leg_RMS_TimeRes->AddEntry(((*detIter).second).graph_RMS_TimeRes_v_Curr,((*detIter).first).c_str(),"LP");
                leg_RMS_TimeRes->Draw("same");
                
                //Draw Info Panel
                cmsPrelim->DrawLatex(paintPos_Curr-10,25.25,"CMS Preliminary");
                
                ((*dlyIter).second).texInfo_run->DrawLatex(paintPos_Curr, 25*0.48,Form("Runs %s - %s",(getString(((*dlyIter).second).run_initial)).c_str(),(getString(((*dlyIter).second).run_final)).c_str() ) );
                
                if ( ((*detIter).second).infoMatch_DLY ) { //Case: Info Matches
                    ((*dlyIter).second).texInfo_beam->DrawLatex(paintPos_Curr,25*0.44,Form("Beam: %s",((*dlyIter).second).beamType.c_str()));
                    ((*dlyIter).second).texInfo_pulseLen->DrawLatex(paintPos_Curr,25*0.40,Form("MSPL%s",(getString(((*dlyIter).second).pulseLen)).c_str()));
                    ((*dlyIter).second).texInfo_delay->DrawLatex(paintPos_Curr,25*0.36,"Async. Mode");
                    ((*dlyIter).second).texInfo_thresh->DrawLatex(paintPos_Curr,25*0.32,Form("VFAT Thresh. = %s fC",(getString(((*dlyIter).second).thresh).c_str())));
                } //End Case: Info Matches
                
                //Plot The Curve - One Delay : Fit Sigma vs Imon
                //======================================================
                //Initialize the canvas - single delay
                ((*detIter).second).canvas_Fit_TimeRes_v_Curr = new TCanvas(
                    Form("Plot_%s_Async_Fit_TimeRes_v_Curr_R%s_R%s",((*detIter).first).c_str(), getString( ((*detIter).second).run_initial ).c_str(), getString( ((*detIter).second).run_final ).c_str() ),
                    Form("%s_Async_Fit_TimeRes_v_Curr_R%s_R%s",((*detIter).first).c_str(), getString( ((*detIter).second).run_initial ).c_str(), getString( ((*detIter).second).run_final ).c_str() ),
                    700,700);
                
                //Go To Active Canvas & Draw Plot
                ((*detIter).second).canvas_Fit_TimeRes_v_Curr->cd();
                ((*detIter).second).canvas_Fit_TimeRes_v_Curr->SetGridy();
                ((*detIter).second).canvas_Fit_TimeRes_v_Curr->SetTickx();
                ((*detIter).second).canvas_Fit_TimeRes_v_Curr->SetTicky();
                ((*detIter).second).graph_Fit_TimeRes_v_Curr->SetTitle("");
                ((*detIter).second).graph_Fit_TimeRes_v_Curr->GetYaxis()->SetRangeUser(5,25);
                ((*detIter).second).graph_Fit_TimeRes_v_Curr->GetYaxis()->SetTitle("Time Resolution #sigma_{#font[12]{t}}^{Fit} #left(ns#right)");
                ((*detIter).second).graph_Fit_TimeRes_v_Curr->GetYaxis()->SetTitleOffset(1.20);
                ((*detIter).second).graph_Fit_TimeRes_v_Curr->GetXaxis()->SetRangeUser(paintPos_Curr-10,curr_max+10);
                ((*detIter).second).graph_Fit_TimeRes_v_Curr->GetXaxis()->SetTitle("Current Supplied to HV Divider #left(#muA#right)");
                ((*detIter).second).graph_Fit_TimeRes_v_Curr->GetXaxis()->SetTitleOffset(1.10);
                ((*detIter).second).graph_Fit_TimeRes_v_Curr->SetMarkerStyle(21);
                ((*detIter).second).graph_Fit_TimeRes_v_Curr->SetMarkerSize(1.);
                ((*detIter).second).graph_Fit_TimeRes_v_Curr->SetLineWidth(2.);
                ((*detIter).second).graph_Fit_TimeRes_v_Curr->Draw("AP");
                
                //Draw Legend (Just use the same one for now)
                leg_RMS_TimeRes->Draw("same");
                
                //Draw Info Panel
                cmsPrelim->DrawLatex(paintPos_Curr-10,25.25,"CMS Preliminary");
                
                ((*dlyIter).second).texInfo_run->DrawLatex(paintPos_Curr, 25*0.48,Form("Runs %s - %s",(getString(((*dlyIter).second).run_initial)).c_str(),(getString(((*dlyIter).second).run_final)).c_str() ) );
                
                if ( ((*detIter).second).infoMatch_DLY ) { //Case: Info Matches
                    ((*dlyIter).second).texInfo_beam->DrawLatex(paintPos_Curr,25*0.44,Form("Beam: %s",((*dlyIter).second).beamType.c_str()));
                    ((*dlyIter).second).texInfo_pulseLen->DrawLatex(paintPos_Curr,25*0.40,Form("MSPL%s",(getString(((*dlyIter).second).pulseLen)).c_str()));
                    ((*dlyIter).second).texInfo_delay->DrawLatex(paintPos_Curr,25*0.36,"Async. Mode");
                    ((*dlyIter).second).texInfo_thresh->DrawLatex(paintPos_Curr,25*0.32,Form("VFAT Thresh. = %s fC",(getString(((*dlyIter).second).thresh).c_str())));
                } //End Case: Info Matches
                
                //Plot The Curve - One Delay : Fit normChi2 vs Imon
                //======================================================
                //Initialize the canvas - single delay
                ((*detIter).second).canvas_Fit_normChi2_v_Curr = new TCanvas(
                    Form("Plot_%s_Async_Fit_normChi2_v_Curr_R%s_R%s",((*detIter).first).c_str(), getString( ((*detIter).second).run_initial ).c_str(), getString( ((*detIter).second).run_final ).c_str() ),
                    Form("%s_Async_Fit_normChi2_v_Curr_R%s_R%s",((*detIter).first).c_str(), getString( ((*detIter).second).run_initial ).c_str(), getString( ((*detIter).second).run_final ).c_str() ),
                    700,700);
                
                //Go To Active Canvas & Draw Plot
                ((*detIter).second).canvas_Fit_normChi2_v_Curr->cd();
                ((*detIter).second).canvas_Fit_normChi2_v_Curr->SetGridy();
                ((*detIter).second).canvas_Fit_normChi2_v_Curr->SetTickx();
                ((*detIter).second).canvas_Fit_normChi2_v_Curr->SetTicky();
                ((*detIter).second).graph_Fit_normChi2_v_Curr->SetTitle("");
                ((*detIter).second).graph_Fit_normChi2_v_Curr->GetYaxis()->SetRangeUser(0,12);
                ((*detIter).second).graph_Fit_normChi2_v_Curr->GetYaxis()->SetTitle("Fit #chi^{2} / nDoF");
                ((*detIter).second).graph_Fit_normChi2_v_Curr->GetYaxis()->SetTitleOffset(1.20);
                ((*detIter).second).graph_Fit_normChi2_v_Curr->GetXaxis()->SetRangeUser(paintPos_Curr-10,curr_max+10);
                ((*detIter).second).graph_Fit_normChi2_v_Curr->GetXaxis()->SetTitle("Current Supplied to HV Divider #left(#muA#right)");
                ((*detIter).second).graph_Fit_normChi2_v_Curr->GetXaxis()->SetTitleOffset(1.10);
                ((*detIter).second).graph_Fit_normChi2_v_Curr->SetMarkerStyle(21);
                ((*detIter).second).graph_Fit_normChi2_v_Curr->SetMarkerSize(1.);
                ((*detIter).second).graph_Fit_normChi2_v_Curr->SetLineWidth(2.);
                ((*detIter).second).graph_Fit_normChi2_v_Curr->Draw("AP");
                
                //Draw Legend
                
                //Draw Info Panel
                cmsPrelim->DrawLatex(paintPos_Curr-10,12.1,"CMS Preliminary");
                
                //Debugging
                //cout<<"TestBeamAnalyzer::makeHistogramsTDC() - No Fault 3_c_ii_4" << endl;
                
                //Write
                dir_ThisDet->cd();
                
                ((*detIter).second).graph_RMS_TimeRes_v_Curr->Write();
                ((*detIter).second).graph_Fit_TimeRes_v_Curr->Write();
                ((*detIter).second).graph_Fit_normChi2_v_Curr->Write();
                
                ((*detIter).second).graph_RMS_TimeRes_v_HVDrift->Write();
                ((*detIter).second).graph_Fit_TimeRes_v_HVDrift->Write();
                ((*detIter).second).graph_Fit_normChi2_v_HVDrift->Write();
                
                ((*detIter).second).graph_RMS_Deconvo_TimeRes_v_Curr->Write();
                ((*detIter).second).graph_Fit_Deconvo_TimeRes_v_Curr->Write();
                ((*detIter).second).graph_Fit_Deconvo_normChi2_v_Curr->Write();
                
                ((*detIter).second).graph_RMS_Deconvo_TimeRes_v_HVDrift->Write();
                ((*detIter).second).graph_Fit_Deconvo_TimeRes_v_HVDrift->Write();
                ((*detIter).second).graph_Fit_Deconvo_normChi2_v_HVDrift->Write();
                
                ((*detIter).second).canvas_RMS_TimeRes_v_Curr->Write();
                ((*detIter).second).canvas_Fit_TimeRes_v_Curr->Write();
                ((*detIter).second).canvas_Fit_normChi2_v_Curr->Write();
            } //End Case: meas_TDC_TimeRes
            
            //Debugging
            //cout<<"TestBeamAnalyzer::makeHistogramsTDC() - No Fault 3_c_iii" << endl;
        } //End Loop Over Delays
        
        //Debugging
        //cout<<"TestBeamAnalyzer::makeHistogramsTDC() - No Fault 3_d" << endl;
        
        if (meas_TDC_ClockScan) { //Case: meas_TDC_ClockScan
            //Plot The Curve - One Delay : Max Trig Eff vs Delay
            //======================================================
            //Initialize the canvas - single delay
            ((*detIter).second).canvas_MaxTrigEff_v_Delay->cd();
            ((*detIter).second).canvas_MaxTrigEff_v_Delay->SetTicky();
            ((*detIter).second).canvas_MaxTrigEff_v_Delay->SetTickx();
            ((*detIter).second).graph_MaxTrigEff_v_Delay->SetTitle("");
            ((*detIter).second).graph_MaxTrigEff_v_Delay->GetYaxis()->SetRangeUser(0.,1.);
            ((*detIter).second).graph_MaxTrigEff_v_Delay->GetYaxis()->SetDecimals(true);
            ((*detIter).second).graph_MaxTrigEff_v_Delay->GetYaxis()->SetTitle("Efficiency to Trigger in One Clock Cylce");
            ((*detIter).second).graph_MaxTrigEff_v_Delay->GetYaxis()->SetTitleOffset(1.20);
            ((*detIter).second).graph_MaxTrigEff_v_Delay->GetXaxis()->SetTitle("Added Delay #left(ns#right)");
            ((*detIter).second).graph_MaxTrigEff_v_Delay->GetXaxis()->SetTitleOffset(1.10);
            ((*detIter).second).graph_MaxTrigEff_v_Delay->SetMarkerStyle(21);
            ((*detIter).second).graph_MaxTrigEff_v_Delay->SetMarkerSize(1.);
            ((*detIter).second).graph_MaxTrigEff_v_Delay->SetLineWidth(2.);
            ((*detIter).second).graph_MaxTrigEff_v_Delay->Draw("ap");
            
            //Draw Legend - Single Delay
            leg_MaxTrigEff_v_Delay->AddEntry(((*detIter).second).graph_MaxTrigEff_v_Delay,((*detIter).first).c_str(),"LP");
            leg_MaxTrigEff_v_Delay->Draw("same");
            
            //Draw Info Panel
            ((*detIter).second).texInfo_run         = new TLatex();     ((*detIter).second).texInfo_run->SetTextSize(0.03);
            ((*detIter).second).texInfo_beam        = new TLatex();     ((*detIter).second).texInfo_beam->SetTextSize(0.03);
            ((*detIter).second).texInfo_pulseLen    = new TLatex();     ((*detIter).second).texInfo_pulseLen->SetTextSize(0.03);
            ((*detIter).second).texInfo_delay      = new TLatex();     ((*detIter).second).texInfo_delay->SetTextSize(0.03);
            ((*detIter).second).texInfo_thresh      = new TLatex();     ((*detIter).second).texInfo_thresh->SetTextSize(0.03);
            
            cmsPrelim->DrawLatex(paintPos_Dly-1,1.01,"CMS Preliminary");
            
            ((*detIter).second).texInfo_run->DrawLatex(paintPos_Dly, 0.4,Form("Runs %s - %s",(getString(((*detIter).second).run_initial)).c_str(),(getString(((*detIter).second).run_final)).c_str() ) );
            
            if ( ((*detIter).second).infoMatch_DLY ) { //Case: Info Matches
                ((*detIter).second).texInfo_beam->DrawLatex(paintPos_Dly,0.35,Form("Beam: %s",((*detIter).second).beamType.c_str()));
                ((*detIter).second).texInfo_pulseLen->DrawLatex(paintPos_Dly,0.3,Form("MSPL%s",(getString(((*detIter).second).pulseLen)).c_str()));
                ((*detIter).second).texInfo_delay->DrawLatex(paintPos_Dly,0.25,"Sync. Mode");
                ((*detIter).second).texInfo_thresh->DrawLatex(paintPos_Dly,0.2,Form("VFAT Thresh. = %s fC",(getString(((*detIter).second).thresh).c_str())));
            } //End Case: Info Matches
            
            //Write
            dir_ThisDet->cd();
            ((*detIter).second).graph_MaxTrigEff_v_Delay->Write();
            ((*detIter).second).canvas_MaxTrigEff_v_Delay->Write();
            
            //Store the Curves - MaxTrigEff information for the comparison!
            //======================================================
            //Set the Style
            ((*detIter).second).graph_MaxTrigEff_v_Delay->SetMarkerStyle( getCyclicMarkerStyle( std::distance(results.begin(),detIter) ) );
            ((*detIter).second).graph_MaxTrigEff_v_Delay->SetMarkerColor( getCyclicColor( std::distance(results.begin(),detIter) ) );
            ((*detIter).second).graph_MaxTrigEff_v_Delay->SetLineColor( getCyclicColor( std::distance(results.begin(),detIter) ) );
            
            //Store in MultiGraph
            comparison.mGraph_AllDet_MaxTrigEff_v_Delay->Add(((*detIter).second).graph_MaxTrigEff_v_Delay,"P");
            
            //Setup Legend
            comparison.leg_AllDet_MaxTrigEff_v_Delay->AddEntry(((*detIter).second).graph_MaxTrigEff_v_Delay, getParsedDetName((*detIter).first).c_str(), "LP");
        } //End Case: meas_TDC_ClockScan
        
        //Debugging
        //cout<<"TestBeamAnalyzer::makeHistogramsTDC() - No Fault 3_e" << endl;
        
        if (meas_TDC_TimeRes) { //Case: meas_TDC_TimeRes
            //Plot The Curve - One Delay : Comparison of Time Res from RMS & Fit
            //======================================================
            //Initialize the canvas - single delay
            ((*detIter).second).canvas_FitnRMS_TimeRes_v_Curr = new TCanvas(
                Form("Plot_%s_Async_FitComp2RMS_TimeRes_v_Curr_R%s_R%s",((*detIter).first).c_str(), getString( ((*detIter).second).run_initial ).c_str(), getString( ((*detIter).second).run_final ).c_str() ),
                Form("%s_Async_FitComp2RMS_TimeRes_v_Curr_R%s_R%s",((*detIter).first).c_str(), getString( ((*detIter).second).run_initial ).c_str(), getString( ((*detIter).second).run_final ).c_str() ),
                700,700);
            
            //Go To Active Canvas & Draw Plot
            ((*detIter).second).canvas_FitnRMS_TimeRes_v_Curr->cd();
            ((*detIter).second).canvas_FitnRMS_TimeRes_v_Curr->SetGridy();
            ((*detIter).second).canvas_FitnRMS_TimeRes_v_Curr->SetTickx();
            ((*detIter).second).canvas_FitnRMS_TimeRes_v_Curr->SetTicky();
            ((*detIter).second).graph_RMS_TimeRes_v_Curr->SetMarkerStyle(21);
            ((*detIter).second).graph_RMS_TimeRes_v_Curr->SetMarkerColor(kRed);
            ((*detIter).second).graph_RMS_TimeRes_v_Curr->SetLineColor(kRed);
            ((*detIter).second).graph_RMS_TimeRes_v_Curr->GetYaxis()->SetTitle("Time Resolution #sigma_{#font[12]{t}}^{} #left(ns#right)");
            ((*detIter).second).graph_RMS_TimeRes_v_Curr->Draw("AP");
            ((*detIter).second).graph_Fit_TimeRes_v_Curr->SetMarkerStyle(21);
            ((*detIter).second).graph_Fit_TimeRes_v_Curr->SetMarkerColor(kRed+3);
            ((*detIter).second).graph_Fit_TimeRes_v_Curr->SetLineColor(kRed+3);
            ((*detIter).second).graph_Fit_TimeRes_v_Curr->Draw("sameP");
            
            //Draw Legend
            ((*detIter).second).leg_Info = new TLegend(0.15,110./700.-25./700.,0.45,160./700.);
            ((*detIter).second).leg_Info->SetLineColor(0);
            ((*detIter).second).leg_Info->SetFillColor(0);
            ((*detIter).second).leg_Info->AddEntry(((*detIter).second).graph_RMS_TimeRes_v_Curr, Form("%s - #sigma_{#font[12]{t}}^{RMS}", ((*detIter).first ).c_str() ), "LP");
            ((*detIter).second).leg_Info->AddEntry(((*detIter).second).graph_Fit_TimeRes_v_Curr, Form("%s - #sigma_{#font[12]{t}}^{Fit}", ((*detIter).first).c_str() ), "LP");
            ((*detIter).second).leg_Info->Draw("same");
            
            //Draw Info Panel
            ((*detIter).second).texInfo_run         = new TLatex();     ((*detIter).second).texInfo_run->SetTextSize(0.03);
            ((*detIter).second).texInfo_beam        = new TLatex();     ((*detIter).second).texInfo_beam->SetTextSize(0.03);
            ((*detIter).second).texInfo_pulseLen    = new TLatex();     ((*detIter).second).texInfo_pulseLen->SetTextSize(0.03);
            ((*detIter).second).texInfo_delay      = new TLatex();     ((*detIter).second).texInfo_delay->SetTextSize(0.03);
            ((*detIter).second).texInfo_thresh      = new TLatex();     ((*detIter).second).texInfo_thresh->SetTextSize(0.03);
            
            cmsPrelim->DrawLatex(paintPos_Curr-10,25.25,"CMS Preliminary");
            
            ((*detIter).second).texInfo_run->DrawLatex(paintPos_Curr, 25*0.48,Form("Runs %s - %s",(getString(((*detIter).second).run_initial)).c_str(),(getString(((*detIter).second).run_final)).c_str() ) );
            ((*detIter).second).texInfo_beam->DrawLatex(paintPos_Curr,25*0.44,Form("Beam: %s",((*detIter).second).beamType.c_str()));
            ((*detIter).second).texInfo_pulseLen->DrawLatex(paintPos_Curr,25*0.40,Form("MSPL%s",(getString(((*detIter).second).pulseLen)).c_str()));
            ((*detIter).second).texInfo_delay->DrawLatex(paintPos_Curr,25*0.36,"Async. Mode");
            ((*detIter).second).texInfo_thresh->DrawLatex(paintPos_Curr,25*0.32,Form("VFAT Thresh. = %s fC",(getString(((*detIter).second).thresh).c_str())));
            
            //Write
            dir_ThisDet->cd();
            
            ((*detIter).second).canvas_FitnRMS_TimeRes_v_Curr->Write();
            
            //Setup comparison of detectors
            //================================================================
            //Change Color of RMS Plot
            ((*detIter).second).graph_RMS_TimeRes_v_Curr->SetMarkerStyle( getCyclicMarkerStyle( (int)std::distance(results.begin(), detIter) ) );
            ((*detIter).second).graph_RMS_TimeRes_v_Curr->SetMarkerColor( getCyclicColor( (int)std::distance(results.begin(), detIter) ) );
            ((*detIter).second).graph_RMS_TimeRes_v_Curr->SetLineColor( getCyclicColor( (int)std::distance(results.begin(), detIter) ) );
            ((*detIter).second).graph_RMS_TimeRes_v_Curr->GetYaxis()->SetTitle("Time Resolution #sigma_{#font[12]{t}}^{RMS} #left(ns#right)");
            
            //Store RMS Plot
            comparison.mGraph_AllDet_TimeResRMS_v_Curr->Add(((*detIter).second).graph_RMS_TimeRes_v_Curr, "P" );
            
            //Setup Legend
            comparison.leg_AllDet_TimeRes->AddEntry( ((*detIter).second).graph_RMS_TimeRes_v_Curr, ((*detIter).first).c_str(),"LP");
            
            //Change Color of Fit Plot
            ((*detIter).second).graph_Fit_TimeRes_v_Curr->SetMarkerStyle( getCyclicMarkerStyle( (int)std::distance(results.begin(), detIter) ) );
            ((*detIter).second).graph_Fit_TimeRes_v_Curr->SetMarkerColor( getCyclicColor( (int)std::distance(results.begin(), detIter) ) );
            ((*detIter).second).graph_Fit_TimeRes_v_Curr->SetLineColor( getCyclicColor( (int)std::distance(results.begin(), detIter) ) );
            
            //Store Fit Plot
            comparison.mGraph_AllDet_TimeResFit_v_Curr->Add(((*detIter).second).graph_Fit_TimeRes_v_Curr, "P" );
        } //End Case: meas_TDC_TimeRes
        
        //Setup info panel stored in comparison
        //======================================================
        //Store Run Range of Comparison
        if (comparison.run_final   < ((*detIter).second).run_final  ) comparison.run_final   = ((*detIter).second).run_final;
        if (comparison.run_initial > ((*detIter).second).run_initial) comparison.run_initial = ((*detIter).second).run_initial;
        
        //Set Other Parameters in comparison (MSPL, Thresh, etc...)
        if(comparison.infoMatch_DLY && detIter == results.begin() ){ //Case: Data Match & First Occurrence
            comparison.beamType = ((*detIter).second).beamType;
            comparison.pulseLen = ((*detIter).second).pulseLen;
            comparison.thresh   = ((*detIter).second).thresh;
        } //End Case: Data Match & First Occurrence
        
        //Check to see if info matches across runs
        if(!((*detIter).second).infoMatch_DLY) comparison.infoMatch_DLY = ((*detIter).second).infoMatch_DLY;
        
        //cout<<"TestBeamAnalyzer::makeHistogramsTDC() - No Fault 3_f" << endl;
    } //End Loop Over Detectors
    
    //Plot Comparison - Clock Scan
    if (meas_TDC_ClockScan){ //Case: Clock Scan
        //Plot The Curve - Comparison of MaxTrigEff_v_Curr
        //======================================================
        //Append The Name to Include The Runs!
        tempHistoName = ((string) comparison.canvas_AllDet_MaxTrigEff_v_Curr->GetName() ) + "_R" + getString( comparison.run_initial ) + "_R" + getString( comparison.run_final );
        comparison.canvas_AllDet_MaxTrigEff_v_Curr->SetName( tempHistoName.c_str() );
        
        //Go To Active Canvas & Draw Plot
        comparison.canvas_AllDet_MaxTrigEff_v_Curr->cd();
        comparison.canvas_AllDet_MaxTrigEff_v_Curr->SetTickx();
        comparison.canvas_AllDet_MaxTrigEff_v_Curr->SetTicky();
        comparison.mGraph_AllDet_MaxTrigEff_v_Curr->Draw("a"); //Do this the 1st time to make TMultiGraph::GetHistogram() for this object valid
        comparison.mGraph_AllDet_MaxTrigEff_v_Curr->GetHistogram()->SetTitleOffset(1.20,"Y");
        comparison.mGraph_AllDet_MaxTrigEff_v_Curr->GetYaxis()->SetRangeUser(0.,1.);
        comparison.mGraph_AllDet_MaxTrigEff_v_Curr->GetYaxis()->SetDecimals(true);
        comparison.mGraph_AllDet_MaxTrigEff_v_Curr->GetHistogram()->SetTitleOffset(1.10,"X");
        comparison.mGraph_AllDet_MaxTrigEff_v_Curr->GetXaxis()->SetRangeUser(paintPos_Curr-10,curr_max+10);
        comparison.mGraph_AllDet_MaxTrigEff_v_Curr->Draw("a");
        
        //Draw Legend
        comparison.leg_AllDet_MaxTrigEff_v_Curr->Draw("same");
        
        //Draw Info Panel
        cmsPrelim->DrawLatex(paintPos_Curr-10,1.01,"CMS Preliminary");
        
        comparison.texInfo_run->DrawLatex(paintPos_Curr, 0.9,Form("Runs %s - %s",(getString(comparison.run_initial)).c_str(),(getString(comparison.run_final)).c_str() ) );
        
        if (comparison.infoMatch_DLY){ //Case: Info Same For All Detectors
            comparison.texInfo_beam->DrawLatex(paintPos_Curr,0.85,Form("Beam: %s",(comparison.beamType.c_str())));
            comparison.texInfo_pulseLen->DrawLatex(paintPos_Curr,0.8,Form("MSPL%s",(getString(comparison.pulseLen)).c_str()));
            comparison.texInfo_delay->DrawLatex(paintPos_Curr,0.75,Form("Sync. Mode; DLY = %sns",(getString(comparison.delay).c_str())));
            comparison.texInfo_thresh->DrawLatex(paintPos_Curr,0.7,Form("VFAT Thresh. = %s fC",(getString(comparison.thresh).c_str())));
        } //End Case: Info Same For All Detectors
        
        //Write
        dir_Comp->cd();
        
        comparison.mGraph_AllDet_MaxTrigEff_v_Curr->Write();
        comparison.canvas_AllDet_MaxTrigEff_v_Curr->Write();
        
        //Plot The Curve - Comparison of MaxTrigEff_v_Delay
        //======================================================
        //Append The Name to Include The Runs!
        tempHistoName = ((string) comparison.canvas_AllDet_MaxTrigEff_v_Delay->GetName() ) + "_R" + getString( comparison.run_initial ) + "_R" + getString( comparison.run_final );
        comparison.canvas_AllDet_MaxTrigEff_v_Delay->SetName( tempHistoName.c_str() );
        
        //Go To Active Canvas & Draw Plot
        comparison.canvas_AllDet_MaxTrigEff_v_Delay->cd();
        comparison.canvas_AllDet_MaxTrigEff_v_Delay->SetTickx();
        comparison.canvas_AllDet_MaxTrigEff_v_Delay->SetTicky();
        comparison.mGraph_AllDet_MaxTrigEff_v_Delay->Draw("a"); //Do this the 1st time to make TMultiGraph::GetHistogram() for this object valid
        comparison.mGraph_AllDet_MaxTrigEff_v_Delay->GetHistogram()->SetTitleOffset(1.20,"Y");
        comparison.mGraph_AllDet_MaxTrigEff_v_Delay->GetYaxis()->SetRangeUser(0.,1.);
        comparison.mGraph_AllDet_MaxTrigEff_v_Delay->GetYaxis()->SetDecimals(true);
        comparison.mGraph_AllDet_MaxTrigEff_v_Delay->GetHistogram()->SetTitleOffset(1.10,"X");
        comparison.mGraph_AllDet_MaxTrigEff_v_Delay->Draw("a");
        
        //Draw Legend
        comparison.leg_AllDet_MaxTrigEff_v_Delay->Draw("same");
        
        //Draw Info Panel
        cmsPrelim->DrawLatex(paintPos_Dly-1,1.01,"CMS Preliminary");
        
        comparison.texInfo_run->DrawLatex(paintPos_Dly, 0.4,Form("Runs %s - %s",(getString(comparison.run_initial)).c_str(),(getString(comparison.run_final)).c_str() ) );
        
        if (comparison.infoMatch_DLY){ //Case: Info Same For All Detectors
            comparison.texInfo_beam->DrawLatex(paintPos_Dly,0.35,Form("Beam: %s",(comparison.beamType.c_str())));
            comparison.texInfo_pulseLen->DrawLatex(paintPos_Dly,0.3,Form("MSPL%s",(getString(comparison.pulseLen)).c_str()));
            comparison.texInfo_delay->DrawLatex(paintPos_Dly,0.25,"Sync. Mode");
            comparison.texInfo_thresh->DrawLatex(paintPos_Dly,0.2,Form("VFAT Thresh. = %s fC",(getString(comparison.thresh).c_str())));
        } //End Case: Info Same For All Detectors

        //Write
        dir_Comp->cd(); //This should already be the active directory, but what the hell, why not...
        
        comparison.mGraph_AllDet_MaxTrigEff_v_Delay->Write();
        comparison.canvas_AllDet_MaxTrigEff_v_Delay->Write();
        
        //Plot The Curve - Comparison of Clock Scan
        //======================================================
        //The canvas are already made; need to loop over them and add the legend
        map<int, map<float, TCanvas*, cmp_flt>, cmp_int >::iterator cnvIterOuter;
        for (cnvIterOuter = comparison.map_canvas_AllDet_ClkCyl.begin(); cnvIterOuter != comparison.map_canvas_AllDet_ClkCyl.end(); cnvIterOuter++) { //Loop Over comparison.map_canvas_AllDet_ClkCyl (Outer Map DLY -> map<float,canvas> )
            map<float, TCanvas*, cmp_flt>::iterator cnvIterInner;
            
            //Loop Over Inner Map (float -> canvas)
            for (cnvIterInner = ((*cnvIterOuter).second).begin(); cnvIterInner != ((*cnvIterOuter).second).end(); cnvIterInner++) { //Loop Over Inner Map (float -> canvas)
                //Change the active canvas
                ((*cnvIterInner).second)->cd();
                
                //Draw the legend
                (comparison.map_leg_AllDet_ClkCyl[ (*cnvIterOuter).first ])->Draw("same");
                
                //Change the active directory
                ( (comparison.map_dir_Curr_Parent_DLY[ (*cnvIterOuter).first ])[ (*cnvIterInner).first ] )->cd();
                
                //Write the TCanvas to the Root File
                ((*cnvIterInner).second)->Write();
            } //End Loop Over Inner Map (float -> canvas)
            
        } //End Loop Over comparison.map_canvas_AllDet_ClkCyl (Outer Map DLY -> map<float,canvas>)
        
    } //End Case: Clock Scan
    
    //Plot Comparison - Time Resolution
    if (meas_TDC_TimeRes) {
        //Plot The Curve - Comparison of Time Res from All Detectors (RMS)
        //======================================================
        //Append The Name to Include The Runs!
        tempHistoName = ((string)comparison.canvas_AllDet_TimeResRMS_v_Curr->GetName() ) + "_R" + getString( comparison.run_initial ) + "_R" + getString( comparison.run_final );
        comparison.canvas_AllDet_TimeResRMS_v_Curr->SetName( tempHistoName.c_str() );
        
        //Go To Active Canvas & Draw Plot
        comparison.canvas_AllDet_TimeResRMS_v_Curr->cd();
        comparison.canvas_AllDet_TimeResRMS_v_Curr->SetGridy();
        comparison.canvas_AllDet_TimeResRMS_v_Curr->SetTickx();
        comparison.canvas_AllDet_TimeResRMS_v_Curr->SetTicky();
        comparison.mGraph_AllDet_TimeResRMS_v_Curr->Draw("a"); //Do this the 1st time to make TMultiGraph::GetHistogram() for this object valid
        comparison.mGraph_AllDet_TimeResRMS_v_Curr->GetHistogram()->SetTitleOffset(1.20,"Y");
        comparison.mGraph_AllDet_TimeResRMS_v_Curr->GetYaxis()->SetRangeUser(5,25);
        comparison.mGraph_AllDet_TimeResRMS_v_Curr->GetHistogram()->SetTitleOffset(1.10,"X");
        comparison.mGraph_AllDet_TimeResRMS_v_Curr->GetXaxis()->SetRangeUser(paintPos_Curr-10,curr_max+10);
        comparison.mGraph_AllDet_TimeResRMS_v_Curr->Draw("a");
        
        //Draw Legend
        comparison.leg_AllDet_TimeRes->Draw("same");
        
        //Draw Info Panel
        cmsPrelim->DrawLatex(paintPos_Curr-10,25.25,"CMS Preliminary");
        
        comparison.texInfo_run->DrawLatex(paintPos_Curr, 25*0.48,Form("Runs %s - %s",(getString(comparison.run_initial)).c_str(),(getString(comparison.run_final)).c_str() ) );
        
        if (comparison.infoMatch_DLY) { //Case: Info Same For All Detectors
            comparison.texInfo_beam->DrawLatex(paintPos_Curr,25*0.44,Form("Beam: %s",comparison.beamType.c_str()));
            comparison.texInfo_pulseLen->DrawLatex(paintPos_Curr,25*0.40,Form("MSPL%s",(getString(comparison.pulseLen)).c_str()));
            comparison.texInfo_delay->DrawLatex(paintPos_Curr,25*0.36,"Async. Mode");
            comparison.texInfo_thresh->DrawLatex(paintPos_Curr,25*0.32,Form("VFAT Thresh. = %s fC",(getString(comparison.thresh).c_str())));
        } //End Case: Info Same For All Detectors
        
        //Plot The Curve - Comparison of Time Res from All Detectors (Fit)
        //======================================================
        //Append The Name to Include The Runs!
        tempHistoName = ((string)comparison.canvas_AllDet_TimeResFit_v_Curr->GetName() ) + "_R" + getString( comparison.run_initial ) + "_R" + getString( comparison.run_final );
        comparison.canvas_AllDet_TimeResFit_v_Curr->SetName( tempHistoName.c_str() );
        
        //Go To Active Canvas & Draw Plot
        comparison.canvas_AllDet_TimeResFit_v_Curr->cd();
        comparison.canvas_AllDet_TimeResFit_v_Curr->SetGridy();
        comparison.canvas_AllDet_TimeResFit_v_Curr->SetTickx();
        comparison.canvas_AllDet_TimeResFit_v_Curr->SetTicky();
        comparison.mGraph_AllDet_TimeResFit_v_Curr->Draw("a"); //Do this the 1st time to make TMultiGraph::GetHistogram() for this object valid
        comparison.mGraph_AllDet_TimeResFit_v_Curr->GetHistogram()->SetTitleOffset(1.20,"Y");
        comparison.mGraph_AllDet_TimeResFit_v_Curr->GetYaxis()->SetRangeUser(5,25);
        comparison.mGraph_AllDet_TimeResFit_v_Curr->GetHistogram()->SetTitleOffset(1.10,"X");
        comparison.mGraph_AllDet_TimeResFit_v_Curr->GetXaxis()->SetRangeUser(paintPos_Curr-10,curr_max+10);
        comparison.mGraph_AllDet_TimeResFit_v_Curr->Draw("a");
        
        //Draw Legend
        comparison.leg_AllDet_TimeRes->Draw("same");
        
        //Draw Info Panel
        cmsPrelim->DrawLatex(paintPos_Curr-10,25.25,"CMS Preliminary");
        
        comparison.texInfo_run->DrawLatex(paintPos_Curr, 25*0.48,Form("Runs %s - %s",(getString(comparison.run_initial)).c_str(),(getString(comparison.run_final)).c_str() ) );
        
        if (comparison.infoMatch_DLY) { //Case: Info Same For All Detectors
            comparison.texInfo_beam->DrawLatex(paintPos_Curr,25*0.44,Form("Beam: %s",comparison.beamType.c_str()));
            comparison.texInfo_pulseLen->DrawLatex(paintPos_Curr,25*0.40,Form("MSPL%s",(getString(comparison.pulseLen)).c_str()));
            comparison.texInfo_delay->DrawLatex(paintPos_Curr,25*0.36,"Async. Mode");
            comparison.texInfo_thresh->DrawLatex(paintPos_Curr,25*0.32,Form("VFAT Thresh. = %s fC",(getString(comparison.thresh).c_str())));
        } //End Case: Info Same For All Detectors
        
        //Write
        dir_Comp->cd();
        
        comparison.mGraph_AllDet_TimeResFit_v_Curr->Write();
        comparison.mGraph_AllDet_TimeResRMS_v_Curr->Write();
        
        comparison.canvas_AllDet_TimeResFit_v_Curr->Write();
        comparison.canvas_AllDet_TimeResRMS_v_Curr->Write();
    } //End Case: meas_TDC_TimeRes
    
    //Debugging
    //cout<<"TestBeamAnalyzer::makeHistogramsTDC() - No Fault End" << endl;
    
    return;
} //End TestBeamAnalyzer::makeHistogramsTDC()

//Miscillaneous
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------

//Recursively Finds a Peak in histogram histo
//The boolean "shiftRight" determines which way the code will shift if it detects a valley
//Valley's are identified by sequences like "Y1 Y2 0 0 ... 0 0 Y3 Y4" here Y1 > Y2 > 0 and 0 < Y3 < Y4
//peakInfo is a map (string,float) that contains:
//  "Position" Starting Position To Look For the Peak
//  "Integral" Integral of the Peak that is found
//  "Delta"    How far we have moved from the ORIGINAL position (sets exit condition)
//Notice peakInfo is passed by reference so the original input map is modified as we run
//The initial map setup is understood to be "Position" = Starting Position; "Integral" = 0; "Delta" = 0;
void TestBeamAnalyzer::recursivePeakFinder(std::map<string,float> &peakInfo, TH1 *histo, bool shiftRight){
    //Variable Declaration
    bool inPeak     = true;
    bool limit_lf   = false;    //Have you reached the lower limit of the histogram when integrating the peak?
    bool limit_rt   = false;    //Have you reached the upper limit of the histogram when integrating the peak?
    
    int peakWidth_lf= 1; //Used to track the peak width once found
    int peakWidth_rt= 1; //Used to track the peak width once found
    
    int posDiff_lf  = 0; //Used by the algorithm to find it's way out of a valley/plateau
    int posDiff_rt  = 0; //Used by the algorithm to find it's way out of a valley/plateau
    
    int posBin_lf   = (int)peakInfo[peakKey_Pos] - 1; //Position of bin_lf after evaluation
    int posBin_rt   = (int)peakInfo[peakKey_Pos] + 1; //Position of bin_rt after evaluation
    
    float bin_lf    = histo->GetBinContent( (int)peakInfo[peakKey_Pos] - 1 );
    float bin_mid   = histo->GetBinContent( (int)peakInfo[peakKey_Pos] );
    float bin_rt    = histo->GetBinContent( (int)peakInfo[peakKey_Pos] + 1);
    
    //Debugging
    //int dummy;
    //cout<<"Would You Like To Terminate? (Press Ctrl+C)"<<endl;
    //cin>>dummy;
    
    //Debugging
    //cout<<"idx-1\tNum\tidx\tNum\tidx+1\tNum\tDelta\tIntegral"<<endl;
    //cout<< peakInfo[peakKey_Pos]-1<<"\t"<<bin_lf<<"\t";
    //cout<< peakInfo[peakKey_Pos]  <<"\t"<<bin_mid<<"\t";
    //cout<< peakInfo[peakKey_Pos]+1<<"\t"<<bin_rt<<"\t";
    //cout<< peakInfo[peakKey_Delta]     <<"\t";
    //cout<< peakInfo[peakKey_Int]  <<"\t"<<endl;
    
    //The below if-else-if statement checks to see if:
    //  1) the histogram bins are all the same (i.e. a Valley of 0's or a plateau)
    //  2) the left two histogram bins are the same and not zero (i.e. start of a left leaning ledge)
    //  3) the right two histogram bins are the same and not zero (i.e. start of a right leaning ledge)
    if ( bin_lf == bin_mid && bin_mid == bin_rt ) { //Case: All Three Bins the Same!
        //Look Left for first difference
        while (histo->GetBinContent( (int)peakInfo[peakKey_Pos] - posDiff_lf - 1) == bin_mid
               && ( ( (int)peakInfo[peakKey_Pos] - posDiff_lf) > 0 ) ) { //Loop Left Through histo
            //Check Exit condition (all 0's or irregular noise)
            if (posDiff_lf > ceil(30/rebinFactor_TDC) ) {break;}
            
            //Check to Make sure Histogram Range not Exceeded
            if ( ( (int)peakInfo[peakKey_Pos] - posDiff_lf - 1) < 1 ) { break;} //First Bin of Histo is [1]
            
            //Increment posDiff_lf
            posDiff_lf++;
        } //End Loop Left Through histo
        
        //Look Right for first difference
        while (histo->GetBinContent( (int)peakInfo[peakKey_Pos] + posDiff_rt + 1) == bin_mid
               && ( ( (int)peakInfo[peakKey_Pos] + posDiff_rt) < histo->GetNbinsX() ) ) { //Loop Left Through histo
            //Check Exit condition (all 0's or irregular noise)
            if (posDiff_rt > ceil(30/rebinFactor_TDC) ) {break;}
            
            //Check to Make sure Histogram Range not Exceeded
            if ( ( (int)peakInfo[peakKey_Pos] + posDiff_rt + 1) > histo->GetNbinsX() ) { break;}
            
            //Increment posDiff_rt
            posDiff_rt++;
        } //End Loop Right Through histo
        
        //Add these bins together to make the new bin_mid - Left Portion
        if ( posDiff_lf < ceil(31/rebinFactor_TDC) ) { //Case: Time Saver
            //Shift - Left
            for (int i=0; i<posDiff_lf; i++) { (i==0) ? bin_mid += bin_lf : bin_mid += histo->GetBinContent( (int)peakInfo[peakKey_Pos] - i);}
        } //End Case: time Saver
        
        //Add these bins together to make the new bin_mid - Right Portion
        if ( posDiff_rt < ceil(31/rebinFactor_TDC) ) {
            //Shift - Right
            for (int i=0; i<posDiff_rt; i++) { (i==0) ? bin_mid += bin_rt : bin_mid += histo->GetBinContent( (int)peakInfo[peakKey_Pos] + i);}
        }
        
        //Get New left and right bins
        bin_lf = histo->GetBinContent( (int)peakInfo[peakKey_Pos] - posDiff_lf - 1); //For Loops go less than posDiff_lf
        bin_rt = histo->GetBinContent( (int)peakInfo[peakKey_Pos] + posDiff_rt + 1); //For Loops go less than posDiff_rt
        
        //Set Position of New left and right bins
        posBin_lf = (int)peakInfo[peakKey_Pos] - posDiff_lf - 1;
        posBin_rt = (int)peakInfo[peakKey_Pos] + posDiff_rt + 1;
        
        //Adjust the Position
        if (shiftRight) { //Case: Prefer Right Shift
            peakInfo[peakKey_Pos] += posDiff_rt;
            peakInfo[peakKey_Delta] += posDiff_rt;
        } //End Case: Prefer Right Shift
        else {//Case: Prefer Left Shift
            peakInfo[peakKey_Pos] -= posDiff_lf;
            peakInfo[peakKey_Delta] -= posDiff_lf;
        } //End Case: Prefer Left Shift
    } //End Case: All Three Bins the Same!
    else if ( bin_lf == bin_mid && bin_mid > 0) { //Case: Left Two Bins the Same and not zero!
        //Look Left for first difference
        while (histo->GetBinContent( (int)peakInfo[peakKey_Pos] - posDiff_lf - 1) == bin_mid
               && ( ( (int)peakInfo[peakKey_Pos] - posDiff_lf) > 0 ) ) { //Loop Left Through histo
            //Check Exit condition (all 0's or irregular noise)
            if (posDiff_lf > ceil(30/rebinFactor_TDC) ) {break;}
            
            //Check to Make sure Histogram Range not Exceeded
            if ( ( (int)peakInfo[peakKey_Pos] - posDiff_lf - 1) < 1 ) { break;} //First Bin of Histo is [1]
            
            //Increment posDiff_lf
            posDiff_lf++;
        } //End Loop Left Through histo
        
        //Add these bins together to make the new bin_mid - Left Portion
        if ( posDiff_lf < ceil(31/rebinFactor_TDC) ) { //Case: Time Saver
            //Shift - Left
            for (int i=0; i<posDiff_lf; i++) { (i==0) ? bin_mid += bin_lf : bin_mid += histo->GetBinContent( (int)peakInfo[peakKey_Pos] - i);}
        } //End Case: time Saver
        
        //Get New left bin
        bin_lf = histo->GetBinContent( (int)peakInfo[peakKey_Pos] - posDiff_lf - 1); //For Loop goes less than posDiff_lf
        
        //Set Position of New left bin
        posBin_lf = (int)peakInfo[peakKey_Pos] - posDiff_lf - 1;
        
        //Adjust the position
        peakInfo[peakKey_Pos] -= posDiff_lf;
        peakInfo[peakKey_Delta] -= posDiff_lf;
    } //End Case: Lef Two Bins the Same and not zero!
    if ( bin_mid == bin_rt && bin_mid > 0 ) { //Case: Right Two Bins the Same and not zero!
        //Look Right for first difference
        while (histo->GetBinContent( (int)peakInfo[peakKey_Pos] + posDiff_rt + 1) == bin_mid
               && ( ( (int)peakInfo[peakKey_Pos] + posDiff_rt) < histo->GetNbinsX() ) ) { //Loop Left Through histo
            //Check Exit condition (all 0's or irregular noise)
            if (posDiff_rt > ceil(30/rebinFactor_TDC) ) { break;}
            
            //Check to Make sure Histogram Range not Exceeded
            if ( ( (int)peakInfo[peakKey_Pos] + posDiff_rt + 1) > histo->GetNbinsX() ) { break;}
            
            //Increment posDiff_rt
            posDiff_rt++;
        } //End Loop Right Through histo
        
        //Add these bins together to make the new bin_mid - Right Portion
        if ( posDiff_rt < ceil(31/rebinFactor_TDC) ) {
            //Shift - Right
            for (int i=0; i<posDiff_rt; i++) { (i==0) ? bin_mid += bin_rt : bin_mid += histo->GetBinContent( (int)peakInfo[peakKey_Pos] + i);}
        }
        
        //Get New right bin
        bin_rt = histo->GetBinContent( (int)peakInfo[peakKey_Pos] + posDiff_rt + 1); //For loop goes less than posDiff_rt
        
        //Set Position of New right bin
        posBin_rt = (int)peakInfo[peakKey_Pos] + posDiff_rt + 1;
        
        //Adjust the Position
        peakInfo[peakKey_Pos] += posDiff_rt;
        peakInfo[peakKey_Delta] += posDiff_rt;
    } //End Case: Right Two Bins the Same and not zero!
    
    //Debugging
    //cout<<"idx-1\tNum\tidx\tNum\tidx+1\tNum\tDelta\tIntegral"<<endl;
    //cout<< posBin_lf                <<"\t"<<bin_lf  <<"\t";
    //cout<< peakInfo[peakKey_Pos]     <<"\t"<<bin_mid <<"\t";
    //cout<< posBin_rt                <<"\t"<<bin_rt  <<"\t";
    //cout<< peakInfo[peakKey_Delta]        <<"\t";
    //cout<< peakInfo[peakKey_Int]     <<"\t"<<endl;
    
    //Check Exit Condition i.e. we went to far, no peak found
    if ( abs( peakInfo[peakKey_Delta] ) > ceil(30/rebinFactor_TDC)
        || abs(posDiff_lf) > ceil(30/rebinFactor_TDC)
        || abs(posDiff_rt) > ceil(30/rebinFactor_TDC)
        || (peakInfo[peakKey_Pos]+1) > histo->GetNbinsX()
        || (peakInfo[peakKey_Pos]-1) < 1) { //Case: Exit - Peaks Not Found
        peakInfo[peakKey_Pos] = -1; //Not a valid histogram bin
        peakInfo[peakKey_Int] = -1; //Not a valid integral for the data that is being inputed

        return;
    } //End Case: Exit - Peaks Not Found
    
    //Debugging
    //cout<<"-----------------------------------------------"<<endl;
    //cout<< "(int)peakInfo['Position'] = " << (int)peakInfo[peakKey_Pos] << endl;
    //cout<<"bin_lf = " << bin_lf << endl;
    //cout<<"histo->GetBinContent("<< (int)peakInfo[peakKey_Pos] - peakWidth_lf <<") = " << histo->GetBinContent( (int)peakInfo[peakKey_Pos] - peakWidth_lf)<<endl;
    //cout<<"bin_rt = " << bin_rt << endl;
    //cout<<"histo->GetBinContent("<< (int)peakInfo[peakKey_Pos] + peakWidth_rt <<") = " << histo->GetBinContent( (int)peakInfo[peakKey_Pos] + peakWidth_rt)<<endl;
    //cout<<"-----------------------------------------------"<<endl;
    
    //Look If we are in a Peak; Possible Cases are:
    //  1) PEAK:        bin_lf < bin_mid > bin_rt               CALCULATE!
    //  2) VALLEY:      bin_lf > 0, bin_mid = 0, bin_rt > 0     SHIFT BY PREFERENCE!
    //  3) Lf Ledge:    bin_lf > bin_mid >= bin_rt              SHIFT LEFT!
    //  4) Rt Ledge:    bin_lf <=bin_mid < bin_rt               SHIFT RIGHT!
    if ( ( bin_lf < bin_mid ) && ( bin_mid > bin_rt) ) { //Case: Peak Found!
        //Set Starting Integral
        peakInfo[peakKey_Int] = histo->GetBinContent( (int)peakInfo[peakKey_Pos] );
        
        //Set Peak Bounds
        //Since this gives the lower edge the upper boundary must be +2
        peakInfo[peakKey_LwrBd] = histo->GetBinLowEdge(peakInfo[peakKey_Pos] - 1);
        peakInfo[peakKey_UprBd] = histo->GetBinLowEdge(peakInfo[peakKey_Pos] + 2);
        
        //Debugging
        //cout<<"peakInfo['Integral'] = " << peakInfo[peakKey_Int] << endl;
        //cout<<"histo->GetBinContent("<< (int)peakInfo[peakKey_Pos] - peakWidth_lf <<") = " << histo->GetBinContent( (int)peakInfo[peakKey_Pos] - peakWidth_lf)<<endl;
        //cout<<"histo->GetBinContent("<< (int)peakInfo[peakKey_Pos] + peakWidth_rt <<") = " << histo->GetBinContent( (int)peakInfo[peakKey_Pos] + peakWidth_rt)<<endl;
        
        while ( !(histo->GetBinContent( (int)peakInfo[peakKey_Pos] - peakWidth_lf) == 0
               && histo->GetBinContent( (int)peakInfo[peakKey_Pos] + peakWidth_rt ) == 0) ) { //Loop Through Peak
            
            //Debugging
            //cout<<"============Loop============"<<endl;
            //cout<<"peakInfo['Integral'] = " << peakInfo[peakKey_Int] << endl;
            
            //Increase Integral
            if (!limit_lf && !limit_rt) { //Case: Neither Histogram Limit Reached
                peakInfo[peakKey_Int]+= histo->GetBinContent( (int)peakInfo[peakKey_Pos] - peakWidth_lf) + histo->GetBinContent( (int)peakInfo[peakKey_Pos] + peakWidth_rt);
                
                peakInfo[peakKey_LwrBd] = histo->GetBinLowEdge( (int)peakInfo[peakKey_Pos] - peakWidth_lf);
                peakInfo[peakKey_UprBd] = histo->GetBinLowEdge( (int)peakInfo[peakKey_Pos] + peakWidth_rt + 1); //Plus one Here for same reason as +2 above.
            } //End Case: Neither Histogram Limit Reached
            else if(limit_lf && !limit_rt){ //Case: Left Histogram Limit Reached, Add Only in Right Direction
                peakInfo[peakKey_Int]+= histo->GetBinContent( (int)peakInfo[peakKey_Pos] + peakWidth_rt);
                
                peakInfo[peakKey_UprBd] = histo->GetBinLowEdge( (int)peakInfo[peakKey_Pos] + peakWidth_rt + 1); //Plus one Here for same reason as +2 above.
            } //End Case: Left Histogram Limit Reached, Add Only in Right Direction
            else if(!limit_lf && limit_rt){ //Case: Right Histogram Limit Reached, Add Only in Left Direction
                peakInfo[peakKey_Int]+= histo->GetBinContent( (int)peakInfo[peakKey_Pos] - peakWidth_lf);
                
                peakInfo[peakKey_LwrBd] = histo->GetBinLowEdge( (int)peakInfo[peakKey_Pos] - peakWidth_lf);
            } //End Case: Right Histogram Limit Reached, Add Only in Left Direction
            
            //Debugging
            //cout<<"peakInfo['Integral'] = " << peakInfo[peakKey_Int] << endl;
            
            //Widen Lower Acceptance Zone
            if ( ( (int)peakInfo[peakKey_Pos] - peakWidth_lf - 1) > 1 ) { //Check: Left Limit Reached?
                peakWidth_lf++;             //Yes ++ if you -- you will go in the wrong direction because of how the expression is made!
            } //End Check: Left Limit Reached?
            else{ //Check: Left Limit Reached, Set Flag
                limit_lf = true;
            } //End Check: Left Limit Reached, Set Flag
            
            //Widen Upper Acceptance Zone
            if ( ( (int)peakInfo[peakKey_Pos] + peakWidth_rt + 1) < histo->GetNbinsX() ) { //Check: Right Limit Reached?
                peakWidth_rt++;
            } //End Check: Right Limit Reached?
            else{ //Check: Right Limit Reached, Set Flag
                limit_rt = true;
            } //End Check: Right Limit Reached, Set Flag
            
            //Debugging
            //cout<<"histo->GetBinContent("<< (int)peakInfo[peakKey_Pos] - peakWidth_lf <<") = " << histo->GetBinContent( (int)peakInfo[peakKey_Pos] - peakWidth_lf)<<endl;
            //cout<<"histo->GetBinContent("<< (int)peakInfo[peakKey_Pos] + peakWidth_rt <<") = " << histo->GetBinContent( (int)peakInfo[peakKey_Pos] + peakWidth_rt)<<endl;
        } //End Loop Through Peak
        
        //Debugging
        //cout<< "Integral = " << peakInfo[peakKey_Int] << endl;
    } //End Case: Peak Found!
    else if ( bin_lf > 0 && bin_mid == 0 && bin_rt > 0 ) { //Case: Located in Valley, Shift by Preference
        //Debugging
        //cout<<"VALLEY! Shifting ";
        //shiftRight ? cout<<"Right"<<endl : cout<<"Left" << endl;
        
        if (shiftRight) { //Case: In Valley's Shift Right
            peakInfo[peakKey_Pos]++;
            peakInfo[peakKey_Delta]++;
        } //End Case: In Valley's Shift Right
        else{ //Case: In Valley's Shift Left
            peakInfo[peakKey_Pos]--;
            peakInfo[peakKey_Delta]--;
        } //End Case: In Valley's Shift Left
        
        recursivePeakFinder(peakInfo,histo,shiftRight);
    } //End Case: Located in Valley, Shift by Preference
    else if ( bin_lf > bin_mid && bin_mid >= bin_rt) { //Case: Peak Offset to Left
        //Debugging
        //cout<<"Shifting Left!"<<endl;
        
        //Shift Position to the left, decrease delta to show we have moved
        peakInfo[peakKey_Pos]--;
        peakInfo[peakKey_Delta]--;
        
        recursivePeakFinder(peakInfo,histo,shiftRight);
    } //End Case: Peak Offset to Left
    else if ( bin_lf <= bin_mid && bin_mid < bin_rt) { //Case: Peak Offset to Right
        //Debugging
        //cout<<"Shifting Right!"<<endl;
        
        //Shift Position to the right, decrease delta to show we have moved
        peakInfo[peakKey_Pos]++;
        peakInfo[peakKey_Delta]++;
        
        recursivePeakFinder(peakInfo,histo,shiftRight);
    } //End Case: Peak Offset to Left
    
    return;
} //End TestBeamAnalyzer::recursivePeakFinder()

//Write Root Files
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
void TestBeamAnalyzer::writeEffHistograms2File(string input, string option){
    //Variable Declaration
    TDirectory *dir_Detectors;
    
    TFile *TFOutput = new TFile(input.c_str(), option.c_str(), "", 1);
    
    std::vector<std::vector<RunParam> >::iterator latIter;
    std::map<string,DetResults,cmp_str>::iterator detIter;
    
    //Check if File Exists Already
    if( option.compare("RECREATE") == 0){ //Case: TFOutput Does Not Exist, Create File Structure
        dir_Detectors = TFOutput->mkdir("Detectors");
    } //End Case: TFOutput Does Not Exist, Create File Structure
    else{ //Case: TFOutput Exists, get Previously Created File Structure
        if ( TFOutput->GetDirectory("Detectors", false, "GetDirectory") == 0) {
            dir_Detectors = TFOutput->mkdir("Detectors");
        }
        else{
            dir_Detectors = TFOutput->GetDirectory("Detectors", false, "GetDirectory");
        }
    } //End Case: TFOutput Exists, get Previously Created File Structure
        
    for(detIter = results.begin(); detIter != results.end(); detIter++){ //Loop Over Detectors
        TDirectory *dir_ThisDet = dir_Detectors->mkdir( ((*detIter).first).c_str() );
        
        map<int,InfoPerLat,cmp_int>::iterator latIter = ((*detIter).second).Scan_Lat.begin();
        
        for(latIter; latIter!=((*detIter).second).Scan_Lat.end(); latIter++){ //Loop Over Latencies for Each Detector
            TDirectory *dir_ThisLat = dir_ThisDet->mkdir( Form("Lat%s", (getString((*latIter).first)).c_str()) );
            
            TDirectory *dir_RawGraphs   = dir_ThisLat->mkdir("RawGraphs");
            TDirectory *dir_Plots       = dir_ThisLat->mkdir("PremadePlots");
            
            dir_RawGraphs->cd();
            ((*latIter).second).graph_DetEff_v_Curr->Write();
            
            dir_Plots->cd();
            ((*latIter).second).canvas_DetEff_v_Curr->Write();
        } //End Loop Over Latencies for Each Detector
    } //End Loop Over Detectors
    
    return;
} //End TestBeamAnalyzer::writeEffHistograms()




