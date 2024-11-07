#include <vector>

#include "TFile.h"
#include "TH1F.h"
void Draw() {
  TFile* file = new TFile("particle.root", "READ");

  TH1F* h1 = (TH1F*)file->Get("azimuth_histo");
  TH1F* h2 = (TH1F*)file->Get("polar_histo");
  TH1F* h3 = (TH1F*)file->Get("impulse_histo");
  TH1F* h4 = (TH1F*)file->Get("transimpulse_histo");
  TH1F* h5 = (TH1F*)file->Get("energy_histo");
  TH1F* h6 = (TH1F*)file->Get("invariant_mass_all_histo");
  TH1F* h7 = (TH1F*)file->Get("invariant_mass_same_histo");
  TH1F* h8 = (TH1F*)file->Get("invariant_mass_opposite_histo");
  TH1F* h9 = (TH1F*)file->Get("invariant_mass_same_pk_histo");
  TH1F* h10 = (TH1F*)file->Get("invariant_mass_opposite_pk_histo");
  TH1F* h11 = (TH1F*)file->Get("invariant_mass_decayed_histo");
  std::vector<TH1F*> histograms = {h1, h2, h3, h4, h5, h6, h7, h8, h9, h10, h11};

  for (auto hist : histograms) {
    if (hist) {
      hist->Draw();  // Disegna l'istogramma
    } else {
      std::cout << "Istogramma non trovato nel file." << std::endl;
    }
  }
  file->Close();
  // delete file;  // Libera la memoria
}
