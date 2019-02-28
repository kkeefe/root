//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// NTC-Hawaii team
//
// This program proccess the output file of createTree and generates a ntuple file with time
// and amplitude information. The improve of this with its last version is that this file is
// capable to obtain the vector time using the time calibration file from the DSR4. The con-
// stant fraction discriminator method is also changed to the EDGE LEADING method, using
// the 50% of the total height of the pulse.
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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
#include "TAxis.h"
#include "TLegend.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TApplication.h"
#include "TPaveLabel.h"
#include "TPaveText.h"
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <vector>
#include "Riostream.h"
#include "TStyle.h"
#include "TNtuple.h"


using namespace std;

int main(int argc, char **argv){
cout << argv[1]<< endl;
  if(argc!=3) {
    cerr << "Usage:\n   "<<argv[1]<<" path and name to root data files input to analyze"<<endl;
    cerr << "Usage:\n   "<<argv[2]<<" filename.root output file"<<endl;
    exit(1);
  }



//string nombre = argv[1];
  string path = argv[1];
 // string outFile = argv[1];
  string filesList = path + "*";
//gROOT->SetBatch();
TApplication app("app",0,0);

gROOT->ProcessLine("#include <vector>");
// string filesList = "/home/alinegalindo/Documents/Data/rootFiles/Sr90-2018.06.05.Sr90.2/*";
// string filesList = "/home/aline/Documents/DataAnalysis/Sr90BigFileTest/Data/Sr90-2018.06.05.Sr90.2/*";
// string filesList = "./" + nombre
cout<<filesList<<endl;

 TObjArray Hlist(0);

//Histograms
 TH1F *hMean = new TH1F("hMean","Mean; Baseline(mV)",100,-30,30);
 TH1F *hMeanAfter = new TH1F("hMeanBefore","Mean; Baseline(mV)",100,-5,5);

 //Open data file
 TChain *chain = new TChain("T","data"); //Name of the tree in the root data file
 chain->Add(filesList.c_str());
 Double_t Nfiles = chain->GetNtrees();
 cout << "Number of Files in the Chain= " << Nfiles << endl;
 Int_t nentries = (Int_t)chain->GetEntries();
 cout << "Number of Entries in chain= " << nentries << endl;
//==============================================================
 //Declare variables
 Float_t eventNumber_;
 chain->SetBranchAddress("EventNumber",&eventNumber_);
 Float_t boardId_;
 chain->SetBranchAddress("boardId",&boardId_);
 Float_t channel_;
 chain->SetBranchAddress("channel", &channel_);
 Float_t triggerCell;
 chain->SetBranchAddress("GetTriggerCell",&triggerCell);
 Float_t motorPosition_;
 chain->SetBranchAddress("motorPosition",&motorPosition_);
 Float_t GetTemperature_;
 chain->SetBranchAddress("GetTemperature",&GetTemperature_);
 vector<float> *signal_=0;
 chain->SetBranchAddress("vpx",&signal_);
 
 std::vector<float> line;
 std::vector<float> inverted;
 const int n = 1024;  //size of the signal arrayi
 const int n1 = 230;   // size for the CFD signal
 const float limit = 50; // to avoid the two peaks caused by the DRS
 const int delay = 0;
 const float threshold = 7; // Threshold for the leading edges method, init of the pulse
 Float_t y0[n1], y1[n1], y2[n1], y3[n1];
 Float_t timeCh0=0, timeCh1=0, timeCh2=0, timeCh3=0, deltaT1,deltaT2,x_1,x_2,y_1,y_2;
 Int_t flag;
 Double_t mean;
 Float_t max0,max1,max2,max3,  eventNumberAnt_, R12=0, R21=0, RS12=0, RS21=0;
 Float_t amplVar1, amplVar2, logAmplitudes, logAmplitudesInv;
 // variables for time vectors
 int indexTime;
 double time[4][1024];
 double t1, t2, dt;
 float bin_width[4][1024];
 float dt_ch0, dt_ch1, dt_ch2, dt_ch3;
 // variables to remove peaks
 Float_t v1,v2,v3,v4;

 //==============================================================
 //loop to associate bin_width with time calibration file

 ifstream FILE1("2018_10_31_dt_calib.txt",ios::in);
 int aux=0;
 while (FILE1>>indexTime>>dt_ch0>>dt_ch1>>dt_ch2>>dt_ch3){
     bin_width[0][aux]=dt_ch0;
     bin_width[1][aux]=dt_ch1;
     bin_width[2][aux]=dt_ch2;
     bin_width[3][aux]=dt_ch3;
     aux++;
 }

 //==============================================================

 TNtuple *ntuple = new TNtuple("ntuple","data from root file","motorPosition_:deltaT1:deltaT2:amplVar1:amplVar2:logAmplitudes:logAmplitudesInv:timeCh0:timeCh1:timeCh2:timeCh3:max0:max1:max2:max3");
//TNtuple *ntuple = new TNtuple("ntuple","data from root file","sqrtA1A2:A1:A2");
//==============================================================
  Float_t eventInit = 0;
  for (Int_t i = 0; i < nentries ; i++){
//  for (Int_t i = 0; i < 3 ; i++){ 
    chain->GetEntry(i);

//==============================================================
//Calculate time vectors for each channel
if(eventInit!=eventNumber_) {// at the begining of each event

    //initializing the vector in the old way
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 1024; x++)
        {
            time[y][x] = 0;
        }
    }

for (int chn=0 ; chn<4 ; chn++) {
    for (int l=0 ; l<1024 ; l++) {
         // calculate time for this cell
         for (int k=0 ; k<l ; k++){
             time[chn][l] = time[chn][l] + bin_width[chn][(k+(int) triggerCell) % 1024];
         }
      }
   }


 // align cell #0 of all channels
t1 = time[0][(1024 - (int) triggerCell) % 1024];
for (int chn=1 ; chn<4 ; chn++) {
   t2 = time[chn][(1024-(int) triggerCell) % 1024];
   dt = t1 - t2;
   for (int l=0 ; l<1024 ; l++){
      time[chn][l] += dt;}
   }
eventInit=eventNumber_;
//if(triggerCell==880){
//for (Int_t contador = 0; contador < 1023 ; contador++){
//    cout<<time[0][contador]<<"  "<<time[1][contador]<<" "<<time[2][contador]<<" "<<time[3][contador]<<endl;
//}}
}//end if initial event

//==============================================================



 //   if ((eventNumber_==10000)&&(channel_==0)){

 if(i==0){eventNumberAnt_=eventNumber_;}
 else{ if((eventNumberAnt_!=eventNumber_)||(i==nentries-1)){


         deltaT1 = (timeCh1-timeCh0);//*0.196;//.196 corresponds to 5.1 Gsamples
         deltaT2 = (timeCh2-timeCh3);//*0.196;//.196 corresponds to 5.1 Gsamples
         amplVar1 = TMath::Sqrt(max0*max2);
         amplVar2 = TMath::Sqrt(max2*max3);
         R12 = max0/max1;
         R21 = max1/max0;
         RS12 = max0/max3;
         RS21 = max3/max2;
         logAmplitudes = TMath::Log(max0/max1);
         logAmplitudesInv = TMath::Log(max1/max0);
         //after asign deltaT and deltaT2, the scale is changed to ns for the times
         /*timeCh0 = timeCh0*0.196;
         timeCh1 = timeCh1*0.196;
         timeCh2 = timeCh2*0.196;
         timeCh3 = timeCh3*0.196;*/
        if (deltaT1<-20){
         cout<<"Event: "<<eventNumber_<<endl;
         cout<<"Time0: "<<timeCh0<<" Time1: "<<timeCh1<<" DeltaT1: "<<deltaT1<<endl;
         cout<<"Time2: "<<timeCh2<<" Time3: "<<timeCh3<<" DeltaT2: "<<deltaT2<<endl;
         cout<<"ampl2: "<<max2<<" ampl3: "<<max3<<endl;
          }

         //if ((deltaT1<100)&&(deltaT1>-100)&&(deltaT2<100)&&(deltaT2>-100)){
        ntuple->Fill(motorPosition_,deltaT1,deltaT2,amplVar1,amplVar2,logAmplitudes,logAmplitudesInv,timeCh0,timeCh1, timeCh2,timeCh3,max0,max1,max2,max3);
        // ntuple->Fill(amplVar1,max0,max2);
         }}//}
 //==============================================================
 // Move to 0 the baseline

    for (unsigned int j=0; j<400 ; j++) {
       hMean->Fill(signal_->at(j));
      }
     mean = hMean->GetMean();
     for (unsigned int j=0; j<signal_->size() ; j++) {
       signal_->at(j) = signal_->at(j) - mean;}

//==============================================================
//==============================================================
//Remove peaks

   for (unsigned int j=0; j<signal_->size()-4 ; j++) {
          v1=signal_->at(j);
          v2=signal_->at(j+1);
          v3=signal_->at(j+2);
          v4=signal_->at(j+3);
          if((v2-v1>10)&&(v3-v4>10)){
              signal_->at(j+1)=v1;
              signal_->at(j+2)=v4;
          }
          /*if((v2-v1>10)&&(v2-v3>10)){ //lonely spikes
              signal_->at(j+1)=v1;
          }
          if((v2-v1<10)&&(v3-v4<10)){//negative typical spikes
              signal_->at(j+1)=v1;
              signal_->at(j+2)=v4;
          }
          if((v2-v1<10)&&(v2-v3<10)){ //lonely negative spikes
              signal_->at(j+1)=v1;
          }*/
   }

//==============================================================
// Move to 0 the baseline after removing peaks

   for (unsigned int j=0; j<400 ; j++) {
     hMeanAfter->Fill(signal_->at(j));
     }
    mean = hMeanAfter->GetMean();
   for (unsigned int j=0; j<signal_->size() ; j++) {
     signal_->at(j) = signal_->at(j) - mean;}
//==============================================================


if (channel_== 0){

line.clear();
inverted.clear();
max0=0;
flag=1;

      for (unsigned int j=0; j<signal_->size() ; j++) {

        if(signal_->at(j) > max0){ //Amplitude
          max0 = signal_->at(j);
          }
        }//cout<<"max value"<<max0<<endl;

     for (unsigned int j=500; j<700+delay ; j++){
       if((signal_->at(j) > 0.5*max0)&&(flag==1)){
           y_1 = signal_->at(j-1);
           x_1 = (Float_t) time[0][j-1];
           y_2 = signal_->at(j);
           x_2 = (Float_t) time[0][j];
           flag = 0;
       }
     }
//line function obtained from two points and set to get the time at 50% of the total peak height
     timeCh0=((((max0/2)-y_1)/(y_2-y_1))*(x_2-x_1))+x_1;

//encontrar la mitad del pulso y el tiempo al que le corresponde

}//end if

if (channel_== 1){
line.clear();
inverted.clear();
max1=0;
flag=1;

   for (unsigned int j=0; j<signal_->size() ; j++) {

        if(signal_->at(j) > max1){//Amplitude
          max1= signal_->at(j);
          }
     }

     for (unsigned int j=500; j<700+delay ; j++){ //pulse inverted
         if((signal_->at(j) > 0.5*max1)&&(flag==1)){
             y_1 = signal_->at(j-1);
             x_1 = (Float_t) time[1][j-1];
             y_2 = signal_->at(j);
             x_2 = (Float_t) time[1][j];
             flag = 0;
         }
       }
  //line function obtained from two points and set to get the time at 50% of the total peak height
       timeCh1=((((max0/2)-y_1)/(y_2-y_1))*(x_2-x_1))+x_1;
}//end if


if (channel_== 2){
line.clear();
inverted.clear();
max2=0;
flag=1;

    for (unsigned int j=0; j<signal_->size() ; j++) {;

        if(signal_->at(j) > max2){
          max2= signal_->at(j);
          }
        }

     for (unsigned int j=500; j<700+delay ; j++){ //pulse inverted
         if((signal_->at(j) > 0.5*max2)&&(flag==1)){
             y_1 = signal_->at(j-1);
             x_1 = (Float_t) time[2][j-1];
             y_2 = signal_->at(j);
             x_2 = (Float_t) time[2][j];
             flag = 0;
         }
       }
  //line function obtained from two points and set to get the time at 50% of the total peak height
       timeCh2=((((max0/2)-y_1)/(y_2-y_1))*(x_2-x_1))+x_1;
}//end if



if (channel_== 3){
line.clear();
inverted.clear();
max3=0;
flag=1;
    for (unsigned int j=0; j<signal_->size() ; j++) {

       if(signal_->at(j) > max3){
           max3= signal_->at(j);
           }
       }

    for (unsigned int j=500; j<700+delay ; j++){ //pulse inverted
        if((signal_->at(j) > 0.5*max3)&&(flag==1)){
            y_1 = signal_->at(j-1);
            x_1 = (Float_t) time[3][j-1];
            y_2 = signal_->at(j);
            x_2 = (Float_t) time[3][j];
            flag = 0;
        }
      }
 //line function obtained from two points and set to get the time at 50% of the total peak height
      timeCh3=((((max0/2)-y_1)/(y_2-y_1))*(x_2-x_1))+x_1;
}//end if
hMeanAfter-> Reset("ICESM");
hMean-> Reset("ICESM");
 eventNumberAnt_=eventNumber_;
// }//end if events<10
}//end for entries
//==============================================================

  //Last event to be recorded
 deltaT1 = (timeCh1-timeCh0);
 deltaT2 = (timeCh2-timeCh3);
 amplVar1 = TMath::Sqrt(max0*max1);
 amplVar2 = TMath::Sqrt(max2*max3);
 ntuple->Fill(motorPosition_,deltaT1,deltaT2,amplVar1,amplVar2,logAmplitudes,logAmplitudesInv,timeCh0, timeCh1, timeCh2,timeCh3, max0, max1, max2, max3);
 //ntuple->Fill(amplVar1, max0, max1);
 //==============================================================


TFile *frt = new TFile(argv[2], "RECREATE");
ntuple->Write();
cout<<" File written"<<endl;

//cout<<"Press any key to continue"<<endl;
//cin.get();
//app.Terminate();
return 0;


}// end program

