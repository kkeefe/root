{

  //make sure that you keep only one version of the f1 uncommented..
  //this allows for multiple plots to be put into the same macro
  c1 = new TCanvas("c1", "Canvas name", 500, 500);
  
  // c1->cd(1); //selects where you're going to draw on your canvas
  // // lets try something like a wein displacement function.. (inspired via qual prep)
  // f1 = new TF1("f", "place your function here with x are the variable", 0, 10); domain of x: 0 to 10
  // f1->SetLineColor(kGreen -3); //pic a color you want
  // f1->Draw();
  // f1->SetTitle("Title of the Graph; Y-Axis name (unit); X-axis name (unit)");

  //this is the information that is set for the first formula
  c1->cd(1);
  f1 = new TF1("f", "10*(1-x/2.4)^2", 0, 2.4);
  f1->SetLineColor(kGreen -3);
  f1->Draw();
  f1->SetTitle("I_d vs V_gs; V_gs (-V); I_d (mA)");

  // //feel free the play with additional examples of 1-D functions you'd like to see:
  // c1->cd(1);
  // // lets try something like a wein displacement function.. (inspired via qual prep)
  // f1 = new TF1("f", "x^3/(e^x-1)", 0, 10);
  // f1->SetLineColor(kGreen -3);
  // f1->Draw();
  // f1->SetTitle("Probability Density of a Photon; energy (w); U(w) (w)");

  // current errors here.. there is something wrong with root trying to parse the Log function..
  // //Helmholtz free energy of a photon gas
  // c1->cd(1);
  // f1 = new TF1("f", "x^2*TMath::LogE(1-e^(x))", 0, 10);
  // f1->SetLineColor(kGreen -3);
  // f1->Draw();
  // f1->SetTitle("Probability Density of a Photon; energy (w); U(w) (w)");

}
