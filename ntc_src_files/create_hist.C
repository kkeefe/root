//This program reads the output ntuple root file from the NTuples-improve.cpp.
//It is recomended that execute this program in a new folder, as it will save images of every fit done,
//and data files as well. Run in batch mode to avoid the generation of canvas on the screen:
//$root -b -q create_hist.c

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
#include "TClass.h"
#include <iostream>
#include <string>
#include "TMath.h"
#include <TROOT.h>
#include "TH1F.h"
#include "TF1.h"
#include "TH2F.h"
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

// Converts an int to a string
string int_to_string(int integer)
{
  ostringstream stst;
  stst << integer;
  return stst.str();
}

void create_hist()
{

  //initial declarations:
  //-----------------------------------------------------------------------------

  TObjArray Hlist(0);
  TApplication app("app", 0, 0);

  //---------------------------------------------------------------------------
  TFile *f = new TFile("tempNtuple.root");
  TNtuple *ntuple = (TNtuple *)f->Get("ntuple");
  ULong64_t nentries = (Int_t)ntuple->GetEntries();
  cout << ntuple->GetEntries() << ", the number of entires for this ntuple.. " << endl;

  //---------------------------------------------------------------------------
  //  Setting Branches for the Ntuples
  //---------------------------------------------------------------------------
  Float_t motorPosition, motorPositionAnt, limit;
  ntuple->SetBranchAddress("motorPosition_", &motorPosition);
  Float_t deltaT1_;
  ntuple->SetBranchAddress("deltaT1", &deltaT1_);
  Float_t amplVar1_;
  ntuple->SetBranchAddress("amplVar1", &amplVar1_); //Sqrt for fast output
  Float_t amplVar2_;
  ntuple->SetBranchAddress("amplVar2", &amplVar2_); //Sqrt for standard output
  Float_t logAmplitudes_;
  ntuple->SetBranchAddress("logAmplitudes", &logAmplitudes_);
  Float_t max0_;
  ntuple->SetBranchAddress("max0", &max0_);
  Float_t max1_;
  ntuple->SetBranchAddress("max1", &max1_);
  Float_t max2_;
  ntuple->SetBranchAddress("max2", &max2_);
  Float_t max3_;
  ntuple->SetBranchAddress("max3", &max3_);

  //---------------------------------------------------------------------------
  //  Variable delcarations to be used for analysis..
  //---------------------------------------------------------------------------
  double mean_tmp, sigma_tmp, a_tmp, mean_tmp1, sigma_tmp1, a_tmp1, mean_DeltaT1, sigma_DeltaT1, mean_LogAmpl, sigma_LogAmpl, mean_LogAmplSlow;
  double sigma_LogAmplSlow, mean_hRatio, sigma_hRatio, mean_DeltaT1Error, sigma_DeltaT1Error, mean_LogAmplError, sigma_LogAmplError, mean_LogAmplSlowError;
  double sigma_LogAmplSlowError, mean_hRatioError, sigma_hRatioError;
  double mean, rms, meanError, rmsError, meanS, rmsS, meanErrorS, rmsErrorS;
  double meanMax0, meanErrorMax0, rmsMax0, rmsErrorMax0;
  double meanTimePos, sigmaTimePos, meanAmplPos, sigmaAmplPos, meanAmplPosError, meanPos, sigmaPos, meanPosNum1, meanPosNum2, meanPosDen;
  double meanMax1, meanErrorMax1, rmsMax1, rmsErrorMax1;
  double mean_hdiffAmplVar1, sigma_hdiffAmplVar1, mean_hdiffAmplVar1Error, sigma_hdiffAmplVar1Error;
  std::vector<double> meanT;
  std::vector<double> sigmaT;
  std::vector<double> meanLog;
  std::vector<double> sigmaLog;
  std::vector<double> meanTimePosVec;
  std::vector<double> sigmaTimePosVec;
  std::vector<double> meanAmplPosVec;
  std::vector<double> sigmaAmplPosVec;
  int name;

  //constant values
  const float nIndex = 1.5;                                             //index for EJ-200, EJ204 & EJ-230
  float distance, error_distance, t1Rec, Ttotal, t1RecError, distanceA; // reconstructed
  const float cSpeed = 299792458000.;                                   // speed of light, in mm.s-
  const float longBar = 200;                                            // bar longitude, in mm
  const float atLenght = 1600;                                          //in mm //380 cm for EJ200, 160 cm for EJ204 and 120 cm for EJ230

  //---------------------------------------------------------------------------
  //  Files, where the original filled data will be stored for each histogram..
  //---------------------------------------------------------------------------
  std::fstream outputFile1;
  outputFile1.open("residualsDT.dat", std::ios::out | std::ios::trunc);

  //---------------------------------------------------------------------------
  //  Histograms 1D and 2D, each of these will have their own .dat file..
  //---------------------------------------------------------------------------

  //TH2* h = new TH1I("h1","",31,-13,18);
  //1
  TH1 *hDeltaT1 = new TH1I("hDeltaT1", "#Delta t", 65, -4.0, 5.0);
  hDeltaT1->GetYaxis()->SetTitle("events");
  hDeltaT1->GetXaxis()->SetTitle("#Delta t (ns)");

  //10
  TH1F *hdiffAmplVar1 = new TH1F("hdiffAmplVar1", "#frac{A_{1}-A_{2}}{A_{1}+A_{2}}", 50, -.7, .7);
  hdiffAmplVar1->GetXaxis()->SetTitle("#frac{A_{1}-A_{2}}{A_{1}+A_{2}}");
  hdiffAmplVar1->GetYaxis()->SetTitle("events");

  //5
  TH2F *h1 = new TH2F("h1", "#Delta t (ns) vs log(A_{1} / A_{2})", 300, 20, 100, 65, -4, 5);
  h1->GetYaxis()->SetTitle("#Delta t (ns)");
  h1->GetXaxis()->SetTitle("log(A_{1}/A_{2})");

  //---------------------------------------------------------------------------
  //  Filling histograms
  //---------------------------------------------------------------------------
  Ttotal = 1000000000 * longBar * nIndex / cSpeed; //in ns

  for (ULong64_t j = 0; j < nentries; j++)
  {
    ntuple->GetEntry(j);
    motorPosition = motorPosition + 4000;

    //~~~~~~~~~~~~~Set motor position!!!!!~~~~~~~~~~~~~~~~~~
    if (j == 0)
    {
      motorPositionAnt = motorPosition;
    }

    //Distance reconstructed with time
    t1Rec = (-deltaT1_ + Ttotal) / 2;
    distance = t1Rec * cSpeed / (nIndex * 1000000000) - 100 - 16; // in mm, at the center of the bar
    distance = distance / 2;

    //Distance reconstructed with amplitude
    distanceA = ((longBar - (atLenght * logAmplitudes_)) / 2) - 120; //offset de 70

    name = ((int)motorPositionAnt / 4000) - 10;
    limit = (motorPositionAnt / 4000) - 10;
    if (limit <= 10)
    {
      if (motorPosition == motorPositionAnt)
      {
        hDeltaT1->Fill(deltaT1_);
        h1->Fill(logAmplitudes_, deltaT1_);
        hdiffAmplVar1->Fill((max0_ - max1_) / (max1_ + max0_));
      }

      else
      {
        //------------Filling histograms-------------------

        //***********For DetaT1************************
        TF1 *fGauss_1 = new TF1("fGauss_1", "gaus");
        hDeltaT1->Fit("fGauss_1");
        a_tmp = fGauss_1->GetParameter(0);
        mean_tmp = fGauss_1->GetParameter(1);
        sigma_tmp = fGauss_1->GetParameter(2);

        TF1 *fGauss_2 = new TF1("fGauss_2", "[0]*exp(-pow((x-[1])/[2],2))", mean_tmp - 2 * sigma_tmp, mean_tmp + 2 * sigma_tmp);
        fGauss_2->SetParameters(a_tmp, mean_tmp, sigma_tmp);
        fGauss_2->Update();
        fGauss_2->SetLineColor(7);
        hDeltaT1->Fit("fGauss_2", "R", "", mean_tmp - 2 * sigma_tmp, mean_tmp - 2 * sigma_tmp);
        a_tmp1 = fGauss_2->GetParameter(0);
        mean_tmp1 = fGauss_2->GetParameter(1);
        sigma_tmp1 = fGauss_2->GetParameter(2);

        TF1 *fGauss_3 = new TF1("fGauss_3", "[0]*exp(-pow((x-[1])/[2],2))", mean_tmp - 2 * sigma_tmp, mean_tmp + 2 * sigma_tmp);
        fGauss_3->SetParameters(a_tmp1, mean_tmp1, sigma_tmp1);
        fGauss_3->SetParNames("A", "Mean", "Sigma");
        fGauss_3->SetLineColor(6);
        hDeltaT1->Fit("fGauss_3", "R", "", mean_tmp - 2 * sigma_tmp, mean_tmp - 2 * sigma_tmp);

        mean_DeltaT1 = fGauss_3->GetParameter(1);
        sigma_DeltaT1 = fGauss_3->GetParameter(2);
        mean_DeltaT1Error = fGauss_3->GetParError(1);
        sigma_DeltaT1Error = fGauss_3->GetParError(2);

        //*******************************************
        mean = hAmplVar1_->GetMean();
        meanError = hAmplVar1_->GetMeanError();
        rms = hAmplVar1_->GetRMS();
        rmsError = hAmplVar1_->GetRMSError();

        meanS = hAmplVar2_->GetMean();
        meanErrorS = hAmplVar2_->GetMeanError();
        rmsS = hAmplVar2_->GetRMS();
        rmsErrorS = hAmplVar2_->GetRMSError();

        //***********For hdiffAmplVar1 ************************
        TF1 *fGauss_4 = new TF1("fGauss_4", "gaus");
        hdiffAmplVar1->Fit("fGauss_4");
        a_tmp = fGauss_4->GetParameter(0);
        mean_tmp = fGauss_4->GetParameter(1);
        sigma_tmp = fGauss_4->GetParameter(2);

        TF1 *fGauss_24 = new TF1("fGauss_24", "[0]*exp(-pow((x-[1])/[2],2))", mean_tmp - sigma_tmp, mean_tmp + sigma_tmp);
        fGauss_24->SetParameters(a_tmp, mean_tmp, sigma_tmp);
        fGauss_24->Update();
        hdiffAmplVar1->Fit("fGauss_24", "R", "", mean_tmp - sigma_tmp, mean_tmp - sigma_tmp);
        a_tmp1 = fGauss_24->GetParameter(0);
        mean_tmp1 = fGauss_24->GetParameter(1);
        sigma_tmp1 = fGauss_24->GetParameter(2);

        TF1 *fGauss_34 = new TF1("fGauss_34", "[0]*exp(-pow((x-[1])/[2],2))", mean_tmp1 - sigma_tmp1, mean_tmp1 + sigma_tmp1);
        fGauss_34->SetParameters(a_tmp1, mean_tmp1, sigma_tmp1);
        fGauss_34->SetParNames("A", "Mean", "Sigma");
        fGauss_34->SetLineColor(6);
        hdiffAmplVar1->Fit("fGauss_34", "R", "", mean_tmp1 - sigma_tmp1, mean_tmp1 - sigma_tmp1);

        //changed for new function! ponting to fGauss_24, not fGauss_34:
        mean_hdiffAmplVar1 = fGauss_24->GetParameter(1);
        sigma_hdiffAmplVar1 = fGauss_24->GetParameter(2);
        mean_hdiffAmplVar1Error = fGauss_24->GetParError(1);
        sigma_hdiffAmplVar1Error = fGauss_24->GetParError(2);

        //**********************Amplitudes******************
        meanMax0 = hmax0->GetMean();
        meanErrorMax0 = hmax0->GetMeanError();
        rmsMax0 = hmax0->GetRMS();
        rmsErrorMax0 = hmax0->GetRMSError();

        meanMax1 = hmax1->GetMean();
        meanErrorMax1 = hmax1->GetMeanError();
        rmsMax1 = hmax1->GetRMS();
        rmsErrorMax1 = hmax1->GetRMSError();

        //******************************************************
        TCanvas *c2 = new TCanvas("c2", "hDeltaT1", 1000, 600);
        c2->Divide(1, 1);
        c2->cd(1);
        //gPad->SetLogy();
        // gStyle->SetOptStat(0);
        gStyle->SetOptFit(1111);
        hDeltaT1->Draw();
        c2->Print(("plots/hDeltaT1_" + int_to_string((int)motorPositionAnt) + ".png").c_str());
        //c2->SaveAs("hDeltaT1_.pdf");
        c2->cd();

        //******************************************************
        TCanvas *c4 = new TCanvas("c4", "hAmplVar1_", 1000, 600);
        c4->Divide(1, 1);
        c4->cd(1);
        // gPad->SetLogy();
        //  gStyle->SetOptStat(0);
        gStyle->SetOptFit(1111);
        hAmplVar1_->Draw();
        c4->Print(("plots/hAmplVar1_" + int_to_string((int)motorPositionAnt) + ".png").c_str());
        //c4->SaveAs("hAmplVar1_.pdf");
        c4->cd();

        //******************************************************
        hDeltaT1->Reset("ICESM");
        hAmplVar1_->Reset("ICESM");
        h1->Reset("ICESM");
        hdiffAmplVar1->Reset("ICESM");
      }
      motorPositionAnt = motorPosition;
    }
  }
}
