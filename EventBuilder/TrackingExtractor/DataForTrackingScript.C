void DataForTrackingScript(TString InputRootFile)
{
/*
cout <<endl;
cout << "-----------------------------------------------------------------------------------------------------"<<endl;
cout << " Input File 	: " << InputRootFile << endl;
cout << " Output File 	: " << OutputRecoFile << endl;
if (TotalEntries==0){cout << " Total Number of Entries Analized : " << "All Entries" << endl;}
else {cout << " Total Number of Entries Analized : " << TotalEntries << endl;}
cout << " First Entry Analized : " << FirstEntry << endl;
cout << "-----------------------------------------------------------------------------------------------------"<<endl;
cout <<endl;
*/
//cout << " Input File : " << InputRootFile << " Output File : " << OutputRecoFile;
gROOT->ProcessLine(".x ./Load.cpp");
TFile file0(InputRootFile); 
//gROOT->ProcessLine(".! rm -f RecoGeo2d_ps_C.so");
//gROOT->ProcessLine(".! rm -f RecoGeo_baseclass_C.so");
rd51tbgeo->MakeSelector("RecoGeo_baseclass");
gROOT->ProcessLine(".L ./RecoGeo_baseclass.C++");
//rd51tbgeo->Process("RecoGeo_baseclass.C++");
rd51tbgeo->Process("DataForTracking.C++");
}
