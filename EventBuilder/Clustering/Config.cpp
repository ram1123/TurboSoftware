#include <iostream>
#include "TObject.h"
#include "TString.h"
#include "Config.hpp"


///////////////////////////////////////////////////////////
//
// class Detector
//
///////////////////////////////////////////////////////////

ClassImp(Detector)

//Explicit Constructors 
        
Detector::Detector(TString    DetName,
                   int        RType,
                   float      OffH, 
                   float      OffV, 
                   float      OffZ, 
                   int        FlipH,
                   int        FlipV,
                   int        TotChs,
                   int        PossHits,
                   double     MaxDistInCl,
                   int        PerInCl,
                   double     MaxDistPerInCl,
                   int        MaxNumOfCl)
		   :	TObject(),
			DetectorName(DetName),               			
                        ReadoutType(RType),
                        OffsetHorizontal(OffH),
                        OffsetVertical(OffV),
                        OffsetZ(OffZ),
                        FlipHorizontal(FlipH),
                        FlipVertical(FlipV),
                        TotChannels(TotChs),
                        PossibleHits(PossHits),
	                MaxDistInCluster(MaxDistInCl),
                        PeriodicityInCluster(PerInCl),
                        MaxDistPeriodicityInCluster(MaxDistPerInCl),
                        MaxNumOfClusters(MaxNumOfCl)
			{}


///////////////////////////////////////////////////////////
//
// class VFAT2
//
///////////////////////////////////////////////////////////

ClassImp(VFAT2)

//Explicit Constructors 
        
VFAT2::VFAT2( unsigned short  ChId,
              int             Chs,
              int             DetId,
              TString         DetName,
              TString         DetSec,
              bool            ChInv,
              int             ChOff,
              int             TId,
              int             SId)
              :       TObject(),
                      ChipId(         ChId    ),
                      Channels(       Chs     ),
                      DetectorId(     DetId   ),
                      DetectorName(   DetName ),
                      DetectorSector( DetSec  ),
                      ChipInvert(     ChInv   ),
                      ChipOffset(     ChOff   ),
                      TurboId(        TId     ),
                      SlotId(         SId     )
                      {}





