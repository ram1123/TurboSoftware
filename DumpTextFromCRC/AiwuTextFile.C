#define AiwuTextFile_cxx
#include "AiwuTextFile.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>


void AiwuTextFile::Loop()
{
//   In a ROOT session, you can do:
//      root> .L AiwuTextFile.C
//      root> AiwuTextFile t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//    Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
//
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();


   Long64_t nbytes = 0, nb = 0;
   bool verbose = 0;

   //================================	Event Loop Starts   ======================================================
    int count_ngeoch_occ = 0;
    int EventNb = 0;
   //for (Long64_t jentry=0; jentry<nentries;jentry++) {
   for (Long64_t jentry=0; jentry<17;jentry++) {
  //     if (jentry<11) continue;

      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      //============================= count number of actual clusters =======================================
      //
      int NumCluster = 0;
      for(int nbcl=0;nbcl<12;nbcl++)
      {
	  if (verbose)
	      cout<<g1xcl_geoposch[nbcl]<<endl;
	  if (g1xcl_geoposch[nbcl]==0)
	      break;
	  NumCluster += 1;
      }
      if (verbose)
	  cout<<"Actual number of clusters = "<<NumCluster<<endl;
      std::fill_n(g1xcl_geoposch,sizeof g1xcl_geoposch/sizeof(g1xcl_geoposch[0]),0);
      if (NumCluster != 1) 
	  continue;
      EventNb += 1;
      //cout<<"EventNb "<<EventNb<<endl;
      cout<<"EventNb "<<jentry<<endl;
      //
      //
      //
   //================================	Reference Tracker 1 (g1xcl)   ======================================================
      cout<<"g1xcl\t";
      int channelFired = 0;
      for(Int_t nch=0;nch<12;nch++)
      {
	  if (g1xcl_ngeoch[nch]==0)
	      break;
	  channelFired +=g1xcl_ngeoch[nch];
	  
      }
      std::cout<<channelFired<<"\t"<<"Edit1\t"<<"Edit2\t"<<"Edit3\t";
    count_ngeoch_occ = 0;
    //cout<<"\n\nsize = "<<sizeof(g1xcl_geoch)/sizeof(g1xcl_geoch[0])<<"\t"<<sizeof(g1xcl_geoch[0])/sizeof(g1xcl_geoch[0][0])<<"\n\n"<<endl;
    for(Int_t nch=0;nch<12;nch++)
    {
	if (g1xcl_ngeoch[nch]==0)
	break;
    for (int chfird=0;chfird<g1xcl_ngeoch[nch];chfird++)
    {
	if((g1xcl_geoch)[count_ngeoch_occ][chfird] == 0)
	    break;
	std::cout<<(g1xcl_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
    }
    count_ngeoch_occ += 1;
    }
    std::cout<<std::endl;
    //===============================	Clear array g1xcl_geoch		============
    //
    //Trying to use some shortcut method to delete the memory but did not succeed so apply simple method
    //
    //memset(g1xcl_geoch, 0, sizeof(g1xcl_geoch[0][0]) * count_ngeoch_occ * 12);
    //memset(g1xcl_geoch, sizeof(int)*count_ngeoch_occ*12);
    //delete[] g1xcl_geoch; g1xcl_geoch = NULL;
    count_ngeoch_occ = 0;
    for(Int_t nch=0;nch<12;nch++)
    {
	if (g1xcl_ngeoch[nch]==0)
	break;
    for (int chfird=0;chfird<g1xcl_ngeoch[nch];chfird++)
    {
	if((g1xcl_geoch)[count_ngeoch_occ][chfird] == 0)
	    break;
	g1xcl_geoch[count_ngeoch_occ][chfird]= 0;
    }
    count_ngeoch_occ += 1;
    }
    
    
      /*
       //================================	Reference Tracker 1 (g1ycl)   ======================================================
      cout<<"g1ycl\t";
      channelFired = 0;
      for(Int_t nch=0;nch<12;nch++)
      {
	  if (g1ycl_ngeoch[nch]==0)
	      break;
	  channelFired +=g1ycl_ngeoch[nch];
	  
      }
      std::cout<<channelFired<<"\t"<<"Edit1\t"<<"Edit2\t"<<"Edit3\t";
    count_ngeoch_occ = 0;
    for(Int_t nch=0;nch<12;nch++)
    {
	if (g1ycl_ngeoch[nch]==0)
	break;
    for (int chfird=0;chfird<g1ycl_ngeoch[nch];chfird++)
    {
	if((g1ycl_geoch)[count_ngeoch_occ][chfird] == 0)
	    break;
	std::cout<<(g1ycl_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
    	
    }
    count_ngeoch_occ += 1;
    }
    std::cout<<std::endl;
   //================================	Reference Tracker 2 (g2xcl)   ======================================================
          cout<<"g2xcl\t";
      channelFired = 0;
      for(Int_t nch=0;nch<12;nch++)
      {
	  if (g2xcl_ngeoch[nch]==0)
	      break;
	  channelFired +=g2xcl_ngeoch[nch];
	  
      }
      std::cout<<channelFired<<"\t"<<"Edit1\t"<<"Edit2\t"<<"Edit3\t";
    count_ngeoch_occ = 0;
    for(Int_t nch=0;nch<12;nch++)
    {
	if (g2xcl_ngeoch[nch]==0)
	break;
    for (int chfird=0;chfird<g2xcl_ngeoch[nch];chfird++)
    {
	if((g2xcl_geoch)[count_ngeoch_occ][chfird] == 0)
	    break;
	std::cout<<(g2xcl_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
    	
    }
    count_ngeoch_occ += 1;
    }
    std::cout<<std::endl;
       //================================	Reference Tracker 2 (g2ycl)   ======================================================
          cout<<"g2ycl\t";
      channelFired = 0;
      for(Int_t nch=0;nch<12;nch++)
      {
	  if (g2ycl_ngeoch[nch]==0)
	      break;
	  channelFired +=g2ycl_ngeoch[nch];
	  
      }
      std::cout<<channelFired<<"\t"<<"Edit1\t"<<"Edit2\t"<<"Edit3\t";
    count_ngeoch_occ = 0;
    for(Int_t nch=0;nch<12;nch++)
    {
	if (g2ycl_ngeoch[nch]==0)
	break;
    for (int chfird=0;chfird<g2ycl_ngeoch[nch];chfird++)
    {
	if((g2ycl_geoch)[count_ngeoch_occ][chfird] == 0)
	    break;
	std::cout<<(g2ycl_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
    	
    }
    count_ngeoch_occ += 1;
    }
    std::cout<<std::endl;
   //================================	Reference Tracker 3 (g3xcl)   ======================================================
          cout<<"g3xcl\t";
      channelFired = 0;
      for(Int_t nch=0;nch<12;nch++)
      {
	  if (g3xcl_ngeoch[nch]==0)
	      break;
	  channelFired +=g3xcl_ngeoch[nch];
	  
      }
      std::cout<<channelFired<<"\t"<<"Edit1\t"<<"Edit2\t"<<"Edit3\t";
    count_ngeoch_occ = 0;
    for(Int_t nch=0;nch<12;nch++)
    {
	if (g3xcl_ngeoch[nch]==0)
	break;
    for (int chfird=0;chfird<g3xcl_ngeoch[nch];chfird++)
    {
	if((g3xcl_geoch)[count_ngeoch_occ][chfird] == 0)
	    break;
	std::cout<<(g3xcl_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
    	
    }
    count_ngeoch_occ += 1;
    }
    std::cout<<std::endl;
   //================================	Reference Tracker 3 (g3ycl)   ======================================================
          cout<<"g3ycl\t";
      channelFired = 0;
      for(Int_t nch=0;nch<12;nch++)
      {
	  if (g3ycl_ngeoch[nch]==0)
	      break;
	  channelFired +=g3ycl_ngeoch[nch];
	  
      }
      std::cout<<channelFired<<"\t"<<"Edit1\t"<<"Edit2\t"<<"Edit3\t";
    count_ngeoch_occ = 0;
    for(Int_t nch=0;nch<12;nch++)
    {
	if (g3ycl_ngeoch[nch]==0)
	break;
    for (int chfird=0;chfird<g3ycl_ngeoch[nch];chfird++)
    {
	if((g3ycl_geoch)[count_ngeoch_occ][chfird] == 0)
	    break;
	std::cout<<(g3ycl_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
    	
    }
    count_ngeoch_occ += 1;
    }
    std::cout<<std::endl;
   //================================	Large GEM 1 (sCMSNS2LC1)   ======================================================
          cout<<"sCMSNS2LC1\t";
      channelFired = 0;
      for(Int_t nch=0;nch<12;nch++)
      {
	  if (sCMSNS2LC1_ngeoch[nch]==0)
	      break;
	  channelFired +=sCMSNS2LC1_ngeoch[nch];
	  
      }
      std::cout<<channelFired<<"\t"<<"Edit1\t"<<"Edit2\t"<<"Edit3\t";
    count_ngeoch_occ = 0;
    for(Int_t nch=0;nch<12;nch++)
    {
	if (sCMSNS2LC1_ngeoch[nch]==0)
	break;
    for (int chfird=0;chfird<sCMSNS2LC1_ngeoch[nch];chfird++)
    {
	if((sCMSNS2LC1_geoch)[count_ngeoch_occ][chfird] == 0)
	    break;
	std::cout<<(sCMSNS2LC1_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
    	
    }
    count_ngeoch_occ += 1;
    }
    std::cout<<std::endl;
       //================================   Large GEM 2 (sCMSNS2LC2)   ======================================================
          cout<<"sCMSNS2LC2\t";
      channelFired = 0;
      for(Int_t nch=0;nch<12;nch++)
      {
	  if (sCMSNS2LC2_ngeoch[nch]==0)
	      break;
	  channelFired +=sCMSNS2LC2_ngeoch[nch];
	  
      }
      std::cout<<channelFired<<"\t"<<"Edit1\t"<<"Edit2\t"<<"Edit3\t";
    count_ngeoch_occ = 0;
    for(Int_t nch=0;nch<12;nch++)
    {
	if (sCMSNS2LC2_ngeoch[nch]==0)
	break;
    for (int chfird=0;chfird<sCMSNS2LC2_ngeoch[nch];chfird++)
    {
	if((sCMSNS2LC2_geoch)[count_ngeoch_occ][chfird] == 0)
	    break;
	std::cout<<(sCMSNS2LC2_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
    	
    }
    count_ngeoch_occ += 1;
    }
    std::cout<<std::endl;
       //================================   Large GEM 2 (sCMSNS2LC2_L)   ======================================================
          cout<<"sCMSNS2LC2_L\t";
      channelFired = 0;
      for(Int_t nch=0;nch<12;nch++)
      {
	  if (sCMSNS2LC2_L_ngeoch[nch]==0)
	      break;
	  channelFired +=sCMSNS2LC2_L_ngeoch[nch];
	  
      }
      std::cout<<channelFired<<"\t"<<"Edit1\t"<<"Edit2\t"<<"Edit3\t";
    count_ngeoch_occ = 0;
    for(Int_t nch=0;nch<12;nch++)
    {
	if (sCMSNS2LC2_L_ngeoch[nch]==0)
	break;
    for (int chfird=0;chfird<sCMSNS2LC2_L_ngeoch[nch];chfird++)
    {
	if((sCMSNS2LC2_L_geoch)[count_ngeoch_occ][chfird] == 0)
	    break;
	std::cout<<(sCMSNS2LC2_L_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
    	
    }
    count_ngeoch_occ += 1;
    }
    std::cout<<std::endl;
       //================================   Large GEM 2 (sCMSNS2LC2_R)   ======================================================
          cout<<"sCMSNS2LC2_R\t";
      channelFired = 0;
      for(Int_t nch=0;nch<12;nch++)
      {
	  if (sCMSNS2LC2_R_ngeoch[nch]==0)
	      break;
	  channelFired +=sCMSNS2LC2_R_ngeoch[nch];
	  
      }
      std::cout<<channelFired<<"\t"<<"Edit1\t"<<"Edit2\t"<<"Edit3\t";
    count_ngeoch_occ = 0;
    for(Int_t nch=0;nch<12;nch++)
    {
	if (sCMSNS2LC2_R_ngeoch[nch]==0)
	break;
    for (int chfird=0;chfird<sCMSNS2LC2_R_ngeoch[nch];chfird++)
    {
	if((sCMSNS2LC2_R_geoch)[count_ngeoch_occ][chfird] == 0)
	    break;
	std::cout<<(sCMSNS2LC2_R_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
    	
    }
    count_ngeoch_occ += 1;
    }
    std::cout<<std::endl;    
       //================================	Large GEM 3 (sCMSNS2LC3)   ======================================================
          cout<<"sCMSNS2LC3\t";
      channelFired = 0;
      for(Int_t nch=0;nch<12;nch++)
      {
	  if (sCMSNS2LC3_ngeoch[nch]==0)
	      break;
	  channelFired +=sCMSNS2LC3_ngeoch[nch];
	  
      }
      std::cout<<channelFired<<"\t"<<"Edit1\t"<<"Edit2\t"<<"Edit3\t";
    count_ngeoch_occ = 0;
    for(Int_t nch=0;nch<12;nch++)
    {
	if (sCMSNS2LC3_ngeoch[nch]==0)
	break;
    for (int chfird=0;chfird<sCMSNS2LC3_ngeoch[nch];chfird++)
    {
	if((sCMSNS2LC3_geoch)[count_ngeoch_occ][chfird] == 0)
	    break;
	std::cout<<(sCMSNS2LC3_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
    	
    }
    count_ngeoch_occ += 1;
    }
    std::cout<<std::endl;
    */
   }
}
