
/////////////////////////////////////////////////////////////
//
// class DataArray
//
/////////////////////////////////////////////////////////////

//templace <typename T, int maxelements>
//#include <limits>

//With respect to Test0, now I derive Cluster also from DataArray
//instead of embedding DataArray as member object.
//So I give up with trying to avoid a virtual function table in
//DataArray, and rather I make the distructor virtual.
//Still I try to not derive DataArray from TObject

#include "TObject.h"

class DataArray 
  : public TObject 
{

public:
  typedef int chtype;
  typedef bool valtype;
  enum opresult 
    { operror = -1, noop = 0, 
      maxop  = 1000000000 /*numeric_limits<int>::max()*/ };


public: //private?
  int nallocated; //!

public:
  int nch;
  chtype *ch; //[nch]

public:
  //Default constructor for I/O
  DataArray() : TObject(), nallocated(0), nch(0), ch(0)
  {
    std::cout << "Standard constructor. Object at " 
          << static_cast<void*>(this) << std::endl; 
  };

  //Constructors with number of elements to allocate or inizializers
  explicit DataArray(const int maxNumOfChannels); 

  //Copy constructor
  DataArray(const DataArray& original);

  virtual ~DataArray() { if(ch) delete [] ch; };
  //~DataArray() { if(ch) delete [] ch; };

  //Resize (old contents are lost!)
  virtual int Reallocate(const int maxNumOfChannels);

  //Getters
  valtype Get(chtype channel);

  
  //Modify contents
  virtual int InsertChannel(chtype channel);
  //TODO: int RemoveChannel(chtype channel);
  virtual void RemoveAllChannels() 
	{ 
	nch = 0; 
	};


  //  int Sum();

  //ROOT macro for persistence support
  //  ClassDefNV(DataArray,1)    //DataArray
  ClassDef(DataArray,1)    //DataArray
    ;
};

// With FindCluster we define the max distance between two hits and
// the periodicity of the readout. For particular readout close
// channels could have "not close" channels. One example is a Pads
// readout. 
int FindCluster(const double hitsmaxdist, 
		const int periodicity,
		const double periodicitymaxdist, 
		const DataArray& inputhits, 
		bool* alreadyused,
		DataArray& result); 


/*
//#ifdef __CINT__

#if defined(__CINT__)
#pragma link C++ class DataArray;
#endif
*/


////////////////////////////////////////////////////////////
//
// class VFATDataArray, derived from TObject and DataArray
//
////////////////////////////////////////////////////////////

class VFATDataArray : public DataArray
{

public:

  int eid;
  int turboid;
  int slotid;
  int trignum;
  int timestamp;
  int bc;
  int ec;
    
public:
  //Standard constructor for I/O
  VFATDataArray() :  DataArray(), eid(0), turboid(0), slotid(0), trignum(0), timestamp(0), bc(0), ec(0) { };

  explicit VFATDataArray(const int maxNumOfChannels)
    :  DataArray(maxNumOfChannels), eid(0), turboid(0), slotid(0), trignum(0), timestamp(0), bc(0), ec(0)
  {
  }

  //Copy constructor
  VFATDataArray(const VFATDataArray& original)
    :	DataArray(original),
	eid(original.eid), 
	turboid(original.turboid), 
	slotid(original.slotid), 
	trignum(original.trignum), 	
	timestamp(original.timestamp), 
	bc(original.bc), 
	ec(original.ec) 
  { 
  }

  //Destructor
  virtual ~VFATDataArray() { };

  virtual int InsertChannel(chtype channel)
	{
	DataArray::InsertChannel(channel);
	return 1;
	}

  virtual int InsertEventInfo(int ievent, int tid, int sid, int trg, int tstamp, int bunch, int event);

  virtual void RemoveAllEventInfo() 
	{
  	eid		=0;
  	turboid		=0;
  	slotid		=0;
  	trignum		=0;
  	timestamp	=0;
  	bc		=0;
  	ec		=0;
	};

  //Clear contents 
  virtual void RemoveAllChannels()
  { 
    VFATDataArray::RemoveAllEventInfo();
    DataArray::RemoveAllChannels(); 
  }


  ClassDef(VFATDataArray,1)   
    ;
};



//////////////////////////////////////////////////////////////
//
// class Cluster, derived from TObject and DataArray
//
////////////////////////////////////////////////////////////

class Cluster : public DataArray
{

public:
  //  DataArray* hits; //I cannot specify "->" for the moment, I'm not yet
		   //sure if I'll be able to have a valid pointer all
		   //the time..

  Double32_t pos;
    
public:
  //Standard constructor for I/O
  Cluster() : DataArray(), pos(0)  { };

  explicit Cluster(const int maxNumOfChannels)
    : DataArray(maxNumOfChannels), pos(0)
  {
  }

  //Copy constructor
  Cluster(const Cluster& original)
    : DataArray(original)
    , pos(original.pos) 
  { 
  }

  //Destructor
  virtual ~Cluster() { };

  virtual double AsDouble() { return pos; }

  virtual int InsertChannel(chtype channel);

  //Clear contents 
  virtual void RemoveAllChannels()
  { 
    DataArray::RemoveAllChannels(); 
    pos = 0;
  }

  // TO DO: explicit void ResizeMaxHits(const int maxNumOfChannels);

  //Recalculate Pos
  int UpdatePos()
  {
    if ( !(nch && ch) )
      return operror;
      
    pos = 0;
    for (int i=0; i<nch; i++)
      pos += ch[i];
    pos /= nch;
    return 1;
  }




//  int Find(const DataArray& inputhits, 
//	   DataArray& lefthits,
//   	   const double hitsmaxdist);
  
  ClassDef(Cluster,1)   //Cluster
    ;
};




//////////////////////////////////////////////////////////
//
// Class Track derived from TObject //////////////////////
/////////////////////////////////////////////////////////


 class Track 
    : private TObject
  {
    
  public:
    Double32_t m;
    Double32_t q;
    Double32_t chi2;
    Double32_t ndf;
    

 
    //Default constructor
    Track (Double32_t m = 0, Double32_t q = 1,
	   Double32_t chisquare = 0, Double32_t ndf = 0);
    //Copy constructor
    Track (const Track& original);

    //Destructor
    virtual ~Track() {};

    //all other methods
    double GetXatZ(double z) { return m*z + q; };

    ClassDef(Track,1)    //Track class ROOT macro for persistence
                         //support
  };



/*
#if defined(__CINT__)
#pragma link C++ class Cluster;
#endif
*/
