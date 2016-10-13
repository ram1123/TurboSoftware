#include "../Utilities/ColoredMessages.hpp"
#include "LoaderOffsetAndCoverage_Analyzer.hpp"

//constructor with filename
LoaderOffsetAndCoverage_Analyzer::LoaderOffsetAndCoverage_Analyzer(string filename, int loadedDetectors)
  :     NumberOfDetectors(0), det_index(0), xOffset(0), yOffset(0), zOffset(0),
        xTrackerOffset(0), yTrackerOffset(0),
        xCoverageMin(0), xCoverageMax(0), yCoverageMin(0), yCoverageMax(0),
        RCoverageMin(0), RCoverageMax(0), PhiCoverageMax(0), PhiCoverageMin(0),
	effRad(0),
	error(0)
{

  ifstream ifile;
  
  ifile.open(filename.c_str());

  string beginningofsettings, head, det_name, endofsettings;
  string col1, col2, col3, col4; 
  string col5, col6; 
  string col7, col8, col9, col10; 
  string col11, col12, col13, col14; 
  string col15; 

  int i=0;
  int verbose =1;
  int dataverbose =1;

  if ( ifile.is_open() )
    {
	error=0;
  	if (verbose) 
	{
        //char openingfile[100];
        //sprintf(openingfile, "\nOpening the Analyzer Offset and Covrage Configuration File: %s", filename.c_str());
        //GreenOut(openingfile);
	GreenOut("Opening the Analyzer Offset and Covrage Configuration File: "); cout << filename.c_str() << endl;
	}
      	while(ifile.good())
	{
		if (i==0) 
		{
	  		ifile >> beginningofsettings >> head >> NumberOfDetectors 
			>> col1  >> col2  >> col3  >> col4 
			>> col5  >> col6  
			>> col7	 >> col8  >> col9  >> col10 
			>> col11 >> col12 >> col13 >> col14 
			>> col15
			>> det_name;

			if (dataverbose) 
			{cout << "Loading: " 
			<< col1  << ", "  << col2  << ", " << col3  << ", " << col4 
			<< ", "  << col5  << col6  
			<< ", "  << col7  << col8  << ", " << col9  << ", " << col10 
			<< ", "  << col11 << col12 << ", " << col13 << ", " << col14 
			<< ", "  << col15
			<< ", "  << det_name
			<< endl;}
 
  			det_index 	= new int[NumberOfDetectors];
  			xOffset 	= new double[NumberOfDetectors];
  			yOffset 	= new double[NumberOfDetectors]; 	
			zOffset       	= new double[NumberOfDetectors];
                        xTrackerOffset  = new double[NumberOfDetectors];
                        yTrackerOffset  = new double[NumberOfDetectors];
                        xCoverageMin    = new double[NumberOfDetectors];
                        xCoverageMax    = new double[NumberOfDetectors]; 
                        yCoverageMin    = new double[NumberOfDetectors];
                        yCoverageMax    = new double[NumberOfDetectors]; 
                        RCoverageMin    = new double[NumberOfDetectors];
                        RCoverageMax    = new double[NumberOfDetectors]; 
                        PhiCoverageMax  = new double[NumberOfDetectors];
                        PhiCoverageMin  = new double[NumberOfDetectors];
                        effRad  	= new double[NumberOfDetectors];

		}
	  	ifile 
		>> det_index[i] >> xOffset[i] >> yOffset[i] >> zOffset[i]
		>> xTrackerOffset[i] >> yTrackerOffset[i] 
		>> xCoverageMin[i] >> xCoverageMax[i] >> yCoverageMin[i] >> yCoverageMax[i]
		>> RCoverageMin[i] >> RCoverageMax[i] >> PhiCoverageMax[i] >> PhiCoverageMin[i]
		>> effRad[i]
		>> det_name;

                if (i==NumberOfDetectors-1)
                {
                ifile   >>  endofsettings;
                }

	  	if (dataverbose && i<NumberOfDetectors)
	 	{	
	  		cout 	<< "ID: " 	<< det_index[i] 
				<< "\t"	<< xOffset[i]
				<< "\t"	<< yOffset[i]
				<< "\t"	<< zOffset[i]
				<< "\t"	<< xTrackerOffset[i]	
                                << "\t"	<< yTrackerOffset[i]
                                << "\t"	<< xCoverageMin[i]
				<< "\t"	<< xCoverageMax[i]	
                                << "\t"	<< yCoverageMin[i]
                                << "\t"	<< yCoverageMax[i]
				<< "\t"	<< RCoverageMin[i]	
                                << "\t"	<< RCoverageMax[i]
                                << "\t"	<< PhiCoverageMax[i]
				<< "\t"	<< PhiCoverageMin[i]	
				<< "\t"	<< effRad[i]	
				<< "\t" << det_name
				<< endl;
	  	}
	  	i++;
	}
    if (loadedDetectors!=NumberOfDetectors)
    {RedErrorOut("ERROR[Analyzer Offset&Coverage File]: The number of loaded detectors is DIFFERENT from the ones in the OFFSET File\n");error=1;}

    if (i!=NumberOfDetectors+1)
    {RedErrorOut("ERROR[Analyzer Offset&Coverage File]: The number of loaded paramenter is DIFFERENT from the numbers of detector\n");error=1;}

    if (beginningofsettings!="BEGINNINGOFSETTINGS" || endofsettings!="ENDOFSETTINGS")
    {RedErrorOut("ERROR[Analyzer Offset&Coverage File]: BEGINNING and END of settings NOT FOUND\n");error=1;}

    }
  else 
  {	
        //char notfounderror[100];
        //sprintf(notfounderror, "ERROR[Analyzer Offset&Coverage File]: OFFSET FILE %s NOT FOUND\n", filename.c_str());
        //RedErrorOut(notfounderror);
	RedErrorOut("ERROR[Analyzer Offset&Coverage File]: FILE NOT FOUND: "); cout << filename.c_str() << endl;
	error=1;
  }

  ifile.close();
      
}
  
