//this is the second example of a graphing function
//going to use a random number generator



{

  //create a new graph, and set the graph styles.
  g2 = new TGraph();
  g2->SetMarkerStyle(22);
  g2->SetName("First macro Data Fit");
  g2->SetMarkerColor(kBlue);

  //this is set to graph a series of cubic points from 0 to 10.
  for(int i = 0; i < 10; i++){
    g2->SetPoint(i, i, i*i*i);
  }

  //actually draw the graph. Include data points and form a line fit between the points
  g2->Draw("ALP");
  
}
