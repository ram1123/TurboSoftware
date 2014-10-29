#include "../Utilities/ColoredMessages.hpp"
#include "LoaderOffset.hpp"

//constructor with filename
LoaderOffset::LoaderOffset(string filename, int loadedDetectors)
  :   NumberOfDetectors(0), det_index(0), xOffset(0) , yOffset(0), zOffset(0), error(0) 
{

  ifstream ifile;
  
  ifile.open(filename.c_str());

  string beginningofsettings, head, det_name, col1, col2, col3, col4, col5, endofsettings;

  int i=0;
  int verbose =1;
  int dataverbose =0;

  if ( ifile.is_open() )
    {
	error=0;
  	if (verbose) 
	{
	//cout << "\nOpening the  Detector Offset and Flip Configuration File: " << filename << endl;
        //char openingfile[100];
        //sprintf(openingfile, "\nOpening the Detector Offset and Flip Configuration File: %s", filename.c_str());
        //GreenOut(openingfile);
	GreenOut("\nOpening the Detector Offset File: "); cout << filename.c_str() << endl;
	}
      	while(ifile.good())
	{
		if (i==0) 
		{
	  		ifile >> beginningofsettings >> head >> NumberOfDetectors >> col1 >> col2 >> col3 >> col4 >> col5;
			if (dataverbose) cout << "Loading: " << col1 << ", " << col2 << ", " << col3 << ", " << col4 << ", " << col5 << endl; 
  			det_index 	= new int[NumberOfDetectors];
  			xOffset 	= new double[NumberOfDetectors];
  			yOffset 	= new double[NumberOfDetectors]; 	
  			zOffset 	= new double[NumberOfDetectors]; 	

		}
	  	ifile >> det_index[i] >> xOffset[i] >> yOffset[i] >> zOffset[i] >> det_name;

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
				<< "\t" << det_name
				<< endl;
	  	}
	  	i++;
	}
    if (loadedDetectors!=NumberOfDetectors)
    {RedErrorOut("ERROR[Offset File]: The number of loaded detectors is DIFFERENT from the ones in the OFFSET File\n");error=1;}

    if (i!=NumberOfDetectors+1)
    {RedErrorOut("ERROR[Offset File]: The number of loaded paramenter is DIFFERENT from the numbers of detector\n");error=1;}

    if (beginningofsettings!="BEGINNINGOFSETTINGS" || endofsettings!="ENDOFSETTINGS")
    {RedErrorOut("ERROR[Offset File]: BEGINNING and END of settings NOT FOUND\n");error=1;}

    }
  else 
  {	
        //char notfounderror[100];
        //sprintf(notfounderror, "ERROR[Offset File]: OFFSET FILE %s NOT FOUND\n", filename.c_str());
        //RedErrorOut(notfounderror);
	RedErrorOut("ERROR[Offset File]: OFFSET FILE NOT FOUND: "); cout << filename.c_str() << endl;
	error=1;
  }

  ifile.close();
      
}
  
