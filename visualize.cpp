#include "TCanvas.h"
#include "TFile.h"
#include "TH1F.h"
#include "TStyle.h"

void visualize_v2() {
  TFile* data = new TFile("particle.root", "READ");
  TFile* fit = new TFile("fit.root", "READ");
  TFile* canvases = new TFile("canvases.root", "RECREATE");

  TH1F* types_histo = (TH1F*)data->Get("types_histo");
  TH1F* raw_azimuth_histo = (TH1F*)data->Get("azimuth_histo");
  TH1F* raw_polar_histo = (TH1F*)data->Get("polar_histo");
  TH1F* raw_impulse_histo = (TH1F*)data->Get("impulse_histo");
  TH1F* transimpulse_histo = (TH1F*)data->Get("transimpulse_histo");
  TH1F* energy_histo = (TH1F*)data->Get("energy_histo");
  TH1F* invariant_mass_all_histo = (TH1F*)data->Get("invariant_mass_all_histo");
  TH1F* invariant_mass_same_histo = (TH1F*)data->Get("invariant_mass_same_histo");
  TH1F* invariant_mass_opposite_histo = (TH1F*)data->Get("invariant_mass_opposite_histo");
  TH1F* invariant_mass_same_pk_histo = (TH1F*)data->Get("invariant_mass_same_pk_histo");
  TH1F* invariant_mass_opposite_pk_histo = (TH1F*)data->Get("invariant_mass_opposite_pk_histo");
  TH1F* raw_invariant_mass_decayed_histo = (TH1F*)data->Get("invariant_mass_decayed_histo");

  TH1F* all_difference = (TH1F*)fit->Get("all_difference");
  TH1F* pk_difference = (TH1F*)fit->Get("pk_difference");
  TH1F* fit_azimuth_histo = (TH1F*)fit->Get("azimuth_histo");
  TH1F* fit_polar_histo = (TH1F*)fit->Get("polar_histo");
  TH1F* fit_invariant_mass_decayed_histo = (TH1F*)fit->Get("invariant_mass_decayed_histo");
  TH1F* fit_impulse_histo = (TH1F*)fit->Get("impulse_histo");

  TCanvas* generation_graphs = new TCanvas("generation_graphs", "Fit Graphs");
  generation_graphs->Divide(2, 2);
  generation_graphs->cd(1);
  types_histo->GetYaxis()->SetTitle("Occurrencies");
  types_histo->GetXaxis()->SetBinLabel(1, "Positive pion");
  types_histo->GetXaxis()->SetBinLabel(2, "Negative pion");
  types_histo->GetXaxis()->SetBinLabel(3, "Positive kaon");
  types_histo->GetXaxis()->SetBinLabel(4, "Negative kaon");
  types_histo->GetXaxis()->SetBinLabel(5, "Positive proton");
  types_histo->GetXaxis()->SetBinLabel(6, "Negative proton");
  types_histo->GetXaxis()->SetBinLabel(7, "k*");
  gStyle->SetOptStat(1);
  types_histo->Draw();
  generation_graphs->cd(2);
  fit_azimuth_histo->GetXaxis()->SetTitle("Initial azimuthal angle (rad)");
  fit_azimuth_histo->GetYaxis()->SetTitle("Occurrencies");
  gStyle->SetOptStat(2210);
  fit_azimuth_histo->Draw();
  generation_graphs->cd(3);
  fit_polar_histo->GetXaxis()->SetTitle("Initial polar angle (rad)");
  fit_polar_histo->GetYaxis()->SetTitle("Occurrencies");
  fit_polar_histo->Draw();
  generation_graphs->cd(4);
  fit_impulse_histo->GetXaxis()->SetTitle("Initial impulse module (GeV/c^2)");
  fit_impulse_histo->GetYaxis()->SetTitle("Occurrencies");
  fit_impulse_histo->Draw();
  generation_graphs->SaveAs("generation_graphs.pdf");
  generation_graphs->SaveAs("generation_graphs.C");
  canvases->WriteObject(generation_graphs, "generation_graphs");

  TCanvas* gauss_graphs = new TCanvas("gauss_graphs", "Fit Graphs");
  gauss_graphs->Divide(3, 1);
  gauss_graphs->cd(1);
  all_difference->GetXaxis()->SetTitle("Invariant mass (GeV)");
  all_difference->GetYaxis()->SetTitle("Occurrencies");
  gStyle->SetOptStat(2200);
  all_difference->Draw();
  gauss_graphs->cd(2);
  pk_difference->GetXaxis()->SetTitle("Invariant mass (GeV)");
  pk_difference->GetYaxis()->SetTitle("Occurrencies");
  pk_difference->Draw();
  gauss_graphs->cd(3);
  fit_invariant_mass_decayed_histo->GetXaxis()->SetTitle("Invariant mass (GeV)");
  fit_invariant_mass_decayed_histo->GetYaxis()->SetTitle("Occurrencies");
  fit_invariant_mass_decayed_histo->Draw();
  gauss_graphs->SaveAs("gauss_graphs.pdf");
  gauss_graphs->SaveAs("gauss_graphs.C");
  canvases->WriteObject(gauss_graphs, "gauss_graphs");
}