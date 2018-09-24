void c1()
{
//=========Macro generated from canvas: c1/c1
//=========  (Thu May 24 15:33:49 2018) by ROOT version 6.12/06
   TCanvas *c1 = new TCanvas("c1", "c1",10,67,961,665);
   c1->ToggleEventStatus();
   c1->Range(-12.47396,-0.4462051,12.5,1.227636);
   c1->SetFillColor(51);
   c1->SetFillStyle(3014);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetGridx();
   c1->SetGridy();
   c1->SetTickx(1);
   c1->SetTicky(1);
   c1->SetFrameFillColor(0);
   c1->SetFrameBorderMode(0);
   c1->SetFrameFillColor(2);
   c1->SetFrameFillStyle(3011);
   c1->SetFrameBorderMode(0);
   
   TF1 *f1 = new TF1("f","sin(x)/x",-10,10, TF1::EAddToList::kDefault);
   f1->SetFillColor(19);
   f1->SetFillStyle(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000000");
   f1->SetMarkerColor(ci);
   f1->SetLineColor(9);
   f1->SetLineWidth(5);
   f1->SetLineStyle(2);
   f1->GetXaxis()->SetLabelFont(42);
   f1->GetXaxis()->SetLabelSize(0.035);
   f1->GetXaxis()->SetTitleSize(0.035);
   f1->GetXaxis()->SetTitleFont(42);
   f1->GetYaxis()->SetLabelFont(42);
   f1->GetYaxis()->SetLabelSize(0.035);
   f1->GetYaxis()->SetTitleSize(0.035);
   f1->GetYaxis()->SetTitleOffset(0);
   f1->GetYaxis()->SetTitleFont(42);
   f1->Draw("");
   
   TPaveText *pt = new TPaveText(0.4298281,0.9368947,0.5701719,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("sin(x)/x");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
