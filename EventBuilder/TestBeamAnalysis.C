//
//  TestBeamAnalysis.C
//  
//
//  Created by Brian L Dorney on 14/10/14.
//
//

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

//My Includes
#include "TestBeamAnalyzer.cc"

int main (){
    string fileInput        = "FilesToAnalyze.txt";
    string fileInput_TDC    = "FilesToAnalyze_TDC.txt";
    
    string masterFileName;
    string latFile;
    
    vector<string> vec_latFiles;
    
    TestBeamAnalyzer myAnalyzer;
    
    ifstream dataInput; dataInput.open( fileInput.c_str() );
    
    int counter=0;
    
    do {
        if (dataInput.eof()) break;
        
        if(counter == 0){
            getline(dataInput,masterFileName);
            //cout<<"masterFileName = " << masterFileName << endl;
        }
        else{
            getline(dataInput,latFile);
            
            if(latFile.compare("")==0) break;
            
            //cout<<"latFile = " << latFile << endl;
            
            vec_latFiles.push_back(latFile);
        }
        
        counter++;
    } while (!dataInput.eof());

    //Detection Efficiency
    myAnalyzer.setFilesEff(masterFileName,vec_latFiles);
    myAnalyzer.setEffFitDraw(true);	//Draws the fit on the canvas if true
    //myAnalyzer.setEffFitFormula(/* string argument */); //Takes string formula, default is hard-coded to "(1+exp([0]*(x+[1])))^(-1)" may require some "play"
    myAnalyzer.setEffFitFormula("TMath::Sqrt2()/TMath::Sqrt(TMath::Pi())*(1+TMath::Erf((x*[0]-[1])+[2]))+[3]*TMath::Sqrt(TMath::Pi())*(1+TMath::Erf((x*[0]-[1])+[2]))"); // Function Provided by Patrizia	//Takes string formula, default is hard-coded to "(1+exp([0]*(x+[1])))^(-1)" may require some "play"
//    virtual void setEffFitFormula(string input = "TMath::Sqrt2()/TMath::Sqrt(TMath::Pi())*(1+TMath::Erf((x*[0]-[1])+[2]))+[3]*TMath::Sqrt(TMath::Pi())*(1+TMath::Erf((x*[0]-[1])+[2]))"){fitEff_Formula = input; return;};
    myAnalyzer.setEffFitOption("R");
    myAnalyzer.analyzeRunsEff();
    myAnalyzer.makeDetLogEff();
    myAnalyzer.makeHistogramsEff("EffPlots.root","RECREATE");
    
    //TDC
    //myAnalyzer.setFilesTDC(fileInput_TDC);
    //myAnalyzer.setTDCNoiseThreshold(9);
    //myAnalyzer.setTDCAutoRangingFit(false);
    //myAnalyzer.setTDCFitOption("R");
    //myAnalyzer.setTDCRebinFactor(2);
    //myAnalyzer.analyzeRunsTDC();
    //myAnalyzer.makeDetLogTDC();
    //myAnalyzer.makeHistogramsTDC("EffPlots_TDC.root","RECREATE");
    
    return 0;
} //End main()
