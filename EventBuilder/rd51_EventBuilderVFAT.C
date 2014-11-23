// Thu, 21 July 2011
//
// In this version we will define a general detector
// in order to avoid additional definition all the time tha
// a detector is added. 
// We will create a TTree with the VFAT raw data. 
// 
//
// Sat, 23 July 2011
//
// In this version we add informationn on the event
// as trigger, timestamp, turbo and slot id...
// We have defined a VFATDataArray with those information
// defined in the object.
// Inside the detectors ttre, those value are extracted from the
// first VFAT.
// Inside the vfat ttree (raw) they are defined for all
// of them as they are (usefull fof check)
//
// Sun, 24 July 2011
//
// In this version we add the geometrical information 
// associated to each channel. We would like to have something
// that can be used for each tyoe of detector.
// For this reason we will associate to each detector
// X,Y,R Phi coordinate. They will be filled only if they are reasonable.
//
// Wed, 27 July 2011
//
// We modified also the reco. We keep only the tracker detectors and
// we add the event info also in the recofile.
//
// Tue, 28 July 2011
//
// New Classes for VFAT and Detector have been defined.
// The configuration used has to be inserted in the CONFIGURATION SECTION
//
// Sun, 31 July 2011
//
// We have now the geo containers working properly. 
//
// Wed, 3 Aug 2011
//
// We have added the geocontainer also in the clusterization. This
// is useful beacause it helps on creating the clusters for more 
// complex readout (layout). 
// Additional Geometrical Flips (Horizontal and Vertical) of the detectors 
// have been added in their definition. I this way it is possible to
// adapt them to the used geometry.
//
//
// Sat, 3 Mar 2012
//
// We changed the basic scheme of the rd51tb analysys software.
// The idea is the following:
// 1. EventBuilder 	-> Convert channels Hits into cluster with spatial coordinate
// 2. Track Finder 	-> Extract the Tracks
// 3. Analyzer		-> Using the tracks Info, calcutes efficiencies, cluster size,...
//
// Main Changes in the EventBuilder:
// -We add as for the tracks reconstruction the possibility to load the detectors offset
//  from an external file (without recompiling the code)
// -We load the detector and chip configuartion from the external configuartion files

#include <stdlib.h>
#include "Riostream.h"
#include <string>
#include "TObject.h"
#include <TApplication.h>
#include "Clustering/Config.hpp"
//#include "Loaders/LoaderSettings.hpp"
#include "Loaders/LoaderSettings.cpp"
//#include "Loaders/LoaderDetectorConf.hpp"
#include "Loaders/LoaderDetectorConf.cpp"
#include "Loaders/LoaderVFATConf.cpp"
#include "Loaders/LoaderOffsetFlipConf.cpp"
#include "Mapping/ReadoutType.cpp"
#include "Mapping/TotemT2.cpp"
#include "Mapping/TotemT1LG.cpp"
#include "Mapping/CmsMapping.cpp"
#include "Clustering/DataArray_T.cpp"
#include "Clustering/GeoDataArray_T.cpp"
//#include "Utilities/ColoredMessages.hpp"
#include "TClonesArray.h"
#include <iostream>
#include <fstream>
#include "TMath.h"
#include "TSystem.h"
#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TCut.h"

//using namespace std;

// Event Builder Routine
// The VFAT DAQ creates binary files and the event builder creates a raw data TTree saved on a root file
//

int rd51_EventBuilderVFAT(
                          const char* rawfilename 	= "input.dat"		, 
                          const char* rootfilename	= "Events_built.root"	, 
                          const int readmaxevent 	= 100000000)	
{
    
    LoaderSettings *LoaderSettings_rd51_EventBuilderVFAT = new LoaderSettings("Setting_EventBuilderVFAT.conf");
    if (LoaderSettings_rd51_EventBuilderVFAT->error) gApplication->Terminate(0);
    
    string rd51_EventBuilderVFAT_DetectorConfigFile 	=(LoaderSettings_rd51_EventBuilderVFAT->DetectorConfigFile).c_str();
    string rd51_EventBuilderVFAT_DetectorOffsetAndFlipFile=(LoaderSettings_rd51_EventBuilderVFAT->DetectorOffsetAndFlipFile).c_str();
    string rd51_EventBuilderVFAT_VFATConfigFile 		=(LoaderSettings_rd51_EventBuilderVFAT->VFATConfigFile).c_str();
    int EBV_Verbose					= LoaderSettings_rd51_EventBuilderVFAT->Verbose;
    int EBV_LoaderSettingsPrintOut			= LoaderSettings_rd51_EventBuilderVFAT->LoaderSettingsPrintOut;
    int EBV_DetectorInfoPrintOut				= LoaderSettings_rd51_EventBuilderVFAT->DetectorInfoPrintOut;
    int EBV_VFATInfoPrintOut				= LoaderSettings_rd51_EventBuilderVFAT->VFATInfoPrintOut;
    int EBV_ChipIdVerbose					= LoaderSettings_rd51_EventBuilderVFAT->ChipIdVerbose;
    int EBV_EfficiencyEstimatorPrintOut 			= LoaderSettings_rd51_EventBuilderVFAT->EfficiencyEstimatorPrintOut;
    int EBV_BeampProfiledataPrintOut 			= LoaderSettings_rd51_EventBuilderVFAT->BeampProfiledataPrintOut;
    
    if (EBV_LoaderSettingsPrintOut)
    {
        cout    << "Detector Configuration File:  \t" << rd51_EventBuilderVFAT_DetectorConfigFile 		<< "\n"
        << "Detector Offset And Flip File:\t" << rd51_EventBuilderVFAT_DetectorOffsetAndFlipFile 	<< "\n"
        << "VFAT Configuration File:      \t" << rd51_EventBuilderVFAT_VFATConfigFile 			
        << endl;
    }
    
    // The clusterization is readout dependent. 
    // We prefer to have independent clusterization
    // Classes for different readout electrodes. 
    // TO UPGRADE: A general definition can be usefull
    //  TClass::GetClass("VFAT2")->IgnoreTObjectStreamer();
    //  TClass::GetClass("Detector")->IgnoreTObjectStreamer();
    //  TClass::GetClass("VFATDataArray")->IgnoreTObjectStreamer();
    //  TClass::GetClass("GeoDataArray")->IgnoreTObjectStreamer();
    //  TClass::GetClass("Hit")->IgnoreTObjectStreamer();
    //---Original  TClass::GetClass("Cluster")->IgnoreTObjectStreamer();
    
    TClass::GetClass("GeoCluster")->IgnoreTObjectStreamer();
    TClass::GetClass("Track")->IgnoreTObjectStreamer();
    
    if (!rawfilename) rawfilename = "input.dat";
    if (!rootfilename) rootfilename = "Events_built.root";
    
    ifstream ifile(rawfilename, ifstream::binary);
    
    TFile f(rootfilename,"RECREATE");
    
    //----------TTree Definition ----------------------------------------------------------------
    TTree *tree_conf = new TTree("rd51tbconfig","RD51 test beam configuration");
    TTree *tree_raw = new TTree("rd51tbraw","RD51 test beam raw data");
    //---Original  TTree tree("rd51tb","RD51 test beam");
    TTree *tree_geo = new TTree("rd51tbgeo","RD51 test beam geometry");
    //  tree_conf->SetDirectory(gDirectory);
    //  tree_raw->SetDirectory(gDirectory);
    //  tree_geo->SetDirectory(gDirectory);
    
    //----------TTree Definition ----------------------------------------------------------------
    
    
    
    //-------------- CONFIGURATION (DETECTORS AND VFATS)-----------------------------------------
    
    //----------------------------------------------------------
    // DETECTOR CONFIGURATION. 
    //----------------------------------------------------------
    
    //--- Loading the detector configuration file and Retrieving the number of detectors
    LoaderDetectorConf *DetectorConf_rd51_EventBuilderVFAT = new LoaderDetectorConf(rd51_EventBuilderVFAT_DetectorConfigFile);
    if (DetectorConf_rd51_EventBuilderVFAT->error) gApplication->Terminate(0);
    
    Int_t MaxNumbersOfDetDir = DetectorConf_rd51_EventBuilderVFAT->det_NumberOfDetectors;
    
    //--- Inizializing the detectors
    Detector* DET[MaxNumbersOfDetDir];
    for (Int_t i=0; i<MaxNumbersOfDetDir; i++)
    {
        DET[i] = new Detector("",0,0,0,0,0,0,0,0,0,0,0,0);
    }
    
    //--- Loading the detector configuration
    for (Int_t i=0; i<MaxNumbersOfDetDir; i++)
    {
        (*DET[i]).DetectorName			= DetectorConf_rd51_EventBuilderVFAT->det_Name[i]               		;	
        (*DET[i]).ReadoutType			= DetectorConf_rd51_EventBuilderVFAT->det_ReadoutType[i]                 	;	
        (*DET[i]).OffsetHorizontal		= DetectorConf_rd51_EventBuilderVFAT->det_xOffset[i]                     	;
        (*DET[i]).OffsetVertical		= DetectorConf_rd51_EventBuilderVFAT->det_yOffset[i]                     	;
        (*DET[i]).FlipHorizontal		= DetectorConf_rd51_EventBuilderVFAT->det_xFlip[i]                       	;
        (*DET[i]).FlipVertical                	= DetectorConf_rd51_EventBuilderVFAT->det_yFlip[i]                       	;
        (*DET[i]).TotChannels                 	= DetectorConf_rd51_EventBuilderVFAT->det_TotChannels[i]                 	;	
        (*DET[i]).PossibleHits                	= DetectorConf_rd51_EventBuilderVFAT->det_PossibleHits[i]                	;
        (*DET[i]).MaxDistInCluster		= DetectorConf_rd51_EventBuilderVFAT->det_MaxDistInCluster[i]            	;
        (*DET[i]).PeriodicityInCluster        	= DetectorConf_rd51_EventBuilderVFAT->det_PeriodicityInCluster[i]        	;
        (*DET[i]).MaxDistPeriodicityInCluster 	= DetectorConf_rd51_EventBuilderVFAT->det_MaxDistPeriodicityInCluster[i] 	;
        (*DET[i]).MaxNumOfClusters            	= DetectorConf_rd51_EventBuilderVFAT->det_MaxNumOfClusters[i]	       	;
//cout<<"###########\t"<< (*DET[i]).PossibleHits <<endl;
    }
    
    LoaderOffsetFlipConf *OffsetFlip_rd51_EventBuilderVFAT = new LoaderOffsetFlipConf(rd51_EventBuilderVFAT_DetectorOffsetAndFlipFile, MaxNumbersOfDetDir);
    if (OffsetFlip_rd51_EventBuilderVFAT->error) gApplication->Terminate(0);
    
    //--- Updating the offsets/flips (the offsets/flips have been written in a 
    //--- different filein order to be completely independent from the main config file)
    for (Int_t i=0; i<MaxNumbersOfDetDir; i++)
    {
        (*DET[i]).OffsetHorizontal 	= OffsetFlip_rd51_EventBuilderVFAT->xOffset[i];
        (*DET[i]).OffsetVertical 	= OffsetFlip_rd51_EventBuilderVFAT->yOffset[i];
        (*DET[i]).OffsetZ 		= OffsetFlip_rd51_EventBuilderVFAT->zOffset[i];
        (*DET[i]).FlipHorizontal 	= OffsetFlip_rd51_EventBuilderVFAT->xFlip[i];
        (*DET[i]).FlipVertical 		= OffsetFlip_rd51_EventBuilderVFAT->yFlip[i];
    }
    
    //--- PrintOut of the detector configuration loaded
    if(EBV_DetectorInfoPrintOut)
    {
        cout << "______________________________________________________________________________________________________________" << endl;
        cout << "Number of Loaded Detectors: " << MaxNumbersOfDetDir << endl;
        cout << "" << endl;
        cout << "DetID,ROTyp,Offx,Offy,Offz,Flipx,Flipy,TotChs,PossibleHits,MaxDistInCls,PerInCls,MaxDistPerInCls,MaxNumOfCls,DetName" << endl;
        cout << "" << endl;
        for (Int_t i=0; i<MaxNumbersOfDetDir; i++)
        {
            cout << i 				<< "\t" <<
            (*DET[i]).ReadoutType			<< "\t" <<	
            (*DET[i]).OffsetHorizontal		<< "\t" <<
            (*DET[i]).OffsetVertical		<< "\t" <<
            (*DET[i]).OffsetZ			<< "\t" <<
            (*DET[i]).FlipHorizontal		<< "\t" <<
            (*DET[i]).FlipVertical                 << "\t" <<
            (*DET[i]).TotChannels                  << "\t" <<	
            (*DET[i]).PossibleHits                 << "\t" <<
            (*DET[i]).MaxDistInCluster		<< "\t" <<
            (*DET[i]).PeriodicityInCluster         << "\t" <<
            (*DET[i]).MaxDistPeriodicityInCluster  << "\t" <<
            (*DET[i]).MaxNumOfClusters             << "\t" <<
            (*DET[i]).DetectorName				
            << endl;
        }
        cout << "_____________________________________________________________________________________________________________" << endl;
    }
    //--- END OF DETECTOR CONFIGURATION ------------------------
    
    //----------------------------------------------------------
    // VFAT CONFIGURATION. Please specify here the system
    //----------------------------------------------------------
    
    //--- Loading the VFAT configuration file and Retrieving the number of VFATs
    LoaderVFATConf *VFATConf_rd51_EventBuilderVFAT = new LoaderVFATConf(rd51_EventBuilderVFAT_VFATConfigFile);
    if (VFATConf_rd51_EventBuilderVFAT->error) gApplication->Terminate(0);
    
    Int_t chips_per_evt = VFATConf_rd51_EventBuilderVFAT->vfat_NumberOfVFATs;
    
    //--- Inizializing the detectors
    VFAT2* VFAT[chips_per_evt];
    for (Int_t i=0; i<chips_per_evt; i++)
    {
        VFAT[i] = new VFAT2(0XFFFF,128,0,"","",0,0,0,0);
    }
    
//VFAT->Dump();
    //--- Loading the detector configuration
    for (Int_t i=0; i<chips_per_evt; i++)
    {
        (*VFAT[i]).ChipId          = VFATConf_rd51_EventBuilderVFAT->vfat_ChipId[i]        ;	
        (*VFAT[i]).Channels        = VFATConf_rd51_EventBuilderVFAT->vfat_Channels[i]      ;	
        (*VFAT[i]).DetectorId      = VFATConf_rd51_EventBuilderVFAT->vfat_DetectorId[i]    ;
        (*VFAT[i]).DetectorName    = VFATConf_rd51_EventBuilderVFAT->vfat_DetectorName[i]  ;
        (*VFAT[i]).DetectorSector  = VFATConf_rd51_EventBuilderVFAT->vfat_DetectorSector[i];
        (*VFAT[i]).ChipInvert      = VFATConf_rd51_EventBuilderVFAT->vfat_ChipInvert[i]    ;
        (*VFAT[i]).ChipOffset      = VFATConf_rd51_EventBuilderVFAT->vfat_ChipOffset[i]    ;	
        (*VFAT[i]).TurboId         = VFATConf_rd51_EventBuilderVFAT->vfat_TurboId[i]       ;
        (*VFAT[i]).SlotId          = VFATConf_rd51_EventBuilderVFAT->vfat_SlotId[i]        ;
    }
    
    //--- PrintOut of the detector configuration loaded
    if(EBV_VFATInfoPrintOut)
    {
        char hex_ChipId_printout[7];
        
        cout << "______________________________________________________________________________________________________________" << endl;
        cout << "Number of Loaded VFATs: " << chips_per_evt << endl;
        cout << "" << endl;
        cout << "Id,ChipId, Channels, DetectorId, DetectorName ,DetectorSector , ChipInvert, ChipOffset, TurboId, SlotId" << endl;
        cout << "" << endl;
        for (Int_t i=0; i<chips_per_evt; i++)
        {
            sprintf(hex_ChipId_printout, "0X%x", (*VFAT[i]).ChipId);
            cout << i 			<< "\t" <<
            //          (*VFAT[i]).ChipId          	<< "\t" <<	
            hex_ChipId_printout  	        << "\t" <<	
            (*VFAT[i]).Channels        	<< "\t" <<
            (*VFAT[i]).DetectorId      	<< "\t" <<
            (*VFAT[i]).DetectorName    	<< "\t" <<
            (*VFAT[i]).DetectorSector   	<< "\t" <<
            (*VFAT[i]).ChipInvert       	<< "\t" <<	
            (*VFAT[i]).ChipOffset       	<< "\t" <<
            (*VFAT[i]).TurboId   		<< "\t" <<
            (*VFAT[i]).SlotId          
            << endl;
        }
        cout << "_____________________________________________________________________________________________________________" << endl;
    }
    //--- END OF VFAT CONFIGURATION ------------------------
    
    //-------------- END OF CONFIGURATION (DETECTORS AND VFATS)-----------------------------------------
    
    
    
    //-------------- DETECTOR DEFINITION ---------------------------------------------------------
    
    //Here we will define all the detectors with their parameters  
    
    //Define the DataArrays for each detector. 
    //NB: fo 2D readout or complex (1D) we define multiple "virtual" detector associated to the real one.
    //The 10x10 XY strips readout for example is considered as two detectors, one associated to the X and one the Y.
    //
    //In the July Beam we used 3 trackers (X & Y), 1 Large CMS GEM (1D Strips) and 2 T2 Triple GEM (Strips & Pads).
    //In total we will have therefore 11 detectors. 
    //
    //TO UPGRADE: We have to use an easyiest way of defining the following parameters.
    //On possibility is to define VFAT and Detector object with all the parameters defined.
    //The following array will be therefore filled with a loop over all the existing elements 	
    
    
    Int_t TypeOfReadout[MaxNumbersOfDetDir];
    for (Int_t i=0; i<MaxNumbersOfDetDir; i++){TypeOfReadout[i]=(*DET[i]).ReadoutType;}
    
//    Int_t TotChannels[MaxNumbersOfDetDir];
//    for (Int_t i=0; i<MaxNumbersOfDetDir; i++){TotChannels[i]=(*DET[i]).TotChannels;}
    
    Int_t PossibleHits[MaxNumbersOfDetDir];
    for (Int_t i=0; i<MaxNumbersOfDetDir; i++){PossibleHits[i]=(*DET[i]).PossibleHits;
//	cout<<"############# Possible hits = "<<PossibleHits[i]<<endl;
}
    
    Int_t MaxPossibleHits = (TMath::MaxElement(MaxNumbersOfDetDir,PossibleHits));	//T MaxElement(Long64_t n, const T *a) Return maximum of array a of length n.

    
    double MaxDistInCluster[MaxNumbersOfDetDir];
    for (Int_t i=0; i<MaxNumbersOfDetDir; i++){MaxDistInCluster[i]=(*DET[i]).MaxDistInCluster;}
    
    Int_t PeriodicityInCluster[MaxNumbersOfDetDir];
    for (Int_t i=0; i<MaxNumbersOfDetDir; i++){PeriodicityInCluster[i]=(*DET[i]).PeriodicityInCluster;}
    
    double MaxDistPeriodicityInCluster[MaxNumbersOfDetDir];
    for (Int_t i=0; i<MaxNumbersOfDetDir; i++){MaxDistPeriodicityInCluster[i]=(*DET[i]).MaxDistPeriodicityInCluster;}
    
// cout<<"Data saved in arrays"<<endl;   
    
    //--- DATA CONTAINER --------------------------------------------------------------------------------------------
    
    // Here we difine the "container" for the VFAT data. A data Array contains the channels
    // fired per events and their number.
    DataArray* g[MaxNumbersOfDetDir];
//cout<<"##################"<<endl;
    for(Int_t i=0; i<MaxNumbersOfDetDir; i++) 
	{
//	cout<<"test"<<endl;
        g[i] = new DataArray((const int)PossibleHits[i]);
//	cout<<"Possible hits = "<<PossibleHits[i]<<"\t g[i] = "<<g[i]<<endl;
	}
    
    // In the following object we will store the same information as before, adding 
    // the spatial coordinate of the hits.
    
    GeoDataArray* gGeo[MaxNumbersOfDetDir];
    for(Int_t i=0; i<MaxNumbersOfDetDir; i++) 
	{
        gGeo[i] = new GeoDataArray(PossibleHits[i]);
	}
    
    //  We tried a TClonesArray but we had some problem 
    //  (it became very slow increasing the number of event processed - 
    //  we probably forgot to delete/clear something)   
    //  and we decided to use GeoDataAray.
    //  Below is the code for the TClonesArray
    //
    //--- Using TClonesArray:   bool geoalreadyused[MaxPossibleHits];
    //--- Using TClonesArray:   GeoCluster tmpgeocluster(MaxPossibleHits); 
    //--- Using TClonesArray:   TClonesArray* gGeo[MaxNumbersOfDetDir];
    //--- Using TClonesArray:   for(Int_t i=0; i<MaxNumbersOfDetDir; i++) 
    //--- Using TClonesArray:     gGeo[i] = new TClonesArray("GeoCluster", PossibleHits[i]);
    
    
    //--- CLUSTERIZATION -----------------------------------------------------------------------------------------
    
    //Detector Clusterization. This is dependent on the readout type
    //and it has to be define for each detector.
//   cout<<"Define the max no. of cluster array"<<endl; 
    Int_t MaxNumOfClusters[MaxNumbersOfDetDir];
    for (Int_t i=0; i<MaxNumbersOfDetDir; i++){MaxNumOfClusters[i]=(*DET[i]).MaxNumOfClusters;}
    
    // We define a temporary Cluster with as many elements as the maximum number of possible hits for 
    // all the detectors used.
    
    //---Not Used Variable:  bool alreadyused[MaxPossibleHits];
    //   Cluster tmpcluster(MaxPossibleHits); 
    //   TClonesArray* gClustVect[MaxNumbersOfDetDir]; //Geo+Cluster
    //   for (Int_t i=0; i<MaxNumbersOfDetDir; i++)
    //     gClustVect[i] = new TClonesArray("Cluster", MaxNumOfClusters[i]);
    
    
    bool geoalreadyused[MaxPossibleHits];
    GeoCluster* geotmpcluster[MaxNumbersOfDetDir]; 
    for (Int_t i=0; i<MaxNumbersOfDetDir; i++)
    {	
        geotmpcluster[i] = new GeoCluster(MaxNumOfClusters[i]); 
    }
    
    TClonesArray* gGeoClustVect[MaxNumbersOfDetDir]; //Geo+Cluster
    for (Int_t i=0; i<MaxNumbersOfDetDir; i++)
    {
        gGeoClustVect[i] = new TClonesArray("GeoCluster", MaxNumOfClusters[i]);
      	gGeoClustVect[i]->SetOwner(kTRUE);
    }
    //--- DATA CONTAINER --------------------------------------------------------------------------------------------
    
    
    //--------------- EVENT INFO ---------------------------------------------------
    //I define some Event Info. They are defined by the first read chip.	
    
    struct EventInfo_t {
        int	EventNumber;	
        int	TriggerNumber;	
        int	TimeStamp;	
        int	BunchCounter;	
        int	EventCounter;	
    };
    EventInfo_t EventInfo;
    //--------------- EVENT INFO ---------------------------------------------------
    
    
    //--------------- TREEs ---------------------------------------------------------
    //Define Branches for the clusterized data and for the data in space coordinate
    tree_geo->Branch("EventInfo"	,&EventInfo.EventNumber	,"EventNumber/I:TriggerNumber/I:TimeStamp/I:BunchCounter/I:EventCounter/I");
    
    for(Int_t i=0; i<MaxNumbersOfDetDir; i++) 
    {
        tree_geo->Branch( (*DET[i]).DetectorName,"TClonesArray",&(gGeoClustVect[i]),32000,1);
    }              
    //--------------- TREEs ---------------------------------------------------------
    
    
    //-----------END DETECTOR DEFINITION ---------------------------------------------------------
    
    
    
    
    //-------------- VFAT DEFINITION -------------------------------------------------------------
    
    // Insert here the number of channels per chip (128 for the VFAT)
    const Int_t channels_per_chip = (*VFAT[0]).Channels;
    
    // Insert here the VFAT chip ID (16 bit). The order used in this array has to be maintened for the next ones, where 
    // invert, offset, detector ID are specified. 
    // TO UPGRADE: The VFAT ID can be extracted by the xml file saved at the end of the acquisition.	
    
    unsigned short chipID[chips_per_evt]; 
    for (Int_t i=0; i<chips_per_evt; i++){chipID[i]=(*VFAT[i]).ChipId;} 
    
    // The chipdet array specify to which detector the chip are connected. The X and Y coordinates
    // of the Trackers are considered as two different detectors. This ID will be used later to assign
    // the VFAT channel status to a detector channel status.	
    
    Int_t chipdet[chips_per_evt]; 
    for (Int_t i=0; i<chips_per_evt; i++){chipdet[i]=(*VFAT[i]).DetectorId;} 
    
    // The Invert tell to the software how the VFATs channels are placed in the space (right-left, top-bottom).
    // Looking at the chip from the top of the hybrid (with the chip in the bottom) the channel 0 is on the Left 
    // and is on the side closest to the black connector used for connecting the hybrid to the TURBO or TTP.
    // The invert for the T2 Triple GEM Pads is not "simple". For the Strips it is easyier. SS1 and SS2 have to be inverted.
    // SS3 and SS4 no.                                              
    
    bool chipinvert[chips_per_evt]; 
    for (Int_t i=0; i<chips_per_evt; i++){chipinvert[i]=(*VFAT[i]).ChipInvert;} 
    
    // The Offset is defined in terms of VFAT channels and it used to build the detector.
    // The T2 Triple GEM has 1560 Pads Channels. Each Chip has 120 channels connected. There are 13 Sectors. From Pad Sector 1 (PS1)
    // to Pad Sector 13 (PS13). PS1 is the one closest to the High Voltage Divider. The channel 0 of each chips correspond to the small 
    // pad and Channel 120 is the largest pad of the sector. A proper mapping is needed. Channels 0,1,2,123,124,125,126,127 of the chips 
    // are grounded. 
    //
    // PS01=  0,..,119                                                                                     
    // PS02=120,..,239
    // ...
    // PS##=(##-1)*120             
    //
    // The Strips are 512. We have four Sectors SS1(Int), SS2(Ext), SS3(Ext), SS4(Int).
    // SS1 and SS2 are on the HV Divider side. The strips numbering Start from that side.
    
    Int_t chipoffset[chips_per_evt]; 
    for (Int_t i=0; i<chips_per_evt; i++){chipoffset[i]=(*VFAT[i]).ChipOffset;} 
    
    
    //--- VFAT RAW DATA CONTAINER ---------------------------------------------------------------------
    VFATDataArray* vfat_data[chips_per_evt];
    for(Int_t i=0; i<chips_per_evt; i++) {vfat_data[i] = new VFATDataArray((*VFAT[i]).Channels);}
    //--- VFAT RAW DATA CONTAINER ---------------------------------------------------------------------
    
    //Define Branches for the vfats configuration
    char vfatID_ChipId[6];
    for(Int_t i=0; i<chips_per_evt; i++) 
    {
        sprintf(vfatID_ChipId, "%x", (*VFAT[i]).ChipId);
        tree_conf->Branch( vfatID_ChipId,"VFAT2",&(VFAT[i]),chips_per_evt,1);
        tree_conf->GetBranch(vfatID_ChipId)->SetAutoDelete();
    }    

    //Define Branches for the vfats raw data
    tree_raw->Branch("EventInfo"	,&EventInfo.EventNumber	,"EventNumber/I:TriggerNumber/I:TimeStamp/I:BunchCounter/I:EventCounter/I");
    char vfatID_string[6];
    for(Int_t i=0; i<chips_per_evt; i++) 
    {
        sprintf(vfatID_string, "%x", (*VFAT[i]).ChipId);
        tree_raw->Branch( vfatID_string,"VFATDataArray",&(vfat_data[i]),32000,0);
        tree_raw->GetBranch(vfatID_string)->SetAutoDelete();
    }              
    
    //-----------END VFAT DEFINITION -------------------------------------------------------------
    
    
    
    
    
    //-------------------------------------------------------------------------------------------
    //
    //    FRAME READOUT                                                                            
    //                                                                                           
    //-------------------------------------------------------------------------------------------
    
    // Variables derived from the above-mentioned configuration:
    Int_t readcheck[chips_per_evt];
    
    for(Int_t ichip = 0; ichip < chips_per_evt; ichip++)
    {
        readcheck[ichip] = 0;
    }
    
    
    
    //cout << "Define DataStructure" << endl;
    
    
    //TO UPGRADE: Define one object with the event charachteristics vs event number.
    //This will be useful to monitor the data. We should do it in DataArray.
    struct datastructure {
        unsigned short bof;
        unsigned short turboid;
        unsigned short slotid;
        unsigned short fullid;
        unsigned short trignum;
        unsigned short timestamp;
        unsigned short bc;
        unsigned short ec;
        unsigned short chipid;
        unsigned short data[8];
        unsigned short crc;
        unsigned short eof;
    } testdata;
    const unsigned int framelenght = 38;
    
    //Check of data structures and alignment in the machine it is running
    if (EBV_Verbose ==1 ){  cout << "Size of datastructure on this machine is (should be "
        << framelenght << "): " << sizeof(datastructure) << endl;
        
        cout << "\nChecking Alignment..";
        cout << "\ntestdata.bof        is at " << reinterpret_cast<void*>(&testdata.bof);
        cout << "\ntestdata.turboid    is at " << reinterpret_cast<void*>(&testdata.turboid);
        cout << "\ntestdata.slotid     is at " << reinterpret_cast<void*>(&testdata.slotid);
        cout << "\ntestdata.fullid     is at " << reinterpret_cast<void*>(&testdata.fullid);
        cout << "\ntestdata.trignum    is at " << reinterpret_cast<void*>(&testdata.trignum);
        cout << "\ntestdata.timestamp  is at " << reinterpret_cast<void*>(&testdata.timestamp);
        cout << "\ntestdata.bc         is at " << reinterpret_cast<void*>(&testdata.bc);
        cout << "\ntestdata.ec         is at " << reinterpret_cast<void*>(&testdata.ec);
        cout << "\ntestdata.chipid     is at " << reinterpret_cast<void*>(&testdata.chipid);
        cout << "\ntestdata.data[0]    is at " << reinterpret_cast<void*>(&(testdata.data[0]));
        cout << "\ntestdata.data[1]    is at " << reinterpret_cast<void*>(&(testdata.data[1]));
        cout << "\ntestdata.data[2]    is at " << reinterpret_cast<void*>(&(testdata.data[2]));
        cout << "\ntestdata.data[3]    is at " << reinterpret_cast<void*>(&(testdata.data[3]));
        cout << "\ntestdata.data[4]    is at " << reinterpret_cast<void*>(&(testdata.data[4]));
        cout << "\ntestdata.data[5]    is at " << reinterpret_cast<void*>(&(testdata.data[5]));
        cout << "\ntestdata.data[6]    is at " << reinterpret_cast<void*>(&(testdata.data[6]));
        cout << "\ntestdata.data[7]    is at " << reinterpret_cast<void*>(&(testdata.data[7]));
        cout << "\ntestdata.crc        is at " << reinterpret_cast<void*>(&testdata.crc);
        cout << "\ntestdata.eof        is at " << reinterpret_cast<void*>(&testdata.eof);
        cout << "\n" << endl;
    }
    union {
        struct datastructure frame;
        char bytes[framelenght];
    } buffer;
    
    
    //--------------------- Cleaning -------------------------------------
    //clear all contents
    for(Int_t ichip = 0; ichip < chips_per_evt; ichip++)
    {
        readcheck[ichip] = 0;
    }
    
    // Cleaning all the vfats DataArray
    for (Int_t i=0; i<chips_per_evt; i++)  vfat_data[i]->Clear("C");
    
    // Cleaning all the detectors DataArray
    for (Int_t i=0; i<MaxNumbersOfDetDir; i++) g[i]->RemoveAllChannels();
    
    //  for (Int_t i=0; i<MaxNumbersOfDetDir; i++) gGeo[i]->RemoveAllChannels();
    // Using TClonesArray also for the geo, we have to replace the previous line with the following ones.
    //  tmpgeocluster.RemoveAllChannels();
    //  for (Int_t i=0; i<MaxNumbersOfDetDir; i++)  gGeo[i]->Clear();
    
    // Cleaning all the detectors Clusterization TClonesArray
    //   tmpcluster.RemoveAllChannels();
    //   for (Int_t i=0; i<MaxNumbersOfDetDir; i++)  gClustVect[i]->Clear("C");
    
    for (Int_t i=0; i<MaxNumbersOfDetDir; i++)
	{  
        gGeoClustVect[i]->Clear("C");
        geotmpcluster[i]->RemoveAllChannels();
	}
    //test cluster
    //ROOT BUG??!?! it seems that if I fill the first event with an
    //empty TClonesArray (as it was the case with the datafile used
    //during debugging), you get a crash when you Draw("XXXcl.ch"),
    //i.e. the union of all the hits of all the cluster. The workaround
    //here is just a fake filling of the TClonesArray with a cluster that
    //is after discarded
    
    /* FOR THE MOMENT THIS IS REMOVED..
     tmpcluster.InsertChannel(0);
     for (i=0; i<MaxNumbersOfDetDir; i++) 
     new((*(gClustVect[i]))[0]) Cluster(tmpcluster);
     tree.Fill();
     */
    
    //---------------End of Cleaning -------------------------------------
    
    
    
    //--------------- DATA READING ---------------------------------------
    
    Int_t iframe = 0;
    Int_t ievent = 0;
    Int_t errorstatus = 0;
    
    
    if(ifile.is_open())
    { 
        if(EBV_Verbose ==1)      cout << "File is open\n" << endl;
        
        while (ifile.good() && (!errorstatus) 
               && (iframe++ < chips_per_evt*readmaxevent))
     	{
            
            //if (EBV_Verbose >= 2) cout << "Reading at file position " << ifile.tellg() << endl;
            //cout << "Reading frame " << iframe << endl;
            
            
            //----------------------------------------------------------------------------------------
            //		READING OF THE FRAME
            //----------------------------------------------------------------------------------------
            
            //cout << "Reading Frame " << iframe << "...." << endl;
            ifile.read(buffer.bytes, framelenght);
            //cout << "..Done!" << endl;
            
            //----------------------------------------------------------------------------------------
            //		READING OF THE FRAME
            //----------------------------------------------------------------------------------------
            
            	  if (EBV_Verbose >= 2)
            	    {
               char lastfillchar = cout.fill('0');
               cout << "\nChecking a VFAT frame..\n" << hex<<"\trk\n";
               cout.width(4); cout << buffer.frame.bof << " ";
               cout.width(4); cout << buffer.frame.turboid << " ";
               cout.width(4); cout << buffer.frame.slotid  << " ";
               cout.width(4); cout << buffer.frame.fullid << " ";
               cout.width(4); cout << buffer.frame.trignum << " ";
               cout.width(4); cout << buffer.frame.timestamp << " ";
               cout.width(4); cout << buffer.frame.bc << " ";
               cout.width(4); cout << buffer.frame.ec << " ";
               cout.width(4); cout << buffer.frame.chipid << " ";
               cout.width(4); cout << buffer.frame.data[0] << " ";
               cout.width(4); cout << buffer.frame.data[1] << " ";
               cout.width(4); cout << buffer.frame.data[2] << " ";
               cout.width(4); cout << buffer.frame.data[3] << " ";
               cout.width(4); cout << buffer.frame.data[4] << " ";
               cout.width(4); cout << buffer.frame.data[5] << " ";
               cout.width(4); cout << buffer.frame.data[6] << " ";
               cout.width(4); cout << buffer.frame.data[7] << " ";
               cout.width(4); cout << buffer.frame.crc << " ";
               cout.width(4); cout << buffer.frame.eof << "\n" << dec << endl;
               cout.fill(lastfillchar);
            	    }
        //    cout << "Checking frames...." << endl;
	
	//cout<<"buffer.frame.bof & 0xFFF0  = "<<buffer.frame.bof & 0xFFF0<<endl;
            
        if ( ((buffer.frame.bof & 0xFFF0) == 0xB0F0)  && ((buffer.frame.eof & 0xFFF0) == 0xE0F0) )
     	    {
                // We Fill the Turbo and Slot Id of the VFAT (only in the first Event)
                if (ievent == 0)
                {
                    for(Int_t i=0; i<chips_per_evt; i++)
                    {
                        if (buffer.frame.fullid == (*VFAT[i]).ChipId) 
						{
							(*VFAT[i]).TurboId = buffer.frame.turboid;
							(*VFAT[i]).SlotId = buffer.frame.slotid;
							break;
						}
                    }
                }	  	
                
                
                
                
                // We Fill the Event Info in the Detectors Branches
                if (buffer.frame.fullid == chipID[0])
                {
                    EventInfo.EventNumber		=	ievent;
                    EventInfo.TriggerNumber		=	buffer.frame.trignum;
                    EventInfo.TimeStamp			=	buffer.frame.timestamp;
                    EventInfo.BunchCounter		=	(buffer.frame.bc & 0X0FFF);
                    EventInfo.EventCounter		=	(buffer.frame.ec & 0X0FF0)>>4;
                }
                
                Int_t ichip = -1;
                for (Int_t i = 0; i < chips_per_evt; i++)
                    if (buffer.frame.fullid == chipID[i])
                    {
                        ichip = i;
                        break;
                    };
                
                /////////////////////////////////////////////////////////////////////////////////////////
                //
                //          VFAT RAW DATA
                /////////////////////////////////////////////////////////////////////////////////////////
                if (ichip>= 0)
                {
                    if ( EBV_ChipIdVerbose  )  cout << "VFAT RAW DATA of Chip" << buffer.frame.fullid << " read in event "<< ievent << endl;
                    if (readcheck[ichip] > 1)
                    {
                        cout << "11 Data misalignment error on chip index "
                        << ichip << "\nat file position " << ifile.tellg()
                        << "\nat Chip ID " << buffer.frame.fullid
                        << "\nin detector " <<(*DET[chipdet[ichip]]).DetectorName
                        << "\nVFAT RAW DATA " 
                        << "\nEvent Number: " << ievent 
                        << endl;
                        errorstatus = 10;
                        break;
                    }
                    
                    // We Fill the Event Info in the VFAT Braches
                    vfat_data[ichip]->InsertEventInfo(
                                                      ievent,
                                                      buffer.frame.turboid,
                                                      buffer.frame.slotid,
                                                      buffer.frame.trignum,
                                                      buffer.frame.timestamp,
                                                      (buffer.frame.bc & 0X0FFF),
                                                      (buffer.frame.ec & 0X0FF0)>>4);
                    
                    Int_t vfat_lastchanblock = channels_per_chip-16;
                    for(Int_t offset=0; offset < 8; offset++)
                    {
                        Int_t vfat_rightblock = vfat_lastchanblock-(offset<<4);
                        
                        if (buffer.frame.data[offset] & 0x8000) vfat_data[ichip]->InsertChannel(vfat_rightblock+15); 
                        if (buffer.frame.data[offset] & 0x4000) vfat_data[ichip]->InsertChannel(vfat_rightblock+14);
                        if (buffer.frame.data[offset] & 0x2000) vfat_data[ichip]->InsertChannel(vfat_rightblock+13);
                        if (buffer.frame.data[offset] & 0x1000) vfat_data[ichip]->InsertChannel(vfat_rightblock+12);
                        if (buffer.frame.data[offset] & 0x0800) vfat_data[ichip]->InsertChannel(vfat_rightblock+11);
                        if (buffer.frame.data[offset] & 0x0400) vfat_data[ichip]->InsertChannel(vfat_rightblock+10);
                        if (buffer.frame.data[offset] & 0x0200) vfat_data[ichip]->InsertChannel(vfat_rightblock+9 );
                        if (buffer.frame.data[offset] & 0x0100) vfat_data[ichip]->InsertChannel(vfat_rightblock+8 );
                        if (buffer.frame.data[offset] & 0x0080) vfat_data[ichip]->InsertChannel(vfat_rightblock+7 );
                        if (buffer.frame.data[offset] & 0x0040) vfat_data[ichip]->InsertChannel(vfat_rightblock+6 );
                        if (buffer.frame.data[offset] & 0x0020) vfat_data[ichip]->InsertChannel(vfat_rightblock+5 );
                        if (buffer.frame.data[offset] & 0x0010) vfat_data[ichip]->InsertChannel(vfat_rightblock+4 );
                        if (buffer.frame.data[offset] & 0x0008) vfat_data[ichip]->InsertChannel(vfat_rightblock+3 );
                        if (buffer.frame.data[offset] & 0x0004) vfat_data[ichip]->InsertChannel(vfat_rightblock+2 );
                        if (buffer.frame.data[offset] & 0x0002) vfat_data[ichip]->InsertChannel(vfat_rightblock+1 );
                        if (buffer.frame.data[offset] & 0x0001) vfat_data[ichip]->InsertChannel(vfat_rightblock+0 );
                    }
                }
                /////////////////////////////////////////////////////////////////////////////////////////
                //
                //          VFAT RAW DATA
                //
                /////////////////////////////////////////////////////////////////////////////////////////
                
                
                
                /////////////////////////////////////////////////////////////////////////////////////////
                //
                //          TRACKER & Timing  
                //
                /////////////////////////////////////////////////////////////////////////////////////////
                
               
                if ( (ichip>= 0) && (chipdet[ichip]<6) ) 
                {
                     
//                    cout << "TRACKER and Timing   "<<"ChipId: " << ichip << " DetId: " << chipdet[ichip] << endl;
                    // I mark this chip as read
                    readcheck[ichip]++;
                    if ( EBV_ChipIdVerbose  )  cout << "Chip " << buffer.frame.fullid << " read in event "<< ievent << endl;
                    if (readcheck[ichip] > 1) 
                    {
                        cout << "22 Data misalignment error on chip index "
                        << ichip << "\nat file position " << ifile.tellg() 
                        << "\nat Chip ID " << buffer.frame.fullid
                        << "\nin detector " <<(*DET[chipdet[ichip]]).DetectorName
                        << "\nTracker Filling" 
                        << "\nEvent Number: " << ievent 
                        << endl;
                        errorstatus = 10;
                        break;
                    }
                    
                    if (!chipinvert[ichip])
                    {
                        Int_t lastchanblock = channels_per_chip-16;
                        for(Int_t offset=0; offset < 8; offset++)
                        {
                            //I write explicitely instead of using a for loop, hoping to save some cpu time
                            //offset<<4 is a bit shift of 4 places, that is equivalent to a multiplication by 16 but
                            //it is more cpu time cheap
                            Int_t rightblock = lastchanblock-(offset<<4);
                            
                            if (buffer.frame.data[offset] & 0x8000) g[chipdet[ichip]]->InsertChannel(rightblock+15+ chipoffset[ichip]); 
                            if (buffer.frame.data[offset] & 0x4000) g[chipdet[ichip]]->InsertChannel(rightblock+14+ chipoffset[ichip]);
                            if (buffer.frame.data[offset] & 0x2000) g[chipdet[ichip]]->InsertChannel(rightblock+13+ chipoffset[ichip]);
                            if (buffer.frame.data[offset] & 0x1000) g[chipdet[ichip]]->InsertChannel(rightblock+12+ chipoffset[ichip]);
                            if (buffer.frame.data[offset] & 0x0800) g[chipdet[ichip]]->InsertChannel(rightblock+11+ chipoffset[ichip]);
                            if (buffer.frame.data[offset] & 0x0400) g[chipdet[ichip]]->InsertChannel(rightblock+10+ chipoffset[ichip]);
                            if (buffer.frame.data[offset] & 0x0200) g[chipdet[ichip]]->InsertChannel(rightblock+9 + chipoffset[ichip]);
                            if (buffer.frame.data[offset] & 0x0100) g[chipdet[ichip]]->InsertChannel(rightblock+8 + chipoffset[ichip]);
                            if (buffer.frame.data[offset] & 0x0080) g[chipdet[ichip]]->InsertChannel(rightblock+7 + chipoffset[ichip]);
                            if (buffer.frame.data[offset] & 0x0040) g[chipdet[ichip]]->InsertChannel(rightblock+6 + chipoffset[ichip]);
                            if (buffer.frame.data[offset] & 0x0020) g[chipdet[ichip]]->InsertChannel(rightblock+5 + chipoffset[ichip]);
                            if (buffer.frame.data[offset] & 0x0010) g[chipdet[ichip]]->InsertChannel(rightblock+4 + chipoffset[ichip]);
                            if (buffer.frame.data[offset] & 0x0008) g[chipdet[ichip]]->InsertChannel(rightblock+3 + chipoffset[ichip]);
                            if (buffer.frame.data[offset] & 0x0004) g[chipdet[ichip]]->InsertChannel(rightblock+2 + chipoffset[ichip]);
                            if (buffer.frame.data[offset] & 0x0002) g[chipdet[ichip]]->InsertChannel(rightblock+1 + chipoffset[ichip]);
                            if (buffer.frame.data[offset] & 0x0001) g[chipdet[ichip]]->InsertChannel(rightblock+0 + chipoffset[ichip]);
                        }
                    }
                    else
                    {
                        for(Int_t offset=0; offset < 8; offset++)
                        {
                            Int_t rightblock = offset<<4;
                            if (buffer.frame.data[offset] & 0x8000) g[chipdet[ichip]]->InsertChannel(rightblock+0 + chipoffset[ichip]);
                            if (buffer.frame.data[offset] & 0x4000) g[chipdet[ichip]]->InsertChannel(rightblock+1 + chipoffset[ichip]);
                            if (buffer.frame.data[offset] & 0x2000) g[chipdet[ichip]]->InsertChannel(rightblock+2 + chipoffset[ichip]);
                            if (buffer.frame.data[offset] & 0x1000) g[chipdet[ichip]]->InsertChannel(rightblock+3 + chipoffset[ichip]);
                            if (buffer.frame.data[offset] & 0x0800) g[chipdet[ichip]]->InsertChannel(rightblock+4 + chipoffset[ichip]);
                            if (buffer.frame.data[offset] & 0x0400) g[chipdet[ichip]]->InsertChannel(rightblock+5 + chipoffset[ichip]);
                            if (buffer.frame.data[offset] & 0x0200) g[chipdet[ichip]]->InsertChannel(rightblock+6 + chipoffset[ichip]);
                            if (buffer.frame.data[offset] & 0x0100) g[chipdet[ichip]]->InsertChannel(rightblock+7 + chipoffset[ichip]);
                            if (buffer.frame.data[offset] & 0x0080) g[chipdet[ichip]]->InsertChannel(rightblock+8 + chipoffset[ichip]);
                            if (buffer.frame.data[offset] & 0x0040) g[chipdet[ichip]]->InsertChannel(rightblock+9 + chipoffset[ichip]);
                            if (buffer.frame.data[offset] & 0x0020) g[chipdet[ichip]]->InsertChannel(rightblock+10+ chipoffset[ichip]);
                            if (buffer.frame.data[offset] & 0x0010) g[chipdet[ichip]]->InsertChannel(rightblock+11+ chipoffset[ichip]);
                            if (buffer.frame.data[offset] & 0x0008) g[chipdet[ichip]]->InsertChannel(rightblock+12+ chipoffset[ichip]);
                            if (buffer.frame.data[offset] & 0x0004) g[chipdet[ichip]]->InsertChannel(rightblock+13+ chipoffset[ichip]);
                            if (buffer.frame.data[offset] & 0x0002) g[chipdet[ichip]]->InsertChannel(rightblock+14+ chipoffset[ichip]);
                            if (buffer.frame.data[offset] & 0x0001) g[chipdet[ichip]]->InsertChannel(rightblock+15+ chipoffset[ichip]);
                        }
                    }
                } 
                /////////////////////////////////////////////////////////////////////////////////////////
                //
                //          TRACKER   
                //
                /////////////////////////////////////////////////////////////////////////////////////////
                
                
                
                
                /////////////////////////////////////////////////////////////////////////////////////////
                //
                //          CMS Guest 
                //
                /////////////////////////////////////////////////////////////////////////////////////////
                
	 	if ( (ichip>=0) &&  (chipdet[ichip] >= 6) )
                {
                    //cout << "CMS ChipId: " << ichip << " DetId: " << chipdet[ichip] << endl;
                    // I mark this chip as read
                    readcheck[ichip]++;
                    if ( EBV_ChipIdVerbose  )  cout << "Chip " << buffer.frame.fullid << " read in event "<< ievent << endl;
                    if (readcheck[ichip] > 1) 
                    {
                        cout << "33 Data misalignment error on chip index "
                        << ichip << "\nat file position " << ifile.tellg() 
                        << "\nat Chip ID " << buffer.frame.fullid
                        << "\nin detector " <<(*DET[chipdet[ichip]]).DetectorName
                        << "\nCMS Guest Filling" 
                        << "\nEvent Number: " << ievent 
                        << endl;
                        errorstatus = 10;
                        break;
                    }
                    
                    if (!chipinvert[ichip])
                    {
                        Int_t lastchanblock = channels_per_chip-16;
                        for(Int_t offset=0; offset < 8; offset++)
                        {
                            Int_t rightblock = lastchanblock-(offset<<4);
                            
                            if (buffer.frame.data[offset] & 0x8000) g[chipdet[ichip]]->InsertChannel(rightblock+15+ chipoffset[ichip]); 
                            if (buffer.frame.data[offset] & 0x4000) g[chipdet[ichip]]->InsertChannel(rightblock+14+ chipoffset[ichip]);
                            if (buffer.frame.data[offset] & 0x2000) g[chipdet[ichip]]->InsertChannel(rightblock+13+ chipoffset[ichip]);
                            if (buffer.frame.data[offset] & 0x1000) g[chipdet[ichip]]->InsertChannel(rightblock+12+ chipoffset[ichip]);
                            if (buffer.frame.data[offset] & 0x0800) g[chipdet[ichip]]->InsertChannel(rightblock+11+ chipoffset[ichip]);
                            if (buffer.frame.data[offset] & 0x0400) g[chipdet[ichip]]->InsertChannel(rightblock+10+ chipoffset[ichip]);
                            if (buffer.frame.data[offset] & 0x0200) g[chipdet[ichip]]->InsertChannel(rightblock+9 + chipoffset[ichip]);
                            if (buffer.frame.data[offset] & 0x0100) g[chipdet[ichip]]->InsertChannel(rightblock+8 + chipoffset[ichip]);
                            if (buffer.frame.data[offset] & 0x0080) g[chipdet[ichip]]->InsertChannel(rightblock+7 + chipoffset[ichip]);
                            if (buffer.frame.data[offset] & 0x0040) g[chipdet[ichip]]->InsertChannel(rightblock+6 + chipoffset[ichip]);
                            if (buffer.frame.data[offset] & 0x0020) g[chipdet[ichip]]->InsertChannel(rightblock+5 + chipoffset[ichip]);
                            if (buffer.frame.data[offset] & 0x0010) g[chipdet[ichip]]->InsertChannel(rightblock+4 + chipoffset[ichip]);
                            if (buffer.frame.data[offset] & 0x0008) g[chipdet[ichip]]->InsertChannel(rightblock+3 + chipoffset[ichip]);
                            if (buffer.frame.data[offset] & 0x0004) g[chipdet[ichip]]->InsertChannel(rightblock+2 + chipoffset[ichip]);
                            if (buffer.frame.data[offset] & 0x0002) g[chipdet[ichip]]->InsertChannel(rightblock+1 + chipoffset[ichip]);
                            if (buffer.frame.data[offset] & 0x0001) g[chipdet[ichip]]->InsertChannel(rightblock+0 + chipoffset[ichip]);
                        }
                    }
                    else
                    {
                        for(Int_t offset=0; offset < 8; offset++)
                        {
                            Int_t rightblock = offset<<4;
                            if (buffer.frame.data[offset] & 0x8000) g[chipdet[ichip]]->InsertChannel(rightblock+0 + chipoffset[ichip]);
                            if (buffer.frame.data[offset] & 0x4000) g[chipdet[ichip]]->InsertChannel(rightblock+1 + chipoffset[ichip]);
                            if (buffer.frame.data[offset] & 0x2000) g[chipdet[ichip]]->InsertChannel(rightblock+2 + chipoffset[ichip]);
                            if (buffer.frame.data[offset] & 0x1000) g[chipdet[ichip]]->InsertChannel(rightblock+3 + chipoffset[ichip]);
                            if (buffer.frame.data[offset] & 0x0800) g[chipdet[ichip]]->InsertChannel(rightblock+4 + chipoffset[ichip]);
                            if (buffer.frame.data[offset] & 0x0400) g[chipdet[ichip]]->InsertChannel(rightblock+5 + chipoffset[ichip]);
                            if (buffer.frame.data[offset] & 0x0200) g[chipdet[ichip]]->InsertChannel(rightblock+6 + chipoffset[ichip]);
                            if (buffer.frame.data[offset] & 0x0100) g[chipdet[ichip]]->InsertChannel(rightblock+7 + chipoffset[ichip]);
                            if (buffer.frame.data[offset] & 0x0080) g[chipdet[ichip]]->InsertChannel(rightblock+8 + chipoffset[ichip]);
                            if (buffer.frame.data[offset] & 0x0040) g[chipdet[ichip]]->InsertChannel(rightblock+9 + chipoffset[ichip]);
                            if (buffer.frame.data[offset] & 0x0020) g[chipdet[ichip]]->InsertChannel(rightblock+10+ chipoffset[ichip]);
                            if (buffer.frame.data[offset] & 0x0010) g[chipdet[ichip]]->InsertChannel(rightblock+11+ chipoffset[ichip]);
                            if (buffer.frame.data[offset] & 0x0008) g[chipdet[ichip]]->InsertChannel(rightblock+12+ chipoffset[ichip]);
                            if (buffer.frame.data[offset] & 0x0004) g[chipdet[ichip]]->InsertChannel(rightblock+13+ chipoffset[ichip]);
                            if (buffer.frame.data[offset] & 0x0002) g[chipdet[ichip]]->InsertChannel(rightblock+14+ chipoffset[ichip]);
                            if (buffer.frame.data[offset] & 0x0001) g[chipdet[ichip]]->InsertChannel(rightblock+15+ chipoffset[ichip]);
                        }
                    }
                } 
                /////////////////////////////////////////////////////////////////////////////////////////
                //
                //          CMS Guest 
                //
                /////////////////////////////////////////////////////////////////////////////////////////
                
                
                
                
                
     	    } //end of "if ( (buffer.frame.bof & 0x0FFF) == 0x0B0F .. etc.."
            else
            {
                cout << "Wrong Beginning \"BOFO\" or End \"EOF0\" of Frame" << endl;
            }
            
            ////////////////////////////////////////////////////////////////////////////////////
            //
            // Conversion into Spatial Coordinate Rootine
            //
            // Clusterization Routine
            //
            ///////////////////////////////////////////////////////////////////////////////////
            
            Int_t newevent = 0;
            for (Int_t i = 0; i < chips_per_evt; i++)
     	    {
                // readcheck is set to one after having read the frame of the corresponding chip.		
                if (readcheck[i]) newevent++;
                //cout << "i = "  << i << " readcheck[i]= " << readcheck[i] << endl;
     	    }
            
            // This part is done when all the chips have been read.     
            if (newevent == chips_per_evt)
     	    {
                // TClonesArray* gGeoClustVect[MaxNumbersOfDetDir]; //Geo+Cluster
                // for (Int_t i=0; i<MaxNumbersOfDetDir; i++)
                // gGeoClustVect[i] = new TClonesArray("GeoCluster", MaxNumOfClusters[i]/5);
                
                for (Int_t idet = 0; idet < MaxNumbersOfDetDir; idet++)
                {
                    //-----------------------------------------------------------------------------------------------------------------------------------------------------------
                    //cout << "Begin of the Conversion into Spatial Coordinate routine..." << endl;
                    //-----------------------------------------------------------------------------------------------------------------------------------------------------------
                    
                    //--- Using TClonesArray: gGeo[idet]->Clear();
                    if ( ((*g[idet]).nch) > 0 )
                    {
                        gGeo[idet]->RemoveAllChannels();
                        //--- Using TClonesArray: Int_t igeocluster = 0;
                        for (Int_t ich = 0; ich < (*g[idet]).nch; ich++)
                        {
                            gGeo[idet]->InsertChannel(TypeOfReadout[idet], (*DET[idet]).OffsetHorizontal, (*DET[idet]).OffsetVertical, (*DET[idet]).FlipHorizontal, (*DET[idet]).FlipVertical, (*g[idet]).ch[ich] );
                            //--- Using TClonesArray:tmpgeocluster.RemoveAllChannels();
                            //--- Using TClonesArray:tmpgeocluster.InsertChannel((*g[idet]).ch[ich]); 
                            //--- Using TClonesArray:new((*(gGeo[idet]))[igeocluster++]) GeoDataArray(tmpgeocluster);
                        }
                    }
                    
                    //-----------------------------------------------------------------------------------------------------------------------------------------------------------
                    //cout << "End of the Conversion into Spatial Coordinate routine..." << endl;
                    //-----------------------------------------------------------------------------------------------------------------------------------------------------------
                    
                    //-----------------------------------------------------------------------------------------------------------------------------------------------------------
                    //cout << "Begin of the GeoClusterization routine..." << endl;
                    //-----------------------------------------------------------------------------------------------------------------------------------------------------------
                    
                    gGeoClustVect[idet]->Clear("C");
                    
                    for (Int_t i=0; i<MaxPossibleHits; i++)
                        geoalreadyused[i] = false;
                    
                    Int_t geocs = 0;
                    Int_t igeocluster = 0;
                    
                    do 
                    {
                        geotmpcluster[idet]->RemoveAllChannels();
                        geocs = FindGeoCluster(	TypeOfReadout[idet], 
                                               (*DET[idet]).OffsetHorizontal, 
                                               (*DET[idet]).OffsetVertical, 
                                               (*DET[idet]).FlipHorizontal, 
                                               (*DET[idet]).FlipVertical, 
                                               MaxDistInCluster[idet], 
                                               PeriodicityInCluster[idet],
                                               MaxDistPeriodicityInCluster[idet],
                                               *gGeo[idet],geoalreadyused,*geotmpcluster[idet]); 
                        //Insert this function into a kind of LookForClusters
                        if (geocs) 
                        {
                            geotmpcluster[idet]->UpdatePos();
                            new ( (*(gGeoClustVect[idet]))[igeocluster++]) GeoCluster(*geotmpcluster[idet]);
                        }
                    } while ( geocs && (igeocluster < MaxNumOfClusters[idet]) );
                    
                    //-----------------------------------------------------------------------------------------------------------------------------------------------------------
                    //cout << "End of the Clusterization routine..." << endl;
                    //-----------------------------------------------------------------------------------------------------------------------------------------------------------
                } 
                
                //if (EBV_Verbose >= 1) cout << "Filling Tree" << endl;
                
                tree_raw->Fill();
                tree_geo->Fill();
                
                ievent++;
                if (ievent%100 == 0 && EBV_Verbose==1) cout << "Processing event " 
                    << ievent << "\r" << flush;
                //clear all contents
                for(Int_t ichip = 0; ichip < chips_per_evt; ichip++)
                {
                    readcheck[ichip] = 0;
                }
                for (Int_t i=0; 	i<MaxNumbersOfDetDir; 	i++) 	g[i]->RemoveAllChannels();
                for (Int_t i=0; 	i<MaxNumbersOfDetDir; 	i++) 	gGeo[i]->RemoveAllChannels(); 
                //--- Using TClonesArray: for (Int_t i=0; 	i<MaxNumbersOfDetDir; 	i++) 	gGeo[i]->Clear(); 
                for (Int_t i=0;   i<MaxNumbersOfDetDir;   i++)	geotmpcluster[i]->RemoveAllChannels();
                for (Int_t i=0; 	i<MaxNumbersOfDetDir; 	i++) 	gGeoClustVect[i]->Clear("C");
                for (Int_t i=0; 	i<chips_per_evt; 	i++) 	vfat_data[i]->RemoveAllChannels();
                
                //   for (Int_t i=0; i<MaxNumbersOfDetDir; i++)  delete gGeoClustVect[i];
     	    }
            
            /////////////////////////////////////////////////////////////////////////////////////////
            //
            // Conversion into Spatial Coordinate Rootine
            //
            // Clusterization Routine
            //
            /////////////////////////////////////////////////////////////////////////////////////////
            
            
     	} 
        // end of "while (ifile.good() && (!errorstatus) .. etc .."
        
    } 
    // end of "if(ifile.is_open())"
    
    
    
    ifile.close();
    
    if (EBV_Verbose ==1)  cout << "Processed " << ievent << " events\n" << endl;
    
    tree_conf->Fill();
    
    tree_conf->Write();	
    tree_raw->Write();
    //---Original  tree.Write();
    tree_geo->Write();
    
    //  tree_conf->Print();
    //  tree_raw->Print();
    //  tree.Print();
    //  tree_geo->Print();
    
    TCanvas *c1 = new TCanvas("c1","ROOT Canvas",10,10,1200,600);
    
    
    
    
    //cout << "---------------------------------------------------------------------------------" << endl;
    //cout << "---  BEAM PROFILE AND RELATIVE ALIGNMENT ----------------------------------------" << endl;
    //cout << "---------------------------------------------------------------------------------" << endl;
    
    for (Int_t i=0; i<chips_per_evt; i++)
    {
        if((*VFAT[i]).DetectorName == "g1")
        {	
            //TH2F *hg1BeamProfile = new TH2F("hg1BeamProfile","Beam profile on Tracker 1", 1000,-200.,200.,1000,-200.,200.);
            TH2F *hg1BeamProfile = new TH2F("hg1BeamProfile","Beam profile on Tracker 1", 100,0.,100.,100,0.,100.);
            //tree_geo->Draw("g1ycl.geoposY:g1xcl.geoposX>>hg1BeamProfile","g1ycl@.GetEntries()==1 && g1xcl@.GetEntries()==1","lego2");
            tree_geo->Draw("g1ycl.geoposY:g1xcl.geoposX>>hg1BeamProfile","g1ycl@.GetEntries()==1 && g1xcl@.GetEntries()==1","colz");
            hg1BeamProfile->Write();
            if (EBV_BeampProfiledataPrintOut==1 && EBV_Verbose==0)
            {
                cout << rawfilename; 	
                cout << " g1yBeamMean: "<< hg1BeamProfile->GetMean(2) << " g1yBeamRMS: "<< hg1BeamProfile->GetRMS(2) 
                << " g1xBeamMean: "<< hg1BeamProfile->GetMean(1) << " g1xBeamRMS: "<< hg1BeamProfile->GetRMS(1);
            }
            if (EBV_BeampProfiledataPrintOut==1 && EBV_Verbose==1)
            {
                BlueOut("\nTRACKERS BEAM PROFILE DATA ......................................................................\n"); 	
                BlueOut("Detector\tYMean\t\tYRMS\t\tXMean\t\tXRMS\t\tDY\t\tDYRMS\t\tDX\t\tDXRMS\t\tENTRIES\n"); 	
                printf("g1\t\t%-.3f\t\t%-.3f\t\t%-.3f\t\t%-.3f\t\t0.000\t\t0.000\t\t0.000\t\t0.000\t\t%-.0f\n",	
                       hg1BeamProfile->GetMean(2)   ,hg1BeamProfile->GetRMS(2)  ,hg1BeamProfile->GetMean(1)  ,hg1BeamProfile->GetRMS(1),
                       hg1BeamProfile->GetEntries());
            }
            break;
        }
    }	
    
    for (Int_t i=0; i<chips_per_evt; i++)
    {
        if((*VFAT[i]).DetectorName == "g2")
        {
            //TH2F *hg2BeamProfile = new TH2F("hg2BeamProfile","Beam profile on Tracker 2", 1000,-200.,200.,1000,-200.,200.);
            //tree_geo->Draw("g2ycl.geoposY:g2xcl.geoposX>>hg2BeamProfile","g2ycl@.GetEntries()==1 && g2xcl@.GetEntries()==1","Lego2");
            TH2F *hg2BeamProfile = new TH2F("hg2BeamProfile","Beam profile on Tracker 2", 100,0.,100.,100,0.,100.);
            tree_geo->Draw("g2ycl.geoposY:g2xcl.geoposX>>hg2BeamProfile","g2ycl@.GetEntries()==1 && g2xcl@.GetEntries()==1","colz");
            hg2BeamProfile->Write();
            
            TH1F *hg2xoffsetwithg1 = new TH1F("hg2xoffsetwithg1","X Offset of Tracker 2 respect with Tracker 1", 500,-100.,100.);
            tree_geo->Draw("g2xcl.geoposX-g1xcl.geoposX>>hg2xoffsetwithg1","g2xcl@.GetEntries()==1 && g1xcl@.GetEntries()==1","Lego2");
            //hg2xoffsetwithg1->Write();
            TH1F *hg2yoffsetwithg1 = new TH1F("hg2yoffsetwithg1","Y Offset of Tracker 2 respect with Tracker 1", 500,-100.,100.);
            tree_geo->Draw("g2ycl.geoposY-g1ycl.geoposY>>hg2yoffsetwithg1","g2ycl@.GetEntries()==1 && g1ycl@.GetEntries()==1","Lego2");
            //hg2yoffsetwithg1->Write();
            if (EBV_BeampProfiledataPrintOut==1 && EBV_Verbose==0)
            {
                cout << " g2yBeamMean: "<< hg2BeamProfile->GetMean(2) << " g2yBeamRMS: "<< hg2BeamProfile->GetRMS(2) 
                << " g2xBeamMean: "<< hg2BeamProfile->GetMean(1) << " g2xBeamRMS: "<< hg2BeamProfile->GetRMS(1);
                cout << " g2-g1yoffset:"<< hg2yoffsetwithg1->GetMean() << " g2-g1yoffsetRMS:"<< hg2yoffsetwithg1->GetRMS() 
                << " g2-g1xoffset:"<< hg2xoffsetwithg1->GetMean() << " g2-g1xoffsetRMS:"<< hg2xoffsetwithg1->GetRMS(); 
            }
            if (EBV_BeampProfiledataPrintOut==1 && EBV_Verbose==1)
            {
                printf("g2\t\t%-.3f\t\t%-.3f\t\t%-.3f\t\t%-.3f\t\t%-.3f\t\t%-.3f\t\t%-.3f\t\t%-.3f\t\t%-.0f\n",	
                       hg2BeamProfile->GetMean(2)   ,hg2BeamProfile->GetRMS(2)  ,hg2BeamProfile->GetMean(1)  ,hg2BeamProfile->GetRMS(1),
                       hg2yoffsetwithg1->GetMean()  ,hg2yoffsetwithg1->GetRMS() ,hg2xoffsetwithg1->GetMean() ,hg2xoffsetwithg1->GetRMS(),
                       hg2BeamProfile->GetEntries());
            }
            
            break;
        }
    }	
    
    for (Int_t i=0; i<chips_per_evt; i++)
    {
        if((*VFAT[i]).DetectorName == "g3")
        {
            //TH2F *hg3BeamProfile = new TH2F("hg3BeamProfile","Beam profile on Tracker 3", 1000,-200.,200.,1000,-200.,200.);
            //tree_geo->Draw("g3ycl.geoposY:g3xcl.geoposX>>hg3BeamProfile","g3ycl@.GetEntries()==1 && g3xcl@.GetEntries()==1","Lego2");
            TH2F *hg3BeamProfile = new TH2F("hg3BeamProfile","Beam profile on Tracker 3", 100,0.,100.,100,0.,100.);
            tree_geo->Draw("g3ycl.geoposY:g3xcl.geoposX>>hg3BeamProfile","g3ycl@.GetEntries()==1 && g3xcl@.GetEntries()==1","colz");
            hg3BeamProfile->Write();
            
            TH1F *hg3xoffsetwithg1 = new TH1F("hg3xoffsetwithg1","X Offset of Tracker 3 respect with Tracker 1", 500,-100.,100.);
            tree_geo->Draw("g3xcl.geoposX-g1xcl.geoposX>>hg3xoffsetwithg1","g3xcl@.GetEntries()==1 && g1xcl@.GetEntries()==1","Lego2");
            //hg3xoffsetwithg1->Write();
            TH1F *hg3yoffsetwithg1 = new TH1F("hg3yoffsetwithg1","Y Offset of Tracker 3 respect with Tracker 1", 500,-100.,100.);
            tree_geo->Draw("g3ycl.geoposY-g1ycl.geoposY>>hg3yoffsetwithg1","g3ycl@.GetEntries()==1 && g1ycl@.GetEntries()==1","Lego2");
            //hg3yoffsetwithg1->Write();
            if (EBV_BeampProfiledataPrintOut==1 && EBV_Verbose==0)
            {
                cout << " g3yBeamMean: "<< hg3BeamProfile->GetMean(2) << " g3yBeamRMS: "<< hg3BeamProfile->GetRMS(2) 
                << " g3xBeamMean: "<< hg3BeamProfile->GetMean(1) << " g3xBeamRMS: "<< hg3BeamProfile->GetRMS(1);
                cout << " g3-g1yoffset:"<< hg3yoffsetwithg1->GetMean() << " g3-g1yoffsetRMS:"<< hg3yoffsetwithg1->GetRMS() 
                << " g3-g1xoffset:"<< hg3xoffsetwithg1->GetMean() << " g3-g1xoffsetRMS:"<< hg3xoffsetwithg1->GetRMS(); 
            }
            if (EBV_BeampProfiledataPrintOut==1 && EBV_Verbose==1)
            {
                printf("g3\t\t%-.3f\t\t%-.3f\t\t%-.3f\t\t%-.3f\t\t%-.3f\t\t%-.3f\t\t%-.3f\t\t%-.3f\t\t%-.0f\n",	
                       hg3BeamProfile->GetMean(2)   ,hg3BeamProfile->GetRMS(2)  ,hg3BeamProfile->GetMean(1)  ,hg3BeamProfile->GetRMS(1),
                       hg3yoffsetwithg1->GetMean()  ,hg3yoffsetwithg1->GetRMS() ,hg3xoffsetwithg1->GetMean() ,hg3xoffsetwithg1->GetRMS(),
                       hg3BeamProfile->GetEntries());
            }
            
            break;
        }
    }	
    
    
    
    
    //--- XLoop on the declared detectors -------------------------------------------------------------------------------------------------
    TString xref;
    bool 	xdet_exist;
    Float_t 	xdet_xcoord_mean=0., xdet_xcoord_rms=0., xmeanoff=999., xrmsoff=999.;
    Int_t 	xentriesoff=0;
    TString 	xdet, xdet_xcoord, xdet_xcoord_name, hxdet_name, hxdet_title, hxdet_draw, hx_cut;
    Int_t	xrefid=0;	
    
    if (EBV_BeampProfiledataPrintOut==1 && EBV_Verbose==1)
    {
        BlueOut("\nDetector XOffset DATA ......................................................................\n"); 	
        BlueOut("Entries\t\tXMean\t\tXRMS\t\tDX\t\tDXRMS\t\tDetector\n"); 	
        
    }
    
    for (Int_t i=0; i<MaxNumbersOfDetDir; i++)
    {
        xmeanoff=999.; xrmsoff=999.; xentriesoff=0;
        
        xref = (*DET[xrefid]).DetectorName;
        xdet = (*DET[i]).DetectorName;
        
        TH1F *hxcoordtmp = new TH1F("hxcoordtmp", "hxcoordtmp", 100,-1000.,1000.);
        xdet_xcoord = xdet + ".geoposX";
        xdet_xcoord_name = xdet_xcoord + ">> hxcoordtmp"; 
        tree_geo->Draw(xdet_xcoord_name);
        xdet_xcoord_mean = hxcoordtmp->GetMean();
        xdet_xcoord_rms = hxcoordtmp->GetRMS();
        if (xdet_xcoord_rms!=0 && xdet_xcoord_mean!=999) {xdet_exist = 1;} else {xdet_exist = 0;};
        
        if (xdet_exist)
        {
            hxdet_name = "hXOffset_" + xdet + "_" + xref;
            hxdet_title= "X Offset of " + xdet + " respect with " + xref;
            hxdet_draw = xdet + ".geoposX"+"-"+ xref + ".geoposX" + ">>" + hxdet_name;
            hx_cut  = xref + "@.GetEntries()==1" + " && " + xdet + "@.GetEntries()==1"; 
            char hxdet[hxdet_name.Length()];
            sprintf(hxdet,"%s",(const char *)hxdet_name);
	        TH1F *hxdetPtr;
            hxdetPtr=(TH1F*)hxdet;
            
            tree_geo->Draw(xdet_xcoord_name, hx_cut);
            xdet_xcoord_mean = hxcoordtmp->GetMean();
            xdet_xcoord_rms = hxcoordtmp->GetRMS();
            
            hxdetPtr = new TH1F(hxdet_name, hxdet_title, 500,-100.,100.);
            tree_geo->Draw(hxdet_draw, hx_cut);
            xmeanoff = hxdetPtr->GetMean();
            xrmsoff = hxdetPtr->GetRMS();
            xentriesoff = hxdetPtr->GetEntries();
            hxdetPtr->Write();
            delete hxdetPtr;
        }
        
        delete hxcoordtmp;
        
        /*
         if (EBV_BeampProfiledataPrintOut==1 && EBV_Verbose==0)
         {
         cout << " g4yBeamMean: "<< hg4BeamProfile->GetMean(2) << " g4yBeamRMS: "<< hg4BeamProfile->GetRMS(2) 
	     << " g4xBeamMean: "<< hg4BeamProfile->GetMean(1) << " g4xBeamRMS: "<< hg4BeamProfile->GetRMS(1);
         cout << " g4-g1yoffset:"<< hg4yoffsetwithg1->GetMean() << " g4-g1yoffsetRMS:"<< hg4yoffsetwithg1->GetRMS() 
   	     << " g4-g1xoffset:"<< hg4xoffsetwithg1->GetMean() << " g4-g1xoffsetRMS:"<< hg4xoffsetwithg1->GetRMS(); 
         }
         */
        if (EBV_BeampProfiledataPrintOut==1 && EBV_Verbose==1)
        {
            if (xentriesoff>0) printf("%d\t\t%-.3f\t\t%-.3f\t\t%-.3f\t\t%-.3f\t\t%s\n", 
                                      xentriesoff, xdet_xcoord_mean, xdet_xcoord_rms, xmeanoff, xrmsoff,(const char*)(*DET[i]).DetectorName);
        }
    }
    if (EBV_BeampProfiledataPrintOut==1 && EBV_Verbose==1)
    {
        BlueOut(".................................................................................................\n\n"); 	
    }
    //--- XLoop on the declared detectors -------------------------------------------------------------------------------------------------
    
    //--- YLoop on the declared detectors -------------------------------------------------------------------------------------------------
    
    TString yref;
    bool 	ydet_exist;
    Float_t 	ydet_ycoord_mean=0., ydet_ycoord_rms=0., ymeanoff=999., yrmsoff=999.;
    Int_t 	yentriesoff=0;
    TString 	ydet, ydet_ycoord, ydet_ycoord_name, hydet_name, hydet_title, hydet_draw, hy_cut;
    Int_t 	yrefid=1;
    
    if (EBV_BeampProfiledataPrintOut==1 && EBV_Verbose==1)
    {
        BlueOut("\nDetector YOffset DATA ......................................................................\n"); 	
        BlueOut("Entries\t\tYMean\t\tYRMS\t\tDY\t\tDYRMS\t\tDetector\n"); 	
        
    }
    
    for (Int_t i=0; i<MaxNumbersOfDetDir; i++)
    {
        ymeanoff=999.; yrmsoff=999.; yentriesoff=0;
        
        yref = (*DET[yrefid]).DetectorName;
        ydet = (*DET[i]).DetectorName;
        
        
        TH1F *hycoordtmp = new TH1F("hycoordtmp", "hycoordtmp", 100,-1000.,1000.);
        ydet_ycoord = ydet + ".geoposY";
        ydet_ycoord_name = ydet_ycoord + ">> hycoordtmp"; 
        tree_geo->Draw(ydet_ycoord_name);
        ydet_ycoord_mean = hycoordtmp->GetMean();
        ydet_ycoord_rms = hycoordtmp->GetRMS();
        if (ydet_ycoord_rms!=0 && ydet_ycoord_mean!=999) {ydet_exist = 1;} else {ydet_exist = 0;};
        
        
        if (ydet_exist)
        {
            ydet = (*DET[i]).DetectorName;
            hydet_name = "hYOffset_" + ydet + "_" + yref;
            hydet_title= "Y Offset of " + ydet + " respect with " + yref;
            hydet_draw = ydet + ".geoposY"+"-"+ yref + ".geoposY" + ">>" + hydet_name;
            hy_cut  = yref + "@.GetEntries()==1" + " && " + ydet + "@.GetEntries()==1"; 
            char hydet[hydet_name.Length()];
            sprintf(hydet,"%s",(const char *)hydet_name);
	        TH1F *hydetPtr;
            hydetPtr=(TH1F*)hydet;
            
            tree_geo->Draw(ydet_ycoord_name,hy_cut);
            ydet_ycoord_mean = hycoordtmp->GetMean();
            ydet_ycoord_rms = hycoordtmp->GetRMS();
            
            hydetPtr = new TH1F(hydet_name, hydet_title, 500,-100.,100.);
            tree_geo->Draw(hydet_draw, hy_cut);
            ymeanoff = hydetPtr->GetMean();
            yrmsoff = hydetPtr->GetRMS();
            yentriesoff = hydetPtr->GetEntries();
            hydetPtr->Write();
            delete hydetPtr;
        }
        
        delete hycoordtmp;
        
        /*
         if (EBV_BeampProfiledataPrintOut==1 && EBV_Verbose==0)
         {
         cout << " g4yBeamMean: "<< hg4BeamProfile->GetMean(2) << " g4yBeamRMS: "<< hg4BeamProfile->GetRMS(2) 
	     << " g4xBeamMean: "<< hg4BeamProfile->GetMean(1) << " g4xBeamRMS: "<< hg4BeamProfile->GetRMS(1);
         cout << " g4-g1yoffset:"<< hg4yoffsetwithg1->GetMean() << " g4-g1yoffsetRMS:"<< hg4yoffsetwithg1->GetRMS() 
   	     << " g4-g1xoffset:"<< hg4xoffsetwithg1->GetMean() << " g4-g1xoffsetRMS:"<< hg4xoffsetwithg1->GetRMS(); 
         }
         */
        if (EBV_BeampProfiledataPrintOut==1 && EBV_Verbose==1)
        {
            if (yentriesoff>0) printf("%d\t\t%-.3f\t\t%-.3f\t\t%-.3f\t\t%-.3f\t\t%s\n", 
                                      yentriesoff, ydet_ycoord_mean, ydet_ycoord_rms, ymeanoff, yrmsoff,(const char*)(*DET[i]).DetectorName);
        }
    }
    if (EBV_BeampProfiledataPrintOut==1 && EBV_Verbose==1)
    {
        BlueOut(".................................................................................................\n\n"); 	
    }
    //--- XLoop on the declared detectors -------------------------------------------------------------------------------------------------
    
    
    cout << endl;
    
    
    //cout << "---------------------------------------------------------------------------------" << endl;
    //cout << "---  END OF BEAM PROFILE AND RELATIVE ALIGNMENT ---------------------------------" << endl;
    //cout << "---------------------------------------------------------------------------------" << endl;
    
    
    
    
    
    
    if (EBV_EfficiencyEstimatorPrintOut){   
        //cout << "---------------------------------------------------------------------------------" << endl;
        //cout << "---  EFFICIENCIES ESTIMATION  ---------------------------------------------------" << endl;
        //cout << "---------------------------------------------------------------------------------" << endl;
        
        TCut g1SingleHit("g1SingleHit","g1ycl@.GetEntries()==1 && g1xcl@.GetEntries()==1");
        TCut g2SingleHit("g2SingleHit","g2ycl@.GetEntries()==1 && g2xcl@.GetEntries()==1");
        TCut g3SingleHit("g3SingleHit","g3ycl@.GetEntries()==1 && g3xcl@.GetEntries()==1");
        
        TCut g1g2Algnd("g1g2Algnd","TMath::Abs(g1xcl.geoposX-g2xcl.geoposX)<4 && TMath::Abs(g1ycl.geoposY-g2ycl.geoposY)<4");
        TCut g1g3Algnd("g1g3Algnd","TMath::Abs(g1xcl.geoposX-g3xcl.geoposX)<4 && TMath::Abs(g1ycl.geoposY-g3ycl.geoposY)<4");
        
        TCut g2g3Algnd("g2g3Algnd","TMath::Abs(g2xcl.geoposX-g3xcl.geoposX)<4 && TMath::Abs(g2ycl.geoposY-g3ycl.geoposY)<4");
        
        TCut CTLMiddleArea("CTLMiddleArea","g2xcl.geoposX>50 && g2xcl.geoposX<75 && g2ycl.geoposY>60 && g2ycl.geoposY<90");
        TCut CTLBottomLeftArea("CTLMiddleLeftArea","g2xcl.geoposX>22 && g2xcl.geoposX<44 && g2ycl.geoposY>32 && g2ycl.geoposY<54");
        
//        TCut CTLMiddleLeftg2Algnd("CTLMiddleLeftg2Algnd","TMath::Abs(gCTLMiddleLeftycl.geoposY-g2ycl.geoposY)<10");
//        TCut CTLTopMiddleg2Algnd("CTLTopMiddleg2Algnd","TMath::Abs(gCTLTopMiddlexcl.geoposX-g2xcl.geoposX)<10");
        
//        TCut CTLBottomLeftXg2Algnd("CTLBottomLeftXg2Algnd","TMath::Abs(gCTLBottomLeftxcl.geoposX-g2xcl.geoposX)<10");
//        TCut CTLBottomLeftYg2Algnd("CTLBottomLeftYg2Algnd","TMath::Abs(gCTLBottomLeftycl.geoposY-g2ycl.geoposY)<10");
        
        //TCut g1T2StripsAligned("g1T2Strips","TMath::Abs(g1T2Padscl.geoposR-g1T2Stripscl.geoposR)<10");
        //TCut g2T2StripsAligned("g2T2Strips","TMath::Abs(g2T2Padscl.geoposR-g2T2Stripscl.geoposR)<10");
        
        
        Float_t gCTLMiddleLeft_Eff, gCTLMiddleLeft_EffErr, gCTLMiddleLeft_Sample, gCTLMiddleLeft_True;
        Float_t gCTLTopMiddle_Eff, gCTLTopMiddle_EffErr, gCTLTopMiddle_Sample, gCTLTopMiddle_True;
        Float_t gCTLBottomLeftY_Eff, gCTLBottomLeftX_EffErr, gCTLBottomLeftX_Sample, gCTLBottomLeftX_True;
        Float_t gCTLBottomLeftX_Eff, gCTLBottomLeftY_EffErr, gCTLBottomLeftY_Sample, gCTLBottomLeftY_True;
        
        
        gCTLMiddleLeft_True	=(Float_t)(tree_geo->Project("htmp","g2ycl.geoposY:g2xcl.geoposX",g1SingleHit && g2SingleHit && g1g2Algnd && CTLMiddleArea && CTLMiddleLeftg2Algnd));
        gCTLTopMiddle_True	=(Float_t)(tree_geo->Project("htmp","g2ycl.geoposY:g2xcl.geoposX",g1SingleHit && g2SingleHit && g1g2Algnd && CTLMiddleArea && CTLTopMiddleg2Algnd));
        gCTLBottomLeftY_True	=(Float_t)(tree_geo->Project("htmp","g2ycl.geoposY:g2xcl.geoposX",g1SingleHit && g2SingleHit && g1g2Algnd && CTLBottomLeftArea && CTLBottomLeftXg2Algnd));
        gCTLBottomLeftX_True	=(Float_t)(tree_geo->Project("htmp","g2ycl.geoposY:g2xcl.geoposX",g1SingleHit && g2SingleHit && g1g2Algnd && CTLBottomLeftArea && CTLBottomLeftYg2Algnd));
        
        
        
        gCTLMiddleLeft_Sample	=(Float_t)(tree_geo->Project("htmp","g2ycl.geoposY:g2xcl.geoposX",g1SingleHit && g2SingleHit && g1g2Algnd && CTLMiddleArea));
        gCTLTopMiddle_Sample	=(Float_t)(tree_geo->Project("htmp","g2ycl.geoposY:g2xcl.geoposX",g1SingleHit && g2SingleHit && g1g2Algnd && CTLMiddleArea));
        gCTLBottomLeftY_Sample  =(Float_t)(tree_geo->Project("htmp","g2ycl.geoposY:g2xcl.geoposX",g1SingleHit && g2SingleHit && g1g2Algnd && CTLBottomLeftArea));
        gCTLBottomLeftX_Sample  =(Float_t)(tree_geo->Project("htmp","g2ycl.geoposY:g2xcl.geoposX",g1SingleHit && g2SingleHit && g1g2Algnd && CTLBottomLeftArea));
        
        
        
        gCTLMiddleLeft_Eff	=gCTLMiddleLeft_True/gCTLMiddleLeft_Sample;
        gCTLTopMiddle_Eff	=gCTLTopMiddle_True/gCTLTopMiddle_Sample;
        gCTLBottomLeftY_Eff	=gCTLBottomLeftX_True/gCTLBottomLeftX_Sample;
        gCTLBottomLeftX_Eff	=gCTLBottomLeftY_True/gCTLBottomLeftY_Sample;
        
        
        gCTLMiddleLeft_EffErr	=TMath::Sqrt(gCTLMiddleLeft_Eff*(1-gCTLMiddleLeft_Eff)/gCTLMiddleLeft_Sample);
        gCTLTopMiddle_EffErr	=TMath::Sqrt(gCTLTopMiddle_Eff*(1-gCTLTopMiddle_Eff)/gCTLTopMiddle_Sample);
        gCTLBottomLeftY_EffErr	=TMath::Sqrt(gCTLBottomLeftX_Eff*(1-gCTLBottomLeftX_Eff)/(gCTLBottomLeftX_Sample));
        gCTLBottomLeftX_EffErr	=TMath::Sqrt(gCTLBottomLeftY_Eff*(1-gCTLBottomLeftY_Eff)/(gCTLBottomLeftY_Sample));
        
        if (EBV_EfficiencyEstimatorPrintOut==1 && EBV_Verbose==0){
            cout << "FileName	"<<	
            "gCTLMiddleLeft_Eff	"	<<"gCTLMiddleLeft_EffErr	"	<<"gCTLMiddleLeft_Sample	"	<<
            "gCTLTopMiddle_Eff	"	<<"gCTLTopMiddle_EffErr	"	<<"gCTLTopMiddle_Sample	"		<<
            "gCTLBottomLeftY_Eff	"	<<"gCTLBottomLeftX_EffErr	"	<<"gCTLBottomLeftX_Sample	"		<<
            "gCTLBottomLeftX_Eff	"	<<"gCTLBottomLeftY_EffErr	"	<<"gCTLBottomLeftY_Sample	"		<< endl;
            cout << rawfilename <<"	"<<	            gCTLMiddleLeft_Eff	<<"	"<<gCTLMiddleLeft_EffErr	<<"	"<<gCTLMiddleLeft_Sample	<<" 	"<<
            gCTLTopMiddle_Eff	<<"	"<<gCTLTopMiddle_EffErr		<<"	"<<gCTLTopMiddle_Sample		<<"	"<<
            gCTLBottomLeftY_Eff	<<"	"<<gCTLBottomLeftX_EffErr	<<"	"<<gCTLBottomLeftX_Sample	<<"	"<<
            gCTLBottomLeftX_Eff	<<"	"<<gCTLBottomLeftY_EffErr	<<"	"<<gCTLBottomLeftY_Sample	<<"	"<< endl;
        }
        if (EBV_EfficiencyEstimatorPrintOut==1 && EBV_Verbose==1)
        {
            BlueOut("\nEFFICIENCY ESTIMATION OF THE DETECTRS UNDER TEST................................................\n");
            BlueOut("Sample\t\tEfficiency\tError\t\tDetector Name\n");
            printf("%-.0f\t\t%-.3f\t\t%-.3f\t\tgCTLMiddleLeft\n"	,gCTLMiddleLeft_Sample	,gCTLMiddleLeft_Eff	,gCTLMiddleLeft_EffErr	);
            printf("%-.0f\t\t%-.3f\t\t%-.3f\t\tgCTLTopMiddle\n"	,gCTLTopMiddle_Sample	,gCTLTopMiddle_Eff	,gCTLTopMiddle_EffErr	);
            printf("%-.0f\t\t%-.3f\t\t%-.3f\t\tgCTLBottomLeftY\n"	,gCTLBottomLeftX_Sample	,gCTLBottomLeftY_Eff	,gCTLBottomLeftX_EffErr	);
            printf("%-.0f\t\t%-.3f\t\t%-.3f\t\tgCTLBottomLeftX\n"	,gCTLBottomLeftX_Sample	,gCTLBottomLeftY_Eff	,gCTLBottomLeftX_EffErr	);
            BlueOut("................................................................................................\n\n");
        }
        
cout<<"#############################11"<<endl;    
    }



//cout<<"#############################22"<<endl;    
//    if (LoaderSettings_rd51_EventBuilderVFAT) 	{delete  LoaderSettings_rd51_EventBuilderVFAT;}
//    if (DetectorConf_rd51_EventBuilderVFAT)   	{delete  DetectorConf_rd51_EventBuilderVFAT;}
//    if (OffsetFlip_rd51_EventBuilderVFAT) 	{delete  OffsetFlip_rd51_EventBuilderVFAT;}
//cout<<"#############################33"<<endl;    
//    if (VFATConf_rd51_EventBuilderVFAT) 	{delete  VFATConf_rd51_EventBuilderVFAT; }
//cout<<"#############################34"<<endl;    
 //    for (Int_t i=0; i<MaxNumbersOfDetDir; i++) 	delete DET[i];      
 //    for (Int_t i=0; i<chips_per_evt; i++) 	delete VFAT[i];
 //    for (Int_t i=0; i<chips_per_evt; i++) 	delete vfat_data[i];
//    for (Int_t i=0; i<MaxNumbersOfDetDir; i++)  {cout<<"delete = "<<g[i]<<endl; delete g[i];}
 //    for (Int_t i=0; i<MaxNumbersOfDetDir; i++)  delete gGeo[i];
 //    for (Int_t i=0; i<MaxNumbersOfDetDir; i++)  delete gGeoClustVect[i];
 //    for (Int_t i=0; i<MaxNumbersOfDetDir; i++)  delete geotmpcluster[i];




    
cout<<"#############################44"<<endl;    
    
    
    f.Save();
    //  f.ls();
    
    f.Close();
    
    c1->Close();
    
    /* 
     
     for (Int_t i=0; i<chips_per_evt; i++)
     {
     if((*VFAT[i]).DetectorName == "g1")
     {
     hg1BeamProfile->Delete() ;
     break;
     }
     }	
     for (Int_t i=0; i<chips_per_evt; i++)
     {
     if((*VFAT[i]).DetectorName == "g2")
     {
     hg2BeamProfile->Delete()  ;
     hg2xoffsetwithg1->Delete()  ;
     hg2yoffsetwithg1->Delete()  ;
     break;
     }
     }	
     for (Int_t i=0; i<chips_per_evt; i++)
     {
     if((*VFAT[i]).DetectorName == "g3")
     {
     hg3BeamProfile->Delete()  ;
     hg3xoffsetwithg1->Delete()  ;
     hg3yoffsetwithg1->Delete()  ;
     break;
     }
     }	
     for (Int_t i=0; i<chips_per_evt; i++)
     {
     if((*VFAT[i]).DetectorName == "g4")
     {
     hg4BeamProfile->Delete()  ;
     hg4xoffsetwithg1->Delete()  ;
     hg4yoffsetwithg1->Delete()  ;
     break;
     }
     }	
     */
    if (EBV_Verbose==1)
    { 
        YellowOut("\nTrees written on file and file closed.To access it:\n\n1. From ROOT:\n");
        cout << "TFile file0(\"" << rootfilename << "\");  file0.ls();" << endl;
        YellowOut("2. From Shell:\n");
        cout << "root -l " << rootfilename <<"\n"<<endl;
    }
    
    
    return 1;
    
}
