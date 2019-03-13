#include <TROOT.h>
#include "TCanvas.h"
#include "TGraph.h"

void construct_graph(TGraph *g1, const char *title, const char *x_axis, const char *y_axis, int x_min, int x_max)
{
    g1->SetName(title);
    g1->SetMarkerColor(kRed);
    // g1->SetMaximum(100000);
    // g1->SetMinimum(0);
    g1->GetXaxis()->SetTitle(x_axis);
    g1->GetYaxis()->SetTitle(y_axis);
    g1->SetFillColor(40);
    g1->GetXaxis()->CenterTitle();
    g1->GetYaxis()->CenterTitle();
    g1->GetXaxis()->SetRangeUser(x_min, x_max);
    //g1->Draw("AB");
}
//used for creating a graph of difference between value and fit..
void residual_fits(TGraph *tg, TF1 *fit, double_t x_min, double_t x_max, TGraph* tg_out, int point)
{
    double *x_points = tg->GetX();
    double *y_points = tg->GetY();
    double_t difference(0);
        
    for (int i = 0; i < tg->GetN(); i++)
    {
        difference = y_points[i] - fit->Eval(x_points[i]);
        if (difference != 0 and x_points[i] > x_min and x_points[i] < x_max)
        {
            cout << "thresh: " << x_points[i] << "\tdiff:" << difference << "\tfit value: " << fit->Eval(x_points[i]) << "\tval: " << y_points[i] << endl;
            tg_out->SetPoint(++point, x_points[i], difference);
        }
    }
}

void iterate_fit(TGraph *tg, double_t x_min, double_t x_max, int num_fits, TGraph *tg_out, int point)
{

    TF1 *my_func = new TF1("my_func", "pol2");

    double_t width = (x_max - x_min) / num_fits;
    //previous parameters to guess for fits (avoid explosive fits)
    double_t prev_p0, prev_p1, prev_p2;    
    //printf("avg_slope\tmid_slope\tthresh_mid\n");
    for (int i = 0; i < num_fits; ++i)
    {
        // set the min and max values for this iteration..
        double_t x_min_p = x_min + (width * i);
        double_t x_max_p = x_min + (width * (i + 1));

        my_func->SetParameter("p0", prev_p0);
        my_func->SetParameter("p1", prev_p1);
        my_func->SetParameter("p2", prev_p2);

        tg->Fit(my_func, "QW", "L", x_min_p, x_max_p);
        residual_fits(tg,my_func, x_min_p, x_max_p, tg_out, point);
        
        if (my_func->IsZombie()) {
            prev_p0 = my_func->GetParameter("p0");
            prev_p1 = my_func->GetParameter("p1");
            prev_p2 = my_func->GetParameter("p2");
        }
    }
}

void fill_hist_from_file(const char * file)
{
    TFile *f = new TFile(file);
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
        point++;
        double slope = Scalar - Prev_Scalar;
        g1->SetPoint(point, Thresh, Scalar);
        g2->SetPoint(point, Thresh, slope);
        Prev_Scalar = Scalar;
    }

    // // get the x and y points of the graph that you want
    // double_t *x_points = g1->GetX();
    // double_t *y_points = g1->GetY();

    // //create a histogram from the graph..
    // TH1F *hist1 = new TH1F("hist1", "hist1_title", g1->GetN(), -0.5, 4095.5);
    // for (int i = 0; i < g1->GetN(); i++)
    // {
    //     hist1->Fill(x_points[i], y_points[i]);
    // }
    
    int point2(0);
    TGraph *tg_diff =  new TGraph();
    iterate_fit(g1, 3150, 3470, 8, tg_diff, point2);

    TCanvas *c1 = new TCanvas("c1", "Canvas name", 1400, 600);
    gStyle->SetOptStat(1111111); // draws statistics on the plots
    gStyle->SetOptFit(1111);     //includes a fit on the graph
    gStyle->SetPalette(57);
    c1->Divide(2,1);
    c1->cd(1);
    c1->SetLogy();
    construct_graph(g1, "graph_1", "threshold", "Scalar_counts", 2900, 3600); 
    g1->Draw("ABQ");
    
    c1->cd(2);
    c1->SetLogy();
    construct_graph(tg_diff, "graph_2", "threshold", "Difference", 2900, 3600);
    tg_diff->Draw("");

    // //create a spline from the graph..
    // TSpline3 *spline3 = new TSpline3("spline", x_points, y_points, g1->GetN());
    // spline3->Draw("LSAME");

    // c1->cd(2);
    // construct_graph(g2, "graph_1", "threshold", "Scalar_slope", 3400, 3500);
    // g2->Draw("ABQ");
}