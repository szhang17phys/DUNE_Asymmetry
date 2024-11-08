//--szhang; Jul 7, 2021
//Features: 1.
//          2.
//          3.sdf
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
void Poisson_wrongAsy(){
    TCanvas *c1=new TCanvas("c1", "c1", 200, 10, 700, 500);
    gStyle->SetOptStat("nemr");

    TRandom3 *r1 = new TRandom3(0);//0 is the time-dependent seed!===
    TRandom3 *r2 = new TRandom3(0); 
    Int_t nu[9] = {18, 20, 22, 24, 26, 28, 30, 32, 34};
    Int_t x1 = 0;
    Int_t y1 = 0;
    Int_t asy = 0;
    TH1F *hist_nu_1 = new TH1F("hist_nu_1", "; x; Counts", 200, -100.5, 99.5);
    TH1F *hist_anti_1 = new TH1F("hist_anti_1", "; x; Counts", 200, -100.5, 99.5);
    TH1F *hist_asy_1 = new TH1F("hist_asy_1", "; x; Counts", 200, -100.5, 99.5);
    for(Int_t i=0; i<Repeat; ++i){
        x1 = r1->Poisson(nu[8]);
        y1 = r2->Poisson(36-nu[8]);
        asy = x1-y1;

//        hist_nu_1->AddBinContent(x1+101, 1);//bin_num starts from 1.
        hist_nu_1->Fill(x1);
        hist_anti_1->Fill(y1);
        hist_asy_1->Fill(asy); 
    }

//===For test=======================
//    hist_asy_1->AddBinContent(1, 50);
    Int_t testSum = 0;
    for(Int_t i=0; i<201; ++i){
        testSum += hist_asy_1->GetBinContent(i);
    }
    cout<<"---------------------"<<endl;
    cout<<"The total number is: "<<testSum<<endl;
    cout<<"---------------------"<<endl;

//Set range of y axis of a histo===
    hist_asy_1->GetYaxis()->SetRangeUser(0, 300000);

    hist_nu_1->SetLineColor(kBlack);
    hist_nu_1->SetLineWidth(1);
    hist_anti_1->SetLineColor(kBlue);
    hist_anti_1->SetLineWidth(1);
    hist_asy_1->SetLineColor(kRed);
    hist_asy_1->SetLineWidth(1);

    hist_asy_1->Draw();
    hist_nu_1->Draw("same");
    hist_anti_1->Draw("same");


    TLegend *leg = new TLegend(.7, .7, .9, .9);
    leg->AddEntry(hist_nu_1, "nu");
    leg->AddEntry(hist_anti_1, "anti_nu");
    leg->AddEntry(hist_asy_1, "Asymmetry");
    leg->Draw();    

//output some statistical information of asy===
    cout<<"nu = 34, anti_nu=2: "<<endl;
    Double_t per[5] = {0.05, 0.16, 0.50, 0.84, 0.95};
    Int_t val[5] = {0, 0, 0, 0, 0};
    Int_t sum = 0;
    for(Int_t i=0; i<5; ++i){
        for(Int_t j=1; j<200; ++j){
            sum += hist_asy_1->GetBinContent(j);
            if(sum > per[i]*Repeat){ 
                val[i] = j-101;  
                cout<< setiosflags(ios::fixed) << setprecision(2)<<per[i]<<": "<<val[i]<<endl;
                break;
            }        
        }
        sum = 0;
    }


//---For test-------------------------------------
//    cout<<"==========================="<<endl;
//    cout<<hist_asy_1->GetBinContent(0)<<endl;
//    cout<<hist_asy_1->GetBinContent(1)<<endl;

}
       
#ifndef __CINT__
int main(){
    Poisson_wrongAsy();
}
#endif


