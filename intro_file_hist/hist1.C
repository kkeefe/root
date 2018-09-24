//first histogram root macro
//currently the two different histograms are filled using different random guassians.
//this is not quite an ideal comparison between different types of histograms.


{

  //this allows for multiple plots to be put into the same macro
  c1 = new TCanvas("c1", "Canvas name", 1000, 500);
  c1->Divide(2,1);

  //make sure that the drawing is happening on the correct canvas
  c1->cd(1);
  h1 = new TH1D("h1", "first histogram", 50, 0, 50);

  //basic fill of h1 with a random number.
  for(int i = 0; i < 5000; i++){
    h1->Fill(gRandom->Gaus(25,10));
  }

  //forces the bottom of the bins to be zero
  h1->SetMinimum(0);
  
  //place the first histogram on the first canvas
  h1->Draw();
  
  //place the canvas to the new position
  c1->cd(2);

  //double the bins of the second histogram to compare
  h2 = new TH1D("h2","Second histogram", 100, 0, 50);
  //basic fill of h1 with a random number.
  for(int i = 0; i < 5000; i++){
    h2->Fill(gRandom->Gaus(25,10));
  }

  //forces the bottom of h2 to be 0
  h2->SetMinimum(0);
  
  //be sure to also draw the second histogram!
  h2->Draw();
  
}
