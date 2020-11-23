//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~~~ Project:       EPICAL                            ~~~~~//
//~~~~~ File:          EPICALAnalysisObject.cxx          ~~~~~//
//~~~~~ Author:        F. Pliquett                       ~~~~~//
//~~~~~ Created:       05.08.2020                        ~~~~~//
//~~~~~ Description:   "Implementation of                ~~~~~//
//~~~~~                 EPICALAnalysisObject class.      ~~~~~//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//


#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <filesystem>

#include "TFile.h"
#include "TString.h"
#include "TUnixSystem.h"
#include "TGraph2D.h"
#include "TF1.h"

#include "ROOT/RDataFrame.hxx"

#include "../../include/EPICALAnalysisObject.h"
#include "../../include/EPICALGeometry.h"
#include "../../include/EPICALUtility.h"
#include "../../include/EPICALConversions.h"


// public functions

// special functions

EPICALAnalysisObject::EPICALAnalysisObject (const int &run) :
fRunNr(run),
fNevents(getnevents(run)), // number of events from run condition table
fDataTakingPeriod(getdataperiod(run)),

fRawDataFilePath(rawdatafilepath()),
fTreeName("Frames"),

fOutputDirPath("../output/rootfiles/"),
fHitmapDirPath(Form("%shitmaps/Run_%.4i/", fOutputDirPath.data(), fRunNr)),
fPixelMaskDirPath(Form("%spixelmasks/total/Run_%.4i/", fOutputDirPath.data(), fRunNr)),
fNoisyPixelMaskClassificationDirPath(Form("%spixelmasks/noisypixels/classification/", fOutputDirPath.data())),
fNoisyPixelMaskPedestalDirPath(Form("%spixelmasks/noisypixels/pedestal/Run_%.4i/", fOutputDirPath.data(), fRunNr)),
fNoisyPixelMaskBeamDirPath(Form("%spixelmasks/noisypixels/beam/", fOutputDirPath.data())), // pixelmaskdirpath("noisypixels/beam")
fDeadPixelMaskClassificationDirPath(Form("%spixelmasks/deadpixels/classification/", fOutputDirPath.data())),
fDeadPixelMaskBeamDirPath(Form("%spixelmasks/deadpixels/beam/Run_%.4i/", fOutputDirPath.data(), fRunNr)),
fManualPixelMaskDirPath(Form("%spixelmasks/manualmask/", fOutputDirPath.data())),
fCombinedPixelMaskDirPath(Form("%spixelmasks/combined/Run_%.4i/", fOutputDirPath.data(), fRunNr)),

fHotPixelCriterion(0.001),
fHitmaps(),
fPixelMasks(),
fHitmapStatus(kNotLoaded),
fPixelMaskStatus(kNotLoaded),

fGeometry(fDataTakingPeriod),
fColumnMin(fGeometry.GetColMin()),
fColumnMax(fGeometry.GetColMax()),
fNcolumns (fGeometry.GetNcols()),
fRowMin   (fGeometry.GetRowMin()),
fRowMax   (fGeometry.GetRowMax()),
fNrows    (fGeometry.GetNrows()),
fLaneMin  (fGeometry.GetLaneMin()),
fLaneMax  (fGeometry.GetLaneMax()),
fNlanes   (fGeometry.GetNlanes()),
fChipMin  (fGeometry.GetChipMin()),
fChipMax  (fGeometry.GetChipMax()),
fNchips   (fGeometry.GetNchips()),
fLayerMin (fGeometry.GetLayerMin()),
fLayerMax (fGeometry.GetLayerMax()),
fNlayers  (fGeometry.GetNlayers())
{
  if ( !check_fileexists(fHitmapDirPath) )
  {
    gSystem->Exec(Form("mkdir -p %s", fHitmapDirPath.data()));
  }
};


EPICALAnalysisObject::~EPICALAnalysisObject ()
{
  ResetHitmaps();
  ResetPixelMasks();
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~ end special functions ~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// analysis functions

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// EPICALAnalysisObject::ProduceHitmaps
void EPICALAnalysisObject::ProduceHitmaps (bool force)
{
  printf("\n >>> Producing hitmaps... \n");

  if (!force)
  {
    if( check_fileexists( hitmapfilepath() ) )
    {
      std::cout << " >>> Hitmaps do already exist and can be loaded. " << std::endl;
      std::cout << " >>> If hitmaps should be produced anyways, use 'force'. " << std::endl;
      return;
    }
  }

  if ( !check_fileexists(fRawDataFilePath) )
  {
    std::cout << " ### Raw root data input file \'" << fRawDataFilePath << "\' does not exist. " << std::endl;
    std::cout << " ### Can not produce hitmaps for run " << fRunNr << ". " << std::endl;
    return;
  }

  if ( !check_fileexists(fHitmapDirPath) )
  {
    gSystem->Exec(Form("mkdir -p %s", fHitmapDirPath.data()));
  }
  TFile* f_out = new TFile(hitmapfilepath().data(), "RECREATE");

  ROOT::RDataFrame df(fTreeName.data(), fRawDataFilePath.data());

  auto h3_colrowlane = df.Histo3D(
    {Form("h3_colrowlane_%.4i", fRunNr), Form("h3_colrowlane_%.4i", fRunNr),
    fNcolumns, fColumnMin-0.5, fColumnMax+0.5,
    fNrows, fRowMin-0.5, fRowMax+0.5,
    fNlanes, fLaneMin-0.5, fLaneMax+0.5},
    "column",
    "row",
    "lane");

  TH2D* h2_colrow;
  int iChipID, iLane, iBinLane;

  for (auto iLayer = fLayerMin; iLayer <= fLayerMax; ++iLayer)
  {
    for (auto iChip = 0; iChip <= 1; ++iChip)
    {
      if      (iChip == 0) iChipID = fGeometry.GetChipIDFromLayer(iLayer).first;
      else if (iChip == 1) iChipID = fGeometry.GetChipIDFromLayer(iLayer).second;
      iLane   = fGeometry.GetLaneFromChipID(iChipID);
      iBinLane = h3_colrowlane->GetZaxis()->FindBin(iLane);
      h3_colrowlane->GetZaxis()->SetRange(iBinLane, iBinLane);
      h2_colrow = (TH2D*) h3_colrowlane->Project3D("yx");
      h2_colrow->SetName(Form("h2_colrow_chip%i", iChipID));
      h2_colrow->GetXaxis()->SetTitle("column");
      h2_colrow->GetYaxis()->SetTitle("row");
      h2_colrow->Write();
    }
  }

  delete f_out;
};
// EPICALAnalysisObject::ProduceHitmaps
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// EPICALAnalysisObject::LoadHitmaps
void EPICALAnalysisObject::LoadHitmaps ()
{
  if (fHitmapStatus == kNotApplied) // hitmaps have been loaded and not modified
  {
    std::cout << " >>> Hitmaps already loaded. Skipping 'LoadHitmaps'. " << std::endl;
    return;
  }
  else
  {
    ResetHitmaps();
    std::cout << "\n >>> Loading unmodified hitmaps... " << std::endl;
  }

  if( !check_fileexists( hitmapfilepath() ) )
  {
    std::cout << " >>> Hitmaps do not exist yet. " << std::endl;
    ProduceHitmaps();
  }

  TFile* f_in = new TFile(hitmapfilepath().data(), "READ");

  for (auto iChipID = fChipMin; iChipID <= fChipMax; ++iChipID)
  {
    fHitmaps.push_back((TH2D*)f_in->Get(Form("h2_colrow_chip%i", iChipID)));
    fHitmaps.at(iChipID)->SetDirectory(0);
  }
  delete f_in;

  fHitmapStatus = kNotApplied; // set hitmap status to "unmodified hitmap"
};
// EPICALAnalysisObject::LoadHitmaps
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// EPICALAnalysisObject::ProduceNoisyPixelMapClassification
void EPICALAnalysisObject::ProduceNoisyPixelMapClassification (bool force)
{
  ProduceBadPixelMapClassification("noisy", force);
};
// EPICALAnalysisObject::ProduceNoisyPixelMapClassification
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// EPICALAnalysisObject::ProduceNoisyPixelMapPedestal
void EPICALAnalysisObject::ProduceNoisyPixelMapPedestal (bool force)
{

  printf("\n >>> Producing noisy pixel mask from pedestal... \n");

  // skip if pixel mask already exists
  if (!force)
  {
    if( check_fileexists( noisypixelmaskpedestalfilepath() ) )
    {
      std::cout << " >>> Noisy pixel masks from pedestal do already exist. " << std::endl;
      std::cout << " >>> If they should be produced anyways, use 'force'. " << std::endl;
      return;
    }
  }
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


  // check if run is pedestal run
  if (!IsPedestal())
  {
    std::cout << " ### Run is not a pedestal run. " << std::endl;
    std::cout << " ### Cannot produce noisy pixel mask. " << std::endl;
    return;
  }
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


  // check if criterion for noisy pixels is set
  if (fHotPixelCriterion < 0.)
  {
    std::cout << " ### Noisy pixel criterion not set. " << std::endl;
    std::cout << " ### Cannot produce noisy pixel mask. " << std::endl;
    return;
  }
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


  // create directory if it doesn't exist
  if ( !check_fileexists(fNoisyPixelMaskPedestalDirPath) )
  {
    gSystem->Exec(Form("mkdir -p %s", fNoisyPixelMaskPedestalDirPath.data()));
  }
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


  // load raw (unmodified) hitmaps
  ePixelMask SaveStatus = GetHitmapStatus(); // save status to restore hitmaps in the end
  LoadHitmaps(); // loading unmodified hitmaps
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  TFile* f_out = new TFile(noisypixelmaskpedestalfilepath().data(), "RECREATE");


  // define hot pixel: absolute number of hits
  double iNhitsHot = static_cast<double>(fNevents) * fHotPixelCriterion; // if pixel fired more often (absolute hit count) it's flagged hot
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


  // define output histograms
  TH2C* h2_hotpixelmap = InitHist2DChip<TH2C>("h2_pixelmap"); // 2D hot pixel map per chip to be reused chip-by-chip
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


  // main loop over all pixels of the whole detector (chips->columns->rows)
  for (int iChip = fChipMin; iChip <= fChipMax; ++iChip) // loop over chips
  {
    h2_hotpixelmap->Reset();
    TH2D* h2_colrow_chip = fHitmaps.at(iChip); // get 2D hitmap from input file
    for (int iCol = fColumnMin; iCol <= fColumnMax; ++iCol) // loop over columns
    {
      int iBinColumn = h2_colrow_chip->GetXaxis()->FindBin(iCol); // get bin number of corresponding column
      for (int iRow = fRowMin; iRow <= fRowMax; ++iRow) // loop over rows
      {
        int iBinRow = h2_colrow_chip->GetYaxis()->FindBin(iRow); // get bin number of corresponding row

        // start analyzing on pixel level
        int iNhitsPixel = h2_colrow_chip->GetBinContent(iBinColumn, iBinRow); // get number of hits
        if (iNhitsPixel > iNhitsHot) // check if criterion is met for hot pixel
        {
          h2_hotpixelmap->SetBinContent(iBinColumn, iBinRow, 1); // set hot pixel map to one
        }
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
      } // rows
    } // columns

    string s_histname = Form("h2_pixelmap_chip%i", iChip);
    h2_hotpixelmap->SetName(s_histname.data());
    h2_hotpixelmap->SetTitle(s_histname.data());
    h2_hotpixelmap->Write();

  } // chips
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


  delete h2_hotpixelmap;
  delete f_out;

  if (SaveStatus != kNotApplied) ApplyPixelMask(SaveStatus); // restore hitmap from before function
};
// EPICALAnalysisObject::ProduceNoisyPixelMapPedestal
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// EPICALAnalysisObject::ProduceNoisyPixelMapBeam
void EPICALAnalysisObject::ProduceNoisyPixelMapBeam (bool force)
{

  printf("\n >>> Producing noisy pixel mask from beam... \n");

  if ( !check_fileexists( fNoisyPixelMaskBeamDirPath ) )
  {
    gSystem->Exec(Form("mkdir -p %s", fNoisyPixelMaskBeamDirPath.data()));
  }

  const std::vector<std::pair<float, string>> e2filename =
    {
      {1.0, "../input/noisypixels_beam/outMaskPtn_TB_1R0_GeV.txt"},
      {2.0, "../input/noisypixels_beam/outMaskPtn_TB_2R0_GeV.txt"},
      {3.0, "../input/noisypixels_beam/outMaskPtn_TB_3R0_GeV.txt"},
      {4.0, "../input/noisypixels_beam/outMaskPtn_TB_4R0_GeV.txt"},
      {5.0, "../input/noisypixels_beam/outMaskPtn_TB_5R0_GeV.txt"},
      {5.8, "../input/noisypixels_beam/outMaskPtn_TB_5R8_GeV.txt"}
    };

  for (auto& pairs : e2filename)
  {

    float energy = pairs.first;
    string s_in = pairs.second;

    // noisypixelmaskbeamfilepath() cannot be used here because it loops over all energies
    string s_out = Form("%snoisypixelmask_beam_%.1fGeV.root", fNoisyPixelMaskBeamDirPath.data(), energy);

    if (!force)
    {
      if( check_fileexists( s_out ) )
      {
        printf( " >>> Noisy pixel map for %.1f GeV already exists.\n", energy );
        printf( " >>> If noisy pixel map should be produced anyways, use 'force'. \n");
        continue;
      }
    }

    vector<TH2C*> vh2_hotpixelmaps = this->GetBadPixelMapFromTextFile(s_in.data());

    TFile* f_out = new TFile(s_out.data(),"RECREATE");
    for (auto &map : vh2_hotpixelmaps)
    {
        map->Write();
        delete map;
    }

    delete f_out;
  }

  return;
};
// EPICALAnalysisObject::ProduceNoisyPixelMapBeam
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// EPICALAnalysisObject::ProduceNhitsPerPixel
void EPICALAnalysisObject::ProduceNhitsPerPixel (bool force)
{

  printf("\n >>> Producing number of hits per pixel histograms... \n");

  if (!force)
  {
    if( check_fileexists( nhitsperpixelfilepath() ) )
    {
      std::cout << " >>> Number of hits per pixel plots do already exist. " << std::endl;
      std::cout << " >>> If they should be produced anyways, use 'force'. " << std::endl;
      return;
    }
  }

  if (fHitmapStatus == kNotLoaded) LoadHitmaps(); // load unmodified hitmaps if not loaded before, otherwise use previously loaded (un)modified hitmap

  TFile* f_out = new TFile(nhitsperpixelfilepath().data(), "RECREATE");


  // define output histograms
  TH1D* h1_nHitsperPixel = new TH1D("h1_nHitsperPixel", "h1_nHitsperPixel", fNevents+1, -0.5, static_cast<float>(fNevents)+0.5); // number of hits per pixel for the complete stack (control histogram for hot pixel criterion)
  TH1D* h1_nHitsperPixel_Chip[static_cast<const int>(fNchips)]; // number of hits per pixel for each chip individually to compare noise level between chips
  for (int iChip = fChipMin; iChip <= fChipMax; ++iChip)
  {
    h1_nHitsperPixel_Chip[iChip] = new TH1D(Form("h1_nHitsperPixel_Chip%i", iChip), Form("h1_nHitsperPixel_Chip%i", iChip), fNevents+1, -0.5, static_cast<float>(fNevents+0.5));
  }
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


  // main loop over all pixels of the whole detector (chips->columns->rows)
  for (int iChip = fChipMin; iChip <= fChipMax; ++iChip) // loop over chips
  {
    for (int iCol = fColumnMin; iCol <= fColumnMax; ++iCol) // loop over columns
    {
      int iBinColumn = fHitmaps[iChip]->GetXaxis()->FindBin(iCol); // get bin number of corresponding column
      for (int iRow = fRowMin; iRow <= fRowMax; iRow++) // loop over rows
      {
        int iBinRow = fHitmaps[iChip]->GetYaxis()->FindBin(iRow); // get bin number of corresponding row

        // start analyzing on pixel level
        int iNhitsPixel = fHitmaps[iChip]->GetBinContent(iBinColumn, iBinRow); // get number of hits
        h1_nHitsperPixel->Fill(iNhitsPixel); // fill the number of hits for this pixel in histogram
        h1_nHitsperPixel_Chip[iChip]->Fill(iNhitsPixel); // fill the number of hits for this pixel in histogram chip-by-chip
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
      }
    }
  }
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


  // define further output histograms
  TH1D* h1_nHitsperPixel_relative = (TH1D*) h1_nHitsperPixel->Clone("h1_nHitsperPixel_relative"); // create histogram for number of hits per pixel relative to number of events (max possible number of hits)
  h1_nHitsperPixel_relative->SetTitle("h1_nHitsperPixel_relative");
  h1_nHitsperPixel_relative->GetXaxis()->Set(h1_nHitsperPixel_relative->GetXaxis()->GetNbins(), h1_nHitsperPixel_relative->GetXaxis()->GetXmin() / fNevents, h1_nHitsperPixel_relative->GetXaxis()->GetXmax() / fNevents); // scale x-axis to get relative number of hits

  TH1D* h1_nHitsperPixel_Chip_relative[static_cast<const int>(fNchips)];
  for (int iChip = fChipMin; iChip <= fChipMax; ++iChip)
  {
    h1_nHitsperPixel_Chip_relative[iChip] = (TH1D*) h1_nHitsperPixel_Chip[iChip]->Clone(Form("h1_nHitsperPixel_Chip%i_relative", iChip)); // create histogram for number of hits per pixel relative to number of events (max possible number of hits)
    h1_nHitsperPixel_Chip_relative[iChip]->SetTitle(Form("h1_nHitsperPixel_Chip%i_relative", iChip));
    h1_nHitsperPixel_Chip_relative[iChip]->GetXaxis()->Set(h1_nHitsperPixel_Chip_relative[iChip]->GetXaxis()->GetNbins(), h1_nHitsperPixel_Chip_relative[iChip]->GetXaxis()->GetXmin() / fNevents, h1_nHitsperPixel_Chip_relative[iChip]->GetXaxis()->GetXmax() / fNevents); // scale x-axis to get relative number of hits
  }
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


  // save all output histograms to file
  f_out->cd();
  h1_nHitsperPixel->Write();
  h1_nHitsperPixel_relative->Write();
  int iChipID;
  for (auto iLayer = fLayerMin; iLayer <= fLayerMax; ++iLayer)
  {
    for (auto iChip = 0; iChip <= 1; ++iChip)
    {
      if      (iChip == 0) iChipID = fGeometry.GetChipIDFromLayer(iLayer).first;
      else if (iChip == 1) iChipID = fGeometry.GetChipIDFromLayer(iLayer).second;
      h1_nHitsperPixel_Chip[iChipID]->Write();
      h1_nHitsperPixel_Chip_relative[iChipID]->Write();
    }
  }
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


  // cleaning up
  for (int iChip = fChipMin; iChip < fChipMax; ++iChip)
  {
    delete h1_nHitsperPixel_Chip[iChip];
    delete h1_nHitsperPixel_Chip_relative[iChip];
  }
  delete h1_nHitsperPixel_relative;
  delete h1_nHitsperPixel;
  delete f_out;
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
};
// EPICALAnalysisObject::ProduceNhitsPerPixel
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// EPICALAnalysisObject::ProduceDeadPixelMapClassification
void EPICALAnalysisObject::ProduceDeadPixelMapClassification (bool force)
{
  ProduceBadPixelMapClassification("dead", force);
};
// EPICALAnalysisObject::ProduceDeadPixelMapClassification
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// EPICALAnalysisObject::ProduceDeadPixelMapBeam
void EPICALAnalysisObject::ProduceDeadPixelMapBeam (bool force)
{

  printf("\n >>> Producing dead pixel mask from beam... \n");

  if (IsPedestal())
  {
    printf(" ### Current run (%i) is pedestal run. \n", fRunNr);
    printf(" ### Cannot produce dead pixel mask. \n");
    return;
  }

  string s_out = deadpixelmaskbeamfilepath();

  if (!force)
  {
    if( check_fileexists( s_out ) )
    {
      printf( " >>> Dead pixel map for run %.4i already exists.\n", fRunNr);
      printf( " >>> If dead pixel map should be produced anyways, use 'force'. \n");
      return;
    }
  }

  if ( !check_fileexists( fDeadPixelMaskBeamDirPath ) )
  {
    gSystem->Exec(Form("mkdir -p %s", fDeadPixelMaskBeamDirPath.data()));
  }

  TFile* f_out = new TFile(s_out.data(),"RECREATE"); // output file for pixel mask
  TFile* f_out_QA = new TFile(Form("%sdeadpixelmaskQA_beam_Run%.4i.root", fDeadPixelMaskBeamDirPath.data(), fRunNr), "RECREATE");


  // define objects to be used in the loop over chips
  ePixelMask SaveStatus = GetHitmapStatus(); // save status of hitmaps to restore later
  ePixelMask Applied = kNoisy; // set which mask should be applied
  // LoadHitmaps(); // load unmodified hitmaps for every chip
  ApplyPixelMask(Applied); // remove noisy pixels to get better results
  ResetPixelMasks();
  TH2D* h2_colrow_chip;  // 2D hitmap for every chip
  TH1D* h1_projection_col; // projection of hitmap on columns
  // TH1D* h1_projection_col_cumulative; // projection of hitmap on columns, cumulative
  TH2C* h2_deadpixelmap; // 2D histogram to store dead pixel map
  TH1D* h1_dev_chip = new TH1D("h1_dev_chip", "h1_dev_chip", 201, -20.05, 20.05);
  vector<TH1D*> h1_dev;
  int iNdiv = 10;
  for (int i = 0; i < iNdiv+1; ++i)
  {
    h1_dev.push_back(new TH1D(Form("h1_dev%i", i), Form("h1_dev%i", i), 401, -20.05, 20.05));
  }
  TGraph* g_Mean  = new TGraph(fNchips);
  TGraph* g_Sigma = new TGraph(fNchips);

  double maxhits = GetMaxHitsCol();
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


  // loop over all chips
  for (int iChipID = fChipMin; iChipID <= fChipMax; ++iChipID)
  {

    // create objects for dead pixel map for each chip
    h2_colrow_chip    = fHitmaps.at(iChipID);
    h2_deadpixelmap   = InitHist2DChip<TH2C>(Form("h2_pixelmap_chip%i", iChipID));
    h1_projection_col = (TH1D*) h2_colrow_chip->ProjectionX(Form("h1_projection_col_chip%i", iChipID));
    h1_dev_chip->Reset();
    h1_dev_chip->SetName(Form("h1_dev_chip%i", iChipID));
    h1_dev_chip->SetTitle(Form("h1_dev_chip%i", iChipID));
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    if (h2_colrow_chip->GetEntries() == 0)
    {
      f_out_QA->cd();
      h1_projection_col->Write();
      h2_deadpixelmap->Write();
      h1_dev_chip->Write();
      f_out->cd();
      h2_deadpixelmap->Write();
      continue; // skip broken chips
    }


    // calculate deviation from expected value (defined in function) and mean/sigma needed in column loop
    vector<double> vdDevCols = CalcDev(h1_projection_col, h1_dev_chip, h1_dev, maxhits); // calculate deviation and fill histograms
    pair<double, double> pdMeanSigma = CalcMeanSigma(h1_dev_chip); // calculate mean and sigma of gaussian fit to deviation distribution

    g_Mean ->SetPoint(iChipID, iChipID, pdMeanSigma.first);
    g_Sigma->SetPoint(iChipID, iChipID, pdMeanSigma.second);
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


    // loop over columns to check for dead columns
    bool bColIsDead = false;
    for (int iCol = fColumnMin; iCol <= fColumnMax; ++iCol) // loop over columns
    {

      // check if column is dead
      bColIsDead = false;
      int iBinColumn = h2_colrow_chip->GetXaxis()->FindBin(iCol); // get bin number of corresponding column
      bColIsDead = IsDeadCol(vdDevCols.at(iCol), pdMeanSigma); // check if columnn of interest is dead
      //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


       // mask whole column if dead
      if (bColIsDead == true)
      {
        for (int iRow = fRowMin; iRow <= fRowMax; iRow++) // loop over rows
        {

          int iBinRow = h2_colrow_chip->GetYaxis()->FindBin(iRow); // get bin number of corresponding row
          h2_deadpixelmap->SetBinContent(iBinColumn, iBinRow, 1.); //

        } // loop rows
      } // if (bColIsDead == true)
    } // loop columns
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    f_out_QA->cd();
    h1_projection_col->Write();
    h2_deadpixelmap->Write();
    h1_dev_chip->Write();
    f_out->cd();
    h2_deadpixelmap->Write();

    delete h2_deadpixelmap;

  } // end loop over chips
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


  // write to file and clean up
  f_out_QA->cd();
  for (int i = 0; i < iNdiv+1; ++i)
  {
    h1_dev.at(i)->Write();
    delete h1_dev.at(i);
  }
  g_Mean->SetName("g_MeanChip");
  g_Mean->Write();
  g_Sigma->SetName("g_SigmaChip");
  g_Sigma->Write();
  delete g_Sigma;
  delete g_Mean;
  delete h1_dev_chip;
  delete f_out_QA;
  delete f_out;
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  if (SaveStatus != Applied) ApplyPixelMask(SaveStatus);

  return;
};
// EPICALAnalysisObject::ProduceDeadPixelMapBeam
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// EPICALAnalysisObject::ProduceManualPixelMap
void EPICALAnalysisObject::ProduceManualPixelMap (bool force)
{

  printf("\n >>> Producing manual pixel mask... \n");

  string s_out = manualpixelmaskfilepath();

  if (!force)
  {
    if( check_fileexists( s_out ) )
    {
      printf( " >>> Manual pixel map already exists.\n");
      printf( " >>> If manual pixel map should be produced anyways, use 'force'. \n");
      return;
    }
  }

  if ( !check_fileexists( fManualPixelMaskDirPath ) )
  {
    gSystem->Exec(Form("mkdir -p %s", fManualPixelMaskDirPath.data()));
  }


  TFile* f_out = new TFile(s_out.data(),"RECREATE"); // output file for pixel mask

  TH2C* h2_deadpixelmap = InitHist2DChip<TH2C>("h2_pixelmap");

  int iBinCol = -1, iBinRow = -1;

  for (int iChipID = fChipMin; iChipID <= fChipMax; ++iChipID)
  {
    h2_deadpixelmap->Reset();
    h2_deadpixelmap->SetName(Form("h2_pixelmap_chip%i", iChipID));
    h2_deadpixelmap->SetTitle(Form("h2_pixelmap_chip%i", iChipID));

    for (int iCol = fColumnMin; iCol <= fColumnMax; ++iCol)
    {
      iBinCol = h2_deadpixelmap->GetXaxis()->FindBin(iCol);
      for (int iRow = fRowMin; iRow <= fRowMax; ++iRow)
      {
        iBinRow = h2_deadpixelmap->GetYaxis()->FindBin(iRow);

        // mask if pixel is on edge of prototype for every chip
        if (iCol == fColumnMin || // first column
            iCol == fColumnMax || // last column
            iRow == fRowMin || // first row
            iRow == fRowMax) // last row
        {
          h2_deadpixelmap->SetBinContent(iBinCol, iBinRow, 1);
        }
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


        // mask faulty readout region in chip 30
        if (iChipID == 30 && // chip 30 only
            iCol >= 160 && // begin of readout region
            iCol <= 191) // end of readout region
        {
          h2_deadpixelmap->SetBinContent(iBinCol, iBinRow, 1);
        }
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

      }
    }

    f_out->cd();
    h2_deadpixelmap->Write();
  }

  delete h2_deadpixelmap;
  delete f_out;

  return;
}
// EPICALAnalysisObject::ProduceManualPixelMap
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// EPICALAnalysisObject::ProduceCombinedPixelMap
void EPICALAnalysisObject::ProduceCombinedPixelMap (bool force)
{

  printf("\n >>> Producing combined pixel mask... \n");

  string s_out = combinedpixelmaskfilepath();

  if (!force)
  {
    if( check_fileexists( s_out ) )
    {
      printf( " >>> Combined pixel mask already exists.\n");
      printf( " >>> If combined pixel mask should be produced anyways, use 'force'. \n");
      return;
    }
  }
  else gSystem->Exec(Form("rm %s", s_out.data())); // if production is forced file needs to be deleted otherwise LoadPixelMasks would just load old file

  if ( !check_fileexists( fCombinedPixelMaskDirPath ) )
  {
    gSystem->Exec(Form("mkdir -p %s", fCombinedPixelMaskDirPath.data()));
  }


  // produce all single masks
  ProduceNoisyPixelMapClassification(force);
  ProduceNoisyPixelMapPedestal(force);
  ProduceNoisyPixelMapBeam(force);
  ProduceDeadPixelMapClassification(force);
  ProduceDeadPixelMapBeam(force);
  ProduceManualPixelMap(force);
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  LoadPixelMasks(kAll);

  TFile* f_out = new TFile(s_out.data(),"RECREATE"); // output file for pixel mask

  f_out->cd();

  for (auto& mask : fPixelMasks)
  {
    mask->Write();
    mask->SetDirectory(0);
  }

  delete f_out;

  return;
}
// EPICALAnalysisObject::ProduceCombinedPixelMap
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// EPICALAnalysisObject::LoadPixelMasks
void EPICALAnalysisObject::LoadPixelMasks (ePixelMask ePM)
{

  std::cout << "\n >>> Loading pixel masks... " << std::endl;

  if (ePM == fPixelMaskStatus) return;


  // reset pixel masks if previously loaded
  ResetPixelMasks();
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


  // set which pixel masks to load
  const int nMasks = 6; // number of different available pixel masks (noisy class, ped, beam, dead class, beam, manual)
  bool bToLoad[nMasks] = {false}; // array of bools handling which masks to load

  if (ePM == kAll) // use all masks
  {
    if ( check_fileexists( combinedpixelmaskfilepath() ) )
    {
      TFile* f_in = new TFile(combinedpixelmaskfilepath().data(), "READ");

      for (auto iChipID = fChipMin; iChipID <= fChipMax; ++iChipID)
      {
        fPixelMasks.push_back((TH2C*) f_in->Get(Form("h2_pixelmap_chip%i", iChipID)));
        fPixelMasks.at(iChipID)->SetDirectory(0);
      }

      delete f_in;
      fPixelMaskStatus = ePM;
      return;
    }
    else for (int i = 0; i < nMasks; ++i) bToLoad[i] = true;
  }
  else if (ePM == kNoisy) // use noisy masks
  {
    bToLoad[0] = true; // noisy from classification
    bToLoad[1] = true; // noisy from pedestal
    bToLoad[2] = true; // noisy from beam
  }
  else if (ePM == kDead) // use dead masks
  {
    bToLoad[3] = true; // dead from classification
    bToLoad[4] = true; // dead from beam
  }
  else if (ePM == kManual) // use dead masks
  {
    bToLoad[5] = true; // manual pixel mask
  }
  else if (ePM == kNoisyClass) // use noisy masks from classification
  {
    bToLoad[0] = true; // noisy from classification
  }
  else if (ePM == kNoisyPed) // use noisy masks from pedestals
  {
    bToLoad[1] = true; // noisy from pedestal
  }
  else if (ePM == kNoisyBeam) // use noisy masks from beam
  {
    bToLoad[2] = true; // noisy from beam
  }
  else if (ePM == kDeadClass) // use dead masks from classification
  {
    bToLoad[3] = true; // dead from classification
  }
  else if (ePM == kDeadBeam) // use dead masks from beam
  {
    bToLoad[4] = true; // dead from beam
  }
  else
  {
    printf(" ### Unknown pixel mask identifier. \n");
    printf(" ### Cannot load pixel masks. \n");
    return;
  }
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  int iPedRun = getpedestalrunnr(fRunNr);
  string filepaths[nMasks] = {
    noisypixelmaskclassificationfilepath(), // same for all runs
    Form("%spixelmasks/noisypixels/pedestal/Run_%.4i/noisypixelmask_pedestal_Run%.4i.root", fOutputDirPath.data(), iPedRun, iPedRun), // makes sure to load corresponding pedestal run
    noisypixelmaskbeamfilepath(), // automatically loads correct energy
    deadpixelmaskclassificationfilepath(), // same for all runs
    deadpixelmaskbeamfilepath(),
    manualpixelmaskfilepath() // same for all runs
  };

  string notes[nMasks] = {
    "noisy -> classification",
    "noisy -> pedestal",
    "noisy -> beam",
    "dead  -> classification",
    "dead  -> beam",
    "manual"
  };


  // create pixel masks for every chip to be filled
  for (auto iChipID = fChipMin; iChipID <= fChipMax; ++iChipID)
  {
    fPixelMasks.push_back(InitHist2DChip<TH2C>(Form("h2_pixelmap_chip%i", iChipID)));
  }
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


  // loop over all available masks
  for (int it = 0; it < nMasks; ++it)
  {

    if (!bToLoad[it]) continue; // skip masks if not in list to be loaded

    printf(" >>> %s \n", notes[it].data());


    // check if root file exists
    if( !check_fileexists( filepaths[it] ) )
    {
      printf(" ### Pixel masks (%s) do not exist. \n", filepaths[it].data());
      printf(" ### Produce them first. \n");
      continue;
    }
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


    TFile* f_in = new TFile(filepaths[it].data(), "READ");
    TH2C* h2_pixelmap;
    double factor = TMath::Power(2,it); // equivalent to 6 different bits, each representing one mask

    for (auto iChipID = fChipMin; iChipID <= fChipMax; ++iChipID)
    {
      h2_pixelmap = (TH2C*) f_in->Get(Form("h2_pixelmap_chip%i", iChipID));
      fPixelMasks.at(iChipID)->Add(h2_pixelmap, factor);
    }

    delete f_in;
  } // loop over masks
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  fPixelMaskStatus = ePM;

  return;
};
// EPICALAnalysisObject::LoadPixelMasks
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// EPICALAnalysisObject::ApplyPixelMask
void EPICALAnalysisObject::ApplyPixelMask ()
{
  ApplyPixelMask(fPixelMaskStatus); // per default apply whichever mask is loaded
  return;
};


void EPICALAnalysisObject::ApplyPixelMask (ePixelMask ePM)
{

  printf("\n >>> Applying pixel mask... \n");
  if (ePM == fHitmapStatus) return; // mask is already applied to hitmap
  if (ePM == kNotLoaded || ePM == kNotApplied) // can't apply undefined/no pixel mask
  {
    LoadHitmaps();
    ResetPixelMasks();
    return;
  }

  // make sure hitmaps and pixel masks are loaded (always reloads pixel mask!)
  LoadHitmaps(); // load unmodified hitmaps
  LoadPixelMasks(ePM); // default is whichever mask is currently loaded
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


  int iBinCol = -1, iBinRow = -1;
  for (int iChipID = fChipMin; iChipID <= fChipMax; ++iChipID)
  {
    for (int iCol = fColumnMin; iCol <= fColumnMax; ++iCol)
    {
      iBinCol = fHitmaps.at(iChipID)->GetXaxis()->FindBin(iCol); // find bin for column on x axis
      for (int iRow = fRowMin; iRow <= fRowMax; ++iRow)
      {
        iBinRow = fHitmaps.at(iChipID)->GetYaxis()->FindBin(iRow); // find bin for row on y axis


        // apply pixel mask
        if (fPixelMasks.at(iChipID)->GetBinContent(iBinCol, iBinRow) > 0) // check if pixel should be masked
        {
          fHitmaps.at(iChipID)->SetBinContent(iBinCol, iBinRow, 0.); // modify hitmap
          fHitmaps.at(iChipID)->SetBinError(iBinCol, iBinRow, 0.); // modify hitmap
        }
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


      } // loop over rows
    } // loop over columns
    fHitmaps.at(iChipID)->ResetStats(); // reset stats to account for masked pixels
  } // loop over chips

  fHitmapStatus = ePM; // set status of hitmap to modified

  return;
};
// EPICALAnalysisObject::ApplyPixelMask
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// EPICALAnalysisObject::ResetHitmaps
void EPICALAnalysisObject::ResetHitmaps ()
{
  if (!fHitmaps.empty())
  {
    for (auto& mask : fHitmaps) delete mask;
    fHitmaps.clear();
  }
  fHitmapStatus = kNotLoaded;
  return;
};
// EPICALAnalysisObject::ResetHitmaps
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// EPICALAnalysisObject::ResetPixelMasks
void EPICALAnalysisObject::ResetPixelMasks ()
{
  if (!fPixelMasks.empty())
  {
    for (auto& mask : fPixelMasks) delete mask;
    fPixelMasks.clear();
  }
  fPixelMaskStatus = kNotLoaded;
  return;
};
// EPICALAnalysisObject::ResetPixelMasks
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// EPICALAnalysisObject::GetBadPixelMapFromTextFile
vector<TH2C*> EPICALAnalysisObject::GetBadPixelMapFromTextFile (string str)
{
  TGraph2D* gbeam = new TGraph2D(str.data(), "%lg %*lg %lg %lg"); // structure of input file is: chip lane col row

  vector<TH2C*> vh2_hotpixelmaps;
  for (auto iChip = fChipMin; iChip <= fChipMax; ++iChip)
  {
    vh2_hotpixelmaps.push_back(InitHist2DChip<TH2C>(Form("h2_pixelmap_chip%i", iChip)));
  }

  double col, row, chip;
  for (int it = 0; it < gbeam->GetN(); ++it)
  {
    gbeam->GetPoint(it, chip, col, row);
    int iBinCol  = vh2_hotpixelmaps.at(chip)->GetXaxis()->FindBin(col);
    int iBinRow  = vh2_hotpixelmaps.at(chip)->GetYaxis()->FindBin(row);
    vh2_hotpixelmaps.at(chip)->SetBinContent(iBinCol, iBinRow, 1);
  }

  delete gbeam;

  return vh2_hotpixelmaps;
};
// EPICALAnalysisObject::GetBadPixelMapFromTextFile
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// EPICALAnalysisObject::ProduceBadPixelMapClassification
void EPICALAnalysisObject::ProduceBadPixelMapClassification (string str, bool force)
{

  if (strcmp(str.data(), "noisy") != 0 && strcmp(str.data(), "dead") != 0)
  {
    printf( " ### Cannot produce bad pixel map from classification for '%s'.\n", str.data() );
    printf( " ### Use either 'noisy' or 'dead' as argument. \n");
    return;
  }

  printf("\n >>> Producing %s pixel mask from classification... \n", str.data());

  string s_in = Form("../input/%spixels_classification/%spixels_chipID_col_row.txt", str.data(), str.data());
  string s_dirpath, s_out;
  if      (strcmp(str.data(), "noisy") == 0)
  {
    s_dirpath = fNoisyPixelMaskClassificationDirPath;
    s_out = noisypixelmaskclassificationfilepath();
  }
  else if (strcmp(str.data(), "dead")  == 0)
  {
    s_dirpath = fDeadPixelMaskClassificationDirPath;
    s_out = deadpixelmaskclassificationfilepath();
  }
  else return;

  if ( !check_fileexists( s_dirpath ) )
  {
    gSystem->Exec(Form("mkdir -p %s", s_dirpath.data()));
  }

  if (!force)
  {
    if( check_fileexists( s_out ) )
    {
      printf( " >>> Bad (%s) pixel map from classification already exists.\n", str.data());
      printf( " >>> If %s pixel map should be produced anyways, use 'force'. \n", str.data());
      return;
    }
  }

  vector<TH2C*> vh2_hotpixelmaps = this->GetBadPixelMapFromTextFile(s_in.data());

  TFile* f_out = new TFile(s_out.data(),"RECREATE");
  for (auto &map : vh2_hotpixelmaps)
  {
      map->Write();
      delete map;
  }

  delete f_out;

  return;
};
// EPICALAnalysisObject::ProduceBadPixelMapClassification
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool EPICALAnalysisObject::IsPedestal()
{
  bool isped;
  if (fRunNr == getpedestalrunnr(fRunNr)) isped = true;
  else isped = false;
  return isped;
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~ end analysis functions ~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~ end public functions ~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


// private functions

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// EPICALAnalysisObject::rawdatafilepath
string EPICALAnalysisObject::rawdatafilepath ()
{
  const char *homedir = getenv("HOME");

  string s_Foldernamedataperiod;
  if      (fDataTakingPeriod == kFeb20) s_Foldernamedataperiod = "mTower_Data_DESY_Feb_2020";
  else if (fDataTakingPeriod == kNov19) s_Foldernamedataperiod = "mTower_Data_DESY_Nov-Dec_2019";
  string s_Pathtofile = Form("%s/data/%s/Run_%.4i/rootout_raw/conv_Run_%.4i.root", homedir, s_Foldernamedataperiod.data(), fRunNr, fRunNr);
  return s_Pathtofile;
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
string EPICALAnalysisObject::hitmapdirpath ()
{
  return Form("%shitmaps/Run_%.4i/", fOutputDirPath.data(), fRunNr);
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
string EPICALAnalysisObject::hitmapfilepath ()
{
  return Form("%shitmap_Run%.4i.root", fHitmapDirPath.data(), fRunNr);
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
string EPICALAnalysisObject::noisypixelmaskclassificationfilepath ()
{
  return Form("%snoisypixelmask_classification.root", fNoisyPixelMaskClassificationDirPath.data());
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
string EPICALAnalysisObject::noisypixelmaskpedestalfilepath ()
{
  return Form("%snoisypixelmask_pedestal_Run%.4i.root", fNoisyPixelMaskPedestalDirPath.data(), fRunNr);
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
string EPICALAnalysisObject::noisypixelmaskbeamfilepath ()
{
  return Form("%snoisypixelmask_beam_%.1fGeV.root", fNoisyPixelMaskBeamDirPath.data(), runnumber2energy_Feb.at(fRunNr));
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
string EPICALAnalysisObject::nhitsperpixelfilepath ()
{
  return Form("%snhitsperpixel_Run%.4i.root", fHitmapDirPath.data(), fRunNr);
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
string EPICALAnalysisObject::deadpixelmaskclassificationfilepath ()
{
  return Form("%sdeadpixelmask_classification.root", fDeadPixelMaskClassificationDirPath.data());
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
string EPICALAnalysisObject::deadpixelmaskbeamfilepath ()
{
  return Form("%sdeadpixelmask_beam_Run%.4i.root", fDeadPixelMaskBeamDirPath.data(), fRunNr);
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
string EPICALAnalysisObject::manualpixelmaskfilepath ()
{
  return Form("%smanualpixelmask.root", fManualPixelMaskDirPath.data());
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
string EPICALAnalysisObject::combinedpixelmaskfilepath ()
{
  return Form("%scombinedpixelmask_Run%.4i.root", fCombinedPixelMaskDirPath.data(), fRunNr);
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// EPICALAnalysisObject::CalcDev
vector<double> EPICALAnalysisObject::CalcDev(TH1D* h_proj, TH1D* h1_dev_chip, vector<TH1D*> h1_dev, double maxhits)
{
  vector<double> vdDevCols; // return variable, filled in loop over columns
  double width = 32.; // width of fitting window for column of interest

  // loop over columns
  for (int col = fColumnMin; col <= fColumnMax; ++col) // loop over columns
  {

    // define lower and upper bound for region of interest
    double collow = col - width;
    double colup  = col + width;
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


    // get bin numbers for columnn of interest and lower and upper bound
    int bincent = h_proj->FindBin(col);
    int binlow  = h_proj->FindBin(collow);
    int binup   = h_proj->FindBin(colup);
    if (binlow < 1) binlow = 1; // lower bound can't be below first bin
    if (binup  > h_proj->GetNbinsX()) binup = h_proj->GetNbinsX(); // upper bound can't be higher than number of bins
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


    // option 1: compare to fit value
    TF1* f_pol1 = new TF1("pol1", "pol1", collow, colup); // define pol1 in region of interest
    h_proj->Fit(f_pol1, "QR0");
    double contcent = h_proj->GetBinContent(bincent);
    double sigma = TMath::Sqrt(contcent); // error of column is square root of content
    double exp = f_pol1->Eval(h_proj->GetBinCenter(bincent)); // expected value is fit function at column of interest
    double reldev = (contcent - exp) / sigma; // relative deviation of number of hits in column from expected value in terms of unc.
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


    // store values in variables/histograms
    vdDevCols.push_back(reldev);
    h1_dev_chip->Fill(reldev);
    h1_dev.at(0)->Fill(reldev);
    if (h1_dev.size() > 1)
    {
      int ndiv = h1_dev.size() - 1;

      // loop over hit density regions
      double regwidth[2] = {0., 0.}; // first hit density region starts at 0., then logarithmicaly until max number of hits
      for (int it = 1; it <= ndiv; ++it)
      {
        regwidth[0] = regwidth[1];
        regwidth[1] = TMath::Power(10, it * TMath::Log10(maxhits) / ndiv); // divide range from 0 to max number of hits logarithmicaly
        if (contcent >= regwidth[0] && contcent < regwidth[1]) // check if hit density is in region
        {
          h1_dev.at(it)->Fill(reldev);
        }
      } // loop over hit density regions
    } // if (h1_dev.size() > 1)
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    delete f_pol1;

  } // loop over columns
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


  return vdDevCols;
};
// EPICALAnalysisObject::CalcDev
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// EPICALAnalysisObject::CalcMeanSigma
pair<double, double> EPICALAnalysisObject::CalcMeanSigma (TH1D* h1_dev_chip)
{
  TF1* f_gaus = new TF1("f_gaus", "gaus", h1_dev_chip->GetXaxis()->GetXmin(), h1_dev_chip->GetXaxis()->GetXmax());
  h1_dev_chip->Fit(f_gaus, "Q0");
  double mean = f_gaus->GetParameter(1);
  double sigma = f_gaus->GetParameter(2);

  delete f_gaus;

  return make_pair(mean, sigma);
};
// EPICALAnalysisObject::CalcMeanSigma
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// EPICALAnalysisObject::IsDeadCol
bool EPICALAnalysisObject::IsDeadCol (double dDevCol, pair<double, double> pdMeanSigma)
{

  double reldev = dDevCol; // deviation for column of interest
  double dMean  = pdMeanSigma.first; // mean of deviation distribution for for current chip
  double dSigma = pdMeanSigma.second; // sigma of deviation distribution for for current chip
  double dWidth = 5.; // allowed width in terms of sigma for definition of dead column

  bool bColIsDead = false;
  if (reldev < dMean-dWidth*dSigma) bColIsDead = true;

  return bColIsDead;
};
// EPICALAnalysisObject::IsDeadCol
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// EPICALAnalysisObject::GetMaxHitsCol
double EPICALAnalysisObject::GetMaxHitsCol ()
{
  double nHitsmax = 0.;

  for (auto& hitmap : fHitmaps)
  {
    TH1D* proj = (TH1D*) hitmap->ProjectionX();
    for (int col = fColumnMin; col <= fColumnMax; ++col)
    {
      if (proj->GetBinContent(col) > nHitsmax) nHitsmax = proj->GetBinContent(col);
    }
  }

  return nHitsmax;
};
// EPICALAnalysisObject::GetMaxHitsCol
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~ end private functions ~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
