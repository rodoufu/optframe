#include <iostream>
#include <iomanip>
#include <fstream>
#include <memory>
#include <utility>
#include <tuple>
#include <chrono>
#include <future>

#include <sys/types.h>
#include <dirent.h>

#include <stdlib.h>
#include <math.h>

#include "OptFrame/Heuristics/SA/BasicSimulatedAnnealing.hpp"
#include "OptFrame/Heuristics/LocalSearches/BestImprovement.hpp"
#include "OptFrame/Heuristics/LocalSearches/FirstImprovement.hpp"
#include "OptFrame/Heuristics/LocalSearches/HillClimbing.hpp"
#include "OptFrame/Heuristics/LocalSearches/RandomDescentMethod.hpp"
#include "OptFrame/Util/CheckCommand.hpp"
#include "OptFrame/SingleObjSearch.hpp"
#include "OptFrame/Util/RandGenMersenneTwister.hpp"
#include "OptFrame/Util/printable.h"

#include "NPP.h"
#include "NPP/SolvingMethod.h"

using namespace std;
using namespace optframe;
using namespace NPP;

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("The expected use is:\n%s <input file> <seed>", argv[0]);
        return EXIT_FAILURE;
    }
    unsigned seed;
    string fileName(argv[1]);
    sscanf("%u", argv[2], &seed);
    if (!ifstream(fileName.c_str()).good()) {
        printf("The file \"%s\" does not exist", fileName.c_str());
        return EXIT_FAILURE;
    }

    RandGenMersenneTwister rg(seed); // not using system rand() anymore

    auto resp = solveSA(rg, fileName);
    cout << "file;SA;timeSA;LS;timeLS" << endl;
    cout <<
         fileName << ";" <<
         std::fixed << std::setprecision(0) << get<1>(resp).evaluation() << ";" <<
         std::fixed << std::setprecision(5) << get<2>(resp) << ";" <<
         std::fixed << std::setprecision(0) << get<4>(resp).evaluation() << ";" <<
         std::fixed << std::setprecision(5) << get<5>(resp) << "" <<
         endl;

    return 0;
}
