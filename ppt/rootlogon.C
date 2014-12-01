{
cout<<"to >> rootlogon.C"<<endl;
gROOT->GetApplication()->ProcessLine("#include <iomanip>");
gStyle->SetPalette(1);
gStyle->SetLabelOffset(0.01,"X");
gStyle->SetLabelOffset(0.01,"Y");
gStyle->SetLabelSize(0.04,"X"); /////////////////// 0.08 / 0.04
gStyle->SetLabelSize(0.04,"Y");
gStyle->SetLabelSize(0.04,"Z");
gStyle->SetMarkerStyle(20);
gStyle->SetMarkerColor(1);
gStyle->SetMarkerSize(0.1);
gStyle->SetOptStat(1111111);
gStyle->SetOptFit(1111);
gStyle->SetStatY(0.99);
gStyle->SetStatX(0.99);
gStyle->SetStatW(0.22);
gStyle->SetStatH(0.11);
gStyle->SetLineWidth(1);
gStyle->SetLineColor(1);     // errbars
gStyle->SetHistLineWidth(1);
gStyle->SetHistLineColor(1); // frames
gStyle->SetHistFillColor(0); // ?
gStyle->SetFillStyle(0);
gStyle->SetFillColor(1);    // ?
gStyle->SetFuncWidth(1);   // fitline
gStyle->SetFuncColor(2);   // fitline
//gStyle->SetTitleXOffset(1.8);
//gStyle->SetTitleYOffset(1.6);
//gStyle->SetTitleXSize(0.2);
gStyle->SetTitleXOffset(0.7);
gStyle->SetTitleXSize(0.08);
gStyle->SetTitleYOffset(1.0);
gStyle->SetTitleColor(1);
gStyle->SetTitleFillColor(0);
gStyle->SetStatColor(0);
gStyle->SetCanvasColor(0);
gStyle->SetCanvasDefX(0);
gStyle->SetCanvasDefY(0);
gStyle->SetCanvasDefW(500);
gStyle->SetCanvasDefH(500);
gStyle->SetPadLeftMargin(0.1);
gStyle->SetPadRightMargin(0.1);
gStyle->SetPadTopMargin(0.06);
gStyle->SetPadBottomMargin(0.15); ///0.09 / 0.15
gStyle->SetCanvasBorderMode(0);
gStyle->SetCanvasBorderSize(0);
gStyle->SetTitleBorderSize(2);
gStyle->SetTitleX(0.01);
gStyle->SetTitleW(0.65);
gStyle->SetTitleH(0.05);
gStyle->SetNdivisions(510,"Y");
gStyle->SetNdivisions(510,"X");
gStyle->SetDrawBorder(0);
gStyle->SetPadBorderSize(0);
gStyle->SetPadGridX(0);
gStyle->SetPadGridY(0);
gStyle->SetOptLogx(0);
gStyle->SetOptLogy(0);
gROOT->ForceStyle();
cout<<"rootlogon.C >> end"<<endl;
}
// vim: set ai sw=4 ts=4:
