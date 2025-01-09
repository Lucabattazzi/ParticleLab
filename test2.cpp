#include <iostream>
#include <string>

#include "particle.hpp"
#include "resonancetype.hpp"

int main() {
  p::Particle::AddParticleType("pion+", 0.13957, 1., 0.);
  p::Particle::AddParticleType("pion-", 0.13957, -1., 0.);
  p::Particle::AddParticleType("kaon+", 0.49367, 1., 0.);
  p::Particle::AddParticleType("kaon-", 0.49367, -1., 0.);
  p::Particle::AddParticleType("proton+", 0.93827, 1., 0.);
  p::Particle::AddParticleType("proton-", 0.93827, -1., 0.);
  p::Particle::AddParticleType("k*", 0.89166, 0., 0.050);
  p::Particle::PrintParticleTypes();

  return 0;
}