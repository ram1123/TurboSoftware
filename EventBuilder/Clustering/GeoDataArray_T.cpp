#include <iostream>
#include <fstream>
#include "TSystem.h"
#include "TString.h"
#include "TMath.h"
//#include "DataArray_T.hpp"
#include "GeoDataArray_T.hpp"
#include "./../Mapping/ReadoutType.hpp"
#include "./../Mapping/TotemT2.hpp"
#include "./../Mapping/TotemT1LG.hpp"

//ClassImp(Hit)
//ClassImp(DataArray)
ClassImp(GeoDataArray)
ClassImp(GeoCluster)


/////////////////////////////////////////////////////////////
//
// class GeoDataArray
//
/////////////////////////////////////////////////////////////


//Constructor with number of elements to allocate
GeoDataArray::GeoDataArray(const Int_t maxNumOfChannels) 
  : TObject(), ngeoallocated(0), ngeoch(0), geoch(0), geoX(0), geoY(0), geoZ(0), geoR(0), geoPhi(0)
{ 
  if (maxNumOfChannels > 0) 
    {
      geoch = new geochtype[maxNumOfChannels];
      geoX = new geotype[maxNumOfChannels];
      geoY = new geotype[maxNumOfChannels];
      geoZ = new geotype[maxNumOfChannels];
      geoR = new geotype[maxNumOfChannels];
      geoPhi = new geotype[maxNumOfChannels];
      ngeoallocated = maxNumOfChannels;
      //std::cout << "New object with " << ngeoallocated 
      //	<< " elements. Object at " 
      //	<< static_cast<void*>(this) << std::endl; 
    };
}

//Copy constructor
GeoDataArray::GeoDataArray(const GeoDataArray& original)
  : TObject(), ngeoallocated(original.ngeoallocated)
  , ngeoch(original.ngeoch), geoch(0), geoX(0), geoY(0), geoZ(0), geoR(0), geoPhi(0)
{
  if (ngeoallocated > ngeoch)
    {
      geoch = new geochtype[ngeoallocated];
      geoX = new geotype[ngeoallocated];
      geoY = new geotype[ngeoallocated];
      geoZ = new geotype[ngeoallocated];
      geoR = new geotype[ngeoallocated];
      geoPhi = new geotype[ngeoallocated];
      for (Int_t i = 0; i < ngeoch; i++){
	geoch[i] = original.geoch[i];
	geoX[i] = original.geoX[i];
	geoY[i] = original.geoY[i];
	geoZ[i] = original.geoZ[i];
	geoR[i] = original.geoR[i];
	geoPhi[i] = original.geoPhi[i];
	}
    }
  else
    {
      geoch = new geochtype[ngeoch];
      geoX = new geotype[ngeoch];
      geoY = new geotype[ngeoch];
      geoZ = new geotype[ngeoch];
      geoR = new geotype[ngeoch];
      geoPhi = new geotype[ngeoch];
      for (Int_t i = 0; i < ngeoch; i++){
	geoch[i] = original.geoch[i];
	geoX[i] = original.geoX[i];
	geoY[i] = original.geoY[i];
	geoZ[i] = original.geoZ[i];
	geoR[i] = original.geoR[i];
	geoPhi[i] = original.geoPhi[i];
	}
    }
}
	
//Resize (old contents are lost!)
Int_t GeoDataArray::Reallocate(const Int_t maxNumOfChannels)
{
  if (maxNumOfChannels <= 0) return noop;
  if (geoch) {delete [] geoch; delete [] geoX; delete [] geoY; delete [] geoZ; delete [] geoR; delete [] geoPhi;}
  geoch = new geochtype[maxNumOfChannels];
  geoX = new geotype[maxNumOfChannels];
  geoY = new geotype[maxNumOfChannels];
  geoZ = new geotype[maxNumOfChannels];
  geoR = new geotype[maxNumOfChannels];
  geoPhi = new geotype[maxNumOfChannels];
  ngeoallocated = maxNumOfChannels;
  ngeoch = 0;
  return 1;
}

GeoDataArray::valgeotype GeoDataArray::Get(GeoDataArray::geochtype geochannel)
{ 
  for (Int_t i=0; i<ngeoch; i++)
    if (geoch[i]==geochannel) return 1;
  return 0;
};


Int_t GeoDataArray::InsertChannel(Int_t RType, Float_t OffsetH, Float_t OffsetV, Int_t FlipH, Int_t FlipV, GeoDataArray::geochtype geochannel)
{ 
  if (ngeoch >= ngeoallocated)
    {
      //std::cout << "Inside IF ngeoch = " << ngeoch << " ngeoallocated = " << ngeoallocated << std::endl;
      std::cerr << "\nERROR: Read-only object or max number of geochannels\n" << std::endl;
      return operror;
    }

  //std::cout << "ngeoch = " << ngeoch << " ngeoallocated = " << ngeoallocated << std::endl;

  Int_t place = 0;
  for ( ; place<ngeoch; place++)
  if (geoch[place]==geochannel) return noop;

// ReadoutType
// 0:   X Strips with 400um pitch
// 1:   Y Strips with 400um pitch
// 2:   X Strips with 800um pitch
// 3:   Y Strips with 800um pitch
// 4:   Totem T2 Strips
// 5:   Totem T2 Pads
// 6:   Totem T1 LG
// 8:   CMS NS2 Pitch 0.8
// 9:   CMS GE1/1

  //  std::cout << "Inserting geochannel " << geochannel
  //	    << " in the slot " << place; 
  geoch[place] = geochannel;


        if (RType == 0)
	{
  		geoX[place] 	= FlipH*GetX(RType,geochannel)+OffsetH;
  		geoY[place] 	= 999;//GetY(RType,geochannel); 
  		geoZ[place] 	= 999;//GetZ(RType,geochannel); 
  		geoR[place] 	= 999;//GetR(RType,geochannel); 
  		geoPhi[place] 	= 999;//GetPhi(RType,geochannel); 
	} 
        else if (RType == 1)
	{
  		geoX[place] 	= 999;//GetX(RType,geochannel);
  		geoY[place] 	= FlipV*GetY(RType,geochannel)+OffsetV; 
  		geoZ[place] 	= 999;//GetZ(RType,geochannel); 
  		geoR[place] 	= 999;//GetR(RType,geochannel); 
  		geoPhi[place] 	= 999;//GetPhi(RType,geochannel); 
	} 
        else if (RType == 2)
	{
  		geoX[place] 	= FlipH*GetX(RType,geochannel)+OffsetH;
  		geoY[place] 	= 999;//GetY(RType,geochannel); 
  		geoZ[place] 	= 999;//GetZ(RType,geochannel); 
  		geoR[place] 	= 999;//GetR(RType,geochannel); 
  		geoPhi[place] 	= 999;//GetPhi(RType,geochannel); 
	} 
        else if (RType == 3)
	{
  		geoX[place] 	= 999;//GetX(RType,geochannel);
  		geoY[place] 	= FlipV*GetY(RType,geochannel)+OffsetV; 
  		geoZ[place] 	= 999;//GetZ(RType,geochannel); 
  		geoR[place] 	= 999;//GetR(RType,geochannel); 
  		geoPhi[place] 	= 999;//GetPhi(RType,geochannel); 
	} 
        else if (RType == 4)
	{
  		geoX[place] 	= 999; //GetX(RType,geochannel);
  		geoY[place] 	= 999; //GetY(RType,geochannel); 
  		geoZ[place] 	= 999; //GetZ(RType,geochannel); 
  		geoR[place] 	= GetR(RType,geochannel); 
  		geoPhi[place] 	= 999; //GetPhi(RType,geochannel); 
	} 
        else if (RType == 5)
	{
  		geoX[place] 	= FlipH*GetX(RType,geochannel)+OffsetH;
  		geoY[place] 	= FlipV*GetY(RType,geochannel)+OffsetV; 
  		geoZ[place] 	= 999; //GetZ(RType,geochannel); 
  		geoR[place] 	= GetR(RType,geochannel);
		if 	(FlipH==1 	&& FlipV==1  ){geoPhi[place] = GetPhi(RType,geochannel);}
		else if (FlipH==-1 	&& FlipV==1  ){geoPhi[place] =TMath::DegToRad()*180.-GetPhi(RType,geochannel);}
		else if (FlipH==1 	&& FlipV==-1 ){geoPhi[place] =TMath::DegToRad()*360.-GetPhi(RType,geochannel);}
		else if (FlipH==-1 	&& FlipV==-1 ){geoPhi[place] =TMath::DegToRad()*180.+GetPhi(RType,geochannel);}
		else {geoPhi[place] = 999;}
	} 
        else if (RType == 6)
	{
  		geoX[place] 	= FlipH*GetX(RType,geochannel)+OffsetH;
  		geoY[place] 	= FlipV*GetY(RType,geochannel)+OffsetV; 
  		geoZ[place] 	= 999; //GetZ(RType,geochannel); 
  		geoR[place] 	= GetR(RType,geochannel); 
  		geoPhi[place] 	= 999; //GetPhi(RType,geochannel); 
	} 
	        else if (RType == 8)
        {
                geoX[place]     = FlipH*GetX(RType,geochannel)+OffsetH;
                geoY[place]     = 999;//GetY(RType,geochannel); 
                geoZ[place]     = 999;//GetZ(RType,geochannel); 
                geoR[place]     = 999;//GetR(RType,geochannel); 
                geoPhi[place]   = 999;//GetPhi(RType,geochannel); 
        }

                else if (RType == 9)
        {
                geoX[place]     = 999;//FlipH*GetX(RType,geochannel)+OffsetH;
                geoY[place]     = FlipV*GetY(RType,geochannel)+OffsetV;
                geoZ[place]     = 999;//GetZ(RType,geochannel);
                geoR[place]     = 999;//GetR(RType,geochannel);
                geoPhi[place]   = 999;//GetPhi(RType,geochannel);
        }


        else {cout <<  "Wrong Map Type in the Inserting Channel Call"; return 999;}

  //geoX[place] = geochannel*0.4;
  //geoY[place] = geochannel*0.4;
  //geoZ[place] = geochannel*10;
  //geoR[place] = TMath::Sqrt( TMath::Power(geoX[place],2) + TMath::Power(geoY[place],2) );
  //geoPhi[place] = TMath::RadToDeg()*TMath::ATan(geoY[place]/geoX[place]);
  ngeoch++;
  //  std::cout << "\nNow ngeoch is " << ngeoch << std::endl;

  return 1;
};




//Int_t GeoDataArray::Sum()
//{ 
//  Int_t sum = 0;
//  for (Int_t i=0 ; i<nval; i++)
//    sum += val[i];
//
//  return sum; 
//};


#define mygeodistance(x,y) ( (x<y)? (y-x) : (x-y) )




////////////////////////////////////////////////////////////
//
// class GeoCluster, derived from TObject and GeoDataArray
//
////////////////////////////////////////////////////////////
Int_t GeoCluster::InsertChannel(Int_t ReadoutType, Float_t OffsetHorizontal, Float_t OffsetVertical, Int_t FlipHorizontal, Int_t FlipVertical, geochtype geochannel)
{
  Int_t oldngeoch = ngeoch;
  Float_t oldgeoposch = geoposch;
  Float_t oldgeoposX = geoposX;
  Float_t oldgeoposY = geoposY;
  Float_t oldgeoposZ = geoposZ;
  Float_t oldgeoposR = geoposR;
  Float_t oldgeoposPhi = geoposPhi;
  Int_t moregeoch = GeoDataArray::InsertChannel(ReadoutType, OffsetHorizontal, OffsetVertical, FlipHorizontal, FlipVertical, geochannel);
  if (moregeoch == 1)
//    {
//	if ((mygeodistance(mygeodistance(geopos, geochannel), 24)<1) && oldngeoch > 0) 
//	{ 
//	cout << "mygeodistance(geopos, geochannel)>=20. Pos: " << geopos <<";  Channel: "<< geochannel <<";  Diff: " <<mygeodistance(geopos, geochannel) << endl;
//	geopos = geopos;
//	}
//	else geopos = ( geopos*oldngeoch + geochannel ) / ngeoch;
	geoposch 	= ( oldgeoposch*oldngeoch + geoch[ngeoch-1] ) / ngeoch;
	geoposX 	= ( oldgeoposX*oldngeoch + geoX[ngeoch-1] ) / ngeoch;
	geoposY 	= ( oldgeoposY*oldngeoch + geoY[ngeoch-1]) / ngeoch;
	geoposZ 	= ( oldgeoposZ*oldngeoch + geoZ[ngeoch-1]) / ngeoch;
	geoposR 	= ( oldgeoposR*oldngeoch + geoR[ngeoch-1] ) / ngeoch;
	geoposPhi 	= ( oldgeoposPhi*oldngeoch + geoPhi[ngeoch-1] ) / ngeoch;
//    }
  return moregeoch;
	
}





//    Int_t GeoCluster::Find(const GeoDataArray& inputhits,
//          		  GeoDataArray& lefthits,
//          		  const double hitsmaxdist)
//    {
//      Int_t arraysize = inputhits.ngeoch;
//      bool* alreadyused = new bool[arraysize];
//      FindGeoCluster(hitsmaxdist, inputhits,
//    	      alreadyused, *this);
//      UpdatePos();
//      
//      //Now geocheck the remaining hits; 
//      if (lefthits.ngeoallocated < arraysize)
//        {
//          lefthits.Reallocate(arraysize);
//        }
//      else lefthits.ngeoch = 0;
//      
//      Int_t nleft = 0;
//      for (Int_t i = 0; i < arraysize; i++)
//        {
//          if (alreadyused[i]) continue;
//          lefthits.InsertChannel(inputhits.geoch[i]);
//          nleft++;
//        }
//      
//      delete [] alreadyused;
//      
//      return nleft;
//    }





Int_t FindGeoCluster(Int_t RType,
		Float_t OffH,
		Float_t OffV, 
		Int_t FlipH,
		Int_t FlipV, 
		const double hitsmaxdist,
		const Int_t periodicity,
		const double periodicitymaxdist,
		const GeoDataArray& inputhits, 
		bool* alreadyused,
		GeoCluster& result)
  //FIXINGS TO BE DONE: result should be large enough.. not
  //geochecked for the moment.. similar problem for alreadyused
{

  if (inputhits.ngeoch <= 0)
    {
      //      std::cout << "FindGeoCluster: No hits in input GeoDataArray" 
      //		<< std::endl;
      return 0;
    }



  //  if (!alreadyused)    //WE DECIDED THAT THE USER MUST ALLOCATE IT!
  //    {
  //      alreadyused = new bool[inputhits.nch];
  //      for (Int_t i=0; i<inputhits.nch; i++)
  //	alreadyused[i] = false;
  //    }


  Int_t moregeochannels = 0;

  //  //if not existing, create //WE DECIDED THAT THE USER MUST ALLOCATE IT!
  //  if (!result) result = new GeoDataArray(inputhits.nch);

  //if empty, insert the first unused geochannel
  if (result.ngeoch == 0)
    {
      for (Int_t i=0; i<inputhits.ngeoch; i++)
	{
	  if(alreadyused[i]) continue;
	  
	  result.InsertChannel(RType, OffH, OffV,FlipH, FlipV, inputhits.geoch[i]);
	  alreadyused[i] = true;
	  moregeochannels++;
	  break;
	}

      if (moregeochannels < 1) return 0; //go out if you cannot find even
				      //a first geochannel
    }

  //add more geochannels, the ones close enough to the geochannels already selected
  for (Int_t i = 0; i < inputhits.ngeoch; i++)
    {
      if (alreadyused[i]) continue;

      for (Int_t j = 0; j < result.ngeoch; j++)
	{
	if ( mygeodistance(inputhits.geoch[i], result.geoch[j]) < hitsmaxdist )
	  {
//	cout << "mygeodistance(inputhits.geoch[i], result.geoch[j]) < hitsmaxdist" << inputhits.geoch[i] << ","<< result.geoch[j] << endl;
	    result.InsertChannel(RType, OffH, OffV, FlipH, FlipV, inputhits.geoch[i]);
	    alreadyused[i] = true;
	    moregeochannels++;
	    break;
	  }
	else if ( (inputhits.geoch[i]+periodicity == result.geoch[j]) )
	//else if ( mygeodistance(inputhits.geoch[i]+periodicity, result.geoch[j]) < periodicitymaxdist )
	  {
//	cout << "mygeodistance(inputhits.geoch[i]+periodicity, result.geoch[j]) < hitsmaxdist" << inputhits.geoch[i]+periodicity << ","<< result.geoch[j] << endl;
	    result.InsertChannel(RType, OffH, OffV, FlipH, FlipV, inputhits.geoch[i]);
	    alreadyused[i] = true;
	    moregeochannels++;
	    break;
	  }
	else if ( (inputhits.geoch[i]-periodicity == result.geoch[j]) )
	//else if ( mygeodistance(inputhits.geoch[i]-periodicity, result.geoch[j]) < periodicitymaxdist )
	  {
//	cout << "mygeodistance(inputhits.geoch[i]-periodicity, result.geoch[j]) < hitsmaxdist" << inputhits.geoch[i]-periodicity << ","<< result.geoch[j] << endl;
	    result.InsertChannel(RType, OffH, OffV, FlipH, FlipV,inputhits.geoch[i]);
	    alreadyused[i] = true;
	    moregeochannels++;
	    break;
	  }
	else continue;
	}
    }

  if (moregeochannels < 1) return 0;

  return moregeochannels + FindGeoCluster(RType, OffH, OffV, FlipH, FlipV, hitsmaxdist, 
				    periodicity, 
				    periodicitymaxdist,
				    inputhits, 
				    alreadyused,
				    result);

}; 
