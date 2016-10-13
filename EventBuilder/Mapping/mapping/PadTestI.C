{        
              for(Int_t j=0; j < 13; j++)
                    {
		      Int_t chipoffset = 120*j;	
                      Int_t lastchanblock = 128-16;
                      for(Int_t offset=0; offset < 8; offset++)
                        {

                          Int_t rightblock = lastchanblock-(offset<<4)-3+ chipoffset;
                          if (offset != 0)
                                {
                                if (0xFFFF & 0x8000)
                                        {cout << rightblock+15-chipoffset << "\t" << (2*((rightblock+15)/120)*120+(rightblock+15)%24+(4-(rightblock+15)/24)*24) << endl;}
                                if (0xFFFF & 0x4000)          
                                        {cout << rightblock+14-chipoffset  << "\t" << (2*((rightblock+14)/120)*120+(rightblock+14)%24+(4-(rightblock+14)/24)*24) << endl;}
                                if (0xFFFF & 0x2000)          
                                        {cout << rightblock+13-chipoffset  << "\t" << (2*((rightblock+13)/120)*120+(rightblock+13)%24+(4-(rightblock+13)/24)*24) << endl;}
                                if (0xFFFF & 0x1000)          
                                        {cout << rightblock+12-chipoffset  << "\t" << (2*((rightblock+12)/120)*120+(rightblock+12)%24+(4-(rightblock+12)/24)*24) << endl;}
                                if (0xFFFF & 0x0800)          
                                        {cout << rightblock+11-chipoffset  << "\t" << (2*((rightblock+11)/120)*120+(rightblock+11)%24+(4-(rightblock+11)/24)*24) << endl;}
                                }                             
                          if (0xFFFF & 0x0400)                
                                        {cout << rightblock+10-chipoffset  << "\t" << (2*((rightblock+10)/120)*120+(rightblock+10)%24+(4-(rightblock+10)/24)*24) << endl;}
                          if (0xFFFF & 0x0200)                
                                        {cout << rightblock+ 9-chipoffset  << "\t" << (2*((rightblock+ 9)/120)*120+(rightblock+ 9)%24+(4-(rightblock+ 9)/24)*24) << endl;}
                          if (0xFFFF & 0x0100)                
                                        {cout << rightblock+ 8-chipoffset  << "\t" << (2*((rightblock+ 8)/120)*120+(rightblock+ 8)%24+(4-(rightblock+ 8)/24)*24) << endl;}
                          if (0xFFFF & 0x0080)                
                                        {cout << rightblock+ 7-chipoffset  << "\t" << (2*((rightblock+ 7)/120)*120+(rightblock+ 7)%24+(4-(rightblock+ 7)/24)*24) << endl;}
                          if (0xFFFF & 0x0040)                
                                        {cout << rightblock+ 6-chipoffset  << "\t" << (2*((rightblock+ 6)/120)*120+(rightblock+ 6)%24+(4-(rightblock+ 6)/24)*24) << endl;}
                          if (0xFFFF & 0x0020)                
                                        {cout << rightblock+ 5-chipoffset  << "\t" << (2*((rightblock+ 5)/120)*120+(rightblock+ 5)%24+(4-(rightblock+ 5)/24)*24) << endl;}
                          if (0xFFFF & 0x0010)                
                                        {cout << rightblock+ 4-chipoffset  << "\t" << (2*((rightblock+ 4)/120)*120+(rightblock+ 4)%24+(4-(rightblock+ 4)/24)*24) << endl;}
                          if (0xFFFF & 0x0008)                
                                        {cout << rightblock+ 3-chipoffset  << "\t" << (2*((rightblock+ 3)/120)*120+(rightblock+ 3)%24+(4-(rightblock+ 3)/24)*24) << endl;}
                          if (offset != 7)                    
                                {                             
                                if (0xFFFF & 0x0004)          
                                        {cout << rightblock+ 2-chipoffset  << "\t" << (2*((rightblock+ 2)/120)*120+(rightblock+ 2)%24+(4-(rightblock+ 2)/24)*24) << endl;}
                                if (0xFFFF & 0x0002)          
                                        {cout << rightblock+ 1-chipoffset  << "\t" << (2*((rightblock+ 1)/120)*120+(rightblock+ 1)%24+(4-(rightblock+ 1)/24)*24) << endl;}
                                if (0xFFFF & 0x0001)          
                                        {cout << rightblock+ 0-chipoffset  << "\t" << (2*((rightblock+ 0)/120)*120+(rightblock+ 0)%24+(4-(rightblock+ 0)/24)*24) << endl;}
                                }
			}
		}
}

