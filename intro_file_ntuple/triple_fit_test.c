// need to define a histogram to fit a function too..
// needs to be called on some TTree file and fill a histogram from that tree..

void triple_fit_test() {

  TTree *tree = myTree;

  Float_t X_values, Y_values;
  tree->SetBranchAddress("X_Values", &X_values);
  tree->SetBranchAddress("Y_Values", &Y_values);
  
  ULong64_t nentries = tree->GetEntries();
  
  TH1* hist_1 = new TH1I("hist_1","#Delta t",65,-4.0,5.0);
  hist_1->GetYaxis()->SetTitle("y_axis");
  hist_1->GetXaxis()->SetTitle("x_axis");

  double g1_temp_par1, g1_temp_par2, g1_temp_par3;

  for(int i = 0; i < nentries; ++i){

    tree->GetEntry(i);
    hist_1->Fill(X_values);
    
  }
  
  
  TF1 *fGauss_1 = new TF1("fGauss_1","gaus");
  hist_1->Fit("fGauss_1");
  g1_temp_par1 = fGauss_1->GetParameter(0);
  g1_temp_par2 = fGauss_1->GetParameter(1);
  g1_temp_par3 = fGauss_1->GetParameter(2);
  
  TCanvas *c1 = new TCanvas ("c1","hist_1",1000,600);
  c1->Divide(1,1);
  c1->cd(1);
  // gPad->SetLogy();
  // gStyle->SetOptStat(0);

  hist_1->Draw();
  fGauss_1->Draw();
  //c1 ->Print();
  c1->SaveAs("hist_1_.pdf");
  c1->cd();

  hist_1 -> Reset("ICESM");

}
