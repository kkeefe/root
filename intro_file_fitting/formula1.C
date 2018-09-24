//example of a TF1 formula class to compile
//this is to be instanced as a root macro file

 {

   //this allows for multiple plots to be put into the same macro
  c1 = new TCanvas("c1", "Canvas name", 1500, 500);
  c1->Divide(3,1);

  //this is the information that is set for the first formula
  c1->cd(1);
  f1 = new TF1("f", "sin(x)/x", -10, 10);
  f1->SetLineColor(kGreen -3);
  f1->Draw();
  f1->SetTitle("My Function; X-axis title; Y-axis title");

  //this is the second graph. If you want to have them draw on the same graph
  //then you would need to add the "SAME" argument to draw()
  c1->cd(2);  
  f2 = new TF1("f", "cos(x)", -10, 10);
  f2->SetLineColor(kRed -3);
  f2->Draw();
  f2->SetTitle("My Second Function; Fun; Hate");

  //this will create a 2-dimensional function! can use x and y
  //this will create a 2-d surface view of the function
  // to really get a great idea of what you can do with 2-D functions you can right click on the function and set view options: surf1 gives a movable 3-D graph.
  //you can also use view -> view with OpenGL to get some very nice viewing of the 2-D functions.
  //for further options: TF2 root draw options.
  c1->cd(3);
  f3 = new TF2("f3", "10*cos(x)*sin(y)", -5, 5, -5, 5);
  f3->SetTitle("This is my first 2-variable graph; x; y");
  f3->Draw("surf1");

}
