// need to define a histogram to fit a function too..
// needs to be called on some TTree file and fill a histogram from that tree..

//the three external values that this function needs is: tree name, parameter name, and possibly output file name for STD data..

void triple_fit_test() {

  TTree *tree = myTree;
  ULong64_t nentries = tree->GetEntries();
  double g1_temp_par1, g1_temp_par2, g1_temp_par3;
  double g2_temp_par1, g2_temp_par2, g2_temp_par3;

  Float_t X_values;
  tree->SetBranchAddress("X_Values", &X_values);
  
  TH1D* hist_1 = new TH1D("hist_1","#Delta t",300,-1.0,1.0);
  hist_1->GetYaxis()->SetTitle("y_axis");
  hist_1->GetXaxis()->SetTitle("x_axis");
  
  for(int i = 0; i < nentries; ++i){
    tree->GetEntry(i);
    hist_1->Fill(X_values);
  }
  
  TF1 *fGauss_1 = new TF1("fGauss_1","gaus");
  hist_1->Fit("fGauss_1");
  g1_temp_par1 = fGauss_1->GetParameter(0);
  g1_temp_par2 = fGauss_1->GetParameter(1);
  g1_temp_par3 = fGauss_1->GetParameter(2);

  TF1 *fGauss_2 = new TF1("fGauss_2","[0]*exp(-pow((x-[1])/[2],2))",g1_temp_par2-2*g1_temp_par3,g1_temp_par2+2*g1_temp_par3);  hist_1->Fit("fGauss_2");
  fGauss_2 -> SetParameters(g1_temp_par1,g1_temp_par2,g1_temp_par3);
  fGauss_2 -> Update();
  fGauss_2 -> SetLineColor(7);
  hist_1->Fit("fGauss_2","R","",g1_temp_par2-2*g1_temp_par3,g1_temp_par2+2*g1_temp_par3);
  g2_temp_par1 = fGauss_2->GetParameter(0);
  g2_temp_par2 = fGauss_2->GetParameter(1);
  g2_temp_par3 = fGauss_2->GetParameter(2);

  TF1 *fGauss_3 = new TF1("fGauss_3","[0]*exp(-pow((x-[1])/[2],2))",g1_temp_par2-2*g1_temp_par3,g1_temp_par2+2*g1_temp_par3);
  fGauss_3 -> SetParameters(g2_temp_par1,g2_temp_par2,g2_temp_par3);
  fGauss_3 -> SetParNames("A","Mean","Sigma");
  fGauss_3 -> SetLineColor(6);
  hist_1 -> Fit("fGauss_3","R","",g1_temp_par2-2*g1_temp_par3,g1_temp_par2+2*g1_temp_par3);

  TCanvas *c1 = new TCanvas ("c1","hist_1",1000,600);
  c1->cd(1);
  gStyle->SetOptStat(1111);
  hist_1->Draw();
  c1->SaveAs("hist_1_.pdf");
  c1->cd();

}
