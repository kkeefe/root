{

  //declare the variables you will read from;
  int x, y;
  TNtuple ntup("first", "title", "X:Y");
  TCanvas *c1 = new TCanvas("c1", "ntuples", 1500, 500);
  c1->Divide(3,1);
  
  for(int i = 0; i < 10; ++i){
    x = i;
    y = i*i;
    ntup.Fill(x,y);
  }
  

  //write the ntuple and close the file
  ntup.Write();

  c1->cd(1);
  ntup.Draw("X:Y");
  ntup.Draw("Y");
  ntup.Draw("X");
  
  c1->cd(2);
  ntup.Draw("Y:X");
  ntup.Draw("Y");

  c1->cd(3);
  ntup.Draw("Y/X:X", "Y");
  ntup.Draw("Y");
  
}
