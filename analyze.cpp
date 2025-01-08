#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <iostream>

#include "TF1.h"
#include "TFile.h"
#include "TH1F.h"

void gaussAmplitude(TF1* func) {  // sigma = [0], a = [2]
  double par_0 = func->GetParameter(0);
  double par_0_err = func->GetParError(0);
  double par_2 = func->GetParameter(2);
  double par_2_err = func->GetParError(2);

  double value = par_2 / (TMath::Sqrt(2 * TMath::Pi()) * par_0);
  double error = TMath::Sqrt(TMath::Power((par_2_err / (TMath::Sqrt(2 * TMath::Pi()) * par_0)), 2) + TMath::Power(par_2 * par_0_err / (TMath::Sqrt(2 * TMath::Pi()) * TMath::Power(par_0, 2)), 2));
  std::cout << "amplitude: " << value << " +/- " << error << "\n";
}

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
  TH1F* all_difference = new TH1F("all_difference", "All particles same and opposite charge difference", 5E2, 0, 8);
  TH1F* pk_difference = new TH1F("pk_difference", "Pions and kaons same and opposite charge difference", 1E3, 0, 8);

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

  std::cout << "\nCheck proportions: \n";
  for (int i = 1; i <= types_histo->GetNbinsX(); i++) {
    std::cout << types_histo->GetBinContent(i) / 1E5 << "% +- " << types_histo->GetBinError(i) / 1E5 << "%\n";
  }
  
  std::cout << "\nFirst fit, on Azimuth angle:";
  std::cout << "\nParameter: " << azimuth_fit->GetParameter(0) << "\nchi squared: " << azimuth_fit->GetChisquare() << "\nDOF: " << azimuth_fit->GetNDF() << "\nreduced chi squared: " << azimuth_fit->GetChisquare() / azimuth_fit->GetNDF() << "\nprobability: " << azimuth_fit->GetProb() << "\n";

  std::cout << "\nSecond fit, on Polar angle:";
  std::cout << "\nParameter: " << polar_fit->GetParameter(0) << "\nchi squared: " << polar_fit->GetChisquare() << "\nDOF: " << polar_fit->GetNDF() << "\nreduced chi squared: " << polar_fit->GetChisquare() / polar_fit->GetNDF() << "\nprobability: " << polar_fit->GetProb() << "\n";

  std::cout << "\nThird fit, on impulse module: ";
  std::cout << "\nFirst parameter: " << impulse_fit->GetParameter(0) << "\nsecond parameter: " << impulse_fit->GetParameter(1) << " +/- " << impulse_fit->GetParError(1) << "\nchi squared: " << impulse_fit->GetChisquare() << "\nDOF: " << impulse_fit->GetNDF() << "\nreduced chi squared: " << impulse_fit->GetChisquare() / impulse_fit->GetNDF() << "\nprobability:" << impulse_fit->GetProb() << "\n";

  std::cout << "\nFourth fit, on invariant mass of decayed particles: ";
  std::cout << "\nsigma: " << decayed_fit->GetParameter(0) << " +/- " << decayed_fit->GetParError(0) << "\nmean: " << decayed_fit->GetParameter(1) << " +/- " << decayed_fit->GetParError(1) << "\nthird parameter: " << decayed_fit->GetParameter(2) << "\nreduced chi squared: " << decayed_fit->GetChisquare() / decayed_fit->GetNDF() << "\nprobability:" << decayed_fit->GetProb() << "\n";
  gaussAmplitude(decayed_fit);

  std::cout << "\nFifth fit, on signal from all particles: ";
  std::cout << "\nsigma: " << all_fit->GetParameter(0) << " +/- " << all_fit->GetParError(0) << "\nmean: " << all_fit->GetParameter(1) << " +/- " << all_fit->GetParError(1) << "\nthird parameter: " << all_fit->GetParameter(2) << "\nreduced chi squared: " << all_fit->GetChisquare() / all_fit->GetNDF() << "\nprobability:" << all_fit->GetProb() << "\n";
  gaussAmplitude(all_fit);

  std::cout << "\nSixth fit, on signal from pion and kaon particles: ";
  std::cout << "\nsigma: " << pk_fit->GetParameter(0) << " +/- " << pk_fit->GetParError(0) << "\nmean: " << pk_fit->GetParameter(1) << " +/- " << pk_fit->GetParError(1) << "\nthird parameter: " << pk_fit->GetParameter(2) << "\nreduced chi squared: " << pk_fit->GetChisquare() / pk_fit->GetNDF() << "\nprobability:" << pk_fit->GetProb() << "\n";
  gaussAmplitude(pk_fit);
}
