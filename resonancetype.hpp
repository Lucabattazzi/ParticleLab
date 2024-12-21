#ifndef RESONANCETYPE_H
#define RESONANCETYPE_H
#include "particletype.hpp"
namespace p {
class ResonanceType : public ParticleType {
 public:
  double getWidth() const override;
  void print() const override;
  ResonanceType(const std::string, const double, const int, const double);

 private:
  const double width_;
};
}  // namespace p

#endif