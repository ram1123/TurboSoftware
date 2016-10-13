///////////////////////////////////////
//
// Class LoaderVFATConf
//////////////////////////////////////

#include <stdlib.h>
#include "Riostream.h"
#include <iostream>
#include <fstream>
#include <string>

class LoaderVFATConf
{
 public:

  int			vfat_NumberOfVFATs; 
  int	 		*vfat_Id;
  unsigned int		*vfat_ChipId;
  int			*vfat_Channels;
  int	 		*vfat_DetectorId;
  string 		*vfat_DetectorName;
  string 		*vfat_DetectorSector;
  bool	 		*vfat_ChipInvert;
  int			*vfat_ChipOffset;
  int			*vfat_TurboId;
  int			*vfat_SlotId;		
  bool			error;

  //Std Constructor
  LoaderVFATConf(): 
    vfat_NumberOfVFATs(0), vfat_Id(0), vfat_ChipId(0), vfat_Channels(0), vfat_DetectorId(0), vfat_DetectorName(0), 
    vfat_DetectorSector(0), vfat_ChipInvert(0), vfat_ChipOffset(0), vfat_TurboId(0), vfat_SlotId(0),
    error(0)	
    {};
  
  //Constructor with filename
  explicit LoaderVFATConf (string filename);
    
  virtual ~LoaderVFATConf() {
        if(vfat_Id)		delete [] vfat_Id		;
        if(vfat_ChipId)		delete [] vfat_ChipId		;
        if(vfat_Channels)	delete [] vfat_Channels		;
        if(vfat_DetectorId)	delete [] vfat_DetectorId	;
        if(vfat_DetectorName)	delete [] vfat_DetectorName	;
        if(vfat_DetectorSector)	delete [] vfat_DetectorSector	;
        if(vfat_ChipInvert)	delete [] vfat_ChipInvert	;
        if(vfat_ChipOffset)	delete [] vfat_ChipOffset	;
        if(vfat_TurboId)	delete [] vfat_TurboId		;
        if(vfat_SlotId)		delete [] vfat_SlotId		;
        };

 
  ClassDef(LoaderVFATConf,1);
};

  
