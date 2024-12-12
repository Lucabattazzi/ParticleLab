#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <iostream>
// #include <vector>

#include "TF1.h"
#include "TFile.h"
#include "TH1F.h"
// #include "doctest.h"

void analyze() {
  TFile* file = new TFile("particle.root", "READ");
  TCanvas* c1 = new TCanvas("c1", "Canvas");
  //   c1->Divide(2,1);
  file->ls();
  TF1* constant_generation = new TF1("constant_generation", "[0]", 0, 2 * TMath::Pi());
  TF1* impulse_generation = new TF1("impulse_generation", "[0]*exp([1]*x)", 0, 9);
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
  TH1F* all_difference = new TH1F("all_difference", "Difference of all particles with opposite charge", 1000000, 0, 8);
  TH1F* pk_difference = new TH1F("pk_difference", "Difference between pions and kaons with opposite charge and same charge", 100000, 0, 8);
  // std::cout << "CHECK TOTAL ENTRIES: \n";
  // std::cout << h1->GetTitle()<<" entries: " << h1->GetEntries() <<"; Expected: exactly 1E7\n";
  // std::cout << h2->GetTitle()<<" entries: " << h2->GetEntries() <<"; Expected: exactly 1E7\n";
  // std::cout << h3->GetTitle()<<" entries: " << h3->GetEntries() <<"; Expected: exactly 1E7\n";
  // std::cout << h4->GetTitle()<<" entries: " << h4->GetEntries() <<"; Expected: exactly 1E7\n";
  // std::cout << h5->GetTitle()<<" entries: " << h5->GetEntries() <<"; Expected: exactly 1E7\n";
  // std::cout << h6->GetTitle()<<" entries: " << h6->GetEntries() <<"; Expected: exactly 1E7\n";
  std::cout << "Check proportions: \n";
  for (int i = 1; i <= h1->GetNbinsX(); i++) {
    std::cout << h1->GetBinContent(i) / 1E5 << "% +- " << h1->GetBinError(i) / 1E5 << "%\n";
  }
  h2->Fit("constant_generation");
  std::cout << "First fit, on Azimuth angle: \n";
  std::cout << "Parameter: " << constant_generation->GetParameter(0) << "; reduced chi squared: " << constant_generation->GetChisquare() / constant_generation->GetNDF() << "; probability: " << constant_generation->GetProb() << "\n";
  h4->Fit("constant_generation");
  //   c1->cd(1);
  //   h2->Draw();
  std::cout << "Second fit, on Polar angle: \n";
  std::cout << "Parameter: " << constant_generation->GetParameter(0) << "; reduced chi squared: " << constant_generation->GetChisquare() / constant_generation->GetNDF() << "; probability: " << constant_generation->GetProb() << "\n";
  //   c1->cd(2);
  //   h4->Draw();
  // ATTENZIONE: NON FUNZIONA CORRETTAMENTE PROBABILITà
  std::cout << "Third fit, on impulse module: \n";
  h3->Fit("impulse_generation");
  std::cout << "First parameter: " << impulse_generation->GetParameter(0) << "; second parameter: " << impulse_generation->GetParameter(1) << "; reduced chi squared: " << impulse_generation->GetChisquare() / impulse_generation->GetNDF() << "; probability:" << impulse_generation->GetProb() << "\n";
  // ATTENZIONE: IL CHI QUADRO E LA PROBABILITà SONO COMPLETAMENTI DI FUORI
  //   h3->Draw();
  //   h4->Draw();
  h8->Sumw2();
  h9->Sumw2();
  all_difference->Add(h8, h9, -1, 1);
  h10->Sumw2();
  h11->Sumw2();
  pk_difference->Add(h11, h10, 1, -1);
  pk_difference->Draw();
}

// TEST_CASE("") {
//   SUBCASE("") {
//     //   CHECK(it->getPosition().x == doctest::Approx(102));
//     //   CHECK(it->getPosition().y == doctest::Approx(102));}
//   }
// }
