//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~~~ Project:       EPICAL                            ~~~~~//
//~~~~~ File:          EPICALAnalysisObject.h            ~~~~~//
//~~~~~ Author:        F. Pliquett                       ~~~~~//
//~~~~~ Created:       31.07.2020                        ~~~~~//
//~~~~~ Description:   "Header file for class that is    ~~~~~//
//~~~~~                 used for analyses for the        ~~~~~//
//~~~~~                 digital calorimeter prototype    ~~~~~//
//~~~~~                 EPICAL."                         ~~~~~//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//


#ifndef _EPICALANALYSISOBJECT_H_
#define _EPICALANALYSISOBJECT_H_

#include <string>
#include <utility>
#include <vector>

#include "TH1.h"
#include "TH2.h"

#include "EPICALGeometry.h"

using namespace std;

// enum eDTP {kNov19, kFeb20}; // enum containing the test beam periods

enum ePixelMask {kAll, kNoisy, kDead, kManual, kNoisyClass, kNoisyPed, kNoisyBeam, kDeadClass, kDeadBeam, kNotApplied, kNotLoaded};


class EPICALAnalysisObject
{

  private:

    // private variables

    // variables depending on the run number
    int fRunNr; // run number
    int fNevents; // number of events of current run
    eDTP fDataTakingPeriod; // month of test beam ("Nov", "Feb")
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


    // variables for raw data root files
    string fRawDataFilePath; // path to local directory where raw root files are stored
    string fTreeName; // name tree in raw data files
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


    // directory structure
    string fOutputDirPath; // path to local directory where output files are stored
    string fHitmapDirPath; // path to local directory where produced hitmaps are/should be stored
    string fPixelMaskDirPath; // path to local directory where produced pixel masks are/should be stored
    string fNoisyPixelMaskClassificationDirPath; // path to local directory where hot pixel mask from classification is stored
    string fNoisyPixelMaskPedestalDirPath; // path to local directory where hot pixel mask from pedestal runs is stored
    string fNoisyPixelMaskBeamDirPath; // path to local directory where hot pixel mask from beam runs is stored
    string fDeadPixelMaskClassificationDirPath; // path to local directory where dead pixel mask from classification is stored
    string fDeadPixelMaskBeamDirPath; // path to local directory where dead pixel mask from beam runs is stored
    string fManualPixelMaskDirPath; // path to local directory where manual pixel mask is stored
    string fCombinedPixelMaskDirPath; // path to local directory where combined pixel mask is stored
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


    // hitmaps and pixel masking
    float fHotPixelCriterion; // criterion for pedestal-based hot pixel removal

    std::vector<TH2D*> fHitmaps; // vector of hitmaps for current run
    std::vector<TH2C*> fPixelMasks; // vector of pixel masks for current run

    ePixelMask fHitmapStatus; // status of hitmap/which pixel mask has been applied
    ePixelMask fPixelMaskStatus; // status of pixel mask/which pixel mask is loaded
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


    // EPICAL geometry
    EPICALGeometry fGeometry; // geometry object in which number of columns, rows etc. is stored as well as conversion tables for lane/chip/layer numbers

    int fColumnMin ;
    int fColumnMax ;
    int fNcolumns  ;

    int fRowMin    ;
    int fRowMax    ;
    int fNrows     ;

    int fLaneMin   ;
    int fLaneMax   ;
    int fNlanes    ;

    int fChipMin   ;
    int fChipMax   ;
    int fNchips    ;

    int fLayerMin  ;
    int fLayerMax  ;
    int fNlayers   ;
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //~~~~~ end private variables ~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


    // private functions
    string rawdatafilepath ();
    string hitmapdirpath ();
    string hitmapfilepath ();
    string noisypixelmaskclassificationfilepath ();
    string noisypixelmaskpedestalfilepath ();
    string noisypixelmaskbeamfilepath ();
    string nhitsperpixelfilepath ();
    string deadpixelmaskclassificationfilepath ();
    string deadpixelmaskbeamfilepath ();
    string manualpixelmaskfilepath ();
    string combinedpixelmaskfilepath ();

    vector<double> CalcDev(TH1D* h1_projection_col, TH1D* h1_dev_chip, vector<TH1D*> h1_dev, double maxhits);
    pair<double, double> CalcMeanSigma(TH1D* h1_dev_chip);
    bool IsDeadCol(double dDevCol, pair<double, double> pdMeanSigma);
    double GetMaxHitsCol ();
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //~~~~~ end private functions ~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


  public:

    // public functions

    // constructor/destructor
    EPICALAnalysisObject(); // default constructor
    EPICALAnalysisObject(const int &run); // constructor initializing variables depending on run number
    ~EPICALAnalysisObject(); // default destructor
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


    // analysis functions
    void ProduceHitmaps (bool force = false);
    void LoadHitmaps ();
    void ProduceNoisyPixelMapClassification (bool force = false);
    void ProduceNoisyPixelMapPedestal       (bool force = false);
    void ProduceNoisyPixelMapBeam           (bool force = false);
    void ProduceNhitsPerPixel               (bool force = false);
    void ProduceDeadPixelMapClassification  (bool force = false);
    void ProduceDeadPixelMapBeam            (bool force = false);
    void ProduceManualPixelMap              (bool force = false);
    void ProduceCombinedPixelMap            (bool force = false);
    void LoadPixelMasks                     (ePixelMask ePM);
    void ApplyPixelMask                     ();
    void ApplyPixelMask                     (ePixelMask ePM);

    void ResetHitmaps ();
    void ResetPixelMasks ();

    vector<TH2C*> GetBadPixelMapFromTextFile (string str);
    void ProduceBadPixelMapClassification (string str, bool force = false);

    template<class T> T* InitHist2DChip (string name);
    bool IsPedestal ();
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


    // setter and getter for internal variables
    int  GetRunNr ()               { return fRunNr; };
    void SetRunNr (const int &run) { fRunNr = run; };

    int  GetNevents ()                 { return fNevents; };
    void SetNevents (const int &nevts) { fNevents = nevts; };

    eDTP GetDataTakingPeriod ()                { return fDataTakingPeriod; };
    void SetDataTakingPeriod (const eDTP &dtp) { fDataTakingPeriod = dtp; };


    string GetDataFilePath ()                  { return fRawDataFilePath; };
    void   SetDataFilePath (const string &str) { fRawDataFilePath = str; };

    string GetTreeName ()                  { return fTreeName; };
    void   SetTreeName (const string &str) { fTreeName = str; };


    string GetOutputDirPath ()                  { return fOutputDirPath; };
    void   SetOutputDirPath (const string &str) { fOutputDirPath = str; };

    string GetHitmapDirPath ()                  { return fHitmapDirPath; };
    void   SetHitmapDirPath (const string &str) { fHitmapDirPath = str; };

    string GetPixelMaskDirPath ()                  { return fPixelMaskDirPath; };
    void   SetPixelMaskDirPath (const string &str) { fPixelMaskDirPath = str; };


    float GetHotPixelCriterion ()                 { return fHotPixelCriterion; };
    void  SetHotPixelCriterion (const float &hpc) { fHotPixelCriterion = hpc; };

    std::vector<TH2D*> GetHitmaps ()    {return fHitmaps; };
    std::vector<TH2C*> GetPixelMasks () {return fPixelMasks; };

    ePixelMask GetHitmapStatus ()    {return fHitmapStatus; };
    ePixelMask GetPixelMaskStatus () {return fPixelMaskStatus; };


    EPICALGeometry GetGeometry ()                   { return fGeometry; };
    void           SetGeometry (EPICALGeometry geo) { fGeometry = geo; };


    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //~~~~~ end public functions ~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~ begin template functions ~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

template<class T> T* EPICALAnalysisObject::InitHist2DChip (string name)
{
  T* hist = new T(name.data(), name.data(),
    fNcolumns, static_cast<double>(fColumnMin)-0.5, static_cast<double>(fColumnMax)+0.5,
    fNrows, static_cast<double>(fRowMin)-0.5, static_cast<double>(fRowMax)+0.5);
  hist->GetXaxis()->SetTitle("column");
  hist->GetYaxis()->SetTitle("row");
  return hist;
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~ end template functions ~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif
