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
    string fileInput_TDC    = "FilesToAnalyze_TDC.txt";
    
    TestBeamAnalyzer myAnalyzer;
    
    //TDC
    myAnalyzer.setFilesTDC(fileInput_TDC);
    myAnalyzer.setTDCNoiseThreshold(9);
    myAnalyzer.setTDCAutoRangingFit(false);
    //myAnalyzer.setTDCFitOption("R");
    myAnalyzer.setTDCRebinFactor(2);
    myAnalyzer.analyzeRunsTDC();
    myAnalyzer.makeDetLogTDC();
    myAnalyzer.makeHistogramsTDC("TDCPlots.root","RECREATE");
    
    return 0;
} //End main()
