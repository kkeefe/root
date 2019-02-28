{

  TFile *f = new TFile("NtupleRandom.root","RECREATE","first_ntuple");
  
  //declare the variables you will read from;
  double x, y;
  TTree *ntup = new TTree("myTree","A ROOT tree");

  /* ntup->Branch("Branch_Name", &variable_address, "variable/type:separated:by_colons"); */

  ntup->Branch("X_values", &x, "x_axis/D");
  ntup->Branch("Y_values", &y, "y_axis/D");
  
  for(int i = 0; i < 100000; ++i){
    x = i;
    y = gRandom->Gaus(5, 1);
    ntup->Fill();
  }
  

  //write the ntuple and close the file
  ntup->Write();
  TCanvas *c1 = new TCanvas("c1", "ntuples", 700, 600);
  ntup->Draw("X_values:Y_values");  
}
