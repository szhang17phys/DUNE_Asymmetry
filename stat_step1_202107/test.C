//--szhang; Jul 7, 2021

#include "TCanvas.h"
#include "TROOT.h"
#include "TGraphErrors.h"
#include "TF1.h"            //(x, y) graphs
#include "TH1F.h"           //one variable histogram  
#include "TLegend.h" 
#include "TArrow.h"
#include "TLatex.h"
#include "TRandom.h"        //TRandom

using namespace std;

void format_h(TH1F* h, int linecolor){
    h->SetLineWidth(3);
    h->SetLineColor(linecolor);
}

void test(){
    TCanvas *c1=new TCanvas("c1", "c1", 200, 10, 700, 500);
    gStyle->SetOptStat("nemr");

    TRandom3 *r1 = new TRandom3(10);
    TRandom3 *r2 = new TRandom3(20);
    Int_t nu[9] = {18, 20, 22, 24, 26, 28, 30, 32, 34};
    Int_t x1 = 0;
    Int_t y1 = 0;
    Int_t asy = 0;
    TH1F *hist_nu_1 = new TH1F("hist_nu_1", "; x; Counts", 200, -100.5, 99.5);
    TH1F *hist_anti_1 = new TH1F("hist_anti_1", "; x; Counts", 200, -100.5, 99.5);
    TH1F *hist_asy_1 = new TH1F("hist_asy_1", "; x; Counts", 200, -100.5, 99.5);
    for(Int_t i=0; i<1000000; ++i){
        x1 = r1->Poisson(nu[0]);
        y1 = r2->Poisson(36-nu[0]);
        asy = x1-y1;

        hist_nu_1->Fill(x1);//bin_num starts from 1.
        hist_anti_1->Fill(y1);
        hist_asy_1->Fill(asy); 
    }


    hist_nu_1->SetLineColor(kRed);
    hist_nu_1->SetLineWidth(1);
    hist_anti_1->SetLineColor(kBlue);
    hist_anti_1->SetLineWidth(1);
    hist_asy_1->SetLineColor(kGreen);
    hist_asy_1->SetLineWidth(1);

    hist_anti_1->Draw();
    hist_nu_1->Draw("same");
    hist_asy_1->Draw("same");


}
  
       
#ifndef __CINT__
int main(){
    test();
}
#endif



