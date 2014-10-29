#include <fstream>


#include <TMath.h>

void T2PadPhi(){
Double_t dphi = 192./65.;


Double_t phiPS[1560];
for (Int_t i=0; i<1560; i++)
	{
                	phiPS[i] = 0;
	}
for (Int_t sphi=0; sphi<13; sphi++)
	{
		for (Int_t iphi=0; iphi<120; iphi++)
                	{
			phiPS[(sphi*120)+iphi] = ((276-dphi*5*(sphi+1)+dphi/2.)+(iphi/24)*dphi)*TMath::DegToRad();
        		}
	}
               cout << "double GetT2PadPhi(int channel)						"<< endl;
               cout << "{									"<< endl;
               cout << "  const static double mapT2padphi[1560]=					"<< endl;
               cout << "    {									"<< endl;

for (Int_t i=0; i<1559; i++)
	{
               cout << "/* Phi Pad Channel " << i  << " */ " << phiPS[i] << ",			"<< endl;
	}
               cout << "/* Phi Pad Channel " << "1559"  << " */ " << phiPS[1559] << "		"<< endl;
               cout << "    };									"<< endl;
               cout << "  return mapT2padphi[channel];						"<< endl;
               cout << "}                        						"<< endl;


//
//Double_t phiPS[1664];
//for (Int_t i=0; i<1664; i++)
//	{
//                	phiPS[i] = 0;
//	}
//for (Int_t sphi=0; sphi<13; sphi++)
//	{
//		for (Int_t iphi=3; iphi<123; iphi++)
//                	{
//			phiPS[(sphi*128)+iphi] = ((276-dphi*5*(sphi+1)+dphi/2.)+((iphi-3)/24)*dphi)*TMath::DegToRad();
//        		}
//	}
//
//
//               cout << "double GetT2PadPhi(int channel)			"<< endl;
//               cout << "{						"<< endl;
//               cout << "  const static double mapT2padphi[1664]=		"<< endl;
//               cout << "    {						"<< endl;
//
//for (Int_t i=0; i<1663; i++)
//	{
//               cout << "/* Phi Pad Channel " << i  << " */ " << phiPS[i] << ","<< endl;
//	}
//               cout << "/* Phi Pad Channel " << "1663"  << " */ " << phiPS[1663] << ""<< endl;
//               cout << "    };						"<< endl;
//               cout << "  return mapT2padphi[channel];"<< endl;
//               cout << "}"<< endl;

}
