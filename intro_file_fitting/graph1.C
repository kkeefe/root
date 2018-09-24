//this is an intro the graphing macro

{
  g = new TGraph("graph_fit.txt");
  g->SetMarkerStyle(21);
  g->SetLineColor(kRed);
  g->SetTitle("Data plot, first attempt; GigaW; Ksec");
  g->Draw("APL");
  
}
