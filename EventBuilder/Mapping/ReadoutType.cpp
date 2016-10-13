#include <iostream>
#include "TotemT2.hpp"
#include "TotemT1LG.hpp"
#include "CmsMapping.hpp"

// ReadoutType
// 0:	X Strips with 400um pitch
// 1:	Y Strips with 400um pitch
// 2:	X Strips with 800um pitch
// 3:	Y Strips with 800um pitch
// 4:	Totem T2 Strips
// 5:	Totem T2 Pads
// 6:	Totem T1 LG
// 8:	CMS 30x30
// 9:   CMS GE1/1
//
// WARNING: If a new readout is added also "Clustering/GeoDataArray_T.cpp" has to be updated

Float_t GetX(Int_t ReadoutType, Int_t channel)
{
	if (ReadoutType == 0) return 0.4*channel;
	else if (ReadoutType == 2) return 0.8*channel;
	else if (ReadoutType == 5) return GetX_TotemT2Pads(channel);
	else if (ReadoutType == 6) return GetX_TotemT1LG(channel);
	else if (ReadoutType == 8) return 0.8*GetX_Cms30x30(channel);
        else if (ReadoutType == 9) return 0.8169*GetX_Cmsbig(channel);
	/*
	 * ReadoutType = 9 details for GE11:
	 * if sector 5 then pitch = 0.816915 mm
	 * if sector 8 then pitch = 0.674115 mm
	 * if sector 1 then pitch = 1.0598 mm
	 *
	 * Ref: https://indico.cern.ch/event/284233/session/2/contribution/13/attachments/525033/724083/131122_GEM_Geometry_Highlights_v9.pdf
	 */
	else {cout <<  "ReadOutType: " << ReadoutType << "\tAttention Wrong Map Type: No Type Found or Wrong Request "<< endl; return 999;}
};

Float_t GetY(Int_t ReadoutType, Int_t channel)
{
	if (ReadoutType == 1) return 0.4*channel;
	else if (ReadoutType == 3) return 0.8*channel;
	else if (ReadoutType == 5) return GetY_TotemT2Pads(channel);
	else if (ReadoutType == 6) return GetY_TotemT1LG(channel);
	else {cout <<  "Wrong Map Type: No Type Found or Wrong Request"; return 999;}
};

//Float_t GetZ(Int_t ReadoutType, Int_t channel)
//{
//	if (ReadoutType <=9 ) return 0.;
//	else {cout<<  "ReadOutType: " << ReadoutType  <<  "Wrong Map Type: No Type Found or Wrong Request"<< endl; return 999;}
//};

Float_t GetR(Int_t ReadoutType, Int_t channel)
{
	if (ReadoutType == 4) return GetR_TotemT2Strips(channel);
	else if (ReadoutType == 5) return GetR_TotemT2Pads(channel);
	else {cout <<  "Wrong Map Type: No Type Found or Wrong Request"; return 999;}
};

Float_t GetRMax(Int_t ReadoutType, Int_t channel)
{
	if (ReadoutType == 5) return GetRMax_TotemT2Pads(channel);
	else {cout <<  "Wrong Map Type: No Type Found or Wrong Request"; return 999;}
};

Float_t GetRMin(Int_t ReadoutType, Int_t channel)
{
	if (ReadoutType == 5) return GetRMin_TotemT2Pads(channel);
	else {cout <<  "Wrong Map Type: No Type Found or Wrong Request"; return 999;}
};

Float_t GetPhi(Int_t ReadoutType, Int_t channel)
{
	if (ReadoutType == 5) return GetPhi_TotemT2Pads(channel);
	else {cout <<  "Wrong Map Type: No Type Found or Wrong Request"; return 999;}
};

Float_t GetPhiMax(Int_t ReadoutType, Int_t channel)
{
	if (ReadoutType == 5) return GetPhiMax_TotemT2Pads(channel);
	else {cout <<  "Wrong Map Type: No Type Found or Wrong Request"; return 999;}
};

Float_t GetPhiMin(Int_t ReadoutType, Int_t channel)
{
	if (ReadoutType == 5) return GetPhiMin_TotemT2Pads(channel);
	else {cout <<  "Wrong Map Type: No Type Found or Wrong Request"; return 999;}

};
