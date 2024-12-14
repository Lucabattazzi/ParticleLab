#include "particletype.hpp"

#include <iostream>
#include <string>
namespace p {

std::string ParticleType::getName() const { return name_; }
double ParticleType::getMass() const { return mass_; } // le funzioni ritornano tipi const, o sbaglio?
int ParticleType::getCharge() const { return charge_; }
void ParticleType::print() const {
  std::cout << "Name: " << name_ << "   Mass: " << mass_
            << "   Charge: " << charge_;
};
ParticleType::ParticleType(const std::string name, const double mass,
                           const int charge)
    : name_{name}, mass_{mass}, charge_{charge} {};
double ParticleType::getWidth() const { return 0.; }
}  // namespace p