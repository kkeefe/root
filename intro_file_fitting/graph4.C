//this is going to graph a gausssian distributation function

{

  //create a new graph object
  g4 = new TGraph();

  //set the new graph parameters and title.
  g4->SetMarkerStyle(22);
  g4->SetName("First macro Data Fit");
  g4->SetMarkerColor(kBlue);

  double x, y;
  //this sets 1000 different points to add to the graph.
  for(int i = 0; i < 100; i++){
    x = 0.25*i;
    y = 2*sin(x + 1) + gRandom->Uniform(-0.25, 0.25);
    g4->SetPoint(i, x, y);
  }

  //goal is to find a guessed fit function!
  //this fits a sine function using the three below parameters to adjust the 'guessed' fit
  //note that each [n] indicates the nth parameter.
  f = new TF1("f", "[0]*sin(x+[1])+[2]",0, 3.14159);
  f->SetParNames("Amplitude" , "Phase" , "Translation");

  //apply the fucntion, the argument of the function, must be a pointer to a function.
  g4->Fit(f);
  
  //note that L has been taken out to prevent a forced line fit 
  g4->Draw("AP");

}
