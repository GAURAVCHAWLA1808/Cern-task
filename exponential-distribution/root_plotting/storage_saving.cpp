#include <iostream>
#include <TCanvas.h>
#include <TGraph.h>
#include <TAxis.h>
#include <TLatex.h>

const int numTechniques = 7;
const char* techniques[numTechniques] = {
    "No Compression", "gzip", "8-bit Zeroing + gzip","10-bit Zeroing + gzip",
    "12-bit Zeroing + gzip", "16-bit Zeroing + gzip", "32-bit to 16-bit"
};

double storage_savings[numTechniques] = {0, 9.12, 26.81, 32.28,40.47, 55.63 , 50.0};

//This is to Storage Savings vs Techniques
void plotStorageSavings() {
    TCanvas* c1 = new TCanvas("c1", "Storage Savings vs Techniques", 800, 600);
    TGraph* graph = new TGraph(numTechniques);

    for (int i = 0; i < numTechniques; i++) {
        graph->SetPoint(i, i, storage_savings[i]);
    }

    graph->SetTitle("Storage Savings (%) vs. Compression Technique");
    graph->GetXaxis()->SetTitle("Compression Technique");
    graph->GetYaxis()->SetTitle("Storage Savings (%)");
    graph->SetMarkerStyle(20);
    graph->SetMarkerColor(kBlue);
    graph->Draw("APL");

    for (int i = 0; i < numTechniques; i++) {
        TLatex* tex = new TLatex(i + 0.1, storage_savings[i] + 2, techniques[i]);  //To Shift right
        tex->SetTextSize(0.03);
        tex->Draw();
    }

    c1->SaveAs("storage_savings.png");
}

int main() {
    plotStorageSavings();
    return 0;
}
