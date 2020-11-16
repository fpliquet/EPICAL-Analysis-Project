//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~~~ Project:       EPICAL                            ~~~~~//
//~~~~~ File:          EPICALGeometry.h                  ~~~~~//
//~~~~~ Author:        F. Pliquett                       ~~~~~//
//~~~~~ Created:       31.07.2020                        ~~~~~//
//~~~~~ Description:   "Geometry of EPICAL (constant)    ~~~~~//
//~~~~~                 values for chips, columns,       ~~~~~//
//~~~~~                 rows, etc.                       ~~~~~//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//


#ifndef _EPICALGEOMETRY_H_
#define _EPICALGEOMETRY_H_

#include <iostream>
#include <map>
#include <utility>

#include "EPICALUtility.h"
#include "EPICALConversions.h"

using namespace std;


class EPICALGeometry
{

  private:

    // private variables
    eDTP fPeriod;

    int fColMin;
    int fColMax;

    int fRowMin;
    int fRowMax;

    int fChipMin;
    int fChipMax;

    int fLaneMin;
    int fLaneMax;

    int fLayerMin;
    int fLayerMax;

    std::map<int, int>                 fChipID2Lane;
    std::map<int, int>                 fLane2ChipID;
    std::map<int, int>                 fChipID2Layer;
    std::map<int, std::pair<int, int>> fLayer2ChipID;
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //~~~~~ end private variables ~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


    // private functions
    void init();
    void init(eDTP);
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //~~~~~ end private functions ~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


  public:

    // public functions

    // constructor/destructor
    EPICALGeometry (); // default constructor
    EPICALGeometry (eDTP); // constructor using data taking period to set geometry
    EPICALGeometry (unsigned int); // constructor using run number to set geometry
    EPICALGeometry (const EPICALGeometry&) = default;
    EPICALGeometry& operator= (const EPICALGeometry&);
    ~EPICALGeometry () = default; // default destructor
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


    // useful functions
    void PrintDetectorGeometry();
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


    // getter for internal variables
    int GetColMin   () { return fColMin; };
    int GetRowMin   () { return fRowMin; };
    int GetChipMin  () { return fChipMin; };
    int GetLaneMin  () { return fLaneMin; };
    int GetLayerMin () { return fLayerMin; };

    int GetColMax   () { return fColMax; };
    int GetRowMax   () { return fRowMax; };
    int GetChipMax  () { return fChipMax; };
    int GetLaneMax  () { return fLaneMax; };
    int GetLayerMax () { return fLayerMax; };

    int GetNcols   () { return fColMax - fColMin + 1; };
    int GetNrows   () { return fRowMax - fRowMin + 1; };
    int GetNchips  () { return fChipMax - fChipMin + 1; };
    int GetNlanes  () { return fLaneMax - fLaneMin +1; };
    int GetNlayers () { return fLayerMax - fLayerMin +1; };
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


    // chip/lane/layer conversions
    int GetChipIDFromLane (int lane)              { return fLane2ChipID.at(lane); };
    int GetLaneFromChipID (int chipid)            { return fChipID2Lane.at(chipid); };
    int GetLayerFromChipID (int chipid)           { return fChipID2Layer.at(chipid); };
    pair<int, int> GetChipIDFromLayer (int layer) { return fLayer2ChipID.at(layer); };
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //~~~~~ end public functions ~~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

};

#endif
