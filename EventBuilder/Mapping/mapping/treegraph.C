#include "Riostream.h"
void treegraph(TString filename) {
   gROOT->SetStyle("Plain");
   gStyle->SetOptDate();


   Double_t x, y;
   Int_t nlines = 0;
   TFile *f = new TFile("graph.root","RECREATE");

   TCanvas *canvas_graph = new TCanvas("canvas_graph", "y vs x",467,89,400,700);

   TTree t;
   t.ReadFile(filename,"x:y");
   t.Draw("x:y","","goff");

   TGraph *g = new TGraph(t.GetSelectedRows(),t.GetV1(),t.GetV2());
   g->SetTitle(filename+": Y vs X");
   g->GetXaxis()->SetTitle("x[a.u.]");
   g->GetYaxis()->SetTitle("y[a.u.]");

   g->SetMarkerStyle(21);
   g->Draw("AP");

   f->Write();
}

