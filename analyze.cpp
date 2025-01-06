#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <iostream>

#include "TF1.h"
#include "TFile.h"
#include "TH1F.h"

void analyze() {
  TFile* data = new TFile("particle.root", "UPDATE");
  TFile* fit = new TFile("fit.root", "RECREATE");

  TF1* azimuth_fit = new TF1("azimuth_fit", "[0]", 0., 2 * TMath::Pi());
  TF1* polar_fit = new TF1("polar_fit", "[0]", 0., 1 * TMath::Pi());
  TF1* impulse_fit = new TF1("impulse_fit", "[0]*exp([1]*x)", 0., 9.);
  TF1* decayed_fit = new TF1("decayed_fit", "[2]/(sqrt(2*pi)*[0])*exp(-((x-[1])^2)/(2*[0]^2))", 0.6, 1.2);
  TF1* all_fit = new TF1("all_fit", "[2]/(sqrt(2*pi)*[0])*exp(-((x-[1])^2)/(2*[0]^2))", 0.6, 1.2);
  TF1* pk_fit = new TF1("pk_fit", "[2]/(sqrt(2*pi)*[0])*exp(-((x-[1])^2)/(2*[0]^2))", 0.6, 1.2);

  TH1F* types_histo = (TH1F*)data->Get("types_histo");
  TH1F* azimuth_histo = (TH1F*)data->Get("azimuth_histo");
  TH1F* polar_histo = (TH1F*)data->Get("polar_histo");
  TH1F* impulse_histo = (TH1F*)data->Get("impulse_histo");
  TH1F* transimpulse_histo = (TH1F*)data->Get("transimpulse_histo");
  TH1F* energy_histo = (TH1F*)data->Get("energy_histo");
  TH1F* invariant_mass_all_histo = (TH1F*)data->Get("invariant_mass_all_histo");
  TH1F* invariant_mass_same_histo = (TH1F*)data->Get("invariant_mass_same_histo");
  TH1F* invariant_mass_opposite_histo = (TH1F*)data->Get("invariant_mass_opposite_histo");
  TH1F* invariant_mass_same_pk_histo = (TH1F*)data->Get("invariant_mass_same_pk_histo");
  TH1F* invariant_mass_opposite_pk_histo = (TH1F*)data->Get("invariant_mass_opposite_pk_histo");
  TH1F* invariant_mass_decayed_histo = (TH1F*)data->Get("invariant_mass_decayed_histo");

  TH1F* all_difference = new TH1F("all_difference", "Difference of all particles with opposite charge", 5E2, 0, 8);
  TH1F* pk_difference = new TH1F("pk_difference", "Difference between pions and kaons with opposite charge and same charge", 1E3, 0, 8);

  std::cout << "Check proportions: \n";
  for (int i = 1; i <= types_histo->GetNbinsX(); i++) {
    std::cout << types_histo->GetBinContent(i) / 1E5 << "% +- " << types_histo->GetBinError(i) / 1E5 << "%\n";
  }

  invariant_mass_same_histo->Sumw2();
  invariant_mass_opposite_histo->Sumw2();
  all_difference->Add(invariant_mass_same_histo, invariant_mass_opposite_histo, -1, 1);

  invariant_mass_same_pk_histo->Sumw2();
  invariant_mass_opposite_pk_histo->Sumw2();
  pk_difference->Add(invariant_mass_opposite_pk_histo, invariant_mass_same_pk_histo, 1, -1);

  data->WriteObject(all_difference, "all_difference");
  data->WriteObject(pk_difference, "pk_difference");

  decayed_fit->SetParameter(0, 0.05);
  decayed_fit->SetParameter(1, 0.8917);
  all_fit->SetParameter(0, 0.05);
  all_fit->SetParameter(1, 0.8917);
  pk_fit->SetParameter(0, 0.05);
  pk_fit->SetParameter(1, 0.8917);

  std::cout << "Fitting invariant mass decayed: \n";
  invariant_mass_decayed_histo->Fit(decayed_fit, "R");
  std::cout << "\n Fitting difference between all opposite-charge particles: \n";
  all_difference->Fit(all_fit, "R");
  std::cout << "\n Fitting difference between opposite-charge pions and kaons: \n";
  pk_difference->Fit(pk_fit, "R");
  azimuth_fit->SetParameter(0, 1E4);
  std::cout << "\n Fitting azimuth angles: \n";
  azimuth_histo->Fit("azimuth_fit");
  polar_fit->SetParameter(0, 1E4);
  std::cout << "\n Fitting polar angles: \n";
  polar_histo->Fit("polar_fit");
  impulse_fit->SetParameter(1, -1.);
  std::cout << "\n Fitting impulse modules: \n";
  impulse_histo->Fit("impulse_fit");

  all_difference->GetXaxis()->SetRangeUser(0, 2);
  pk_difference->GetXaxis()->SetRangeUser(0, 2);

  fit->WriteObject(all_difference, "all_difference");
  fit->WriteObject(pk_difference, "pk_difference");
  fit->WriteObject(invariant_mass_decayed_histo, "invariant_mass_decayed_histo");
  fit->WriteObject(azimuth_histo, "azimuth_histo");
  fit->WriteObject(polar_histo, "polar_histo");
  fit->WriteObject(impulse_histo, "impulse_histo");

  std::cout << "First fit, on Azimuth angle: \n";
  std::cout << "Parameter: " << azimuth_fit->GetParameter(0) << "; chi squared: " << azimuth_fit->GetChisquare() << "; DOF: " << azimuth_fit->GetNDF() << "; reduced chi squared: " << azimuth_fit->GetChisquare() / azimuth_fit->GetNDF() << "; probability: " << azimuth_fit->GetProb() << "\n";

  std::cout << "Second fit, on Polar angle: \n";
  std::cout << "Parameter: " << polar_fit->GetParameter(0) <<"; chi squared: " << polar_fit->GetChisquare() << "; DOF: " << polar_fit->GetNDF() << "; reduced chi squared: " << polar_fit->GetChisquare() / polar_fit->GetNDF() << "; probability: " << polar_fit->GetProb() << "\n";

  std::cout << "Third fit, on impulse module: \n";
  std::cout << "First parameter: " << impulse_fit->GetParameter(0) << "; second parameter: " << impulse_fit->GetParameter(1) <<"; chi squared: " << impulse_fit->GetChisquare() << "; DOF: " << impulse_fit->GetNDF() << "; reduced chi squared: " << impulse_fit->GetChisquare() / impulse_fit->GetNDF() << "; probability:" << impulse_fit->GetProb() << "\n";

  std::cout << "Fourth fit, on invariant mass of decayed particles: \n";
  std::cout << "First parameter: " << decayed_fit->GetParameter(0) << "; second parameter: " << decayed_fit->GetParameter(1) << "; third parameter: " << decayed_fit->GetParameter(2) << "; reduced chi squared: " << decayed_fit->GetChisquare() / decayed_fit->GetNDF() << "; probability:" << decayed_fit->GetProb() << "\n";

  std::cout << "Fifth fit, on signal from all particles: \n";
  std::cout << "First parameter: " << all_fit->GetParameter(0) << "; second parameter: " << all_fit->GetParameter(1) << "; third parameter: " << all_fit->GetParameter(2) << "; reduced chi squared: " << all_fit->GetChisquare() / all_fit->GetNDF() << "; probability:" << all_fit->GetProb() << "\n";

  std::cout << "Sixth fit, on signal from pion and kaon particles: \n";
  std::cout << "First parameter: " << pk_fit->GetParameter(0) << "; second parameter: " << pk_fit->GetParameter(1) << "; third parameter: " << pk_fit->GetParameter(2) << "; reduced chi squared: " << pk_fit->GetChisquare() / pk_fit->GetNDF() << "; probability:" << pk_fit->GetProb() << "\n";
}
