{
  h1 = new TH1I("h", "random hist", 2, -0.5, 1.5);

  for(int i = 0; i < 10; i++){
    h1->Fill(gRandom->Integer(2));
  }

  h1->SetMinimum(0);
  h1->Draw();
}
