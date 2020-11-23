#include <vector>
#include <algorithm>

#include "TH2.h"
#include "TFile.h"

#include "../../include/EPICALAnalysisObject.h"
#include "../../include/EPICALGeometry.h"
#include "../../include/EPICALUtility.h"

using namespace std;


int main (int argc, char** argv)
{

  if (argc != 1) { printf(" ### Macro does not expect any argument. \n"); return 1;}

  vector<int> ivAnaRuns = GetAnalysisRunList(); // list of runs with standard settings
  // vector<int> ivAnaRuns = {1252}; // list of runs with standard settings

  EPICALAnalysisObject ao(ivAnaRuns.at(0));
  EPICALGeometry geo = ao.GetGeometry();
  vector<TH2C*> h2v_commonpixelmask;
  for (int iChip = geo.GetChipMin(); iChip <= geo.GetChipMax(); ++iChip) {
    h2v_commonpixelmask.push_back(ao.InitHist2DChip<TH2C>(Form("h2_pixelmap_chip%i", iChip)));
  }
  TH2C* h2_commonpixelmask_chip;

  vector<TH2C*> h2v_pixelmask_run;
  TH2C* h2_pixelmask_chip;

  const int nMethods = 6; // six methods in total: noisyclass noisyped noisybeam deadclass deadbeam manual
  std::bitset<nMethods> bs_stat_common(0); // status bits for pixel mask
  std::bitset<nMethods> bs_stat_run(0); // status bits for pixel mask

  int iBinCol = 0, iBinRow = 0;

  for (auto& RunNr : ivAnaRuns)
  {
    printf("\n\n ~~~~~ Starting run %i ~~~~~ \n", RunNr);
    EPICALAnalysisObject ao_run = EPICALAnalysisObject(RunNr);
    ao_run.LoadPixelMasks(kAll);
    h2v_pixelmask_run = ao_run.GetPixelMasks();
    for (int iChip = geo.GetChipMin(); iChip <= geo.GetChipMax(); ++iChip) {
      printf(" >>> chip %i \n", iChip);
      h2_commonpixelmask_chip = h2v_commonpixelmask.at(iChip);
      h2_pixelmask_chip       = h2v_pixelmask_run.at(iChip);
      for (int iCol = geo.GetColMin(); iCol <= geo.GetColMax(); ++iCol) {
        iBinCol = h2_commonpixelmask_chip->GetXaxis()->FindBin(iCol);
        for (int iRow = geo.GetRowMin(); iRow <= geo.GetRowMax(); ++iRow) {
          iBinRow = h2_commonpixelmask_chip->GetYaxis()->FindBin(iRow);
          bs_stat_common = h2_commonpixelmask_chip->GetBinContent(iBinCol, iBinRow); // extract current status of pixel in common pixel mask
          bs_stat_run    = h2_pixelmask_chip->GetBinContent(iBinCol, iBinRow); // extract status of pixel in pixel mask of current run
          bs_stat_common |= bs_stat_run; // include set bits of current run in common pixel mask
          h2_commonpixelmask_chip->SetBinContent(iBinCol, iBinRow, bs_stat_common.to_ulong()); // set new status in common pixel mask
        } // row
      } // column
    } // chip
  } // runs

  TFile* f_out = new TFile("../output/rootfiles/pixelmasks/commonpixelmask.root", "RECREATE");
  for (auto& mask : h2v_commonpixelmask) {mask->ResetStats(); mask->Write(); delete mask;}

  delete f_out;
  return 0;
}
