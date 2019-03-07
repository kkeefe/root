
void fill_hist_from_file(){

    TFile *f = new TFile("root_file_name.root");
	TNtuple *ntup1 = (TNtuple *)f->Get("ntup1");

    int entries = ntup1->GetEntries();

    //set your branch addresses
    float_t DSP_Card, DSP_Chan, Reg, Thresh, Scalar;
    ntup1->SetBranchAddress("DSP_Card", &DSP_Card);
    ntup1->SetBranchAddress("DSP_Chan", &DSP_Chan);
    ntup1->SetBranchAddress("Reg", &Reg);
    ntup1->SetBranchAddress("Thresh", &Thresh);
    ntup1->SetBranchAddress("Scalar", &Scalar);

    //create your own histogram
    int bin_count(30);
    int x_min(0), x_max(6000);
    TH1 *hist1 = new TH1I("hist_1", "ntup1 hist", bin_count, x_min, x_max);    

    //ntup1->Draw("Thresh>>hist1");

    for(int i = 0; i < entries; ++i){
        ntup1->GetEntry(i);
        //cout << Reg << "\t" << entries << "\t" << i << "\t" << Scalar << "\t" << Thresh << endl;
        if (Reg == 111) {
            hist1->Fill(Scalar);
            //cout << "iterating.. \n";
        }
        
    }

    hist1->Draw();

}