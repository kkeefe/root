#include <TROOT.h>
#include "TCanvas.h"
#include "TGraph.h"

//one line method of constructing a graph and settings title / axis values.. will change graph passed to it as argument..
void construct_graph(TGraph *g1, const char *title, const char *x_axis, const char *y_axis, int x_min, int x_max)
{
    g1->SetName(title);
    g1->SetMarkerColor(39);
    g1->SetMaximum(80000);
    g1->SetMinimum(0);
    g1->GetXaxis()->SetTitle(x_axis);
    g1->GetYaxis()->SetTitle(y_axis);
    g1->SetFillColor(38);
    g1->GetXaxis()->CenterTitle();
    g1->GetYaxis()->CenterTitle();
    g1->GetXaxis()->SetRangeUser(x_min, x_max);
    //g1->Draw("AB");
}
//same as construct graph but mirrors min and max y-values on the axis..
void construct_graph_min(TGraph *g1, const char *title, const char *x_axis, const char *y_axis, int x_min, int x_max)
{
    g1->SetName(title);
    g1->SetMarkerColor(39);
    g1->SetMaximum(80000);
    g1->SetMinimum(-80000);
    g1->GetXaxis()->SetTitle(x_axis);
    g1->GetYaxis()->SetTitle(y_axis);
    g1->SetFillColor(38);
    g1->GetXaxis()->CenterTitle();
    g1->GetYaxis()->CenterTitle();
    g1->GetXaxis()->SetRangeUser(x_min, x_max);
    //g1->Draw("AB");
}

const char *make_constChar(double_t type)
{
    TString name;
    name.Form("%f", type);
    return name.Data();
}
// find the pair with the largest second abs_value..
pair<double_t, double_t> find_max(vector<pair<double_t, double_t>> xy_points){

    double_t max_y(0);
    double_t x_point(0);
    
    for(auto c : xy_points){
        if (c.second > max_y or -c.second < -max_y) { //make sure to check positive and negative ranges..
            max_y = c.second;
            x_point = c.first;
        }
    }
    return make_pair(x_point, max_y);
}

pair<double_t, double_t> find_thresh_and_diff_of_tg_diff(TGraph *tg, double_t thresh_val){
    
    double *x_points = tg->GetX();
    double *y_points = tg->GetY();

    double_t threshold_x;
    double_t difference;

    //this will find the first time the threshold is broken..
    for(int i = 0; i < tg->GetN(); i++)
    {
        if (y_points[i] > thresh_val) {
            threshold_x = x_points[i];
            difference = y_points[i];
            break; //stop looking once you found it..
        }
    }
    return make_pair(threshold_x, difference);
}


//at each point, calculate the difference between the fit and the data.. 
void residual_fits(TGraph *tg, TF1 *fit, double_t x_min, double_t x_max, TGraph *tg_out, int *point)
{
    double *x_points = tg->GetX();
    double *y_points = tg->GetY();
    double_t difference(0);

    for (int i = 0; i < tg->GetN(); i++)
    {
        difference = y_points[i] - fit->Eval(x_points[i]);
        if (difference != 0 and x_points[i] > x_min and x_points[i] < x_max) //make sure that you're only looking in the assigned range..
        {
            tg_out->SetPoint(++(*point), x_points[i], difference); //save each point to graph the differences later.. 
        }
    }
}


//defines the range of the total fits, number of total fits, and the fitting function
void iterate_fit(TGraph *tg, double_t x_min, double_t x_max, int num_fits, TGraph *tg_out, int *point)
{
    //select choice of fitting function here..
    TF1 *my_func = new TF1("my_func", "gaus");

    double_t width = (x_max - x_min) / num_fits; //define the width of where the fit will be.
    //previous parameters to guess for fits (avoid explosive fits)
    double_t prev_p0, prev_p1, prev_p2, prev_p3;
    vector<pair<double_t, double_t>> thresholds_xy;

    for (int i = 0; i < num_fits; ++i)
    {
        // set the min and max values for this iteration..
        double_t x_min_p = x_min + (width * i);
        double_t x_max_p = x_min + (width * (i + 1));

        //expo fit parameters..
        my_func->SetParameter("Constant", prev_p0);
        my_func->SetParameter("Mean", prev_p1);
        my_func->SetParameter("Sigma", prev_p2);

        tg->Fit(my_func, "QW", "L", x_min_p, x_max_p);
        //save the max difference from each of the fits..
        
        residual_fits(tg, my_func, x_min_p, x_max_p, tg_out, point);

        prev_p0 = my_func->GetParameter("Constant");
        prev_p1 = my_func->GetParameter("Mean");
        prev_p1 = my_func->GetParameter("Sigma");

        cout << "constant value: " << prev_p0
             << "\t Mean value: " << prev_p1
             << "\t Slope value: " << prev_p2
             << "\t range: " << x_min_p << " to " << x_max_p << endl;
    }
}

void fill_hist_from_file(const char *file){     
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
    vector<pair<Double_t, double_t>> max_thresh_slope;

    for (int i = 0; i < ntup1->GetEntries(); ++i)
    {
        ntup1->GetEntry(i);
        point++;
        double slope = Scalar - Prev_Scalar;
        g1->SetPoint(point, Thresh, Scalar);
        g2->SetPoint(point, Thresh, slope);
        Prev_Scalar = Scalar;
        max_thresh_slope.push_back(make_pair(Thresh,slope));
    }

    int point2(0);
    //will use tg_diff to identify where the threshold_xy value should be placed..
    TGraph *tg_diff = new TGraph();

    //this method fills the tg_diff graph..
    iterate_fit(g1, 2900, 3700, 48, tg_diff, &point2);
    pair<Double_t, double_t> threshold_xy, slope_diff_xy;
    double_t threshold_val(450); //define a threshold value to look for in the difference graph..
    threshold_xy = find_thresh_and_diff_of_tg_diff(tg_diff, threshold_val);
    slope_diff_xy = find_thresh_and_diff_of_tg_diff(g2, threshold_val);

    TCanvas *c1 = new TCanvas("c1", "Canvas name", 2100, 600);
    gStyle->SetOptStat(1111111); // draws statistics on the plots
    gStyle->SetOptFit(1);
    gStyle->SetPalette(57);

    c1->Divide(3, 1);
    c1->cd(1);
    gStyle->SetStatX(0.5);
    gStyle->SetStatY(0.9);
    c1->GetPad(1)->SetLogy();
    construct_graph(g1, "graph_1", "threshold", "Scalar_counts", 2900, 3700);
    g1->Draw("ABQ");
    
    TLine *tl = new TLine();
    tl->SetLineColor(kRed);
    tl->SetLineWidth(2);
    tl->SetLineStyle(9);
    tl->DrawLine(threshold_xy.first, g1->GetMinimum(), threshold_xy.first, g1->GetMaximum());
    
    TLine *tl2 = new TLine();
    tl2->SetLineColor(kBlue);
    tl2->SetLineWidth(2);
    tl2->SetLineStyle(8);
    // // tl2->DrawLine((find_max(max_thresh_slope.first), g1->GetMinimum(), (find_max(max_thresh_slope.first), g1->GetMaximum());
    tl2->DrawLine(slope_diff_xy.first, g1->GetMinimum(), slope_diff_xy.first, g1->GetMaximum());

    c1->cd(2);
    construct_graph_min(tg_diff, "graph_2", "threshold", "Difference", 2900, 3700);
    tg_diff->Draw("APL");
    TPaveText *labeA = new TPaveText(0.15, 0.70, 0.4, 0.79, "brNDC");
    labeA->AddText(make_constChar(threshold_xy.first));
    labeA->Draw();
    TPaveText *labeB = new TPaveText(0.15, 0.80, 0.4, 0.89, "brNDC");
    labeB->AddText(make_constChar(threshold_xy.second));
    labeB->Draw();
    TPaveText *labeB2 = new TPaveText(0.15, 0.20, 0.4, 0.29, "brNDC");
    labeB2->AddText("gaus-fits");
    labeB2->Draw();
    tl->DrawLine(threshold_xy.first, tg_diff->GetMinimum(), threshold_xy.first, tg_diff->GetMaximum());

    c1->cd(3);
    construct_graph_min(g2, "graph_3", "threshold", "scalar point-slope", 2900, 3700);
    g2->Draw("APL");
    TPaveText *labeC = new TPaveText(0.15, 0.70, 0.4, 0.79, "brNDC");
    // labeC->AddText(make_constChar((find_max(max_thresh_slope).first)));
    labeC->AddText(make_constChar(slope_diff_xy.first));
    labeC->Draw();
    TPaveText *labeD = new TPaveText(0.15, 0.80, 0.40, 0.89, "brNDC");
    //labeD->AddText(make_constChar((find_max(max_thresh_slope).second)));
    labeD->AddText(make_constChar(slope_diff_xy.second));
    labeD->Draw();
    TPaveText *labeB3 = new TPaveText(0.15, 0.20, 0.4, 0.29, "brNDC");
    labeB3->AddText("linear-fit");
    labeB3->Draw();
    //tl2->DrawLine((find_max(max_thresh_slope).first), g2->GetMinimum(), (find_max(max_thresh_slope).first), g2->GetMaximum());
    tl2->DrawLine(slope_diff_xy.first, g2->GetMinimum(), slope_diff_xy.first, g2->GetMaximum());

    //create the file name you want, and of course root doesn't mak it easy..
    TString file_string = file;
    int size = file_string.Sizeof();
    file_string.Remove(size - 5, 4);
    file_string.Append("png");
    const char *output_file = file_string;
    c1->SaveAs(output_file);

}