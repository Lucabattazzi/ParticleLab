#ifndef PARTICLETYPE_H
#define PARTICLETYPE_H
namespace p {
class ParticleType {
 public:
  const char* getName() const;
  double getMass() const;
  int getCharge() const;
  virtual void print() const;
  ParticleType(const char*, const double, const int);

 private:
  const char* name_;
  const double mass_;
  const int charge_;
};

}  // namespace p
#endif