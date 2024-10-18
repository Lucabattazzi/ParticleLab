#ifndef PARTICLE_H
#define PARTICLE_H
#include <cstdlib>
#include <vector>

#include "particletype.hpp"

namespace p {
constexpr int maxtypes = 7;

struct Momentum {
  double x;
  double y;
  double z;
  double norm() const; //not const because of std::hypot return type
  void print() const;
};
Momentum operator+(Momentum const&, Momentum const&);
class Particle {
 public:
  static void PrintParticleTypes();
  Momentum getMomentum() const;
   double getMass() const;
  double getEnergy() const;
  double getInvariantMass(Particle const&) const;
  void setMomentum(double, double, double);
  void printParticle();
  Particle(char*, double, double, double);
  int getIndex() const;
  static void AddParticleType(const char*, const double, const int,
                              const double);
  void setIndex(const char*);
  void setIndex(const int);

 private:
  static std::vector<ParticleType*> types_;
  Momentum momentum_;
  int index_;

  static std::size_t FindParticle(const char*);
};

}  // namespace p

#endif