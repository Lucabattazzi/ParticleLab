#include "particletype.hpp"

#include <iostream>
namespace p {

const char* ParticleType::getName() const { return name_; }
double ParticleType::getMass() const { return mass_; }
int ParticleType::getCharge() const { return charge_; }
void ParticleType::print() const {
  std::cout << "Name: " << name_ << "   Mass: " << mass_
            << "   Charge: " << charge_;
};
ParticleType::ParticleType(const char* name, const double mass,
                           const int charge)
    : name_{name}, mass_{mass}, charge_{charge} {};
double ParticleType::getWidth() const { return 0.; }
}  // namespace p