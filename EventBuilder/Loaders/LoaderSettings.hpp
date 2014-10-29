///////////////////////////////////////
//
// Class LoaderSettings
//////////////////////////////////////

#ifndef LOADERSETTINGS_HPP_
#define LOADERSETTINGS_HPP_


#include <string>
#include <iostream>
#include <fstream>

class LoaderSettings
{
 public:

  string 	DetectorConfigFile		;
  string 	DetectorOffsetAndFlipFile	;
  string 	VFATConfigFile			;
  int 		Verbose                    	;
  int 		LoaderSettingsPrintOut     	;
  int 		DetectorInfoPrintOut       	;
  int 		VFATInfoPrintOut           	;
  int 		ChipIdVerbose              	;
  int 		EfficiencyEstimatorPrintOut	;
  int 		BeampProfiledataPrintOut   	;
  bool		error				;

  //Std Constructor
  LoaderSettings(): 
	DetectorConfigFile(""), DetectorOffsetAndFlipFile(""), VFATConfigFile(""),
	Verbose(0),LoaderSettingsPrintOut(0),DetectorInfoPrintOut(0),VFATInfoPrintOut(0),
	ChipIdVerbose(0),EfficiencyEstimatorPrintOut(0),BeampProfiledataPrintOut(0),
	error(0)
    {};
  
  //Constructor with filename
  LoaderSettings (string filename);
    
  virtual ~LoaderSettings() {};

  ClassDef(LoaderSettings,1);
};

#endif 
