

#include "particle.hpp"

#include <cmath>
#include <iostream>

#include "resonancetype.hpp"

namespace p {
void Momentum::print() const {
  std::cout << "Momentum: "
            << "(" << x << ", " << y << ", " << z << ")";
};
double Momentum::norm() const { return std::hypot(x, y, z); }
Particle::Particle(char* name, double x = 0, double y = 0, double z = 0)
    : momentum_{x, y, z} {
  std::size_t index = FindParticle(name);
  if (index != types_.size()) {
    std::cout << "abort \n";
  } else {
    index_ = index;
  }
}
Momentum operator+(Momentum const& a, Momentum const& b){
    return Momentum {a.x + b.x, a.y + b.y, a.z + b.z}; 
}
int Particle::getIndex() const { return index_; }
std::size_t Particle::FindParticle(const char* name) {
  for (size_t i = 0; i < types_.size(); ++i) {
    if (*types_[i]->getName() == *name) {
      return i;
    }
  }
  std::cout << "not found \n";
  return types_.size();
}
void Particle::AddParticleType(const char* name, const double mass,
                               const int charge, const double width = 0) {
  if (FindParticle(name) == types_.size() && types_.size() <= maxtypes) {
    if (width == 0) {
      ParticleType* particle = new ParticleType(name, mass, charge);
      types_.push_back(particle);
    } else {
      ResonanceType* particle = new ResonanceType(name, mass, charge, width);
      types_.push_back(particle);
    }
    return;
  }
  std::cout << "Cannot add \n";
};
void Particle::setIndex(const int index) { index_ = index; };
void Particle::setIndex(const char* name) {
  std::size_t index = FindParticle(name);
  if (index == types_.size()) {
    std::cout << "abort \n";
  } else {
    index_ = index;
  }
};
void Particle::PrintParticleTypes() {
  for (size_t i = 0; i < types_.size(); ++i) {
    types_[i]->print();
    std::cout << "\n";
  }
};
void Particle::printParticle() {
  std::cout << "Index: " << index_ << "   Name: " << *types_[index_]->getName();
  momentum_.print();
  std::cout << "\n";
};
Momentum Particle::getMomentum() const { return momentum_; }
double Particle::getMass() const { return types_[index_]->getMass(); }
double Particle::getEnergy() const {
  return std::hypot(getMass(), momentum_.norm());
}
double Particle::getInvariantMass(Particle const& other) const{
    return std::sqrt(std::pow(other.getEnergy() + this->getEnergy(),2) - std::pow((this->momentum_ + other.momentum_).norm(), 2));
}
void Particle::setMomentum(double px, double py, double pz){
    momentum_.x = px;
    momentum_.y = py;
    momentum_.z = pz;
}
}  // namespace p