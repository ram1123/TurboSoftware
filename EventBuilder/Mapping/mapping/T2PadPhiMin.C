#include <fstream>


#include <TMath.h>

void T2PadPhiMin(){
Double_t dphi = 192./65.;


Double_t minphiPS[1560];
for (Int_t i=0; i<1560; i++)
	{
                	minphiPS[i] = 0;
	}
for (Int_t sphi=0; sphi<13; sphi++)
	{
		for (Int_t iphi=0; iphi<120; iphi++)
                	{
			minphiPS[(sphi*120)+iphi] = (((276-dphi*5*(sphi+1)+dphi/2.)+(iphi/24)*dphi)-dphi/2.)*TMath::DegToRad();
        		}
	}
               cout << "double GetT2PadPhiMin(int channel)						"<< endl;
               cout << "{									"<< endl;
               cout << "  const static double mapT2padphimin[1560]=					"<< endl;
               cout << "    {									"<< endl;

for (Int_t i=0; i<1559; i++)
	{
               cout << "/* Min Phi Pad Channel " << i  << " */ " << minphiPS[i] << ",			"<< endl;
	}
               cout << "/* Min Phi Pad Channel " << "1559"  << " */ " << minphiPS[1559] << "		"<< endl;
               cout << "    };									"<< endl;
               cout << "  return mapT2padphimin[channel];						"<< endl;
               cout << "}                        						"<< endl;


//
//Double_t minphiPS[1664];
//for (Int_t i=0; i<1664; i++)
//	{
//                	minphiPS[i] = 0;
//	}
//for (Int_t sphi=0; sphi<13; sphi++)
//	{
//		for (Int_t iphi=3; iphi<123; iphi++)
//                	{
//			minphiPS[(sphi*128)+iphi] = (((276-dphi*5*(sphi+1)+dphi/2.)+((iphi-3)/24)*dphi)-dphi/2.)*TMath::DegToRad();
//        		}
//	}
//
//
//               cout << "double GetT2PadPhiMin(int channel)			"<< endl;
//               cout << "{						"<< endl;
//               cout << "  const static double mapT2padphimin[1664]=		"<< endl;
//               cout << "    {						"<< endl;
//
//for (Int_t i=0; i<1663; i++)
//	{
//               cout << "/* Min Phi Pad Channel " << i  << " */ " << minphiPS[i] << ","<< endl;
//	}
//               cout << "/* Min Phi Pad Channel " << "1663"  << " */ " << minphiPS[1663] << ""<< endl;
//               cout << "    };						"<< endl;
//               cout << "  return mapT2padphimin[channel];"<< endl;
//               cout << "}"<< endl;

}
