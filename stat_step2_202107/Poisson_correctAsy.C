//--szhang; Jul 14, 2021

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
void Poisson_correctAsy(){
    TCanvas *c1=new TCanvas("c1", "c1", 200, 10, 700, 500);
    gStyle->SetOptStat("nemr");

    TRandom3 *r1 = new TRandom3(0);//0 is the time-dependent seed!===
    TRandom3 *r2 = new TRandom3(0); 
    Double_t nu[17] = {7.98, 11.14, 13.89, 16.30, 18.43, 20.33, 22.04, 23.58, 24.97, 26.24, 27.40, 28.46, 29.44, 30.35, 31.19, 31.97, 32.70};
    Double_t Num_nu = 0.0;
    Num_nu = nu[16]; //---change every time------------
    Int_t x1 = 0;
    Int_t y1 = 0;
    Double_t asy = 0;

    TH1F *hist_asy = new TH1F("hist_asy", "; Asy; Counts", 201, -1.005, 1.005);
    for(Int_t i=0; i<Repeat; ++i){
        x1 = r1->Poisson(Num_nu);
        y1 = r2->Poisson(34-Num_nu);
        asy = 1.0*(x1*1.0/470-y1*1.0/170)/(x1*1.0/470+y1*1.0/170);

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


    hist_asy->SetLineColor(kRed);
    hist_asy->SetLineWidth(1);
    hist_asy->Draw();

//    TLegend *leg = new TLegend(.7, .55, .9, .65);
//    leg->AddEntry(hist_asy, "Asymmetry");
//    leg->Draw();    

//output some statistical information of asy===
cout<<"nu = "<<Num_nu<<", anti_nu = "<<(34-Num_nu)<<": "<<endl;
    Double_t per[5] = {0.05, 0.16, 0.50, 0.84, 0.95};
    Double_t val[5] = {0.0, 0.0, 0.0, 0.0, 0.0};
    Int_t sum = 0;
    for(Int_t i=0; i<5; ++i){
        for(Int_t j=1; j<202; ++j){
            sum += hist_asy->GetBinContent(j);
            if(sum > per[i]*Repeat){ 
                val[i] = 1.0*j/100-1.01;  
                cout<< setiosflags(ios::fixed) << setprecision(2)<<per[i]<<": "<<val[i]<<endl;
                break;
            }        
        }
        sum = 0;
    }

}
       
#ifndef __CINT__
int main(){
    Poisson_correctAsy();
}
#endif


