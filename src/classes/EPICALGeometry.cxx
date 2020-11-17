//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~~~ Project:       EPICAL                            ~~~~~//
//~~~~~ File:          EPICALGeometry.cxx                ~~~~~//
//~~~~~ Author:        F. Pliquett                       ~~~~~//
//~~~~~ Created:       03.08.2020                        ~~~~~//
//~~~~~ Description:   "Implementation of                ~~~~~//
//~~~~~                 EPICAL geometry"                 ~~~~~//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//


#include <iostream>
#include <cmath>

#include "../../include/EPICALGeometry.h"
#include "../../include/EPICALUtility.h"
#include "../../include/EPICALConversions.h"

unsigned int countdigits (const unsigned int &);


// public functions

// special functions (constructor/destructor)

EPICALGeometry::EPICALGeometry () :
fPeriod(kFeb20)
{
  init();
};


EPICALGeometry::EPICALGeometry (eDTP period) :
fPeriod(period)
{
  init();
};


EPICALGeometry::EPICALGeometry (unsigned int run) :
fPeriod(getdataperiod(run))
{
  init();
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


// useful functions
void EPICALGeometry::PrintDetectorGeometry ()
{
  pair<int, int> chips;
  pair<int, int> lanes;
  std::cout <<  "               |beam|                 " << std::endl;
  std::cout <<  "               | e- |                 " << std::endl;
  std::cout <<  "               | e- |                 " << std::endl;
  std::cout <<  "               | e- |                 " << std::endl;
  std::cout <<  "               | e- |                 " << std::endl;
  std::cout << "           \\   | e- |   /             " << std::endl;
  std::cout << "            \\----------/             " << std::endl;
  std::cout << "             \\   e-   /             " << std::endl;
  std::cout << "              \\  e-  /             " << std::endl;
  std::cout << "               \\ e- /             " << std::endl;
  std::cout << "                \\  /             " << std::endl;
  std::cout << "                 \\/             " << std::endl << std::endl;
  std::cout << "     right                left" << std::endl;
  std::cout << "   chip/lane   layer   chip/lane" << std::endl;
  for (auto layer = this->GetLayerMin(); layer <= this->GetLayerMax(); ++layer)
  {
    chips = this->GetChipIDFromLayer(layer);
    std::swap(chips.first, chips.second); // swap left/right chips (beam is from top)
    int l2[2] = {this->GetLaneFromChipID(chips.first), this->GetLaneFromChipID(chips.second)};
    lanes = make_pair(l2[0], l2[1]);

    std::cout << std::string(7-countdigits(chips.first),' ')
              << chips.first << "/" << lanes.first
              << std::string(9-countdigits(lanes.first), ' ')
              << layer
              << std::string(10-countdigits(layer)-countdigits(chips.second), ' ')
              << chips.second<< "/" << lanes.second << std::endl;
  }
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~ end public functions ~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



void EPICALGeometry::init ()
{
  if (fPeriod == kFeb20)
  {
    fColMin       = 0    ;
    fColMax       = 1023 ;
    fRowMin       = 0    ;
    fRowMax       = 511  ;
    fChipMin      = 0    ;
    fChipMax      = 47   ;
    fLaneMin      = 32   ;
    fLaneMax      = 79   ;
    fLayerMin     = 0    ;
    fLayerMax     = 23   ;
    fChipID2Lane  = chipid2lane_feb_lut;
    fLane2ChipID  = lane2chipid_feb_lut;
    fChipID2Layer = chipid2layer_feb_lut;
    fLayer2ChipID = layer2chipid_feb_lut;
  }

  else if (fPeriod == kNov19)
  {
    // to be implemented if needed
    std::cout << " ### EPICAL geometry for november data taking not yet implemented. " << std::endl;
  }

  else
  {
    std::cout << " ### Undefined data taking period, cannot initialize EPICAL geometry properly. " << std::endl;
  }
};



unsigned int countdigits (const unsigned int &number)
{
  if (number == 0) return 1;
  else return static_cast<unsigned int>(log10(number)+1);
};
