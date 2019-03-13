//call this guy in batch motch with root -l -q -b "create_root.cc(\"file_name\")" 
void create_root(const char * file){

    //can use this macro to create any root file of an ntup that you wish..
    
    //use this to define any ntuple you want and to parse it's data directly from an ASCII file
    //name, title, columns of information or branches for the Ntuple..
    TNtuple ntup1("ntup1", "ntup1", "DSP_Card:DSP_Chan:Reg:Thresh:Scalar");
    ntup1.ReadFile(file);

    TString file_string = file;
    int size = file_string.Sizeof();
    file_string.Remove(size - 4, 4);
    file_string.Append("root");
    const char* output_file = file_string;    

    //create and save your own rootfile from this text:
    TFile *f = new TFile (output_file, "RECREATE");
    f->cd();
    ntup1.Write();
    f->Close();

}