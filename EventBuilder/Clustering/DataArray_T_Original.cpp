#include <iostream>
#include "TMath.h"
#include "DataArray_T.hpp"

//ClassImp(Hit)
ClassImp(DataArray)
ClassImp(VFATDataArray)
//ClassImp(GeoDataArray)
ClassImp(Cluster)


/////////////////////////////////////////////////////////////
//
// class DataArray
//
/////////////////////////////////////////////////////////////


//Constructor with number of elements to allocate
DataArray::DataArray(const int maxNumOfChannels) 
  : TObject(), nallocated(0), nch(0), ch(0)
{ 
cout<<"in Dataarray cpp 11"<<endl;
  if (maxNumOfChannels > 0) 
    {
cout<<"in Dataarray cpp 22 = "<<maxNumOfChannels<<endl;
      ch = new chtype[maxNumOfChannels];
cout<<"in Dataarray cpp 22 ch = "<<ch<<endl;
      nallocated = maxNumOfChannels;
      std::cout << "New object with " << nallocated 
      	<< " elements. "<<ch<<"\t Object at " 
      	<< (this) << std::endl; 
    };
}

//Copy constructor
DataArray::DataArray(const DataArray& original)
  : TObject(), nallocated(original.nallocated)
  , nch(original.nch), ch(0) 
{
  if (nallocated > nch)
    {
      ch = new chtype[nallocated];
      for (int i = 0; i < nch; i++)
	ch[i] = original.ch[i];
    }
  else
    {
      ch = new chtype[nch];
      for (int i = 0; i < nch; i++)
	ch[i] = original.ch[i];
    }
}
	
//Resize (old contents are lost!)
int DataArray::Reallocate(const int maxNumOfChannels)
{
  if (maxNumOfChannels <= 0) return noop;
  if (ch) delete [] ch;
  ch = new chtype[maxNumOfChannels];
  nallocated = maxNumOfChannels;
  nch = 0;
  return 1;
}

DataArray::valtype DataArray::Get(DataArray::chtype channel)
{ 
  for (int i=0; i<nch; i++)
    if (ch[i]==channel) return 1;
  return 0;
};


int DataArray::InsertChannel(DataArray::chtype channel)
{ 
  if (nch >= nallocated)
    {
      //std::cout << "Inside IF nch = " << nch << " nallocated = " << nallocated << std::endl;
      std::cerr << "\nERROR: Read-only object or max number of channels\n" << std::endl;
      return operror;
    }

  //std::cout << "nch = " << nch << " nallocated = " << nallocated << std::endl;

  int place = 0;
  for ( ; place<nch; place++)
  if (ch[place]==channel) return noop;

  //  std::cout << "Inserting channel " << channel
  //	    << " in the slot " << place; 
  ch[place] = channel;
  nch++;
  //  std::cout << "\nNow nch is " << nch << std::endl;

  return 1;
};




//int DataArray::Sum()
//{ 
//  int sum = 0;
//  for (int i=0 ; i<nval; i++)
//    sum += val[i];
//
//  return sum; 
//};


#define mydistance(x,y) ( (x<y)? (y-x) : (x-y) )


int FindCluster(const double hitsmaxdist,
		const int periodicity,
		const double periodicitymaxdist,
		const DataArray& inputhits, 
		bool* alreadyused,
		DataArray& result)
  //FIXINGS TO BE DONE: result should be large enough.. not
  //checked for the moment.. similar problem for alreadyused
{

  if (inputhits.nch <= 0)
    {
      //      std::cout << "FindCluster: No hits in input DataArray" 
      //		<< std::endl;
      return 0;
    }



  //  if (!alreadyused)    //WE DECIDED THAT THE USER MUST ALLOCATE IT!
  //    {
  //      alreadyused = new bool[inputhits.nch];
  //      for (int i=0; i<inputhits.nch; i++)
  //	alreadyused[i] = false;
  //    }


  int morechannels = 0;

  //  //if not existing, create //WE DECIDED THAT THE USER MUST ALLOCATE IT!
  //  if (!result) result = new DataArray(inputhits.nch);

  //if empty, insert the first unused channel
  if (result.nch == 0)
    {
      for (int i=0; i<inputhits.nch; i++)
	{
	  if(alreadyused[i]) continue;
	  
	  result.InsertChannel(inputhits.ch[i]);
	  alreadyused[i] = true;
	  morechannels++;
	  break;
	}

      if (morechannels < 1) return 0; //go out if you cannot find even
				      //a first channel
    }

  //add more channels, the ones close enough to the channels already selected
  for (int i = 0; i < inputhits.nch; i++)
    {
      if (alreadyused[i]) continue;

      for (int j = 0; j < result.nch; j++)
	{
	if ( mydistance(inputhits.ch[i], result.ch[j]) < hitsmaxdist )
	  {
//	cout << "mydistance(inputhits.ch[i], result.ch[j]) < hitsmaxdist" << inputhits.ch[i] << ","<< result.ch[j] << endl;
	    result.InsertChannel(inputhits.ch[i]);
	    alreadyused[i] = true;
	    morechannels++;
	    break;
	  }
	else if ( mydistance(inputhits.ch[i]+periodicity, result.ch[j]) < periodicitymaxdist )
	  {
//	cout << "mydistance(inputhits.ch[i]+periodicity, result.ch[j]) < hitsmaxdist" << inputhits.ch[i]+periodicity << ","<< result.ch[j] << endl;
	    result.InsertChannel(inputhits.ch[i]);
	    alreadyused[i] = true;
	    morechannels++;
	    break;
	  }
	else if ( mydistance(inputhits.ch[i]-periodicity, result.ch[j]) < periodicitymaxdist )
	  {
//	cout << "mydistance(inputhits.ch[i]-periodicity, result.ch[j]) < hitsmaxdist" << inputhits.ch[i]-periodicity << ","<< result.ch[j] << endl;
	    result.InsertChannel(inputhits.ch[i]);
	    alreadyused[i] = true;
	    morechannels++;
	    break;
	  }
	else continue;
	}
    }

  if (morechannels < 1) return 0;

  return morechannels + FindCluster(hitsmaxdist, 
				    periodicity, 
				    periodicitymaxdist,
				    inputhits, 
				    alreadyused,
				    result);

}; 


////////////////////////////////////////////////////////////
//
// class VFATDataArray, derived from TObject and DataArray
//
////////////////////////////////////////////////////////////


int VFATDataArray::InsertEventInfo(int ievent, int tid, int sid, int trg, int tstamp, int bunch, int event)
{
        eid         	=ievent;
        turboid         =tid;
        slotid          =sid;
        trignum         =trg;
        timestamp       =tstamp;
        bc              =bunch;
        ec              =event;
	return 1;
}


////////////////////////////////////////////////////////////
//
// class Cluster, derived from TObject and DataArray
//
////////////////////////////////////////////////////////////

int Cluster::InsertChannel(chtype channel)
{
  int oldnch = nch;
  int morech = DataArray::InsertChannel(channel);
  if (morech == 1)
//    {
//	if ((mydistance(mydistance(pos, channel), 24)<1) && oldnch > 0) 
//	{ 
//	cout << "mydistance(pos, channel)>=20. Pos: " << pos <<";  Channel: "<< channel <<";  Diff: " <<mydistance(pos, channel) << endl;
//	pos = pos;
//	}
//	else pos = ( pos*oldnch + channel ) / nch;
	pos = ( pos*oldnch + channel ) / nch;
//    }
  return morech;
	
}

//    int Cluster::Find(const DataArray& inputhits,
//          		  DataArray& lefthits,
//          		  const double hitsmaxdist)
//    {
//      int arraysize = inputhits.nch;
//      bool* alreadyused = new bool[arraysize];
//      FindCluster(hitsmaxdist, inputhits,
//    	      alreadyused, *this);
//      UpdatePos();
//      
//      //Now check the remaining hits; 
//      if (lefthits.nallocated < arraysize)
//        {
//          lefthits.Reallocate(arraysize);
//        }
//      else lefthits.nch = 0;
//      
//      int nleft = 0;
//      for (int i = 0; i < arraysize; i++)
//        {
//          if (alreadyused[i]) continue;
//          lefthits.InsertChannel(inputhits.ch[i]);
//          nleft++;
//        }
//      
//      delete [] alreadyused;
//      
//      return nleft;
//    }





/////////////////////////////////////////////////////////////////
//
// class Track methods:
//
/////////////////////////////////////////////////////////////////

Track::Track(Double32_t _m, Double32_t _q,
	       Double32_t _chisquare, Double32_t _ndf)
  : 
  TObject(),
  m(_m), q(_q),
  chi2(_chisquare),ndf(_ndf)
{
  
}

Track::Track(const Track& original)
  : 
  TObject(original),
  m(original.m), q(original.q),
  chi2(original.chi2), ndf(original.ndf)
{
  
}
