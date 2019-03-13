//call this guy in batch motch with root -l -q -b "create_root.cc(\"file_name\")" 
void create_root(const char * file){

    //can use this macro to create any root file of an ntup that you wish..
    
    //use this to define any ntuple you want and to parse it's data directly from an ASCII file
    //name, title, columns of information or branches for the Ntuple..
    TNtuple ntup1("ntup1", "ntup1", "DSP_Card:DSP_Chan:Reg:Thresh:Scalar");
    ntup1.ReadFile(file);

    string file_output_name = file - ".txt" + ".root";

    //create and save your own rootfile from this text:
    TFile *f = new TFile (file_output_name.c_str(), "RECREATE");
    f->cd();
    ntup1.Write();
    f->Close();

}