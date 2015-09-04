#define AiwuTextFile_cxx
#include "AiwuTextFile.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

//int main()
//{
//    gROOT->ProcessLine(.L AiwuTextFile.C);
//    AiwuTextFile t;
//    t.Loop();
//}

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
cout<< "Total "<<nentries<<endl;
   // create a text file
   //
   std::ofstream file_out("Hit_Position_Info.txt");
   if (!file_out){
       std::cout << "error: Could not open the file Hit_Position_Info.txt" << std::endl;
   }

   Long64_t nbytes = 0, nb = 0;
   bool verbose = 0;
   //================================	Event Loop Starts   ======================================================
    int count_ngeoch_occ = 0;
    int EventNb = 0;
    int g1x_Hit_count = 0 ;
    int g1y_Hit_count = 0 ;
    int g2x_Hit_count = 0 ;
    int g2y_Hit_count = 0 ;
    int g3x_Hit_count = 0 ;
    int g3y_Hit_count = 0 ;
    int g1_Hit_count = 0 ;   
    int g2_Hit_count = 0 ;
    int g3_Hit_count = 0 ;   
    int LC1_Hit_count = 0 ;
    int LC2_Hit_count = 0 ;
    int LC3_Hit_count = 0 ;

//cout<<"#Detector\tFired Strip\tTot Charge\tCls Pos(mm)\tCls Pos (stripno)\tStripNo\tCharge"<<endl;
    //cout<<"#Detector\tFired Strip\tTot Charge\tCls Pos(mm)\tCls Pos (stripno)\tStripNo\tCharge"<<endl;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
   //for (Long64_t jentry=0; jentry<33;jentry++) {
//	if (jentry>1193) continue;
	//if (jentry>22) continue;

      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      //============================= count number of actual clusters for each Tracker and Large GEMs	=======================================
      //
      /*    
       *    This loops added because presently Aiwu's framework can only accepts those events for which
       *    there are only cluster in each tracker and GEM for each event
       */
      //=========   Check Number of Clusters For g1xcl	============================
      //
      //
      int NumCluster_g1x = 0;
      for(int nbcl=0;nbcl<kMaxg1xcl;nbcl++)
      {
	  if (verbose)
	      cout<<g1xcl_geoposch[nbcl]<<endl;
	  if (g1xcl_geoposch[nbcl]==0)
	      break;
	  NumCluster_g1x += 1;
     } 

if (NumCluster_g1x !=0 ) 
{
           g1x_Hit_count++;
//cout<<"g1x_hits "<<g1x_Hit_count<<endl;
//cout<<"efficiency_g1x "<<(float) g1x_Hit_count/(float) nentries<<endl;
}

      if (verbose)
	  cout<<"Actual number of clusters = "<<NumCluster_g1x<<endl;
	// if (NumCluster_g1x != 1) 
	//  continue;

      //
      //
      //=========   END:: Check Number of Clusters For g1xcl	============================
      //=========   Check Number of Clusters For g1ycl	============================
      //
      //
      int NumCluster_g1y = 0;
      for(int nbcl=0;nbcl<kMaxg1ycl;nbcl++)
      {
	  if (verbose)
	      cout<<g1ycl_geoposch[nbcl]<<endl;
	  if (g1ycl_geoposch[nbcl]==0)
	      break;
	  NumCluster_g1y += 1;
}
if (NumCluster_g1y !=0 )
{
           g1y_Hit_count++;
//cout<<"g1y_hits "<<g1y_Hit_count<<endl;
//cout<<"efficiency_g1y "<<(float) g1y_Hit_count/(float) nentries<<endl;

}



if (NumCluster_g1x !=0 && NumCluster_g1y !=0)
    {       g1_Hit_count++;
}

      if (verbose)
	  cout<<"Actual number of clusters = "<<NumCluster_g1y<<endl;
	// if (NumCluster_g1y != 1) 
	//  continue;

      //
      //
      //=========   END:: Check Number of Clusters For g1ycl	============================
      //=========   Check Number of Clusters For g2xcl	============================
      //
      //
      int NumCluster_g2x = 0;
      for(int nbcl=0;nbcl<kMaxg2xcl;nbcl++)
      {
	  if (verbose)
	      cout<<g2xcl_geoposch[nbcl]<<endl;
	  if (g2xcl_geoposch[nbcl]==0)
	      break;
	  NumCluster_g2x += 1;
}
if (NumCluster_g2x !=0 )
{
           g2x_Hit_count++;
//cout<<"g2x_hits "<<g2x_Hit_count<<endl;
//cout<<"efficiency_g2x "<<(float) g2x_Hit_count/(float) nentries<<endl;
}
 
      if (verbose)
	  cout<<"Actual number of clusters = "<<NumCluster_g2x<<endl;
	// if (NumCluster_g2x != 1) 
	//  continue;

      //
      //
      //=========   END:: Check Number of Clusters For g2xcl	============================
      //=========   Check Number of Clusters For g2ycl	============================
      //
      //
      int NumCluster_g2y = 0;
      for(int nbcl=0;nbcl<kMaxg2ycl;nbcl++)
      {
	  if (verbose)
	      cout<<g2ycl_geoposch[nbcl]<<endl;
	  if (g2ycl_geoposch[nbcl]==0)
	      break;
	  NumCluster_g2y += 1;
}
 if (NumCluster_g2y !=0 )
{
           g2y_Hit_count++;
//cout<<"g2y_hits "<<g2y_Hit_count<<endl;
//cout<<"efficiency_g2y "<<(float) g2y_Hit_count/(float) nentries<<endl;
}
 
if (NumCluster_g2x !=0 && NumCluster_g2y !=0)
    {       g2_Hit_count++;
}

      if (verbose)
	  cout<<"Actual number of clusters = "<<NumCluster_g2y<<endl;
	// if (NumCluster_g2y != 1) 
	//  continue;


      //=========   END:: Check Number of Clusters For g2ycl	============================
      //=========   Check Number of Clusters For g3xcl	============================
      //
      //
      int NumCluster_g3x = 0;
      for(int nbcl=0;nbcl<kMaxg3xcl;nbcl++)
      {
	  if (verbose)
	      cout<<g3xcl_geoposch[nbcl]<<endl;
	  if (g3xcl_geoposch[nbcl]==0)
	      break;
	  NumCluster_g3x += 1;

}
if (NumCluster_g3x !=0 )
{
           g3x_Hit_count++;
//cout<<"g3x_hits "<<g3x_Hit_count<<endl;
//cout<<"efficiency_g3x "<<(float) g3x_Hit_count/(float) nentries<<endl;
}
 
      if (verbose)
	  cout<<"Actual number of clusters = "<<NumCluster_g3x<<endl;
	// if (NumCluster_g3x != 1) 
	//  continue;

      //=========   END:: Check Number of Clusters For g3xcl	============================
      //=========   Check Number of Clusters For g3ycl	============================
      //
      //
      int NumCluster_g3y = 0;
      for(int nbcl=0;nbcl<kMaxg3ycl;nbcl++)
      {
	  if (verbose)
	      cout<<g3ycl_geoposch[nbcl]<<endl;
	  if (g3ycl_geoposch[nbcl]==0)
	      break;
	  NumCluster_g3y += 1;
}
 if (NumCluster_g3y !=0 )
{
           g3y_Hit_count++;
//cout<<"g3y_hits "<<g3y_Hit_count<<endl;
//cout<<"efficiency_g3y "<<(float) g3y_Hit_count/(float) nentries<<endl;
}
 if (NumCluster_g3x !=0 && NumCluster_g3y !=0)
    {       g3_Hit_count++;
}

      if (verbose)
	  cout<<"Actual number of clusters = "<<NumCluster_g3y<<endl;


/* if (NumCluster_g1x !=0 && NumCluster_g1y !=0 )
{
           g1_Hit_count++;
cout<<"NumCluster_g1x: "<<NumCluster_g1x<<"   "<<"NumCluster_g1y: "<<NumCluster_g1y<<endl;
//cout<<"g1_hits "<<g1_Hit_count<<endl;
//cout<<"efficiency_g1 "<<(float) g1_Hit_count/(float) nentries<<endl;
}*/

	// if (NumCluster_g3y != 1) 
	//  continue;


      //=========   END:: Check Number of Clusters For g3ycl	============================
      //=========   Check Number of Clusters For sCMSNS2LC1	============================
      //
      //
      int NumCluster_LC1 = 0;
      for(int nbcl=0;nbcl<kMaxsCMSNS2LC1;nbcl++)
      {
	  if (verbose)
	      cout<<sCMSNS2LC1_geoposch[nbcl]<<endl;
	  if (sCMSNS2LC1_geoposch[nbcl]==0)
	      break;
	  NumCluster_LC1 += 1;
      }
if (NumCluster_LC1 !=0)
{
  LC1_Hit_count++;
} 

      if (verbose)
	  cout<<"Actual number of clusters = "<<NumCluster_LC1<<endl;
	// if (NumCluster_LC1 != 1) 
	//  continue;

      //=========   END:: Check Number of Clusters For sCMSNS2LC1	============================
      //=========   Check Number of Clusters For sCMSNS2LC2	============================

      int NumCluster_LC2 = 0;
      for(int nbcl=0;nbcl<kMaxsCMSNS2LC2;nbcl++)
      {
	  if (verbose)
	      cout<<sCMSNS2LC2_geoposch[nbcl]<<endl;
	  if (sCMSNS2LC2_geoposch[nbcl]==0)
	      break;
	  NumCluster_LC2 += 1;
      }

if (NumCluster_LC2 !=0)
{
  LC2_Hit_count++;
}

      if (verbose)
	  cout<<"Actual number of clusters = "<<NumCluster_LC2<<endl;
	// if (NumCluster_LC2 != 1) 
	//  continue;

      //=========   END:: Check Number of Clusters For sCMSNS2LC2	============================
      //=========   Check Number of Clusters For sCMSNS2LC3	============================
      int NumCluster_LC3 = 0;
      for(int nbcl=0;nbcl<kMaxsCMSNS2LC3;nbcl++)
      {
	  if (verbose)
	      cout<<sCMSNS2LC3_geoposch[nbcl]<<endl;
	  if (sCMSNS2LC3_geoposch[nbcl]==0)
	      break;
	  NumCluster_LC3 += 1;
      }

if (NumCluster_LC3 !=0)
{
  LC3_Hit_count++;
}
     if (verbose)
	  cout<<"Actual number of clusters = "<<NumCluster_LC3<<endl;
	// if (NumCluster_LC3 != 1) 
	//  continue;

      //
      //
      //=========   END:: Check Number of Clusters For sCMSNS2LC3	============================    
      //cout<<"EventNb "<<jentry<<endl;
 
      //if (NumCluster_g1x == 1 &&  NumCluster_g1y ==1 && NumCluster_g2x == 1 && NumCluster_g2y==1 && NumCluster_g3x ==1 && NumCluster_g3y == 1)
      if (NumCluster_g1x == 1 &&  NumCluster_g1y ==1 && NumCluster_g2x == 1 && NumCluster_g2y==1 && NumCluster_g3x ==1 && NumCluster_g3y == 1 && NumCluster_LC1 == 1 && NumCluster_LC2 == 1 && NumCluster_LC3 == 1)
      {
	  EventNb += 1;
	  if (verbose)
	      cout<<"EventNb "<<EventNb<<endl;
	      //cout<<"EventNb "<<EventNb<<"\tActual EvtNumber = "<< jentry <<endl;
	      //cout<<"EventNb "<<jentry<<endl;
	  file_out<<"EventNb "<<EventNb<<endl;
	  //file_out<<"EventNb "<<EventNb<<"\tActual EvtNumber = "<< jentry <<endl;
      
}

   //================================	Reference Tracker 1 (g1xcl)   ======================================================
      channelFired = 0;		//==== ERROR:: ERROR:: ERROR::  I have to forcefully put channelFired = 0 at two places. If not then it behaves strangly.
      count_ngeoch_occ = 0;
      //if (NumCluster_g1x == 1 &&  NumCluster_g1y ==1 && NumCluster_g2x == 1 && NumCluster_g2y==1 && NumCluster_g3x ==1 && NumCluster_g3y == 1)
      if (NumCluster_g1x == 1 &&  NumCluster_g1y ==1 && NumCluster_g2x == 1 && NumCluster_g2y==1 && NumCluster_g3x ==1 && NumCluster_g3y == 1 && NumCluster_LC1 == 1 && NumCluster_LC2 == 1 && NumCluster_LC3 == 1)
      {
//cout<<"final "<<jentry<<endl;
          if (verbose)
              cout<<"g1xcl\t";
          file_out<<"g1xcl\t";
	  channelFired = 0;
	  for(Int_t nch=0;nch<kMaxg1xcl;nch++)
	  {
	      if (g1xcl_ngeoch[nch]==0)
		  break;
	      channelFired +=g1xcl_ngeoch[nch];
	      //cout<<"Channel Fired = "<<channelFired<<endl;
 //cout<<"effeciency "<<(float) jentry/ (float) nentries <<endl;
	  }
	  if (verbose)
	      std::cout<<channelFired<<"\t"<<channelFired<<"\t"<<g1xcl_geoposX[0]<<"\t"<<g1xcl_geoposch[0]<<"\t";
	  file_out<<channelFired<<"\t"<<channelFired<<"\t"<<g1xcl_geoposX[0]<<"\t"<<g1xcl_geoposch[0]<<"\t";
	  count_ngeoch_occ = 0;
	  for(Int_t nch=0;nch<kMaxg1xcl;nch++)
	  {
	      if (g1xcl_ngeoch[nch]==0)
		  break;
	      for (int chfird=0;chfird<g1xcl_ngeoch[nch];chfird++)
	      {
		  if((g1xcl_geoch)[count_ngeoch_occ][chfird] == 0)
		      break;
		  if (verbose)
		      std::cout<<(g1xcl_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
		  //std::cout<<(g1xcl_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
		  file_out<<(g1xcl_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
//	    cout<<"effeciency_1 "<<(float) jentry/ (float) nentries <<endl;
   }
	      count_ngeoch_occ += 1;
	  }
	  if (verbose)
	      std::cout<<std::endl;
	  // std::cout<<std::endl;
g1x = jentry ;
	  file_out<<std::endl;
 cout<<"effeciency_g1x "<<(float) jentry/ (float) nentries <<endl;
  }
   //================================	END::	Reference Tracker 1 (g1xcl)   ======================================================
   
   //================================	Reference Tracker 1 (g1ycl)   ======================================================
      channelFired = 0;		//==== ERROR:: ERROR:: ERROR::  I have to forcefully put channelFired = 0 at two places. If not then it behaves strangly.
      count_ngeoch_occ = 0;
      //if (NumCluster_g1x == 1 &&  NumCluster_g1y ==1 && NumCluster_g2x == 1 && NumCluster_g2y==1 && NumCluster_g3x ==1 && NumCluster_g3y == 1)
      if (NumCluster_g1x == 1 &&  NumCluster_g1y ==1 && NumCluster_g2x == 1 && NumCluster_g2y==1 && NumCluster_g3x ==1 && NumCluster_g3y == 1 && NumCluster_LC1 == 1 && NumCluster_LC2 == 1 && NumCluster_LC3 == 1)
      {
          if (verbose)
              cout<<"g1ycl\t";
          file_out<<"g1ycl\t";
	  channelFired = 0;
	  for(Int_t nch=0;nch<kMaxg1ycl;nch++)
	  {
	      if (g1ycl_ngeoch[nch]==0)
		  break;
	      channelFired +=g1ycl_ngeoch[nch];
	      //cout<<"Channel Fired = "<<channelFired<<endl;
	  }
	  if (verbose)
	      std::cout<<channelFired<<"\t"<<channelFired<<"\t"<<g1ycl_geoposY[0]<<"\t"<<g1ycl_geoposch[0]<<"\t";
	  file_out<<channelFired<<"\t"<<channelFired<<"\t"<<g1ycl_geoposY[0]<<"\t"<<g1ycl_geoposch[0]<<"\t";
	  count_ngeoch_occ = 0;
	  for(Int_t nch=0;nch<kMaxg1xcl;nch++)
	  {
	      if (g1ycl_ngeoch[nch]==0)
		  break;
	      for (int chfird=0;chfird<g1ycl_ngeoch[nch];chfird++)
	      {
		  if((g1ycl_geoch)[count_ngeoch_occ][chfird] == 0)
		      break;
		  if (verbose)
		      std::cout<<(g1ycl_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
		  //std::cout<<(g1ycl_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
		  file_out<<(g1ycl_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
	      }
	      count_ngeoch_occ += 1;
	  }
	  if (verbose)
	      std::cout<<std::endl;
	  // std::cout<<std::endl;
	  file_out<<std::endl;
 }


   //================================	END::	Reference Tracker 1 (g1ycl)   ======================================================    
   
   //================================	Reference Tracker 1 (g2xcl)   ======================================================
      channelFired = 0;		//==== ERROR:: ERROR:: ERROR::  I have to forcefully put channelFired = 0 at two places. If not then it behaves strangly.
      count_ngeoch_occ = 0;
      //if (NumCluster_g1x == 1 &&  NumCluster_g1y ==1 && NumCluster_g2x == 1 && NumCluster_g2y==1 && NumCluster_g3x ==1 && NumCluster_g3y == 1)
      if (NumCluster_g1x == 1 &&  NumCluster_g1y ==1 && NumCluster_g2x == 1 && NumCluster_g2y==1 && NumCluster_g3x ==1 && NumCluster_g3y == 1 && NumCluster_LC1 == 1 && NumCluster_LC2 == 1 && NumCluster_LC3 == 1)
      {
         if (verbose)
              cout<<"g2xcl\t";
          file_out<<"g2xcl\t";
	  channelFired = 0;
	  for(Int_t nch=0;nch<kMaxg2xcl;nch++)
	  {
	      if (g2xcl_ngeoch[nch]==0)
		  break;
	      channelFired +=g2xcl_ngeoch[nch];
	      //cout<<"Channel Fired = "<<channelFired<<endl;
	  }
	  if (verbose)
	      std::cout<<channelFired<<"\t"<<channelFired<<"\t"<<g2xcl_geoposX[0]<<"\t"<<g2xcl_geoposch[0]<<"\t";
	  file_out<<channelFired<<"\t"<<channelFired<<"\t"<<g2xcl_geoposX[0]<<"\t"<<g2xcl_geoposch[0]<<"\t";
	  count_ngeoch_occ = 0;
	  for(Int_t nch=0;nch<kMaxg2xcl;nch++)
	  {
	      if (g2xcl_ngeoch[nch]==0)
		  break;
	      for (int chfird=0;chfird<g2xcl_ngeoch[nch];chfird++)
	      {
		  if((g2xcl_geoch)[count_ngeoch_occ][chfird] == 0)
		      break;
		  if (verbose)
		      std::cout<<(g2xcl_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
		  //std::cout<<(g2xcl_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
		  file_out<<(g2xcl_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
	      }
	      count_ngeoch_occ += 1;
	  }
	  if (verbose)
	      std::cout<<std::endl;
	  // std::cout<<std::endl;
	  file_out<<std::endl;
   }
   //================================	END::	Reference Tracker 1 (g2xcl)   ======================================================       
   
   //================================	Reference Tracker 1 (g2ycl)   ======================================================
      channelFired = 0;		//==== ERROR:: ERROR:: ERROR::  I have to forcefully put channelFired = 0 at two places. If not then it behaves strangly.
      count_ngeoch_occ = 0;
      //if (NumCluster_g1x == 1 &&  NumCluster_g1y ==1 && NumCluster_g2x == 1 && NumCluster_g2y==1 && NumCluster_g3x ==1 && NumCluster_g3y == 1)
      if (NumCluster_g1x == 1 &&  NumCluster_g1y ==1 && NumCluster_g2x == 1 && NumCluster_g2y==1 && NumCluster_g3x ==1 && NumCluster_g3y == 1 && NumCluster_LC1 == 1 && NumCluster_LC2 == 1 && NumCluster_LC3 == 1)
      {
          if (verbose)
              cout<<"g2ycl\t";
          file_out<<"g2ycl\t";
	  channelFired = 0;
	  for(Int_t nch=0;nch<kMaxg2ycl;nch++)
	  {
	      if (g2ycl_ngeoch[nch]==0)
		  break;
	      channelFired +=g2ycl_ngeoch[nch];
	      //cout<<"Channel Fired = "<<channelFired<<endl;
	  }
	  if (verbose)
	      std::cout<<channelFired<<"\t"<<channelFired<<"\t"<<g2ycl_geoposY[0]<<"\t"<<g2ycl_geoposch[0]<<"\t";
	  file_out<<channelFired<<"\t"<<channelFired<<"\t"<<g2ycl_geoposY[0]<<"\t"<<g2ycl_geoposch[0]<<"\t";
	  count_ngeoch_occ = 0;
	  for(Int_t nch=0;nch<kMaxg2ycl;nch++)
	  {
	      if (g2ycl_ngeoch[nch]==0)
		  break;
	      for (int chfird=0;chfird<g2ycl_ngeoch[nch];chfird++)
	      {
		  if((g2ycl_geoch)[count_ngeoch_occ][chfird] == 0)
		      break;
		  if (verbose)
		      std::cout<<(g2ycl_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
		  //std::cout<<(g2ycl_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
		  file_out<<(g2ycl_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
	      }
	      count_ngeoch_occ += 1;
	  }
	  if (verbose)
	      std::cout<<std::endl;
	  // std::cout<<std::endl;
	  file_out<<std::endl;
 }
   //================================	END::	Reference Tracker 1 (g2ycl)   ======================================================    
      
   //================================	Reference Tracker 1 (g3xcl)   ======================================================
      channelFired = 0;		//==== ERROR:: ERROR:: ERROR::  I have to forcefully put channelFired = 0 at two places. If not then it behaves strangly.
      count_ngeoch_occ = 0;
      //if (NumCluster_g1x == 1 &&  NumCluster_g1y ==1 && NumCluster_g2x == 1 && NumCluster_g2y==1 && NumCluster_g3x ==1 && NumCluster_g3y == 1)
      if (NumCluster_g1x == 1 &&  NumCluster_g1y ==1 && NumCluster_g2x == 1 && NumCluster_g2y==1 && NumCluster_g3x ==1 && NumCluster_g3y == 1 && NumCluster_LC1 == 1 && NumCluster_LC2 == 1 && NumCluster_LC3 == 1)
      {
          if (verbose)
              cout<<"g3xcl\t";
          file_out<<"g3xcl\t";
	  channelFired = 0;
	  for(Int_t nch=0;nch<kMaxg3xcl;nch++)
	  {
	      if (g3xcl_ngeoch[nch]==0)
		  break;
	      channelFired +=g3xcl_ngeoch[nch];
	      //cout<<"Channel Fired = "<<channelFired<<endl;
	  }
	  if (verbose)
	      std::cout<<channelFired<<"\t"<<channelFired<<"\t"<<g3xcl_geoposX[0]<<"\t"<<g3xcl_geoposch[0]<<"\t";
	  file_out<<channelFired<<"\t"<<channelFired<<"\t"<<g3xcl_geoposX[0]<<"\t"<<g3xcl_geoposch[0]<<"\t";
	  count_ngeoch_occ = 0;
	  for(Int_t nch=0;nch<kMaxg3xcl;nch++)
	  {
	      if (g3xcl_ngeoch[nch]==0)
		  break;
	      for (int chfird=0;chfird<g3xcl_ngeoch[nch];chfird++)
	      {
		  if((g3xcl_geoch)[count_ngeoch_occ][chfird] == 0)
		      break;
		  if (verbose)
		      std::cout<<(g3xcl_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
		  //std::cout<<(g3xcl_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
		  file_out<<(g3xcl_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
	      }
	      count_ngeoch_occ += 1;
	  }
	  if (verbose)
	      std::cout<<std::endl;
	  // std::cout<<std::endl;
	  file_out<<std::endl;
 }
   //================================	END::	Reference Tracker 1 (g3xcl)   ======================================================      
   
   //================================	Reference Tracker 1 (g3ycl)   ======================================================
      channelFired = 0;		//==== ERROR:: ERROR:: ERROR::  I have to forcefully put channelFired = 0 at two places. If not then it behaves strangly.
      count_ngeoch_occ = 0;
      //if (NumCluster_g1x == 1 &&  NumCluster_g1y ==1 && NumCluster_g2x == 1 && NumCluster_g2y==1 && NumCluster_g3x ==1 && NumCluster_g3y == 1)
      if (NumCluster_g1x == 1 &&  NumCluster_g1y ==1 && NumCluster_g2x == 1 && NumCluster_g2y==1 && NumCluster_g3x ==1 && NumCluster_g3y == 1 && NumCluster_LC1 == 1 && NumCluster_LC2 == 1 && NumCluster_LC3 == 1)
      {
          if (verbose)
              cout<<"g3ycl\t";
          file_out<<"g3ycl\t";
	  channelFired = 0;
	  for(Int_t nch=0;nch<kMaxg3ycl;nch++)
	  {
	      if (g3ycl_ngeoch[nch]==0)
		  break;
	      channelFired +=g3ycl_ngeoch[nch];
	      //cout<<"Channel Fired = "<<channelFired<<endl;
	  }
	  if (verbose)
	      std::cout<<channelFired<<"\t"<<channelFired<<"\t"<<g3ycl_geoposY[0]<<"\t"<<g3ycl_geoposch[0]<<"\t";
	  file_out<<channelFired<<"\t"<<channelFired<<"\t"<<g3ycl_geoposY[0]<<"\t"<<g3ycl_geoposch[0]<<"\t";
	  count_ngeoch_occ = 0;
	  for(Int_t nch=0;nch<kMaxg3ycl;nch++)
	  {
	      if (g3ycl_ngeoch[nch]==0)
		  break;
	      for (int chfird=0;chfird<g3ycl_ngeoch[nch];chfird++)
	      {
		  if((g3ycl_geoch)[count_ngeoch_occ][chfird] == 0)
		      break;
		  if (verbose)
		      std::cout<<(g3ycl_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
		  //std::cout<<(g3ycl_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
		  file_out<<(g3ycl_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
	      }
	      count_ngeoch_occ += 1;
	  }
	  if (verbose)
	      std::cout<<std::endl;
	  // std::cout<<std::endl;
	  file_out<<std::endl;
    }
   //================================	END::	Reference Tracker 1 (g3ycl)   ======================================================    
      
   //================================	GE1/1  1 (sCMSNS2LC1)   ======================================================
      channelFired = 0;		//==== ERROR:: ERROR:: ERROR::  I have to forcefully put channelFired = 0 at two places. If not then it behaves strangly.
      count_ngeoch_occ = 0;
      //if (NumCluster_g1x == 1 &&  NumCluster_g1y ==1 && NumCluster_g2x == 1 && NumCluster_g2y==1 && NumCluster_g3x ==1 && NumCluster_g3y == 1)
      if (NumCluster_g1x == 1 &&  NumCluster_g1y ==1 && NumCluster_g2x == 1 && NumCluster_g2y==1 && NumCluster_g3x ==1 && NumCluster_g3y == 1 && NumCluster_LC1 == 1 && NumCluster_LC2 == 1 && NumCluster_LC3 == 1)
      {
          if (verbose)
              cout<<"sCMSNS2LC1\t";
          file_out<<"sCMSNS2LC1\t";
	  channelFired = 0;
	  for(Int_t nch=0;nch<kMaxsCMSNS2LC1;nch++)
	  {
		  //cout<<"sCMSNS2LC1_ngeoch[ "<<nch<<" ] = "<< sCMSNS2LC1_ngeoch[nch]<<endl;
	      if (sCMSNS2LC1_ngeoch[nch]==0)
		  break;
	      channelFired +=sCMSNS2LC1_ngeoch[nch];
	      //cout<<"Channel Fired = "<<channelFired<<endl;
	  }
	  if (verbose)
	      std::cout<<channelFired<<"\t"<<channelFired<<"\t"<<sCMSNS2LC1_geoposY[0]<<"\t"<<sCMSNS2LC1_geoposch[0]<<"\t";
	  file_out<<channelFired<<"\t"<<channelFired<<"\t"<<sCMSNS2LC1_geoposY[0]<<"\t"<<sCMSNS2LC1_geoposch[0]<<"\t";
	  count_ngeoch_occ = 0;
	  for(Int_t nch=0;nch<kMaxsCMSNS2LC1;nch++)
	  {
	      if (sCMSNS2LC1_ngeoch[nch]==0)
		  break;
		  cout<<"sCMSNS2LC1_ngeoch[ "<<nch<<" ] = "<< sCMSNS2LC1_ngeoch[nch]<<endl;
		  cout<<"jentry = "<<jentry<<endl;
		  //cin.ignore();
	      for (int chfird=0;chfird<sCMSNS2LC1_ngeoch[nch];chfird++)
	      {
		  //file_out<<"\n"<<sCMSNS2LC1_ngeoch[nch]<<"\t"<<"(sCMSNS2LC1_geoch)[ "<< count_ngeoch_occ << " ][ "<<chfird <<" ] = " << (sCMSNS2LC1_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t\n";
		  //if((sCMSNS2LC1_geoch)[count_ngeoch_occ][chfird] == 0)
		  //    break;
		  if (verbose)
		      std::cout<<(sCMSNS2LC1_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
		  //std::cout<<(sCMSNS2LC1_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
		  file_out<<(sCMSNS2LC1_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
	      }
	      count_ngeoch_occ += 1;
	  }
	  if (verbose)
	      std::cout<<std::endl;
	  // std::cout<<std::endl;
	  file_out<<std::endl;
      }
   //================================	END::	GE1/1  1 (sCMSNS2LC1)   ======================================================  
      
   //================================	GE1/1  1 (sCMSNS2LC2)   ======================================================
      channelFired = 0;		//==== ERROR:: ERROR:: ERROR::  I have to forcefully put channelFired = 0 at two places. If not then it behaves strangly.
      count_ngeoch_occ = 0;
      //if (NumCluster_g1x == 1 &&  NumCluster_g1y ==1 && NumCluster_g2x == 1 && NumCluster_g2y==1 && NumCluster_g3x ==1 && NumCluster_g3y == 1)
      if (NumCluster_g1x == 1 &&  NumCluster_g1y ==1 && NumCluster_g2x == 1 && NumCluster_g2y==1 && NumCluster_g3x ==1 && NumCluster_g3y == 1 && NumCluster_LC1 == 1 && NumCluster_LC2 == 1 && NumCluster_LC3 == 1)
      {
          if (verbose)
              cout<<"sCMSNS2LC2\t";
          file_out<<"sCMSNS2LC2\t";
	  channelFired = 0;
	  for(Int_t nch=0;nch<kMaxsCMSNS2LC2;nch++)
	  {
	      if (sCMSNS2LC2_ngeoch[nch]==0)
		  break;
	      channelFired +=sCMSNS2LC2_ngeoch[nch];
	      //cout<<"Channel Fired = "<<channelFired<<endl;
	  }
	  if (verbose)
	      std::cout<<channelFired<<"\t"<<channelFired<<"\t"<<sCMSNS2LC2_geoposY[0]<<"\t"<<sCMSNS2LC2_geoposch[0]<<"\t";
	  file_out<<channelFired<<"\t"<<channelFired<<"\t"<<sCMSNS2LC2_geoposY[0]<<"\t"<<sCMSNS2LC2_geoposch[0]<<"\t";
	  count_ngeoch_occ = 0;
	  for(Int_t nch=0;nch<kMaxsCMSNS2LC2;nch++)
	  {
	      if (sCMSNS2LC2_ngeoch[nch]==0)
		  break;
         cout<<"sCMSNS2LC2_ngeoch[ "<<nch<<" ] = "<< sCMSNS2LC2_ngeoch[nch]<<endl;
		  cout<<"jentry = "<<jentry<<endl;
	      for (int chfird=0;chfird<sCMSNS2LC2_ngeoch[nch];chfird++)
	      {
		 // if((sCMSNS2LC2_geoch)[count_ngeoch_occ][chfird] == 0)
		    //  break;
		  if (verbose)
		      std::cout<<(sCMSNS2LC2_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
		  //std::cout<<(sCMSNS2LC2_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
		  file_out<<(sCMSNS2LC2_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
	      }
	      count_ngeoch_occ += 1;
	  }
	  if (verbose)
	      std::cout<<std::endl;
	  // std::cout<<std::endl;
	  file_out<<std::endl;
      }
   //================================	END::	GE1/1  1 (sCMSNS2LC2)   ======================================================  
      
   //================================	GE1/1  1 (sCMSNS2LC3)   ======================================================
      channelFired = 0;		//==== ERROR:: ERROR:: ERROR::  I have to forcefully put channelFired = 0 at two places. If not then it behaves strangly.
      count_ngeoch_occ = 0;
      //if (NumCluster_g1x == 1 &&  NumCluster_g1y ==1 && NumCluster_g2x == 1 && NumCluster_g2y==1 && NumCluster_g3x ==1 && NumCluster_g3y == 1)
      if (NumCluster_g1x == 1 &&  NumCluster_g1y ==1 && NumCluster_g2x == 1 && NumCluster_g2y==1 && NumCluster_g3x ==1 && NumCluster_g3y == 1 && NumCluster_LC1 == 1 && NumCluster_LC2 == 1 && NumCluster_LC3 == 1)
      {
          if (verbose)
              cout<<"sCMSNS2LC3\t";
          file_out<<"sCMSNS2LC3\t";
	  channelFired = 0;
	  for(Int_t nch=0;nch<kMaxsCMSNS2LC3;nch++)
	  {
	      if (sCMSNS2LC3_ngeoch[nch]==0)
		  break;
	      channelFired +=sCMSNS2LC3_ngeoch[nch];
	      //cout<<"Channel Fired = "<<channelFired<<endl;
	  }
	  if (verbose)
	      std::cout<<channelFired<<"\t"<<channelFired<<"\t"<<sCMSNS2LC3_geoposY[0]<<"\t"<<sCMSNS2LC3_geoposch[0]<<"\t";
	  file_out<<channelFired<<"\t"<<channelFired<<"\t"<<sCMSNS2LC3_geoposY[0]<<"\t"<<sCMSNS2LC3_geoposch[0]<<"\t";
	  count_ngeoch_occ = 0;
	  for(Int_t nch=0;nch<kMaxsCMSNS2LC3;nch++)
	  {
	      if (sCMSNS2LC3_ngeoch[nch]==0)
		  break;
 cout<<"sCMSNS2LC3_ngeoch[ "<<nch<<" ] = "<< sCMSNS2LC3_ngeoch[nch]<<endl;
		  cout<<"jentry = "<<jentry<<endl;
	      for (int chfird=0;chfird<sCMSNS2LC3_ngeoch[nch];chfird++)
	      {
		  //if((sCMSNS2LC3_geoch)[count_ngeoch_occ][chfird] == 0)
		     // break;
		  if (verbose)
		      std::cout<<(sCMSNS2LC3_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
		  file_out<<(sCMSNS2LC3_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
	      }
	      count_ngeoch_occ += 1;
	  }
	  if (verbose)
	      std::cout<<std::endl;
	  // std::cout<<std::endl;
	  file_out<<std::endl;
      }
   //================================	END::	GE1/1  1 (sCMSNS2LC3)   ======================================================     
      //====================== Clear few arrays: Those behaving Strange.	===============================
   /*
    * Here we are clearing few arrays because somehow it is giving strange behaviour
    *
    * Problem:	For each event the size of the following arrays or pointer to array
    *		should be different. But once we get get some array of length 5-6 
    *		then the size of the array fixed to 5-6 and then in next event event 
    *		the size of these array is 1-2 but it is fixed to 5-6 and first two
    *		entry remains from present event but then rest are copied from last 
    *		big array.
    */
      std::fill_n(g1xcl_ngeoch,sizeof g1xcl_ngeoch/sizeof(g1xcl_ngeoch[0]),0);
      std::fill_n(g1ycl_ngeoch,sizeof g1ycl_ngeoch/sizeof(g1ycl_ngeoch[0]),0);
      std::fill_n(g2xcl_ngeoch,sizeof g2xcl_ngeoch/sizeof(g2xcl_ngeoch[0]),0);
      std::fill_n(g2ycl_ngeoch,sizeof g2ycl_ngeoch/sizeof(g2ycl_ngeoch[0]),0);
      std::fill_n(g3xcl_ngeoch,sizeof g3xcl_ngeoch/sizeof(g3xcl_ngeoch[0]),0);
      std::fill_n(g3ycl_ngeoch,sizeof g3ycl_ngeoch/sizeof(g3ycl_ngeoch[0]),0);
      std::fill_n(sCMSNS2LC1_ngeoch,sizeof sCMSNS2LC1_ngeoch/sizeof(sCMSNS2LC1_ngeoch[0]),0);
      std::fill_n(sCMSNS2LC2_ngeoch,sizeof sCMSNS2LC2_ngeoch/sizeof(sCMSNS2LC2_ngeoch[0]),0);
      std::fill_n(sCMSNS2LC3_ngeoch,sizeof sCMSNS2LC3_ngeoch/sizeof(sCMSNS2LC3_ngeoch[0]),0);
      std::fill_n(g1xcl_geoposch,sizeof g1xcl_geoposch/sizeof(g1xcl_geoposch[0]),0);
      std::fill_n(g1ycl_geoposch,sizeof g1ycl_geoposch/sizeof(g1ycl_geoposch[0]),0);
      std::fill_n(g2xcl_geoposch,sizeof g2xcl_geoposch/sizeof(g2xcl_geoposch[0]),0);
      std::fill_n(g2ycl_geoposch,sizeof g2ycl_geoposch/sizeof(g2ycl_geoposch[0]),0);
      std::fill_n(g3xcl_geoposch,sizeof g3xcl_geoposch/sizeof(g3xcl_geoposch[0]),0);
      std::fill_n(g3ycl_geoposch,sizeof g3ycl_geoposch/sizeof(g3ycl_geoposch[0]),0);
      std::fill_n(sCMSNS2LC1_geoposch,sizeof sCMSNS2LC1_geoposch/sizeof(sCMSNS2LC1_geoposch[0]),0);
      std::fill_n(sCMSNS2LC2_geoposch,sizeof sCMSNS2LC2_geoposch/sizeof(sCMSNS2LC2_geoposch[0]),0);
      std::fill_n(sCMSNS2LC3_geoposch,sizeof sCMSNS2LC3_geoposch/sizeof(sCMSNS2LC3_geoposch[0]),0);
      std::fill_n(g1xcl_geoposX,sizeof g1xcl_geoposX/sizeof(g1xcl_geoposX[0]),0);
      std::fill_n(g2xcl_geoposX,sizeof g2xcl_geoposX/sizeof(g2xcl_geoposX[0]),0);
      std::fill_n(g3xcl_geoposX,sizeof g3xcl_geoposX/sizeof(g3xcl_geoposX[0]),0);
      std::fill_n(g1ycl_geoposY,sizeof g1ycl_geoposY/sizeof(g1ycl_geoposY[0]),0);
      std::fill_n(g2ycl_geoposY,sizeof g2ycl_geoposY/sizeof(g2ycl_geoposY[0]),0);
      std::fill_n(g3ycl_geoposY,sizeof g3ycl_geoposY/sizeof(g3ycl_geoposY[0]),0);
      std::fill_n(sCMSNS2LC1_geoposY,sizeof sCMSNS2LC1_geoposY/sizeof(sCMSNS2LC1_geoposY[0]),0);
      std::fill_n(sCMSNS2LC2_geoposY,sizeof sCMSNS2LC2_geoposY/sizeof(sCMSNS2LC2_geoposY[0]),0);
      std::fill_n(sCMSNS2LC3_geoposY,sizeof sCMSNS2LC3_geoposY/sizeof(sCMSNS2LC3_geoposY[0]),0);
    //
    //Trying to use some shortcut method to delete the memory but did not succeed so apply simple method
    //
    //memset(g1xcl_geoch, 0, sizeof(g1xcl_geoch[0][0]) * count_ngeoch_occ * 12);
    //memset(g1xcl_geoch, sizeof(int)*count_ngeoch_occ*12);
    //delete[] g1xcl_geoch; g1xcl_geoch = NULL;
    //================================
    count_ngeoch_occ = 0;
    for(Int_t nch=0;nch<kMaxg1xcl;nch++)
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
    count_ngeoch_occ = 0;
    for(Int_t nch=0;nch<kMaxg1ycl;nch++)
    {
	if (g1ycl_ngeoch[nch]==0)
	break;
    for (int chfird=0;chfird<g1ycl_ngeoch[nch];chfird++)
    {
	if((g1ycl_geoch)[count_ngeoch_occ][chfird] == 0)
	    break;
	g1ycl_geoch[count_ngeoch_occ][chfird]= 0;
    }
    count_ngeoch_occ += 1;
    }    
    //================================
    count_ngeoch_occ = 0;
    for(Int_t nch=0;nch<kMaxg2xcl;nch++)
    {
	if (g2xcl_ngeoch[nch]==0)
	break;
    for (int chfird=0;chfird<g2xcl_ngeoch[nch];chfird++)
    {
	if((g2xcl_geoch)[count_ngeoch_occ][chfird] == 0)
	    break;
	g2xcl_geoch[count_ngeoch_occ][chfird]= 0;
    }
    count_ngeoch_occ += 1;
    }
    count_ngeoch_occ = 0;
    for(Int_t nch=0;nch<kMaxg2ycl;nch++)
    {
	if (g2ycl_ngeoch[nch]==0)
	break;
    for (int chfird=0;chfird<g2ycl_ngeoch[nch];chfird++)
    {
	if((g2ycl_geoch)[count_ngeoch_occ][chfird] == 0)
	    break;
	g2ycl_geoch[count_ngeoch_occ][chfird]= 0;
    }
    count_ngeoch_occ += 1;
    }    
    //================================
    count_ngeoch_occ = 0;
    for(Int_t nch=0;nch<kMaxg3xcl;nch++)
    {
	if (g3xcl_ngeoch[nch]==0)
	break;
    for (int chfird=0;chfird<g3xcl_ngeoch[nch];chfird++)
    {
	if((g3xcl_geoch)[count_ngeoch_occ][chfird] == 0)
	    break;
	g3xcl_geoch[count_ngeoch_occ][chfird]= 0;
    }
    count_ngeoch_occ += 1;
    }
    count_ngeoch_occ = 0;
    for(Int_t nch=0;nch<kMaxg3ycl;nch++)
    {
	if (g3ycl_ngeoch[nch]==0)
	break;
    for (int chfird=0;chfird<g3ycl_ngeoch[nch];chfird++)
    {
	if((g3ycl_geoch)[count_ngeoch_occ][chfird] == 0)
	    break;
	g3ycl_geoch[count_ngeoch_occ][chfird]= 0;
    }
    count_ngeoch_occ += 1;
    }    
    //================================
    //================================
    count_ngeoch_occ = 0;
    for(Int_t nch=0;nch<kMaxsCMSNS2LC1;nch++)
    {
	if (sCMSNS2LC1_ngeoch[nch]==0)
	break;
    for (int chfird=0;chfird<sCMSNS2LC1_ngeoch[nch];chfird++)
    {
	if((sCMSNS2LC1_geoch)[count_ngeoch_occ][chfird] == 0)
	    break;
	sCMSNS2LC1_geoch[count_ngeoch_occ][chfird]= 0;
    }
    count_ngeoch_occ += 1;
    }
    count_ngeoch_occ = 0;
    for(Int_t nch=0;nch<kMaxsCMSNS2LC2;nch++)
    {
	if (sCMSNS2LC2_ngeoch[nch]==0)
	break;
    for (int chfird=0;chfird<sCMSNS2LC2_ngeoch[nch];chfird++)
    {
	if((sCMSNS2LC2_geoch)[count_ngeoch_occ][chfird] == 0)
	    break;
	sCMSNS2LC2_geoch[count_ngeoch_occ][chfird]= 0;
    }
    count_ngeoch_occ += 1;
    }    
    //================================
    count_ngeoch_occ = 0;
    for(Int_t nch=0;nch<kMaxsCMSNS2LC1;nch++)
    {
	if (sCMSNS2LC3_ngeoch[nch]==0)
	break;
    for (int chfird=0;chfird<sCMSNS2LC3_ngeoch[nch];chfird++)
    {
	if((sCMSNS2LC3_geoch)[count_ngeoch_occ][chfird] == 0)
	    break;
	sCMSNS2LC3_geoch[count_ngeoch_occ][chfird]= 0;
    }
    count_ngeoch_occ += 1;
    }    
    //================================    
    //====================== END::  Clear few arrays: Those behaving Strange.	===============================	

  }
cout<<"g1x_Hit=============> "<<g1x_Hit_count<<endl;
cout<<"efficiency_g1x "<<(float) g1x_Hit_count* 100./(float) nentries<<endl;

cout<<"g1y_Hits=============> "<<g1y_Hit_count<<endl;
cout<<"efficiency_g1y "<<(float) g1y_Hit_count* 100./(float) nentries<<endl;

cout<<"g2x_Hits=============> "<<g2x_Hit_count<<endl;
cout<<"efficiency_g2x "<<(float) g2x_Hit_count* 100./(float) nentries<<endl;

cout<<"g2y_Hits=============> "<<g2y_Hit_count<<endl;
cout<<"efficiency_g2y "<<(float) g2y_Hit_count* 100./(float) nentries<<endl;
cout<<"g3x_Hits=============> "<<g3x_Hit_count<<endl;
cout<<"efficiency_g3x "<<(float) g3x_Hit_count* 100./(float) nentries<<endl;

cout<<"g3y_Hits=============> "<<g3y_Hit_count<<endl;
cout<<"efficiency_g3y "<<(float) g3y_Hit_count* 100./(float) nentries<<endl;
cout<<"g1_Hits=============> "<<g1_Hit_count<<endl;
cout<<"efficiency_g1 "<<(float) g1_Hit_count* 100./(float) nentries<<endl;
cout<<"g2_Hits=============> "<<g2_Hit_count<<endl;
cout<<"efficiency_g2 "<<(float) g2_Hit_count* 100./(float) nentries<<endl;
cout<<"g3_Hits=============> "<<g3_Hit_count<<endl;
cout<<"efficiency_g3 "<<(float) g3_Hit_count* 100./(float) nentries<<endl;
cout<<"LC1_Hits=============> "<<LC1_Hit_count<<endl;
cout<<"efficiency_LC1 "<<(float) LC1_Hit_count* 100./(float) nentries<<endl;
cout<<"LC2_Hits=============> "<<LC2_Hit_count<<endl;
cout<<"efficiency_LC2 "<<(float) LC2_Hit_count* 100./(float) nentries<<endl;
cout<<"LC3_Hits=============> "<<LC3_Hit_count<<endl;
cout<<"efficiency_LC3 "<<(float) LC3_Hit_count* 100./(float) nentries<<endl;

}
