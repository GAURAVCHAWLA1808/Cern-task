#include <TCanvas.h>
#include <TH1F.h>
#include <TStyle.h>

void simulation() {
    const int n = 7; // Number of compression techniques

    const char* techniques[n] = {"Uncompressed", "Gzip", "8 bit+gzip","10 bit+gzip",  "12bit+Gzip", "16bit+Gzip","32-16 bit"};

    double mse[n] = {0, 0 , 1.6735e-10, 2.69561e-09,4.32203e-08, 1.09706e-05 ,8.27386e-05 }; 

    TCanvas *c1 = new TCanvas("c1", "MSE vs. Compression Techniques", 800, 600);
    gStyle->SetOptStat(0); 
    c1->SetLogy(); 

    // Create Histogram for Bar Graph
    TH1F *h1 = new TH1F("h1", "MSE for Different Compression Techniques;Compression Techniques;MSE ", n, 0, n);
    
    for (int i = 0; i < n; i++) {
        h1->SetBinContent(i+1, mse[i]); 
        h1->GetXaxis()->SetBinLabel(i+1, techniques[i]); 
    }

    h1->SetFillColor(kBlue);
    h1->SetBarWidth(0.5);
    h1->SetBarOffset(0.2);
    h1->Draw("bar"); 

    c1->Update(); 
    c1->SaveAs("mse.png");
    c1->Draw(); 
}

int main() {
    simulation();
    return 0;
}
