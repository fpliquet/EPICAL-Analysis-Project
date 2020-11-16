#include <iostream>
#include <utility>
#include <cmath>

#include "TFile.h"
#include "TCanvas.h"
#include "TH2.h"
#include "THStack.h"

#include "/Users/fpliquett/work/FoCal/analysiscode/mTowerProject/include/mTowerAnalysisObject.h"
#include "/Users/fpliquett/work/FoCal/analysiscode/mTowerProject/include/mTowerGeometry.h"
#include "/Users/fpliquett/work/FoCal/analysiscode/mTowerProject/include/mTowerUtility.h"
#include "/Users/fpliquett/commoncode/myStyle.h"

using namespace std;


int main (int argc, char** argv)
{

  if (argc == 1) return 1;
  int run = atoi(argv[1]);
  // string str = argv[2];

  bool force = false;

  mTowerAnalysisObject ao(run);
  // ao.ProduceHitmaps(force);
  // ao.LoadHitmaps();
  // ao.ProduceNhitsPerPixel(true);
  // ao.SetHotPixelCriterion(0.001);
  // ao.ProduceNoisyPixelMapClassification(force);
  // ao.ProduceNoisyPixelMapPedestal(force);
  // ao.ProduceNoisyPixelMapBeam(force);
  // ao.ProduceDeadPixelMapClassification(force);
  // ao.ProduceDeadPixelMapBeam(force);
  // ao.ProduceManualPixelMap(force);
  ao.ProduceCombinedPixelMap(force);
  ao.LoadPixelMasks(kAll);
  mTowerGeometry geo = ao.GetGeometry();

  int status = 0, iBinCol, iBinRow, cont = 0; // 6 digits: noisyclass noisyped noisybeam deadclass deadbeam manual
  const int nMethods = 6;
  std::bitset<nMethods> bs_stat;

  myStyle style;
  style.ApplyStyle(gStyle);
  TH1D* h1_total = new TH1D("h1_total", "", geo.GetNchips(), geo.GetChipMin()-0.5, geo.GetChipMax()+0.5);
  style.makenicehist((TH1F*) h1_total, "chipID", "number of pixels", kBlack);
  TH1D* h1_noisy = (TH1D*) h1_total->Clone("h1_noisy");
  TH1D* h1_dead  = (TH1D*) h1_total->Clone("h1_dead");
  TH1D* h1_man   = (TH1D*) h1_total->Clone("h1_man");
  TH1D* h1_noisy_total = (TH1D*) h1_total->Clone("h1_noisy_total");
  TH1D* h1_dead_total  = (TH1D*) h1_total->Clone("h1_dead_total");
  TH1D* h1_noisy_AND = (TH1D*) h1_total->Clone("h1_noisy_AND");
  TH1D* h1_dead_AND  = (TH1D*) h1_total->Clone("h1_dead_AND");
  // TH1D* h1_noisy = new TH1D("h1_noisy", "", geo.GetNchips(), geo.GetChipMin()-0.5, geo.GetChipMax()+0.5);
  // TH1D* h1_dead  = new TH1D("h1_dead",  "",  geo.GetNchips(), geo.GetChipMin()-0.5, geo.GetChipMax()+0.5);
  // TH1D* h1_man   = new TH1D("h1_man",   "",   geo.GetNchips(), geo.GetChipMin()-0.5, geo.GetChipMax()+0.5);
  TH1D* h1_method[nMethods];
  for (int it = 0; it < nMethods; ++it) h1_method[it] = (TH1D*) h1_total->Clone(Form("h1_method%i", it));

  vector<TH2C*> vh2_pixelmasks = ao.GetPixelMasks();
  int chipcounter = 0;
  for (auto& mask : vh2_pixelmasks)
  {
    for (int iCol = geo.GetColMin(); iCol <= geo.GetColMax(); ++iCol)
    {
      iBinCol = mask->GetXaxis()->FindBin(iCol);
      for (int iRow = geo.GetRowMin(); iRow <= geo.GetRowMax(); ++iRow)
      {
        iBinRow = mask->GetYaxis()->FindBin(iRow);
        cont = mask->GetBinContent(iBinCol, iBinRow);
        bs_stat = cont;
        if (bs_stat.any()) h1_total->Fill(chipcounter);
        else continue;

        for (int it = 0; it < nMethods; ++it) if (bs_stat.test(it)) h1_method[it]->Fill(chipcounter);

        bool pixeldone = false, noisydone = false, deaddone = false;
        if(bs_stat.test(5)) { // if manual
          if (!pixeldone) {h1_man->Fill(chipcounter); pixeldone = true;}
        }
        if(bs_stat.test(0) || bs_stat.test(1) || bs_stat.test(2)) { // if noisy
          if (!pixeldone) {h1_noisy->Fill(chipcounter); pixeldone = true;}
          if (!noisydone) {h1_noisy_total->Fill(chipcounter); noisydone = true;}
        }
        if(bs_stat.test(3) || bs_stat.test(4)) { // if dead
          if (!pixeldone) {h1_dead->Fill(chipcounter); pixeldone = true;}
          if (!deaddone) {h1_dead_total->Fill(chipcounter); deaddone = true;}
        }

        if(bs_stat.test(0) && bs_stat.test(1) && bs_stat.test(2)) {h1_noisy_AND->Fill(chipcounter);}
        if(bs_stat.test(3) && bs_stat.test(4)) {h1_dead_AND->Fill(chipcounter);}
      }
    }
    ++chipcounter;
  }


  TCanvas* c = new TCanvas("c", "c");
  THStack* hst_all = new THStack("hst_all", "");
  THStack* hst_noisy = new THStack("hst_noisy", "");
  THStack* hst_dead = new THStack("hst_dead", "");
  // makenicestack(hst_all, "chipID", "number of pixels");
  // makenicestack(hst_noisy, "chipID", "number of pixels");
  // makenicestack(hst_dead, "chipID", "number of pixels");
  // h1_total->SetLineColor(kBlack);
  h1_total->SetLineWidth(2.);
  // h1_total->SetStats(0);
  h1_total->GetYaxis()->SetRangeUser(0., 1.1*h1_total->GetMaximum());
  h1_noisy->SetFillColor(kOrange+2);
  // h1_noisy->SetLineColor(kOrange+2);
  h1_noisy->SetLineWidth(0.);
  h1_dead->SetFillColor(kGray+1);
  // h1_dead->SetLineColor(kGray+1);
  h1_dead->SetLineWidth(0.);
  h1_man->SetFillColor(kBlue-2);
  // h1_man->SetLineColor(kBlue+2);
  h1_man->SetLineWidth(0.);
  h1_noisy_total->SetLineWidth(2.);
  h1_noisy_total->SetLineColor(kRed);
  h1_dead_total->SetLineWidth(2.);
  h1_dead_total->SetLineColor(kBlack);
  h1_noisy_AND->SetLineWidth(2.);
  h1_noisy_AND->SetLineColor(kOrange+2);
  h1_dead_AND->SetLineWidth(2.);
  h1_dead_AND->SetLineColor(kGray+2);

  int col[nMethods] = {kYellow+2, kOrange+2, kRed+2, kGray+2, kGray, kBlue+2};
  hst_noisy->Add(h1_noisy_total);
  hst_dead->Add(h1_dead_total);
  for (int it = 0; it < nMethods; ++it) {
    // h1_method[it]->SetFillColor(col[it]);
    h1_method[it]->SetLineColor(col[it]);
    h1_method[it]->SetLineWidth(2.);
    if (it == 0 || it == 1 || it == 2) hst_noisy->Add(h1_method[it]);
    if (it == 3 || it == 4) hst_dead->Add(h1_method[it]);
    // hst_all->Add(h1_method[it]);
  }
  hst_all->Add(h1_man);
  hst_all->Add(h1_dead);
  hst_all->Add(h1_noisy);

  int nTotal = h1_total->GetEntries();
  int nTotal_noisy = h1_noisy_total->GetEntries();
  int nTotal_dead = h1_dead_total->GetEntries();


  float xpos, ypos, yspace;
  int iLine;

  xpos = 0.15, ypos = 0.90, yspace = 0.045;


  h1_total->DrawCopy();
  for (int it = nMethods-1; it >= 0; --it) h1_method[it]->DrawCopy("same");

  iLine = 0;
  style.drawtext("EPICAL-2 test beam data", xpos, ypos - iLine++*yspace);
  style.drawtext("Feb. '20 at DESY", xpos, ypos - iLine++*yspace);
  iLine++;
  style.drawtext(Form("Run %i", run), xpos, ypos - iLine++*yspace);
  iLine++;
  style.drawtext(Form("Total number of masked pixels:"), xpos, ypos - iLine++*yspace);
  style.drawtext(Form("%i", nTotal), xpos, ypos - iLine++*yspace);

  float drawlegx = 0.73, drawlegy = 0.93;
  int legNcolumns = 1;
  int nhists = nMethods + 1;
  float legysize = nhists / legNcolumns + 1;
  TLegend* leg = new TLegend(drawlegx,drawlegy,drawlegx+legNcolumns*0.15,drawlegy - legysize * yspace);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->SetTextFont(43);
  leg->SetTextSize(30);
  leg->SetNColumns(legNcolumns);
  leg->SetHeader("Pixel masking method:");
  leg->AddEntry(h1_total, "all", "l");
  leg->AddEntry(h1_method[0], "noisy (class.)", "l");
  leg->AddEntry(h1_method[1], "noisy (pedestal)", "l");
  leg->AddEntry(h1_method[2], "noisy (beam)", "l");
  leg->AddEntry(h1_method[3], "dead (class.)", "l");
  leg->AddEntry(h1_method[4], "dead (beam)", "l");
  leg->AddEntry(h1_method[5], "manual", "l");
  leg->Draw();

  c->SaveAs("all.pdf");


  h1_total->DrawCopy();
  hst_all->Draw("same");
  style.makenicehist((TH1F*) hst_all->GetHistogram(), "chipID", "number of pixels");

  iLine = 0;
  style.drawtext("EPICAL-2 test beam data", xpos, ypos - iLine++*yspace);
  style.drawtext("Feb. '20 at DESY", xpos, ypos - iLine++*yspace);
  iLine++;
  style.drawtext(Form("Run %i", run), xpos, ypos - iLine++*yspace);
  iLine++;
  style.drawtext(Form("Total number of masked pixels:"), xpos, ypos - iLine++*yspace);
  style.drawtext(Form("%i", nTotal), xpos, ypos - iLine++*yspace);

  delete leg;
  nhists = hst_all->GetNhists() + 1;
  legysize = nhists / legNcolumns + 1;
  leg = new TLegend(drawlegx,drawlegy,drawlegx+legNcolumns*0.15,drawlegy - legysize * yspace);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->SetTextFont(43);
  leg->SetTextSize(30);
  leg->SetNColumns(legNcolumns);
  leg->SetHeader("Pixel masking method:");
  leg->AddEntry(h1_total, "all", "l");
  leg->AddEntry( (TH1D*) hst_all->GetHists()->FindObject("h1_noisy"), "noisy",  "f");
  leg->AddEntry( (TH1D*) hst_all->GetHists()->FindObject("h1_dead"),  "dead",   "f");
  leg->AddEntry( (TH1D*) hst_all->GetHists()->FindObject("h1_man"),   "manual", "f");
  leg->Draw();

  c->SaveAs("all_stacked.pdf");


  hst_noisy->Draw("nostack");
  style.makenicehist((TH1F*) hst_noisy->GetHistogram(), "chipID", "number of pixels");

  iLine = 0;
  style.drawtext("EPICAL-2 test beam data", xpos, ypos - iLine++*yspace);
  style.drawtext("Feb. '20 at DESY", xpos, ypos - iLine++*yspace);
  iLine++;
  style.drawtext(Form("Run %i", run), xpos, ypos - iLine++*yspace);
  iLine++;
  style.drawtext(Form("Total number of noisy pixels:"), xpos, ypos - iLine++*yspace);
  style.drawtext(Form("%i", nTotal_noisy), xpos, ypos - iLine++*yspace);

  delete leg;
  drawlegx = 0.53, drawlegy = 0.93;
  nhists = hst_noisy->GetNhists();
  legysize = nhists / legNcolumns + 1;
  leg = new TLegend(drawlegx,drawlegy,drawlegx+legNcolumns*0.15,drawlegy - legysize * yspace);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->SetTextFont(43);
  leg->SetTextSize(30);
  leg->SetNColumns(legNcolumns);
  leg->SetHeader("Pixel masking method:");
  leg->AddEntry( (TH1D*) hst_noisy->GetHists()->FindObject("h1_noisy_total"), "noisy (all)",  "l");
  leg->AddEntry( (TH1D*) hst_noisy->GetHists()->FindObject("h1_method0"), "noisy (class.)",  "l");
  leg->AddEntry( (TH1D*) hst_noisy->GetHists()->FindObject("h1_method1"), "noisy (pedestal)",  "l");
  leg->AddEntry( (TH1D*) hst_noisy->GetHists()->FindObject("h1_method2"), "noisy (beam)",  "l");
  leg->Draw();

  c->SaveAs("noisy.pdf");


  h1_noisy_total->Draw("");
  h1_noisy_AND->Draw("same");
  int nTotal_noisy_AND = h1_noisy_AND->GetEntries();

  iLine = 0;
  style.drawtext("EPICAL-2 test beam data", xpos, ypos - iLine++*yspace);
  style.drawtext("Feb. '20 at DESY", xpos, ypos - iLine++*yspace);
  iLine++;
  style.drawtext(Form("Run %i", run), xpos, ypos - iLine++*yspace);
  iLine++;
  style.drawtext(Form("Total (AND) number"), xpos, ypos - iLine++*yspace);
  style.drawtext(Form("of noisy pixels:"), xpos, ypos - iLine++*yspace);
  style.drawtext(Form("%i (%i)", nTotal_noisy, nTotal_noisy_AND), xpos, ypos - iLine++*yspace);

  delete leg;
  drawlegx = 0.53, drawlegy = 0.93;
  nhists = 2;
  legysize = nhists / legNcolumns + 1;
  leg = new TLegend(drawlegx,drawlegy,drawlegx+legNcolumns*0.15,drawlegy - legysize * yspace);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->SetTextFont(43);
  leg->SetTextSize(30);
  leg->SetNColumns(legNcolumns);
  leg->SetHeader("Pixel masking method:");
  leg->AddEntry( h1_noisy_total, "noisy (all)",  "l");
  leg->AddEntry( h1_noisy_AND, "noisy (AND)",  "l");
  leg->Draw();

  c->SaveAs("noisy_AND.pdf");


  hst_dead->Draw("nostack");
  style.makenicehist((TH1F*) hst_dead->GetHistogram(), "chipID", "number of pixels");

  iLine = 0;
  style.drawtext("EPICAL-2 test beam data", xpos, ypos - iLine++*yspace);
  style.drawtext("Feb. '20 at DESY", xpos, ypos - iLine++*yspace);
  iLine++;
  style.drawtext(Form("Run %i", run), xpos, ypos - iLine++*yspace);
  iLine++;
  style.drawtext(Form("Total number of dead pixels:"), xpos, ypos - iLine++*yspace);
  style.drawtext(Form("%i", nTotal_dead), xpos, ypos - iLine++*yspace);

  drawlegx = 0.73, drawlegy = 0.93;
  nhists = hst_dead->GetNhists();
  legysize = nhists / legNcolumns + 1;
  leg = new TLegend(drawlegx,drawlegy,drawlegx+legNcolumns*0.15,drawlegy - legysize * yspace);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->SetTextFont(43);
  leg->SetTextSize(30);
  leg->SetNColumns(legNcolumns);
  leg->SetHeader("Pixel masking method:");
  leg->AddEntry( (TH1D*) hst_dead->GetHists()->FindObject("h1_dead_total"), "dead (all)",  "l");
  leg->AddEntry( (TH1D*) hst_dead->GetHists()->FindObject("h1_method3"), "dead (class.)",  "l");
  leg->AddEntry( (TH1D*) hst_dead->GetHists()->FindObject("h1_method4"), "dead (pedestal)",  "l");
  leg->Draw();

  c->SaveAs("dead.pdf");


  h1_dead_total->Draw("");
  h1_dead_AND->Draw("same");
  int nTotal_dead_AND = h1_dead_AND->GetEntries();

  iLine = 0;
  style.drawtext("EPICAL-2 test beam data", xpos, ypos - iLine++*yspace);
  style.drawtext("Feb. '20 at DESY", xpos, ypos - iLine++*yspace);
  iLine++;
  style.drawtext(Form("Run %i", run), xpos, ypos - iLine++*yspace);
  iLine++;
  style.drawtext(Form("Total (AND) number"), xpos, ypos - iLine++*yspace);
  style.drawtext(Form("of dead pixels:"), xpos, ypos - iLine++*yspace);
  style.drawtext(Form("%i (%i)", nTotal_dead, nTotal_dead_AND), xpos, ypos - iLine++*yspace);

  delete leg;
  drawlegx = 0.73, drawlegy = 0.93;
  nhists = 2;
  legysize = nhists / legNcolumns + 1;
  leg = new TLegend(drawlegx,drawlegy,drawlegx+legNcolumns*0.15,drawlegy - legysize * yspace);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->SetTextFont(43);
  leg->SetTextSize(30);
  leg->SetNColumns(legNcolumns);
  leg->SetHeader("Pixel masking method:");
  leg->AddEntry( h1_dead_total, "dead (all)",  "l");
  leg->AddEntry( h1_dead_AND, "dead (AND)",  "l");
  leg->Draw();

  c->SaveAs("dead_AND.pdf");


// printf("\n\n hitmap status: %i\n pixel mask status: %i\n\n", ao.GetHitmapStatus(), ao.GetPixelMaskStatus());
  // vector<TH2D*> vh2_hotpixelmaps = ao.GetHitmaps();
  //
  // TCanvas* c = new TCanvas("c","c");
  // c->Divide(6,8);
  //
  // TFile* fout = new TFile("test.root", "RECREATE");
  //
  //
  // int it=1;
  // for (auto& map : vh2_hotpixelmaps)
  // {
  //   c->cd(it);
  //   map->DrawCopy("COLZ");
  //   map->Write();
  //   ++it;
  // }
  // c->SaveAs("test.png");
  // delete c;
  // delete fout;

  return 0;
}
