{
  //get the ntuple you want
  TFile* f = new TFile("2018_12_13_Sr90_Tranloc_Ch1_2_3_4_OR.root", "title");
  TCanvas *c1 = new TCanvas("c1","c1",1500,500);
  TNtuple* ntup = (TNtuple*)f->Get("ntuple");
  c1->Divide(3,1);

  gStyle->SetPalette(1, 0);
  gPad->SetMargin(0.1, 0.16, 0.1, 0.1);      
  gPad->Modified();
  gPad->Update();

  c1->cd(1);
  ntup->Draw("amplVar1", "amplVar2");

  c1->cd(2);
  ntup->Draw("max0", "max1");

  c1->cd(3);
  ntup->Draw("max2", "max3");
  
  c1->SaveAs("ntup.png");      
  
}
