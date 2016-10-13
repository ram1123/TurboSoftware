//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Sep 10 11:24:03 2011 by ROOT version 5.27/04
// from TTree recotree/RecoGeonstruction routine results
// found on file: reco.root
//////////////////////////////////////////////////////////

#ifndef Recotree_baseclass_h
#define Recotree_baseclass_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
   const Int_t kMaxtrackx = 1;
   const Int_t kMaxtracky = 1;

class Recotree_baseclass : public TSelector {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain

   // Declaration of leaf types
   Int_t           RecoGeoEventInfo_EventNumber;
   Int_t           RecoGeoEventInfo_TriggerNumber;
   Int_t           RecoGeoEventInfo_TimeStamp;
   Int_t           RecoGeoEventInfo_BunchCounter;
   Int_t           RecoGeoEventInfo_EventCounter;
   Int_t           trackx_;
   Double32_t      trackx_m[kMaxtrackx];   //[trackx_]
   Double32_t      trackx_q[kMaxtrackx];   //[trackx_]
   Double32_t      trackx_chi2[kMaxtrackx];   //[trackx_]
   Double32_t      trackx_ndf[kMaxtrackx];   //[trackx_]
   Double_t        residualx[4];
   Int_t           tracky_;
   Double32_t      tracky_m[kMaxtracky];   //[tracky_]
   Double32_t      tracky_q[kMaxtracky];   //[tracky_]
   Double32_t      tracky_chi2[kMaxtracky];   //[tracky_]
   Double32_t      tracky_ndf[kMaxtracky];   //[tracky_]
   Double_t        residualy[4];

   // List of branches
   TBranch        *b_RecoGeoEventInfo;   //!
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

   Recotree_baseclass(TTree * /*tree*/ =0) { }
   virtual ~Recotree_baseclass() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();

   ClassDef(Recotree_baseclass,0);
};

#endif

#ifdef Recotree_baseclass_cxx
void Recotree_baseclass::Init(TTree *tree)
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
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("RecoGeoEventInfo", &RecoGeoEventInfo_EventNumber, &b_RecoGeoEventInfo);
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
}

Bool_t Recotree_baseclass::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef Recotree_baseclass_cxx
