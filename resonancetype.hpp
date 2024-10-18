#ifndef RESONANCETYPE_H
#define RESONANCETYPE_H
#include "particletype.hpp"
namespace p {
class ResonanceType : public ParticleType {
 public:
  double getWidth() const;
  void print() const;
  ResonanceType(const char*, const double, const int, const double);

 private:
  const double width_;
};
}  // namespace p

#endif