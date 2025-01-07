#include <TFile.h>
#include <TH1F.h>
#include <TMath.h>
#include <TRandom.h>
#include <stdlib.h>

#include <cmath>
#include <iostream>

#include "particle.hpp"
#include "particletype.hpp"

int loop() {
  p::Particle::AddParticleType("pion+", 0.13957, 1, 0.);
  p::Particle::AddParticleType("pion-", 0.13957, -1, 0.);
  p::Particle::AddParticleType("kaon+", 0.49367, 1, 0.);
  p::Particle::AddParticleType("kaon-", 0.49367, -1, 0.);
  p::Particle::AddParticleType("proton+", 0.93827, 1, 0.);
  p::Particle::AddParticleType("proton-", 0.93827, -1, 0.);
  p::Particle::AddParticleType("k*", 0.89166, 0, 0.050);
  gRandom->SetSeed();
  std::vector<p::Particle> event;  // all particles of first generation (including K*)
  event.reserve(100);
  std::vector<p::Particle> decayed;  // K* daughters
  decayed.reserve(20);
  std::vector<p::Particle> stable;  // allstable particles (including K* daughters)
  stable.reserve(120);
  TFile* data = new TFile("particle.root", "RECREATE");
  TH1F* types_histo = new TH1F("types_histo", "Particle types", 7, 0, 7);
  TH1F* azimuth_histo = new TH1F("azimuth_histo", "Azimuthal angle", 1E3, 0, 2 * TMath::Pi());
  TH1F* polar_histo = new TH1F("polar_histo", "Polar angle", 1E3, 0, TMath::Pi());
  TH1F* impulse_histo = new TH1F("impulse_histo", "Impulse module", 1E3, 0, 9);
  TH1F* transimpulse_histo = new TH1F("transimpulse_histo", "Transverse impulse", 1E4, 0, 7);
  TH1F* energy_histo = new TH1F("energy_histo", "Energy", 1E4, 0, 6.4);
  TH1F* invariant_mass_all_histo = new TH1F("invariant_mass_all_histo", "Invariant mass between all particles", 1E4, 0, 8);
  TH1F* invariant_mass_same_histo = new TH1F("invariant_mass_same_histo", "Invariant mass between particles of same charge", 5E2, 0, 8);
  TH1F* invariant_mass_opposite_histo = new TH1F("invariant_mass_opposite_histo", "Invariant mass between particles of opposite charge", 5E2, 0, 8);
  TH1F* invariant_mass_same_pk_histo = new TH1F("invariant_mass_same_pk_histo", "Invariant mass between pions and kaons of same charge", 1E3, 0, 8);
  TH1F* invariant_mass_opposite_pk_histo = new TH1F("invariant_mass_opposite_pk_histo", "Invariant mass between pions and kaons of opposite charge", 1E3, 0, 8);
  TH1F* invariant_mass_decayed_histo = new TH1F("invariant_mass_decayed_histo", "Decayed particles", 1E3, 0.4, 1.4);

  for (int i = 0; i < 1E5; ++i) {
    for (int j = 0; j < 100; j++) {
      try {
        double phi = gRandom->Uniform(2 * TMath::Pi());
        double theta = gRandom->Uniform(TMath::Pi());
        double norm = gRandom->Exp(1.);
        azimuth_histo->Fill(phi);
        polar_histo->Fill(theta);
        impulse_histo->Fill(norm);
        p::Momentum momentum{norm * TMath::Sin(theta) * TMath::Cos(phi), norm * TMath::Sin(theta) * TMath::Sin(phi), norm * TMath::Cos(theta)};
        double pro = gRandom->Uniform(1);
        p::Particle particle;
        particle.setMomentum(momentum);
        if (pro < 0.4) {
          particle.setIndex("pion+");
        } else if (pro < 0.8) {
          particle.setIndex("pion-");
        } else if (pro < 0.85) {
          particle.setIndex("kaon+");
        } else if (pro < 0.9) {
          particle.setIndex("kaon-");
        } else if (pro < 0.945) {
          particle.setIndex("proton+");
        } else if (pro < 0.99) {
          particle.setIndex("proton-");
        } else {
          particle.setIndex("k*");
        }
        event.push_back(particle);
        if (particle.getName() == "k*") {
          p::Particle pion;
          p::Particle kaon;
          if (gRandom->Rndm() < 0.5) {
            pion.setIndex("pion+");
            kaon.setIndex("kaon-");
            particle.Decay2Body(pion, kaon);
          } else {
            pion.setIndex("pion-");
            kaon.setIndex("kaon+");
            particle.Decay2Body(pion, kaon);
          }
          stable.push_back(pion);
          stable.push_back(kaon);
          decayed.push_back(pion);
          decayed.push_back(kaon);
        } else {
          stable.push_back(particle);
        }
      } catch (std::runtime_error const& e) {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
      }
    }

    for (std::size_t i = 0; i < event.size(); ++i) {
      types_histo->Fill(event[i].getIndex());
      energy_histo->Fill(event[i].getEnergy());
      transimpulse_histo->Fill(std::hypot(event[i].getMomentum().x, event[i].getMomentum().y));
    }
    for (std::size_t i = 0; i < decayed.size(); i += 2) {
      double mass = decayed[i].getInvariantMass(decayed[i + 1]);
      invariant_mass_decayed_histo->Fill(mass);
    }
    for (std::size_t i = 0; i < stable.size(); ++i) {
      for (std::size_t j = i + 1; j < stable.size(); ++j) {
        double mass = stable[i].getInvariantMass(stable[j]);
        invariant_mass_all_histo->Fill(mass);
        if (stable[i].getCharge() == stable[j].getCharge()) {
          invariant_mass_same_histo->Fill(mass);
          if (((stable[i].getName() == "pion+" && stable[j].getName() == "kaon+") || (stable[i].getName() == "kaon+" && stable[j].getName() == "pion+")) || (stable[i].getName() == "pion-" && stable[j].getName() == "kaon-") || (stable[i].getName() == "kaon-" && stable[j].getName() == "pion-")) {
            invariant_mass_same_pk_histo->Fill(mass);
          };
        } else {
          invariant_mass_opposite_histo->Fill(mass);
          if (((stable[i].getName() == "pion+" && stable[j].getName() == "kaon-") || (stable[i].getName() == "kaon-" && stable[j].getName() == "pion+")) || (stable[i].getName() == "pion-" && stable[j].getName() == "kaon+") || (stable[i].getName() == "kaon+" && stable[j].getName() == "pion-")) {
            invariant_mass_opposite_pk_histo->Fill(mass);
          };
        }
      }
    }
    event.clear();
    decayed.clear();
    stable.clear();
  }
  data->Write();
  data->Close();
  return 0;  // fine execution of the program
}