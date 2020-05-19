#include <TROOT.h>
#include "TCanvas.h"
#include "TGraph.h"

void threshScan32Bit(const char *file)
{
  TFile *f = new TFile(file);
  TNtuple *ntup0 = (TNtuple *)f->Get("ntup0"); // ntup without the data - 3 elements..
  int pixelNum = 46;

  //set your branch addresses
  float_t pixel, thresh, count_val;
  ntup0->SetBranchAddress("pixel", &pixel);
  ntup0->SetBranchAddress("thresh", &thresh);
  ntup0->SetBranchAddress("count_val", &count_val);

  // create a new graph object
  TGraph *g0 = new TGraph(); // use for raw data graph
  TGraph *g1 = new TGraph(); // going to use this to plot the slope of the points..
  TGraph *g2 = new TGraph(); // going to use this for the total sum..

  // the current point we're plotting
  int point(0);
  float_t prev_count, running_sum;

  for (int i = 0; i < ntup0->GetEntries(); ++i)
  {
      // look at every entry to see if it's good..
      ntup0->GetEntry(i);
      // make sure you're only looking at the pixel you want..
      if(pixel == pixelNum){
          point++;
          double slope = count_val - prev_count;
          running_sum += count_val;
          g0->SetPoint(point, thresh, count_val); // fill the graphs..
          g1->SetPoint(point, thresh, slope);
          g2->SetPoint(point, thresh, running_sum);
          prev_count = count_val;
      }
  }

////////////////////////////// graph stuff //////////////////////////////

TCanvas *c1 = new TCanvas("c1", "Canvas name", 2100, 600);

// first canvas
c1->Divide(3, 1);
c1->cd(1);
c1->GetPad(1)->SetLogy();
g0->SetName("title 0");
g0->SetMarkerColor(39);
g0->SetMinimum(0);
g0->SetFillColor(38);
g0->Draw("APL");
g0->GetXaxis()->SetTitle("thresh value");
g0->GetYaxis()->SetTitle("total count");
g0->GetXaxis()->CenterTitle();
g0->GetYaxis()->CenterTitle();
TLegend *legend = new TLegend(.15, .65, .4, .9, "");
legend->AddEntry(g0, "scaler count vs. threshold");
legend->DrawClone("Same");
legend->Draw("");

// second canvas
c1->cd(2);
g1->SetName("title 1");
g1->SetMarkerColor(40);
g1->SetMinimum(0);
g1->SetFillColor(38);
g1->GetXaxis()->SetTitle("thresh value");
g1->GetYaxis()->SetTitle("point to point slope");
g1->Draw("APL");

// third canvas
c1->cd(3);
c1->GetPad(3)->SetLogy(1);
g2->SetName("title 2");
g2->SetMarkerColor(41);
g2->SetMinimum(0);
g2->SetFillColor(38);
g2->GetXaxis()->SetTitle("thresh value");
g2->GetYaxis()->SetTitle("total sum of counts");
g2->Draw("APL");

//begin saving the file stuff you want to save..
string file_name(file);
string count = std::to_string(pixelNum);
file_name = count + file_name;

//create the file name you want, and of course root doesn't make it easy.
TString file_string = file_name;
int size = file_string.Sizeof();
file_string.Remove(size - 5, 4);
file_string.Append("png");
const char *output_file = file_string;
c1->SaveAs(output_file);

}
