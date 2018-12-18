#include <iostream>
#include <string>
#include <limits>
#include <sstream>
#include <iomanip>

using namespace std;


// Converts an int to a string
string int_to_string(int integer) {
  ostringstream stst;
  stst << integer;
  return stst.str();
}
//-----------------------------------------------------------------------------
// Converts a double to a string
namespace my {

    std::string to_string( double d ) {

        std::ostringstream stm ;
        //stm << std::setprecision(std::numeric_limits<double>::digits10) << d ;
        stm << std::setprecision(4) << d ;
        return stm.str() ;
    }
}
//-----------------------------------------------------------------------------
void allFinalCurves1() {
Double_t newx1=0.6, newx2=0.9, newy1=0.1, newy2=0.35;
Float_t labelOffsetY=0.65, labelSizeY = 0.06;
Float_t labelOffsetX=0.7, labelSizeX = 0.06;

TCanvas *c2 = new TCanvas("c2","Sigma",200,10,700,500);
c2->SetGrid();
TGraphErrors *g2 = new TGraphErrors("sigma_DeltaT1.dat");
TAxis *axis2 = g2 -> GetXaxis();
  gStyle->SetOptStat(0);
//ajuste de la línea recta

TF1 *line2 = new TF1("line2","pol0",-5.,5.);
line2 -> SetLineColor(2);
g2 -> Fit(line2);

g2 -> SetMarkerColor(kBlack);
g2 -> SetMarkerStyle(21);
g2 -> Draw("AP");
g2 -> SetTitle("#Delta t");
g2 -> GetYaxis() -> SetTitle ("#sigma_{#Delta t} (ns)");
g2 -> GetXaxis() -> SetTitle ("position (cm)");
g2 -> GetYaxis() -> SetTitleOffset(labelOffsetY);
g2 -> GetYaxis() -> SetTitleSize(labelSizeY);
g2 -> GetXaxis() -> SetTitleOffset(labelOffsetX);
g2 -> GetXaxis() -> SetTitleSize(labelSizeX);
gStyle->SetOptFit(1111);
//gStyle->SetStatX(0.7);
//gStyle->SetStatY(0.1);

c2->Print("sigmaT.png");

//**********************************************************************************


TCanvas *c1 = new TCanvas("c1","Mean",200,10,700,500);
c1->SetGrid();
TGraphErrors *g = new TGraphErrors("mean_DeltaT11.dat");
TAxis *axis1 = g -> GetXaxis();
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(0);
//ajuste de la línea recta

TF1 *line1 = new TF1("line1","pol1",-5.,5.);
line1 -> SetLineColor(2);
g -> Fit(line1);

g -> SetMarkerColor(kBlack);
g -> SetMarkerStyle(21);
g -> Draw("AP");
g -> SetTitle("#Delta t");
g -> GetYaxis() -> SetTitle ("#mu_{#Delta t} (ns)");
gStyle->SetOptFit(1111);
g -> GetXaxis() -> SetTitle ("position (cm)");
g -> GetYaxis() -> SetTitleOffset(labelOffsetY);
g -> GetYaxis() -> SetTitleSize(labelSizeY);
g -> GetXaxis() -> SetTitleOffset(labelOffsetX);
g -> GetXaxis() -> SetTitleSize(labelSizeX);
double meanDT = line1 -> GetParameter(1);
double eMeanDT = line1 -> GetParError(1);
double sigmaDT = line2 -> GetParameter(0);
double eSigmaDT = line2 -> GetParError(0);
string resoltionDt="Position resolution: ";
string resoltionDt1= my::to_string(TMath::Abs(sigmaDT/meanDT))+"#pm"+my::to_string(TMath::Sqrt(((sigmaDT*eMeanDT/(meanDT*meanDT))*(sigmaDT*eMeanDT/(meanDT*meanDT)))+((eSigmaDT/meanDT)*(eSigmaDT/meanDT))))+"cm";
TPaveText *labelDt = new TPaveText(0.1,0.1,0.5,0.3,"brNDC");
labelDt->AddText(resoltionDt.c_str());
labelDt->AddText(resoltionDt1.c_str());
labelDt->Draw();
c1->Print("meanT.png");
c1->Print("meanT.pdf");

//**********************************************************************************
TCanvas *c4 = new TCanvas("c4","Sigma",200,10,700,500);
c4->SetGrid();
TGraphErrors *g4 = new TGraphErrors("sigmaHdiffAmplVar11.dat");
TAxis *axis4 = g4 -> GetXaxis();

  gStyle->SetOptStat(0);

//gPad->SetLogy();
//gPad->SetLogx();
//ajuste de la línea recta

TF1 *line4 = new TF1("line4","pol0",-5,5);
line4 -> SetLineColor(2);
g4-> Fit(line4);

g4 -> SetMarkerColor(kBlack);
g4 -> SetMarkerStyle(21);
g4 -> Draw("AP");
g4 -> SetTitle("#sigma_{#frac{A_{1}-A_{2}}{A_{1}+A_{2}}}");
g4 -> GetYaxis() -> SetTitle ("#sigma_{#frac{A_{1}-A_{2}}{A_{1}+A_{2}}}");
g4 -> GetYaxis() -> SetTitleOffset(labelOffsetY);
g4 -> GetYaxis() -> SetTitleSize(labelSizeY);
g4 -> GetXaxis() -> SetTitleOffset(labelOffsetX);
g4 -> GetXaxis() -> SetTitleSize(labelSizeX);
g4 -> GetXaxis() -> SetTitle ("position (cm)");
gStyle->SetOptFit(1111);
c4->Print("sigmaRatio.png");

//**********************************************************************************
TCanvas *c7 = new TCanvas("c7","Mean",200,10,700,500);
c7->SetGrid();
TGraphErrors *g7= new TGraphErrors("mean_hRatioError1.dat");
TAxis *axis7 = g7-> GetXaxis();


TF1 *line7 = new TF1("line7","pol5",-5,5);
line7 -> SetLineColor(2);
g7-> Fit(line7);

  gStyle->SetOptStat(0);
  gStyle->SetOptFit(0);
g7-> SetMarkerColor(kBlack);
g7-> SetMarkerStyle(21);
g7-> Draw("AP");
//g7a->Draw("same");
g7-> SetTitle("A_{2}/A_{1}");
g7-> GetYaxis() -> SetTitle ("#mu_{A_{2}/A_{1}}");
g7-> GetXaxis() -> SetTitle ("position (cm)");
g7 -> GetYaxis() -> SetTitleOffset(labelOffsetY);
g7 -> GetYaxis() -> SetTitleSize(labelSizeY);
g7 -> GetXaxis() -> SetTitleOffset(labelOffsetX);
g7 -> GetXaxis() -> SetTitleSize(labelSizeX);
gStyle->SetOptFit(1111);
TPaveStats *st1 = (TPaveStats*)g7->FindObject("stats");
st1->SetX1NDC(newx1); //new x start position
st1->SetX2NDC(newx2); //new x end position
st1->SetY1NDC(0.7); //new y start position
st1->SetY2NDC(0.95); //new y end posit

/*double p1 = line7 -> GetParameter(1);
double eP1= line7 -> GetParError(1);
double p2 = line7 -> GetParameter(2);
double eP2= line7 -> GetParError(2);
double p3 = line7 -> GetParameter(3);
double eP3= line7 -> GetParError(3);
double p4 = line7 -> GetParameter(4);
double eP4= line7 -> GetParError(4);
double p5 = line7 -> GetParameter(5);
double eP5= line7 -> GetParError(5);
*/
c7->Print("meanRatio.png");
//**********************************************************************************

//**********************************************************************************
//**********************************************************************************


TCanvas *c10 = new TCanvas("c10","Sigma",200,10,700,500);
c10->SetGrid();
TGraphErrors *g10= new TGraphErrors("sigma_hLogAmpl1.dat");
TAxis *axis10 = g10-> GetXaxis();


TF1 *line10 = new TF1("line9","pol0",-5,5);
line10 -> SetLineColor(2);
g10-> Fit(line10);

  gStyle->SetOptStat(0);
  gStyle->SetOptFit(0);
g10-> SetMarkerColor(kBlack);
g10-> SetMarkerStyle(21);
g10-> Draw("AP");
//g10a->Draw("same");
g10-> SetTitle("log(A_{1}/A_{2})");
g10-> GetYaxis() -> SetTitle ("#sigma_{log(A_{1}/A_{2})} (mV)");
g10-> GetXaxis() -> SetTitle ("position (cm)");
gStyle->SetOptFit(1111);
TPaveStats *st10 = (TPaveStats*)g10->FindObject("stats");
st10->SetX1NDC(newx1); //new x start position
st10->SetX2NDC(newx2); //new x end position
st10->SetY1NDC(0.85); //new y start position
st10->SetY2NDC(0.95); //new y end posit
c10->Print("sigmahLog.png");
//**********************************************************************************

TCanvas *c3 = new TCanvas("c3","Mean",200,10,700,500);
c3->SetGrid();

TGraphErrors *g3 = new TGraphErrors("mean_hLogAmpl1.dat");
TAxis *axis3 = g3-> GetXaxis();
  gStyle->SetOptStat(0);

//ajuste de la línea recta

TF1 *line3 = new TF1("line3","pol1",-5,5);
line3 -> SetLineColor(2);
g3-> Fit(line3);

g3-> SetMarkerColor(kBlack);
g3-> SetMarkerStyle(21);
g3-> Draw("AP");
g3-> SetTitle("log(A_{1}/A_{2})");
g3-> GetYaxis() -> SetTitle ("#mu_{log(A_{1}/A_{2})}");
g3-> GetXaxis() -> SetTitle ("position (cm)");
g3 -> GetYaxis() -> SetTitleOffset(labelOffsetY);
g3 -> GetYaxis() -> SetTitleSize(labelSizeY);
g3 -> GetXaxis() -> SetTitleOffset(labelOffsetX);
g3 -> GetXaxis() -> SetTitleSize(labelSizeX);
gStyle->SetOptFit(1111);
TPaveStats *st = (TPaveStats*)g3->FindObject("stats");
st->SetX1NDC(newx1); //new x start position
st->SetX2NDC(newx2); //new x end position
st->SetY1NDC(0.7); //new y start position
st->SetY2NDC(0.95); //new y end posit

double meanHLog = line3 -> GetParameter(1);
double eMeanHLog = line3 -> GetParError(1);
double sigmaHLog = line10 -> GetParameter(0);
double eSigmaHLog = line10 -> GetParError(0);
/*
double p1Log = line3 -> GetParameter(1);
double eP1Log= line3 -> GetParError(1);
double p2Log = line3 -> GetParameter(2);
double eP2Log= line3 -> GetParError(2);
double p3Log = line3 -> GetParameter(3);
double eP3Log= line3 -> GetParError(3);
double p4Log = line3 -> GetParameter(4);
double eP4Log= line3 -> GetParError(4);
double p5Log = line3 -> GetParameter(5);
double eP5Log= line3 -> GetParError(5);
*/
string resoltionHLog="Position resolution: ";
string resoltionHLog1= my::to_string(TMath::Abs(sigmaHLog/meanHLog))+"#pm"+my::to_string(TMath::Sqrt(((sigmaHLog*eMeanHLog/(meanHLog*meanHLog))*(sigmaHLog*eMeanHLog/(meanHLog*meanHLog)))+((eSigmaHLog/meanHLog)*(eSigmaHLog/meanHLog))))+"cm";
TPaveText *labelHLog = new TPaveText(0.1,0.1,0.5,0.3,"brNDC");
labelHLog->AddText(resoltionHLog.c_str());
labelHLog->AddText(resoltionHLog1.c_str());
labelHLog->Draw();

//double sigmahLog = line4 -> GetParameter(0);
//string resoltionhLog=" "+int_to_string((int) sigmaDT/meanDT)+"cm";
//TPaveText *labelhLog = new TPaveText(0.65,0.90,0.9,0.99,"brNDC");
//labelhLog->AddText(resoltionhLog.c_str());
//labelhLog->Draw();
c3->Print("meanLog.png");

//**********************************************************************************
TCanvas *c8 = new TCanvas("c8","positionRecAmpl",200,10,700,500);
c8->SetGrid();
TGraphErrors *g8= new TGraphErrors("posRec_ampl.dat");
TAxis *axis8 = g8-> GetXaxis();
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(0);
//ajuste de la línea recta

TF1 *line8 = new TF1("line8","pol1",-5,5);
line8 -> SetLineColor(2);
g8-> Fit(line8);

g8-> SetMarkerColor(kBlack);
g8-> SetMarkerStyle(21);
g8-> Draw("AP");
//g8a->Draw("same");
g8-> SetTitle("Position reconstruction via amplitude");
g8-> GetYaxis() -> SetTitle ("calculated position (mm)");
gStyle->SetOptFit(1111);
g8-> GetXaxis() -> SetTitle ("true position (mm)");
g8 -> GetYaxis() -> SetTitleOffset(labelOffsetY);
g8 -> GetYaxis() -> SetTitleSize(labelSizeY);
g8 -> GetXaxis() -> SetTitleOffset(labelOffsetX);
g8 -> GetXaxis() -> SetTitleSize(labelSizeX);
gStyle -> SetOptFit();
TPaveStats *st8 = (TPaveStats*)g8->FindObject("stats");
st8->SetX1NDC(newx1); //new x start position
st8->SetX2NDC(newx2); //new x end position
st8->SetY1NDC(0.85); //new y start position
st8->SetY2NDC(0.95); //new y end posit
c8->Print("posRec_ampl.png");

//**********************************************************************************

TCanvas *c5 = new TCanvas("c5","Mean",200,10,700,500);
c5->SetGrid();
TGraphErrors *g5= new TGraphErrors("hAmplVarS_Mean.dat");
TAxis *axis5 = g5-> GetXaxis();
  gStyle->SetOptStat(0);

TF1 *line5 = new TF1("line5","pol2",-5,5);
line5 -> SetLineColor(2);
g5-> Fit(line5);

g5-> SetMarkerColor(kBlack);
g5-> SetMarkerStyle(21);
g5-> Draw("AP");
g5-> SetTitle("Mean _{#sqrt{A_{1} A_{2}}}-Slow");
g5-> GetYaxis() -> SetTitle ("Mean_{#sqrt{A_{1} A_{2}}}");
gStyle->SetOptFit(1111);
g5-> GetXaxis() -> SetTitle ("position (cm)");
g5 -> GetYaxis() -> SetTitleOffset(labelOffsetY);
g5 -> GetYaxis() -> SetTitleSize(labelSizeY);
g5 -> GetXaxis() -> SetTitleOffset(labelOffsetX);
g5 -> GetXaxis() -> SetTitleSize(labelSizeX);
gStyle -> SetOptFit();
TPaveStats *st5 = (TPaveStats*)g5->FindObject("stats");
st5->SetX1NDC(newx1); //new x start position
st5->SetX2NDC(newx2); //new x end position
st5->SetY1NDC(0.85); //new y start position
st5->SetY2NDC(0.95); //new y end posit
c5->Print("meanVarS.png");

//**********************************************************************************
TCanvas *c6 = new TCanvas("c6","Mean",200,10,700,500);
c6->SetGrid();
TGraphErrors *g6= new TGraphErrors("hAmplVarF_Mean.dat");
TGraphErrors *g6a= new TGraphErrors("hAmplVarF_Mean.dat");
TAxis *axis6 = g6-> GetXaxis();
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(0);
//ajuste de la línea recta

TF1 *line6 = new TF1("line6","pol2",-5,5);
line6 -> SetLineColor(2);
g6-> Fit(line6);

g6-> SetMarkerColor(kBlack);
g6-> SetMarkerStyle(21);
g6-> Draw("AP");
//g6a->Draw("same");
g6-> SetTitle("Mean _{#sqrt{A_{1} A_{2}}}-Fast");
g6-> GetYaxis() -> SetTitle ("Mean_{#sqrt{A_{1} A_{2}}}");
gStyle->SetOptFit(1111);
g6-> GetXaxis() -> SetTitle ("position (cm)");
g6 -> GetYaxis() -> SetTitleOffset(labelOffsetY);
g6 -> GetYaxis() -> SetTitleSize(labelSizeY);
g6 -> GetXaxis() -> SetTitleOffset(labelOffsetX);
g6 -> GetXaxis() -> SetTitleSize(labelSizeX);
gStyle -> SetOptFit();
TPaveStats *st6 = (TPaveStats*)g6->FindObject("stats");
st6->SetX1NDC(newx1); //new x start position
st6->SetX2NDC(newx2); //new x end position
st6->SetY1NDC(0.85); //new y start position
st6->SetY2NDC(0.95); //new y end posit
c6->Print("meanVarF.png");



//**********************************************************************************

TCanvas *c9 = new TCanvas("c9","Mean",200,10,700,500);
c9->SetGrid();
TGraphErrors *g9= new TGraphErrors("meanhDiffAmplVar11.dat");
TGraphErrors *g9a= new TGraphErrors("meanhDiffAmplVar11.dat");
TAxis *axis9 = g9-> GetXaxis();


TF1 *line9 = new TF1("line9","pol5",-5,5);
line9 -> SetLineColor(2);
g9-> Fit(line9);

  gStyle->SetOptStat(0);
  gStyle->SetOptFit(0);
g9-> SetMarkerColor(kBlack);
g9-> SetMarkerStyle(21);
g9-> Draw("AP");
//g9a->Draw("same");
g9-> SetTitle("#frac{A_{1}-A_{2}}{A_{1} + A_{2}}");
g9-> GetYaxis() -> SetTitle ("#mu_{#frac{A_{1}-A_{2}}{A_{1}+A_{2}}}");
g9-> GetXaxis() -> SetTitle ("position (cm)");
g9 -> GetYaxis() -> SetTitleOffset(labelOffsetY);
g9 -> GetYaxis() -> SetTitleSize(labelSizeY);
g9 -> GetXaxis() -> SetTitleOffset(labelOffsetX);
g9 -> GetXaxis() -> SetTitleSize(labelSizeX);
gStyle->SetOptFit(1111);
TPaveStats *st9 = (TPaveStats*)g9->FindObject("stats");
st9->SetX1NDC(newx1); //new x start position
st9->SetX2NDC(newx2); //new x end position
st9->SetY1NDC(0.65); //new y start position
st9->SetY2NDC(0.95); //new y end posit

c9->Print("meanHDiff.png");

//**********************************************************************************

//**********************************************************************************

TCanvas *c12 = new TCanvas("c12","Max0",200,10,700,500);
c12->SetGrid();
TGraphErrors *g12= new TGraphErrors("max0.dat");
TAxis *axis12 = g12-> GetXaxis();
  gStyle->SetOptStat(0);

//ajuste de la línea recta
/*
TF1 *line1 = new TF1("line1","[0]+[1]*x",-8.,8.);
line1 -> SetParNames("#p0","#p1");
line1 -> SetParameters(-0.75,-0.147);
line1 -> SetLineColor(2);
g12-> Fit(line1);
*/
g12-> SetMarkerColor(kBlack);
g12-> SetMarkerStyle(43);
g12-> Draw("AP");
g12-> SetTitle("A_{1}-mean");
g12 -> GetYaxis() -> SetTitleOffset(labelOffsetY);
g12 -> GetYaxis() -> SetTitleSize(labelSizeY);
g12 -> GetXaxis() -> SetTitleOffset(labelOffsetX);
g12 -> GetXaxis() -> SetTitleSize(labelSizeX);
g12 -> GetYaxis() -> SetTitle ("A_{1} (mV)");
gStyle->SetOptFit(1111);
g12-> GetXaxis() -> SetTitle ("position (cm)");
gStyle -> SetOptFit();
c12->Print("A1.png");
//**********************************************************************************

TCanvas *c13 = new TCanvas("c13","Max1",200,10,700,500);
c13->SetGrid();
TGraphErrors *g13= new TGraphErrors("max1.dat");
TAxis *axis13 = g13-> GetXaxis();
  gStyle->SetOptStat(0);

//ajuste de la línea recta
/*
TF1 *line1 = new TF1("line1","[0]+[1]*x",-8.,8.);
line1 -> SetParNames("#p0","#p1");
line1 -> SetParameters(-0.75,-0.147);
line1 -> SetLineColor(2);
g13-> Fit(line1);
*/
g13-> SetMarkerColor(kBlack);
g13-> SetMarkerStyle(43);
g13-> Draw("AP");
g13-> SetTitle("A_{2}-mean");
g13-> GetYaxis() -> SetTitle ("A_{2} (mV)");
gStyle->SetOptFit(1111);
g13-> GetXaxis() -> SetTitle ("position (cm)");
g13 -> GetYaxis() -> SetTitleOffset(labelOffsetY);
g13 -> GetYaxis() -> SetTitleSize(labelSizeY);
g13 -> GetXaxis() -> SetTitleOffset(labelOffsetX);
g13 -> GetXaxis() -> SetTitleSize(labelSizeX);
gStyle -> SetOptFit();
c13->Print("A2.png");
//**********************************************************************************
//**********************************************************************************

TCanvas *c14 = new TCanvas("c14","Max0rms",200,10,700,500);
c14->SetGrid();
TGraphErrors *g14= new TGraphErrors("max0rms.dat");
TAxis *axis14 = g14-> GetXaxis();
  gStyle->SetOptStat(0);

//ajuste de la línea recta
/*
TF1 *line1 = new TF1("line1","[0]+[1]*x",-8.,8.);
line1 -> SetParNames("#p0","#p1");
line1 -> SetParameters(-0.75,-0.147);
line1 -> SetLineColor(2);
g14-> Fit(line1);
*/
g14-> SetMarkerColor(kBlack);
g14-> SetMarkerStyle(43);
g14-> Draw("AP");
g14-> SetTitle("A_{1}-rms");
g14-> GetYaxis() -> SetTitle ("A_{1} (mV)");
gStyle->SetOptFit(1111);
g14-> GetXaxis() -> SetTitle ("position (cm)");
g14 -> GetYaxis() -> SetTitleOffset(labelOffsetY);
g14 -> GetYaxis() -> SetTitleSize(labelSizeY);
g14 -> GetXaxis() -> SetTitleOffset(labelOffsetX);
g14 -> GetXaxis() -> SetTitleSize(labelSizeX);
gStyle -> SetOptFit();
c14->Print("rmsA1.png");
//**********************************************************************************

TCanvas *c15 = new TCanvas("c15","Max1rms",200,10,700,500);
c15->SetGrid();
TGraphErrors *g15= new TGraphErrors("max1rms.dat");
TAxis *axis15 = g15-> GetXaxis();
  gStyle->SetOptStat(0);

//ajuste de la línea recta
/*
TF1 *line1 = new TF1("line1","[0]+[1]*x",-8.,8.);
line1 -> SetParNames("#p0","#p1");
line1 -> SetParameters(-0.75,-0.147);
line1 -> SetLineColor(2);
g15-> Fit(line1);
*/
g15-> SetMarkerColor(kBlack);
g15-> SetMarkerStyle(43);
g15-> Draw("AP");
g15-> SetTitle("A_{2}-rms");
g15-> GetYaxis() -> SetTitle ("A_{2} (mV)");
gStyle->SetOptFit(1111);
g15-> GetXaxis() -> SetTitle ("position (cm)");
g15 -> GetYaxis() -> SetTitleOffset(labelOffsetY);
g15 -> GetYaxis() -> SetTitleSize(labelSizeY);
g15 -> GetXaxis() -> SetTitleOffset(labelOffsetX);
g15 -> GetXaxis() -> SetTitleSize(labelSizeX);
gStyle -> SetOptFit();
c15->Print("rmsA2.png");


//**********************************************************************************
//**********************************************************************************
TCanvas *c16 = new TCanvas("c16","sigmaVar1",200,10,700,500);
c16->SetGrid();
TGraphErrors *g16= new TGraphErrors("hAmplVarF_sigma.dat");
TGraphErrors *g16a= new TGraphErrors("hAmplVarF_sigma.dat");
TAxis *axis16 = g16-> GetXaxis();
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(0);
//ajuste de la línea recta

TF1 *line16 = new TF1("line16","pol2",-8,8);
line16 -> SetLineColor(2);
g16-> Fit(line16);

g16-> SetMarkerColor(kBlack);
g16-> SetMarkerStyle(21);
g16-> Draw("AP");
//g16a->Draw("same");
g16-> SetTitle("#RMS_{#sqrt{A_{1} A_{2}}}-Fast");
g16-> GetYaxis() -> SetTitle ("RMS_{#sqrt{A_{1} A_{2}}} (mV)");
gStyle->SetOptFit(1111);
g16-> GetXaxis() -> SetTitle ("position (cm)");
g16 -> GetYaxis() -> SetTitleOffset(labelOffsetY);
g16 -> GetYaxis() -> SetTitleSize(labelSizeY);
g16 -> GetXaxis() -> SetTitleOffset(labelOffsetX);
g16 -> GetXaxis() -> SetTitleSize(labelSizeX);
gStyle -> SetOptFit();
TPaveStats *st16 = (TPaveStats*)g16->FindObject("stats");
st16->SetX1NDC(newx1); //new x start position
st16->SetX2NDC(newx2); //new x end position
st16->SetY1NDC(0.85); //new y start position
st16->SetY2NDC(0.95); //new y end posit
c16->Print("simgaVarF.png");

//**********************************************************************************
TCanvas *c17 = new TCanvas("c17","sigmaVar2",200,10,700,500);
c17->SetGrid();
TGraphErrors *g17= new TGraphErrors("hAmplVarS_sigma.dat");
TGraphErrors *g17a= new TGraphErrors("hAmplVarS_sigma.dat");
TAxis *axis17 = g17-> GetXaxis();
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(0);
//ajuste de la línea recta

TF1 *line17 = new TF1("line17","pol2",-8,8);
line17 -> SetLineColor(2);
g17-> Fit(line17);

g17-> SetMarkerColor(kBlack);
g17-> SetMarkerStyle(21);
g17-> Draw("AP");
//g17a->Draw("same");
g17-> SetTitle("#RMS_{#sqrt{A_{1} A_{2}}}-Slow");
g17-> GetYaxis() -> SetTitle ("RMS_{#sqrt{A_{1} A_{2}}} (mV)");
gStyle->SetOptFit(1111);
g17-> GetXaxis() -> SetTitle ("position (cm)");
g17 -> GetYaxis() -> SetTitleOffset(labelOffsetY);
g17 -> GetYaxis() -> SetTitleSize(labelSizeY);
g17 -> GetXaxis() -> SetTitleOffset(labelOffsetX);
g17 -> GetXaxis() -> SetTitleSize(labelSizeX);
gStyle -> SetOptFit();
TPaveStats *st17 = (TPaveStats*)g17->FindObject("stats");
st17->SetX1NDC(newx1); //new x start position
st17->SetX2NDC(newx2); //new x end position
st17->SetY1NDC(0.85); //new y start position
st17->SetY2NDC(0.95); //new y end posit
//c17->Print("sigmaVarF.png");


//**********************************************************************************

TCanvas *c18 = new TCanvas("c18","correlation",200,10,700,500);
c18->SetGrid();
TGraph *g18= new TGraph("correlation.dat");
TAxis *axis18 = g18-> GetXaxis();
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(0);
//ajuste de la línea recta

TF1 *line18 = new TF1("line18","pol0",-5,5);
line18 -> SetLineColor(2);
g18-> Fit("line18","R","", -5,5);

g18-> SetMarkerColor(kBlack);
g18-> SetMarkerStyle(21);
g18-> Draw("AP");
//g18a->Draw("same");
g18-> SetTitle("Correlation #Delta_{t} vs log(A_{1}/A_{2}");
g18-> GetYaxis() -> SetTitle ("#rho");
gStyle->SetOptFit(1111);
g18-> GetXaxis() -> SetTitle ("position (cm)");
g18 -> GetYaxis() -> SetTitleOffset(labelOffsetY);
g18 -> GetYaxis() -> SetTitleSize(labelSizeY);
g18 -> GetXaxis() -> SetTitleOffset(labelOffsetX);
g18 -> GetXaxis() -> SetTitleSize(labelSizeX);
gStyle -> SetOptFit();
TPaveStats *st18 = (TPaveStats*)g18->FindObject("stats");
st18->SetX1NDC(newx1); //new x start position
st18->SetX2NDC(newx2); //new x end position
st18->SetY1NDC(0.85); //new y start position
st18->SetY2NDC(0.95); //new y end posit
c18->Print("correlation.png");



//**********************************************************************************

TCanvas *c19 = new TCanvas("c19","positionRec",200,10,700,500);
c19->SetGrid();
TGraphErrors *g19= new TGraphErrors("posRec_time.dat");
TAxis *axis19 = g19-> GetXaxis();
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(0);
//ajuste de la línea recta

TF1 *line19 = new TF1("line19","pol1",-5,5);
line19 -> SetLineColor(2);
g19-> Fit(line19);

g19-> SetMarkerColor(kBlack);
g19-> SetMarkerStyle(21);
g19-> Draw("AP");
//g19a->Draw("same");
g19-> SetTitle("Position reconstruction via time");
g19-> GetYaxis() -> SetTitle ("calculated position (mm)");
gStyle->SetOptFit(1111);
g19-> GetXaxis() -> SetTitle ("true position (mm)");
g19 -> GetYaxis() -> SetTitleOffset(labelOffsetY);
g19 -> GetYaxis() -> SetTitleSize(labelSizeY);
g19 -> GetXaxis() -> SetTitleOffset(labelOffsetX);
g19 -> GetXaxis() -> SetTitleSize(labelSizeX);
gStyle -> SetOptFit();
TPaveStats *st19 = (TPaveStats*)g19->FindObject("stats");
st19->SetX1NDC(newx1); //new x start position
st19->SetX2NDC(newx2); //new x end position
st19->SetY1NDC(0.85); //new y start position
st19->SetY2NDC(0.95); //new y end posit
c19->Print("posRec_time.png");
//**********************************************************************************

TCanvas *c20 = new TCanvas("c20","positionRec",200,10,700,500);
c20->SetGrid();
TGraphErrors *g20= new TGraphErrors("posRec.dat");
TAxis *axis20 = g20-> GetXaxis();
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(0);
//ajuste de la línea recta

TF1 *line20 = new TF1("line20","pol1",-5,5);
line20 -> SetLineColor(2);
g20-> Fit(line20);

g20-> SetMarkerColor(kBlack);
g20-> SetMarkerStyle(21);
g20-> Draw("AP");
//g20a->Draw("same");
g20-> SetTitle("Position reconstruction using time and amplitudes (BLUE)");
g20-> GetYaxis() -> SetTitle ("calculated position (mm)");
gStyle->SetOptFit(1111);
g20-> GetXaxis() -> SetTitle ("true position (mm)");
g20 -> GetYaxis() -> SetTitleOffset(labelOffsetY);
g20 -> GetYaxis() -> SetTitleSize(labelSizeY);
g20 -> GetXaxis() -> SetTitleOffset(labelOffsetX);
g20 -> GetXaxis() -> SetTitleSize(labelSizeX);
gStyle -> SetOptFit();
TPaveStats *st20 = (TPaveStats*)g20->FindObject("stats");
st20->SetX1NDC(newx1); //new x start position
st20->SetX2NDC(newx2); //new x end position
st20->SetY1NDC(0.85); //new y start position
st20->SetY2NDC(0.95); //new y end posit
c20->Print("posRec.png");

}


