{

   //this allows for multiple plots to be put into the same macro
  c1 = new TCanvas("c1", "Canvas name", 500, 500);
  
  //this is the information that is set for the first formula
  c1->cd(1);
  f1 = new TF1("f", "10*(1-x/2.4)^2", 0, 2.4);
  f1->SetLineColor(kGreen -3);
  f1->Draw();
  f1->SetTitle("I_d vs V_gs; V_gs (-V); I_d (mA)");


}
