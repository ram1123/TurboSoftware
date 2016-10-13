///////////////////////////////////////
//
// Class LoaderOffsetAndCoverage_Analyzer
//////////////////////////////////////

#include <string>
#include <iostream>
#include <fstream>


class LoaderOffsetAndCoverage_Analyzer
{
 public:

  int           NumberOfDetectors	;
  int	 	*det_index		;
  double 	*xOffset		;
  double 	*yOffset		;
  double 	*zOffset		;
  double 	*xTrackerOffset		;
  double 	*yTrackerOffset		;
  double 	*xCoverageMin		;
  double 	*xCoverageMax		;
  double 	*yCoverageMin		;
  double 	*yCoverageMax		;
  double 	*RCoverageMin		;
  double 	*RCoverageMax		;
  double 	*PhiCoverageMax		;
  double 	*PhiCoverageMin		;
  double 	*effRad			;
  bool		error;

  //Std Constructor
  LoaderOffsetAndCoverage_Analyzer(): 
    NumberOfDetectors(0), det_index(0), xOffset(0), yOffset(0), zOffset(0),
	xTrackerOffset(0), yTrackerOffset(0),
	xCoverageMin(0), xCoverageMax(0), yCoverageMin(0), yCoverageMax(0),
	RCoverageMin(0), RCoverageMax(0), PhiCoverageMax(0), PhiCoverageMin(0),
	effRad(0),
	error(0)
    {};
  
  //Constructor with filename
  explicit LoaderOffsetAndCoverage_Analyzer (string filename, int loadedDetectors);
    
  virtual ~LoaderOffsetAndCoverage_Analyzer() {
        if(det_index     )     	 delete [] det_index;
        if(xOffset       )       delete [] xOffset;
        if(yOffset       )       delete [] yOffset;
        if(zOffset       )       delete [] zOffset;
        if(xTrackerOffset)       delete [] xTrackerOffset;
        if(yTrackerOffset)       delete [] yTrackerOffset;
        if(xCoverageMin  )       delete [] xCoverageMin  ;
        if(xCoverageMax  )       delete [] xCoverageMax  ;
        if(yCoverageMin  )       delete [] yCoverageMin  ;
        if(yCoverageMax  )       delete [] yCoverageMax  ;
        if(RCoverageMin  )       delete [] RCoverageMin  ;
        if(RCoverageMax  )       delete [] RCoverageMax  ;
        if(PhiCoverageMax)       delete [] PhiCoverageMax;
        if(PhiCoverageMin)       delete [] PhiCoverageMin;
        if(effRad)       	 delete [] effRad;
        };

 
  ClassDef(LoaderOffsetAndCoverage_Analyzer,1);
};

  
