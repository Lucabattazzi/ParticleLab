#include <TMath.h>
#include <TRandom.h>

#include <iostream>

#include "TF1.h"
#include "TFile.h"
#include "TH1F.h"

void testfunct() {
  TF1* gaus_fit = new TF1("gaus_fit", "[2]/(sqrt(2*pi)*[0])*exp(-((x-[1])^2)/(2*[0]^2))", 0.6, 1.2);
  TH1F* histo = new TH1F("histo", "Energy", 1E4, 0, 8);
  for (int i = 0; i < 1E4; ++i) {
    double x = gRandom->Gaus(0.89, 0.05);
    histo->Fill(x);
  }
  TFile* file1 = new TFile("file1.root", "RECREATE");
  TFile* file2 = new TFile("file2.root", "RECREATE");
  file1->WriteObject(histo, "histo");
  gaus_fit->SetParameters(0.05, 0.89);
  histo->Fit("gaus_fit", "R");
  file2->WriteObject(histo, "histo");
}