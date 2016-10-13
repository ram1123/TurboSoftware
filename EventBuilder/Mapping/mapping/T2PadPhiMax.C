#include <fstream>


#include <TMath.h>

void T2PadPhiMax(){
Double_t dphi = 192./65.;


Double_t maxphiPS[1560];
for (Int_t i=0; i<1560; i++)
	{
                	maxphiPS[i] = 0;
	}
for (Int_t sphi=0; sphi<13; sphi++)
	{
		for (Int_t iphi=0; iphi<120; iphi++)
                	{
			maxphiPS[(sphi*120)+iphi] = (((276-dphi*5*(sphi+1)+dphi/2.)+(iphi/24)*dphi)+dphi/2.)*TMath::DegToRad();
        		}
	}
               cout << "double GetT2PadPhiMax(int channel)						"<< endl;
               cout << "{									"<< endl;
               cout << "  const static double mapT2padphimax[1560]=					"<< endl;
               cout << "    {									"<< endl;

for (Int_t i=0; i<1559; i++)
	{
               cout << "/* Max Phi Pad Channel " << i  << " */ " << maxphiPS[i] << ",			"<< endl;
	}
               cout << "/* Max Phi Pad Channel " << "1559"  << " */ " << maxphiPS[1559] << "		"<< endl;
               cout << "    };									"<< endl;
               cout << "  return mapT2padphimax[channel];						"<< endl;
               cout << "}                        						"<< endl;


//
//Double_t maxphiPS[1664];
//for (Int_t i=0; i<1664; i++)
//	{
//                	maxphiPS[i] = 0;
//	}
//for (Int_t sphi=0; sphi<13; sphi++)
//	{
//		for (Int_t iphi=3; iphi<123; iphi++)
//                	{
//			maxphiPS[(sphi*128)+iphi] = (((276-dphi*5*(sphi+1)+dphi/2.)+((iphi-3)/24)*dphi)+dphi/2.)*TMath::DegToRad();
//        		}
//	}
//
//
//               cout << "double GetT2PadPhiMax(int channel)			"<< endl;
//               cout << "{						"<< endl;
//               cout << "  const static double mapT2padphimax[1664]=		"<< endl;
//               cout << "    {						"<< endl;
//
//for (Int_t i=0; i<1663; i++)
//	{
//               cout << "/* Max Phi Pad Channel " << i  << " */ " << maxphiPS[i] << ","<< endl;
//	}
//               cout << "/* Max Phi Pad Channel " << "1663"  << " */ " << maxphiPS[1663] << ""<< endl;
//               cout << "    };						"<< endl;
//               cout << "  return mapT2padphimax[channel];"<< endl;
//               cout << "}"<< endl;

}
