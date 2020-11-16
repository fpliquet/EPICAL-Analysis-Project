#include <iostream>
#include <utility>
#include <cmath>

#include "TFile.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TH2.h"
#include "TUnixSystem.h"

#include "../../include/EPICALAnalysisObject.h"
#include "../../include/EPICALGeometry.h"
#include "../../include/EPICALUtility.h"

using namespace std;

int main (int argc, char** argv)
{

  if (argc == 1) return 1;
  int run = atoi(argv[1]);
  // string str = argv[2];

  bool force = false;

  EPICALAnalysisObject ao(run);
  ao.ProduceHitmaps(force);
  ao.ProduceNoisyPixelMapClassification(force);
  ao.ProduceNoisyPixelMapPedestal(force);
  ao.ProduceNoisyPixelMapBeam(force);
  ao.ProduceDeadPixelMapClassification(force);
  ao.ProduceDeadPixelMapBeam(force);
  ao.ProduceManualPixelMap(force);
  ao.LoadPixelMasks(kAll);
  ao.ApplyPixelMask();

  vector<TH2D*> vh2_hitmaps = ao.GetHitmaps();

  gStyle->SetPadBottomMargin(0.0);
  gStyle->SetPadLeftMargin(0.0);
  gStyle->SetPadTopMargin(0.0);
  gStyle->SetPadRightMargin(0.0);

  TCanvas* c = new TCanvas("c","c");
  c->Divide(6,8,0.,0.);

  int it=1; // iterator for range-based loop
  for (auto& map : vh2_hitmaps)
  {
    c->cd(it);
    map->SetStats(0);
    map->SetTitle(Form("ChipID %i", it-1));
    map->Draw("COLZ");
    ++it;
  }

  string str_outfold = Form("../output/pics/Run%i/hitmaps/", ao.GetRunNr());
  gSystem->Exec(Form("mkdir -p %s", str_outfold.data()));
  string str_outfile = Form("hitmapoverview_Run%i.png", ao.GetRunNr());
  string str_out = str_outfold + str_outfile;
  c->SaveAs(str_out.data());

  return 0;
}
