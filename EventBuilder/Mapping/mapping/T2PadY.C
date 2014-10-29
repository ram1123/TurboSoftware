#include <fstream>


#include <TMath.h>

Double_t radPS[1560];
Double_t phiPS[1560];

void T2PadPhi(){
Double_t dphi = 192./65.;


//Double_t phiPS[1560];
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

}



void T2PadRad(){
Double_t rPad[25];

rPad[0]      = 42.5     ;
rPad[1]      = 44.7273  ;
rPad[2]      = 47.069   ;
rPad[3]      = 49.5332  ;
rPad[4]      = 52.1265  ;
rPad[5]      = 54.8555  ;
rPad[6]      = 57.7274  ;
rPad[7]      = 60.7497  ;
rPad[8]      = 63.9301  ;
rPad[9]      = 67.2771  ;
rPad[10]     = 69.8114  ;
rPad[11]     = 74.5054  ;
rPad[12]     = 78.4061  ;
rPad[13]     = 82.511   ;
rPad[14]     = 86.8307  ;
rPad[15]     = 91.3767  ;
rPad[16]     = 96.1606  ;
rPad[17]     = 100.2298 ;
rPad[18]     = 106.4929 ;
rPad[19]     = 112.0612 ;
rPad[20]     = 117.928  ;
rPad[21]     = 124.1    ;
rPad[22]     = 130.5971 ;
rPad[23]     = 137.4344 ;
rPad[24]     = 144.6296 ;

// Double_t radPS[1560];
for (Int_t i=0; i<1560; i++)
	{
                	radPS[i] = 0;
	}
for (Int_t srad=0; srad<1560; srad++)
	{
			radPS[srad] = (rPad[srad%24+1]-rPad[srad%24])/2.+rPad[srad%24];
	}


//Double_t radPS[1664];
//for (Int_t i=0; i<1664; i++)
//	{
//                	radPS[i] = 0;
//	}
//for (Int_t srad=0; srad<13; srad++)
//	{
//		for (Int_t irad=3; irad<123; irad++)
//                	{
//			radPS[(srad*128)+irad] = (rPad[(irad-3)%24+1]-rPad[(irad-3)%24])/2.+rPad[(irad-3)%24];
//        		}
//	}

}



void T2PadY(){
	T2PadPhi();
	T2PadRad();

Double_t YPS[1560];
for (Int_t i=0; i<1560; i++)
	{
	YPS[i]=radPS[i]*TMath::Sin(phiPS[i]);		
	}

               cout << "double GetT2PadY(int channel)			"<< endl;
               cout << "{						"<< endl;
               cout << "  const static double mapT2pady[1560]=		"<< endl;
               cout << "    {						"<< endl;


for (Int_t i=0; i<1559; i++)
	{
               cout << "/* Y Pad Channel " << i  << " */ " << YPS[i] << ",			"<< endl;
	}
               cout << "/* Y Pad Channel " << "1559"  << " */ " << YPS[1559] << "		"<< endl;
               cout << "    };									"<< endl;
               cout << "  return mapT2pady[channel];						"<< endl;
               cout << "}                        						"<< endl;


}


