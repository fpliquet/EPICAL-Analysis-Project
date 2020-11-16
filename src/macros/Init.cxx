#include <iostream>

#include "TH2.h"
#include "TCanvas.h"

#include "/Users/fpliquett/work/FoCal/analysiscode/mTowerProject/include/mTowerAnalysisObject.h"

using namespace std;

int main (int argc, char** argv)
{
  mTowerAnalysisObject ao(1413);
  TH2C* chip = ao.InitHist2DChip<TH2C>("h2_chip");
  // for (int col = 0; col < 1024; ++col) for (int row = 0; row < 512; ++row) chip->Fill(col, row);
  TCanvas* c = new TCanvas("c","c");
  chip->Draw("colz");
  c->SaveAs("chip.pdf");

  return 0;
}
