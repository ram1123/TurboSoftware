#include "../Utilities/ColoredMessages.hpp"
#include "LoaderDetectorConf.hpp"

//constructor with filename
LoaderDetectorConf::LoaderDetectorConf(string filename)
  : det_NumberOfDetectors(0), det_Id(0), det_Name(0), det_ReadoutType(0), det_xOffset(0), det_yOffset(0), det_zOffset(0), det_xFlip(0), det_yFlip(0),
    det_TotChannels(0), det_PossibleHits(0), det_MaxDistInCluster(0), det_PeriodicityInCluster(0), det_MaxDistPeriodicityInCluster(0), det_MaxNumOfClusters(0),
    error(0)
{
  ifstream ifile;
  
  ifile.open(filename.c_str());

  string beginningofsettings, head, det_name, col1, col2, col3, col4, col5, col6, col7, col8, col9, col10, col11, col12, col13, col14, endofsettings;

  int i=0;
  int verbose =1;
  int dataverbose =0;

  if ( ifile.is_open() )
    {
	error=0;
  	if (verbose) //cout << "\nOpening the Detectors Configuration File: " << filename << endl;
	{
        //char openingfile[100];
        //sprintf(openingfile, "\nOpening the  Detectors Configuration File: %s", filename.c_str());
        //GreenOut(openingfile);
	GreenOut("\nOpening the  Detectors Configuration File: "); cout << filename.c_str() << endl;
	}
      	while(ifile.good())
	{
		if (i==0) 
		{	
			ifile >> beginningofsettings  >> head >> det_NumberOfDetectors;
			if (verbose) cout << "Number of Loaded Detectors: " << det_NumberOfDetectors << endl;
			det_Id					= new int[det_NumberOfDetectors];    
                        det_Name                            	= new string[det_NumberOfDetectors]; 
                        det_ReadoutType                     	= new int[det_NumberOfDetectors];    
                        det_xOffset                         	= new double[det_NumberOfDetectors]; 
                        det_yOffset                         	= new double[det_NumberOfDetectors]; 
                        det_zOffset                         	= new double[det_NumberOfDetectors]; 
                        det_xFlip                           	= new double[det_NumberOfDetectors]; 
                        det_yFlip                           	= new double[det_NumberOfDetectors]; 
                        det_TotChannels                     	= new int[det_NumberOfDetectors];    
                        det_PossibleHits                    	= new int[det_NumberOfDetectors];    
                        det_MaxDistInCluster                	= new int[det_NumberOfDetectors];    
                        det_PeriodicityInCluster            	= new int[det_NumberOfDetectors];    
                        det_MaxDistPeriodicityInCluster     	= new int[det_NumberOfDetectors];    
                        det_MaxNumOfClusters                	= new int[det_NumberOfDetectors];    

	  		ifile >> col1 >> col2 >> col3 >> col4 >> col5 >> col6 >> col7 >> col8 >> col9 >> col10 >> col11 >> col12 >> col13 >> col14;
			if (dataverbose) 
			{	
				cout << "Loading: " << col1 << ", " << col2 << ", " << col3 << ", " << col4 << ", " << col5 << ", " << col6
				<< col7 << ", " << col8 << ", " << col9 << ", " << col10 << ", " << col11 << ", " << col12 << ", " << col13 << ", " << col14 << endl; 
			}
		}
	  	ifile 	>>  det_Id[i]			 
			>>  det_Name[i]                       
			>>  det_ReadoutType[i]                
			>>  det_xOffset[i]                    
			>>  det_yOffset[i]                    
			>>  det_zOffset[i]                    
			>>  det_xFlip[i]                      
			>>  det_yFlip[i]                      
			>>  det_TotChannels[i]                
			>>  det_PossibleHits[i]               
			>>  det_MaxDistInCluster[i]           
			>>  det_PeriodicityInCluster[i]       
			>>  det_MaxDistPeriodicityInCluster[i]
			>>  det_MaxNumOfClusters[i];           
		if (i==det_NumberOfDetectors-1)
		{
		ifile   >>  endofsettings;	
		}
	  	if (dataverbose && i<det_NumberOfDetectors)
	 	{	
	  		cout 
				<< "ID: " 	<<  det_Id[i]			 
				<< "\t"		<<  det_Name[i]                       
				<< "\t"		<<  det_ReadoutType[i]                
				<< "\t"		<<  det_xOffset[i]                    
				<< "\t"		<<  det_yOffset[i]                    
				<< "\t"		<<  det_zOffset[i]                    
				<< "\t" 	<<  det_xFlip[i]                      
				<< "\t"		<<  det_yFlip[i]                      
                                << "\t"		<<  det_TotChannels[i]                
                                << "\t"		<<  det_PossibleHits[i]               
                                << "\t"		<<  det_MaxDistInCluster[i]           
                                << "\t" 	<<  det_PeriodicityInCluster[i]       
				<< "\t"		<<  det_MaxDistPeriodicityInCluster[i]
                                << "\t"		<<  det_MaxNumOfClusters[i]          
				<< endl; 
	  	}                
	  	i++;            
	}
	if (dataverbose) cout << "Header: " << beginningofsettings << "	Footer: " << endofsettings << endl;
    	//if (verbose) cout << "Configuration File " << filename << " has been read" << endl;
    	if (i!=det_NumberOfDetectors+1)
    	{
	    	//cout << "ERROR[Detector Configuration File]: The number of loaded paramenter is DIFFERENT from the numbers of detectors\n" << endl; 
	    	RedErrorOut("ERROR[Detector Configuration File]: The number of loaded paramenter is DIFFERENT from the numbers of detectors\n");
	    	error=1;
    	}
    	if (beginningofsettings!="BEGINNINGOFSETTINGS" || endofsettings!="ENDOFSETTINGS")
	{
	    	//cout << "ERROR[Detector Configuration File]: BEGINNING and END of settings NOT FOUND\n" << endl; 
	    	RedErrorOut("ERROR[Detector Configuration File]: BEGINNING and END of settings NOT FOUND\n");
	    	error=1;
	}			
    }
    else 
    {
    	//cout << "ERROR[Detector Configuration File]: DETECTOR CONFIGURATION FILE "<< filename << " NOT FOUND\n" << endl;
        //char notfounderror[100];
        //sprintf(notfounderror, "ERROR[Detector Configuration File]: DETECTOR CONFIGURATION FILE %s NOT FOUND\n", filename.c_str());
        //RedErrorOut(notfounderror);
	RedErrorOut("ERROR[Detector Configuration File]: FILE NOT FOUND: "); cout << filename.c_str() << endl;
	error=1;
    }
  ifile.close();
}
  
