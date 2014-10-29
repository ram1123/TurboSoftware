void PadTest(Int_t offset){
		      Int_t chipoffset = offset;
		      Int_t channels_per_chip = 128;
                      Int_t lastchanblock = channels_per_chip-16;
                      for(Int_t offset=0; offset < 8; offset++)
                        {
                          Int_t rightblock = lastchanblock-(offset<<4)-3+ chipoffset;
                          if (offset != 0)
                                {
                                        cout << (rightblock+15) << "; Det: " << (2*((rightblock+15)/120)*120+(rightblock+15)%24+(4-(rightblock+15)/24)*24)<<endl;
                                        cout << (rightblock+14) << "; Det: " << (2*((rightblock+14)/120)*120+(rightblock+14)%24+(4-(rightblock+14)/24)*24)<<endl;
                                        cout << (rightblock+13) << "; Det: " << (2*((rightblock+13)/120)*120+(rightblock+13)%24+(4-(rightblock+13)/24)*24)<<endl;
                                        cout << (rightblock+12) << "; Det: " << (2*((rightblock+12)/120)*120+(rightblock+12)%24+(4-(rightblock+12)/24)*24)<<endl;
                                        cout << (rightblock+11) << "; Det: " << (2*((rightblock+11)/120)*120+(rightblock+11)%24+(4-(rightblock+11)/24)*24)<<endl;
                                }
                                        cout << (rightblock+10) << "; Det: " << (2*((rightblock+10)/120)*120+(rightblock+10)%24+(4-(rightblock+10)/24)*24)<<endl;
                                        cout << (rightblock+9) << "; Det: " << (2*((rightblock+ 9)/120)*120+(rightblock+ 9)%24+(4-(rightblock+ 9)/24)*24)<<endl;
                                        cout << (rightblock+8) << "; Det: " << (2*((rightblock+ 8)/120)*120+(rightblock+ 8)%24+(4-(rightblock+ 8)/24)*24)<<endl;
                                        cout << (rightblock+7) << "; Det: " << (2*((rightblock+ 7)/120)*120+(rightblock+ 7)%24+(4-(rightblock+ 7)/24)*24)<<endl;
                                        cout << (rightblock+6) << "; Det: " << (2*((rightblock+ 6)/120)*120+(rightblock+ 6)%24+(4-(rightblock+ 6)/24)*24)<<endl;
                                        cout << (rightblock+5) << "; Det: " << (2*((rightblock+ 5)/120)*120+(rightblock+ 5)%24+(4-(rightblock+ 5)/24)*24)<<endl;
                                        cout << (rightblock+4) << "; Det: " << (2*((rightblock+ 4)/120)*120+(rightblock+ 4)%24+(4-(rightblock+ 4)/24)*24)<<endl;
                                        cout << (rightblock+3) << "; Det: " << (2*((rightblock+ 3)/120)*120+(rightblock+ 3)%24+(4-(rightblock+ 3)/24)*24)<<endl;
                          if (offset != 7)
                                {
                                        cout << (rightblock+2) << "; Det: " << (2*((rightblock+ 2)/120)*120+(rightblock+ 2)%24+(4-(rightblock+ 2)/24)*24)<<endl;
                                        cout << (rightblock+1) << "; Det: " << (2*((rightblock+ 1)/120)*120+(rightblock+ 1)%24+(4-(rightblock+ 1)/24)*24)<<endl;
                                        cout << (rightblock+0) << "; Det: " << (2*((rightblock+ 0)/120)*120+(rightblock+ 0)%24+(4-(rightblock+ 0)/24)*24)<<endl;
                                }
                        }
}
