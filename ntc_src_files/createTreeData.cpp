#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "TTree.h"
#include "TFile.h"

using namespace std;
//class ifstream;

// Converts an int to a string
string int_to_string(int integer) {
  ostringstream stst;
  stst << integer;
  return stst.str();
}

void createtree( char* infilename, char* outfilename ) {

  // Macro to read data from an ascii file and create a root file with a TTree
  //  gROOT->Reset();

  // open file
  ifstream infile;
  infile.open(infilename);

  //*******Creating the name of each variable**************
  std::vector<std::string> var_names;
  var_names.push_back("EventNumber");
  var_names.push_back("boardId");
  var_names.push_back("channel");
  var_names.push_back("GetTriggerCell");
  var_names.push_back("motorPosition");
  var_names.push_back("Ref");
  var_names.push_back("GetTemperature");
  for(int i = 7 ; i < 1031; i++){ 
    var_names.push_back("signal"+int_to_string(i));
  }

  //print var_names:
  //for(unsigned int i = 0; i < var_names.size(); i++) {
  //    cout << var_names[i] << endl;
  //}

  //*******************************************************


  // declare vector to contain floating point variables and initialize to zero
  std::vector<float> variables;
  variables.resize(var_names.size(), 0);

  // create a TTree
  TTree *tree = new TTree("T",infilename);

  // create tree branches 
  //  for ( unsigned int i=0; i<var_names.size(); ++i ) {
  //    std::string format = var_names[i]+"/F";
  //    tree->Branch(var_names[i].c_str(),&(variables[i]),format.c_str());
  //  }


  //Create branches for the headers
  for ( unsigned int i=0; i<7; i++ ) {
    std::string format = var_names[i]+"/F";
    tree->Branch(var_names[i].c_str(),&(variables[i]),format.c_str());
  }

  //Signal vector
  std::vector<float> vpx;
  tree->Branch("vpx",&vpx);

  vpx.clear();

  // fill the tree from the values in ASCII file 
  unsigned int i=0;
  //  unsigned int k=0;
  while ( !infile.eof() ) {
    infile >> variables[i];
    i++;
    //    std::cout<<variables[i]<<" i:"<<i<<"  k:"<<k<<" Outside the if sentence"<<std::endl;

    //     if ((i>6) && (i< var_names.size()) && (k>0)){
    //	std::cout<<variables[i]<<" i:"<<i<<"  k:"<<k<<std::endl;
    //        vpx.push_back(variables[i]);}
    


    // reset i and write variables to tree
    if ( i == var_names.size() ) {
      for ( unsigned int k=7; k<var_names.size(); ++k){
	//                  std::cout<<var_names[k]<<"="<<variables[k]<<std::endl;
	vpx.push_back(variables[k]);
      }
      //            for ( unsigned int j=0; j<var_names.size(); ++j ) std::cout << var_names[j] << "=" << variables[j] << " ";
      //            std::cout << std::endl;
      //      k++;
      tree->Fill();
      vpx.clear();
      i=0;
    }
  }  

  // create a new ROOT file and write TTree into it
  TFile *outfile = new TFile(outfilename,"RECREATE");
  tree->Write();
  tree->Print();

  // close files
  infile.close();
  outfile->Close();

  return;
}

int main(int argc, char* argv[]) {

  if (argc == 2 && std::string(argv[1])=="-h") {
    std::cout << std::endl;
    std::cout << "TEXT2TREE -- RG,9 Oct.2009" << std::endl;
    std::cout << std::endl;
    std::cout << "createtree reads formatted data from an ASCII file and writes it as a ROOT TTree" << std::endl;
    std::cout << "Input file format: " << std::endl;
    std::cout << "First line: variable names separated by one or more spaces" << std::endl;
    std::cout << "Other lines: variable values in columns (as many as variable names)" << std::endl;
    std::cout << std::endl;
    std::cout << "usage: createtree [input file] [root file]" << std::endl;
    std::cout << std::endl;

  } else if (argc == 3) {
    std::cout << std::endl;
    std::cout << "createtree: reading ASCII file " << argv[1] << " and writing ROOT file " << argv[2] << std::endl;
    std::cout << std::endl;
    createtree( argv[1], argv[2] );

  } else {
    std::cout << "ERROR: two arguments required; do createtree -h" << std::endl;
    return 1;
  }

  return 0;
}

