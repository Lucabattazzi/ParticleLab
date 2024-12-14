#include <TFile.h>
#include <TH1F.h>
#include <TMath.h>
#include <TRandom.h>

#include <cmath>
#include <iostream>

#include "particle.hpp"
#include "particletype.hpp"

void testgrandom() {
  gRandom->SetSeed();
  std::cout<< gRandom->Uniform(1.);
}
