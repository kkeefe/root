{
  //this program still works like any C program you would expect
  cout << "hello world" << endl;

  //this allows for multiple plots to be put into the same macro
  c1 = new TCanvas("c1", "Canvas name", 500, 500);

  //this is the information that is set for the first formula
  c1->cd(1);
  f1 = new TF1("f", "sin(x)/x", -10, 10);
  f1->SetLineColor(kGreen -3);
  f1->Draw();
  f1->SetTitle("graph title; y (y); x (x)");

  //the integral function takes only two parameters of the function you're integrating over..
  double int_f1 = f1->Integral(-10, 10);  
  cout << "value of the integral is: " << int_f1 << endl;
  
}
