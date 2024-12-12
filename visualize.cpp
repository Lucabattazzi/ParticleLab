#include <vector>

#include "TFile.h"
#include "TH1F.h"
void visualize() {
  TFile* file = new TFile("particle.root", "READ");
  file->ls();
  TH1F* h1 = (TH1F*)file->Get("h1");
  TH1F* h2 = (TH1F*)file->Get("h2");
  TH1F* h3 = (TH1F*)file->Get("h3");
  TH1F* h4 = (TH1F*)file->Get("h4");
  TH1F* h5 = (TH1F*)file->Get("h5");
  TH1F* h6 = (TH1F*)file->Get("h6");
  TH1F* h7 = (TH1F*)file->Get("h7");
  TH1F* h8 = (TH1F*)file->Get("h8");
  TH1F* h9 = (TH1F*)file->Get("h9");
  TH1F* h10 = (TH1F*)file->Get("h10");
  TH1F* h11 = (TH1F*)file->Get("h11");
  TH1F* h12 = (TH1F*)file->Get("h12");
  TCanvas* c1 = new TCanvas("canvas", "canvas");
  c1->Divide(3, 4);
  int i{1};
  std::vector<TH1F*> histograms = {h1, h2, h3, h4, h5, h6, h7, h8, h9, h10, h11, h12};
  for (auto hist : histograms) {
    c1->cd(i++);
    if (hist) {
      hist->Draw();  // Disegna l'istogramma
    } else {
      std::cout << "Istogramma non trovato nel file." << std::endl;
    }
    hist->SetDirectory(0);
  }
  c1->Modified();
  c1->Update();
  c1->Write();
  TH1::AddDirectory(kFALSE);
  file->Close();
  // delete file;  // Libera la memoria
}
