#include <iostream>
#include <TCanvas.h>
#include <TGraph.h>
#include <TAxis.h>
#include <TLatex.h>
#include <TMarker.h>
#include <TLegend.h>
#include <TStyle.h>

const int numTechniques = 7;
const char* techniques[numTechniques] = {
    "No Compression", "gzip", "8-bit Zeroing + gzip","10-bit Zeroing + gzip",
    "12-bit Zeroing + gzip", "16-bit Zeroing + gzip", "32-16 bit"
};

double storage_savings[numTechniques] = {0, 9.12, 26.81, 32.28,40.47, 55.63 , 50.0};
double mse[numTechniques] = {0, 0 , 3.33151e-10, 5.33735e-09,8.55999e-08, 2.18084e-05 , 1.40414e-04 };

//This is to Find the best compression technique
int findSweetSpotIndex() {
    double bestRatio = 0.0;
    int bestIndex = 0;
    for (int i = 1; i < numTechniques; i++) {
        double ratio = storage_savings[i] / (mse[i] + 1e-10);  
        if (ratio > bestRatio) {
            bestRatio = ratio;
            bestIndex = i;
        }
    }
    return bestIndex;
}

//This is to Plot Storage Savings vs MSE (Sweet Spot)
void plotSweetSpot() {
    TCanvas* c3 = new TCanvas("c3", "Storage Savings vs MSE (Sweet Spot)", 800, 600);
    TGraph* graph = new TGraph(numTechniques);
    
    for (int i = 0; i < numTechniques; i++) {
        graph->SetPoint(i, mse[i] + 1e-10, storage_savings[i]);
    }

    c3->SetLogx();
    graph->SetTitle("Storage Savings (%) vs. MSE (Sweet Spot Highlighted)");
    graph->GetXaxis()->SetTitle("Mean Squared Error (MSE) [Log Scale]");
    graph->GetYaxis()->SetTitle("Storage Savings (%)");
    graph->SetMarkerStyle(21);
    graph->SetMarkerColor(kBlue);
    graph->Draw("APL");

    //This is to Highlight the sweet spot
    int bestIndex = findSweetSpotIndex();
    TMarker* sweetSpot = new TMarker(mse[bestIndex] + 1e-10, storage_savings[bestIndex], 29);
    sweetSpot->SetMarkerColor(kRed);
    sweetSpot->SetMarkerSize(2.0);
    sweetSpot->Draw();

    TLegend* legend = new TLegend(0.6, 0.15, 0.88, 0.3);
    legend->AddEntry(graph, "All Techniques", "P");
    legend->AddEntry(sweetSpot, Form("Sweet Spot: %s", techniques[bestIndex]), "P");
    legend->Draw();

    //This is to Adjust label positions: spread them out to reduce clutter
    for (int i = 0; i < numTechniques; i++) {
        double x_offset = (i % 2 == 0) ? 1.4 : 1.1;  
        double y_offset = (i % 2 == 0) ? 2.8 : 1.8;  
        TLatex* tex = new TLatex(mse[i] * x_offset, storage_savings[i] + y_offset, techniques[i]);  
        tex->SetTextSize(0.027);  
        tex->Draw();
    }

    c3->SaveAs("sweet_spot.png");
}

int main() {
    gStyle->SetOptStat(0);
    
    plotSweetSpot();

    int bestIndex = findSweetSpotIndex();
    std::cout << "Sweet Spot: " << techniques[bestIndex]
              << " (Storage Savings: " << storage_savings[bestIndex]
              << "%, MSE: " << mse[bestIndex] << ")" << std::endl;

    return 0;
}
