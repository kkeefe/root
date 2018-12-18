//This program reads the output ntuple root file from the NTuples-improve.cpp.
//It is recomended that execute this program un a new folder, as it will save images of every fit done,
//and data files as well. Run in batch mode to avoid the generation of canvas on the screen:
//$root -b -q HDAuto.c

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
string int_to_string(int integer) {
  ostringstream stst;
  stst << integer;
  return stst.str();
}

void HDAuto() {

//-----------------------------------------------------------------------------
 
  TObjArray Hlist(0);
  TApplication app("app",0,0);


  //---------------------------------------------------------------------------
    TFile *f =  new TFile("tempNtuple.root");


    TNtuple *ntuple = (TNtuple*)f->Get("ntuple");
    ULong64_t nentries = (Int_t)ntuple->GetEntries();

  cout<<ntuple->GetEntries()<<endl;

  //---------------------------------------------------------------------------
  //  Setting Branches and variables
  //---------------------------------------------------------------------------
    Float_t motorPosition, motorPositionAnt, limit;
    ntuple->SetBranchAddress("motorPosition_", &motorPosition);
    Float_t deltaT1_;
    ntuple->SetBranchAddress("deltaT1", &deltaT1_);
    Float_t amplVar1_;
    ntuple->SetBranchAddress("amplVar1", &amplVar1_);//Sqrt for fast output
    Float_t amplVar2_;
    ntuple->SetBranchAddress("amplVar2", &amplVar2_);//Sqrt for standard output
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
    double mean_tmp, sigma_tmp, a_tmp, mean_tmp1, sigma_tmp1, a_tmp1, mean_DeltaT1, sigma_DeltaT1, mean_LogAmpl, sigma_LogAmpl,mean_LogAmplSlow;
    double sigma_LogAmplSlow, mean_hRatio, sigma_hRatio, mean_DeltaT1Error, sigma_DeltaT1Error, mean_LogAmplError, sigma_LogAmplError, mean_LogAmplSlowError;
    double sigma_LogAmplSlowError, mean_hRatioError, sigma_hRatioError;
    double mean, rms, meanError, rmsError,meanS, rmsS, meanErrorS, rmsErrorS;
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
    const float nIndex = 1.5; //index for EJ-200, EJ204 & EJ-230
    float distance, error_distance, t1Rec, Ttotal, t1RecError, distanceA; // reconstructed
    const float cSpeed = 299792458000.; // speed of light, in mm.s-
    const float longBar= 200; // bar longitude, in mm
    const float atLenght=1600;//in mm //380 cm for EJ200, 160 cm for EJ204 and 120 cm for EJ230




 //---------------------------------------------------------------------------
 //  Files
 //---------------------------------------------------------------------------

    std::fstream outputFile1;
    std::fstream outputFile2;
    std::fstream outputFile3;
    std::fstream outputFile4;
    std::fstream outputFile5;
    std::fstream outputFile6;
    std::fstream outputFile7;
    std::fstream outputFile8;
    std::fstream outputFile9;
    std::fstream outputFile10;
    std::fstream outputFile11;
    std::fstream outputFile12;
    std::fstream outputFile13;
    std::fstream outputFile14;
    std::fstream outputFile15;
    std::fstream outputFile16;
    std::fstream outputFile17;
    //std::fstream outputFile18;
    std::fstream outputFile19;
    std::fstream outputFile20;
    std::fstream outputFile21;
    std::fstream outputFile22;
    std::fstream outputFile23;
    std::fstream outputFile24;
    //std::fstream outputFile25;
    std::fstream outputFile26;
    outputFile1.open("residualsDT.dat",std::ios::out | std::ios::trunc);
    outputFile2.open("sigma_DeltaT1.dat",std::ios::out | std::ios::trunc);
    outputFile3.open("posRec_time.dat",std::ios::out | std::ios::trunc);
    outputFile4.open("posRec_ampl.dat",std::ios::out | std::ios::trunc);
    outputFile5.open("mean_LogAmplSlowError.dat",std::ios::out | std::ios::trunc);
    outputFile6.open("sigma_LogAmplSlowError.dat",std::ios::out | std::ios::trunc);
    outputFile7.open("posRec_ampl.dat",std::ios::out | std::ios::trunc);
    outputFile8.open("hAmplVarF_Mean.dat",std::ios::out | std::ios::trunc);
    outputFile9.open("hAmplVarF_sigma.dat",std::ios::out | std::ios::trunc);
    outputFile10.open("hAmplVarS_Mean.dat",std::ios::out | std::ios::trunc);
    outputFile11.open("mean_DeltaT11.dat",std::ios::out | std::ios::trunc);
    outputFile12.open("sigma_hLogAmpl1.dat",std::ios::out | std::ios::trunc);
    outputFile13.open("mean_hLogAmpl1.dat",std::ios::out | std::ios::trunc);
    outputFile14.open("mean_hRatioError1.dat",std::ios::out | std::ios::trunc);
    outputFile15.open("correlation.dat",std::ios::out | std::ios::trunc);
    outputFile16.open("posRec.dat",std::ios::out | std::ios::trunc);
    outputFile17.open("meanhDiffAmplVar11.dat",std::ios::out | std::ios::trunc);
    //outputFile18.open("sigmaHdiffAmplVar1.dat",std::ios::out | std::ios::trunc);
    outputFile19.open("sigmaHdiffAmplVar11.dat",std::ios::out | std::ios::trunc);
    outputFile20.open("max0.dat",std::ios::out | std::ios::trunc);
    outputFile21.open("max1.dat",std::ios::out | std::ios::trunc);
    outputFile22.open("max0rms.dat",std::ios::out | std::ios::trunc);
    outputFile23.open("max1rms.dat",std::ios::out | std::ios::trunc);
    outputFile24.open("hAmplVarS_sigma.dat",std::ios::out | std::ios::trunc);
    //outputFile25.open("sigma_hRatioError.dat",std::ios::out | std::ios::trunc);
    outputFile26.open("sigma_hRatioError1.dat",std::ios::out | std::ios::trunc);


 //---------------------------------------------------------------------------
 //  Histograms 1D and 2D
 //---------------------------------------------------------------------------



    //TH2* h = new TH1I("h1","",31,-13,18);
    TH1* hDeltaT1 = new TH1I("hDeltaT1","#Delta t",65,-4.0,5.0);
    hDeltaT1->GetYaxis()->SetTitle("events");
    hDeltaT1->GetXaxis()->SetTitle("#Delta t (ns)");

    TH1* hAmplVar1_ = new TH1I("hAmplVar1","#sqrt{A_{1} A_{2}}-Fast output",50,20,100);
    hAmplVar1_->GetYaxis()->SetTitle("events");
    hAmplVar1_->GetXaxis()->SetTitle("#sqrt{A_{1} A_{2}} (mV)");

    TH1* hAmplVar2_ = new TH1I("hAmplVar2","#sqrt{A_{1} A_{2}}-Standard output",50,20,100);
    hAmplVar2_->GetYaxis()->SetTitle("events");
    hAmplVar2_->GetXaxis()->SetTitle("#sqrt{A_{1} A_{2}} (mV)");

    TH1* hLogAmpl = new TH1I("hLogAmpl","log(A_{2}/A_{1})",50,-1,1);
    hLogAmpl->GetYaxis()->SetTitle("events");
    hLogAmpl->GetXaxis()->SetTitle("log(A_{2}/A_{1}) (mV)");

    TH2F *h1 = new TH2F("h1","#Delta t (ns) vs log(A_{1} / A_{2})",300,20,100,65,-4,5);
    h1->GetYaxis()->SetTitle("#Delta t (ns)");
    h1->GetXaxis()->SetTitle("log(A_{1}/A_{2})");

    TH1* hRatio = new TH1I("hRatio","Amplitude ratio",50,0,3.5);
    hRatio->GetYaxis()->SetTitle("events");
    hRatio->GetXaxis()->SetTitle("Amplitude ratio A_{2}/A_{1} (mV)");

    TH1* hLogAmplSlow = new TH1I("hLogAmplSlow","log(A_{2}/A_{1})-slow",50,-2,2);
    hLogAmplSlow->GetYaxis()->SetTitle("events");
    hLogAmplSlow->GetXaxis()->SetTitle("log(A_{2}/A_{1}) (mV)");


    TH2F *h2 = new TH2F("h2","#Delta t (ns) vs A_{2}/A_{1}",50,0,3.5,65,-4,5);
    h2->GetYaxis()->SetTitle("#Delta t (ns)");
    h2->GetXaxis()->SetTitle("A_{2}/A_{1}(mV)");

    TH2F *htmp1 = new TH2F("htmp1","#Delta t (ns) vs log(A_{1}/A_{2})",100,-1,1,65,-2,2);
    htmp1->GetXaxis()->SetTitle("#Delta t (ns)");
    htmp1->GetYaxis()->SetTitle("log(A_{1}/A_{2})");

    TH1F *hdiffAmplVar1 = new TH1F("hdiffAmplVar1","#frac{A_{1}-A_{2}}{A_{1}+A_{2}}",50,-.7,.7);
    hdiffAmplVar1->GetXaxis()->SetTitle("#frac{A_{1}-A_{2}}{A_{1}+A_{2}}");
    hdiffAmplVar1->GetYaxis()->SetTitle("events");


    TH1* hmax0 = new TH1I("hmax0","#sqrt{A_{1} A_{2}}-Fast output",150,20,100);
    hmax0->GetYaxis()->SetTitle("events");
    hmax0->GetXaxis()->SetTitle("#sqrt{A_{1} A_{2}} (mV)");

    TH1* hmax1 = new TH1I("hmax1","#sqrt{A_{1} A_{2}}-Fast output",150,20,100);
    hmax1->GetYaxis()->SetTitle("events");
    hmax1->GetXaxis()->SetTitle("#sqrt{A_{1} A_{2}} (mV)");


    TH1 *hpos = new TH1I("hpos","position reconstruction via time",150,-200,200);
    hpos->GetYaxis()->SetTitle("events");
    hpos->GetXaxis()->SetTitle("reconstructed position (mm)");
    hpos->GetYaxis()->SetTitle("counts");


    TH1 *hposA = new TH1I("hpos","position reconstruction via amplitude",150,-400,400);
    hposA->GetYaxis()->SetTitle("events");
    hposA->GetXaxis()->SetTitle("reconstructed position (mm)");
    hposA->GetYaxis()->SetTitle("counts");



 //---------------------------------------------------------------------------
 //  Filling histograms
 //---------------------------------------------------------------------------
    Ttotal  = 1000000000*longBar*nIndex/cSpeed;//in ns

   // t1RecError = (mean_DeltaT1Error+Ttotal)/2;
   // error_distance =  t1RecError * cSpeed /(3*nIndex *1000000000); // in mm


    for (ULong64_t j = 0 ; j < nentries ; j++){
        ntuple->GetEntry(j);

        motorPosition=motorPosition+4000;

 //~~~~~~~~~~~~~Set motor position!!!!!~~~~~~~~~~~~~~~~~~

        if (j==0){motorPositionAnt=motorPosition;}

        //Distance reconstructed with time
        t1Rec = (-deltaT1_+Ttotal)/2;
        distance = t1Rec * cSpeed /(nIndex *1000000000)-100 -16; // in mm, at the center of the bar
        distance = distance /2;

        //Distance reconstructed with amplitude
        distanceA=((longBar-(atLenght*logAmplitudes_))/2)-120; //offset de 70

        name = ((int) motorPositionAnt/4000)-10;
        limit = (motorPositionAnt/4000)-10;
        if (limit<=10){
        if (motorPosition==motorPositionAnt){


            hpos->Fill(distance);
            hposA->Fill(distanceA*.43);//offset of
            hLogAmpl->Fill(logAmplitudes_);
            hDeltaT1->Fill(deltaT1_);
            h1->Fill(logAmplitudes_,deltaT1_);
            hAmplVar1_->Fill(amplVar1_);
            hAmplVar2_->Fill(amplVar2_);
            hRatio->Fill(max0_/max1_);
            hLogAmplSlow->Fill(TMath::Log(max2_/max3_));
            h2->Fill(max0_/max1_,deltaT1_);
            hdiffAmplVar1->Fill((max0_-max1_)/(max1_+max0_));
            hmax0->Fill(max0_);
            hmax1->Fill(max1_);


        }

        else{


//------------Filling histograms-------------------

//***********For DetaT1************************
TF1 *fGauss_1 = new TF1("fGauss_1","gaus");
hDeltaT1->Fit("fGauss_1");
a_tmp = fGauss_1->GetParameter(0);
mean_tmp = fGauss_1->GetParameter(1);
sigma_tmp = fGauss_1->GetParameter(2);

TF1 *fGauss_2 = new TF1("fGauss_2","[0]*exp(-pow((x-[1])/[2],2))",mean_tmp-2*sigma_tmp,mean_tmp+2*sigma_tmp);
fGauss_2 -> SetParameters(a_tmp,mean_tmp,sigma_tmp);
fGauss_2 -> Update();
fGauss_2 -> SetLineColor(7);
hDeltaT1->Fit("fGauss_2","R","",mean_tmp-2*sigma_tmp,mean_tmp-2*sigma_tmp);
a_tmp1 = fGauss_2->GetParameter(0);
mean_tmp1 = fGauss_2->GetParameter(1);
sigma_tmp1 = fGauss_2->GetParameter(2);

TF1 *fGauss_3 = new TF1("fGauss_3","[0]*exp(-pow((x-[1])/[2],2))",mean_tmp-2*sigma_tmp,mean_tmp+2*sigma_tmp);
fGauss_3 -> SetParameters(a_tmp1,mean_tmp1,sigma_tmp1);
fGauss_3 -> SetParNames("A","Mean","Sigma");
fGauss_3 -> SetLineColor(6);
hDeltaT1 -> Fit("fGauss_3","R","",mean_tmp-2*sigma_tmp,mean_tmp-2*sigma_tmp);

mean_DeltaT1 = fGauss_3->GetParameter(1);
sigma_DeltaT1 = fGauss_3->GetParameter(2);
mean_DeltaT1Error = fGauss_3->GetParError(1);
sigma_DeltaT1Error = fGauss_3->GetParError(2);
//cout <<setprecision(4) << fixed;




//outputFile1<<(motorPositionAnt/4000)-10<<" "<<distance<<" "<<"0"<<" "<<error_distance<<endl;

if ((motorPositionAnt>19000)&&(motorPositionAnt<61000)){outputFile11<<(motorPositionAnt/400)-100<<" "<<mean_DeltaT1<<" "<<"0"<<" "<<mean_DeltaT1Error<<endl;}
if ((motorPositionAnt>19000)&&(motorPositionAnt<61000)){outputFile2<<(motorPositionAnt/400)-100<<" "<<sigma_DeltaT1<<" "<<"0"<<" "<<sigma_DeltaT1Error<<endl;}
meanT.push_back(mean_DeltaT1);
sigmaT.push_back(sigma_DeltaT1);


//***********For reconstruction using time************************
TF1 *fGauss_d1 = new TF1("fGauss_d1","gaus");
hpos->Fit("fGauss_d1");
a_tmp = fGauss_d1->GetParameter(0);
mean_tmp = fGauss_d1->GetParameter(1);
sigma_tmp = fGauss_d1->GetParameter(2);

TF1 *fGauss_d2 = new TF1("fGauss_d2","gaus");
fGauss_d2 -> SetParameters(a_tmp,mean_tmp,sigma_tmp);
fGauss_d2 -> Update();
fGauss_d2 -> SetLineColor(7);
hpos->Fit("fGauss_d2");
a_tmp1 = fGauss_d2->GetParameter(0);
mean_tmp1 = fGauss_d2->GetParameter(1);
sigma_tmp1 = fGauss_d2->GetParameter(2);

TF1 *fGauss_d3 = new TF1("fGauss_d3","gaus");
fGauss_d3 -> SetParameters(a_tmp1,mean_tmp1,sigma_tmp1);
fGauss_d3 -> SetParNames("A","Mean","Sigma");
fGauss_d3 -> SetLineColor(6);
hpos -> Fit("fGauss_d3");

meanTimePos = fGauss_d3->GetParameter(1);
sigmaTimePos = fGauss_d3->GetParameter(2);
//mean_DeltaT1Error = fGauss_3->GetParError(1);
//sigma_DeltaT1Error = fGauss_3->GetParError(2);
meanTimePosVec.push_back(meanTimePos);
sigmaTimePosVec.push_back(sigmaTimePos);

if ((motorPositionAnt>19000)&&(motorPositionAnt<61000)){outputFile3<<(motorPositionAnt/400)-100<<" "<<meanTimePos<<" "<<"0"<<" "<<sigmaTimePos<<endl;}
//if ((motorPositionAnt>19000)&&(motorPositionAnt<61000)){outputFile4<<(motorPositionAnt/4000)-10<<" "<<sigma_DeltaT1<<" "<<"0"<<" "<<sigma_DeltaT1Error<<endl;}

//*******************************************
//***********For reconstruction using amplitude************************
TF1 *fGauss_a1 = new TF1("fGauss_a1","gaus");
hposA->Fit("fGauss_a1");
a_tmp = fGauss_a1->GetParameter(0);
mean_tmp = fGauss_a1->GetParameter(1);
sigma_tmp = fGauss_a1->GetParameter(2);

TF1 *fGauss_a2 = new TF1("fGauss_a2","gaus");
fGauss_a2 -> SetParameters(a_tmp,mean_tmp,sigma_tmp);
fGauss_a2 -> Update();
fGauss_a2 -> SetLineColor(7);
hposA->Fit("fGauss_a2");
a_tmp1 = fGauss_a2->GetParameter(0);
mean_tmp1 = fGauss_a2->GetParameter(1);
sigma_tmp1 = fGauss_a2->GetParameter(2);

TF1 *fGauss_a3 = new TF1("fGauss_a3","gaus");
fGauss_a3 -> SetParameters(a_tmp1,mean_tmp1,sigma_tmp1);
fGauss_a3 -> SetParNames("A","Mean","Sigma");
fGauss_a3 -> SetLineColor(6);
hposA -> Fit("fGauss_a3");

meanAmplPos = fGauss_a3->GetParameter(1);
sigmaAmplPos = fGauss_a3->GetParameter(2);
meanAmplPosError = fGauss_a3->GetParError(1);
//sigmaAmplPosError = fGauss_a3->GetParError(2);
meanAmplPosVec.push_back(meanAmplPos);
sigmaAmplPosVec.push_back(sigmaAmplPos);

if ((motorPositionAnt>19000)&&(motorPositionAnt<61000)){outputFile7<<(motorPositionAnt/400)-100<<" "<<meanAmplPos<<" "<<"0"<<" "<<sigmaAmplPos<<endl;}
//if ((motorPositionAnt>19000)&&(motorPositionAnt<61000)){outputFile4<<(motorPositionAnt/4000)-10<<" "<<sigma_DeltaT1<<" "<<"0"<<" "<<sigma_DeltaT1Error<<endl;}

//*******************************************
//***********For hLogAmpl************************
TF1 *fGauss_11 = new TF1("fGauss_11","gaus");
hLogAmpl->Fit("fGauss_11");
a_tmp = fGauss_11->GetParameter(0);
mean_tmp = fGauss_11->GetParameter(1);
sigma_tmp = fGauss_11->GetParameter(2);

TF1 *fGauss_21 = new TF1("fGauss_21","gaus");
fGauss_21 -> SetParameters(a_tmp,mean_tmp,sigma_tmp);
fGauss_21 -> Update();
hLogAmpl->Fit("fGauss_21");
a_tmp1 = fGauss_21->GetParameter(0);
mean_tmp1 = fGauss_21->GetParameter(1);
sigma_tmp1 = fGauss_21->GetParameter(2);

TF1 *fGauss_31 = new TF1("fGauss_31","gaus");
fGauss_31 -> SetParameters(a_tmp1,mean_tmp1,sigma_tmp1);
fGauss_31 -> SetParNames("A","Mean","Sigma");
fGauss_31 -> SetLineColor(6);
hLogAmpl -> Fit("fGauss_31");
mean_LogAmpl = fGauss_31->GetParameter(1);
sigma_LogAmpl = fGauss_31->GetParameter(2);
mean_LogAmplError = fGauss_31->GetParError(1);
sigma_LogAmplError = fGauss_31->GetParError(2);

meanLog.push_back(mean_LogAmpl);
sigmaLog.push_back(sigma_LogAmpl);

//outputFile3<<(motorPositionAnt/4000)-10<<" "<<mean_LogAmpl<<" "<<"0"<<" "<<mean_LogAmplError<<endl;
if ((motorPositionAnt>19000)&&(motorPositionAnt<61000)){outputFile13<<(motorPositionAnt/400)-100<<" "<<mean_LogAmpl<<" "<<"0"<<" "<<mean_LogAmplError<<endl;}
//outputFile4<<(motorPositionAnt/4000)-10<<" "<<sigma_LogAmpl<<" "<<"0"<<" "<<sigma_LogAmplError<<endl;
if ((motorPositionAnt>19000)&&(motorPositionAnt<61000)){outputFile12<<(motorPositionAnt/400)-100<<" "<<sigma_LogAmpl<<" "<<"0"<<" "<<sigma_LogAmplError<<endl;}


//*******************************************
//***********For hLogAmplSlow************************
TF1 *fGauss_12 = new TF1("fGauss_12","gaus");
hLogAmplSlow->Fit("fGauss_12");
a_tmp = fGauss_12->GetParameter(0);
mean_tmp = fGauss_12->GetParameter(1);
sigma_tmp = fGauss_12->GetParameter(2);

TF1 *fGauss_22 = new TF1("fGauss_22","[0]*exp(-pow((x-[1])/[2],2))",mean_tmp-sigma_tmp,mean_tmp+sigma_tmp);
fGauss_22 -> SetParameters(a_tmp,mean_tmp,sigma_tmp);
fGauss_22 -> Update();
hLogAmplSlow->Fit("fGauss_22","R","",mean_tmp-sigma_tmp,mean_tmp-sigma_tmp);
a_tmp1 = fGauss_22->GetParameter(0);
mean_tmp1 = fGauss_22->GetParameter(1);
sigma_tmp1 = fGauss_22->GetParameter(2);

TF1 *fGauss_32 = new TF1("fGauss_32","[0]*exp(-pow((x-[1])/[2],2))",mean_tmp1-sigma_tmp1,mean_tmp1+sigma_tmp1);
fGauss_32 -> SetParameters(a_tmp1,mean_tmp1,sigma_tmp1);
fGauss_32 -> SetParNames("A","Mean","Sigma");
fGauss_32 -> SetLineColor(6);
hLogAmplSlow -> Fit("fGauss_32","R","",mean_tmp1-sigma_tmp1,mean_tmp1-sigma_tmp1);
mean_LogAmplSlow = fGauss_32->GetParameter(1);
sigma_LogAmplSlow = fGauss_32->GetParameter(2);
mean_LogAmplSlowError = fGauss_32->GetParError(1);
sigma_LogAmplSlowError = fGauss_32->GetParError(2);


outputFile5<<(motorPositionAnt/4000)-10<<" "<<mean_LogAmplSlow<<" "<<"0"<<" "<<mean_LogAmplSlowError<<endl;
outputFile6<<(motorPositionAnt/4000)-10<<" "<<sigma_LogAmplSlow<<" "<<"0"<<" "<<sigma_LogAmplSlowError<<endl;
//*******************************************
//***********hRatio************************
TF1 *fGauss_13 = new TF1("fGauss_13","gaus");
hRatio->Fit("fGauss_13");
a_tmp = fGauss_13->GetParameter(0);
mean_tmp = fGauss_13->GetParameter(1);
sigma_tmp = fGauss_13->GetParameter(2);

TF1 *fGauss_23 = new TF1("fGauss_23","[0]*exp(-pow((x-[1])/[2],2))",mean_tmp-sigma_tmp,mean_tmp+sigma_tmp);
fGauss_23 -> SetParameters(a_tmp,mean_tmp,sigma_tmp);
fGauss_23 -> Update();
hRatio->Fit("fGauss_23","R","",mean_tmp-sigma_tmp,mean_tmp-sigma_tmp);
a_tmp1 = fGauss_23->GetParameter(0);
mean_tmp1 = fGauss_23->GetParameter(1);
sigma_tmp1 = fGauss_23->GetParameter(2);

TF1 *fGauss_33 = new TF1("fGauss_33","[0]*exp(-pow((x-[1])/[2],2))",mean_tmp1-sigma_tmp1,mean_tmp1+sigma_tmp1);
fGauss_33 -> SetParameters(a_tmp1,mean_tmp1,sigma_tmp1);
fGauss_33 -> SetParNames("A","Mean","Sigma");
fGauss_33 -> SetLineColor(6);
hRatio -> Fit("fGauss_33","R","",mean_tmp1-sigma_tmp1,mean_tmp1-sigma_tmp1);
mean_hRatio = fGauss_33->GetParameter(1);
sigma_hRatio = fGauss_33->GetParameter(2);
mean_hRatioError = fGauss_33->GetParError(1);
sigma_hRatioError = fGauss_33->GetParError(2);

//outputFile7<<(motorPositionAnt/4000)-10<<" "<<mean_hRatio<<" "<<"0"<<" "<<mean_hRatioError<<endl;
if ((motorPositionAnt>19000)&&(motorPositionAnt<61000)){outputFile14<<(motorPositionAnt/4000)-10<<" "<<mean_hRatio<<" "<<"0"<<" "<<mean_hRatioError<<endl;}
//outputFile25<<(motorPositionAnt/4000)-10<<" "<<sigma_hRatio<<" "<<"0"<<" "<<sigma_hRatioError<<endl;
if ((motorPositionAnt>19000)&&(motorPositionAnt<61000)){outputFile26<<(motorPositionAnt/4000)-10<<" "<<sigma_hRatio<<" "<<"0"<<" "<<sigma_hRatioError<<endl;}
//
//
//*******************************************
//*******************************************
mean = hAmplVar1_->GetMean();
meanError = hAmplVar1_->GetMeanError();
rms = hAmplVar1_->GetRMS();
rmsError = hAmplVar1_->GetRMSError();

meanS = hAmplVar2_->GetMean();
meanErrorS = hAmplVar2_->GetMeanError();
rmsS = hAmplVar2_->GetRMS();
rmsErrorS = hAmplVar2_->GetRMSError();

//outputFile9<<(motorPositionAnt/4000)-10<<" "<<mean<<" "<<"0"<<" "<<rms<<endl;
if ((motorPositionAnt>19000)&&(motorPositionAnt<61000)){outputFile8<<(motorPositionAnt/4000)-10<<" "<<mean<<" "<<"0"<<" "<<meanError<<endl;}
if ((motorPositionAnt>19000)&&(motorPositionAnt<61000)){outputFile9<<(motorPositionAnt/4000)-10<<" "<<rms<<" "<<"0"<<" "<<rmsError<<endl;}

if ((motorPositionAnt>19000)&&(motorPositionAnt<61000)){outputFile10<<(motorPositionAnt/4000)-10<<" "<<meanS<<" "<<"0"<<" "<<meanErrorS<<endl;}
if ((motorPositionAnt>19000)&&(motorPositionAnt<61000)){outputFile24<<(motorPositionAnt/4000)-10<<" "<<rmsS<<" "<<"0"<<" "<<rmsErrorS<<endl;}

//***********For ************************
TF1 *fGauss_4 = new TF1("fGauss_4","gaus");
hdiffAmplVar1->Fit("fGauss_4");
a_tmp = fGauss_4->GetParameter(0);
mean_tmp = fGauss_4->GetParameter(1);
sigma_tmp = fGauss_4->GetParameter(2);

TF1 *fGauss_24 = new TF1("fGauss_24","[0]*exp(-pow((x-[1])/[2],2))",mean_tmp-sigma_tmp,mean_tmp+sigma_tmp);
fGauss_24 -> SetParameters(a_tmp,mean_tmp,sigma_tmp);
fGauss_24 -> Update();
hdiffAmplVar1->Fit("fGauss_24","R","",mean_tmp-sigma_tmp,mean_tmp-sigma_tmp);
a_tmp1 = fGauss_24->GetParameter(0);
mean_tmp1 = fGauss_24->GetParameter(1);
sigma_tmp1 = fGauss_24->GetParameter(2);

TF1 *fGauss_34 = new TF1("fGauss_34","[0]*exp(-pow((x-[1])/[2],2))",mean_tmp1-sigma_tmp1,mean_tmp1+sigma_tmp1);
fGauss_34 -> SetParameters(a_tmp1,mean_tmp1,sigma_tmp1);
fGauss_34 -> SetParNames("A","Mean","Sigma");
fGauss_34 -> SetLineColor(6);
hdiffAmplVar1 -> Fit("fGauss_34","R","",mean_tmp1-sigma_tmp1,mean_tmp1-sigma_tmp1);
//changed for new function! ponting to fGauss_24, not fGauss_34:
mean_hdiffAmplVar1 = fGauss_24->GetParameter(1);
sigma_hdiffAmplVar1 = fGauss_24->GetParameter(2);
mean_hdiffAmplVar1Error = fGauss_24->GetParError(1);
sigma_hdiffAmplVar1Error = fGauss_24->GetParError(2);



//outputFile16<<(motorPositionAnt/4000)-10<<" "<<mean_hdiffAmplVar1<<" "<<"0"<<" "<<mean_hdiffAmplVar1Error<<endl;
if ((motorPositionAnt>19000)&&(motorPositionAnt<61000)){outputFile17<<(motorPositionAnt/4000)-10<<" "<<mean_hdiffAmplVar1<<" "<<"0"<<" "<<mean_hdiffAmplVar1Error<<endl;}
//outputFile18<<(motorPositionAnt/4000)-10<<" "<<sigma_hdiffAmplVar1<<" "<<"0"<<" "<<sigma_hdiffAmplVar1Error<<endl;
if ((motorPositionAnt>19000)&&(motorPositionAnt<61000)){outputFile19<<(motorPositionAnt/4000)-10<<" "<<sigma_hdiffAmplVar1<<" "<<"0"<<" "<<sigma_hdiffAmplVar1Error<<endl;}

//*******************************************
//**********************Amplitudes******************
meanMax0 = hmax0->GetMean();
meanErrorMax0 = hmax0->GetMeanError();
rmsMax0 = hmax0->GetRMS();
rmsErrorMax0 = hmax0->GetRMSError();

meanMax1 = hmax1->GetMean();
meanErrorMax1 = hmax1->GetMeanError();
rmsMax1 = hmax1->GetRMS();
rmsErrorMax1 = hmax1->GetRMSError();

//outputFile20<<(motorPositionAnt/4000)-10<<" "<<mean<<" "<<"0"<<" "<<rms<<endl;
if ((motorPositionAnt>19000)&&(motorPositionAnt<61000)){outputFile20<<(motorPositionAnt/4000)-10<<" "<<meanMax0<<" "<<"0"<<" "<<meanErrorMax0<<endl;}
if ((motorPositionAnt>19000)&&(motorPositionAnt<61000)){outputFile21<<(motorPositionAnt/4000)-10<<" "<<meanMax1<<" "<<"0"<<" "<<meanErrorMax1<<endl;}
if ((motorPositionAnt>19000)&&(motorPositionAnt<61000)){outputFile22<<(motorPositionAnt/4000)-10<<" "<<rmsMax0<<" "<<"0"<<" "<<rmsErrorMax0<<endl;}
if ((motorPositionAnt>19000)&&(motorPositionAnt<61000)){outputFile23<<(motorPositionAnt/4000)-10<<" "<<rmsMax1<<" "<<"0"<<" "<<rmsErrorMax1<<endl;}
//*******************************************

    TCanvas *c1 = new TCanvas ("c1","hLogAmpl",1000,600);
      c1->Divide(1,1);
      c1->cd(1);
      //gPad->SetLogy();
    //  gStyle->SetOptStat(0);
      gStyle->SetOptFit(1111);
      hLogAmpl->Draw();
      c1 ->Print(("plots/hLogAmpl_"+int_to_string((int) motorPositionAnt)+".png").c_str());
      c1->cd();

 //******************************************************

      TCanvas *c2 = new TCanvas ("c2","hDeltaT1",1000,600);
        c2->Divide(1,1);
        c2->cd(1);
        //gPad->SetLogy();
       // gStyle->SetOptStat(0);
        gStyle->SetOptFit(1111);
        hDeltaT1->Draw();
        c2 ->Print(("plots/hDeltaT1_"+int_to_string((int) motorPositionAnt)+".png").c_str());
        //c2->SaveAs("hDeltaT1_.pdf");
        c2->cd();

 //******************************************************

    TCanvas *c3 = new TCanvas ("c3","AmplVsTime",1000,600);
      c3->Divide(1,1);
      c3->cd(1);
      gPad->SetLogz();
     // gPad->SetLogy();
    //  gStyle->SetOptStat(0);
      gStyle->SetOptFit(1111);
      h1->Draw("contz");
      //c3->SaveAs("AmplVsTime_.pdf");
      c3 ->Print(("plots/AmplVsTime_"+int_to_string((int) motorPositionAnt)+".png").c_str());
      c3->cd();

//******************************************************

      TCanvas *c4 = new TCanvas ("c4","hAmplVar1_",1000,600);
        c4->Divide(1,1);
        c4->cd(1);
       // gPad->SetLogy();
      //  gStyle->SetOptStat(0);
        gStyle->SetOptFit(1111);
        hAmplVar1_->Draw();
        c4 ->Print(("plots/hAmplVar1_"+int_to_string((int) motorPositionAnt)+".png").c_str());
        //c4->SaveAs("hAmplVar1_.pdf");
        c4->cd();

 //******************************************************

      TCanvas *c5 = new TCanvas ("c5","hRatio",1000,600);
        c5->Divide(1,1);
        c5->cd(1);
        //gPad->SetLogy();
       // gStyle->SetOptStat(0);
        gStyle->SetOptFit(1111);
        hRatio->Draw();
        c5 ->Print(("plots/hRatio_"+int_to_string((int) motorPositionAnt)+".png").c_str());
        //c5->SaveAs("plots/hRatio_.pdf");
        c5->cd();
 //******************************************************

      TCanvas *c6 = new TCanvas ("c6","hLogAmplSlow",1000,600);
        c6->Divide(1,1);
        c6->cd(1);
        //gPad->SetLogy();
      //  gStyle->SetOptStat(0);
        gStyle->SetOptFit(1111);
        hLogAmplSlow->Draw();
        c6 ->Print(("plots/hLogAmplSlow_"+int_to_string((int) motorPositionAnt)+".png").c_str());
        //c6->SaveAs("plots/hLogAmplSlow_.pdf");
        c6->cd();
 //******************************************************

        TCanvas *c7 = new TCanvas ("c7","hAmplVar2_",1000,600);
          c7->Divide(1,1);
          c7->cd(1);
         // gPad->SetLogy();
        //  gStyle->SetOptStat(0);
          gStyle->SetOptFit(1111);
          hAmplVar2_->Draw();
          c7 ->Print(("plots/hAmplVar2_"+int_to_string((int) motorPositionAnt)+".png").c_str());
          //c4->SaveAs("hAmplVar2_.pdf");
          c7->cd();
//******************************************************

          TCanvas *c8 = new TCanvas ("c8","A2",1000,600);
          c8->SetGrid();
          c8->Divide(1,1);
          c8->cd(1);
          gPad->SetLogz();
          //gPad->SetLogy();
          //gPad->SetLogx();
          gStyle->SetOptStat(0);
          gStyle->SetOptFit(1111);
          h2->Draw("contz");
          c8 ->Print(("plots/dtVsRatio"+int_to_string((int) motorPositionAnt)+".png").c_str());
          c8->cd();

   //******************************************************
          TCanvas *c11 = new TCanvas ("c11","hdiffAmplVar1",1000,600);
          c11->Divide(1,1);
          c11->cd(1);
          // gPad->SetLogy();
          //  gStyle->SetOptStat(0);
          gStyle->SetOptFit(1111);
          hdiffAmplVar1->Draw();
          c11 ->Print(("plots/hdiffAmplVar1_"+int_to_string((int) motorPositionAnt)+".png").c_str());
          //c4->SaveAs("hAmplVar1_.pdf");
          c11->cd();

     //******************************************************



          TCanvas *c10 = new TCanvas ("c10","hpos",1000,600);
          c10->Divide(1,1);
          c10->cd(1);
          // gPad->SetLogy();
          //  gStyle->SetOptStat(0);
          gStyle->SetOptFit(1111);
          hpos->Draw();
          c10 ->Print(("plots/recTime"+int_to_string((int) motorPositionAnt)+".png").c_str());
          //c4->SaveAs("recTime.pdf");
          c10->cd();

     //******************************************************

          TCanvas *c12 = new TCanvas ("c12","hposAmpl",1000,600);
          c12->Divide(1,1);
          c12->cd(1);
          // gPad->SetLogy();
          //  gStyle->SetOptStat(0);
          gStyle->SetOptFit(1111);
          hposA->Draw();
          c12 ->Print(("plots/recAmpl"+int_to_string((int) motorPositionAnt)+".png").c_str());
          //c4->SaveAs("recTime.pdf");
          c12->cd();

     //******************************************************

 hpos -> Reset("ICESM");
 hposA -> Reset("ICESM");
 hDeltaT1 -> Reset("ICESM");
 hLogAmpl -> Reset("ICESM");
 hLogAmplSlow -> Reset("ICESM");
 hRatio -> Reset("ICESM");
 hAmplVar1_-> Reset("ICESM");
 hAmplVar2_-> Reset("ICESM");
 h1 -> Reset("ICESM");
 h2 -> Reset("ICESM");
 hdiffAmplVar1 -> Reset("ICESM");


}
motorPositionAnt=motorPosition;
        }
}
outputFile1.close();
outputFile2.close();
//outputFile3.close();
//outputFile4.close();
outputFile5.close();
outputFile6.close();
//outputFile7.close();
outputFile8.close();
outputFile9.close();
outputFile10.close();
outputFile11.close();
outputFile12.close();
outputFile13.close();
outputFile14.close();
//outputFile16.close();
outputFile17.close();
//outputFile18.close();
outputFile19.close();
outputFile20.close();
outputFile21.close();
outputFile22.close();
outputFile23.close();
//outputFile25.close();
outputFile26.close();


//******************************************************
float motor1, motor2, motor3, motor4, cero;
int secondCount = 0;

for (ULong64_t j = 0 ; j < nentries ; j++){
    ntuple->GetEntry(j);

//~~~~~~~~~~~~~Set motor position!!!!!~~~~~~~~~~~~~~~~~~

    if (j==0){motorPositionAnt=motorPosition;}

    name = ((int) motorPositionAnt/4000)-10;
    limit = (motorPositionAnt/4000)-10;
    if (limit<=10.5){
    if (motorPosition==motorPositionAnt){


          if ( deltaT1_>=meanT.at(secondCount)-sigmaT.at(secondCount) && deltaT1_<= meanT.at(secondCount)+sigmaT.at(secondCount)  && logAmplitudes_>= meanLog.at(secondCount)-sigmaLog.at(secondCount) && logAmplitudes_<=meanLog.at(secondCount)+sigmaLog.at(secondCount)){

              htmp1->Fill((max0_-max1_)/(max0_+max1_),deltaT1_);

}
    }

          else{
          outputFile15<<(motorPositionAnt/4000)-10<<" "<<htmp1->GetCorrelationFactor()<<endl;

          //***********For reconstruction using time and amplitudes************************
          //Using BLUE method
          // meanTimePos, sigmaTimePos, meanAmplPos, sigmaAmplPos,

          meanPosNum1 = meanTimePosVec.at(secondCount)*((sigmaAmplPosVec.at(secondCount)*sigmaAmplPosVec.at(secondCount))-(htmp1->GetCorrelationFactor()*sigmaTimePosVec.at(secondCount)*sigmaAmplPosVec.at(secondCount)));
          meanPosNum2 = meanAmplPosVec.at(secondCount)*((sigmaTimePosVec.at(secondCount)*sigmaTimePosVec.at(secondCount))-(htmp1->GetCorrelationFactor()*sigmaTimePosVec.at(secondCount)*sigmaAmplPosVec.at(secondCount)));
          meanPosDen = (sigmaTimePosVec.at(secondCount)*sigmaTimePosVec.at(secondCount))-(2*htmp1->GetCorrelationFactor()*sigmaTimePosVec.at(secondCount)*sigmaAmplPosVec.at(secondCount))+(sigmaAmplPosVec.at(secondCount)*sigmaAmplPosVec.at(secondCount));
          meanPos = (meanPosNum1+meanPosNum2)/meanPosDen;

          sigmaPos = TMath::Sqrt(((sigmaTimePosVec.at(secondCount)*sigmaTimePosVec.at(secondCount)*sigmaAmplPosVec.at(secondCount)*sigmaAmplPosVec.at(secondCount))*(1-(htmp1->GetCorrelationFactor()*htmp1->GetCorrelationFactor())))/meanPosDen);

          if ((motorPositionAnt>19000)&&(motorPositionAnt<61000)){outputFile16<<(motorPositionAnt/400)-100<<" "<<meanPos<<" "<<"0"<<" "<<sigmaPos<<endl;}
          //if ((motorPositionAnt>19000)&&(motorPositionAnt<61000)){outputFile4<<(motorPositionAnt/4000)-10<<" "<<sigma_DeltaT1<<" "<<"0"<<" "<<sigma_DeltaT1Error<<endl;}

          secondCount++;
          TCanvas *c9 = new TCanvas ("c9","A3",1000,600);

          string sourcePosition="Source located at "+int_to_string((int) (motorPositionAnt/4000)-10.0)+"cm";

          c9->SetGrid();
          c9->Divide(1,1);
          c9->cd(1);
          //gPad->SetLogz();
          //gPad->SetLogy();
          //gPad->SetLogx();
          gStyle->SetOptStat(0);
          gStyle->SetOptFit(1111);
          //h3->Draw("coldz 0");
          htmp1->Draw("cont1");

          TPaveText *labeA = new TPaveText(0.65,0.90,0.9,0.99,"brNDC");
          labeA->AddText(sourcePosition.c_str());
          labeA->Draw();

          c9 ->Print(("plots/dtVsHdiffAmplVar1"+int_to_string((int) motorPositionAnt)+".png").c_str());
          if((motorPositionAnt==19000)||(motorPositionAnt==40000)||(motorPositionAnt==60000)){
          c9 ->Print(("dtVsHdiffAmplVar1"+int_to_string((int) (motorPositionAnt/4000)-10.0)+".png").c_str());}
          c9->cd();

          htmp1->Reset("ICESM");
      }
      motorPositionAnt=motorPosition;



          }
      }outputFile15.close();
}




