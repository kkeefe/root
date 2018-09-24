//advanced graph fitting attempt

{
  //set the new graph
  g5 = new TGraph();

  //declare the parameters of the graph.
  double x, y;

  //create iteration of data points
  for(int i = 0; i<300; i++){
    x = 0.5*i;
    y = 2*cos(x)+gRandom->Uniform(-1, 1);
    g5->SetPoint(i, x, y);
  }

  //create the function to attempt to the fit the data
  f = new TF1("f", "[0]*cos([1]*x+[2])+[3]", 0, 5);
  f->SetParNames("Amplitude", "period","Phase","Translation");

  //create a guess of each of the values
  f->SetParameters(2,1,0,0.1);
  
  //attempt to fit the function
  g5->Fit(f);

  //don't forget to draw the function!
  g5->Draw("APC");
  
}
