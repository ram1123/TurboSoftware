void PadChannelAssignment(){
	Int_t DetectorChannel;
	Int_t VFATChannel;

	for (Int_t i=0; i<120; i++)
	{
		VFATChannel = i;
		DetectorChannel = 2*(VFATChannel/120)*120+VFATChannel%24+(4-(VFATChannel/24))*24;
		cout << "VFAT Channel: " << VFATChannel << " ;	Detector Channel: " << Detector Channel << ";" << endl;
	}
}
