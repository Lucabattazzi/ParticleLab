#include <iostream>
void compile() {
  gROOT->LoadMacro("particletype.cpp++");
  gROOT->LoadMacro("resonancetype.cpp++");
  gROOT->LoadMacro("particle.cpp++");
  gROOT->LoadMacro("loop.cpp++");
  gROOT ->LoadMacro("analyze.cpp++");
  gROOT ->LoadMacro("visualize.cpp++");

}