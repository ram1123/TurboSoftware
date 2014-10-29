#include <TMath.h>



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


Double_t dphi = 192./65.;
Double_t phiPS[1560];
Double_t maxphiPS[1560];
Double_t minphiPS[1560];
Double_t RPS[1560];
Double_t maxRPS[1560];
Double_t minRPS[1560];

Double_t XPS[1560];
Double_t YPS[1560];



void T2PadPhi(){
//for (Int_t i=0; i<1560; i++)
//	{
//                	phiPS[i] = 0;
//	}
//for (Int_t sphi=0; sphi<13; sphi++)
//	{
//		for (Int_t iphi=0; iphi<120; iphi++)
//               	{
//			phiPS[(sphi*120)+iphi] = ((276-dphi*5*(sphi+1)+dphi/2.)+(iphi/24)*dphi)*TMath::DegToRad();
//        		}
//	}

for (Int_t i=0; i<1560; i++)
	{
                	phiPS[i] = (276-dphi*(i/24)+dphi/2.)*TMath::DegToRad();
	}



               cout << "//------Pads Phi ------------------------------------------------------	"<< endl;
               cout << "Double32_t GetPhi_TotemT2Pads(Int_t channel)					"<< endl;
               cout << "{									"<< endl;
               cout << "  const static Double32_t Phi_TotemT2Pads[1560]=					"<< endl;
               cout << "    {									"<< endl;

for (Int_t i=0; i<1559; i++)
	{
               cout << "/* Phi Pad Channel " << i  << " */ " << phiPS[i] << ",			"<< endl;
	}
               cout << "/* Phi Pad Channel " << "1559"  << " */ " << phiPS[1559] << "		"<< endl;
               cout << "    };									"<< endl;
               cout << "  return Phi_TotemT2Pads[channel];						"<< endl;
               cout << "}                        						"<< endl;
               cout << "//------Pads Phi ------------------------------------------------------	"<< endl;
               cout << "                        						"<< endl;
}


void T2PadPhiMax(){
//for (Int_t i=0; i<1560; i++)
//	{
//                	maxphiPS[i] = 0;
//	}
//for (Int_t sphi=0; sphi<13; sphi++)
//	{
//		for (Int_t iphi=0; iphi<120; iphi++)
//                	{
//			maxphiPS[(sphi*120)+iphi] = (((276-dphi*5*(sphi+1)+dphi/2.)+(iphi/24)*dphi)+dphi/2.)*TMath::DegToRad();
//        		}
//	}

for (Int_t i=0; i<1560; i++)
	{
                	maxphiPS[i] = (276-dphi*(i/24))*TMath::DegToRad();
	}
               cout << "//------Pads Max Phi ------------------------------------------------------	"<< endl;
               cout << "Double32_t GetPhiMax_TotemT2Pads(Int_t channel)						"<< endl;
               cout << "{									"<< endl;
               cout << "  const static Double32_t PhiMax_TotemT2Pads[1560]=					"<< endl;
               cout << "    {									"<< endl;

for (Int_t i=0; i<1559; i++)
	{
               cout << "/* Max Phi Pad Channel " << i  << " */ " << maxphiPS[i] << ",			"<< endl;
	}
               cout << "/* Max Phi Pad Channel " << "1559"  << " */ " << maxphiPS[1559] << "		"<< endl;
               cout << "    };									"<< endl;
               cout << "  return PhiMax_TotemT2Pads[channel];						"<< endl;
               cout << "}                        						"<< endl;
               cout << "//------Pads Max Phi ------------------------------------------------------	"<< endl;
               cout << "                        						"<< endl;
}



void T2PadPhiMin(){
//for (Int_t i=0; i<1560; i++)
//	{
//                	minphiPS[i] = 0;
//	}
//for (Int_t sphi=0; sphi<13; sphi++)
//	{
//		for (Int_t iphi=0; iphi<120; iphi++)
//               	{
//			minphiPS[(sphi*120)+iphi] = (((276-dphi*5*(sphi+1)+dphi/2.)+(iphi/24)*dphi)-dphi/2.)*TMath::DegToRad();
//        		}
//	}
for (Int_t i=0; i<1560; i++)
	{
                	minphiPS[i] = (276-dphi*(i/24)+dphi)*TMath::DegToRad();
	}
               cout << "//------Pads Min Phi ------------------------------------------------------	"<< endl;
               cout << "Double32_t GetPhiMin_TotemT2Pads(Int_t channel)						"<< endl;
               cout << "{									"<< endl;
               cout << "  const static Double32_t PhiMin_TotemT2Pads[1560]=					"<< endl;
               cout << "    {									"<< endl;

for (Int_t i=0; i<1559; i++)
	{
               cout << "/* Min Phi Pad Channel " << i  << " */ " << minphiPS[i] << ",			"<< endl;
	}
               cout << "/* Min Phi Pad Channel " << "1559"  << " */ " << minphiPS[1559] << "		"<< endl;
               cout << "    };									"<< endl;
               cout << "  return PhiMin_TotemT2Pads[channel];						"<< endl;
               cout << "}                        						"<< endl;
               cout << "//------Pads Min Phi ------------------------------------------------------	"<< endl;
               cout << "                        						"<< endl;
}



void T2PadR(){
for (Int_t i=0; i<1560; i++)
	{
                	RPS[i] = 0;
	}
for (Int_t sR=0; sR<1560; sR++)
	{
			RPS[sR] = (rPad[sR%24+1]-rPad[sR%24])/2.+rPad[sR%24];
	}
               cout << "//------Pads R ------------------------------------------------------	"<< endl;
               cout << "Double32_t GetR_TotemT2Pads(Int_t channel)						"<< endl;
               cout << "{									"<< endl;
               cout << "  const static Double32_t R_TotemT2Pads[1560]=				"<< endl;
               cout << "    {									"<< endl;

for (Int_t i=0; i<1559; i++)
	{
               cout << "/* R Pad Channel " << i  << " */ " << RPS[i] << ",			"<< endl;
	}
               cout << "/* R Pad Channel " << "1559"  << " */ " << RPS[1559] << "		"<< endl;
               cout << "    };									"<< endl;
               cout << "  return R_TotemT2Pads[channel];						"<< endl;
               cout << "}                        						"<< endl;
               cout << "//------Pads R ------------------------------------------------------	"<< endl;
               cout << "                        						"<< endl;
}                                               



void T2PadRMax(){
for (Int_t i=0; i<1560; i++)
	{
                	maxRPS[i] = 0;
	}
for (Int_t sR=0; sR<1560; sR++)
	{
			maxRPS[sR] = rPad[sR%24+1];
	}
               cout << "//------Pads Max R ------------------------------------------------------	"<< endl;
               cout << "Double32_t GetRMax_TotemT2Pads(Int_t channel)						"<< endl;
               cout << "{									"<< endl;
               cout << "  const static Double32_t RMax_TotemT2Pads[1560]=				"<< endl;
               cout << "    {									"<< endl;

for (Int_t i=0; i<1559; i++)
	{
               cout << "/* Max R Pad Channel " << i  << " */ " << maxRPS[i] << ",			"<< endl;
	}
               cout << "/* Max R Pad Channel " << "1559"  << " */ " << maxRPS[1559] << "		"<< endl;
               cout << "    };									"<< endl;
               cout << "  return RMax_TotemT2Pads[channel];						"<< endl;
               cout << "}                        						"<< endl;
               cout << "//------Pads R ------------------------------------------------------	"<< endl;
               cout << "                        						"<< endl;
}                                               



void T2PadRMin(){
for (Int_t i=0; i<1560; i++)
	{
                	minRPS[i] = 0;
	}
for (Int_t sR=0; sR<1560; sR++)
	{
			minRPS[sR] = rPad[sR%24];
	}
               cout << "//------Pads Min R ------------------------------------------------------	"<< endl;
               cout << "Double32_t GetRMin_TotemT2Pads(Int_t channel)						"<< endl;
               cout << "{									"<< endl;
               cout << "  const static Double32_t RMin_TotemT2Pads[1560]=				"<< endl;
               cout << "    {									"<< endl;

for (Int_t i=0; i<1559; i++)
	{
               cout << "/* Min R Pad Channel " << i  << " */ " << minRPS[i] << ",			"<< endl;
	}
               cout << "/* Min R Pad Channel " << "1559"  << " */ " << minRPS[1559] << "		"<< endl;
               cout << "    };									"<< endl;
               cout << "  return RMin_TotemT2Pads[channel];						"<< endl;
               cout << "}                        						"<< endl;
               cout << "//------Pads Min R ------------------------------------------------------	"<< endl;
               cout << "                        						"<< endl;
}                                               


void T2PadX(){
for (Int_t i=0; i<1560; i++)
	{
	XPS[i]=RPS[i]*TMath::Cos(phiPS[i]);		
	}

               cout << "//------Pads X ------------------------------------------------------	"<< endl;
               cout << "Double32_t GetX_TotemT2Pads(Int_t channel)			"<< endl;
               cout << "{						"<< endl;
               cout << "  const static Double32_t X_TotemT2Pads[1560]=		"<< endl;
               cout << "    {						"<< endl;


for (Int_t i=0; i<1559; i++)
	{
               cout << "/* X Pad Channel " << i  << " */ " << XPS[i] << ",			"<< endl;
	}
               cout << "/* X Pad Channel " << "1559"  << " */ " << XPS[1559] << "		"<< endl;
               cout << "    };									"<< endl;
               cout << "  return X_TotemT2Pads[channel];						"<< endl;
               cout << "//------Pads X ------------------------------------------------------	"<< endl;
               cout << "}                        						"<< endl;
               cout << "                        						"<< endl;
}



void T2PadY(){
for (Int_t i=0; i<1560; i++)
	{
	YPS[i]=RPS[i]*TMath::Sin(phiPS[i]);		
	}

               cout << "//------Pads Y ------------------------------------------------------	"<< endl;
               cout << "Double32_t GetY_TotemT2Pads(Int_t channel)			"<< endl;
               cout << "{						"<< endl;
               cout << "  const static Double32_t Y_TotemT2Pads[1560]=		"<< endl;
               cout << "    {						"<< endl;


for (Int_t i=0; i<1559; i++)
	{
               cout << "/* Y Pad Channel " << i  << " */ " << YPS[i] << ",			"<< endl;
	}
               cout << "/* Y Pad Channel " << "1559"  << " */ " << YPS[1559] << "		"<< endl;
               cout << "    };									"<< endl;
               cout << "  return Y_TotemT2Pads[channel];						"<< endl;
               cout << "}                        						"<< endl;
               cout << "//------Pads Y ------------------------------------------------------	"<< endl;
               cout << "                        						"<< endl;


}



void T2Map(){



//cout << "Double32_t GetPhi_TotemT2Pads(Int_t channel);"<< endl;
//cout << "Double32_t GetPhiMax_TotemT2Pads(Int_t channel);"<< endl;
//cout << "Double32_t GetPhiMin_TotemT2Pads(Int_t channel);"<< endl;
//cout << "Double32_t GetR_TotemT2Pads(Int_t channel);"<< endl;
//cout << "Double32_t GetRMax_TotemT2Pads(Int_t channel);"<< endl;
//cout << "Double32_t GetRMin_TotemT2Pads(Int_t channel);"<< endl;
//cout << "Double32_t GetX_TotemT2Pads(Int_t channel);"<< endl;
//cout << "Double32_t GetY_TotemT2Pads(Int_t channel);"<< endl;


cout << ""<< endl;
cout << ""<< endl;
cout << "#include \"TMath.h\""<< endl;
cout << "#include \"TotemT2.hpp\""<< endl;
cout << ""<< endl;
cout << ""<< endl;

	T2PadPhi();  
	T2PadPhiMax();  
	T2PadPhiMin();  
	T2PadR();  
	T2PadRMax();  
	T2PadRMin();  
	T2PadX();  
	T2PadY();

cout << ""<< endl;
cout << ""<< endl;
cout << "//------Strips R-----------------------------------------------------	"<< endl;
cout << "Double32_t GetR_TotemT2Strips(Int_t channel)	"<< endl;
cout << "  {						"<< endl;
cout << "        return 0.4*(channel%256)+42.5;		"<< endl;
cout << "  }                                   		"<< endl;
cout << "//------Strips R-----------------------------------------------------	"<< endl;
cout << ""<< endl;
cout << ""<< endl;
cout << "//------Distance-----------------------------------------------------	"<< endl;
cout << "double dist_TotemT2(double x0, double y0, double x1, double y1) 	"<< endl;
cout << "{                                                               	"<< endl;
cout << "  double distance;                                              	"<< endl;
cout << "  distance = TMath::Sqrt ( (x0-x1)*(x0-x1) + (y0-y1)*(y0-y1) );	"<< endl;
cout << "  return distance;                                             	"<< endl;
cout << "}                                                              	"<< endl;
cout << "//------Distance-----------------------------------------------------	"<< endl;






}
