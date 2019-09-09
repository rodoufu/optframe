#pragma once
#ifndef NPP_CONSTRUCTIVE_Rand_H_
#define NPP_CONSTRUCTIVE_Rand_H_

#include "../../OptFrame/Constructive.hpp"
#include "../../OptFrame/Util/RandGenMersenneTwister.hpp"

#include "ProblemInstance.h"

#include "Representation.h"

#include <list>

#include <algorithm>
#include <stdlib.h>

using namespace std;

using namespace optframe;

namespace NPP
{

// If you need ADS, you can inherit Constructive<RepNPP, YourADS>
class ConstructiveRand: public Constructive<RepNPP>
{
private:
   ProblemInstance& pNPP;
    RandGenMersenneTwister &rg;

   // Your private vars

public:
	
	ConstructiveRand(ProblemInstance& _pNPP, RandGenMersenneTwister &rg);
	
	virtual ~ConstructiveRand();

    string id() const
    {
        return Constructive<RepNPP>::idComponent().append(":ConstructiveRand");
    }

	SolutionNPP* generateSolution(double timelimit);
};

}

#endif /*NPP_CONTRUCTIVE_Rand_H_*/
