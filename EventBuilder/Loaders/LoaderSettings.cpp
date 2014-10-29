#include "../Utilities/ColoredMessages.hpp"
#include "LoaderSettings.hpp"

//constructor with filename
LoaderSettings::LoaderSettings(string filename)
    : DetectorConfigFile(""), DetectorOffsetAndFlipFile(""), VFATConfigFile(""),
      Verbose(0),LoaderSettingsPrintOut(0),DetectorInfoPrintOut(0),VFATInfoPrintOut(0),
      ChipIdVerbose(0),EfficiencyEstimatorPrintOut(0),BeampProfiledataPrintOut(0),
      error(0)
{

  ifstream ifile;
  
  ifile.open(filename.c_str());

  string beginningofsettings, endofsettings;
  string head1,  head2,  head3,  head4, head5;
  string head6,  head7,  head8,  head9, head10;

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
			>>  head1  >> DetectorConfigFile			 
			>>  head2  >> DetectorOffsetAndFlipFile             
			>>  head3  >> VFATConfigFile
			>>  head4  >> Verbose                       
			>>  head5  >> LoaderSettingsPrintOut        
			>>  head6  >> DetectorInfoPrintOut          
			>>  head7  >> VFATInfoPrintOut              
			>>  head8  >> ChipIdVerbose                 
			>>  head9  >> EfficiencyEstimatorPrintOut   
			>>  head10 >> BeampProfiledataPrintOut      
			>>  endofsettings;                

	  	if (dataverbose && i==0)
	 	{
	  		cout 	<< "\n" 
				<< head1   << "\t" << DetectorConfigFile                << "\n"
		   		<< head2   << "\t" << DetectorOffsetAndFlipFile         << "\n"
				<< head3   << "\t" << VFATConfigFile			<< "\n"                      
				<< head4   << "\t" << Verbose                           << "\n"
		   		<< head5   << "\t" << LoaderSettingsPrintOut            << "\n"
				<< head6   << "\t" << DetectorInfoPrintOut         	<< "\n"                      
				<< head7   << "\t" << VFATInfoPrintOut                  << "\n"
		   		<< head8   << "\t" << ChipIdVerbose                     << "\n"
				<< head9   << "\t" << EfficiencyEstimatorPrintOut  	<< "\n"                      
				<< head10  << "\t" << BeampProfiledataPrintOut          << "\n"
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
  
