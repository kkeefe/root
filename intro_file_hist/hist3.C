//create a histogram generating random integers to fill between 1 and 6
//additional way of recording data by writing data from the output.
{

  //this allows for multiple plots to be put into the same macro
  c1 = new TCanvas("c1", "Canvas name", 1500, 500);
  c1->Divide(3,1);


  //create two competing histograms
  h1 = new TH1I("h1", "Dice Values", 6, 1, 7);
  h2 = new TH1I("h2", "Dice Values 2", 6, 1, 7);
  h3 = new TH1I("h3", "Dice Values Sumed", 11, 2, 13);
  
  //fill them with random integers
  for(int i = 0; i < 10000; i++){
    int x, y;
    x =  gRandom->Integer(6);
    y =  gRandom->Integer(6);
    h1->Fill(x+1);
    h2->Fill(y+1);
    h3->Fill(x+y+2);
  }


  //error happens when a mimimum is set for a histogram before filling them..
  //make sure the base of the histogram is zero
  h1->SetMinimum(0);
  h2->SetMinimum(0);

  // //set a style of how much info you want to see from the histogram, more 1's more info...
  //gStyle->SetOptStat("random number of 1's)
  
  //draw the first histogram
  c1->cd(1);
  h1->Draw();

  //draw the second
  c1->cd(2);
  h2->Draw();

  //draw the third
  c1->cd(3);
  h3->Draw();

  //to get # of bins use the member function: ::GetNbins
  cout << "Counts for sum of the two dice" << endl;
  cout << "entry # \t #counts:  \t bin center: \n";
  for(int i=1; i<=h3->GetNbinsX(); i++){
    cout << i+1 << "\t \t  " << h3->GetBinContent(i) << "\t  \t \t" <<  h3->GetBinCenter(i) << endl;
  }
 
  
}
