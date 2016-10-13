///////////////////////////////////////
//
// Class LoaderSettings_TrackFinder
//////////////////////////////////////

#include <string>
#include <iostream>
#include <fstream>

class LoaderSettings_TrackFinder
{
 public:

  string 	TrackerOffsetFile		;
  int 		TrackFinder_Verbose		;
  int 		TrackFinder_TrackVerbose	;
  int 		TrackFinder_OffsetVerbose	;
  bool		error				;

  //Std Constructor
  LoaderSettings_TrackFinder(): 
	TrackerOffsetFile(""), TrackFinder_Verbose(0), TrackFinder_TrackVerbose(0), TrackFinder_OffsetVerbose(0), error(0)
    {};
  
  //Constructor with filename
  LoaderSettings_TrackFinder (string filename);
    
  virtual ~LoaderSettings_TrackFinder() {};

  ClassDef(LoaderSettings_TrackFinder,1);
};

  
