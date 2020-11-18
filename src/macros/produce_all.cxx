#include "../../include/EPICALAnalysisObject.h"

using namespace std;


int main (int argc, char** argv)
{

  // if (argc != 2) { printf(" ### Macro expects only the run number as argument. \n"); return 1;}
  // int run = atoi(argv[1]);

  // vector<int> ivPedRuns = {1232, 1246, 1303, 1311, 1332, 1340, 1356, 1374, 1395, 1421, 1438, 1463}; // pedestal run list of february data taking
  vector<int> ivAnalysisRuns = {
    1252, 1263, 1336, 1343, // 1 GeV runs
    1260, 1276, 1337, 1344, // 2 GeV runs
    1251, 1262, 1335, 1341, // 3 GeV runs
    1253, 1257, 1274, 1338, 1345, // 4 GeV runs
    1250, 1261, 1308, 1333, 1339, 1413, // 5 GeV runs
    1309, 1310, 1346, 1375, 1376 // 5.8 GeV runs
  }; // analysis run list of february data taking

  bool force = false;

  for (auto& RunNr : ivAnalysisRuns)
  {
    printf("\n\n ~~~~~ Starting run %i ~~~~~ \n", RunNr);
    EPICALAnalysisObject ao(RunNr);
    // ao.ProduceHitmaps(force);
    // ao.ProduceNoisyPixelMapClassification(force);
    // ao.ProduceNoisyPixelMapPedestal(force);
    // ao.ProduceNoisyPixelMapBeam(force);
    // ao.ProduceDeadPixelMapClassification(force);
    // ao.ProduceDeadPixelMapBeam(force);
    // ao.ProduceManualPixelMap(force);
    ao.ProduceCombinedPixelMap(force);
  }

  return 0;
}
