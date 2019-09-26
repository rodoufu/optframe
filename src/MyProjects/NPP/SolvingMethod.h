#pragma once
#ifndef NPP_SOLVINGMETHOD_H
#define NPP_SOLVINGMETHOD_H

#include <OptFrame/Util/RandGenMersenneTwister.hpp>
#include "Representation.h"

tuple<SolutionNPP, Evaluation, double, SolutionNPP, Evaluation, double>
solveSA(RandGenMersenneTwister &rg, string instance, bool print = false);

#endif //NPP_SOLVINGMETHOD_H
