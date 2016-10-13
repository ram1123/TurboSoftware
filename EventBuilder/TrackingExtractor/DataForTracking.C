#define DataForTracking_cxx
// The class definition in DataForTracking.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.

// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// Root > T->Process("DataForTracking.C")
// Root > T->Process("DataForTracking.C","some options")
// Root > T->Process("DataForTracking.C+")
//

#include "DataForTracking.h"
#include <TH2.h>
#include <TStyle.h>
#include <TMath.h>
#include <TGraphErrors.h>
#include <iostream>




//   Struct RecoEventInfo_t {
//   	int       EventNumber;
//        int       TriggerNumber;
//        int       TimeStamp;
//        int       BunchCounter;
//        int       EventCounter;
//   };
//   RecoEventInfo_t RecoEventInfo;

void DataForTracking::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.

   TString option = GetOption();
   outFileName = option.Copy();
   if (outFileName.Length() == 0) outFileName = "RecoForTracking.root";

   outFile = new TFile(outFileName,"RECREATE");
   outFile->cd();

   treeForTracks = new TTree("TreeForTracks","An example of ROOT tree with the braches for the Tracking");
   treeForTracks->Branch("RecoEventInfo",&RecoEventInfo.EventNumber ,"EventNumber/I:TriggerNumber/I:TimeStamp/I:BunchCounter/I:EventCounter/I");
   char nclBranch[20];
   char posBranch[20];
   char erPosBranch[20];

   sprintf(nclBranch, "ncl[%i]/I", kNumberOfDetector);
   sprintf(posBranch, "pos[%i][%i]/F", kNumberOfDetector, kMaxNumberOfClusters);
   sprintf(erPosBranch, "erPos[%i][%i]/F", kNumberOfDetector, kMaxNumberOfClusters);

   treeForTracks->Branch("ncl",&(ncl),nclBranch);
   treeForTracks->Branch("pos",&(pos),posBranch);
   treeForTracks->Branch("erPos",&(erPos),erPosBranch);

}

void DataForTracking::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

Bool_t DataForTracking::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // It can be passed to either DataForTracking::GetEntry() or TBranch::GetEntry()
   // to read either all or the required parts of the data. When processing
   // keyed objects with PROOF, the object is already loaded and is available
   // via the fObject pointer.
   //
   // This function should contain the "body" of the analysis. It can contain
   // simple or elaborate selection criteria, run algorithms on the data
   // of the event and typically fill histograms.
   //
   // The processing can be stopped by calling Abort().
   //
   // Use fStatus to set the return value of TTree::Process().
   //
   // The return value is currently not used.

   GetEntry(entry);

   for (Int_t i=0; i<kNumberOfDetector;i++)
   {
   	for (Int_t j=0; j<kMaxNumberOfClusters;j++)
	{
	pos[i][j]=-999.;
	erPos[i][j]=-1.;
	}
   }

   RecoEventInfo.EventNumber          =   EventInfo_EventNumber       ;
   RecoEventInfo.TriggerNumber        =   EventInfo_TriggerNumber     ;
   RecoEventInfo.TimeStamp            =   EventInfo_TimeStamp         ;
   RecoEventInfo.BunchCounter         =   EventInfo_BunchCounter      ;
   RecoEventInfo.EventCounter         =   EventInfo_EventCounter      ;
   ncl[0] = kMaxNumberOfClusters;
   ncl[1] = kMaxNumberOfClusters;
   ncl[2] = kMaxNumberOfClusters;
   ncl[3] = kMaxNumberOfClusters;
   ncl[4] = kMaxNumberOfClusters;
   ncl[5] = kMaxNumberOfClusters;


   if (g1xcl_ <= kMaxNumberOfClusters) {ncl[0] = g1xcl_;} 
	else{cout << "WARNING: Event "<<RecoEventInfo.EventNumber<< ", ncl[0] has "<<g1xcl_<< " Clusters that has been limited to " <<kMaxNumberOfClusters<<endl;};
   if (g1ycl_ <= kMaxNumberOfClusters) {ncl[1] = g1ycl_;} 
	else{cout << "WARNING: Event "<<RecoEventInfo.EventNumber<< ", ncl[1] has "<<g1ycl_<< " Clusters that has been limited to " <<kMaxNumberOfClusters<<endl;};
   if (g2xcl_ <= kMaxNumberOfClusters) {ncl[2] = g2xcl_;} 
	else{cout << "WARNING: Event "<<RecoEventInfo.EventNumber<< ", ncl[2] has "<<g2xcl_<< " Clusters that has been limited to " <<kMaxNumberOfClusters<<endl;};
   if (g2ycl_ <= kMaxNumberOfClusters) {ncl[3] = g2ycl_;} 
	else{cout << "WARNING: Event "<<RecoEventInfo.EventNumber<< ", ncl[3] has "<<g2ycl_<< " Clusters that has been limited to " <<kMaxNumberOfClusters<<endl;};
   if (g4xcl_ <= kMaxNumberOfClusters) {ncl[4] = g4xcl_;} 
	else{cout << "WARNING: Event "<<RecoEventInfo.EventNumber<< ", ncl[4] has "<<g4xcl_<< " Clusters that has been limited to " <<kMaxNumberOfClusters<<endl;};
   if (g4ycl_ <= kMaxNumberOfClusters) {ncl[5] = g4ycl_;} 
	else{cout << "WARNING: Event "<<RecoEventInfo.EventNumber<< ", ncl[5] has "<<g4ycl_<< " Clusters that has been limited to " <<kMaxNumberOfClusters<<endl;};
 
//   cout <<"____________________________________________________"<<endl;
//   cout << "Entry	"<< entry << endl;
//   cout << "ncl[0]	"<< ncl[0] << endl;
//   cout << "ncl[1]	"<< ncl[1] << endl;
//   cout << "ncl[2]	"<< ncl[2] << endl;
//   cout << "ncl[3]	"<< ncl[3] << endl;
//   cout << "ncl[4]	"<< ncl[4] << endl;
//   cout << "ncl[5]	"<< ncl[5] << endl;
   for (int icluster=0; icluster<ncl[0]; icluster++)
   {
	pos[0][icluster] = g1xcl_geoposX[icluster];
        erPos[0][icluster] = kPitch/TMath::Sqrt(12);
//   cout <<"----------------------------------------------------"<<endl;
//   	cout << "ncl[0]	"<< ncl[0] << endl;
//	cout << "cluster: :"<< icluster << "	pos: "<< pos[0][icluster] << "	erPos: " << erPos[0][icluster] << endl;
//   cout <<"----------------------------------------------------"<<endl;
   }
   for (int icluster=0; icluster<ncl[1]; icluster++)
   {
	pos[1][icluster] = g1ycl_geoposY[icluster];
        erPos[1][icluster] = kPitch/TMath::Sqrt(12);
//   cout <<"----------------------------------------------------"<<endl;
//	cout << "ncl[1]	"<< ncl[1] << endl;
//	cout << "cluster: :"<< icluster << "	pos: "<< pos[1][icluster] << "	erPos: " << erPos[1][icluster] << endl;
//   cout <<"----------------------------------------------------"<<endl;
   }
   for (int icluster=0; icluster<ncl[2]; icluster++)
   {
	pos[2][icluster] = g2xcl_geoposX[icluster];
        erPos[2][icluster] = kPitch/TMath::Sqrt(12);
   }
   for (int icluster=0; icluster<ncl[3]; icluster++)
   {
	pos[3][icluster] = g2ycl_geoposY[icluster];
        erPos[3][icluster] = kPitch/TMath::Sqrt(12);
   }
   for (int icluster=0; icluster<ncl[4]; icluster++)
   {
	pos[4][icluster] = g4xcl_geoposX[icluster];
        erPos[4][icluster] = kPitch/TMath::Sqrt(12);
   }
   for (int icluster=0; icluster<ncl[5]; icluster++)
   {
	pos[5][icluster] = g4ycl_geoposY[icluster];
        erPos[5][icluster] = kPitch/TMath::Sqrt(12);
   }

   treeForTracks->Fill();
   return kTRUE;
}

void DataForTracking::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void DataForTracking::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.
  treeForTracks->Write();
  treeForTracks->Print();
  outFile->Close();
  
  cout << "File "<< outFileName << " saved."<< endl;
  cout << "To open it..." << endl;
  cout << "TFile *file0 = TFile::Open(\""<< outFileName <<"\"); file0.ls()"<< endl;
}
