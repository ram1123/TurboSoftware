//#include "Riostream.h"
//#include "vector.h"
#include "TGraphErrors.h"
#include "setTDRStyle.C"


void Cluster_Size_vs_HV() {

   ifstream in;
   in.open("Cluster_Size.txt");

   TGaxis::SetMaxDigits(3);
   gStyle->SetOptStat(0);
   // Set TDR Style
   setTDRStyle();


   Float_t HighVoltage, Cluster_Size;
   vector<float> v_HighVoltage, v_Cluster_Size;

   Int_t nlines = 0;
   TFile *f = new TFile("Cluster_Size_R1592_R1646.root","RECREATE");
   TNtuple *ntuple = new TNtuple("ntuple","data from ascii file","HV:Cluster_Size");
//   TCanvas *c1 = new TCanvas("c1","HighVoltage_vs_Cluster_Size");
   TCanvas* c1 = new TCanvas("c1","",1);
   c1->Range(0,0,1,1);
   TPad *pad = new TPad("pad","",0,0,1,1);
   pad->SetGrid();
   pad->Draw();
   pad->cd();


string line;
while(getline(in,line))
{
        if(line[0] == '#') continue;

	stringstream(line) >> HighVoltage >> Cluster_Size;
	
	cout<<"===> "<<HighVoltage <<"\t "<<Cluster_Size<<endl;
	v_HighVoltage.push_back(HighVoltage);
	v_Cluster_Size.push_back(Cluster_Size);
	ntuple->Fill(HighVoltage,Cluster_Size);
}
   printf(" found %zu points\n",v_HighVoltage.size());
   in.close();

   TGraphErrors * gr = new TGraphErrors(v_HighVoltage.size()); 
    
   for (unsigned int i = 0; i<v_HighVoltage.size();i++)
{
	gr->SetPoint(i,v_HighVoltage[i],v_Cluster_Size[i]);
	gr->SetPointError(i,0,0);
}

   gr->SetTitle("");
   //gr->SetTitle("High Voltage vs Cluster Size");
   gr->GetXaxis()->SetTitle("High Voltage supplied to divider (kV)");
   gr->GetYaxis()->SetTitle("Cluster Size");
   gr->GetYaxis()->SetTitleOffset(1.2);
   gr->GetXaxis()->SetTitleOffset(0.9);
   gr->GetYaxis()->SetTitleSize(0.05);
   gr->GetXaxis()->SetTitleSize(0.05);
   //gr->GetXaxis()->SetLabelSize(0.05);
   gr->SetMarkerSize(1);
   gr->SetMarkerColor(2);
   gr->SetMarkerStyle(21);

   gr->Draw("ALP");

   TLatex *text1 = new TLatex(690,2.107,"Threshold = 1.2 fC");
   TLatex *text2 = new TLatex(690,2.104,"Beam: Muon");
   TLatex *text3 = new TLatex(690,2.101,"Gap Config: 3/1/2/1 mm");
   TLatex *text5 = new TLatex(690,2.098,"Gas: Ar/CO2/CF4 (45/15/40)");
//   TLatex *text3 = new TLatex(3800,0.38,MSPL);
//   TLatex *text4 = new TLatex(3800,0.22,Threshold);
//   TLatex *text5 = new TLatex(3250,0.64,ClockMode);


   text1->SetTextFont(42);
   text2->SetTextFont(42);
   text3->SetTextFont(42);
   text5->SetTextFont(42);
   text1->SetTextSize(0.05);
   text2->SetTextSize(0.05);
   text3->SetTextSize(0.05);
   text5->SetTextSize(0.05);
   TLatex *cmsprem = new TLatex(560,2.110,"#it{CMS Preliminary}");

   TLatex *gen = new TLatex(795,2.110,"GE1/1");

   text1->Draw("same");
   text2->Draw("same");
   text3->Draw("same");
   text5->Draw("same");
   cmsprem->Draw("same");
   gen->Draw("same");



   c1->Write();
   c1->SaveAs("HighVoltage_Vs_Cluster_Size.pdf");
   c1->SaveAs("HighVoltage_Vs_Cluster_Size.png");
   c1->SaveAs("HighVoltage_Vs_Cluster_Size.root");
   c1->SaveAs("HighVoltage_Vs_Cluster_Size.C");
   f->Write();
}
