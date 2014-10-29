#ifndef T2TOTEMMAP_hpp
#define T2TOTEMMAP_hpp

double GetT2PadX(int channel);
double GetT2PadY(int channel);
double GetT2PadR(int channel);
double GetT2PadRMax(int channel);
double GetT2PadRMin(int channel);
double GetT2PadPhi(int channel);
double GetT2PadPhiMax(int channel);
double GetT2PadPhiMin(int channel);
double dist(double x0, double y0, double x1, double y1);

//static double gt2g1_offset_x = 0;
//static double gt2g1_offset_y = 0;

//static double gt2g2_offset_x = 0;
//static double gt2g2_offset_y = 0;

#endif
