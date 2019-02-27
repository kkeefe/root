//---------------------------------------------------------------------------
#include "TClass.h"
#include <iostream>
#include <string>
#include "TMath.h"
#include <TROOT.h>
#include "TH1F.h"
#include "TF1.h"
#include "TTree.h"
#include "TFile.h"
#include "TChain.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TGraph.h"
#include "TApplication.h"
#include "TPaveLabel.h"
#include "TPaveText.h"
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <iomanip>
#include <sstream>
#include "TPaveLabel.h"
#include "TPaveText.h"
#include "Riostream.h"
#include "TNtuple.h"

using namespace std;

void triple_fit (TH1* hist_1) {

  double g1_temp_par1, g1_temp_par2, g1_temp_par3;
  double g2_temp_par1, g2_temp_par2, g2_temp_par3;
  double mean, sigma, mean_Error, sigma_Error;  
  
  TF1 *fGauss_1 = new TF1("fGauss_1","gaus");
  hist_1->Fit("fGauss_1");
  g1_temp_par1 = fGauss_1->GetParameter(0);
  g1_temp_par2 = fGauss_1->GetParameter(1);
  g1_temp_par3 = fGauss_1->GetParameter(2);

  TF1 *fGauss_2 = new TF1("fGauss_2","[0]*exp(-pow((x-[1])/[2],2))",g1_temp_par2-2*g1_temp_par3,g1_temp_par2+2*g1_temp_par3);
  fGauss_2 -> SetParameters(a_tmp,mean_tmp,sigma_tmp);
  fGauss_2 -> Update();
  fGauss_2 -> SetLineColor(7);
  hist_1->Fit("fGauss_2","R","",mean_tmp-2*sigma_tmp,mean_tmp-2*sigma_tmp);
  g2_temp_par1 = fGauss_2->GetParameter(0);
  g2_temp_par2 = fGauss_2->GetParameter(1);
  g2_temp_par3 = fGauss_2->GetParameter(2);

  
  TF1 *fGauss_3 = new TF1("fGauss_3","[0]*exp(-pow((x-[1])/[2],2))",g1_temp_par2-2*g1_temp_par3,g1_temp_par2+2*g1_temp_par3);
  fGauss_3 -> SetParameters(a_tmp1,mean_tmp1,sigma_tmp1);
  fGauss_3 -> SetParNames("A","Mean","Sigma");
  fGauss_3 -> SetLineColor(6);
  hist_1 -> Fit("fGauss_3","R","",mean_tmp-2*sigma_tmp,mean_tmp-2*sigma_tmp);

  
  mean = fGauss_3->GetParameter(1);
  sigma = fGauss_3->GetParameter(2);
  mean_Error = fGauss_3->GetParError(1);
  sigma_Error = fGauss_3->GetParError(2);

  TCanvas *c1 = new TCanvas ("c1","hist_1",1000,600);
  c1->Divide(1,1);
  c1->cd(1);
  // gPad->SetLogy();
  // gStyle->SetOptStat(0);
  gStyle->SetOptFit(1111);
  hist_1->Draw();
  c1 ->Print(("plots/hist_1_"+int_to_string((int) motorPositionAnt)+".png").c_str());
  //c1->SaveAs("hist_1_.pdf");
  c1->cd();

  hist_1 -> Reset("ICESM");

}
