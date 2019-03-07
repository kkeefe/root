#include "trip_fit_main.hh"

//make sure that you pass this function the correct root value? 

// tree name, ntuple name

void StandAlone(int argc, char** argv){
  TFile *file = new TFile(argv[1]);  
  TTree *tree = (TTree*)file->Get(argv[2]);

  // print out the values of the tree so you know what the individual values of the tree are./
  std::string input1, input2;   
  tree->Print(); 
  printf("please enter (separately) the values you would like to graph.. \ntype exit first to leave..\n");
  std::cin >> input1 >> input2;
  // example_macro(); //feel free to include and run additional macros on your graph here..
  input2 = input1 + ":" + input2;
  tree->Draw(input2.c_str());
  //example_macro();
}

int main(int argc, char** argv){
 
 //test_print();  
  example_macro();

  if(argc != 3){
    printf("need 2 additional arguments to print:\n");
    printf("please supply the following: \"TFile_name\", \"TTree_name\" \n");
    return 0;
  }

  TApplication app("ROOT Application",&argc, argv);
  StandAlone(app.Argc(), app.Argv());
  app.Run();

  return 0;
}
    
