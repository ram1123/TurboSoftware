
#ifndef __Detector__
#define __Detector__

/////////////////////////////////////////////////////////////
//
// class Detector
//
/////////////////////////////////////////////////////////////

#include "TObject.h"
#include "TString.h"

class Detector 
  : public TObject 
{

public:

	TString	DetectorName			;
	int	ReadoutType			;
	float	OffsetHorizontal		;
	float	OffsetVertical			;
	float	OffsetZ				;
	int	FlipHorizontal			;
	int	FlipVertical			;
	int	TotChannels			;
	int	PossibleHits			;
	double	MaxDistInCluster		;
	int	PeriodicityInCluster		;
	double	MaxDistPeriodicityInCluster	;
	int	MaxNumOfClusters		;

public:
  	//Default constructor for I/O
   	Detector() :TObject()			, 
		DetectorName("")		, 
		ReadoutType(0)			,
		OffsetHorizontal(0)		,
		OffsetVertical(0)		,
		OffsetZ(0)			,
		FlipHorizontal(1)		,
		FlipVertical(1)			,
		TotChannels(0)			,	
                PossibleHits(0)			,	
                MaxDistInCluster(0)		,	
                PeriodicityInCluster(0)		,	
                MaxDistPeriodicityInCluster(0)	,		
                MaxNumOfClusters(0)			
		{};		

  	//Explicit Constructors 
	explicit Detector(TString	DetName,		   
                       int	RType,		   
                       float	OffH,		   
                       float	OffV,		   
                       float	OffZ,		   
                       int	FlipH,		   
                       int	FlipV,		   
                       int	TotChs,		   
                       int	PossHits,		   
                       double	MaxDistInCl,	   
                       int	PerInCl,	   
                       double	MaxDistPerInCl, 
                       int	MaxNumOfCl 
                	);
		
   	virtual	~Detector() {};

   ClassDef(Detector,1);  //
};

#endif






#ifndef __VFAT2__
#define __VFAT2__

/////////////////////////////////////////////////////////////
//
// class VFAT2
//
/////////////////////////////////////////////////////////////

#include "TObject.h"
#include "TString.h"

class VFAT2 
  : public TObject 
{

public:

	unsigned short 	ChipId		;
	int		Channels	;
	int		DetectorId	;
	TString		DetectorName	;
	TString		DetectorSector	;
	bool		ChipInvert	;
	int		ChipOffset	;
	int			TurboId		;
	int			SlotId		;

public:
  	//Default constructor for I/O
   	VFAT2() :TObject()		, 
		ChipId()		, 
		Channels(128)		,	
                DetectorId(0)		,	
                DetectorName("")	,	
                DetectorSector("")	,	
                ChipInvert(0)		,	
                ChipOffset(0)		,	
                TurboId(0)		,		
                SlotId(0)		
		{};		

  	//Explicit Constructors 
	explicit VFAT2( unsigned short 	ChId,
                	int     		Chs,
                	int     		DetId,
                	TString   	DetName,
                	TString   	DetSec,
                	bool     		ChInv,
                	int     		ChOff,
                	int     		TId,
                	int     		SId);
		
   	virtual	~VFAT2() {};

   ClassDef(VFAT2,1);  //
};
#endif
