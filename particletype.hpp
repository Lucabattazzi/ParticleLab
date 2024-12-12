#ifndef PARTICLETYPE_H
#define PARTICLETYPE_H
#include <string>
namespace p {
class ParticleType {
 public:
  const std::string getName() const;
  const double getMass() const;
  const int getCharge() const;
  virtual void print() const;
  virtual double getWidth() const;
  ParticleType(const std::string, const double, const int);

 private:
  const std::string name_;
  const double mass_;
  const int charge_;
};

}  // namespace p
#endif