/*  
here I include generic descriptors on styling of the outputs of what you might want 
to include in your graphs or histograms..

Also included is an example of including error points on your graph

*/

{
  // // most common aesthetic change is gStyle
  // gStyle->SetOptStat(1111111); // draws statistics on the plots
  // gStyle->SetOptFit(1111);     //includes a fit on the graph
  // gStyle->SetPalette(57);

  // Define the canvas you want to draw on..
  Canvas = new TCanvas("canvas name", "multigraph", 700, 500);
  Canvas->SetGrid();

  //define the first graph you want to add
  // define the data:
  const int n_points = 10;;  // number of data points you wish to graph
  double x1_value[n_points], x2_value[n_points]; // x and y values you're going to graph..
  double y1_value[n_points], y2_value[n_points];
  // don't forget to include the errors you want to plot..
  double x1_error[n_points], x2_error[n_points];
  double y1_error[n_points], y2_error[n_points];

  // fill some of the data in any way you want.
  for(int i = 0; i < n_points; ++i){
    x1_value[i] = i; 
    y1_value[i] = x1_value[i]*2;
    x1_error[i] = 0.5*i;
    y1_error[i] = 0.5*y1_value[i];
    // fill the second graph..
    x2_value[i] = i; 
    y2_value[i] = x2_value[i]*2 + 1;
    x2_error[i] = 0.5*i;
    y2_error[i] = 0.5*y2_value[i];    
  }

  // including graph errors you may want to include
  graph1 = new TGraphErrors (n_points, x1_value, y1_value, x1_error, y1_error);
  graph1->SetMarkerColor(kGreen);
  graph1->SetMarkerStyle(19);
  graph1->SetMarkerStyle(kOpenCircle);
  // graph 2 is pretty much identical, but you probably want to have a different color..
  graph2 = new TGraphErrors (n_points, x2_value, y2_value, x2_error, y2_error);
  graph2->SetMarkerColor(kRed);
  graph2->SetMarkerStyle(20);
  graph2->SetMarkerStyle(kOpenCircle);
  
  // standard procedure before creating a graph..
  multigraph = new TMultiGraph ("MultiGraph Name","MultiGraph Title");
  multigraph->SetTitle("Input the Title of the Graph You Want");
  multigraph->Add(graph1);
  multigraph->Add(graph2);  
  multigraph->Draw("APL");
  multigraph->GetXaxis()->SetTitle("X axis title here");
  multigraph->GetYaxis()->SetTitle("Y axis title here");

  Canvas->Draw();

}
