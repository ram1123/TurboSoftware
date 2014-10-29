///////////////////////////////////////
//
// Class LoaderSettings_Analyzer
//////////////////////////////////////

#include <string>
#include <iostream>
#include <fstream>

class LoaderSettings_Analyzer
{
 public:

  string 	Analyzer_OffsetFile		;
  int 		Analyzer_Verbose	 	;
  int 		Analyzer_EffCalculatorVerbose 	;
  int 		Analyzer_EnableCoverage		;
  int		Cut_Verbose			;
  int		Cut_Chi2Value			;
  float 	Cut_ResidualValue		;
  int		Cut_NumberOfTracks		;
  bool		Cut_SingleXYTrackRequest	;
  bool		EfficiencyRadiusScan		;
  float		EfficiencyRadiusMin		;
  float		EfficiencyRadiusMax		;
  float		EfficiencyRadiusStep		;
  bool		error				;

  //Std Constructor
  LoaderSettings_Analyzer(): 
 	Analyzer_OffsetFile(""),Analyzer_Verbose(0),Analyzer_EffCalculatorVerbose(0),Analyzer_EnableCoverage(0),
	Cut_Verbose(0), Cut_Chi2Value(0), Cut_ResidualValue(0.), Cut_NumberOfTracks(0), Cut_SingleXYTrackRequest(0),
	EfficiencyRadiusScan(0), EfficiencyRadiusMin(0.), EfficiencyRadiusMax(0.), EfficiencyRadiusStep(0.),
	error(0)	
    {};
  
  //Constructor with filename
  LoaderSettings_Analyzer (string filename);
    
  virtual ~LoaderSettings_Analyzer() {};

  ClassDef(LoaderSettings_Analyzer,1);
};

  
