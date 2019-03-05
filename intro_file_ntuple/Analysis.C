void Analysis(string &input){
  //get the ntuple you want
  TFile* f = new TFile("Analysis.root", "title");
  TCanvas* c1 = new TCanvas("c1", "  ");

  cout << input << "\n";

  TNtuple* ntup = (TNtuple*)f->Get("NTuple3");
  ntup->Scan();
}
