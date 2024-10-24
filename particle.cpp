

#include "particle.hpp"

#include <cmath>
#include <cstdlib>
#include <iostream>

#include "resonancetype.hpp"

namespace p {
void Momentum::print() const {
  std::cout << "Momentum: "
            << "(" << x << ", " << y << ", " << z << ")";
};
double Momentum::norm() const { return std::hypot(x, y, z); }
Particle::Particle(std::string name) : name_ { name };
Particle::Particle(std::string name, Momentum momentum) : momentum_{momentum} {
  std::size_t index = FindParticle(name);
  if (index != types_.size()) {
    std::cout << "abort \n";
  } else {
    index_ = index;
  }
}
Momentum operator+(Momentum const& a, Momentum const& b) {
  return Momentum{a.x + b.x, a.y + b.y, a.z + b.z};
}

std::vector<ParticleType*> Particle::types_;
int Particle::getIndex() const { return index_; }
std::size_t Particle::FindParticle(const std::string name) {
  for (size_t i = 0; i < types_.size(); ++i) {
    if (types_[i]->getName() == name) {
      return i;
    }
  }
  std::cout << "not found \n";
  return types_.size();
}
void Particle::AddParticleType(const std::string name, double mass, int charge,
                               double width = 0.) {
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
void Particle::setIndex(const std::string name) {
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
  std::cout << "Index: " << index_ << "   Name: " << types_[index_]->getName();
  momentum_.print();
  std::cout << "\n";
};
Momentum Particle::getMomentum() const { return momentum_; }
double Particle::getMass() const { return types_[index_]->getMass(); }
double Particle::getEnergy() const {
  return std::hypot(getMass(), momentum_.norm());
}
double Particle::getInvariantMass(Particle const& other) const {
  return std::sqrt(std::pow(other.getEnergy() + this->getEnergy(), 2) -
                   std::pow((this->momentum_ + other.momentum_).norm(), 2));
}
void Particle::setMomentum(double px, double py, double pz) {
  momentum_.x = px;
  momentum_.y = py;
  momentum_.z = pz;
}
int Particle::Decay2Body(Particle& dau1, Particle& dau2) const {
  if (getMass() == 0.0) {
    std::cout << "Decayment cannot be preformed if mass is zero\n";
    return 1;
  }
  double massMot = getMass();
  double massDau1 = dau1.getMass();
  double massDau2 = dau2.getMass();

  if (index_ > -1) {  // add width effect

    // gaussian random numbers

    float x1, x2, w, y1;

    double invnum = 1. / RAND_MAX;
    do {
      x1 = 2.0 * rand() * invnum - 1.0;
      x2 = 2.0 * rand() * invnum - 1.0;
      w = x1 * x1 + x2 * x2;
    } while (w >= 1.0);

    w = sqrt((-2.0 * log(w)) / w);
    y1 = x1 * w;

    massMot += types_[index_]->getWidth() * y1;
  }

  if (massMot < massDau1 + massDau2) {
    std::cout
        << "Decayment cannot be preformed because mass is too low in this "
           "channel\n";
    return 2;
  }

  double pout =
      sqrt(
          (massMot * massMot - (massDau1 + massDau2) * (massDau1 + massDau2)) *
          (massMot * massMot - (massDau1 - massDau2) * (massDau1 - massDau2))) /
      massMot * 0.5;

  double norm = 2 * M_PI / RAND_MAX;

  double phi = rand() * norm;
  double theta = rand() * norm * 0.5 - M_PI / 2.;
  dau1.setMomentum(pout * sin(theta) * cos(phi), pout * sin(theta) * sin(phi),
                   pout * cos(theta));
  dau2.setMomentum(-pout * sin(theta) * cos(phi), -pout * sin(theta) * sin(phi),
                   -pout * cos(theta));

  double energy = sqrt(momentum_.x * momentum_.x + momentum_.y * momentum_.y +
                       momentum_.z * momentum_.z + massMot * massMot);

  double bx = momentum_.x / energy;
  double by = momentum_.y / energy;
  double bz = momentum_.z / energy;

  dau1.Boost(bx, by, bz);
  dau2.Boost(bx, by, bz);

  return 0;
}
void Particle::Boost(double bx, double by, double bz) {
  double energy = getEnergy();

  // Boost this Lorentz vector
  double b2 = bx * bx + by * by + bz * bz;
  double gamma = 1.0 / sqrt(1.0 - b2);
  double bp = bx * momentum_.x + by * momentum_.y + bz * momentum_.z;
  double gamma2 = b2 > 0 ? (gamma - 1.0) / b2 : 0.0;

  momentum_.x += gamma2 * bp * bx + gamma * bx * energy;
  momentum_.y += gamma2 * bp * by + gamma * by * energy;
  momentum_.z += gamma2 * bp * bz + gamma * bz * energy;
}
}  // namespace p