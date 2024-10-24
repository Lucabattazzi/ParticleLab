#include <TRandom.h>

#include <TMath>

#include "particle.cpp"
#include "particletype.cpp"

int main() {
  p::Particle::AddParticleType("pion+", 0.13957, 1., 0.);
  p::Particle::AddParticleType("pion-", 0.13957, -1., 0.);
  p::Particle::AddParticleType("kaon+", 0.49367, 1., 0.);
  p::Particle::AddParticleType("kaon-", 0.49367, -1., 0.);
  p::Particle::AddParticleType("proton+", 0.93827, 1., 0.);
  p::Particle::AddParticleType("proton-", 0.93827, -1., 0.);
  p::Particle::AddParticleType("k*", 0.89166, 0., 0.050);
  gRandom->SetSeed();
  std::vector event;
  event.reserve(100);
  std::vector decayed;
  decayed.reserve(20);
  std::vector stable;
  stable.reserve(120);
  TH1F* types_histo = new TH1F()  // ricorda di aggiornare l'asse delle ascisse
                                  // inserendo i nomi delle particelle
      TH1F* azimuth_histo =
          new TH1F("azimuth_histo", "Azimuthal angle", 0, 2 * TMath::Pi(), 100);
  TH1F* polar_histo =
      new TH1F("polar_histo", "Polar angle", 0, TMath::Pi(), 100);
  TH1F* impulse_histo = new TH1F("impulse_histo", "Impulse", 100);
  TH1F* energy_histo = new TH1F("energy_histo", "Energy", 100);
  TH1F* invariant_mass__all_histo =
      new TH1F("invariant_mass_all_histo",
               "Invariant mass between all particles", 100);  // on stable
  TH1F* invariant_mass__same_histo = new TH1F(
      "invariant_mass_same_histo",
      "Invariant mass between particles of same charge", 100);  // on stable
  TH1F* invariant_mass__opposite_histo = new TH1F(
      "invariant_mass_opposite_histo",
      "Invariant mass between particles of opposite charge", 100);  // on stable
  TH1F* invariant_mass__same_pk_histo =
      new TH1F("invariant_mass_same_pk_histo",
               "Invariant mass between pions and kaons of same charge",
               100);  // on stable
  TH1F* invariant_mass__opposite_pk_histo =
      new TH1F("invariant_mass_opposite_pk_histo",
               "Invariant mass between pions and kaons of opposite charge",
               100);  // on stable
  TH1F* invariant_mass_decayed_histo = new TH1F(
      "invariant_mass_decayed_histo",
      "Invariant massbetween decayed particles")  // on decayed, for benchmark
      for (int i = 0; i < 10E5; ++i) {
    for (int j = 0; j < 10E2; j++) {
      double phi = TRandom::Uniform(2 * TMath::Pi());
      double theta = TRandom::Uniform(TMath::Pi());
      double norm = TRandom::Exp(1.);
      p::Momentum momentum{norm * TMath::Sin(theta) * TMath::Cos(phi),
                           norm * TMath::Sin(theta) * TMath::Sin(phi),
                           norm * TMath::Cos(theta)};
      double pro = gRandom->Rndm();
      if (pro < 0.4) {
        p::Particle particle("pion+", momentum);
      } else if (pro < 0.8) {
        p::Particle particle("pion-", momentum);
      } else if (pro < 0.85) {
        p::Particle particle("kaon+", momentum);
      } else if (pro < 0.9) {
        p::Particle particle("kaon-", momentum);
      } else if (pro < 0.945) {
        p::Particle particle("proton+", momentum);
      } else if (pro < 0.99) {
        p::Particle particle("proton-", momentum);
      } else {
        p::Particle particle("k*", momentum);
      }
      event.push_back(particle);
      if (particle.getName() == "k*") {
        if (gRandom->Rndm() < 0.5) {
          p::Particle pion("pion+");
          p::Particle kaon("kaon-");
          particle.Decay2Body(pion, kaon);
        } else {
          p::Particle pion("pion-");
          p::Particle kaon("kaon+");
          particle.Decay2Body(pion, kaon);
        }
        stable.push_back(pion);
        stable.push_back(kaon);
        decayed.push_back(pion);
        decayed.push_back(kaon);
      } else {
        stable.push_back(particle);
      }
      event.clear();
      decayed.clear();
      stable.clear();
    }
  }
}