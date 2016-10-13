#ifndef DataArray_T_hpp
#define DataArray_T_hpp

//#include "DataArray_T.hpp"

/////////////////////////////////////////////////////////////
//
// class GeoDataArray
//
/////////////////////////////////////////////////////////////

//templace <typename T, Int_t maxelements>
//#include <limits>

//With respect to Test0, now I derive GeoCluster also from GeoDataArray
//instead of embedding GeoDataArray as member object.
//So I give up with trying to avoid a virtual function table in
//GeoDataArray, and rather I make the distructor virtual.
//Still I try to not derive GeoDataArray from TObject

#include "TObject.h"

class GeoDataArray 
  : public TObject 
{

public:
  typedef Int_t geochtype;
  typedef Float_t geotype;
  typedef bool valgeotype;
  enum opgeoresult 
    { operror = -1, noop = 0, 
      maxop  = 1000000000 /*numeric_limits<int>::max()*/ };


public: //private?
  Int_t ngeoallocated; //!

public:
  Int_t ngeoch;
  geochtype *geoch; //[ngeoch]
  geotype *geoX; //[ngeoch]
  geotype *geoY; //[ngeoch]
  geotype *geoZ; //[ngeoch]
  geotype *geoR; //[ngeoch]
  geotype *geoPhi; //[ngeoch]

public:
  //Default constructor for I/O
  GeoDataArray() : TObject(), ngeoallocated(0), ngeoch(0), geoch(0), geoX(0), geoY(0), geoZ(0), geoR(0), geoPhi(0)
  {
    //std::cout << "Standard constructor. Object at " 
    //      << static_cast<void*>(this) << std::endl; 
  };

  //Constructors with number of elements to allocate or inizializers
  explicit GeoDataArray(const Int_t maxNumOfChannels); 

  //Copy constructor
  GeoDataArray(const GeoDataArray& original);

  virtual ~GeoDataArray() { 
	if(geoch) 	delete [] geoch; 
	if(geoX)	delete [] geoX; 
	if(geoY)	delete [] geoY; 
	if(geoZ)	delete [] geoZ; 
	if(geoR)	delete [] geoR; 
	if(geoPhi)	delete [] geoPhi;
	};
  //~GeoDataArray() { if(geoch) delete [] geoch; };

  virtual void Clear(const Option_t* option="")
	{
	TObject::Clear(option);
        if(geoch) 	delete [] geoch; geoch      =0; //--- THIS WAS EXTREMELY IMPORTANT TO 
        if(geoX)	delete [] geoX;  geoX       =0; //--- AVOID MEMORY LEAK
        if(geoY)	delete [] geoY;  geoY       =0; //--- BOIA DEH!
        if(geoZ)	delete [] geoZ;  geoZ       =0;
        if(geoR)	delete [] geoR;  geoR       =0;
        if(geoPhi)	delete [] geoPhi;geoPhi     =0;
        ngeoch = 0;
	}


  //Resize (old contents are lost!)
  virtual Int_t Reallocate(const Int_t maxNumOfChannels);

  //Getters
  valgeotype Get(geochtype geochannel);

  
  //Modify contents
  virtual Int_t InsertChannel(Int_t ReadoutType, Float_t OffsetHorizontal, Float_t OffsetVertical, Int_t FlipHorizontal, Int_t FlipVertical, geochtype geochannel);
  //TODO: Int_t RemoveChannel(geochtype geochannel);
  virtual void RemoveAllChannels() 
	{ 
	ngeoch = 0; 
	};


  //  Int_t Sum();

  //ROOT macro for persistence support
  //  ClassDefNV(GeoDataArray,1)    //GeoDataArray
  ClassDef(GeoDataArray,1)    //GeoDataArray
    ;
};



/*
//#ifdef __CINT__

#if defined(__CINT__)
#pragma link C++ class GeoDataArray;
#endif
*/


/*
/////////////////////////////////////////////////////////////
//
// class Hit
//
/////////////////////////////////////////////////////////////


#include "TClonesArray.h"
#include "TRefArray.h"
#include "TVector3.h"

class Hit : public TObject {

public:
   Int_t      	fgeoch;          //geoch of hit
   Float_t      fX;           //X of hit
   Float_t      fY;           //Y of hit
   Float_t      fZ;           //Z of hit
   Float_t      fR;           //R of hit
   Float_t      fPhi;         //Phi of hit

public:
   Hit(): fgeoch(), fX(), fY(), fZ(), fR(), fPhi() { }
   virtual ~Hit() { }

   ClassDef(Hit,1)  //An hit
};
*/

/*
/////////////////////////////////////////////////////////////
//
// class GeoGeoDataArray
//
/////////////////////////////////////////////////////////////


#include "TClonesArray.h"
#include "TRefArray.h"
#include "TVector3.h"

class Hit : public TObject {

public:
   Int_t      	fgeoch;          //geoch of hit
   Float_t      fX;           //X of hit
   Float_t      fY;           //Y of hit
   Float_t      fZ;           //Z of hit
   Float_t      fR;           //R of hit
   Float_t      fPhi;         //Phi of hit

public:
   Hit(): fgeoch(), fX(), fY(), fZ(), fR(), fPhi() { }
   virtual ~Hit() { }

   ClassDef(Hit,1)  //An hit
};


class GeoGeoDataArray : public TObject 
{

public:
   Int_t 		ngeoalloc; 
public: 
   Int_t        	fNhit;        	//Number of hist in detector 
   Hit* 	fHits;        	//->array of hits in detector 

public:
   GeoGeoDataArray() : TObject(), ngeoalloc(0), fNhit(0), fHits(0) {}
  
  //explicit constructor
   explicit 	 GeoGeoDataArray(const Int_t maxNumOfHits);  
   virtual 	 ~GeoGeoDataArray(){ if(fHits) delete [] fHits; fNhit=0;}
  //Add hit
   Int_t           AddHit(Int_t geoch);
  //Copy constructor
  	 	 GeoGeoDataArray(const GeoGeoDataArray& original);
  //Remove Hits
  Int_t            RemoveAllHits(const Int_t maxNumOfHits);

   ClassDef(GeoGeoDataArray,1);  //Event structure
};
*/



//////////////////////////////////////////////////////////////
//
// class GeoCluster, derived from TObject and GeoDataArray
//
////////////////////////////////////////////////////////////

class GeoCluster : public GeoDataArray
{

public:
  //  GeoDataArray* hits; //I cannot specify "->" for the moment, I'm not yet
		   //sure if I'll be able to have a valid pointer all
		   //the time..

  Float_t geoposch;
  Float_t geoposX;
  Float_t geoposY;
  Float_t geoposZ;
  Float_t geoposR;
  Float_t geoposPhi;
    
public:
  //Standard constructor for I/O
  GeoCluster() : GeoDataArray(), geoposch(0), geoposX(0), geoposY(0), geoposZ(0), geoposR(0), geoposPhi(0)  { };

  explicit GeoCluster(const Int_t maxNumOfChannels)
    : GeoDataArray(maxNumOfChannels), geoposch(0), geoposX(0), geoposY(0), geoposZ(0), geoposR(0), geoposPhi(0)
  {
  }

  //Copy constructor
  GeoCluster(const GeoCluster& original)
    : GeoDataArray(original)
    , geoposch(original.geoposch) 
    , geoposX(original.geoposX) 
    , geoposY(original.geoposY) 
    , geoposZ(original.geoposZ) 
    , geoposR(original.geoposR) 
    , geoposPhi(original.geoposPhi) 
  { 
  }

  //Destructor
  virtual ~GeoCluster(){   
        };


  virtual double AsDouble() { return geoposch; }

  virtual Int_t InsertChannel(Int_t ReadoutType, Float_t OffsetHorizontal, Float_t OffsetVertical, Int_t FlipHorizontal, Int_t FlipVertical, geochtype geochannel);

  //Clear contents 
  virtual void Clear(const Option_t* option="")
  { 
    GeoDataArray::Clear(option); 
    geoposch = 0;
    geoposX = 0;
    geoposY = 0;
    geoposZ = 0;
    geoposR = 0;
    geoposPhi = 0;
  }

  //Clear contents 
  virtual void RemoveAllChannels()
  { 
    GeoDataArray::RemoveAllChannels(); 
    geoposch = 0;
    geoposX = 0;
    geoposY = 0;
    geoposZ = 0;
    geoposR = 0;
    geoposPhi = 0;
  }

  // TO DO: explicit void ResizeMaxHits(const Int_t maxNumOfChannels);

  //Recalculate Pos
  Int_t UpdatePos()
  {
    if ( !(ngeoch && geoch) )
      return operror;
      
    geoposch = 0;
    geoposX = 0;
    geoposY = 0;
    geoposZ = 0;
    geoposR = 0;
    geoposPhi = 0;
    for (Int_t i=0; i<ngeoch; i++)
	{
      	geoposch += geoch[i];
      	geoposX += geoX[i];
      	geoposY += geoY[i];
      	geoposZ += geoZ[i];
      	geoposR += geoR[i];
      	geoposPhi += geoPhi[i];
	}
    	geoposch /= ngeoch;
    	geoposX /= ngeoch;
    	geoposY /= ngeoch;
    	geoposZ /= ngeoch;
    	geoposR /= ngeoch;
    	geoposPhi /= ngeoch;
    return 1;
  }




//  Int_t Find(const GeoDataArray& inputhits, 
//	   GeoDataArray& lefthits,
//   	   const double hitsmaxdist);
  
  ClassDef(GeoCluster,1)   //GeoCluster
    ;
};




// With FindGeoCluster we define the max distance between two hits and
// the periodicity of the readout. For particular readout close
// geochannels could have "not close" geochannels. One example is a Pads
// readout. 
Int_t FindGeoCluster(Int_t ReadoutType, 
		Float_t OffsetHorizontal, 
		Float_t OffsetVertical,
		Int_t FlipHorizontal, 
		Int_t FlipVertical,
		const double hitsmaxdist, 
		const Int_t periodicity,
		const double periodicitymaxdist, 
		const GeoDataArray& inputhits, 
		bool* alreadyused,
		GeoCluster& result); 


//////////////////////////////////////////////////////////
////
//// Class Track derived from TObject //////////////////////
///////////////////////////////////////////////////////////
//
//
// class Track
//     : private TObject
//       {
//
//       public:
//         Double32_t m;
//         Double32_t q;
//         Double32_t chi2;
//         Double32_t ndf;
//
//
//
////Default constructor
//         Track (Double32_t m = 0, Double32_t q = 1,
//         Double32_t chisquare = 0, Double32_t ndf = 0);
////Copy constructor
//         Track (const Track& original);
//
//Destructor
//         virtual ~Track() {};
//
////all other methods
//         double GetXatZ(double z) { return m*z + q; };
//
//         ClassDef(Track,1)    //Track class ROOT macro for persistence
//                                           //support
//        };
#endif
