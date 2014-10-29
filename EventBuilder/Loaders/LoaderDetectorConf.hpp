///////////////////////////////////////
//
// Class LoaderDetectorConf
//////////////////////////////////////

#include <stdlib.h>
#include "Riostream.h"
#include <iostream>
#include <fstream>
#include <string>

class LoaderDetectorConf
{
 public:

  int		det_NumberOfDetectors; 
  int	 	*det_Id;
  string	*det_Name;
  int		*det_ReadoutType;
  double 	*det_xOffset;
  double 	*det_yOffset;
  double 	*det_zOffset;
  double 	*det_xFlip;
  double 	*det_yFlip;
  int		*det_TotChannels;
  int		*det_PossibleHits;
  int		*det_MaxDistInCluster;
  int		*det_PeriodicityInCluster;
  int		*det_MaxDistPeriodicityInCluster;
  int		*det_MaxNumOfClusters;
  bool		error;
  
  //Std Constructor
  LoaderDetectorConf(): 
    det_NumberOfDetectors(0), det_Id(0), det_Name(0), det_ReadoutType(0), det_xOffset(0), det_yOffset(0), det_zOffset(0), det_xFlip(0), det_yFlip(0),
    det_TotChannels(0), det_PossibleHits(0), det_MaxDistInCluster(0), det_PeriodicityInCluster(0), det_MaxDistPeriodicityInCluster(0), det_MaxNumOfClusters(0),
    error(0)
    {};
  
  //Constructor with filename
  explicit LoaderDetectorConf (string filename);
    
  virtual ~LoaderDetectorConf() {
        if(det_Id)     				delete [] det_Id;
        if(det_Name)     			delete [] det_Name;
        if(det_ReadoutType)     		delete [] det_ReadoutType;
        if(det_xOffset)     			delete [] det_xOffset;
        if(det_yOffset)     			delete [] det_yOffset;
        if(det_zOffset)     			delete [] det_zOffset;
        if(det_xFlip)     			delete [] det_xFlip;
        if(det_yFlip)     			delete [] det_yFlip;
        if(det_TotChannels)     		delete [] det_TotChannels;
        if(det_PossibleHits)     		delete [] det_PossibleHits;
        if(det_MaxDistInCluster)     		delete [] det_MaxDistInCluster;
        if(det_PeriodicityInCluster)     	delete [] det_PeriodicityInCluster;
        if(det_MaxDistPeriodicityInCluster)     delete [] det_MaxDistPeriodicityInCluster;
        if(det_MaxNumOfClusters)     		delete [] det_MaxNumOfClusters;
        };

 
  ClassDef(LoaderDetectorConf,1);
};

  
