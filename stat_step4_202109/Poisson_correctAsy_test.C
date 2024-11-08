//--szhang; Sep 9, 2021

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
const int Repeat = 1000000;

void format_h(TH1F* h, int linecolor){
    h->SetLineWidth(3);
    h->SetLineColor(linecolor);
}

//===Main==================================
void Poisson_correctAsy_test(){
    TCanvas *c1=new TCanvas("c1", "c1", 200, 10, 700, 500);
    gStyle->SetOptStat("nemr");

    TRandom3 *r1 = new TRandom3(0);//0 is the time-dependent seed!===
    TRandom3 *r2 = new TRandom3(0); 
    Double_t nu[17] = {7.54, 10.57, 13.23, 15.59, 17.69, 19.58, 21.28, 22.82, 24.22, 25.50, 26.68, 27.76, 28.77, 29.70, 30.56, 31.36, 32.12};
    Double_t Num_nu = 0.0;
//    Num_nu = nu[16]; //---change every time------
    Num_nu = 26.13;
    Int_t x1 = 0;
    Int_t y1 = 0;
    Double_t asy = 0;
    Double_t nu_bkg = 5.0;
    Double_t antiNu_bkg = 2.5;

    TH1F *hist_asy = new TH1F("hist_asy", "; Asy; Counts", 301, -1.505, 1.505);
    for(Int_t i=0; i<Repeat; ++i){
        x1 = r1->Poisson(Num_nu + nu_bkg);
        y1 = r2->Poisson(33.5- Num_nu + antiNu_bkg);
        x1 = x1-nu_bkg;
        y1 = y1-antiNu_bkg;
        asy = 1.0*(x1*1.0/470-y1*1.0/180)/(x1*1.0/470+y1*1.0/180);

        hist_asy->Fill(asy); 
    }

//===For test=======================
//    hist_asy->AddBinContent(1, 50);
//    Int_t testSum = 0;
//    for(Int_t i=0; i<202; ++i){
//        testSum += hist_asy->GetBinContent(i);
//    }
//    cout<<"Total (0-200): "<<testSum<<endl;
//    cout<<"bin 199: "<<hist_asy->GetBinContent(199)<<endl;


//    TLegend *leg = new TLegend(.7, .55, .9, .65);
//    leg->AddEntry(hist_asy, "Asymmetry");
//    leg->Draw();    

//output some statistical information of asy===
cout<<"nu = "<<Num_nu<<", anti_nu = "<<(33.5-Num_nu)<<": "<<endl;
    Double_t per[6] = {0.05, 0.16, 0.32, 0.50, 0.84, 0.95};
    Double_t val[6] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    Int_t sum = 0;
    for(Int_t i=0; i<6; ++i){
        for(Int_t j=1; j<302; ++j){
            sum += hist_asy->GetBinContent(j);
            if(sum > per[i]*Repeat){ 
                val[i] = 1.0*j/100-1.51;  
                cout<< setiosflags(ios::fixed) << setprecision(2)<<per[i]<<": "<<val[i]<<endl;
                break;
            }        
        }
        sum = 0;
    }

//Draw the histo first!!!=========
    hist_asy->SetLineColor(kRed);
    hist_asy->SetLineWidth(1);
    hist_asy->Draw();

//Auxiliary lines===============
   TLine *line05 = new TLine(val[0], 0, val[0], 60000);
   line05->SetLineColor(4);
   line05->SetLineStyle(2);
   line05->SetLineWidth(2);
   line05->Draw();

   TLine *line16 = new TLine(val[1], 0, val[1], 60000);
   line16->SetLineColor(4);
   line16->SetLineStyle(2);
   line16->SetLineWidth(2);
   line16->Draw();

   TLine *line84 = new TLine(val[4], 0, val[4], 60000);
   line84->SetLineColor(4);
   line84->SetLineStyle(2);
   line84->SetLineWidth(2);
   line84->Draw();

   TLine *line95 = new TLine(val[5], 0, val[5], 60000);
   line95->SetLineColor(4);
   line95->SetLineStyle(2);
   line95->SetLineWidth(2);
   line95->Draw();

//Marker of NEAR real data: 0.087----------
   TLine *lineData = new TLine(-0.087, 0, -0.087, 60000);
   lineData->SetLineColor(6);//purple---
   lineData->SetLineStyle(2);
   lineData->SetLineWidth(2);
   lineData->Draw();


}

#ifndef __CINT__
int main(){
    Poisson_correctAsy_test();
}
#endif


