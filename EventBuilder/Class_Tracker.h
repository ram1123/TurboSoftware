//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Nov  3 12:42:32 2014 by ROOT version 5.34/20
// from TTree trackertree/TrackFinder routine results
// found on file: /afs/cern.ch/user/r/rasharma/work/TurboSoftware/EventBuilder/OutPutData/Run1120_Muon_10k_MSPL1_Sync_HVScan_550pt2_550pt2_550pt1_T20_T20_T20_Lat25/RECO-CRC-Run1120_Muon_10k_MSPL1_Sync_HVScan_550pt2_550pt2_550pt1_T20_T20_T20_Lat25-141013_203356-0.root
//////////////////////////////////////////////////////////

#ifndef Class_Tracker_h
#define Class_Tracker_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <TClonesArray.h>

// Fixed size dimensions of array or collections stored in the TTree if any.
   const Int_t kMaxtrackx = 1;
   const Int_t kMaxtracky = 1;

class Class_Tracker {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           TrackFinder_EventInfo_EventNumber;
   Int_t           TrackFinder_EventInfo_TriggerNumber;
   Int_t           TrackFinder_EventInfo_TimeStamp;
   Int_t           TrackFinder_EventInfo_BunchCounter;
   Int_t           TrackFinder_EventInfo_EventCounter;
   Int_t           trackx_;
   Double32_t      trackx_m[kMaxtrackx];   //[trackx_]
   Double32_t      trackx_q[kMaxtrackx];   //[trackx_]
   Double32_t      trackx_chi2[kMaxtrackx];   //[trackx_]
   Double32_t      trackx_ndf[kMaxtrackx];   //[trackx_]
   Double_t        residualx[5];
   Int_t           tracky_;
   Double32_t      tracky_m[kMaxtracky];   //[tracky_]
   Double32_t      tracky_q[kMaxtracky];   //[tracky_]
   Double32_t      tracky_chi2[kMaxtracky];   //[tracky_]
   Double32_t      tracky_ndf[kMaxtracky];   //[tracky_]
   Double_t        residualy[5];

   // List of branches
   TBranch        *b_TrackFinder_EventInfo;   //!
   TBranch        *b_trackx_;   //!
   TBranch        *b_trackx_m;   //!
   TBranch        *b_trackx_q;   //!
   TBranch        *b_trackx_chi2;   //!
   TBranch        *b_trackx_ndf;   //!
   TBranch        *b_residualx;   //!
   TBranch        *b_tracky_;   //!
   TBranch        *b_tracky_m;   //!
   TBranch        *b_tracky_q;   //!
   TBranch        *b_tracky_chi2;   //!
   TBranch        *b_tracky_ndf;   //!
   TBranch        *b_residualy;   //!

   Class_Tracker(TTree *tree=0);
   virtual ~Class_Tracker();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef Class_Tracker_cxx
Class_Tracker::Class_Tracker(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/afs/cern.ch/user/r/rasharma/work/TurboSoftware/EventBuilder/OutPutData/Run1120_Muon_10k_MSPL1_Sync_HVScan_550pt2_550pt2_550pt1_T20_T20_T20_Lat25/RECO-CRC-Run1120_Muon_10k_MSPL1_Sync_HVScan_550pt2_550pt2_550pt1_T20_T20_T20_Lat25-141013_203356-0.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/afs/cern.ch/user/r/rasharma/work/TurboSoftware/EventBuilder/OutPutData/Run1120_Muon_10k_MSPL1_Sync_HVScan_550pt2_550pt2_550pt1_T20_T20_T20_Lat25/RECO-CRC-Run1120_Muon_10k_MSPL1_Sync_HVScan_550pt2_550pt2_550pt1_T20_T20_T20_Lat25-141013_203356-0.root");
      }
      f->GetObject("trackertree",tree);

   }
   Init(tree);
}

Class_Tracker::~Class_Tracker()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Class_Tracker::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Class_Tracker::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void Class_Tracker::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("TrackFinder_EventInfo", &TrackFinder_EventInfo_EventNumber, &b_TrackFinder_EventInfo);
   fChain->SetBranchAddress("trackx", &trackx_, &b_trackx_);
   fChain->SetBranchAddress("trackx.m", trackx_m, &b_trackx_m);
   fChain->SetBranchAddress("trackx.q", trackx_q, &b_trackx_q);
   fChain->SetBranchAddress("trackx.chi2", trackx_chi2, &b_trackx_chi2);
   fChain->SetBranchAddress("trackx.ndf", trackx_ndf, &b_trackx_ndf);
   fChain->SetBranchAddress("residualx", residualx, &b_residualx);
   fChain->SetBranchAddress("tracky", &tracky_, &b_tracky_);
   fChain->SetBranchAddress("tracky.m", tracky_m, &b_tracky_m);
   fChain->SetBranchAddress("tracky.q", tracky_q, &b_tracky_q);
   fChain->SetBranchAddress("tracky.chi2", tracky_chi2, &b_tracky_chi2);
   fChain->SetBranchAddress("tracky.ndf", tracky_ndf, &b_tracky_ndf);
   fChain->SetBranchAddress("residualy", residualy, &b_residualy);
   Notify();
}

Bool_t Class_Tracker::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Class_Tracker::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Class_Tracker::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Class_Tracker_cxx
