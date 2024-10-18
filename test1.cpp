#include "resonancetype.hpp"
#include <iostream>

int main(){
const int e_charge{-1};

    p::ParticleType* h[2];
    h[0] = new p::ParticleType("battazzi", 9.11E-31, e_charge);
    h[1] = new p::ResonanceType("bandini", 9.9E-31, 0, 10);
    for(auto i=0; i<2; ++i){
        h[i]->print();
        std::cout<< "\n";
    }
}