// requires strings:

/* need to supply the following:
1) .dat title
2) graph title
3) x_axis title
4) y_axis title
 */
void example_macro(){
  printf("hi there..\n");
}

void graph_errors(const char *dat_title, const char *x_axis, const char *y_axis){

  //  cout << param << endl;
  TCanvas *c = new TCanvas("c",dat_title,200,10,700,500);
  c->SetGrid();
  TGraph *g= new TGraphErrors(dat_title);
  TAxis *axis = g-> GetXaxis();
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(0);
  
  TF1 *line = new TF1("line","pol0",-5,5);
  line -> SetLineColor(2);
  g-> Fit("line","R","", -5,5);

  g-> SetMarkerColor(kBlack);
  g-> SetMarkerStyle(21);
  g-> Draw("APL");

  g-> SetTitle(dat_title);
  g-> GetYaxis() -> SetTitle ("#rho");
  gStyle->SetOptFit(1111);
  g-> GetXaxis() -> SetTitle (x_axis);
  g -> GetYaxis() -> SetTitleOffset(0.65);
  g -> GetYaxis() -> SetTitleSize(0.06);
  g -> GetXaxis() -> SetTitleOffset(0.7);
  g -> GetXaxis() -> SetTitleSize(0.06);
  gStyle -> SetOptFit();
  TPaveStats *st = (TPaveStats*)g->FindObject("stats");
  st->SetX1NDC(0.6); //new x start position
  st->SetX2NDC(0.9); //new x end position
  st->SetY1NDC(0.85); //new y start position
  st->SetY2NDC(0.95); //new y end posit
  c->Print(dat_title);
  
}
