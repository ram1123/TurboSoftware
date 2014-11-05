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
    paramType.run       = "Run";
    
    paramType.evt1      = "k";
    paramType.evt2      = "K";
    
    paramType.beam_mu   = "Muon";
    paramType.beam_pi   = "Pion";
    paramType.beam_el   = "El";
    
    paramType.MSPL      = "MSPL";
    
    paramType.delay     = "DLY";
    
    paramType.point     = "pt";
    
    paramType.thresh    = "T";
    paramType.lat       = "Lat";
    
    //Flag Detector Names as Not Set
    detNamesSet         = false;
    
    //Intialize Comparison
    comparison.infoMatch    = true;
    
    comparison.run_initial  = 60000;
    comparison.run_final    = 0;
    
    comparison.canvas_AllDet_DetEff_v_Curr = new TCanvas("Plot_AllDet_DetEff_v_Curr","AllDet_DetEff_v_Curr",700,700);
    
    comparison.texInfo_beam     = new TLatex();  comparison.texInfo_beam->SetTextSize(0.03);
    comparison.texInfo_delay    = new TLatex();  comparison.texInfo_delay->SetTextSize(0.03);
    comparison.texInfo_pulseLen = new TLatex();  comparison.texInfo_pulseLen->SetTextSize(0.03);
    comparison.texInfo_run      = new TLatex();  comparison.texInfo_run->SetTextSize(0.03);
    
    comparison.mGraph_AllDet_DetEff_v_Curr = new TMultiGraph("MultiGraph_AllDet_DetEff_v_Curr"," ;Current Supplied to HV Divider #left(#muA#right); Efficiency");
} //End Default Constructor

//Setters
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//Sets the name of the text files containing the efficiency values
void TestBeamAnalyzer::setEffFiles(string inputFile, string inputFile_LatSpecific){
    fileName_Eff_Master     = inputFile;
    files_Eff_LatSpecific.push_back(inputFile_LatSpecific);
    return;
} //End setEffFiles

//Sets the name of the text files containing the efficiency values
void TestBeamAnalyzer::setEffFiles(string inputFile, std::vector<string> inputFile_LatSpecific){
    fileName_Eff_Master     = inputFile;
    files_Eff_LatSpecific   = inputFile_LatSpecific;
    return;
} //End setEffFiles

//This method scans an input string to determine the parameters of the run.
//The string is the file name of the data
//vec_eff is a vector of pairs where the first member of the pair is the efficiency value and the second member is the statistical uncertainty
void TestBeamAnalyzer::setRunParam(string input, std::vector<std::pair<float,float> > vec_eff){
    //Variable Declaration
    bool exitFlag           = false;
    //bool write_runNum, write_beamType, write_delay, write_evtNum, write_lat, write_MSPL, write_thresh; //Flags for Writting the Info Panel
    
    DetInfo gem;
    
    float current           = 0.;
    
    int posLast             = 0;  //last position of an "_" in the filename
    int posUnderscore1      = 0;
    
    unsigned int idx_current= 0;
    unsigned int idx_thresh = 0;
    unsigned int idx_lat    = 0;
    unsigned int idx_pulseLen=0;
    
    string underscore       = "_";  //delimiter
    string param            = "";   //Parameter
    
    TestBeamAnalyzer::RunParam specificRunParam;
    
    vector<float> vec_current;
    
    vector<int> vec_thresh;
    vector<int> vec_lat;
    vector<int> vec_pulseLen;
    
    //Initialize specificRunParam
    specificRunParam.delay = -1;
    
    //Debugging
    //cout<<"TestBeamAnalyzer::setRunParam - No Fault 1" << endl;
    //cout<<"input string = " << input << endl;
    //cout<<"Looping Over input string" << endl;
    
    //Go through the input file name
    //Treating the underscores as deliminators find the relevant parameters of the run
    //Store them
    do {
        //Debugging
        //cout<<"TestBeamAnalyzer::setRunParam - No Fault 1_a" << endl;
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
        
        //Determine what this parameter is:
        if( param.compare(0,3,paramType.run) == 0 ){                                                            //Run Number
            if( param.compare(3,1,"0") == 0 ){
                specificRunParam.numRun = atoi( (param.substr(4,3)).c_str() );
            }
            else{
                specificRunParam.numRun = atoi( (param.substr(3,4)).c_str() );
            }
        } //End Case: Run Number
        else if( param.compare(0,4,paramType.beam_mu) == 0 ){ specificRunParam.beamType = param; }              //Beam Type
        else if( param.compare(0,4,paramType.beam_pi) == 0 ){ specificRunParam.beamType = param; }              //"        "
        else if( param.compare(0,2,paramType.beam_el) == 0 ){ specificRunParam.beamType = "Electron"; }         //"        "
        else if( param.compare(2,1,paramType.evt1) == 0 || param.compare(2,1,paramType.evt2) == 0 ){            //Event Number
            specificRunParam.numEvt = atoi( (param.substr(0,2)).c_str() ) * 1000;
        } //End Case: Event Number
        else if( param.compare(0,4,paramType.MSPL) == 0 ){                                                      //Mono-stable Pulse Length
            vec_pulseLen.push_back( atoi( (param.substr(4,1)).c_str() ) );
        } //End Case: Mono-stable Pulse Length
        else if( param.compare(0,3,paramType.delay) == 0 ){                                                     //Delay
            specificRunParam.delay = atoi( (param.substr(3,2)).c_str() );
        } //End Case: Delay
        else if( param.compare(3,2,paramType.point) == 0 ){                                                     //Current
            current = atof( (param.substr(0,3)).c_str() )
            + atof( (param.substr(5,1)).c_str() ) / 10.;
            
            vec_current.push_back(current);
        } ///End Case: Current
        else if( param.compare(0,1,paramType.thresh) == 0 ){                                                    //Threshold
            if(param.length() == 2){ //Case: Single-Digit Threshold
                vec_thresh.push_back( atoi( (param.substr(1,1)).c_str() ) );
            } //End Case: Single-Digit Threshold
            else{ //Case: Multi-Digit Threshold
                vec_thresh.push_back( atoi( (param.substr(1,param.length()-1)).c_str() ) );
            } //End Case: Multi-Digit Threshold
        } //End Case: Threshold
        else if( param.compare(0,3,paramType.lat) == 0 ){                                                            //Latency
            vec_lat.push_back( atoi( (param.substr(3,param.length()-3)).c_str() ) );
        } //End Case: Latency
        else { //Case: Unrecognized Parameter
            //cout<<"Case: Unknown"<<endl;
            //cout<<"Parameter = " << param << " Not Recognized" << endl;
        } //End Case: Unrecognized Parameter
    } while (!exitFlag); //Loop Through filename to find all parameters of interest (separated by underscores)
    
    //Debugging
    //cout<<"TestBeamAnalyzer::setRunParam - No Fault 2" << endl;
    
    //Assign the detector specific parameters to the detector structure map
    //It is understood that vec_detNames has the same ordering as what appears in the file name
    //If the size of vec_detNames and the vectors containing the identified parameters are not the same
    //then all detectors will be assigned the same parameters (at index 0) for a given parameter.
    //i.e. if vec_thresh.size() == 2 and vec_detNames == 3 then all detectors are assigned vec_thresh[0]
    for(unsigned int i=0; i<vec_detNames.size(); i++){ //Loop Over vec_detNames
        //Debugging
        //cout<<"======================================================="<<endl;
        //cout<<"vec_detNames["<<i<<"] = " << vec_detNames[i] << endl;
        
        //Set the indicies
        if(vec_detNames.size() == vec_current.size() ){ idx_current = i; }
        else{                                           idx_current = 0; }
        
        if(vec_detNames.size() == vec_lat.size() ){     idx_lat = i; }
        else{                                           idx_lat = 0; }
        
        if(vec_detNames.size() == vec_pulseLen.size() ){idx_pulseLen = i; }
        else{                                           idx_pulseLen = 0; }
        
        if(vec_detNames.size() == vec_thresh.size() ){  idx_thresh = i; }
        else{                                           idx_thresh = 0; }
        
        //Set the values
        gem.current     = vec_current[idx_current];     //cout<<"current = " << vec_current[idx_current] << endl;
        gem.eff         = vec_eff[i].first;             //cout<<"eff = " << vec_eff[i].first << "+/-" << vec_eff[i].second << endl;
        gem.eff_sigma   = vec_eff[i].second;
        gem.latency     = vec_lat[idx_lat];             //cout<<"lat = " << vec_lat[idx_lat] << endl;
        gem.pulseLen    = vec_pulseLen[idx_pulseLen];   //cout<<"MSPL = " << vec_pulseLen[idx_pulseLen] << endl;
        gem.thresh      = vec_thresh[idx_thresh];       //cout<<"thresh = " << vec_thresh[idx_thresh] << endl;
        
        //Set the name
        gem.name        = vec_detNames[i];
        
        specificRunParam.detectors[vec_detNames[i]] = gem;
        
        if( results.count(vec_detNames[i]) > 0 ){ //Case: Detector Exists
            if (results[vec_detNames[i]].latScan.count(vec_lat[idx_lat]) > 0 ) { //Case: Latency for this Detector Exists
                //No delay consistency check; this is allowed to change
                
                //Check Consistency of MSPL
                if(results[vec_detNames[i]].latScan[vec_lat[idx_lat]].pulseLen != vec_pulseLen[idx_pulseLen]){ //Case: MSPL Check
                    cout<<"Warning Pulse Length Changed Mid Run"<<endl;
                    cout<<"Detector = " << vec_detNames[i] << " Latency = " << vec_lat[idx_lat] << endl;
                    cout<<"Expect MSPL = " << results[vec_detNames[i]].latScan[vec_lat[idx_lat]].pulseLen << " Current MSPL = " << vec_pulseLen[idx_pulseLen] << endl;
                    
                    results[vec_detNames[i]].infoMatch = false;
                } //End Case: MSPL Check
                
                //Check to see if the minimum run number for this latency value is set correctly
                if(specificRunParam.numRun < results[vec_detNames[i]].latScan[vec_lat[idx_lat]].run_initial){ //Case: Initial Run Check
                    results[vec_detNames[i]].latScan[vec_lat[idx_lat]].run_initial = specificRunParam.numRun;
                } //End Case: Initial Run Check
                
                //Check to see if the maximum run number for this latency value is set correctly
                if(specificRunParam.numRun > results[vec_detNames[i]].latScan[vec_lat[idx_lat]].run_initial){ //Case: Final Run Check
                    results[vec_detNames[i]].latScan[vec_lat[idx_lat]].run_final = specificRunParam.numRun;
                } //End Case: Final Run Check
                
                //Check Consistency of Threshold
                if(results[vec_detNames[i]].latScan[vec_lat[idx_lat]].thresh != vec_thresh[idx_thresh]){ //Case: Threshold Check
                    cout<<"Warning Threshold Changed Mid Run"<<endl;
                    cout<<"Detector = " << vec_detNames[i] << " Latency = " << vec_lat[idx_lat] << endl;
                    cout<<"Expect Thresh = " << results[vec_detNames[i]].latScan[vec_lat[idx_lat]].thresh << " Current Thresh = " << vec_thresh[idx_thresh] << endl;
                    
                    results[vec_detNames[i]].infoMatch = false;
                } //End Case: Threshold Check
                
                //Check Consistency of Beam Type
                if(results[vec_detNames[i]].latScan[vec_lat[idx_lat]].beamType != specificRunParam.beamType){ //Case: BeamType Check
                    cout<<"Warning Beam Type Changed Mid Run"<<endl;
                    cout<<"Detector = " << vec_detNames[i] << " Latency = " << vec_lat[idx_lat] << endl;
                    cout<<"Expect Beam = " << results[vec_detNames[i]].latScan[vec_lat[idx_lat]].beamType << " Current Beam = " << specificRunParam.beamType << endl;
                    
                    results[vec_detNames[i]].infoMatch = false;
                } //End Case: MSPL Check
                
                //Store Data
                results[vec_detNames[i]].latScan[vec_lat[idx_lat]].currScan.push_back(vec_current[idx_current]);
                results[vec_detNames[i]].latScan[vec_lat[idx_lat]].effs.push_back(vec_eff[i].first);
                results[vec_detNames[i]].latScan[vec_lat[idx_lat]].sigma_effs.push_back(vec_eff[i].second);
            } //End Case: Latency for this Detector Exists
            else{ //Case: Latency for this Detector Does Not Exist
                InfoPerLat firstLatOccurence;
                
                firstLatOccurence.delay         = specificRunParam.delay;
                firstLatOccurence.pulseLen      = vec_pulseLen[idx_pulseLen];
                firstLatOccurence.run_initial   = specificRunParam.numRun;
                firstLatOccurence.run_final     = 0;
                firstLatOccurence.thresh        = vec_thresh[idx_thresh];
                
                firstLatOccurence.beamType      = specificRunParam.beamType;
                
                firstLatOccurence.currScan.push_back(vec_current[idx_current]);
                firstLatOccurence.effs.push_back(vec_eff[i].first);
                firstLatOccurence.sigma_effs.push_back(vec_eff[i].second);
                
                //Check that Info Matches Previous Information
                if (firstLatOccurence.delay != results[vec_detNames[i]].delay
                    || firstLatOccurence.pulseLen != results[vec_detNames[i]].pulseLen
                    || firstLatOccurence.beamType != results[vec_detNames[i]].beamType) { //Case: Check Info Matches for all latency curves for this detector match!
                    
                    cout<<"Warning Information Changed Mid Run for Detector " << vec_detNames[i] <<endl;
                    cout<<"Pulse Length, Trigger Mode/Delay, or Beam Type does not match Expectation"<<endl;
                    cout<<"Please Cross-check input runs"<<endl;
                    
                    results[vec_detNames[i]].infoMatch = false;
                } //End Case: Check Info Matches for all latency curves for this detector match!
                
                results[vec_detNames[i]].latScan[vec_lat[idx_lat]] = firstLatOccurence;
            } //End Case: Latency for this Detector Does Not Exist
        } //End Case: Detector Exists
        else{ //Case: Detector Does Not Exist
            DetResults firstDetOccurrence;
            InfoPerLat firstLatOccurence;
            
            //Set Parameters for Info Per Lat
            firstLatOccurence.delay         = specificRunParam.delay;
            firstLatOccurence.pulseLen      = vec_pulseLen[idx_pulseLen];
            firstLatOccurence.run_initial   = specificRunParam.numRun;
            firstLatOccurence.run_final     = 0;
            firstLatOccurence.thresh        = vec_thresh[idx_thresh];
            
            firstLatOccurence.beamType      = specificRunParam.beamType;
            
            firstLatOccurence.currScan.push_back(vec_current[idx_current]);
            firstLatOccurence.effs.push_back(vec_eff[i].first);
            firstLatOccurence.sigma_effs.push_back(vec_eff[i].second);
            
            //Put Info Per Lat into info per detector
            firstDetOccurrence.latScan[vec_lat[idx_lat]] = firstLatOccurence;
            
            //store delay, pulseLen, and beamType (This is for Easier Access to the Information)
            firstDetOccurrence.infoMatch    = true; //Initialize to true, only after looking at the others will we know this should be false
            firstDetOccurrence.delay        = specificRunParam.delay;
            firstDetOccurrence.pulseLen     = vec_pulseLen[idx_pulseLen];
            firstDetOccurrence.beamType     = specificRunParam.beamType;
            
            //Put Info Per Detector into results
            results[vec_detNames[i]] = firstDetOccurrence;
        } //End Case: Detector Not Exist
    } //End Loop Over vec_detNames
    
    //Debugging
    //cout<<"TestBeamAnalyzer::setRunParam - No Fault 3" << endl;
    
    vec_RunParam.push_back(specificRunParam);
    
    //Debugging
    //cout<<"TestBeamAnalyzer::setRunParam - No Fault End" << endl;
    
    return;
} //End TestBeamAnalyzer::RunParam()

//Getters
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
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

//void TestBeamAnalyzer::setCanvasStyle(TCanvas &canvas){return;} //End TestBeamAnalyzer::setCanvasStyle()


//Analyzers
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------

//Analyze Runs!
void TestBeamAnalyzer::analyzeEffRuns(){
    //Variable Declaration
    float eff, eff_sigma;
    
    ifstream masterEffFile;
    ifstream latSpecificFile;
    
    std::pair<float, float> effAndError;
    
    string fileInput;
    string runName, eff1, eff2, eff3;
    
    vector<std::pair<float, float> > vec_eff;
    
    //Debugging
    //cout<<"TestBeamAnalyzer::analyzeEffRuns() - No Fault 1"<<endl;
    
    //Open Master Files
    masterEffFile.open( fileName_Eff_Master.c_str() );
    
    //Set Detector Names
    if(!detNamesSet){ //Check if Names Have Been Set
        masterEffFile>>fileInput;                                       //First one should be worthless ("Reads FileName")
        masterEffFile>>fileInput;   vec_detNames.push_back(fileInput);  //1sr Detector Name
        masterEffFile>>fileInput;   vec_detNames.push_back(fileInput);  //2nd Detector Name
        masterEffFile>>fileInput;   vec_detNames.push_back(fileInput);  //3rd Detector Name
    } //End Check if Names Have Been Set
    
    //Close Master File, no longer needed
    masterEffFile.close();
    
    //Debugging
    //cout<<"TestBeamAnalyzer::analyzeEffRuns() - No Fault 2"<<endl;
    
    //Analyze Latency Specific Runs
    for(unsigned int i=0; i<files_Eff_LatSpecific.size(); i++){ //Loop Over Latency Specific Files
        //Debugging
        //cout<<"TestBeamAnalyzer::analyzeEffRuns() - No Fault 2_a"<<endl;
        
        latSpecificFile.open( files_Eff_LatSpecific[i].c_str() );
        
        //Debugging
        //cout<<"Latency File I Opened = " << files_Eff_LatSpecific[i] << endl;
        //cout<<"TestBeamAnalyzer::analyzeEffRuns() - No Fault 2_b"<<endl;
        
        while( latSpecificFile >> runName >> eff1 >> eff2 >> eff3){ //Loop Over latSpecificFile
            //Debugging
            //cout<<"TestBeamAnalyzer::analyzeEffRuns() - No Fault 2_b_i"<<endl;
            //cout<<"runName = " << runName << endl;
            
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
            //cout<<"TestBeamAnalyzer::analyzeEffRuns() - No Fault 2_b_ii"<<endl;
            
            //Determine Run Parameters from File Name
            setRunParam(runName, vec_eff);
            
            //Debugging
            //cout<<"TestBeamAnalyzer::analyzeEffRuns() - No Fault 2_b_iii"<<endl;
            
            //Wipe vec_eff for next run
            vec_eff.clear();
            
            //Debugging
            //cout<<"TestBeamAnalyzer::analyzeEffRuns() - No Fault 2_b_iv - LOOP"<<endl;
        } //End Loop Over latSpecificFile
        
        //Debugging
        //cout<<"TestBeamAnalyzer::analyzeEffRuns() - No Fault 2_c"<<endl;
        
        //Close the file so we can open the next one successfully
        latSpecificFile.close();
        
        //Debugging
        //cout<<"TestBeamAnalyzer::analyzeEffRuns() - No Fault 2_d"<<endl;
        
        //Store all runs at the i^th Latency value
        vec_AllRunParams.push_back(vec_RunParam);
        
        //Wipe the runs to reset for the next latency value
        vec_RunParam.clear();
        
        //Debugging
        //cout<<"TestBeamAnalyzer::analyzeEffRuns() - No Fault 2_e - LOOP"<<endl;
    } //End Loop Over Latency Specific Files
    
    //Debugging
    //cout<<"TestBeamAnalyzer::analyzeEffRuns() - No Fault End"<<endl;
    
    return;
} //End TestBeamAnalyzer::analyzeEffRuns()

//Makers
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
void TestBeamAnalyzer::makeDetLog(){
    //Variable Declaration
    std::vector<std::vector<RunParam> >::iterator latIter;
    std::map<string,DetResults,cmp_str>::iterator detIter;
    
    cout<<"Det Log"<<endl;
    cout<<"==========================================================================="<<endl;
    cout<<"Det Name\tRun\tBeam\tDLY\tMSPL\tThresh\tLat\tCurrent\tEff"<<endl;
    for(detIter = results.begin(); detIter != results.end(); detIter++){ //Loop Over Detectors
        map<int,InfoPerLat,cmp_int>::iterator latIter = ((*detIter).second).latScan.begin();
        
        for(latIter; latIter!=((*detIter).second).latScan.end(); latIter++){ //Loop Over Latencies for Each Detector
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
            } //End Loop Over Eff Data
        } //End Loop Over Latencies for Each Detector
    } //End Loop Over Detectors
    
    return;
} //End TestBeamAnalyzer::makeDetLog()

void TestBeamAnalyzer::makeEffHistograms(){
    //Variable Declaration
    float paintPos_X;
    
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
        map<int,InfoPerLat,cmp_int>::iterator latIter = ((*detIter).second).latScan.begin();
        
        //Initialize the canvas - All Latencies
        ((*detIter).second).canvas_DetEff_v_Curr = new TCanvas(
            Form("Plot_%s_LatAll_DetEff_v_Curr",((*detIter).first).c_str()),
            Form("%s_LatAll_DetEff_v_Curr",((*detIter).first).c_str()),
            700,700);
        
        for(latIter; latIter!=((*detIter).second).latScan.end(); latIter++){ //Loop Over Latencies for Each Detector
            //Initialize Histogram
            ((*latIter).second).graph_DetEff_v_Curr = new TGraphErrors( ((*latIter).second).currScan.size() );
            
            ((*latIter).second).graph_DetEff_v_Curr->SetName(Form("%s_Lat%s_DetEff_v_Curr", ((*detIter).first).c_str(), (getString((*latIter).first ) ).c_str() ) );
            
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
                Form("Plot_%s_Lat%s_DetEff_v_Curr",((*detIter).first).c_str(), (getString((*latIter).first)).c_str()),
                Form("%s_Lat%s_DetEff_v_Curr",((*detIter).first).c_str(), (getString((*latIter).first)).c_str()),
                700,700);
            
            //Determine Paint Position
            if(((*latIter).second).currScan[0] > ((*latIter).second).currScan.back()){ //Case: 0^th Member Highest Point
                paintPos_X = ((*latIter).second).currScan.back();
            } //End Case: 0^th Member Highest Point
            else{ //Case: Last Member Highest Point
                paintPos_X = ((*latIter).second).currScan[0];
            } //End Case: Last Member Highest Point
            
            //Set Style of Canvas
            //setCanvasStyle(((*latIter).second).canvas_DetEff_v_Curr);
            
            //Go To Active Canvas
            ((*latIter).second).canvas_DetEff_v_Curr->cd();
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
            ((*latIter).second).texInfo_beam->DrawLatex(paintPos_X,0.85,Form("%s-Beam",((*latIter).second).beamType.c_str()));
            ((*latIter).second).texInfo_pulseLen->DrawLatex(paintPos_X,0.8,Form("MSPL%s",(getString(((*latIter).second).pulseLen)).c_str()));
            
            if(((*latIter).second).delay > -1){ //Case: Sync Mode
                ((*latIter).second).texInfo_delay->DrawLatex(paintPos_X,0.75,Form("Sync. Mode; DLY = %sns",(getString(((*latIter).second).delay)).c_str()));
            } //End Case: Sync Mode
            else{ //Case: Async Mode
                ((*latIter).second).texInfo_delay->DrawLatex(paintPos_X,0.75,"Async. Mode");
            } //End Case: Async Mode
            
            ((*latIter).second).texInfo_thresh->DrawLatex(paintPos_X,0.7,Form("VFAT Thresh. = %s",(getString(((*latIter).second).thresh).c_str())));
            ((*latIter).second).texInfo_lat->DrawLatex(paintPos_X,0.65,Form("VFAT Lat. = %s",(getString(((*latIter).first)).c_str())));
            
        } //End Loop Over Latencies for Each Detector
    } //End Loop Over Detectors
    
    return;
} //End TestBeamAnalyzer::makeEffHistograms()

//Makes the Histograms and simultaneously writes them
void TestBeamAnalyzer::makeEffHistograms(string input, string option){
    //Variable Declaration
    float paintPos_X;
    
    std::vector<std::vector<RunParam> >::iterator latIter;
    std::map<string,DetResults,cmp_str>::iterator detIter;
    
    TDirectory *dir_Detectors;
    
    TFile *TFOutput = new TFile(input.c_str(), option.c_str(), "", 1);
    
    TLatex *cmsPrelim                       = new TLatex();     cmsPrelim->SetTextSize(0.03);
    
    string info_run, info_beam, info_pulseLen, info_delay, info_thresh, info_lat;
    
    //Debugging
    //cout<<"TestBeamAnalyzer::makeEffHistograms - No Fault 1" <<endl;
    
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
    //cout<<"TestBeamAnalyzer::makeEffHistograms - No Fault 2" <<endl;
    
    //Setup Legend - All Detectors
    comparison.leg_AllDet_DetEff = new TLegend(0.15,0.55-0.05*(float)results.size(),0.45,0.60);
    comparison.leg_AllDet_DetEff->SetFillColor(kWhite);
    comparison.leg_AllDet_DetEff->SetLineColor(kWhite);
    
    for(detIter = results.begin(); detIter != results.end(); detIter++){ //Loop Over Detectors
        //Debugging
        //cout<<"TestBeamAnalyzer::makeEffHistograms - No Fault 2_a" <<endl;
        
        TDirectory *dir_ThisDet = dir_Detectors->mkdir( ((*detIter).first).c_str() );
        
        //((*detIter).second).run_initial = std::numeric_limits<int>::max()-1;
        //((*detIter).second).run_final   = std::numeric_limits<int>::min()+1;
        
        ((*detIter).second).run_initial = 60000;
        ((*detIter).second).run_final   = 0;
        
        map<int,InfoPerLat,cmp_int>::iterator latIter = ((*detIter).second).latScan.begin();
        
        //Initialize the MultiGraph - All Latencies
        ((*detIter).second).mGraph_AllLatPlots = new TMultiGraph(Form("MultiGraph_%s_LatAll_DetEff_v_Curr",((*detIter).first).c_str())," ;Current Supplied to HV Divider #left(#muA#right); Efficiency");
        
        //Initialize the canvas - All Latencies
        ((*detIter).second).canvas_DetEff_v_Curr = new TCanvas(
            Form("Plot_%s_LatAll_DetEff_v_Curr",((*detIter).first).c_str()),
            Form("%s_LatAll_DetEff_v_Curr",((*detIter).first).c_str()),
            700,700);
        
        //Setup Legend - All Latencies
        TLegend *leg_DetEff_AllLat = new TLegend(0.15,0.55-0.05*(float)((*detIter).second).latScan.size(),0.35,0.60);
        leg_DetEff_AllLat->SetLineColor(0);
        leg_DetEff_AllLat->SetFillColor(0);
        
        //Set Max Eff to Zero For this detector
        ((*detIter).second).max_eff = 0.;
        
        //Debugging
        //cout<<"TestBeamAnalyzer::makeEffHistograms - No Fault 2_b" <<endl;
        
        for(latIter; latIter!=((*detIter).second).latScan.end(); latIter++){ //Loop Over Latencies for Each Detector
            //Debugging
            //cout<<"TestBeamAnalyzer::makeEffHistograms - No Fault 2_b_i" <<endl;
            
            //Initialize TGraph
            ((*latIter).second).graph_DetEff_v_Curr = new TGraphErrors( ((*latIter).second).currScan.size() );
            ((*latIter).second).graph_DetEff_v_Curr->SetName(Form("%s_Lat%s_DetEff_v_Curr", ((*detIter).first).c_str(), (getString((*latIter).first ) ).c_str() ) );
            
            //Set Efficiencies
            for(unsigned int i=0;i<((*latIter).second).currScan.size(); i++){ //Loop Over Eff Data
                //Set TGraphError Points
                ((*latIter).second).graph_DetEff_v_Curr->SetPoint(i,((*latIter).second).currScan[i],((*latIter).second).effs[i]);
                ((*latIter).second).graph_DetEff_v_Curr->SetPointError(i,0,((*latIter).second).sigma_effs[i]);
                
                //Log Which Latency Value Produces Eff Plateau (Crude Method to determine this)
                if ( ((*latIter).second).effs[i] > ((*detIter).second).max_eff ) { //Check of Max Eff
                    ((*detIter).second).max_eff     = ((*latIter).second).effs[i];
                    ((*detIter).second).latAtMaxEff = (*latIter).first;
                } //End Check of Max Eff
            } //End Loop Over Eff Data
            
            //Determine initial & final run number
            if ( ((*detIter).second).run_initial > ((*latIter).second).run_initial )    ((*detIter).second).run_initial    = ((*latIter).second).run_initial;
            if ( ((*detIter).second).run_final   < ((*latIter).second).run_final )      ((*detIter).second).run_final      = ((*latIter).second).run_final;
            
            //Debugging
            //cout<<"TestBeamAnalyzer::makeEffHistograms - No Fault 2_b_ii" <<endl;
            
            //Plot The Curve - One Latency
            //======================================================
            //Initialize the canvas - Single Latency
            TCanvas *canvas_DetEff_v_Curr = new TCanvas(
                Form("Plot_%s_Lat%s_DetEff_v_Curr",((*detIter).first).c_str(), (getString((*latIter).first)).c_str()),
                Form("%s_Lat%s_DetEff_v_Curr",((*detIter).first).c_str(), (getString((*latIter).first)).c_str()),
                700,700);
            
            //Determine Paint Position
            if(((*latIter).second).currScan[0] > ((*latIter).second).currScan.back()){ //Case: 0^th Member Highest Point
                paintPos_X = ((*latIter).second).currScan.back();
            } //End Case: 0^th Member Highest Point
            else{ //Case: Last Member Highest Point
                paintPos_X = ((*latIter).second).currScan[0];
            } //End Case: Last Member Highest Point
            
            //Set Style of Canvas
            //setCanvasStyle(((*latIter).second).canvas_DetEff_v_Curr);
            
            //Go To Active Canvas & Draw Plot
            canvas_DetEff_v_Curr->cd();
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
            
            //Draw Legend - SingleLat
            TLegend *leg_DetEff_SingleLat = new TLegend(0.15,0.55,0.35,0.60);
            leg_DetEff_SingleLat->SetLineColor(0);
            leg_DetEff_SingleLat->SetFillColor(0);
            leg_DetEff_SingleLat->AddEntry(((*latIter).second).graph_DetEff_v_Curr,((*detIter).first).c_str(),"LP");
            leg_DetEff_SingleLat->Draw("same");
            
            //Draw Info Panel
            ((*latIter).second).texInfo_run         = new TLatex();     ((*latIter).second).texInfo_run->SetTextSize(0.03);
            ((*latIter).second).texInfo_beam        = new TLatex();     ((*latIter).second).texInfo_beam->SetTextSize(0.03);
            ((*latIter).second).texInfo_pulseLen    = new TLatex();     ((*latIter).second).texInfo_pulseLen->SetTextSize(0.03);
            ((*latIter).second).texInfo_delay       = new TLatex();     ((*latIter).second).texInfo_delay->SetTextSize(0.03);
            ((*latIter).second).texInfo_thresh      = new TLatex();     ((*latIter).second).texInfo_thresh->SetTextSize(0.03);
            ((*latIter).second).texInfo_lat         = new TLatex();     ((*latIter).second).texInfo_lat->SetTextSize(0.03);
            
            cmsPrelim->DrawLatex(paintPos_X-5,1.01,"CMS Preliminary");
            
            ((*latIter).second).texInfo_run->DrawLatex(paintPos_X, 0.9,Form("Runs %s - %s",(getString(((*latIter).second).run_initial)).c_str(),(getString(((*latIter).second).run_final)).c_str() ) );
            ((*latIter).second).texInfo_beam->DrawLatex(paintPos_X,0.85,Form("%s-Beam",((*latIter).second).beamType.c_str()));
            ((*latIter).second).texInfo_pulseLen->DrawLatex(paintPos_X,0.8,Form("MSPL%s",(getString(((*latIter).second).pulseLen)).c_str()));
            
            if(((*latIter).second).delay > 0){ //Case: Sync Mode
                ((*latIter).second).texInfo_delay->DrawLatex(paintPos_X,0.75,Form("Sync. Mode; DLY = %sns",(getString(((*latIter).second).delay)).c_str()));
            } //End Case: Sync Mode
            else{ //Case: Async Mode
                ((*latIter).second).texInfo_delay->DrawLatex(paintPos_X,0.75,"Async. Mode");
            } //End Case: Async Mode
            
            ((*latIter).second).texInfo_thresh->DrawLatex(paintPos_X,0.7,Form("VFAT Thresh. = %s",(getString(((*latIter).second).thresh).c_str())));
            ((*latIter).second).texInfo_lat->DrawLatex(paintPos_X,0.65,Form("VFAT Lat. = %s",(getString(((*latIter).first)).c_str())));
            
            //Write
            TDirectory *dir_ThisLat = dir_ThisDet->mkdir( Form("Lat%s", (getString((*latIter).first)).c_str()) );
            
            TDirectory *dir_RawGraphs   = dir_ThisLat->mkdir("RawGraphs");
            TDirectory *dir_Plots       = dir_ThisLat->mkdir("PremadePlots");
            
            dir_RawGraphs->cd();
            ((*latIter).second).graph_DetEff_v_Curr->Write();
            
            dir_Plots->cd();
            canvas_DetEff_v_Curr->Write();

            //Debugging
            //cout<<"TestBeamAnalyzer::makeEffHistograms - No Fault 2_b_iii" <<endl;
            
            //Store the Curves - All Latencies for One Detector
            ((*detIter).second).canvas_DetEff_v_Curr->cd();
            ((*latIter).second).graph_DetEff_v_Curr->SetMarkerStyle( getCyclicMarkerStyle(std::distance(((*detIter).second).latScan.begin(),latIter) + 2 * std::distance(results.begin(),detIter) ) );
            ((*latIter).second).graph_DetEff_v_Curr->SetMarkerColor( getCyclicColor(std::distance(((*detIter).second).latScan.begin(),latIter) + 2 * std::distance(results.begin(),detIter) ) );
            ((*latIter).second).graph_DetEff_v_Curr->SetLineColor( getCyclicColor(std::distance(((*detIter).second).latScan.begin(),latIter) + 2 * std::distance(results.begin(),detIter) ) );
            
            //Store in MultiGraph
            ((*detIter).second).mGraph_AllLatPlots->Add(((*latIter).second).graph_DetEff_v_Curr, "P");
            
            //Setup Legend
            leg_DetEff_AllLat->AddEntry(((*latIter).second).graph_DetEff_v_Curr, Form("%s; Lat %s", ((*detIter).first).c_str(), (getString((*latIter).first)).c_str() ), "LP" );
            
            //Debugging
            //cout<<"TestBeamAnalyzer::makeEffHistograms - No Fault 2_b_iv - LOOP" <<endl;
        } //End Loop Over Latencies for Each Detector
        
        //Debugging
        //cout<<"TestBeamAnalyzer::makeEffHistograms - No Fault 2_c" <<endl;
        
        //Store the Curves - Max Efficiency for Each Detector
        for(latIter = ((*detIter).second).latScan.begin(); latIter != ((*detIter).second).latScan.end(); latIter++ ){ //Loop Over Latencies
            if ( (*latIter).first == ((*detIter).second).latAtMaxEff ) { //Case: Max Found!
                //Add Distribution to Multi-Graph, it has the Eff Plateau for this Detector
                comparison.mGraph_AllDet_DetEff_v_Curr->Add(((*latIter).second).graph_DetEff_v_Curr, "P");
                
                //Add Distribtuion to Legend, it has the Eff Plateau for this Detector
                comparison.leg_AllDet_DetEff->AddEntry(((*latIter).second).graph_DetEff_v_Curr, Form("%s; Lat %s", ((*detIter).first).c_str(), (getString((*latIter).first)).c_str() ), "LP" );
                
                //Store Run Range of Comparison
                if (comparison.run_final   < ((*latIter).second).run_final  ) comparison.run_final   = ((*latIter).second).run_final;
                if (comparison.run_initial > ((*latIter).second).run_initial) comparison.run_initial = ((*latIter).second).run_initial;
                
                //Store Parameters for Info Panel
                if ( detIter == results.begin() ) { //Case: First Detector
                    comparison.infoMatch    = true; //Set to True, we won't know if it should be false until we look at the others
                    
                    //Take from latIter to avoid potential propagation errors
                    comparison.delay        = ((*latIter).second).delay;
                    comparison.pulseLen     = ((*latIter).second).pulseLen;
                    comparison.beamType     = ((*latIter).second).beamType;
                } //End Case: First Detector
                else{ //Case: All Other Detectors
                    
                    //Check to make sure information matches what we set for first detector
                    if (comparison.delay != ((*latIter).second).delay
                        || comparison.pulseLen != ((*latIter).second).pulseLen
                        || comparison.beamType != ((*latIter).second).beamType) { //Case: Detector Does Not Match Other Detector(s)
                        
                        cout<<"Warning Information Changed Mid Run When making ALL DETECTOR comparison using detector " << (*detIter).first <<endl;
                        cout<<"Pulse Length, Trigger Mode/Delay, or Beam Type does not match Expectation"<<endl;
                        cout<<"Please Cross-check input runs"<<endl;
                        
                        //Now set infoMatch to false
                        comparison.infoMatch= false;
                    } //End Case: Detector Does Not Match Other Detector(s)
                } //End Case: All Other Detectors
            } //End Case: Max Found!
        } //End Loop Over Latencies
        
        //Plot The Curve - All Latencies for One Detector
        //======================================================
        //Switch to the canvas - All Latencies
        ((*detIter).second).canvas_DetEff_v_Curr->cd();
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
        ((*detIter).second).texInfo_pulseLen    = new TLatex();     ((*detIter).second).texInfo_pulseLen->SetTextSize(0.03);
        ((*detIter).second).texInfo_delay       = new TLatex();     ((*detIter).second).texInfo_delay->SetTextSize(0.03);
        
        cmsPrelim->DrawLatex(paintPos_X-5,1.01,"CMS Preliminary");
        
        ((*detIter).second).texInfo_run->DrawLatex(paintPos_X, 0.9,Form("Runs %s - %s",(getString(((*detIter).second).run_initial)).c_str(),(getString(((*detIter).second).run_final)).c_str() ) );
        
        if( ((*detIter).second).infoMatch){ //Case: Info Same For All Latency Values
            ((*detIter).second).texInfo_beam->DrawLatex(paintPos_X,0.85,Form("%s-Beam",((*detIter).second).beamType.c_str()));
            ((*detIter).second).texInfo_pulseLen->DrawLatex(paintPos_X,0.8,Form("MSPL%s",(getString(((*detIter).second).pulseLen)).c_str()));
            
            if(((*detIter).second).delay > 0){ //Case: Sync Mode
                ((*detIter).second).texInfo_delay->DrawLatex(paintPos_X,0.75,Form("Sync. Mode; DLY = %sns",(getString(((*detIter).second).delay)).c_str()));
            } //End Case: Sync Mode
            else{ //Case: Async Mode
                ((*detIter).second).texInfo_delay->DrawLatex(paintPos_X,0.75,"Async. Mode");
            } //End Case: Async Mode
        } //End Case: Info Same For All Latency Values
        
        //Debugging
        //cout<<"TestBeamAnalyzer::makeEffHistograms - No Fault 2_d" <<endl;
        
        //Write
        dir_ThisDet->cd();
        ((*detIter).second).mGraph_AllLatPlots->Write();
        ((*detIter).second).canvas_DetEff_v_Curr->Write();
        
        //Debugging
        //cout<<"TestBeamAnalyzer::makeEffHistograms - No Fault 2_e - LOOP" <<endl;
    } //End Loop Over Detectors
    
    //Plot The Curve - Highest Efficiencies for Each Detector
    //======================================================
    comparison.canvas_AllDet_DetEff_v_Curr->cd();
    comparison.mGraph_AllDet_DetEff_v_Curr->Draw("a");  //Do this the first time to make TMultiGraph::GetHistogram() for this object valid
    comparison.mGraph_AllDet_DetEff_v_Curr->GetHistogram()->SetTitleOffset(1.20,"Y");
    comparison.mGraph_AllDet_DetEff_v_Curr->GetHistogram()->GetYaxis()->SetRangeUser(0.,1.);
    comparison.mGraph_AllDet_DetEff_v_Curr->GetHistogram()->GetYaxis()->SetDecimals(true);
    comparison.mGraph_AllDet_DetEff_v_Curr->GetHistogram()->SetTitleOffset(1.10,"X");
    comparison.mGraph_AllDet_DetEff_v_Curr->Draw("a");  //Do this the second time to draw again the plot with the above formatting
    
    //Draw Legend
    comparison.leg_AllDet_DetEff->Draw("same");
    
    //Draw Info Panel
    cmsPrelim->DrawLatex(paintPos_X-5,1.01,"CMS Preliminary");
    
    comparison.texInfo_run->DrawLatex(paintPos_X, 0.9,Form("Runs %s - %s",(getString(comparison.run_initial)).c_str(),(getString(comparison.run_final)).c_str() ) );
    
    if( comparison.infoMatch){ //Case: Info Same For All Latency Values
        comparison.texInfo_beam->DrawLatex(paintPos_X,0.85,Form("%s-Beam",comparison.beamType.c_str()));
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
    
    //Debugging
    //cout<<"TestBeamAnalyzer::makeEffHistograms - No Fault End" <<endl;
    
    return;
} //End TestBeamAnalyzer::makeEffHistograms()


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
        
        map<int,InfoPerLat,cmp_int>::iterator latIter = ((*detIter).second).latScan.begin();
        
        for(latIter; latIter!=((*detIter).second).latScan.end(); latIter++){ //Loop Over Latencies for Each Detector
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




