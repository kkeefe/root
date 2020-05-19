//call this guy in batch motch with root -l -q -b "create_root.cc(\"file_name\")" 
void create_root(const char * file){

    //can use this macro to create any root file of an ntup that you wish..
    // the format of the .txt file assumes that the first line is tabbed with the headers of each column in the correct order..
    
    //use this to define any ntuple you want and to parse it's data directly from an ASCII file
    //name, title, columns of information or branches for the Ntuple..
    ifstream file_input(file);
    string header_line;
    getline(file_input, header_line);
    
    // get each word from the string and use that as the argument list of the ntuple..
    stringstream ss(header_line);
    string header_word;
    vector<string> element_names;
    while(ss >> header_word){
	   element_names.push_back(header_word);
    }
    
    // put colons in between all of the element names..
    string ntup_args;
    for(auto item : element_names){
	    if(ntup_args==""){
		    ntup_args = item;
	    }else
	     ntup_args += ":" + item;
    }
    
    // make the ntuple and read the rest of the file
    cout << "making arguments: " << ntup_args.c_str() << endl;
    TNtuple ntup1("ntup0", "ntup0", ntup_args.c_str());
    ntup1.ReadStream(file_input);

    // change the name of the output file from .txt to .root
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
