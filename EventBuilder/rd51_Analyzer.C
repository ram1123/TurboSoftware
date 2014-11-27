#define rd51_Analyzer_cxx

#include "rd51_Analyzer.h"

rd51_Analyzer::rd51_Analyzer(TString rd51reco_filename, TString rd51tracker_filename, TString rd51analyzer_filename)
{
    // Loading Settings....
    LoadSettings();
    
    // Loading Offset And Coverage....   
    LoadOffsetAndCoverage(rd51analyzer_Verbose);
    
    // Creating Histograms....
    HistoDefine(rd51analyzer_Verbose);
    
    
    cout << "Loading the trees...." << endl;
    // Loading Reco Tree......          
    TFile *rd51reco_file = new TFile(rd51reco_filename);
    if (rd51reco_file && rd51analyzer_Verbose) cout << "Loading: " << rd51reco_filename << endl; 
    rd51reco_tree = (TTree*)rd51reco_file->Get("rd51tbgeo");
    if (rd51reco_tree && rd51analyzer_Verbose)
    {cout << "Getting the rd51tbgeo tree" << endl; rd51reco_tree->ls();} 
    rd51reco = new Class_Reco(rd51reco_tree);
    if (rd51reco && rd51analyzer_Verbose) cout << "Creating the Reco Class\n" << endl; 
    
    // Loading Tracker Tree......       
    TFile *rd51tracker_file = new TFile(rd51tracker_filename);
    if (rd51tracker_file && rd51analyzer_Verbose) cout << "Loading: " << rd51tracker_filename << endl; 
    rd51tracker_tree = (TTree*)rd51tracker_file->Get("trackertree");
    if (rd51tracker_tree && rd51analyzer_Verbose) 
    {cout << "Getting the trakertree tree" << endl; rd51tracker_tree->ls();} 
    rd51tracker = new Class_Tracker(rd51tracker_tree);
    if (rd51tracker && rd51analyzer_Verbose) cout << "Creating the Tracker Class\n" << endl; 
    
    // Add Tracker as Friend to Reco Tree
    rd51reco_tree->AddFriend(rd51tracker_tree);
    
    // Creating the output file.....
    TFile *rd51analyzer_file = new TFile(rd51analyzer_filename, "RECREATE");
    
    
    
    
    //__________________________________________________________________________________________
    //                                                                                          
    //                                                                                          
    //                                                                                          
    //     Analyzing.....
    //                                                                                          
    //                                                                                          
    //__________________________________________________________________________________________
    
    Int_t rd51reco_nentries = (Int_t)rd51reco_tree->GetEntries();
    

    Int_t rd51tracker_nentries = (Int_t)rd51tracker_tree->GetEntries();
    
    
    // Efficiency Radius Scan Initialization
    ERSSteps = 1;
    if (rd51analyzer_EfficiencyRadiusScan) InitializeEfficiencyRadiusScan(rd51analyzer_Verbose);
    
    int NumberOfProcessedEntries=0;
    for (int i=0;i<rd51reco_nentries;i++) 
    {
        // Get the Entry "i"
        rd51reco_tree->GetEntry(i);
        // Selecting the Entries... 
        if (ProcessTheEntry(i,rd51analyzer_Cut_Verbose))
        {
            
            // Processing..........................................................................
            Calc_sCMSNS2LC1_Eff(rd51analyzer_Verbose && rd51analyzer_EffCalculatorVerbose);
            Calc_sCMSNS2LC2_Eff(rd51analyzer_Verbose && rd51analyzer_EffCalculatorVerbose);
            Calc_sCMSNS2LC3_Eff(rd51analyzer_Verbose && rd51analyzer_EffCalculatorVerbose);
            // End of Processing...................................................................
            
            NumberOfProcessedEntries+=1;
        
        }
        else
        {
            if (rd51analyzer_EffCalculatorVerbose==1 && rd51analyzer_Verbose==1) 
                cout 	<< "Not Processed Events: Number Of Found XTracks: " 
                << rd51tracker->trackx_ 
                << "\tNumber Of Found YTracks: " 	
                << rd51tracker->tracky_ << endl;
        }
    }
    	
    
    // Efficiency Radius Scan Processing and "Graphing"
    if (rd51analyzer_EfficiencyRadiusScan) ProcessEfficiencyRadiusScan(rd51analyzer_Verbose);
    
    if (rd51analyzer_Verbose) cout 	
        << "\nNumber of Entries: \t" 		<< rd51reco_nentries
        << "\nNumber of Processed Entries: " 	<< NumberOfProcessedEntries << endl;
    
    
    
    // Estimators.....
    if ((rd51analyzer_EffCalculatorVerbose==1 && rd51analyzer_Verbose==0) || rd51analyzer_Verbose==1)
    {
        BlueOut("...................................................................................................\n");
        BlueOut("Efficiency\tEffErr\t\tNoiseErr\tCombinedErr\tSample\t\tDetectorName\n");
        
        
        //--- Coverage and Efficiency Scanned Area: They will be used to evaluate the error due to noise hits.
        //double sCMSNS2LC3_CovLength	= TMath::Abs(DUT_MaxY[2]-DUT_MinY[2]);  
        double sCMSNS2LC3_CovLength	= TMath::Abs(DUT_MaxX[2]-DUT_MinX[2]);  
        double sCMSNS2LC3_EffRadLength= 2*DUT_effRad[2];     
//	cout<<"sCMSNS2LC3_CovLength = "<<sCMSNS2LC3_CovLength<<"\tsCMSNS2LC3_EffRadLength = "<<sCMSNS2LC3_EffRadLength<<"\thsCMSNS2LC3_Eff->GetBinContent(1) = "<<hsCMSNS2LC3_Eff->GetBinContent(1)<<"\thsCMSNS2LC3_Eff->GetEntries() = "<<hsCMSNS2LC3_Eff->GetEntries()<<endl;
        double sCMSNS2LC3_Eff 	= (1-hsCMSNS2LC3_Eff->GetBinContent(1)/hsCMSNS2LC3_Eff->GetEntries());
        int    sCMSNS2LC3_Sample	= hsCMSNS2LC3_Eff->GetEntries(); 
        double sCMSNS2LC3_NoiseErr	= 
        (sCMSNS2LC3_EffRadLength/sCMSNS2LC3_CovLength)*hsCMSNS2LC3_Distance_Noise->GetEntries()/hsCMSNS2LC3_Eff->GetEntries(); 
        double sCMSNS2LC3_EffErr	= TMath::Sqrt(sCMSNS2LC3_Eff*(1-sCMSNS2LC3_Eff)/sCMSNS2LC3_Sample);
        
        double sCMSNS2LC3_CombErr	= TMath::Sqrt(TMath::Power(sCMSNS2LC3_EffErr,2) + TMath::Power(sCMSNS2LC3_NoiseErr,2));

        printf("%-.3f\t\t%-.3f\t\t%-.3f\t\t%-.3f\t\t%d\t\tsCMSNS2LC3\n",
               sCMSNS2LC3_Eff,sCMSNS2LC3_EffErr,sCMSNS2LC3_NoiseErr,sCMSNS2LC3_CombErr,sCMSNS2LC3_Sample);
 


        //double sCMSNS2LC2_CovLength	= TMath::Abs(DUT_MaxY[1]-DUT_MinY[1]);  // Patr
        double sCMSNS2LC2_CovLength	= TMath::Abs(DUT_MaxX[1]-DUT_MinX[1]);  // Patr
        double sCMSNS2LC2_EffRadLength= 2*DUT_effRad[1];     // Patr
        double sCMSNS2LC2_Eff 	= (1-hsCMSNS2LC2_Eff->GetBinContent(1)/hsCMSNS2LC2_Eff->GetEntries());
        int    sCMSNS2LC2_Sample	= hsCMSNS2LC2_Eff->GetEntries(); 
        double sCMSNS2LC2_NoiseErr	= 
        (sCMSNS2LC2_EffRadLength/sCMSNS2LC2_CovLength)*hsCMSNS2LC2_Distance_Noise->GetEntries()/hsCMSNS2LC2_Eff->GetEntries(); 
        double sCMSNS2LC2_EffErr	= TMath::Sqrt(sCMSNS2LC2_Eff*(1-sCMSNS2LC2_Eff)/sCMSNS2LC2_Sample);
        
        double sCMSNS2LC2_CombErr	= TMath::Sqrt(TMath::Power(sCMSNS2LC2_EffErr,2) + TMath::Power(sCMSNS2LC2_NoiseErr,2));
        printf("%-.3f\t\t%-.3f\t\t%-.3f\t\t%-.3f\t\t%d\t\tsCMSNS2LC2\n",
               sCMSNS2LC2_Eff,sCMSNS2LC2_EffErr,sCMSNS2LC2_NoiseErr,sCMSNS2LC2_CombErr,sCMSNS2LC2_Sample);
        

        //double sCMSNS2LC1_CovLength	= TMath::Abs(DUT_MaxY[0]-DUT_MinY[0]); //Patr
        double sCMSNS2LC1_CovLength	= TMath::Abs(DUT_MaxX[0]-DUT_MinX[0]); //Patr
        double sCMSNS2LC1_EffRadLength= 2*DUT_effRad[0];//Patr
        double sCMSNS2LC1_Eff 	= (1-hsCMSNS2LC1_Eff->GetBinContent(1)/hsCMSNS2LC1_Eff->GetEntries());
        int    sCMSNS2LC1_Sample	= hsCMSNS2LC1_Eff->GetEntries();
        double sCMSNS2LC1_NoiseErr	= 
        (sCMSNS2LC1_EffRadLength/sCMSNS2LC1_CovLength)*hsCMSNS2LC1_Distance_Noise->GetEntries()/hsCMSNS2LC1_Eff->GetEntries(); 
        double sCMSNS2LC1_EffErr	= TMath::Sqrt(sCMSNS2LC1_Eff*(1-sCMSNS2LC1_Eff)/sCMSNS2LC1_Sample);
        double sCMSNS2LC1_CombErr	= TMath::Sqrt(TMath::Power(sCMSNS2LC1_EffErr,2) + TMath::Power(sCMSNS2LC1_NoiseErr,2));
        printf("%-.3f\t\t%-.3f\t\t%-.3f\t\t%-.3f\t\t%d\t\tsCMSNS2LC1\n",
               sCMSNS2LC1_Eff,sCMSNS2LC1_EffErr,sCMSNS2LC1_NoiseErr,sCMSNS2LC1_CombErr,sCMSNS2LC1_Sample);        

        cout << "=======rd51tracker_nentries========= :"<< rd51tracker_tree->GetEntries()<< endl;
        cout << "********rd51reco_nentries********* :"<< rd51reco_tree->GetEntries()<< endl;
        cout << "======ENTRIES PROCESSATE======= :"<< NumberOfProcessedEntries << endl;     

        cout << "sCMSNS2LC3_Sample =" <<  sCMSNS2LC3_Sample << endl;
        cout << "sCMSNS2LC3_CovLength =" <<sCMSNS2LC3_CovLength << endl;
        cout << "sCMSNS2LC3_EffRadLength =" << sCMSNS2LC3_EffRadLength << endl;
        cout << "sCMSNS2LC3_Eff ="<< sCMSNS2LC3_Eff<< endl;
        cout << "sCMSNS2LC3_EffErr =" << sCMSNS2LC3_EffErr << endl;
        cout << "sCMSNS2LC3_NoiseErr =" << sCMSNS2LC3_NoiseErr << endl;
        cout << "sCMSNS2LC3_CombErr =" << sCMSNS2LC3_CombErr << endl;

        cout << "sCMSNS2LC2_Sample =" <<  sCMSNS2LC2_Sample << endl;
        cout << "sCMSNS2LC2_CovLength =" <<sCMSNS2LC2_CovLength << endl;
        cout << "sCMSNS2LC2_EffRadLength =" << sCMSNS2LC2_EffRadLength << endl;
        cout << "sCMSNS2LC2_Eff ="<< sCMSNS2LC2_Eff<< endl;
        cout << "sCMSNS2LC2_EffErr =" << sCMSNS2LC2_EffErr << endl;
        cout << "sCMSNS2LC2_NoiseErr =" << sCMSNS2LC2_NoiseErr << endl;
        cout << "sCMSNS2LC2_CombErr =" << sCMSNS2LC2_CombErr << endl;
    
        cout << "sCMSNS2LC1_Sample =" <<  sCMSNS2LC1_Sample << endl;
        cout << "sCMSNS2LC1_CovLength =" <<sCMSNS2LC1_CovLength << endl;
        cout << "sCMSNS2LC1_EffRadLength =" << sCMSNS2LC1_EffRadLength << endl;
        cout << "sCMSNS2LC1_Eff ="<< sCMSNS2LC1_Eff<< endl;
        cout << "sCMSNS2LC1_EffErr =" << sCMSNS2LC1_EffErr << endl;
        cout << "sCMSNS2LC1_NoiseErr =" << sCMSNS2LC1_NoiseErr << endl;
        cout << "sCMSNS2LC1_CombErr =" << sCMSNS2LC1_CombErr << endl;


        BlueOut("...................................................................................................\n");
    }	
    
    //__________________________________________________________________________________________
    //                                                                                          
    //                                                                                          
    //                                                                                          
    //     End of Analyzing.....
    //                                                                                          
    //                                                                                          
    //__________________________________________________________________________________________
    
    
    //-----------------------------------------------------------------------------------------
    // Logout Message
    //-----------------------------------------------------------------------------------------
    
    //if (rd51analyzer_Verbose==1)
    //{
        YellowOut("\nOutput File closed. To access it:\n\n1. From ROOT:\n");
        cout << "TFile file0(\"" << rd51analyzer_filename << "\");  file0.ls();" << endl;
        YellowOut("2. From Shell:\n");
        cout << "root -l " << rd51analyzer_filename <<"\n"<<endl;
    //}
    //-----------------------------------------------------------------------------------------
    
    
    
    //-----------------------------------------------------------------------------------------
    //--- Writing  
    //-----------------------------------------------------------------------------------------
    // Writing Histograms......
    HistoWrite(rd51analyzer_Verbose);	
    //-----------------------------------------------------------------------------------------
    
    
    //-----------------------------------------------------------------------------------------
    //--- Closing  
    //-----------------------------------------------------------------------------------------
    // Closing Files.......
    rd51reco_file->Close();
    rd51tracker_file->Close();
    rd51analyzer_file->Close();
    //-----------------------------------------------------------------------------------------
    
    
    //-----------------------------------------------------------------------------------------
    //--- Deleting
    //-----------------------------------------------------------------------------------------
    // Deleting Loaders......
    delete rd51analyzer_LoaderSettings		; 
    delete rd51analyzer_LoaderOffsetAndCoverage	;
    // Deleting Reco and Tracker
    //delete rd51reco				;//--- If not commented it breaks for some runs
    //delete rd51tracker				;//--- If not commented it breaks for some runs
    // Deleting Efficiency Radius Scan Arrays;
    if(rd51analyzer_EfficiencyRadiusScan) DeleteEfficiencyRadiusScan(rd51analyzer_Verbose);
    // Deleting Histograms....
    HistoDelete(rd51analyzer_Verbose);
    // Deleting Files......
    delete rd51reco_file				;
    delete rd51tracker_file			;
    delete rd51analyzer_file			;
    //-----------------------------------------------------------------------------------------
}








//__________________________________________________________________________________________
//---
//--- TOTEM Triple GEM Efficiency Calculator
//--- Pads: 	XY coordinates are compared
//--- Strips:	R coordinate is compared 
//--- NB: If two strips sectors with same R and different Phi are used, 
//--- the selection on Phi has to be added.
//__________________________________________________________________________________________


//__________________________________________________________________________________________
//
//--- CMS30x30 and GE1/1 Efficiency Calculator
//__________________________________________________________________________________________

int rd51_Analyzer::Calc_sCMSNS2LC1_Eff(int verbose)
{
//std::cout<<"###################################################################################11"<<std::endl;
    bool ERSFound = 0; //--- Control Variable for the Efficiency Radius Scan 
    
    Float_t ProjectedX = ((rd51tracker->trackx_q)[0]+DUT_trkoffsetX[0]) + (rd51tracker->trackx_m)[0]*DUT_offsetZ[0]; //Patr
    Float_t ProjectedY = ((rd51tracker->tracky_q)[0]+DUT_trkoffsetY[0]) + (rd51tracker->tracky_m)[0]*DUT_offsetZ[0]; //Patr
    
//cout<<"For LC1 (rd51tracker->trackx_q)[0] = "<<(rd51tracker->trackx_q)[0]<<"\tDUT_trkoffsetX[3] = "<<DUT_trkoffsetX[0]<<endl;
//cout<<"For LC1 (rd51tracker->trackx_m)[0] = "<<(rd51tracker->trackx_m)[0]<<"\tDUT_offsetZ[3] = "<<DUT_offsetZ[0]<<endl;
    bool XCov= (ProjectedX   >= DUT_MinX[0]   && ProjectedX <= DUT_MaxX[0]); //Patr		
    bool YCov= (ProjectedY   >= DUT_MinY[0]   && ProjectedY <= DUT_MaxY[0]); //Patr		
    bool InsideCoverage   = XCov && YCov;
    
    if(verbose) cout << "Number of Clusters in sCMSNS2LC1: " << rd51reco->sCMSNS2LC1_ << endl;	
    
  //  cout<<"For LC1 : ProjectedX = "<<ProjectedX<<"\tProjectedY = "<<ProjectedY<<"\tDUT_MinX = "<<DUT_MinX[0]<<"\tmaxX = "<<DUT_MaxX[0]<<"\tXCov = "<<XCov<<"\tYCov = "<<YCov<<endl;
    if ( !rd51analyzer_EnableCoverage || InsideCoverage )
    {
        if ( verbose && rd51analyzer_EnableCoverage) GreenOut("Inside the Coverage\n");
        //--- Updating the entries in the Efficiency Radius Scan
        if (rd51analyzer_EfficiencyRadiusScan) sCMSNS2LC1_ERSEntries += 1.;
        //--- Loop on the DUT clusters
        int neff = 0;
        for (int ihit = 0; ihit <rd51reco->sCMSNS2LC1_ ; ihit++)
        {
	   Float_t distance = TMath::Abs( rd51reco->sCMSNS2LC1_geoposX[ihit] +DUT_offsetX[0] - ProjectedX ); //Patr
	     if ( distance  < DUT_effRad[0] ) //Patr
            {
                hsCMSNS2LC1_XY_Eff->Fill(ProjectedX,ProjectedY);
                hsCMSNS2LC1_CLS_Eff->Fill(rd51reco->sCMSNS2LC1_ngeoch[ihit]);
                hsCMSNS2LC1_Distance_Eff->Fill(distance);
                hsCMSNS2LC1_Residual_X->Fill(rd51reco->sCMSNS2LC1_geoposX[ihit] + DUT_offsetX[0] - ProjectedX); //Patr
                neff++;
            }
            else
            {
                hsCMSNS2LC1_XY_Noise->Fill(ProjectedX,ProjectedY);
                hsCMSNS2LC1_CLS_Noise->Fill(rd51reco->sCMSNS2LC1_ngeoch[ihit]);
                hsCMSNS2LC1_Distance_Noise->Fill(distance);
            }
            //--- Filling the Efficiency Radius Scan Arrays
	      	if (rd51analyzer_EfficiencyRadiusScan && !ERSFound)
            {
                for (int iers=0; iers<ERSSteps; iers++)
                {
                    if (distance < ERSRad[iers]) { sCMSNS2LC1_ERSIneff[iers] += 1.; ERSFound=1;}
                }
            }
        }
        hsCMSNS2LC1_Eff->Fill(neff);
        if (neff==0) hsCMSNS2LC1_XY_Ineff->Fill(ProjectedX,ProjectedY);
    }
    if (  verbose && rd51analyzer_EnableCoverage && !InsideCoverage ) RedOut("Outside of the Coverage\n");
    return 0;
}


int rd51_Analyzer::Calc_sCMSNS2LC2_Eff(int verbose)
{
    bool ERSFound = 0; //--- Control Variable for the Efficiency Radius Scan 
    
     Float_t ProjectedX = ((rd51tracker->trackx_q)[0]+DUT_trkoffsetX[1]) + (rd51tracker->trackx_m)[0]*DUT_offsetZ[1]; //Patr
     Float_t ProjectedY = ((rd51tracker->tracky_q)[0]+DUT_trkoffsetY[1]) + (rd51tracker->tracky_m)[0]*DUT_offsetZ[1]; //Patr
//cout<<"For LC2 (rd51tracker->trackx_q)[0] = "<<(rd51tracker->trackx_q)[0]<<"\tDUT_trkoffsetX[1] = "<<DUT_trkoffsetX[1]<<endl;
//cout<<"For LC2 (rd51tracker->trackx_m)[0] = "<<(rd51tracker->trackx_m)[0]<<"\tDUT_offsetZ[1] = "<<DUT_offsetZ[1]<<endl;

    
     bool XCov= (ProjectedX   >= DUT_MinX[1]   && ProjectedX <= DUT_MaxX[1]); 	//Patr	
     bool YCov= (ProjectedY   >= DUT_MinY[1]   && ProjectedY <= DUT_MaxY[1]);  //Patr		
    bool InsideCoverage   = XCov && YCov;
    
    if(verbose) cout << "Number of Clusters in sCMSNS2LC2: " << rd51reco->sCMSNS2LC2_ << endl;	
 //   cout<<"For LC2 : ProjectedX = "<<ProjectedX<<"\tProjectedY = "<<ProjectedY<<"\tDUT_MinX = "<<DUT_MinX[1]<<"\tmaxX = "<<DUT_MaxX[1]<<"\tXCov = "<<XCov<<"\tYCov = "<<YCov<<endl;
    
    if ( !rd51analyzer_EnableCoverage || InsideCoverage )
    {
        if ( verbose && rd51analyzer_EnableCoverage) GreenOut("Inside the Coverage\n");
        //--- Updating the entries in the Efficiency Radius Scan
        if (rd51analyzer_EfficiencyRadiusScan) sCMSNS2LC2_ERSEntries += 1.;
        //--- Loop on the DUT clusters
        int neff = 0;
        for (int ihit = 0; ihit <rd51reco->sCMSNS2LC2_ ; ihit++)
        {
	   Float_t distance = TMath::Abs( rd51reco->sCMSNS2LC2_geoposX[ihit] +DUT_offsetX[1] - ProjectedX ); //Patr
	  //if ( distance  < DUT_effRad[7] )
	  if ( distance  < DUT_effRad[1] ) //Patr
            {
                hsCMSNS2LC2_XY_Eff->Fill(ProjectedX,ProjectedY);
                hsCMSNS2LC2_CLS_Eff->Fill(rd51reco->sCMSNS2LC2_ngeoch[ihit]);
                hsCMSNS2LC2_Distance_Eff->Fill(distance);
                hsCMSNS2LC2_Residual_X->Fill(rd51reco->sCMSNS2LC2_geoposX[ihit] + DUT_offsetX[1] - ProjectedX); //Patr
                neff++;
            }
            else
            {
                hsCMSNS2LC2_XY_Noise->Fill(ProjectedX,ProjectedY);
                hsCMSNS2LC2_CLS_Noise->Fill(rd51reco->sCMSNS2LC2_ngeoch[ihit]);
                hsCMSNS2LC2_Distance_Noise->Fill(distance);
            }
            //--- Filling the Efficiency Radius Scan Arrays
	    if (rd51analyzer_EfficiencyRadiusScan && !ERSFound) {
                for (int iers=0; iers<ERSSteps; iers++)
                {
                    if (distance < ERSRad[iers]) { sCMSNS2LC2_ERSIneff[iers] += 1.; ERSFound=1;}
                }
            }
        }
        hsCMSNS2LC2_Eff->Fill(neff);
       
       
        if (neff==0) hsCMSNS2LC2_XY_Ineff->Fill(ProjectedX,ProjectedY);
    }
    if (  verbose && rd51analyzer_EnableCoverage && !InsideCoverage ) RedOut("Outside of the Coverage\n");
    return 0;
}



int rd51_Analyzer::Calc_sCMSNS2LC3_Eff(int verbose)
{
    bool ERSFound = 0; //--- Control Variable for the Efficiency Radius Scan 
    
     Float_t ProjectedX = ((rd51tracker->trackx_q)[0]+DUT_trkoffsetX[2]) + (rd51tracker->trackx_m)[0]*DUT_offsetZ[2]; 
     Float_t ProjectedY = ((rd51tracker->tracky_q)[0]+DUT_trkoffsetY[2]) + (rd51tracker->tracky_m)[0]*DUT_offsetZ[2]; 

//cout<<"LC 3 (rd51tracker->trackx_q)[0] = "<<(rd51tracker->trackx_q)[0]<<"\tDUT_trkoffsetX[2] = "<<DUT_trkoffsetX[2]<<endl;
//cout<<"LC 3 (rd51tracker->trackx_m)[0] = "<<(rd51tracker->trackx_m)[0]<<"\tDUT_offsetZ[2] = "<<DUT_offsetZ[2]<<endl;
    
     bool XCov= (ProjectedX   >= DUT_MinX[2]   && ProjectedX <= DUT_MaxX[2]); 		
     bool YCov= (ProjectedY   >= DUT_MinY[2]   && ProjectedY <= DUT_MaxY[2]);  		
    bool InsideCoverage   = XCov && YCov;
    
    if(verbose) cout << "Number of Clusters in sCMSNS2LC3: " << rd51reco->sCMSNS2LC3_ << endl;	
//    cout<<
//    cout<<"For LC3 : ProjectedX = "<<ProjectedX<<"\tProjectedY = "<<ProjectedY<<"\tDUT_MinX = "<<DUT_MinX[2]<<"\tmaxX = "<<DUT_MaxX[2]<<"\tXCov = "<<XCov<<"\tYCov = "<<YCov<<endl;
    
//	GreenOut("Inside the Coverage\n");
    if ( !rd51analyzer_EnableCoverage || InsideCoverage )
    {
        if ( verbose && rd51analyzer_EnableCoverage) GreenOut("Inside the Coverage\n");
        //--- Updating the entries in the Efficiency Radius Scan
        if (rd51analyzer_EfficiencyRadiusScan) sCMSNS2LC3_ERSEntries += 1.;
//	GreenOut("Inside the Coverage11\n");
        //--- Loop on the DUT clusters
        int neff = 0;
        for (int ihit = 0; ihit <rd51reco->sCMSNS2LC3_ ; ihit++)
        {
//	GreenOut("Inside the Coverage22\n");
	   Float_t distance = TMath::Abs( rd51reco->sCMSNS2LC3_geoposX[ihit] +DUT_offsetX[2] - ProjectedX ); 
//	GreenOut("Inside the Coverage33\n");
	  if ( distance  < DUT_effRad[2] ) 
            {
//	GreenOut("Inside the Coverage44\n");
                hsCMSNS2LC3_XY_Eff->Fill(ProjectedX,ProjectedY);
                hsCMSNS2LC3_CLS_Eff->Fill(rd51reco->sCMSNS2LC3_ngeoch[ihit]);
                hsCMSNS2LC3_Distance_Eff->Fill(distance);
                hsCMSNS2LC3_Residual_X->Fill(rd51reco->sCMSNS2LC3_geoposX[ihit] + DUT_offsetX[2] - ProjectedX); //Patr
                neff++;
//	GreenOut("Inside the Coverage55\n");
            }
            else
            {
                hsCMSNS2LC3_XY_Noise->Fill(ProjectedX,ProjectedY);
                hsCMSNS2LC3_CLS_Noise->Fill(rd51reco->sCMSNS2LC3_ngeoch[ihit]);
                hsCMSNS2LC3_Distance_Noise->Fill(distance);
            }
            //--- Filling the Efficiency Radius Scan Arrays
	    if (rd51analyzer_EfficiencyRadiusScan && !ERSFound) {
                for (int iers=0; iers<ERSSteps; iers++)
                {
//	GreenOut("Inside the Coverage 66\n");
//	cout<<"ERSstep = "<<ERSSteps<<"\tiers = "<<iers<<endl;
                    if (distance < ERSRad[iers]) { sCMSNS2LC3_ERSIneff[iers] += 1.; ERSFound=1;}
                }
//	GreenOut("Inside the Coverage77\n");
            }
//	GreenOut("Inside the Coverage88\n");
        }
	////cout<<"neff  =  "<<neff<<endl;
        hsCMSNS2LC3_Eff->Fill(neff);
       
       
        if (neff==0) hsCMSNS2LC3_XY_Ineff->Fill(ProjectedX,ProjectedY);
    }
    if (  verbose && rd51analyzer_EnableCoverage && !InsideCoverage ) RedOut("Outside of the Coverage\n");
    return 0;
}


//__________________________________________________________________________________________
//
//--- END Of CMS30x30 Efficiency Calculator
//__________________________________________________________________________________________













//-------------------------------------------------------------------------------------
//--- Entry Selection on The Tracker 
//-------------------------------------------------------------------------------------

bool rd51_Analyzer::ProcessTheEntry(int processedentry, int verbose)
{
    bool processit=0;
    bool cut_Chi2=0;
    bool cut_Residuals=0;
    bool cut_NumberOfTracks=0;
    bool cut_SingleXYTrack=0;
    // Selection of the events based on the tracks properties
    
    //Single Track on X&Y
    cut_NumberOfTracks= 	
	(rd51tracker->trackx_<=rd51analyzer_Cut_NumberOfTracks &&
     rd51tracker->tracky_<=rd51analyzer_Cut_NumberOfTracks);
    cut_SingleXYTrack= 
	( !rd51analyzer_Cut_SingleXYTrackRequest || (rd51tracker->trackx_==1 && rd51tracker->tracky_==1) );
    
    if (cut_NumberOfTracks && cut_SingleXYTrack)
    {
        cut_Chi2= 	
		((rd51tracker->trackx_chi2)[0]<=rd51analyzer_Cut_Chi2Value &&
	 	 (rd51tracker->tracky_chi2)[0]<=rd51analyzer_Cut_Chi2Value);
        cut_Residuals= 
		((rd51tracker->residualx)[0]<=rd51analyzer_Cut_ResidualValue &&
	 	 (rd51tracker->residualy)[0]<=rd51analyzer_Cut_ResidualValue);
        // Final Selection
        processit = (cut_Chi2 && cut_Residuals);
    }
    
    if (verbose && !processit)
    {
        cout 	<<"Rejected Entry\t"	<<processedentry	<<"\t"
		<<"NumberOfTrack["	<<cut_NumberOfTracks	<<"]\t" 
		<<"SingleXYTrack["	<<cut_SingleXYTrack	<<"]\t" 
		<<"Chi2["		<<cut_Chi2		<<"]\t" 
		<<"Residuals["		<<cut_Residuals		<<"]\t" 
		<<endl; 
    }
    
    return processit;
}
//-------------------------------------------------------------------------------------
//--- End of Entry Selection on The Tracker 
//-------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------
//--- Efficiency Radius Scan Initialization and deleting                                      
//-------------------------------------------------------------------------------------
void rd51_Analyzer::InitializeEfficiencyRadiusScan(int verbose)
{
    
    ERSSteps = 1+(rd51analyzer_EfficiencyRadiusMax-rd51analyzer_EfficiencyRadiusMin)/rd51analyzer_EfficiencyRadiusStep;
    
    if (verbose) cout << "\nEfficiency Radius Scan. Number of Steps = " << ERSSteps << "\n" << endl;
    
    ERSRad = new Float_t[ERSSteps];
  
    sCMSNS2LC3_ERSIneff = new Float_t[ERSSteps];
    sCMSNS2LC2_ERSIneff = new Float_t[ERSSteps];
    sCMSNS2LC1_ERSIneff = new Float_t[ERSSteps];

    sCMSNS2LC3_ERSErr = new Float_t[ERSSteps];
    sCMSNS2LC2_ERSErr = new Float_t[ERSSteps];
    sCMSNS2LC1_ERSErr = new Float_t[ERSSteps];

    sCMSNS2LC3_ERSEntries = 0.;
    sCMSNS2LC2_ERSEntries = 0.;
    sCMSNS2LC1_ERSEntries = 0.;

    for (int i=0; i<ERSSteps; i++) {
        ERSRad[i] = rd51analyzer_EfficiencyRadiusMin+rd51analyzer_EfficiencyRadiusStep*i;
        
        sCMSNS2LC3_ERSIneff[i] = 0.;
        sCMSNS2LC2_ERSIneff[i] = 0.;
        sCMSNS2LC1_ERSIneff[i] = 0.;

        sCMSNS2LC3_ERSErr[i] = 0.;
        sCMSNS2LC2_ERSErr[i] = 0.;
        sCMSNS2LC1_ERSErr[i] = 0.;
    }		
}

void rd51_Analyzer::ProcessEfficiencyRadiusScan(int verbose)
{
    //--- Initializing a tree with the efficiency information vs the efficiency radius
    TTree *EfficiencyTree = new TTree("Efficiency","Efficiency Data");
    EfficiencyTree->Branch("ERSSteps",&ERSSteps,"ERSSteps/I");
    EfficiencyTree->Branch("ERSRad",ERSRad,"ERSRad[ERSSteps]/F");

    EfficiencyTree->Branch("sCMSNS2LC3_ERSEntries",&sCMSNS2LC3_ERSEntries,"sCMSNS2LC3_ERSEntries/I");
    EfficiencyTree->Branch("sCMSNS2LC2_ERSEntries",&sCMSNS2LC2_ERSEntries,"sCMSNS2LC2_ERSEntries/I");
    EfficiencyTree->Branch("sCMSNS2LC1_ERSEntries",&sCMSNS2LC1_ERSEntries,"sCMSNS2LC1_ERSEntries/I");
    
    EfficiencyTree->Branch("sCMSNS2LC3_ERSIneff",sCMSNS2LC3_ERSIneff,"sCMSNS2LC3_ERSIneff[ERSSteps]/F");
    EfficiencyTree->Branch("sCMSNS2LC2_ERSIneff",sCMSNS2LC2_ERSIneff,"sCMSNS2LC2_ERSIneff[ERSSteps]/F");
    EfficiencyTree->Branch("sCMSNS2LC1_ERSIneff",sCMSNS2LC1_ERSIneff,"sCMSNS2LC1_ERSIneff[ERSSteps]/F");

    EfficiencyTree->Branch("sCMSNS2LC3_ERSErr",sCMSNS2LC3_ERSErr,"sCMSNS2LC3_ERSErr[ERSSteps]/F");
    EfficiencyTree->Branch("sCMSNS2LC2_ERSErr",sCMSNS2LC2_ERSErr,"sCMSNS2LC2_ERSErr[ERSSteps]/F");
    EfficiencyTree->Branch("sCMSNS2LC1_ERSErr",sCMSNS2LC1_ERSErr,"sCMSNS2LC1_ERSErr[ERSSteps]/F");
    
    //--- Processing the data----------------------------------------------------------------------------------------------
    for (int i=0; i<ERSSteps; i++)
    {
        //--- Efficiency	
        sCMSNS2LC3_ERSIneff[i] =1- sCMSNS2LC3_ERSIneff[i]  / sCMSNS2LC3_ERSEntries;
        sCMSNS2LC2_ERSIneff[i] =1- sCMSNS2LC2_ERSIneff[i]  / sCMSNS2LC2_ERSEntries;
        sCMSNS2LC1_ERSIneff[i] =1- sCMSNS2LC1_ERSIneff[i]  / sCMSNS2LC1_ERSEntries;

        //---  Binomial Error                                 
        sCMSNS2LC3_ERSErr[i] = TMath::Sqrt(sCMSNS2LC3_ERSIneff[i]*(1-sCMSNS2LC3_ERSIneff[i])/sCMSNS2LC3_ERSEntries);
        sCMSNS2LC2_ERSErr[i] = TMath::Sqrt(sCMSNS2LC2_ERSIneff[i]*(1-sCMSNS2LC2_ERSIneff[i])/sCMSNS2LC2_ERSEntries);
        sCMSNS2LC1_ERSErr[i] = TMath::Sqrt(sCMSNS2LC1_ERSIneff[i]*(1-sCMSNS2LC1_ERSIneff[i])/sCMSNS2LC1_ERSEntries);
    }
    //---End of Processing the data--------------------------------------------------------------------------------------
    
    //--- Filling, Writing and CLosing the tree
    EfficiencyTree->Fill();
    EfficiencyTree->Write();
    delete EfficiencyTree;
    
    //--- Initializing and writing the TGraphErrors	
    sCMSNS2LC3_ERSIneffGraph = new TGraphErrors(ERSSteps,ERSRad,      sCMSNS2LC3_ERSIneff,(const Float_t*)0,      sCMSNS2LC3_ERSErr);
    sCMSNS2LC2_ERSIneffGraph = new TGraphErrors(ERSSteps,ERSRad,      sCMSNS2LC2_ERSIneff,(const Float_t*)0,      sCMSNS2LC2_ERSErr);
    sCMSNS2LC1_ERSIneffGraph = new TGraphErrors(ERSSteps,ERSRad,      sCMSNS2LC1_ERSIneff,(const Float_t*)0,      sCMSNS2LC1_ERSErr);

    sCMSNS2LC3_ERSIneffGraph->SetTitle("sCMSNS2LC3");
    sCMSNS2LC2_ERSIneffGraph->SetTitle("sCMSNS2LC2");
    sCMSNS2LC1_ERSIneffGraph->SetTitle("sCMSNS2LC1");

    sCMSNS2LC3_ERSIneffGraph->SetName("sCMSNS2LC3_ERSIneffGraph");
    sCMSNS2LC2_ERSIneffGraph->SetName("sCMSNS2LC2_ERSIneffGraph");
    sCMSNS2LC1_ERSIneffGraph->SetName("sCMSNS2LC1_ERSIneffGraph");

    sCMSNS2LC3_ERSIneffGraph->GetYaxis()->SetTitle("Efficiency Radius[mm]");
    sCMSNS2LC2_ERSIneffGraph->GetYaxis()->SetTitle("Efficiency Radius[mm]");
    sCMSNS2LC1_ERSIneffGraph->GetYaxis()->SetTitle("Efficiency Radius[mm]");

    sCMSNS2LC3_ERSIneffGraph->GetXaxis()->SetTitle("Inefficiency");
    sCMSNS2LC2_ERSIneffGraph->GetXaxis()->SetTitle("Inefficiency");
    sCMSNS2LC1_ERSIneffGraph->GetXaxis()->SetTitle("Inefficiency");    

    sCMSNS2LC3_ERSIneffGraph->GetXaxis()->SetRangeUser(0,1);
    sCMSNS2LC2_ERSIneffGraph->GetXaxis()->SetRangeUser(0,1);
    sCMSNS2LC1_ERSIneffGraph->GetXaxis()->SetRangeUser(0,1);    

    sCMSNS2LC3_ERSIneffGraph->Write();
    sCMSNS2LC2_ERSIneffGraph->Write();
    sCMSNS2LC1_ERSIneffGraph->Write();
}

void rd51_Analyzer::DeleteEfficiencyRadiusScan(int verbose)
{
    delete 	             		ERSRad;

    delete                sCMSNS2LC3_ERSIneff;
    delete                sCMSNS2LC2_ERSIneff;
    delete                sCMSNS2LC1_ERSIneff;

    delete                sCMSNS2LC3_ERSErr;
    delete                sCMSNS2LC2_ERSErr;
    delete                sCMSNS2LC1_ERSErr;

    delete                sCMSNS2LC3_ERSIneffGraph;
    delete                sCMSNS2LC2_ERSIneffGraph;
    delete                sCMSNS2LC1_ERSIneffGraph;
}
//-------------------------------------------------------------------------------------
//--- End Of Efficiency Radius Scan Initilaization                                       
//-------------------------------------------------------------------------------------



//-------------------------------------------------------------------------------------
//--- Loader                                       
//-------------------------------------------------------------------------------------

void rd51_Analyzer::LoadSettings()
{
    // Loading Settings....
    rd51analyzer_LoaderSettings = new LoaderSettings_Analyzer("Setting_Analyzer.conf"); 
    if (rd51analyzer_LoaderSettings->error) gApplication->Terminate(0);
    
    rd51analyzer_OffsetFile			=(rd51analyzer_LoaderSettings->Analyzer_OffsetFile).c_str()	;
    rd51analyzer_Verbose                 	= rd51analyzer_LoaderSettings->Analyzer_Verbose             	;
    rd51analyzer_EffCalculatorVerbose    	= rd51analyzer_LoaderSettings->Analyzer_EffCalculatorVerbose	;
    rd51analyzer_EnableCoverage          	= rd51analyzer_LoaderSettings->Analyzer_EnableCoverage      	;
    rd51analyzer_Cut_Verbose               	= rd51analyzer_LoaderSettings->Cut_Verbose                	;
    rd51analyzer_Cut_Chi2Value             	= rd51analyzer_LoaderSettings->Cut_Chi2Value              	;
    rd51analyzer_Cut_ResidualValue         	= rd51analyzer_LoaderSettings->Cut_ResidualValue          	;
    rd51analyzer_Cut_NumberOfTracks        	= rd51analyzer_LoaderSettings->Cut_NumberOfTracks         	; 
    rd51analyzer_Cut_SingleXYTrackRequest 	= rd51analyzer_LoaderSettings->Cut_SingleXYTrackRequest  	;
    rd51analyzer_EfficiencyRadiusScan 		= rd51analyzer_LoaderSettings->EfficiencyRadiusScan  	;
    rd51analyzer_EfficiencyRadiusMin = TMath::Min(rd51analyzer_LoaderSettings->EfficiencyRadiusMin,rd51analyzer_LoaderSettings->EfficiencyRadiusMax);
    rd51analyzer_EfficiencyRadiusMax = TMath::Max(rd51analyzer_LoaderSettings->EfficiencyRadiusMax,rd51analyzer_LoaderSettings->EfficiencyRadiusMin); 
    rd51analyzer_EfficiencyRadiusStep 		= rd51analyzer_LoaderSettings->EfficiencyRadiusStep  	;
    
    if (rd51analyzer_Verbose)
    {
	    cout    
        << "Offset File	    		\t" << rd51analyzer_OffsetFile	        	<< "\n"
        << "Verbose             	\t" << rd51analyzer_Verbose             	<< "\n"
        << "EffCalculatorVerbose	\t" << rd51analyzer_EffCalculatorVerbose	<< "\n"
        << "Enable Coverage		\t" << rd51analyzer_EnableCoverage      	<< "\n"    
        << "Cut_Chi2Value            	\t" << rd51analyzer_Cut_Verbose            	<< "\n"
        << "Cut_Chi2Value            	\t" << rd51analyzer_Cut_Chi2Value            	<< "\n"
        << "Cut_ResidualValue        	\t" << rd51analyzer_Cut_ResidualValue        	<< "\n"
        << "Cut_NumberOfTracks       	\t" << rd51analyzer_Cut_NumberOfTracks       	<< "\n"
        << "Cut_SingleXYTrackRequest	\t" << rd51analyzer_Cut_SingleXYTrackRequest   << "\n"
        << "EfficiencyRadiusScan	\t" << rd51analyzer_EfficiencyRadiusScan	<< "\n"
        << "EfficiencyRadiusMin 	\t" << rd51analyzer_EfficiencyRadiusMin 	<< "\n"
        << "EfficiencyRadiusMax 	\t" << rd51analyzer_EfficiencyRadiusMax 	<< "\n"
        << "EfficiencyRadiusStep	\t" << rd51analyzer_EfficiencyRadiusStep    
        << endl;
    }
}

void rd51_Analyzer::LoadOffsetAndCoverage(int verbose)
{
    // Loading Offset And Coverage....  
    rd51analyzer_LoaderOffsetAndCoverage = new LoaderOffsetAndCoverage_Analyzer(rd51analyzer_OffsetFile, 3);//HARDCODED NUMBER OF DETECTOR
    if (rd51analyzer_LoaderOffsetAndCoverage->error) gApplication->Terminate(0);
    
    int rd51analyzer_NumberOfDetectors = rd51analyzer_LoaderOffsetAndCoverage->NumberOfDetectors;
    
    DUT_offsetX      = new double[rd51analyzer_NumberOfDetectors];
    DUT_offsetY      = new double[rd51analyzer_NumberOfDetectors];
    DUT_offsetZ      = new double[rd51analyzer_NumberOfDetectors];
    DUT_trkoffsetX   = new double[rd51analyzer_NumberOfDetectors];
    DUT_trkoffsetY   = new double[rd51analyzer_NumberOfDetectors];
    DUT_MinX         = new double[rd51analyzer_NumberOfDetectors];
    DUT_MaxX         = new double[rd51analyzer_NumberOfDetectors];
    DUT_MinY         = new double[rd51analyzer_NumberOfDetectors];
    DUT_MaxY         = new double[rd51analyzer_NumberOfDetectors];
    DUT_MinR         = new double[rd51analyzer_NumberOfDetectors];
    DUT_MaxR         = new double[rd51analyzer_NumberOfDetectors];
    DUT_MinPhi       = new double[rd51analyzer_NumberOfDetectors];
    DUT_MaxPhi       = new double[rd51analyzer_NumberOfDetectors];
    DUT_effRad       = new double[rd51analyzer_NumberOfDetectors];
    
    for (int i=0; i<rd51analyzer_NumberOfDetectors; i++) {
        DUT_offsetX[i]	= rd51analyzer_LoaderOffsetAndCoverage->xOffset[i]       ;
        DUT_offsetY[i]	= rd51analyzer_LoaderOffsetAndCoverage->yOffset[i]       ;
        DUT_offsetZ[i]	= rd51analyzer_LoaderOffsetAndCoverage->zOffset[i]       ;
        DUT_trkoffsetX[i]	= rd51analyzer_LoaderOffsetAndCoverage->xTrackerOffset[i];
        DUT_trkoffsetY[i]	= rd51analyzer_LoaderOffsetAndCoverage->yTrackerOffset[i];
        DUT_MinX[i]		= rd51analyzer_LoaderOffsetAndCoverage->xCoverageMin[i]  ;
        DUT_MaxX[i]		= rd51analyzer_LoaderOffsetAndCoverage->xCoverageMax[i]  ;
        DUT_MinY[i]		= rd51analyzer_LoaderOffsetAndCoverage->yCoverageMin[i]  ;
        DUT_MaxY[i]		= rd51analyzer_LoaderOffsetAndCoverage->yCoverageMax[i]  ;
        DUT_MinR[i]		= rd51analyzer_LoaderOffsetAndCoverage->RCoverageMin[i]  ;
        DUT_MaxR[i]		= rd51analyzer_LoaderOffsetAndCoverage->RCoverageMax[i]  ;
        DUT_MinPhi[i]	= rd51analyzer_LoaderOffsetAndCoverage->PhiCoverageMax[i];
        DUT_MaxPhi[i]	= rd51analyzer_LoaderOffsetAndCoverage->PhiCoverageMin[i];
        DUT_effRad[i]	= rd51analyzer_LoaderOffsetAndCoverage->effRad[i]	 ;
    }
}
//-------------------------------------------------------------------------------------
//--- End of Loader                                       
//-------------------------------------------------------------------------------------






//-------------------------------------------------------------------------------------
//--- Histograms                                       
//-------------------------------------------------------------------------------------
void rd51_Analyzer::HistoWrite(int verbose)
{
    // Writing Histograms....
    if (verbose) GreenOut("Writing Histograms....\n");
    
    hsCMSNS2LC3_Eff		->Write();		
    hsCMSNS2LC3_XY_Eff		->Write();	
    hsCMSNS2LC3_XY_Ineff	->Write();	
    hsCMSNS2LC3_XY_Noise	->Write();	
    hsCMSNS2LC3_CLS_Eff		->Write();	
    hsCMSNS2LC3_CLS_Noise	->Write();	
    hsCMSNS2LC3_Distance_Eff	->Write();	
    hsCMSNS2LC3_Distance_Noise	->Write();	
    hsCMSNS2LC3_Residual_X	->Write();	    

    hsCMSNS2LC2_Eff		->Write();		
    hsCMSNS2LC2_XY_Eff		->Write();	
    hsCMSNS2LC2_XY_Ineff	->Write();	
    hsCMSNS2LC2_XY_Noise	->Write();	
    hsCMSNS2LC2_CLS_Eff		->Write();	
    hsCMSNS2LC2_CLS_Noise	->Write();	
    hsCMSNS2LC2_Distance_Eff	->Write();	
    hsCMSNS2LC2_Distance_Noise	->Write();	
    hsCMSNS2LC2_Residual_X	->Write();		
    
    hsCMSNS2LC1_Eff		->Write();		
    hsCMSNS2LC1_XY_Eff		->Write();	
    hsCMSNS2LC1_XY_Ineff	->Write();	
    hsCMSNS2LC1_XY_Noise	->Write();	
    hsCMSNS2LC1_CLS_Eff		->Write();	
    hsCMSNS2LC1_CLS_Noise	->Write();	
    hsCMSNS2LC1_Distance_Eff	->Write();	
    hsCMSNS2LC1_Distance_Noise	->Write();	
    hsCMSNS2LC1_Residual_X	->Write();		

}


void rd51_Analyzer::HistoDelete(int verbose)
{
    // Deleting Histograms....
    if (verbose) GreenOut("Deleting Histograms....\n");
    
    
    delete hsCMSNS2LC3_Eff		;
    delete hsCMSNS2LC3_XY_Eff		;
    delete hsCMSNS2LC3_XY_Ineff		;
    delete hsCMSNS2LC3_XY_Noise		;
    delete hsCMSNS2LC3_CLS_Eff		;
    delete hsCMSNS2LC3_CLS_Noise	;
    delete hsCMSNS2LC3_Distance_Eff	;
    delete hsCMSNS2LC3_Distance_Noise	;
    delete hsCMSNS2LC3_Residual_X	;
    
    delete hsCMSNS2LC2_Eff		;
    delete hsCMSNS2LC2_XY_Eff		;
    delete hsCMSNS2LC2_XY_Ineff		;
    delete hsCMSNS2LC2_XY_Noise		;
    delete hsCMSNS2LC2_CLS_Eff		;
    delete hsCMSNS2LC2_CLS_Noise	;
    delete hsCMSNS2LC2_Distance_Eff	;
    delete hsCMSNS2LC2_Distance_Noise	;
    delete hsCMSNS2LC2_Residual_X	;
    
    delete hsCMSNS2LC1_Eff		;
    delete hsCMSNS2LC1_XY_Eff		;
    delete hsCMSNS2LC1_XY_Ineff		;
    delete hsCMSNS2LC1_XY_Noise		;
    delete hsCMSNS2LC1_CLS_Eff		;
    delete hsCMSNS2LC1_CLS_Noise	;
    delete hsCMSNS2LC1_Distance_Eff	;
    delete hsCMSNS2LC1_Distance_Noise	;
    delete hsCMSNS2LC1_Residual_X	;

}

void rd51_Analyzer::HistoDefine(int verbose)
{
    // Creating Histograms....
    if (verbose) GreenOut("Defining Histograms....\n");
    
    //--- CTL BottomLeftxcl---
     //--- CMS 30x30 and GE1/1---
    hsCMSNS2LC3_Eff		= new TH1F("hsCMSNS2LC3_Eff"		,"",  20, -0.5	, 19.5			); // commented by PATR
    hsCMSNS2LC3_XY_Eff		= new TH2F("hsCMSNS2LC3_XY_Eff"		,"", 400,-200.	,200.	,400,-200.,200.	);
    hsCMSNS2LC3_XY_Ineff	= new TH2F("hsCMSNS2LC3_XY_Ineff"	,"", 400,-200.	,200.	,400,-200.,200.	);
    hsCMSNS2LC3_XY_Noise	= new TH2F("hsCMSNS2LC3_XY_Noise"	,"", 400,-200.	,200.	,400,-200.,200.	);
    hsCMSNS2LC3_CLS_Eff		= new TH1F("hsCMSNS2LC3_CLS_Eff"	,"", 100,-0.5	,99.5			);
    hsCMSNS2LC3_CLS_Noise	= new TH1F("hsCMSNS2LC3_CLS_Noise"	,"", 100,-0.5	,99.5			);
    hsCMSNS2LC3_Distance_Eff	= new TH1F("hsCMSNS2LC3_Distance_Eff"	,"",1000, 0.	,100.			);
    hsCMSNS2LC3_Distance_Noise	= new TH1F("hsCMSNS2LC3_Distance_Noise"	,"",1000, 0.	,100.			);
    hsCMSNS2LC3_Residual_X 	= new TH1F("hsCMSNS2LC3_Residual_X"	,"", 110,-4.	,4.			);
    
    hsCMSNS2LC3_Eff		->SetTitle(		"CMS 30x30: Efficiency"					);	   
    hsCMSNS2LC3_XY_Eff		->SetTitle(		"CMS 30x30: Tracker Hits with DUT Active"		);         
    hsCMSNS2LC3_XY_Ineff	->SetTitle(		"CMS 30x30:: Tracker Hits with DUT Inactive/Not Aligned");         
    hsCMSNS2LC3_XY_Noise	->SetTitle(		"CMS 30x30:: Tracker Hits with DUT Not Aligned"		);         
    hsCMSNS2LC3_CLS_Eff		->SetTitle(		"CMS 30x30:: Cluster Size for hits aligned with tracks"	);         
    hsCMSNS2LC3_CLS_Noise	->SetTitle(	"CMS 30x30:: Cluster Size for hits not aligned with tracks" 	);         
    hsCMSNS2LC3_Distance_Eff	->SetTitle(	"CMS 30x30:: Hit-Track Distance for ALIGNED hits"		);         
    hsCMSNS2LC3_Distance_Noise	->SetTitle(	"CMS 30x30:: Hit-Track Distance for NOT ALIGNED hits"	  	);         
    hsCMSNS2LC3_Residual_X	->SetTitle(	"CMS 30x30:: X Residuals"					);         
    

    //--- CMS 30x30 and GE1/1---
    hsCMSNS2LC2_Eff		= new TH1F("hsCMSNS2LC2_Eff"		,"",  20, -0.5	, 19.5			); // commented by PATR
    hsCMSNS2LC2_XY_Eff		= new TH2F("hsCMSNS2LC2_XY_Eff"		,"", 400,-200.	,200.	,400,-200.,200.	);
    hsCMSNS2LC2_XY_Ineff	= new TH2F("hsCMSNS2LC2_XY_Ineff"	,"", 400,-200.	,200.	,400,-200.,200.	);
    hsCMSNS2LC2_XY_Noise	= new TH2F("hsCMSNS2LC2_XY_Noise"	,"", 400,-200.	,200.	,400,-200.,200.	);
    hsCMSNS2LC2_CLS_Eff		= new TH1F("hsCMSNS2LC2_CLS_Eff"	,"", 100,-0.5	,99.5			);
    hsCMSNS2LC2_CLS_Noise	= new TH1F("hsCMSNS2LC2_CLS_Noise"	,"", 100,-0.5	,99.5			);
    hsCMSNS2LC2_Distance_Eff	= new TH1F("hsCMSNS2LC2_Distance_Eff"	,"",1000, 0.	,100.			);
    hsCMSNS2LC2_Distance_Noise	= new TH1F("hsCMSNS2LC2_Distance_Noise"	,"",1000, 0.	,100.			);
    hsCMSNS2LC2_Residual_X 	= new TH1F("hsCMSNS2LC2_Residual_X"	,"",110,-4.	,4.			);
    
    hsCMSNS2LC2_Eff		->SetTitle("CMS 30x30: Efficiency"					  	);	   
    hsCMSNS2LC2_XY_Eff		->SetTitle("CMS 30x30: Tracker Hits with DUT Active"			  	);         
    hsCMSNS2LC2_XY_Ineff	->SetTitle("CMS 30x30:: Tracker Hits with DUT Inactive/Not Aligned"	  	);         
    hsCMSNS2LC2_XY_Noise	->SetTitle("CMS 30x30:: Tracker Hits with DUT Not Aligned"		  	);         
    hsCMSNS2LC2_CLS_Eff		->SetTitle("CMS 30x30:: Cluster Size for hits aligned with tracks"	  	);         
    hsCMSNS2LC2_CLS_Noise	->SetTitle("CMS 30x30:: Cluster Size for hits not aligned with tracks" 		);         
    hsCMSNS2LC2_Distance_Eff	->SetTitle("CMS 30x30:: Hit-Track Distance for ALIGNED hits"		  	);         
    hsCMSNS2LC2_Distance_Noise	->SetTitle("CMS 30x30:: Hit-Track Distance for NOT ALIGNED hits"	  	);         
    hsCMSNS2LC2_Residual_X	->SetTitle("CMS 30x30:: X Residuals"					  	);         

    hsCMSNS2LC1_Eff		= new TH1F("hsCMSNS2LC1_Eff"		,"",  20, -0.5	, 19.5			);
    hsCMSNS2LC1_XY_Eff		= new TH2F("hsCMSNS2LC1_XY_Eff"		,"", 400,-200.	,200.	,400,-200.,200.	);
    hsCMSNS2LC1_XY_Ineff	= new TH2F("hsCMSNS2LC1_XY_Ineff"	,"", 400,-200.	,200.	,400,-200.,200.	);
    hsCMSNS2LC1_XY_Noise	= new TH2F("hsCMSNS2LC1_XY_Noise"	,"", 400,-200.	,200.	,400,-200.,200.	);
    hsCMSNS2LC1_CLS_Eff		= new TH1F("hsCMSNS2LC1_CLS_Eff"	,"", 100,-0.5	,99.5			);
    hsCMSNS2LC1_CLS_Noise	= new TH1F("hsCMSNS2LC1_CLS_Noise"	,"", 100,-0.5	,99.5			);
    hsCMSNS2LC1_Distance_Eff	= new TH1F("hsCMSNS2LC1_Distance_Eff"	,"",1000, 0.	,100.			);
    hsCMSNS2LC1_Distance_Noise	= new TH1F("hsCMSNS2LC1_Distance_Noise"	,"",1000, 0.	,100.			);
    hsCMSNS2LC1_Residual_X 	= new TH1F("hsCMSNS2LC1_Residual_X"	,"",1000,-100.	,100.			);
    
    hsCMSNS2LC1_Eff		->SetTitle("CMS 30x30: Efficiency"					  	);	   
    hsCMSNS2LC1_XY_Eff		->SetTitle("CMS 30x30: Tracker Hits with DUT Active"			  	);         
    hsCMSNS2LC1_XY_Ineff	->SetTitle("CMS 30x30:: Tracker Hits with DUT Inactive/Not Aligned"	  	);         
    hsCMSNS2LC1_XY_Noise	->SetTitle("CMS 30x30:: Tracker Hits with DUT Not Aligned"		  	);         
    hsCMSNS2LC1_CLS_Eff		->SetTitle("CMS 30x30:: Cluster Size for hits aligned with tracks"	  	);         
    hsCMSNS2LC1_CLS_Noise	->SetTitle("CMS 30x30:: Cluster Size for hits not aligned with tracks" 		);         
    hsCMSNS2LC1_Distance_Eff	->SetTitle("CMS 30x30:: Hit-Track Distance for ALIGNED hits"		  	);         
    hsCMSNS2LC1_Distance_Noise	->SetTitle("CMS 30x30:: Hit-Track Distance for NOT ALIGNED hits"	  	);         
    hsCMSNS2LC1_Residual_X	->SetTitle("CMS 30x30:: X Residuals"					  	);         

} 
//-------------------------------------------------------------------------------------
//--- End of Histograms                                       
//-------------------------------------------------------------------------------------
