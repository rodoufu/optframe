#include <iostream>
#include <iomanip>
#include <fstream>
#include <memory>
#include <utility>
#include <tuple>
#include <chrono>
#include <future>

#include <OptFrame/NSSeq.hpp>
#include <OptFrame/Evaluation.hpp>
#include <OptFrame/Util/RandGenMersenneTwister.hpp>
#include <OptFrame/Heuristics/SA/BasicSimulatedAnnealing.hpp>
#include <OptFrame/Heuristics/LocalSearches/BestImprovement.hpp>
#include <OptFrame/Heuristics/LocalSearches/FirstImprovement.hpp>
#include <OptFrame/Heuristics/LocalSearches/HillClimbing.hpp>
#include <OptFrame/Heuristics/LocalSearches/RandomDescentMethod.hpp>

#include "Evaluator.h"
#include "ConstructiveGreedy.h"
#include "ConstructiveRand.h"
#include "ProblemInstance.h"
#include "Representation.h"
#include "NSSeqBitFlip.h"
#include "ProblemInstance.h"

using namespace std;
using namespace optframe;
using namespace NPP;

tuple<SolutionNPP, Evaluation, double, SolutionNPP, Evaluation, double>
solveSA(RandGenMersenneTwister &rg, string instance, bool print) {
    unique_ptr<ifstream> ifs(new std::ifstream(instance, std::ifstream::in));
    Scanner scanner(ifs.get());
    ProblemInstance p(scanner);
    ifs->close();

    MyEvaluator ev(p);
    NSSeqBitFlip ns1(p, rg);
    ConstructiveGreedy c1(p);
    ConstructiveRand c2(p, rg);

    NSSeq<RepNPP> *nsseq_bit = &ns1;

    auto start = chrono::steady_clock::now();
    const double alpha = 0.98;
    const int SAmax = 100;
    double Ti = 900.0;
    BasicSimulatedAnnealing<RepNPP, MY_ADS> sa(ev, c2, *nsseq_bit, alpha, SAmax, Ti, rg, print);
    SOSC sosc; // stop criteria
    unique_ptr<pair<SolutionNPP, Evaluation>> r(sa.search(sosc));
    auto end = chrono::steady_clock::now();
    double saTime = chrono::duration_cast<chrono::milliseconds>(end - start).count() / 1000.0;
    if (print) {
        r->first.print();
    }
    if (print) {
        r->second.print();
    }

    BestImprovement<RepNPP, MY_ADS> bi(ev, ns1);
    FirstImprovement<RepNPP, MY_ADS> fi(ev, ns1);

    auto sol = r->first;
    Evaluation e = ev.evaluate(sol.getR(), sol.getADSptr());

    vector<std::future<pair<CopySolution<RepNPP, MY_ADS> &, Evaluation &>>> futures;
    start = chrono::steady_clock::now();
    futures.push_back(std::async([&]() {
        HillClimbing<RepNPP, MY_ADS> sd1(ev, bi);
        return sd1.search(sol, e, sosc);
    }));

    futures.push_back(std::async([&]() {
        HillClimbing<RepNPP, MY_ADS> pm(ev, fi);
        return pm.search(sol, e, sosc);
    }));

    futures.push_back(std::async([&]() {
        RandomDescentMethod<RepNPP, MY_ADS> rdm(ev, ns1, 10);
        return rdm.search(sol, e, sosc);
    }));

    bool first = true;
    pair<CopySolution<RepNPP, MY_ADS> &, Evaluation &> best(r->first, r->second);
    for (auto &fut : futures) {
        auto value = fut.get();
        if (first) {
            best = value;
            first = false;
        } else if ((ev.isMinimization() && value.second.evaluation() < value.second.evaluation()) ||
                   (ev.isMaximization() && value.second.evaluation() > value.second.evaluation())) {
            best = value;
        }
        if (print) {
            value.second.print();
        }
    }
    end = chrono::steady_clock::now();

    double lsTime = chrono::duration_cast<chrono::milliseconds>(end - start).count() / 1000.0;
    return make_tuple(r->first, r->second, saTime, best.first, best.second, lsTime);
}
