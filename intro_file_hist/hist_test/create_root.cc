void create_root(){

    //can use this macro to create any root file of an ntup that you wish..
    
    //use this to define any ntuple you want and to parse it's data directly from an ASCII file
    //name, title, columns of information or branches for the Ntuple..
    TNtuple ntup1("ntup1", "ntup1", "DSP_Card:DSP_Chan:Reg:Thresh:Scalar");
    ntup1.ReadFile("threshold_scan.dat");

    //create and save your own rootfile from this text:
    TFile *f = new TFile ("root_file_name.root", "RECREATE");
    f->cd();
    ntup1.Write();
    f->Close();

}