#include "../Utilities/ColoredMessages.hpp"
#include "LoaderSettings_Analyzer.hpp"

//constructor with filename
LoaderSettings_Analyzer::LoaderSettings_Analyzer(string filename)
    : 
      Analyzer_OffsetFile(""),Analyzer_Verbose(0),Analyzer_EffCalculatorVerbose(0),Analyzer_EnableCoverage(0),
      Cut_Verbose(0), Cut_Chi2Value(0), Cut_ResidualValue(0.), Cut_NumberOfTracks(0), Cut_SingleXYTrackRequest(0),
      EfficiencyRadiusScan(0), EfficiencyRadiusMin(0.), EfficiencyRadiusMax(0.), EfficiencyRadiusStep(0.),
      error(0)
{

  ifstream ifile;
  
  ifile.open(filename.c_str());

  string beginningofsettings, endofsettings;
  string head00, head01, head02, head03;
  string head04, head05, head06, head07, head08;
  string head10, head11, head12, head13;

  int i=0;
  int verbose =1;
  int dataverbose =0;	

  if ( ifile.is_open() )
    {
	error=0;
     	if (verbose) //cout << "\nOpening the Setting File: " << filename << endl;
	{
        //char openingfile[100];
        //sprintf(openingfile, "\nOpening the Setting File: %s", filename.c_str());
        //GreenOut(openingfile);
	GreenOut("\nOpening the Setting File: "); cout << filename.c_str() << endl;
	}
      	while(ifile.good())
	{
	  	ifile 	>>  beginningofsettings
			>>  head00 >> Analyzer_OffsetFile 
			>>  head01 >> Analyzer_Verbose
			>>  head02 >> Analyzer_EffCalculatorVerbose  
			>>  head03 >> Analyzer_EnableCoverage   
			>>  head04 >> Cut_Verbose            
			>>  head05 >> Cut_Chi2Value            
			>>  head06 >> Cut_ResidualValue        
			>>  head07 >> Cut_NumberOfTracks            
			>>  head08 >> Cut_SingleXYTrackRequest
			>>  head10 >> EfficiencyRadiusScan 
			>>  head11 >> EfficiencyRadiusMin
			>>  head12 >> EfficiencyRadiusMax     
			>>  head13 >> EfficiencyRadiusStep
			>>  endofsettings;                

	  	if (dataverbose && i==0)
	 	{
	  		cout 	<< "\n" 
				<< head00  << "\t" << Analyzer_OffsetFile               << "\n"
				<< head01  << "\t" << Analyzer_Verbose                  << "\n"
				<< head02  << "\t" << Analyzer_EffCalculatorVerbose     << "\n"
				<< head03  << "\t" << Analyzer_EnableCoverage           << "\n"
				<< head04  << "\t" << Cut_Verbose            		<< "\n"
				<< head05  << "\t" << Cut_Chi2Value            		<< "\n"
				<< head06  << "\t" << Cut_ResidualValue        		<< "\n"
				<< head07  << "\t" << Cut_NumberOfTracks       		<< "\n"
				<< head08  << "\t" << Cut_SingleXYTrackRequest		<< "\n"
				<< head10  << "\t" << EfficiencyRadiusScan 		<< "\n"
				<< head11  << "\t" << EfficiencyRadiusMin  		<< "\n"
				<< head12  << "\t" << EfficiencyRadiusMax  		<< "\n"
				<< head13  << "\t" << EfficiencyRadiusStep 		<< "\n"
				<< endl; 
	  	}                
	  	i++;            
	}
    if (beginningofsettings!="BEGINNINGOFSETTINGS" || endofsettings!="ENDOFSETTINGS")
    //cout << "ERROR[Setting File]: BEGINNING and END of settings NOT FOUND\n" << endl;
    {RedErrorOut("ERROR[Setting File]: BEGINNING and END of settings NOT FOUND\n");error=1;}
    }
    else 
    {
	//cout << "ERROR[Setting File]: SETTING FILE "<< filename << " NOT FOUND\n" << endl;
        //char notfounderror[100];
        //sprintf(notfounderror, "ERROR[Setting Configuration File]: SETTING FILE %s NOT FOUND\n", filename.c_str());
        //RedErrorOut(notfounderror);
        RedErrorOut("ERROR[Setting Configuration File]: SETTING FILE NOT FOUND: "); cout << filename.c_str() << endl;
	error=1;
    }
  ifile.close();
}
  
