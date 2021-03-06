//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~~~ Project:       EPICAL                            ~~~~~//
//~~~~~ File:          EPICALUtility.h                   ~~~~~//
//~~~~~ Author:        F. Pliquett                       ~~~~~//
//~~~~~ Created:       07.08.2020                        ~~~~~//
//~~~~~ Description:   "Utility class holding general    ~~~~~//
//~~~~~                 functions."                      ~~~~~//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//


#ifndef _EPICALUTILITY_H_
#define _EPICALUTILITY_H_


#include <iostream>
#include <sys/stat.h>
#include <string>

#include "TH2.h"

#include "EPICALConversions.h"

using namespace std;

enum eDTP {kNov19, kFeb20, kUDF}; // data taking period


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline bool check_fileexists (const std::string& name)
{
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0);
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline bool check_keyinmap (int run, const std::map<int,int>& m)
{
  auto it = m.find(run);
  if (it != m.end()) return true;
  else
  {
    std::cout << " ### Key not found in map. " << std::endl;
    return false;
  }
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
eDTP getdataperiod (unsigned int run)
{
  eDTP period;
  if      (check_keyinmap(run, runnumber2nevents_Feb)) period = kFeb20;
  else if (check_keyinmap(run, runnumber2nevents_Nov)) period = kNov19;
  else
  {
    std::cout << " ### Run number out of range! Period undefined! " << std::endl;
    return kUDF;
  }
  return period;
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int getnevents (unsigned int run)
{
  if      (getdataperiod(run) == kFeb20) return runnumber2nevents_Feb.at(run);
  else if (getdataperiod(run) == kNov19) return runnumber2nevents_Nov.at(run);
  else return -1;
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int getpedestalrunnr (int run) // return pedestal run number corresponding to input run number
{
  vector<int> ivPedRuns = {1232, 1246, 1303, 1311, 1332, 1340, 1356, 1374, 1395, 1421, 1438, 1463, 1750, 1751}; // pedestal run list of february data taking
  std::sort(ivPedRuns.begin(), ivPedRuns.end()); // make sure run numbers are in ascending order
  int iPedRunNr = 0;

  if (run < ivPedRuns.front()) // catch if run number is smaller than first pedestal
  {
    std::cout << "\n ### No pedestal run available for this run (" << run << "). " << std::endl;
    std::cout << " ### Run number too low. " << std::endl;
    return -1;
  }
  else if (run > 1751) // last recorded run in february data taking was 1471 two pedestal (1750, 1751) added later
  {
    std::cout << " ### Run number higher than last run number of data taking. " << std::endl;
    return -1;
  }
  else if (run > ivPedRuns.back()) // catch if run number is higher than last pedestal but smaller than last run recorded
  {
    return ivPedRuns.back(); // return last pedestal run taken
  }

  for (int it = 0; it < static_cast<int>(ivPedRuns.size()); it++) // loop over pedestal runs
  {
    iPedRunNr = ivPedRuns.at(it);

    if (run == iPedRunNr)
    {
      // std::cout << " >>> Current run (" << run << ") is pedestal run. " << std::endl;
      return iPedRunNr;
    }

    if (run > iPedRunNr && run < ivPedRuns.at(it+1)) // check if current run number is between two pedestals
    {
      return iPedRunNr;
    }
  }

  return iPedRunNr;
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
vector<int> GetPedestalRunList (eDTP dtp = kFeb20) // return a list of all pedestal runs from corresponding data taking period
{
  vector<int> ivPedRuns;
  if ( dtp == kFeb20 ) ivPedRuns = {1232, 1246, 1303, 1311, 1332, 1340, 1356, 1374, 1395, 1421, 1438, 1463, 1750, 1751}; // pedestal run list of february data taking
  else if ( dtp == kNov19 ) { printf(" ### Pedestal run list for november data taking not yet implemented. \n");}
  else { printf(" ### Unknown data taking period. \n");}
  return ivPedRuns;
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
vector<int> GetAnalysisRunList (eDTP dtp = kFeb20) // return a list of all runs with defaul settings used for analysis
{
  vector<int> ivAnaRuns;
  if ( dtp == kFeb20 )
  {
    ivAnaRuns = {
      1252, 1263, 1336, 1343, // 1 GeV runs
      1260, 1276, 1337, 1344, // 2 GeV runs
      1251, 1262, 1335, 1341, // 3 GeV runs
      1253, 1257, 1274, 1338, 1345, // 4 GeV runs
      1250, 1261, 1308, 1333, 1339, 1413, // 5 GeV runs
      1309, 1310, 1346, 1375, 1376 // 5.8 GeV runs
    }; // analysis run list of february data taking
  }
  else if ( dtp == kNov19 ) { printf(" ### Analysis run list for november data taking not yet implemented. \n");}
  else { printf(" ### Unknown data taking period. \n");}
  return ivAnaRuns;
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


#endif
