#include "../Utilities/ColoredMessages.hpp"
#include "LoaderVFATConf.hpp"

//constructor with filename
LoaderVFATConf::LoaderVFATConf(string filename)
  : vfat_NumberOfVFATs(0), vfat_Id(0), vfat_ChipId(0), vfat_Channels(0), vfat_DetectorId(0), vfat_DetectorName(0),
    vfat_DetectorSector(0), vfat_ChipInvert(0), vfat_ChipOffset(0), vfat_TurboId(0), vfat_SlotId(0),
    error(0)
{

  ifstream ifile;
  
  ifile.open(filename.c_str());

  string beginningofsettings, head, vfat_name, col1, col2, col3, col4, col5, col6, col7, col8, col9, col10, endofsettings;
  char hex_ChipId_Char[6];


  int i=0;
  int verbose =1;
  int dataverbose =0;

  if ( ifile.is_open() )
    {
	error=0;
  	if (verbose) //cout << "\nOpening the VFAT Configuration File: " << filename << endl;
	{
	//char openingfile[100];
        //sprintf(openingfile, "\nOpening the VFAT Configuration File: %s", filename.c_str());
        //GreenOut(openingfile);	
	GreenOut("\nOpening the VFAT Configuration File: "); cout << filename.c_str() << endl;
	}
      	while(ifile.good())
	{
		if (i==0) 
		{	
			ifile >> beginningofsettings >> head >> vfat_NumberOfVFATs;
			if (verbose) cout << "Number of Loaded VFATs: " << vfat_NumberOfVFATs << endl;
                    	vfat_Id			= new int[vfat_NumberOfVFATs];
                    	vfat_ChipId		= new unsigned int[vfat_NumberOfVFATs];
                    	vfat_Channels		= new int[vfat_NumberOfVFATs];
                    	vfat_DetectorId		= new int[vfat_NumberOfVFATs];
                    	vfat_DetectorName	= new string[vfat_NumberOfVFATs];
                    	vfat_DetectorSector	= new string[vfat_NumberOfVFATs];
                    	vfat_ChipInvert		= new bool[vfat_NumberOfVFATs];
                    	vfat_ChipOffset		= new int[vfat_NumberOfVFATs];
                    	vfat_TurboId		= new int[vfat_NumberOfVFATs];
                    	vfat_SlotId		= new int[vfat_NumberOfVFATs];				

	  		ifile >> col1 >> col2 >> col3 >> col4 >> col5 >> col6 >> col7 >> col8 >> col9 >> col10;
			if (dataverbose) 
			{	
				cout << "Loading: " << col1 << ", " << col2 << ", " << col3 << ", " << col4 << ", " << col5 << ", " << col6
				<< col7 << ", " << col8 << ", " << col9 << ", " << col10 << endl; 
			}
		}
	  	ifile 	>>  vfat_Id[i]			 
			>>  hex_ChipId_Char                
			>>  vfat_Channels[i]                
			>>  vfat_DetectorId[i]                    
			>>  vfat_DetectorName[i]                    
			>>  vfat_DetectorSector[i]                      
			>>  vfat_ChipInvert[i]                      
			>>  vfat_ChipOffset[i]                
			>>  vfat_TurboId[i]               
			>>  vfat_SlotId[i];       

   		sscanf(hex_ChipId_Char, "%x", &(vfat_ChipId[i]));

                if (i==vfat_NumberOfVFATs-1)
                {
                ifile   >>  endofsettings;
                }

	  	if (dataverbose && i<vfat_NumberOfVFATs)
	 	{
	  		cout 	<< "ID: " 	<<  vfat_Id[i]		    
				<< "\t"		<<  hex_ChipId_Char               
				<< "\t"		<<  vfat_Channels[i]             
				<< "\t"		<<  vfat_DetectorId[i]           
				<< "\t"		<<  vfat_DetectorName[i]         
				<< "\t" 	<<  vfat_DetectorSector[i]       
				<< "\t"		<<  vfat_ChipInvert[i]           
                                << "\t"		<<  vfat_ChipOffset[i]           
                                << "\t"		<<  vfat_TurboId[i]              
                                << "\t"		<<  vfat_SlotId[i]              
				<< endl; 
	  	}                
	  	i++;            
	}
    //if (verbose) cout << "Configuration File " << filename << " has been read" << endl;
    if (i!=vfat_NumberOfVFATs+1)
    //cout << "ERROR[VFAT Configuration File]: The number of loaded paramenter is DIFFERENT from the numbers of VFATs\n" << endl;
    {RedErrorOut("ERROR[VFAT Configuration File]: The number of loaded paramenter is DIFFERENT from the numbers of VFATs\n");error=1;}
    if (beginningofsettings!="BEGINNINGOFSETTINGS" || endofsettings!="ENDOFSETTINGS")
    //cout << "ERROR[VFAT Configuration File]: BEGINNING and END of settings NOT FOUND\n" << endl;
    {RedErrorOut("ERROR[VFAT Configuration File]: BEGINNING and END of settings NOT FOUND\n");error=1;}
    }
    else 
    {
	//cout << "ERROR[VFAT Configuration File]: VFAT CONFIGURATION FILE "<< filename << " NOT FOUND\n" << endl;
        //char notfounderror[100];
	//sprintf(notfounderror, "ERROR[VFAT Configuration File]: VFAT CONFIGURATION FILE %s NOT FOUND\n", filename.c_str());
	//RedErrorOut(notfounderror);
	RedErrorOut("ERROR[VFAT Configuration File]: VFAT CONFIGURATION FILE NOT FOUND: "); cout << filename.c_str() << endl;
	error=1;
    }
  ifile.close();
}
  
