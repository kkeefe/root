{
  //get the ntuple you want
  TFile* f = new TFile("Analysis.root", "title");
  TCanvas* c1 = new TCanvas("c1", "  ");

  TNtuple* ntup = (TNtuple*)f->Get("NTuple3");
  ntup->Scan();
}
