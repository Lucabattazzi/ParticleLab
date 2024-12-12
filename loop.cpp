#include <TFile.h>
#include <TH1F.h>
#include <TMath.h>
#include <TRandom.h>

#include <cmath>
#include <iostream>

#include "particle.hpp"
#include "particletype.hpp"

void loop() {
  p::Particle::AddParticleType("pion+", 0.13957, 1, 0.);
  p::Particle::AddParticleType("pion-", 0.13957, -1, 0.);
  p::Particle::AddParticleType("kaon+", 0.49367, 1, 0.);
  p::Particle::AddParticleType("kaon-", 0.49367, -1, 0.);
  p::Particle::AddParticleType("proton+", 0.93827, 1, 0.);
  p::Particle::AddParticleType("proton-", 0.93827, -1, 0.);
  p::Particle::AddParticleType("k*", 0.89166, 0, 0.050);
  TRandom randGen;
  gRandom->SetSeed();
  std::vector<p::Particle> event;
  event.reserve(100);
  std::vector<p::Particle> decayed;
  decayed.reserve(20);
  std::vector<p::Particle> stable;
  stable.reserve(120);
  TH1F* types_histo = new TH1F("h1", "Particle types", 7, 0, 7);  // ricorda di aggiornare l'asse delle ascisse
                                                                  // inserendo i nomi delle particelle
  TH1F* azimuth_histo = new TH1F("h2", "Azimuthal angle", 10000, 0, 2 * TMath::Pi());
  TH1F* polar_histo = new TH1F("h3", "Polar angle", 10000, 0, TMath::Pi());
  TH1F* impulse_histo = new TH1F("h4", "Impulse", 100000, 0, 9);                  // all ranges to be set properly
  TH1F* transimpulse_histo = new TH1F("h5", "Transverse impulse", 100000, 0, 7);  // English?
  TH1F* energy_histo = new TH1F("h6", "Energy", 10000, 0, 8);
  TH1F* invariant_mass__all_histo = new TH1F("h7", "Invariant mass between all particles", 1000000, 0, 8);                               // on stable
  TH1F* invariant_mass__same_histo = new TH1F("h8", "Invariant mass between particles of same charge", 1000000, 0, 8);                   // on stable
  TH1F* invariant_mass__opposite_histo = new TH1F("h9", "Invariant mass between particles of opposite charge", 1000000, 0, 8);           // on stable
  TH1F* invariant_mass__same_pk_histo = new TH1F("h10", "Invariant mass between pions and kaons of same charge", 100000, 0, 8);          // on stable
  TH1F* invariant_mass__opposite_pk_histo = new TH1F("h11", "Invariant mass between pions and kaons of opposite charge", 100000, 0, 8);  // on stable
  TH1F* invariant_mass_decayed_histo = new TH1F("h12", "Invariant mass between decayed particles", 1000, 0.4, 1.4);                      // on decayed, for benchmark
                                                                                                                                         // for (int i = 0; i < 10E5; ++i) {
                                                                                                                                         //   for (int j = 0; j < 10E2; j++) {
  for (int i = 0; i < 1E5; ++i) {
    // std::cout << i << "\n";
    for (int j = 0; j < 100; j++) {
      double phi = randGen.Uniform(2 * TMath::Pi());
      double theta = randGen.Uniform(TMath::Pi());
      double norm = randGen.Exp(1.);
      azimuth_histo->Fill(phi);
      polar_histo->Fill(theta);
      impulse_histo->Fill(norm);
      p::Momentum momentum{norm * TMath::Sin(theta) * TMath::Cos(phi), norm * TMath::Sin(theta) * TMath::Sin(phi), norm * TMath::Cos(theta)};
      double pro = randGen.Uniform(1);
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
    }

    for (std::size_t i = 0; i < event.size(); ++i) {
      types_histo->Fill(event[i].getIndex());
      impulse_histo->Fill(event[i].getMomentum().norm());
      energy_histo->Fill(event[i].getEnergy());
      transimpulse_histo->Fill(std::hypot(event[i].getMomentum().x, event[i].getMomentum().y));
    }
    for (std::size_t i = 0; i < decayed.size(); i += 2) {  // modificato in maniera da fare il calcolo solo su figlie della stessa madre
      double mass = decayed[i].getInvariantMass(decayed[i + 1]);
      invariant_mass_decayed_histo->Fill(mass);
    }
    for (std::size_t i = 0; i < stable.size(); ++i) {
      for (std::size_t j = i + 1; j < stable.size(); ++j) {
        double mass = stable[i].getInvariantMass(stable[j]);
        invariant_mass__all_histo->Fill(mass);
        if (stable[i].getCharge() == stable[j].getCharge()) {
          invariant_mass__same_histo->Fill(mass);
          if (((stable[i].getName() == "pion+" && stable[j].getName() == "kaon+") || (stable[i].getName() == "kaon+" && stable[j].getName() == "pion+")) || (stable[i].getName() == "pion-" && stable[j].getName() == "kaon-") || (stable[i].getName() == "kaon-" && stable[j].getName() == "pion-")) {
            invariant_mass__same_pk_histo->Fill(mass);
          };  // else nothing
        } else {
          invariant_mass__opposite_histo->Fill(mass);
          if (((stable[i].getName() == "pion+" && stable[j].getName() == "kaon-") || (stable[i].getName() == "kaon-" && stable[j].getName() == "pion+")) || (stable[i].getName() == "pion-" && stable[j].getName() == "kaon+") || (stable[i].getName() == "kaon+" && stable[j].getName() == "pion-")) {
            invariant_mass__opposite_pk_histo->Fill(mass);
          };  // else nothing
        }     // carica
      }
    }
    event.clear();  // i vettori vanno svuotati prima di ogni loop interno, non alla fine
    decayed.clear();
    stable.clear();
  }
  TFile* file = new TFile("particle.root", "RECREATE");  // creates if non-existing, ovewrites otherwise.
  // TList* histoList = new TList();
  // for (Int_t i = 1; i <= 12; i++) {
  //   testList->Add(h[i]);
  // }
  // histo_list->Write();
  types_histo->Write("h1");
  azimuth_histo->Write("h2");
  impulse_histo->Write("h3");
  polar_histo->Write("h4");
  transimpulse_histo->Write("h5");
  energy_histo->Write("h6");
  invariant_mass__all_histo->Write("h7");
  invariant_mass__same_histo->Write("h8");
  invariant_mass__opposite_histo->Write("h9");
  invariant_mass__same_pk_histo->Write("h10");
  invariant_mass__opposite_pk_histo->Write("h11");
  invariant_mass_decayed_histo->Write("h12");
  file->Close();
  // delete file;
}
