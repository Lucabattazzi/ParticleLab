#ifndef PARTICLE_H
#define PARTICLE_H
#include <cstdlib>
#include <stdexcept>
#include <vector>

#include "particletype.hpp"

namespace p {
// constexpr int maxtypes = 7; // non ci serve

struct Momentum {
  double x;
  double y;
  double z;
  double norm() const;
  void print() const;
};
Momentum operator+(Momentum const &, Momentum const &);
class Particle {
 public:
  Particle(std::string, Momentum const &);
  Particle() = default;
  Momentum getMomentum() const;
  int getIndex() const;
  int getCharge() const;
  double getMass() const;
  double getEnergy() const;
  double getInvariantMass(Particle const &) const;
  void setMomentum(Momentum const &);
  void setMomentum(double, double, double);
  void setIndex(const std::string);
  void setIndex(const int);
  void printParticle();
  static void PrintParticleTypes();
  static void AddParticleType(const std::string, double, int, double);
  int Decay2Body(Particle &, Particle &) const;
  std::string getName() const;

 private:
  static std::vector<ParticleType *> types_;
  Momentum momentum_;
  int index_;
  static std::size_t FindParticle(const std::string);
  void Boost(double, double, double);
};

}  // namespace p

#endif