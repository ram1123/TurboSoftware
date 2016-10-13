#ifndef ReadoutType_hpp
#define ReadoutType_hpp

#include "TotemT2.hpp"
#include "TotemT1LG.hpp"
#include "CmsMapping.hpp"

Float_t GetX(Int_t ReadoutType, Int_t channel);
Float_t GetY(Int_t ReadoutType, Int_t channel);
Float_t GetZ(Int_t ReadoutType, Int_t channel);
Float_t GetR(Int_t ReadoutType, Int_t channel);
Float_t GetRMax(Int_t ReadoutType, Int_t channel);
Float_t GetRMin(Int_t ReadoutType, Int_t channel);
Float_t GetPhi(Int_t ReadoutType, Int_t channel);
Float_t GetPhiMax(Int_t ReadoutType, Int_t channel);
Float_t GetPhiMin(Int_t ReadoutType, Int_t channel);

#endif
