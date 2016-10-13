///////////////////////////////////////
//
// Class LoaderOffsetFlipConf
//////////////////////////////////////

#include <string>
#include <iostream>
#include <fstream>


class LoaderOffsetFlipConf
{
 public:

  int		NumberOfDetectors; 
  int	 	*det_index;
  double 	*xOffset;
  double 	*yOffset;
  double 	*zOffset;
  double 	*xFlip;
  double 	*yFlip;
  bool		error;
  
  //Std Constructor
  LoaderOffsetFlipConf(): 
    NumberOfDetectors(0), det_index(0), xOffset(0), yOffset(0), zOffset(0), xFlip(0), yFlip(0), error(0)
    {};
  
  //Constructor with filename
  explicit LoaderOffsetFlipConf (string filename, int loadedDetectors);
    
  virtual ~LoaderOffsetFlipConf() {
        if(det_index)     delete [] det_index;
        if(xOffset)       delete [] xOffset;
        if(yOffset)       delete [] yOffset;
        if(zOffset)       delete [] zOffset;
        if(xFlip)         delete [] xFlip;
        if(yFlip)         delete [] yFlip;
        };

 
  ClassDef(LoaderOffsetFlipConf,1);
};

  
