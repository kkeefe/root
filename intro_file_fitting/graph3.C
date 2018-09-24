//this is going to graph a gausssian distributation function

{

  //create a new graph object
  g3 = new TGraph();

  //set the new graph parameters and title.
  g3->SetMarkerStyle(22);
  g3->SetName("First macro Data Fit");
  g3->SetMarkerColor(kBlue);

  //this sets 1000 different points to add to the graph.
  for(int i = 0; i < 1000; i++){

    //gRandom picks random # everytime. gRandom->Gaus("mean", "STD");
    g3->SetPoint(i, gRandom->Uniform(-5, 5), gRandom->Gaus(5, 1));

  }

  
  g3->Draw();

}
