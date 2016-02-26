#define rd51_TrackFinder_cxx
// The class definition in rd51_TrackFinder.h has been generated automatically
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
// Root > T->Process("rd51_TrackFinder.C")
// Root > T->Process("rd51_TrackFinder.C","some options")
// Root > T->Process("rd51_TrackFinder.C+")
//
//
//
// 2012.02.26
// -A Mulitplicity cut has been restored on the track finder.
//
// -Four tracker has been considered as default configuration. If only three trackers are used it should work.
//
// -In the residuals, the element "i" coorespond to tracker g"i"... residualX[1]->g1xcl, ....residualX[4]->g4xcl.
// -In the residuals, -999 is inserted if the detector was not active and/or clean.
// -In residualx(y)[0] there is the SQUARED ROOT OF THE SQUARED SUM of 
//  the existing residuals (the ones of the active and clean detectors). 
//  Be careful that it is not the RMS, because it is not divided by the number of elements
//
// -The Coverage check of T2 has been added before calling the Efficiency Calculator.
//
// -The projected X&Y have been used instead the X&Y in the tracker at Z=0 (trackx.q & tracky.q)
//
// 2012.03.06
// -rd51_TrackFinder has been used only for tracking. Any information concerning the
//  detectors under test has been removed.
// -For Any trackers it is possible to load from an external configuration
//  files X&Y offsets.



#include "rd51_TrackFinder.h"
#include <TH2.h>
#include <TStyle.h>
#include <TGraphErrors.h>
#include <TMath.h>
#include <iostream>

//Event Info
  struct TrackFinder_EventInfo_t {
              int       EventNumber;
              int       TriggerNumber;
              int       TimeStamp;
              int       BunchCounter;
              int       EventCounter;
 };
 TrackFinder_EventInfo_t TrackFinder_EventInfo;

//using namespace std;


void rd51_TrackFinder::Begin(TTree * /*tree*/)
{


   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

//  TClass::GetClass("Cluster")->IgnoreTObjectStreamer();
  TClass::GetClass("GeoCluster")->IgnoreTObjectStreamer();
  TClass::GetClass("Track")->IgnoreTObjectStreamer();

//  cout << "Beginning of Process" << endl;



  // LoadOptions( GetOption() );
  // In the option we pass one information:
  // -The name of the output root file
  //
  //
  // The format is the following:
  // Root > T->Process("rd51_TrackFinder.C","some options")
  // Root > T->Process("rd51_TrackFinder.C","TrackFinderRootFileName.root")

  TString option = GetOption();
//  if (rd51_TrackFinder_Verbose) cout << "Options: " << option << endl;  
  
//  settingfilename = option.Copy();
  trackfinderfilename = option.Copy();

//  settingfilename.Remove(option.Index(",")); 
//  settingfilename.ReplaceAll(" ",""); 
//  if (rd51_TrackFinder_Verbose) cout << "Setting File: " << settingfilename << endl;  
//  trackfinderfilename.Remove(0,settingfilename.Length()+1);
//  trackfinderfilename.ReplaceAll(" ",""); 

  if (rd51_TrackFinder_Verbose) cout << "TrackFinder Output File: " << trackfinderfilename << endl;  

//  const char *sfn = (const char*)settingfilename;
  LoaderSettings = new LoaderSettings_TrackFinder("Setting_TrackFinder.conf");
  if (LoaderSettings->error) gApplication->Terminate(0);


  rd51_TrackFinder_TrackerOffsetFile 	= (LoaderSettings->TrackerOffsetFile).c_str();
  rd51_TrackFinder_Verbose 		= LoaderSettings->TrackFinder_Verbose;
  rd51_TrackFinder_TrackVerbose 	= LoaderSettings->TrackFinder_TrackVerbose;
  rd51_TrackFinder_OffsetVerbose 	= LoaderSettings->TrackFinder_OffsetVerbose;

  if (trackfinderfilename.Length() == 0) trackfinderfilename = "_last_trackfinderfile.root";
    
  XTracksVect = new TClonesArray("Track", maxnumoftracks);
  YTracksVect = new TClonesArray("Track", maxnumoftracks);

  rd51_TrackFinder_LoaderOffset = new LoaderOffset(rd51_TrackFinder_TrackerOffsetFile, 3);
  if (rd51_TrackFinder_LoaderOffset->error) gApplication->Terminate(0);


  deltax1 = rd51_TrackFinder_LoaderOffset->xOffset[0];
  deltax2 = rd51_TrackFinder_LoaderOffset->xOffset[1];
//  deltax3 = rd51_TrackFinder_LoaderOffset->xOffset[2];
//  deltax4 = rd51_TrackFinder_LoaderOffset->xOffset[3];
  
  if (rd51_TrackFinder_OffsetVerbose)
  {
  cout 	<< "\nX Offset Loaded Before Tracking\n" 
  	<< "g1xcl: " << deltax1 <<"\n"
  	<< "g2xcl: " << deltax2 <<"\n"
//  	<< "g3xcl: " << deltax3 <<"\n"
//  	<< "g4xcl: " << deltax4 <<"\n"
  	<< endl;
  }

  deltay1 = rd51_TrackFinder_LoaderOffset->yOffset[0];
  deltay2 = rd51_TrackFinder_LoaderOffset->yOffset[1];
  deltay3 = rd51_TrackFinder_LoaderOffset->yOffset[2];
//  deltay4 = rd51_TrackFinder_LoaderOffset->yOffset[3];
  
  if (rd51_TrackFinder_OffsetVerbose)
  {
  cout 	<< "\nY Offset Loaded Before Tracking\n" 
  	<< "g1ycl: " << deltay1 <<"\n"
  	<< "g2ycl: " << deltay2 <<"\n"
//  	<< "g3ycl: " << deltay3 <<"\n"
//  	<< "g4ycl: " << deltay4 <<"\n"
  	<< endl;
  }


  deltaz1 = rd51_TrackFinder_LoaderOffset->zOffset[0];
  deltaz2 = rd51_TrackFinder_LoaderOffset->zOffset[1];
//  deltaz3 = rd51_TrackFinder_LoaderOffset->zOffset[2];
//  deltaz4 = rd51_TrackFinder_LoaderOffset->zOffset[3];
  
  if (rd51_TrackFinder_OffsetVerbose)
  {
  cout 	<< "\nZ Offset Loaded Before Tracking\n" 
  	<< "g1zcl: " << deltaz1 <<"\n"
  	<< "g2zcl: " << deltaz2 <<"\n"
//  	<< "g3zcl: " << deltaz3 <<"\n"
//  	<< "g4zcl: " << deltaz4 <<"\n"
  	<< endl;
  }
  gDirectory->Delete("trackertree"); //Delete an object IN MEMORY with the same name

  // New Tree for the trackfindernstructed data
  trackfinderfile = new TFile(trackfinderfilename, "RECREATE");
  if (!trackfinderfile->IsOpen()) Abort(" !!! CANNOT OPEN THE OUTPUT ROOT FILE !!! \n");

  trackertree = new TTree("trackertree","TrackFinder routine results");
  trackertree->Branch("TrackFinder_EventInfo"   ,&TrackFinder_EventInfo.EventNumber ,"EventNumber/I:TriggerNumber/I:TimeStamp/I:BunchCounter/I:EventCounter/I");

  //  trackertree->Branch("ntrackx",&NXTracks,"ntrackx/I1");
  trackertree->Branch("trackx","TClonesArray",&XTracksVect);
  trackertree->Branch("residualx",&(residualX[0]),"residualx[5]/D5");

  //  trackertree->Branch("ntracky",&NYTracks,"ntracky/I1");
  trackertree->Branch("tracky","TClonesArray",&YTracksVect);
  trackertree->Branch("residualy",&(residualY[0]),"residualy[5]/D5");
  
  ntotalXtracks=0;
  ntotalYtracks=0;
  
}

Bool_t rd51_TrackFinder::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // It can be passed to either TrackFinder_::GetEntry() or TBranch::GetEntry()
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
//--------------------------------------------------------------
// Event Info
//--------------------------------------------------------------
  TrackFinder_EventInfo.EventNumber          =   EventInfo_EventNumber       ;
  TrackFinder_EventInfo.TriggerNumber        =   EventInfo_TriggerNumber     ;
  TrackFinder_EventInfo.TimeStamp            =   EventInfo_TimeStamp         ;
  TrackFinder_EventInfo.BunchCounter         =   EventInfo_BunchCounter      ;
  TrackFinder_EventInfo.EventCounter         =   EventInfo_EventCounter      ;
//--------------------------------------------------------------
	
//--------------------------------------------------------------
// Trackers
//--------------------------------------------------------------
  g1xNCl = g1xcl_;
  g2xNCl = g2xcl_;
//  g3xNCl = g3xcl_;
//  g4xNCl = g4xcl_;

  g1yNCl = g1ycl_;
  g2yNCl = g2ycl_;
//  g3yNCl = g3ycl_;
//  g4yNCl = g4ycl_;

//--------------------------------------------------------------
// Hit multiplicity (all the hits in each cluster are considered)
//--------------------------------------------------------------
// Trackers: X Projection  
  g1xhm = 0;
  for (int icluster=0; icluster<g1xNCl; icluster++)
    g1xhm += g1xcl_ngeoch[icluster];

  g2xhm = 0;
  for (int icluster=0; icluster<g2xNCl; icluster++)
    g2xhm += g2xcl_ngeoch[icluster];

/*  g3xhm = 0;
  for (int icluster=0; icluster<g3xNCl; icluster++)
    g3xhm += g3xcl_ngeoch[icluster];

  g4xhm = 0;
  for (int icluster=0; icluster<g4xNCl; icluster++)
    g4xhm += g4xcl_ngeoch[icluster];
*/
// Trackers: Y Projection  
  g1yhm = 0;
  for (int icluster=0; icluster<g1yNCl; icluster++)
    g1yhm += g1ycl_ngeoch[icluster];

  g2yhm = 0;
  for (int icluster=0; icluster<g2yNCl; icluster++)
    g2yhm += g2ycl_ngeoch[icluster];

/*  g3yhm = 0;
  for (int icluster=0; icluster<g3yNCl; icluster++)
    g3yhm += g3ycl_ngeoch[icluster];

  g4yhm = 0;
  for (int icluster=0; icluster<g4yNCl; icluster++)
    g4yhm += g4ycl_ngeoch[icluster];
*/
//--------------------------------------------------------------

//-- Main ------------------------------------------------------
  if ((entry%100) == 0 && (entry/100) >= 1 && rd51_TrackFinder_Verbose)
    {
              cout << "Processing event " << entry << "\r" << flush;
    }

//--------------------------------------------------------------
// Find Tracks X Projection
//--------------------------------------------------------------

  XTracksVect->Clear("C");
  for (int i = 0; i<5; i++) residualX[i] = -999;

  NXTracks = FindTracksXProj(rd51_TrackFinder_TrackVerbose);
  ntotalXtracks += NXTracks;

//--------------------------------------------------------------
// Find Tracks Y Projection
//--------------------------------------------------------------

  YTracksVect->Clear("C");
  for (int i = 0; i<5; i++) residualY[i] = -999;

  NYTracks = FindTracksYProj(rd51_TrackFinder_TrackVerbose);
  ntotalYtracks += NYTracks;


//--------------------------------------------------------------
// Fill the ntuple         
//--------------------------------------------------------------
  trackertree->Fill();
 
  ntotalentries=entry;
  return kTRUE;

}

void rd51_TrackFinder::Terminate()
{
// The Terminate() function is the last function to be called during
// a query. It always runs on the client, it can be used to present
// the results graphically or save the results to file.
  
  if (rd51_TrackFinder_Verbose) cout << "\nTerminating Process....." << endl;
  if (GetAbort()==kContinue)
    	{
      	trackertree->Write();
  	if (rd51_TrackFinder_Verbose)
    		{ 
		Info("Terminate","Processed entries: %d",ntotalentries);
      		Info("Terminate","Total Tracks in X projection: %d",ntotalXtracks);
      		Info("Terminate","Total Tracks in Y projection: %d\n",ntotalYtracks);
		} 

      	cout << "Entries: "<< ntotalentries	<< " TracksX: " << ntotalXtracks << " TracksX[%]: "<< ntotalXtracks/(ntotalentries/1.) 
	<< "	TracksY: " << ntotalYtracks << " TracksY[%]: "<< ntotalYtracks/(ntotalentries/1.) << endl;
 
  	//if (rd51_TrackFinder_Verbose)
    	//	{
                YellowOut("\nTrees written on file and file closed.To access it:\n\n");
		YellowOut("1. From ROOT with a builded root file open (rd51tbgeo TTree active):\n");
                cout << "rd51tbgeo->AddFriend(\"trackertree\",\"" << trackfinderfilename << "\");" << endl;
                YellowOut("2. From Shell:\n");
                cout << "root -l " << trackfinderfilename <<"\n"<<endl;
    	//	}


//--------------------------------------------------------------
// Write the histograms in the trackfinderfile
//--------------------------------------------------------------

      	trackfinderfile->Close();
    	}

//--------------------------------------------------------------
//--- Deleting Objects ---------------------------------------
//--------------------------------------------------------------
  if (trackfinderfile) delete trackfinderfile;
  trackfinderfile = 0;

  if (XTracksVect) delete XTracksVect;
  XTracksVect = 0;

  if (YTracksVect) delete YTracksVect;
  YTracksVect = 0;

  if (LoaderSettings) delete LoaderSettings;
  LoaderSettings = 0;

  if (rd51_TrackFinder_LoaderOffset) delete rd51_TrackFinder_LoaderOffset;
  rd51_TrackFinder_LoaderOffset = 0;
//------------------------------------------------------------
}




int rd51_TrackFinder::FindTracksXProj(Int_t verbose)
{
  Int_t NumberOfTrackersX = 2;

// Cleaness Request: At least three detector with only one hit
  Int_t xNCl_Clean[NumberOfTrackersX];
  for (Int_t i=0; i<NumberOfTrackersX; i++ ) {xNCl_Clean[i] = 0;}

  if ( g1xNCl == 1  &&  g1xhm<120 ) xNCl_Clean[0] = 1;
  if ( g2xNCl == 1  &&  g2xhm<120 ) xNCl_Clean[1] = 1;
//  if ( g3xNCl == 1  &&  g3xhm<120 ) xNCl_Clean[2] = 1;
//  if ( g4xNCl == 1  &&  g4xhm<120 ) xNCl_Clean[3] = 1;

  Int_t CleanEventX=0;
  for (Int_t i=0; i<NumberOfTrackersX; i++ ) {CleanEventX += xNCl_Clean[i];}

  if (CleanEventX >=2)
	{

	float xer[CleanEventX]; 
	float zer[CleanEventX]; 

	float x[CleanEventX];
	for (Int_t i=0; i<CleanEventX; i++ ) {xer[i] = .15;}

	float z[CleanEventX];
	for (Int_t i=0; i<CleanEventX; i++ ) {zer[i] = 5.;}

	int ichambers = 0;
	          if (xNCl_Clean[0]) {
	            z[ichambers] = deltaz1;
	            x[ichambers] = g1xcl_geoposX[0] + deltax1;
	          ichambers++;
	          }
	          if (xNCl_Clean[1]) {
	            z[ichambers] = deltaz2;
	            x[ichambers] = g2xcl_geoposX[0] + deltax2;
	          ichambers++;
	          }
/*	          if (xNCl_Clean[2]) {
	            z[ichambers] = deltaz3;
	            x[ichambers] = g3xcl_geoposX[0] + deltax3;
	          ichambers++;
	          }
	          if (xNCl_Clean[3]) {
	            z[ichambers] = deltaz4;
	            x[ichambers] = g4xcl_geoposX[0] + deltax4;
	          ichambers++;
	          }
*/	
	   TF1 *PolFit = new TF1("PolFit","pol1",-1000,1000);
	   PolFit->SetParameter(0,x[0]);
	   PolFit->SetParameter(1,0);
	
	
	  TGraphErrors fitgraph(CleanEventX, z, x, zer, xer);
	  if (verbose)
	    {
	      fitgraph.Fit("PolFit");
	    }
	  else
	    {
	      fitgraph.Fit("PolFit", "Q");
	    }
	
	  TF1 *fitfunc = fitgraph.GetFunction("PolFit");
	  double param[2];
	  fitfunc->GetParameters(param);
	  double chisq = fitfunc->GetChisquare();
	  double ndf = fitfunc->GetNDF();
	
	  new((*XTracksVect)[0]) Track(param[1],param[0],chisq,ndf);
	 
	  // Calculate also residuals for each detector (if the detector 
	  // is not used -999 is written in the residulas) and the squared root of
	  // the squared sum of them (only for the involved ones)
	  Int_t nextDetector=0;
	  Double32_t SumOfSquare = 0;

	  for (Int_t i=0; i<NumberOfTrackersX; i++ ) 
	  {
	  if (xNCl_Clean[i]==1) 
		{
		residualX[i+1] = x[nextDetector] - param[1]*z[nextDetector] - param[0]; 
		SumOfSquare += residualX[i+1]*residualX[i+1];
		nextDetector+=1;
		}
	  else 
		{
		residualX[i+1] = -999;
		}
          }

	  residualX[0] = TMath::Sqrt(SumOfSquare);
	  delete	 PolFit;	  
	  return 1;
  }
  else return 0;
}

int rd51_TrackFinder::FindTracksYProj(Int_t verbose)
{
  Int_t NumberOfTrackersY = 2;

// Cleaness Request: At least three detector with only one hit
  Int_t yNCl_Clean[NumberOfTrackersY];
  for (Int_t i=0; i<NumberOfTrackersY; i++ ) {yNCl_Clean[i] = 0;}

  if ( g1yNCl == 1  &&  g1yhm<120 ) yNCl_Clean[0] = 1;
  if ( g2yNCl == 1  &&  g2yhm<120 ) yNCl_Clean[1] = 1;
//  if ( g3yNCl == 1  &&  g3yhm<120 ) yNCl_Clean[2] = 1;
//  if ( g4yNCl == 1  &&  g4yhm<120 ) yNCl_Clean[3] = 1;

  Int_t CleanEventY=0;
  for (Int_t i=0; i<NumberOfTrackersY; i++ ) {CleanEventY += yNCl_Clean[i];}

  if (CleanEventY >=2)
	{

	float yer[CleanEventY]; 
	float zer[CleanEventY]; 


	float y[CleanEventY];
	for (Int_t i=0; i<CleanEventY; i++ ) {yer[i] = .15;}

	float z[CleanEventY];
	for (Int_t i=0; i<CleanEventY; i++ ) {zer[i] = 5.;}

	int ichambers = 0;
	          if (yNCl_Clean[0]) {
	            z[ichambers] = deltaz1;
	            y[ichambers] = g1ycl_geoposY[0] + deltay1;
	          ichambers++;
	          }
	          if (yNCl_Clean[1]) {
	            z[ichambers] = deltaz2; // October 343;
	            y[ichambers] = g2ycl_geoposY[0] + deltay2;
	          ichambers++;
	          }
/*	          if (yNCl_Clean[2]) {
	            z[ichambers] = deltaz3;
	            y[ichambers] = g3ycl_geoposY[0] + deltay3;
	          ichambers++;
	          }
	          if (yNCl_Clean[3]) {
	            z[ichambers] = deltaz4; // October 883;
	            y[ichambers] = g4ycl_geoposY[0] + deltay4;
	          ichambers++;
	          }
*/
	   TF1 *PolFit = new TF1("PolFit","pol1",-1000,1000);
	   PolFit->SetParameter(0,y[0]);
	   PolFit->SetParameter(1,0);
	
	
	  TGraphErrors fitgraph(CleanEventY, z, y, zer, yer);
	  if (verbose)
	    {
	      fitgraph.Fit("PolFit");
	    }
	  else
	    {
	      fitgraph.Fit("PolFit", "Q");
	    }
	
//	  fitgraph->Draw();

	  TF1 *fitfunc = fitgraph.GetFunction("PolFit");
	  double param[2];
	  fitfunc->GetParameters(param);
	  double chisq = fitfunc->GetChisquare();
	  double ndf = fitfunc->GetNDF();
	
	  new((*YTracksVect)[0]) Track(param[1],param[0],chisq,ndf);
	 
	  // Calculate also residuals for each detector (if the detector 
	  // is not used -999 is written in the residulas) and the squared root of
	  // the squared sum of them (only for the involved ones)
	  Int_t nextDetector=0;
	  Double32_t SumOfSquare = 0;

	  for (Int_t i=0; i<NumberOfTrackersY; i++ ) 
	  {
	  if (yNCl_Clean[i]==1) 
		{
		residualY[i+1] = y[nextDetector] - param[1]*z[nextDetector] - param[0]; 
		SumOfSquare += residualY[i+1]*residualY[i+1];
		nextDetector+=1;
		}
	  else 
		{
		residualY[i+1] = -999;
		}
          }

	  residualY[0] = TMath::Sqrt(SumOfSquare);
	  delete	 PolFit;	  
	  return 1;
  }
  else return 0;
}

