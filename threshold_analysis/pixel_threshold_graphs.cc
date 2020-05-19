#include <TROOT.h>
#include "TCanvas.h"
#include "TGraph.h"
#include "TMultiGraph.h"

//same as construct graph but mirrors min and max y-values on the axis..
void construct_graph(TGraph *g1, const char *title, const char *x_axis, const char *y_axis, int color, int y_max)
{
    g1->SetName(title);
    g1->SetTitle(title);
    g1->SetMarkerColor(39);
    g1->SetMaximum(y_max);
    //g1->SetMinimum(0);
    g1->GetXaxis()->SetTitle(x_axis);
    g1->GetYaxis()->SetTitle(y_axis);
    g1->SetFillColor(color);
    g1->GetXaxis()->CenterTitle();
    g1->GetYaxis()->CenterTitle();
    // g1->GetXaxis()->SetRangeUser(x_min, x_max);
    g1->Draw("AB");
}

double_t find_mean(TGraph *tg) //good to go, but be careful with another function missing point '0' or pixel 59..
{
    double_t *y_points = tg->GetY();
    double_t *x_points = tg->GetX();
    double_t running_sum(0);

    for (int i = 0; i < tg->GetN(); i++)
    {
        running_sum += y_points[i];
        //cout << i << "\t" << x_points[i] << "\t" << y_points[i] << "\t" << running_sum << endl; // print to output to check..
    }
    return (running_sum / (tg->GetN() - 0)); //for whatever reason, pixel 64 is double counted and pixel59 at 0 is neglected..
}

const char * make_constChar(int type) //overload this bad boy to accept ints..
{
  TString name;
  name.Form("%i", type);
  return name.Data();
}

void pixel_threshold_graphs(const char *file)
{

    //set your branch addresses
    float_t pixel_number, gaus_thresh, gaus_diff, linear_thresh, linear_diff, noise_thresh;

    //open the text file you want to read..
    ifstream input_file(file);
    cout << "opening: " << file << endl;

    TGraph *graph_gaus_thresh = new TGraph();   // to be used for the "no - src" ntuple runs..
    TGraph *graph_gaus_diff = new TGraph();     // standard fill graph
    TGraph *graph_linear_thresh = new TGraph(); // point to point slope calculation graph..
    TGraph *graph_linear_diff = new TGraph();   //
    TGraph *graph_noise_thresh = new TGraph();  //

    TGraph *graph_gaus_fromNoise = new TGraph();
    TGraph *graph_lin_fromNoise = new TGraph();

    int point(0); //record the number of points for the graphs that you want..

    while (!input_file.eof())
    {
        input_file >> pixel_number >> gaus_thresh >> gaus_diff >> linear_thresh >> linear_diff >> noise_thresh; //read the whole line..
        graph_gaus_thresh->SetPoint(point, pixel_number, gaus_thresh);                                          // fill the graphs..
        graph_gaus_diff->SetPoint(point, pixel_number, gaus_diff);                                              // fill the graphs..
        graph_linear_thresh->SetPoint(point, pixel_number, linear_thresh);                                      // fill the graphs..
        graph_linear_diff->SetPoint(point, pixel_number, linear_diff);                                          // fill the graphs..
        graph_noise_thresh->SetPoint(point, pixel_number, noise_thresh);                                        // fill the graphs..

        graph_gaus_fromNoise->SetPoint(point, pixel_number, (gaus_thresh - noise_thresh));
        graph_lin_fromNoise->SetPoint(point, pixel_number, (linear_thresh - noise_thresh));
        
        point++;
        // cout << "reading: " << pixel_number <<"\t" << gaus_thresh <<"\t" << gaus_diff <<"\t" << linear_thresh << "\t" <<linear_diff << "\t" << noise_thresh << endl;
    }

    TString file_name = file;
    file_name.Remove(file_name.Sizeof() - 5); //remove .txt
    file_name.Append(".png");

    TCanvas *c0 = new TCanvas("c0", "Gaus_Diff", 1000, 600);
    c0->cd(1);
    graph_gaus_diff->SetMinimum(0);
    construct_graph(graph_gaus_diff, "Gaus Differences", "pixel_number", "Gaus Difference", 38, 10000);
    c0->Print("Gaus_differences_" + file_name);
    c0->cd();

    TCanvas *c1 = new TCanvas("c1", "Gaus_Thresh", 1000, 600);
    c1->cd(1);
    graph_gaus_thresh->SetMinimum(0);
    construct_graph(graph_gaus_thresh, "Gaus Thresholds", "pixel_number", "Gaus Threshold", 39, 4000);
    
    TLine *tl1 = new TLine();
    tl1->SetLineColor(kBlack);
    tl1->SetLineWidth(1);
    tl1->SetLineStyle(10);
    tl1->DrawLine(0, find_mean(graph_gaus_thresh), 70, find_mean(graph_gaus_thresh));
    
    TPaveText *labeA1 = new TPaveText(0.15, 0.20, 0.4, 0.29, "brNDC");
    labeA1->AddText(make_constChar(find_mean(graph_gaus_thresh)));
    labeA1->Draw();

    c1->Print("Gaus_Thresholds_" + file_name);
    c1->cd();

    TCanvas *c2 = new TCanvas("c2", "Linear_diff", 1000, 600);
    c2->cd(1);
    graph_linear_diff->SetMinimum(0);
    construct_graph(graph_linear_diff, "Linear Differences", "pixel_number", "Linear Difference", 41, 2000);
    c2->Print("Linear_differences_" + file_name);
    c2->cd();

    TCanvas *c3 = new TCanvas("c3", "lin-thresh", 1000, 600);
    c3->cd(1);
    graph_linear_thresh->SetMinimum(0);
    construct_graph(graph_linear_thresh, "Linear Thresholds", "pixel_number", "Linear Threshold", 42, 4000);

    TLine *tl3 = new TLine();
    tl3->SetLineColor(kBlack);
    tl3->SetLineWidth(1);
    tl3->SetLineStyle(10);
    tl3->DrawLine(0, find_mean(graph_linear_thresh), 70, find_mean(graph_linear_thresh));
    
    TPaveText *labeA3 = new TPaveText(0.15, 0.20, 0.4, 0.29, "brNDC");
    labeA3->AddText(make_constChar(find_mean(graph_linear_thresh)));
    labeA3->Draw();

    c3->Print("Linear_Thresholds_" + file_name);
    c3->cd();

    TCanvas *c4 = new TCanvas("c4", "Noise-thresh", 1000, 600);
    c4->cd(1);
    graph_noise_thresh->SetMinimum(0);
    construct_graph(graph_noise_thresh, "Noise Thresholds", "pixel_number", "Noise Threshold", 37, 4000);
    // graph_gaus_thresh->SetMinimum()

    TLine *tl4 = new TLine();
    tl4->SetLineColor(kBlack);
    tl4->SetLineWidth(1);
    tl4->SetLineStyle(10);
    tl4->DrawLine(0, find_mean(graph_noise_thresh), 70, find_mean(graph_noise_thresh));

    TPaveText *labeA4 = new TPaveText(0.15, 0.20, 0.4, 0.29, "brNDC");
    labeA4->AddText(make_constChar(find_mean(graph_noise_thresh)));
    labeA4->Draw();

    c4->Print("Noise_Differences_" + file_name);
    c4->cd();

    TCanvas *c5 = new TCanvas("c5", "Gaus From Noise", 1000, 600);
    c5->cd(1);
    graph_gaus_fromNoise->SetMinimum(-50);
    construct_graph(graph_gaus_fromNoise, "Gaus from Noise", "pixel_number", "Gaus - Noise", 35, 50);

    TLine *tl5 = new TLine();
    tl5->SetLineColor(kBlack);
    tl5->SetLineWidth(1);
    tl5->SetLineStyle(10);
    tl5->DrawLine(0, find_mean(graph_gaus_fromNoise), 70, find_mean(graph_gaus_fromNoise));

    TPaveText *labeA5 = new TPaveText(0.15, 0.20, 0.4, 0.29, "brNDC");
    labeA5->AddText(make_constChar(find_mean(graph_gaus_fromNoise)));
    labeA5->Draw();
    c5->Print("Gaus_from_Noise_" + file_name);
    c5->cd();

    TCanvas *c6 = new TCanvas("c6", "Lin from Noise", 1000, 600);
    c6->cd(1);
    graph_lin_fromNoise->SetMinimum(-50);
    construct_graph(graph_lin_fromNoise, "Linear from Noise", "pixel_number", "Linear - Noise", 36, 50);

    TLine *tl6 = new TLine();
    tl6->SetLineColor(kBlack);
    tl6->SetLineWidth(1);
    tl6->SetLineStyle(10);
    tl6->DrawLine(0, find_mean(graph_lin_fromNoise), 70, find_mean(graph_lin_fromNoise));

    TPaveText *labeA6 = new TPaveText(0.15, 0.20, 0.4, 0.29, "brNDC");
    labeA6->AddText(make_constChar(find_mean(graph_lin_fromNoise)));
    labeA6->Draw();
    c6->Print("Linear_from_Noise_" + file_name);
    c6->cd();
}
