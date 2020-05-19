#include "data_headers.hh"
#include "TFile.h"
#include "TTree.h"

// bologna test macro
int test(){

    TFile* tf = new TFile("crap.root", "RECREATE");
    TTree* tt = new TTree("tname", "tcrap");
    extype* b1 = new extype;
    int val;
    tt->Branch("branch1", &val);
    tt->Branch("branch2", &b1, 32000, 0);

    for(int i = 0; i < 5; i++)
    {
        val = i;
        extype bla = extype(i, i*i);
        b1 = &bla;
        b1->cprint();
        tt->Fill();
    }
    tt->Write();
    tf->Close();

    return 0;
}
