#include "ConstructiveRand.h"

using namespace NPP;

ConstructiveRand::ConstructiveRand(ProblemInstance& _pNPP, RandGenMersenneTwister& _rg):
        pNPP(_pNPP), rg(_rg)
{
}
	
ConstructiveRand::~ConstructiveRand()
{
}

SolutionNPP* ConstructiveRand::generateSolution(double timelimit)
{
    RepNPP newRep;

    for (int i = 0; i < pNPP.getSize(); ++i) {
        newRep.push_back(rg.rand(2) == 1);
    }
    return new SolutionNPP(newRep);
}
