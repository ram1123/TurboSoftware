#include "vector"
class TFile;
#ifdef __CINT__ 
#pragma link C++ nestedclasses;
#pragma link C++ nestedtypedefs;
#pragma link C++ class vector<TFile*>+;
#pragma link C++ class vector<TFile*>::*;
#ifdef G__VECTOR_HAS_CLASS_ITERATOR
#pragma link C++ operators vector<TFile*>::iterator;
#pragma link C++ operators vector<TFile*>::const_iterator;
#pragma link C++ operators vector<TFile*>::reverse_iterator;
#endif
#endif
