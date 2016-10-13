#include "../Utilities/ColoredMessages.hpp"
#include "LoaderSettings_TrackFinder.hpp"

//constructor with filename
LoaderSettings_TrackFinder::LoaderSettings_TrackFinder(string filename)
    : 
      TrackerOffsetFile(""), TrackFinder_Verbose(0), TrackFinder_TrackVerbose(0), TrackFinder_OffsetVerbose(0), error(0)


{

  ifstream ifile;
  
  ifile.open(filename.c_str());

  string beginningofsettings, endofsettings;
  string head11, head12, head13, head14;

  int i=0;
  int verbose =1;
  int dataverbose =0;	

  if ( ifile.is_open() )
    {
	error=0;
     	if (verbose) //cout << "\nOpening the Setting File: " << filename << endl;
	{
        char openingfile[100];
        sprintf(openingfile, "\nOpening the Setting File: %s", filename.c_str());
        GreenOut(openingfile);
	GreenOut("\nOpening the Setting File: "); cout << filename.c_str() << endl;
	}
      	while(ifile.good())
	{
	  	ifile 	>>  beginningofsettings
			>>  head11 >> TrackerOffsetFile   
			>>  head12 >> TrackFinder_Verbose   
			>>  head13 >> TrackFinder_TrackVerbose   
			>>  head14 >> TrackFinder_OffsetVerbose   
			>>  endofsettings;                

	  	if (dataverbose && i==0)
	 	{
	  		cout 	<< "\n" 
				<< head11  << "\t" << TrackerOffsetFile  		<< "\n" 
				<< head12  << "\t" << TrackFinder_Verbose                 << "\n"
				<< head13  << "\t" << TrackFinder_TrackVerbose            << "\n"
				<< head14  << "\t" << TrackFinder_OffsetVerbose           << "\n"
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
	RedErrorOut("ERROR[Setting Configuration File]: SETTING FILE %s NOT FOUND\n"); cout << filename.c_str() << endl;
	error=1;
    }
  ifile.close();
}
  
