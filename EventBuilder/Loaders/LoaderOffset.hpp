///////////////////////////////////////
//
// Class LoaderOffset
//////////////////////////////////////

#include <string>
#include <iostream>
#include <fstream>


class LoaderOffset
{
 public:

  int           NumberOfDetectors;
  int	 	*det_index;
  double 	*xOffset;
  double 	*yOffset;
  double 	*zOffset;
  bool 		error;
 
  //Std Constructor
  LoaderOffset(): 
    NumberOfDetectors(0), det_index(0), xOffset(0), yOffset(0), zOffset(0), error(0)
    {};
  
  //Constructor with filename
  explicit LoaderOffset (string filename, int loadedDetectors);
    
  virtual ~LoaderOffset() {
        if(det_index)     delete [] det_index;
        if(xOffset)       delete [] xOffset;
        if(yOffset)       delete [] yOffset;
        if(zOffset)       delete [] zOffset;
        };

 
  ClassDef(LoaderOffset,1);
};

  
