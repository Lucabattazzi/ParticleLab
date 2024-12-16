#include <vector>

#include "TFile.h"
#include "TH1F.h"
void visualize() {
  TFile* file = new TFile("particle.root", "READ");
  file->ls();
  TH1F* types_histo = new TH1F("types_histo", "Particle types", 7, 0, 7);  // ricorda di aggiornare l'asse delle ascisse inserendo i nomi delle particelle
  TH1F* azimuth_histo = new TH1F("azimuth_histo", "Azimuthal angle", 1E3, 0, 2 * TMath::Pi());
  TH1F* polar_histo = new TH1F("polar_histo", "Polar angle", 1E3, 0, TMath::Pi());
  TH1F* impulse_histo = new TH1F("impulse_histo", "Impulse", 1E3, 0, 9);                       // all ranges to be set properly
  TH1F* transimpulse_histo = new TH1F("transimpulse_histo", "Transverse impulse", 1E4, 0, 7);  // English?
  TH1F* energy_histo = new TH1F("energy_histo", "Energy", 1E4, 0, 6.4);
  TH1F* invariant_mass_all_histo = new TH1F("invariant_mass_all_histo", "Invariant mass between all particles", 1E4, 0, 8);                                       // on stable
  TH1F* invariant_mass_same_histo = new TH1F("invariant_mass_same_histo", "Invariant mass between particles of same charge", 5E2, 0, 8);                          // on stable
  TH1F* invariant_mass_opposite_histo = new TH1F("invariant_mass_opposite_histo", "Invariant mass between particles of opposite charge", 5E2, 0, 8);              // on stable
  TH1F* invariant_mass_same_pk_histo = new TH1F("invariant_mass_same_pk_histo", "Invariant mass between pions and kaons of same charge", 1E3, 0, 8);              // on stable
  TH1F* invariant_mass_opposite_pk_histo = new TH1F("invariant_mass_opposite_pk_histo", "Invariant mass between pions and kaons of opposite charge", 1E3, 0, 8);  // on stable
  TH1F* invariant_mass_decayed_histo = new TH1F("invariant_mass_decayed_histo", "Invariant mass between decayed particles", 1E3, 0.4, 1.4);                       // on decayed, for benchmark
   
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
