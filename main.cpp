#include <TFile.h>
#include <TH1F.h>
#include <TMath.h>
#include <TRandom.h>

#include <cmath>
#include <iostream>

#include "particle.hpp"
#include "particletype.hpp"

void loop() {
  p::Particle::AddParticleType("pion+", 0.13957, 1., 0.);
  p::Particle::AddParticleType("pion-", 0.13957, -1., 0.);
  p::Particle::AddParticleType("kaon+", 0.49367, 1., 0.);
  p::Particle::AddParticleType("kaon-", 0.49367, -1., 0.);
  p::Particle::AddParticleType("proton+", 0.93827, 1., 0.);
  p::Particle::AddParticleType("proton-", 0.93827, -1., 0.);
  p::Particle::AddParticleType("k*", 0.89166, 0., 0.050);
  TRandom randGen;
  gRandom->SetSeed(567856);
  std::vector<p::Particle> event;
  event.reserve(100);
  std::vector<p::Particle> decayed;
  decayed.reserve(20);
  std::vector<p::Particle> stable;
  stable.reserve(120);
  TH1F* types_histo = new TH1F("types_histo", "Particle types", 7, 0, 7);  // ricorda di aggiornare l'asse delle ascisse
                                                                           // inserendo i nomi delle particelle
  TH1F* azimuth_histo = new TH1F("azimuth_histo", "Azimuthal angle", 100, 0, 2 * TMath::Pi());
  TH1F* polar_histo = new TH1F("polar_histo", "Polar angle", 100, 0, TMath::Pi());
  TH1F* impulse_histo = new TH1F("impulse_histo", "Impulse", 100, 0, 10);                       // all ranges to be set properly
  TH1F* transimpulse_histo = new TH1F("transimpulse_histo", "Transverse impulse", 100, 0, 10);  // English?
  TH1F* energy_histo = new TH1F("energy_histo", "Energy", 100, 0, 10);
  TH1F* invariant_mass__all_histo = new TH1F("invariant_mass_all_histo", "Invariant mass between all particles", 100, 0, 10);                                       // on stable
  TH1F* invariant_mass__same_histo = new TH1F("invariant_mass_same_histo", "Invariant mass between particles of same charge", 100, 0, 10);                          // on stable
  TH1F* invariant_mass__opposite_histo = new TH1F("invariant_mass_opposite_histo", "Invariant mass between particles of opposite charge", 100, 0, 10);              // on stable
  TH1F* invariant_mass__same_pk_histo = new TH1F("invariant_mass_same_pk_histo", "Invariant mass between pions and kaons of same charge", 100, 0, 10);              // on stable
  TH1F* invariant_mass__opposite_pk_histo = new TH1F("invariant_mass_opposite_pk_histo", "Invariant mass between pions and kaons of opposite charge", 100, 0, 10);  // on stable
  TH1F* invariant_mass_decayed_histo = new TH1F("invariant_mass_decayed_histo", "Invariant massbetween decayed particles", 100, 0, 10);                             // on decayed, for benchmark
                                                                                                                                                                    // for (int i = 0; i < 10E5; ++i) {
  std::cout << "error1\n";                                                                                                                                          //   for (int j = 0; j < 10E2; j++) {
  for (int i = 0; i < 200; ++i) {
    std::cout << i << "\n";
    std::vector<p::Particle> event;
    event.reserve(100);
    std::vector<p::Particle> decayed;
    decayed.reserve(20);
    std::vector<p::Particle> stable;
    stable.reserve(120);

    for (int j = 0; j < 10; j++) {
      std::cout << j << "\n";
      double phi = randGen.Uniform(2 * TMath::Pi());
      double theta = randGen.Uniform(TMath::Pi());
      double norm = randGen.Exp(1.);
      azimuth_histo->Fill(phi);
      polar_histo->Fill(theta);
      impulse_histo->Fill(norm);
      p::Momentum momentum{norm * TMath::Sin(theta) * TMath::Cos(phi), norm * TMath::Sin(theta) * TMath::Sin(phi), norm * TMath::Cos(theta)};
      double pro = gRandom->Rndm();
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
      std::cout << "Progressive count 1\n";
      event.push_back(particle);
      std::cout << "Progressive count 1.1\n";
      if (particle.getName() == "k*") {
        p::Particle pion;
        p::Particle kaon;
        if (gRandom->Rndm() < 0.5) {
          particle.Decay2Body(pion, kaon);
          pion.setIndex("pion+");
          kaon.setIndex("kaon-");
        } else {
          particle.Decay2Body(pion, kaon);
          pion.setIndex("pion-");
          kaon.setIndex("kaon+");
        }
std::cout << "Progressive count 2 \n";
        stable.push_back(pion);
        stable.push_back(kaon);
        decayed.push_back(pion);
        decayed.push_back(kaon);
std::cout << "Progressive count2.2\n";
      } else {
        std::cout << "Progressive count3\n";
        stable.push_back(particle);
        std::cout << "Progressive count3.2\n";
      }
      // event.clear();   // se lo mettiamo qui buttiamo via il vettore appena riempito :)
      // decayed.clear();
      // stable.clear();
    }
    std::cout << "error2\n";
    for (std::size_t i = 0; i < event.size(); ++i) {
      types_histo->Fill(event[i].getIndex());
      impulse_histo->Fill(event[i].getMomentum().norm());
      energy_histo->Fill(event[i].getEnergy());
      transimpulse_histo->Fill(std::hypot(event[i].getMomentum().x, event[i].getMomentum().y));
    }
    std::cout << "error3\n";
    for (std::size_t i = 0; i < decayed.size(); i += 2) {  // modificato in maniera da fare il calcolo solo su figlie della stessa madre
      double mass = decayed[i].getInvariantMass(decayed[i + 1]);
      invariant_mass_decayed_histo->Fill(mass);
    }
    std::cout << "error4\n";
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
    std::cout << "error5\n";
    event.clear();  // i vettori vanno svuotati prima di ogni loop interno, non alla fine
    decayed.clear();
    stable.clear();
    std::cout << "error6\n";
  }
  TFile* file = new TFile("partcile.root", "RECREATE");  // creates if non-existing, ovewrites otherwise.
  std::cout << "error7\n";
  azimuth_histo->Draw();
}
