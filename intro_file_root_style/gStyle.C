/*  
here I include generic descriptors on styling of the outputs of what you might want 
to include in your graphs or histograms..

Also included is an example of including error points on your graph

*/

#include "TLegend.h"
#include "TROOT.h"
#include "TGraphErrors.h"

{

  // most common aesthetic change is gStyle
  gStyle->SetOptStat(1111111); // draws statistics on the plots
  gStyle->SetOptFit(1111);     //includes a fit on the graph
  gStyle->SetPalette(57);
  Canvas->SetGrid();

  // Define the canvas you want to draw on..
  Canvas = new TCanvas();

  // define the data:
  const int n_points = 10;;  // number of data points you wish to graph
  double x_value[n_points]; // x and y values you're going to graph..
  double y_value[n_points];
  // don't forget to include the errors you want to plot..
  double x_error[n_points];
  double y_error[n_points];

  // fill some of the data in any way you want.
  for(int i = 0; i < n_points; ++i){
    x_value[i] = i; 
    y_value[i] = x_value[i]*2;
    x_error[i] = 0.5*i;
    y_error[i] = 0.5*y_value[i];    
  }

  // including graph errors you may want to include
  graph = new TGraphErrors (n_points, x_value, y_value, x_error, y_error);
  // note that TGraphErrors in this function call requires double* calls
  graph->SetTitle("Input the Title of the Graph You Want");
  // each letter has its own condition: A-Axes P-Colors E-Error bars
  graph->SetMarkerColor(kGreen);
  graph->SetFillColor(0);
  graph->SetMarkerStyle(kOpenCircle);
  graph->GetXaxis()->SetTitle("X axis title here");
  graph->GetYaxis()->SetTitle("Y axis title here");

  // make sure that you draw the graph clone after you've set all the values you want..
  graph->DrawClone("APE"); //Draw Clone utilizes options, and prevents the need for drawing on a canvas
  
  // see into_file_fitting for more detail on the functions and parameter fitting..
  straight_line = new TF1("line_fit", "[0]*x+[1]", 0,10);
  straight_line->SetLineColor(kBlue);
  graph->Fit(straight_line);
  straight_line->DrawClone("Same");

  // Create a legend you want to add to your graph
  legend = new TLegend(.1, .7, .3, .9, "legend header");
  legend->SetFillColor(0);
  legend->AddEntry(graph, "graph");
  legend->AddEntry(straight_line, "fitted line");
  legend->DrawClone("Same");

  // put the name of the pdf or png file you want to create here
  Canvas->Print("pretty_graph.pdf");
  
  
}
