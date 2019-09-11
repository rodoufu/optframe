#pragma once
#ifndef NPP_REPRESENTATION_H_
#define NPP_REPRESENTATION_H_

#include <vector>

#include "OptFrame/Util/printable.h"
#include "OptFrame/Util/Matrix.hpp"
#include "OptFrame/Solution.hpp"
#include "OptFrame/Solutions/CopySolution.hpp"


#include <vector>

using namespace std;

using namespace optframe;

// Solution Representation
using RepNPP = std::vector<bool>;

using SolutionNPP = CopySolution<RepNPP>;

// Remember that RepNPP must implement: (i) copy constructor and (ii) operator<<

using MY_ADS = OPTFRAME_DEFAULT_ADS;

// Auxiliary Data Structures (default 'int')
//typedef int MY_ADS; // maybe try again in the future something like ADSNPP...

//#include <ostream>
//ostream & operator<< (ostream & s, const &RepNPP r)
//{
//    bool space = false;
//    for (int x : r) {
//        if (space) {
//            s << " ";
//        }
//        s << x;
//        space = true;
//    }
//}

#define PRINT(X) //{\
//    std::cout << "|"; \
//    for (auto &x : (X)) { \
//        std::cout << x << " "; \
//    } \
//    std::cout << "|"; }
//#define PRINTLN(X) {\
//    PRINT(X); \
//    std::cout << std::endl; }

#endif /*NPP_REPRESENTATION_H_*/

