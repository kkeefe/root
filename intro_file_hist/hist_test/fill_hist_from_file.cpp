#include "Math/Functor.h"
#include "Math/RichardsonDerivator.h"

void fill_hist_from_file()
{
    TFile *f = new TFile("root_file_name.root");
    TNtuple *ntup1 = (TNtuple *)f->Get("ntup1");

    int entries = ntup1->GetEntries();

    //set your branch addresses
    float_t DSP_Card, DSP_Chan, Reg, Thresh, Scalar; 
    //float_t Scalar_total;
    ntup1->SetBranchAddress("DSP_Card", &DSP_Card);
    ntup1->SetBranchAddress("DSP_Chan", &DSP_Chan);
    ntup1->SetBranchAddress("Reg", &Reg);
    ntup1->SetBranchAddress("Thresh", &Thresh);
    ntup1->SetBranchAddress("Scalar", &Scalar);

    //create your own histogram
    int bin_count(1);
    int x_min(0), x_max(4091);
    TH1 *hist1 = new TH1I("hist_1", "ntup1 hist", bin_count, x_min, x_max);

    //ntup1->Draw("Thresh>>hist1");
    //create a new graph object
    TGraph *g1 = new TGraph();
    //set the new graph parameters and title.
    g1->SetMarkerStyle(20);
    g1->SetName("Plot of Thresh vs. Scalar_Total");
    g1->SetMarkerColor(kRed);
    int point(0);

    for (int i = 0; i < entries; ++i)
    {
        ntup1->GetEntry(i);
        //cout << Reg << "\t" << entries << "\t" << i << "\t" << Scalar << "\t" << Thresh << endl;
        //select the register you want to histogram
        if (Reg == 111)
        {
            point++;
            //Scalar_total += Scalar;
            g1->SetPoint(point, Thresh, Scalar);
            hist1->Fill(Scalar);
        }
    }

    // //create the function to attempt to the fit the data
    // TF1 *f = new TF1("f", "[0]*cos([1]*x+[2])+[3]", 0, 5);
    // f->SetParNames("Amplitude", "period", "Phase", "Translation");

    //create a guess of each of the values
    //f->SetParameters(2, 1, 0, 0.1);

    //this allows for multiple plots to be put into the same macro
    TCanvas *c1 = new TCanvas("c1", "Canvas name", 1400, 700);
    c1->Divide(2, 1);
    c1->cd(1);
    //attempt to fit the function
    //g1->Fit(f);
    c1->SetLogy();
    g1->Draw("AP");
    c1->cd(2);
    hist1->Draw();
}
