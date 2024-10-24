
#include "resonancetype.hpp"

#include <iostream>
namespace p {
double ResonanceType::getWidth() const { return width_; }
void ResonanceType::print() const {
  ParticleType::print();
  std::cout << "   Width: " << width_;
}
ResonanceType::ResonanceType(const std::string name, const double mass,
                             const int charge, const double width)
    : ParticleType::ParticleType(name, mass, charge), width_{width} {};

}  // namespace p