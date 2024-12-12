#include <iostream>
#include <string>

#include "particle.hpp"
#include "resonancetype.hpp"
// R_LOAD_LIBRARY(particle_cpp.so)
// R_LOAD_LIBRARY(particletype_cpp.so)
// R_LOAD_LIBRARY(resonancetype_cpp.so)

int main() {
  p::Particle::AddParticleType("pion+", 0.13957, 1., 0.);
  p::Particle::AddParticleType("pion-", 0.13957, -1., 0.);
  p::Particle::AddParticleType("kaon+", 0.49367, 1., 0.);
  p::Particle::AddParticleType("kaon-", 0.49367, -1., 0.);
  p::Particle::AddParticleType("proton+", 0.93827, 1., 0.);
  p::Particle::AddParticleType("proton-", 0.93827, -1., 0.);
  p::Particle::AddParticleType("k*", 0.89166, 0., 0.050);
  p::Particle::PrintParticleTypes();
  // p::Particle particle1("pippo", {0., 0., 0.});
  // std::cout << "1";
  // p::Particle particle2("pion-", {0., 0., 0.});
  // std::cout << "2";
  // particle1.printParticle();
  // // std::cout << "1";
  // particle2.printParticle();
  // // std::cout << "2";

  return 0;
}