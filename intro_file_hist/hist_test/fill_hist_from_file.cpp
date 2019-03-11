#include <TROOT.h>
#include "TCanvas.h"
#include "TGraph.h"

void construct_graph(TGraph *g1, const char *title, const char *x_axis, const char *y_axis, int x_min, int x_max)
{
    g1->SetName(title);
    g1->SetMarkerColor(kRed);
    g1->SetMaximum(100000);
    g1->SetMinimum(0);
    g1->GetXaxis()->SetTitle(x_axis);
    g1->GetYaxis()->SetTitle(y_axis);
    g1->SetFillColor(40);
    g1->GetXaxis()->CenterTitle();
    g1->GetYaxis()->CenterTitle();
    g1->GetXaxis()->SetRangeUser(x_min, x_max);
    gStyle->SetOptStat(1111111); // draws statistics on the plots
    gStyle->SetOptFit(1111);     //includes a fit on the graph
    gStyle->SetPalette(57);
    //g1->Draw("AB");
}

vector<double_t> iterate_fit(TGraph *tg, double_t x_min, double_t x_max, int num_fits)
{

    TF1 *my_func = new TF1("my_func", "[0]+[1]*x+[2]*x^2");
    my_func->SetParNames("s0", "s1", "s2");

    vector<double_t> slopes;
    double_t width = (x_max - x_min) / num_fits;

    printf("avg_slope\tmid_slope\tthresh_mid\n");
    for (int i = 0; i < num_fits; ++i)
    {
        double_t value = x_min + (width * (i + 1 / 2)); //take the derivative in the middle of the current range..
        double_t low_slope, high_slope;

        tg->Fit(my_func, "QW", "L", x_min + (width * i), x_min + (width * (i + 1)));
        slopes.push_back(my_func->Derivative(value));

        low_slope = my_func->Derivative(x_min + (width * i));
        high_slope = my_func->Derivative(x_min + (width * (i + 1)));

        cout << (low_slope + high_slope) / 2 << "\t" << my_func->Derivative(value) << "\t" << value << endl;

        //my_func->Print();
        //cout << my_func->GetParameter("s0") << "\t" << my_func->GetParameter("s1") << "\t" << my_func->GetParameter("s2") << "\t\t" << width << endl;
        //cout << "current derivative: " << slopes[i] << endl;
    }
    return slopes;
}

void fill_hist_from_file()
{
    TFile *f = new TFile("root_file_name.root");
    TNtuple *ntup1 = (TNtuple *)f->Get("ntup1");

    //set your branch addresses
    float_t DSP_Card, DSP_Chan, Reg, Thresh, Scalar, Prev_Scalar;
    ntup1->SetBranchAddress("DSP_Card", &DSP_Card);
    ntup1->SetBranchAddress("DSP_Chan", &DSP_Chan);
    ntup1->SetBranchAddress("Reg", &Reg);
    ntup1->SetBranchAddress("Thresh", &Thresh);
    ntup1->SetBranchAddress("Scalar", &Scalar);

    //create a new graph object
    TGraph *g1 = new TGraph();
    TGraph *g2 = new TGraph();
    int point(0);

    for (int i = 0; i < ntup1->GetEntries(); ++i)
    {
        ntup1->GetEntry(i);
        //select the register you want to histogram
        if (Reg == 111)
        {
            point++;
            double slope = Scalar - Prev_Scalar;
            // //used for finding where the turnover slope is..
            // if (slope != 0 and slope < 0)
            // {
            //     cout << "slope is: " << slope << " at point: " << point << endl;
            // }
            //Scalar_total += Scalar;
            g1->SetPoint(point, Thresh, Scalar);
            g2->SetPoint(point, Thresh, slope);
            Prev_Scalar = Scalar;
        }
    }

    // TF1 *my_fnc = new TF1("my_expo", "[0]exp([1]+x)")
    // //create the function to attempt to the fit the data
    // TF1 *fnc = new TF1("expo_fit", "expo");
    // // fnc->SetParNames("Amplitude", "x_shift", "Phase", "Translation");
    // TF1 *poly_fit = new TF1("poly_fit","pol 4");
    // // create a guess of each of the values
    // //f->SetParameters(2, 1, 0, 0.1);

    TCanvas *c1 = new TCanvas("c1", "Canvas name", 700, 600);
    // c1->Divide(2, 1);
    c1->SetLogy();
    c1->cd(1);
    construct_graph(g1, "graph_1", "threshold", "Scalar_counts", 2900, 3600);

    vector<double_t> slopes = iterate_fit(g1, 2900, 3460, 32);

    //g1->Fit(poly_fit, "MW", "L", 3450, 3453);
    g1->Draw("ABQ");
    // cout << "poly fit p0 is: " << poly_fit->GetParameter("p0") << endl;

    // for(auto c : slopes){
    //     cout << "slope is: " << c << endl;
    // }

    // c1->cd(2);
    // construct_graph(g2, "graph_1", "threshold", "Scalar_slope", 3400, 3500);
    // g2->Draw("ABQ");
}