#include <TROOT.h>
#include "TCanvas.h"
#include "TGraph.h"
#include "TMultiGraph.h"

//one line method of constructing a graph and settings title / axis values.. will change graph passed to it as argument..
void construct_graph(TGraph *g1, const char *title, const char *x_axis, const char *y_axis, int x_min, int x_max)
{
  g1->SetName(title);
  g1->SetMarkerColor(39);
  g1->SetMaximum(80000);
  g1->SetMinimum(0);
  // g1->GetXaxis()->SetTitle(x_axis);
  // g1->GetYaxis()->SetTitle(y_axis);
  g1->SetFillColor(38);
  // g1->GetXaxis()->CenterTitle();
  // g1->GetYaxis()->CenterTitle();
  //g1->GetXaxis()->SetRangeUser(x_min, x_max);
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
pair<double_t, double_t> find_max(vector<pair<double_t, double_t>> xy_points)
{

  double_t max_y(0);
  double_t x_point(0);

  for (auto c : xy_points)
  {
    if (c.second > max_y or -c.second < -max_y)
    { //make sure to check positive and negative ranges..
      max_y = c.second;
      x_point = c.first;
    }
  }
  return make_pair(x_point, max_y);
}

pair<double_t, double_t> find_thresh_and_diff_of_tg_diff(TGraph *tg, double_t thresh_val)
{

  double *x_points = tg->GetX();
  double *y_points = tg->GetY();

  double_t threshold_x;
  double_t difference;

  //this will find the first time the threshold is broken..
  for (int i = 0; i < tg->GetN(); i++)
  {
    if (y_points[i] > thresh_val)
    {
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

    // cout << "constant value: " << prev_p0
    //      << "\t Mean value: " << prev_p1
    //      << "\t Slope value: " << prev_p2
    //      << "\t range: " << x_min_p << " to " << x_max_p << endl;
  }
}

set<int> Register_Set = 
 {111, 113, 115, 109, 85, 117, 119, 121, 112, 114, 116, 77, 124, 118, 120, 122, 110, 82, 80, 79, 89, 87, 90, 92, 83, 78, 81, 84, 88, 86, 91, 123, 19, 47, 49, 48, 58, 56, 54, 59, 46, 51, 50, 45, 57, 55, 53, 22, 18, 16, 14, 20, 60, 28, 26, 24, 17, 15, 13, 52, 21, 27, 25, 23};

// need to convert register information from the Lyso data to the noise measurement on the chanell..
// KEEP IN MIND that channel here actually refers to the pixel number minus 1!!
int conv_Reg(int reg_val)
{
  map<int, int> conv_reg_to_pixel = {
      {111, 1},
      {113, 2},
      {115, 3},
      {109, 4},
      {85, 5},
      {117, 6},
      {119, 7},
      {121, 8},
      {112, 9},
      {114, 10},
      {116, 11},
      {77, 12},
      {124, 13},
      {118, 14},
      {120, 15},
      {122, 16},
      {110, 17},
      {82, 18},
      {80, 19},
      {79, 20},
      {89, 21},
      {87, 22},
      {90, 23},
      {92, 24},
      {83, 25},
      {78, 26},
      {81, 27},
      {84, 28},
      {88, 29},
      {86, 30},
      {91, 31},
      {123, 32},
      {19, 33},
      {47, 34},
      {49, 35},
      {48, 36},
      {58, 37},
      {56, 38},
      {54, 39},
      {59, 40},
      {46, 41},
      {51, 42},
      {50, 43},
      {45, 44},
      {57, 45},
      {55, 46},
      {53, 47},
      {22, 48},
      {18, 49},
      {16, 50},
      {14, 51},
      {20, 52},
      {60, 53},
      {28, 54},
      {26, 55},
      {24, 56},
      {17, 57},
      {15, 58},
      {13, 59},
      {52, 60},
      {21, 61},
      {27, 62},
      {25, 63},
      {23, 64}};
  int pixel = conv_reg_to_pixel.at(reg_val);
  //numbering of the pixels is offset by 1..
  return pixel - 1;
}

void fill_hist_from_file(const char *file)
{

  TFile *f = new TFile(file);
  TNtuple *ntup0 = (TNtuple *)f->Get("ntup0"); // ntup without the data - 3 elements..
  TNtuple *ntup1 = (TNtuple *)f->Get("ntup1"); // ntup with the data - 5 elements

  //set your branch addresses
  float_t DSP_Card, DSP_Chan, Reg, Thresh, Scalar, Prev_Scalar;
  ntup1->SetBranchAddress("DSP_Card", &DSP_Card);
  ntup1->SetBranchAddress("DSP_Chan", &DSP_Chan);
  ntup1->SetBranchAddress("Reg", &Reg);
  ntup1->SetBranchAddress("Thresh", &Thresh);
  ntup1->SetBranchAddress("Scalar", &Scalar);
  //define the other ntuple.. no source on ntup0..
  float_t Channel, Thresh0, Scalar0;
  ntup0->SetBranchAddress("Thresh", &Thresh0);
  ntup0->SetBranchAddress("Scalar", &Scalar0);
  ntup0->SetBranchAddress("Channel", &Channel);

  //define register iteration here..
  const int max_register(125);
  //for (int Reg_I_Want = 13; Reg_I_Want < max_register; Reg_I_Want++)
  for (int Reg_I_Want : Register_Set)
  {

    cout << "looking for: " << Reg_I_Want << endl;
    //create a new graph object
    TGraph *g1 = new TGraph();
    TGraph *g2 = new TGraph();

    TGraph *g0 = new TGraph(); // to be used for the "no - src" ntuple runs..

    int point(0);
    int point0(0);
    bool fill(false); //don't need to try to fill anything if the register number isn't found..
    vector<pair<Double_t, double_t>> max_thresh_slope;
    //get the information for the ntup1
    for (int i = 0; i < ntup1->GetEntries(); ++i)
    {
      ntup1->GetEntry(i);
      if (Reg == Reg_I_Want) //fill only for the desired register..
      {
        point++;
        double slope = Scalar - Prev_Scalar;
        g1->SetPoint(point, Thresh, Scalar);
        g2->SetPoint(point, Thresh, slope);
        Prev_Scalar = Scalar;
        max_thresh_slope.push_back(make_pair(Thresh, slope));
        fill = true;
      }
    }

    cout << "Thresh0 " << Thresh0 << "\t point0: " << point0 << "\t Scalar0: " << Scalar0 << endl;
    //set a fill method for ntup0
    for (int i = 0; i < ntup0->GetEntries(); i++)
    {
      ntup0->GetEntry(i);
      if (Channel == conv_Reg(Reg) and fill)
      {
        point0++;
        g0->SetPoint(point0, Thresh0, Scalar0);
        fill = true;
      }
    }

    int point2(0);
    //will use tg_diff to identify where the threshold_xy value should be placed..
    if (fill == true)
    {
      cout << "found a fill at: " << Reg_I_Want << endl;
      TGraph *tg_diff = new TGraph();
      //this method fills the tg_diff graph..
      iterate_fit(g1, 2900, 3700, 48, tg_diff, &point2);
      pair<Double_t, double_t> threshold_xy, slope_diff_xy;
      double_t threshold_val(550); //define a threshold value to look for in the difference graph..
      threshold_xy = find_thresh_and_diff_of_tg_diff(tg_diff, threshold_val);
      slope_diff_xy = find_thresh_and_diff_of_tg_diff(g2, threshold_val);

      TCanvas *c1 = new TCanvas("c1", "Canvas name", 2100, 600);
      // gStyle->SetOptStat(1111111); // draws statistics on the plots
      // gStyle->SetOptFit(1);
      // gStyle->SetPalette(57);

      c1->Divide(3, 1);
      c1->cd(1);
      // gStyle->SetStatX(0.5);
      // gStyle->SetStatY(0.9);
      c1->GetPad(1)->SetLogy();
      construct_graph(g1, "graph_1", "threshold", "Scalar_counts", 2900, 3700);
      construct_graph(g0, "graph_0", "threshold", "Scalar_counts", 2900, 3700);
      // g0->SetTitle("Noise_data");
      // g1->SetTitle("Source_data");
      g0->SetFillColor(40);
      g1->SetFillColor(38);
      // g1->Draw("ABQ");

      TMultiGraph *mg = new TMultiGraph("mg1", "Source and Noise");
      mg->SetTitle("Scaler Threshold Scans");
      mg->Add(g0);
      mg->Add(g1);
      mg->SetTitle("Noise and Source Scan; Threshold; Scaler Count");
      //mg->GetXaxis()->SetRangeUser(2900,3700);
      mg->Draw("ABQ");

      TLine *tl = new TLine();
      tl->SetLineColor(kRed);
      tl->SetLineWidth(2);
      tl->SetLineStyle(9);
      tl->DrawLine(threshold_xy.first, g1->GetMinimum(), threshold_xy.first, g1->GetMaximum());

      TLine *tl2 = new TLine();
      tl2->SetLineColor(kBlue);
      tl2->SetLineWidth(2);
      tl2->SetLineStyle(8);
      tl2->DrawLine(slope_diff_xy.first, g1->GetMinimum(), slope_diff_xy.first, g1->GetMaximum());
      TPaveText *labeA0 = new TPaveText(0.15, 0.20, 0.4, 0.29, "brNDC");
      labeA0->AddText(make_constChar(conv_Reg(Reg_I_Want)+1));
      labeA0->Draw();


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
      labeC->AddText(make_constChar(slope_diff_xy.first));
      labeC->Draw();
      TPaveText *labeD = new TPaveText(0.15, 0.80, 0.40, 0.89, "brNDC");
      labeD->AddText(make_constChar(slope_diff_xy.second));
      labeD->Draw();
      TPaveText *labeB3 = new TPaveText(0.15, 0.20, 0.4, 0.29, "brNDC");
      labeB3->AddText("linear-fit");
      labeB3->Draw();
      tl2->DrawLine(slope_diff_xy.first, g2->GetMinimum(), slope_diff_xy.first, g2->GetMaximum());

      //begin saving the file stuff you want to save..
      string file_name("_Channel_SiPM.txt");
      string count = std::to_string((conv_Reg(Reg_I_Want) + 1));
      file_name = count + file_name;

      //create the file name you want, and of course root doesn't mak it easy..
      TString file_string = file_name;
      int size = file_string.Sizeof();
      file_string.Remove(size - 5, 4);
      file_string.Append(".png");
      const char *output_file = file_string;
      c1->SaveAs(output_file);
    }
  }
}