#include <TMath.h>

void T2PadR(){
//-- define the pads geometry
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

Double_t RPS[1560];
for (Int_t i=0; i<1560; i++)
	{
                	RPS[i] = 0;
	}
for (Int_t sR=0; sR<1560; sR++)
	{
			RPS[sR] = (rPad[sR%24+1]-rPad[sR%24])/2.+rPad[sR%24];
	}
               cout << "double GetT2PadR(int channel)						"<< endl;
               cout << "{									"<< endl;
               cout << "  const static double mapT2padR[1560]=				"<< endl;
               cout << "    {									"<< endl;

for (Int_t i=0; i<1559; i++)
	{
               cout << "/* R Pad Channel " << i  << " */ " << RPS[i] << ",			"<< endl;
	}
               cout << "/* R Pad Channel " << "1559"  << " */ " << RPS[1559] << "		"<< endl;
               cout << "    };									"<< endl;
               cout << "  return mapT2padR[channel];						"<< endl;
               cout << "}                        						"<< endl;








//Double_t RPS[1664];
//for (Int_t i=0; i<1664; i++)
//	{
//                	RPS[i] = 0;
//	}
//for (Int_t sR=0; sR<13; sR++)
//	{
//		for (Int_t iR=3; iR<123; iR++)
//                	{
//			RPS[(sR*128)+iR] = (rPad[(iR-3)%24+1]-rPad[(iR-3)%24])/2.+rPad[(iR-3)%24];
//        		}
//	}
//
//
//               cout << "double GetT2PadR(int channel)			"<< endl;
//               cout << "{						"<< endl;
//               cout << "  const static double mapT2padR[1664]=	"<< endl;
//               cout << "    {						"<< endl;
//
//for (Int_t i=0; i<1663; i++)
//	{
//               cout << "/* R Pad Channel " << i  << " */ " << RPS[i] << ","<< endl;
//	}
//               cout << "/* R Pad Channel " << "1663"  << " */ " << RPS[1663] << ""<< endl;
//               cout << "    };						"<< endl;
//               cout << "  return mapT2padR[channel];			"<< endl;
//               cout << "}                        				"<< endl;






}                                               


