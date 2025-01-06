#include <iostream>

#include "TFile.h"
#include "TH1F.h"
#include "TCanvas.h"
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

  TCanvas* generation_information = new TCanvas("generation_information", "Generation Information");
  gStyle->SetOptStat(1110);
  generation_information->Divide(2, 2);
  generation_information->cd(1);
  types_histo->GetYaxis()->SetTitle("Occurrencies");
  types_histo->GetXaxis()->SetBinLabel(1, "Positive pion");
  types_histo->GetXaxis()->SetBinLabel(2, "Negative pion");
  types_histo->GetXaxis()->SetBinLabel(3, "Positive kaon");
  types_histo->GetXaxis()->SetBinLabel(4, "Negative kaon");
  types_histo->GetXaxis()->SetBinLabel(5, "Positive proton");
  types_histo->GetXaxis()->SetBinLabel(6, "Negative proton");
  types_histo->GetXaxis()->SetBinLabel(7, "k*");
  types_histo->Draw();
  generation_information->cd(2);
  raw_azimuth_histo->GetXaxis()->SetTitle("Initial azimuthal angle (rad)");
  raw_azimuth_histo->GetYaxis()->SetTitle("Occurrencies");
  raw_azimuth_histo->Draw();
  generation_information->cd(3);
  raw_polar_histo->GetXaxis()->SetTitle("Initial polar angle (rad)");
  raw_polar_histo->GetYaxis()->SetTitle("Occurrencies");
  raw_polar_histo->Draw();
  generation_information->cd(4);
  raw_impulse_histo->GetXaxis()->SetTitle("Initial impulse module (unspecified)");
  raw_impulse_histo->GetYaxis()->SetTitle("Occurrencies");
  raw_impulse_histo->Draw();
  generation_information->SaveAs("_generation_information.pdf");
  generation_information->SaveAs("_generation_information.C");
  canvases->WriteObject(generation_information, "generation_information");
  
  TCanvas* additional_data = new TCanvas("additional_data", "Additional generation data");
  gStyle->SetOptStat(1110);
  additional_data->Divide(3,3);
  additional_data->cd(1);
  transimpulse_histo->GetXaxis()->SetTitle("Transverse impulse relative to all particles (unspecified)");
  transimpulse_histo->GetYaxis()->SetTitle("Occurrencies");
  transimpulse_histo->Draw();
  additional_data->cd(2);
  energy_histo->GetXaxis()->SetTitle("Particle energy (unspecified)");
  energy_histo->GetYaxis()->SetTitle("Occurrencies");
  energy_histo->Draw();
  additional_data->cd(3);
  invariant_mass_all_histo->GetXaxis()->SetTitle("Invariant mass (unspecified)");
  invariant_mass_all_histo->GetYaxis()->SetTitle("Occurrencies");
  invariant_mass_all_histo->Draw();
  additional_data->cd(4);
  invariant_mass_same_histo->GetXaxis()->SetTitle("Invariant mass (unspecified)");
  invariant_mass_same_histo->GetYaxis()->SetTitle("Occurrencies");
  invariant_mass_same_histo->Draw();
  additional_data->cd(5);
  invariant_mass_opposite_histo->GetXaxis()->SetTitle("Invariant mass (unspecified)");
  invariant_mass_opposite_histo->GetYaxis()->SetTitle("Occurrencies");
  invariant_mass_opposite_histo->Draw();
  additional_data->cd(6);
  invariant_mass_same_pk_histo->GetXaxis()->SetTitle("Invariant mass (unspecified)");
  invariant_mass_same_pk_histo->GetYaxis()->SetTitle("Occurrencies");
  invariant_mass_same_pk_histo->Draw();
  additional_data->cd(7);
  invariant_mass_opposite_pk_histo->GetXaxis()->SetTitle("Invariant mass (unspecified)");
  invariant_mass_opposite_pk_histo->GetYaxis()->SetTitle("Occurrencies");
  invariant_mass_opposite_pk_histo->Draw();
  additional_data->cd(8);
  raw_invariant_mass_decayed_histo->GetXaxis()->SetTitle("Invariant mass (unspecified)");
  raw_invariant_mass_decayed_histo->GetYaxis()->SetTitle("Occurrencies");
  raw_invariant_mass_decayed_histo->Draw();
  generation_information->SaveAs("_additional_data.pdf");
  generation_information->SaveAs("_additional_data.C");
  canvases->WriteObject(additional_data, "additional_data");
  
  TCanvas* fit_graphs = new TCanvas("fit_graphs", "Fit Graphs");
  fit_graphs->Divide(3,2);
  fit_graphs->cd(1);
  fit_azimuth_histo->GetXaxis()->SetTitle("Initial azimuthal angle (rad)");
  fit_azimuth_histo->GetYaxis()->SetTitle("Occurrencies");
  gStyle->SetOptStat(2210);
  fit_azimuth_histo->Draw();
  fit_graphs->cd(2);
  fit_polar_histo->GetXaxis()->SetTitle("Initial polar angle (rad)");
  fit_polar_histo->GetYaxis()->SetTitle("Occurrencies");
  gStyle->SetOptStat(2210);
  fit_polar_histo->Draw();
  fit_graphs->cd(3);
  fit_impulse_histo->GetXaxis()->SetTitle("Initial impulse module (unspecified)");
  fit_impulse_histo->GetYaxis()->SetTitle("Occurrencies");
  gStyle->SetOptStat(2210);
  fit_impulse_histo->Draw();
  fit_graphs->cd(4);
  all_difference->GetXaxis()->SetTitle("Difference between corresponding bins");
  all_difference->GetYaxis()->SetTitle("Occurrencies");
  gStyle->SetOptStat(2200);
  all_difference->Draw();
  fit_graphs->cd(5);
  pk_difference->GetXaxis()->SetTitle("Difference between corresponding bins");
  pk_difference->GetYaxis()->SetTitle("Occurrencies");
  gStyle->SetOptStat(2200);
  pk_difference->Draw();  
  fit_graphs->cd(6);
  fit_invariant_mass_decayed_histo->GetXaxis()->SetTitle("Invariant mass (unspecified)");
  fit_invariant_mass_decayed_histo->GetYaxis()->SetTitle("Occurrencies");
  gStyle->SetOptStat(2200);
  fit_invariant_mass_decayed_histo->Draw();
  fit_graphs->SaveAs("_fit_graphs.pdf");
  fit_graphs->SaveAs("_fit_graphs.C");
  canvases->WriteObject(fit_graphs, "fit_graphs"); 
}