#include "Evaluator.h"

using namespace NPP;

MyEvaluator::MyEvaluator(ProblemInstance& _pNPP): // If necessary, add more parameters
pNPP(_pNPP)
{
	// Put the rest of your code here
}
	
MyEvaluator::~MyEvaluator()
{
}

Evaluation MyEvaluator::evaluate(const RepNPP& rep, const OptFrameADS* ads)
{
    return std::get<0>(this->evaluateAndPosition(rep, ads));
}

std::tuple<Evaluation, int> MyEvaluator::evaluateAndPosition(const RepNPP& rep, const OptFrameADS* ads)
{
    // you can ignore parameter 'ads'
    // 'rep' is the representation of the solution

    double fo = 0; // Evaluation Function Value
    for (int i = 0; i < pNPP.getSize(); ++i) {
        fo += pNPP[i];
    }
    int selected = 0;
    for (int i = 0; i < pNPP.getSize(); ++i) {
        int indo, vindo;
        indo = vindo = 0;
        for (int j = 0; j < pNPP.getSize(); ++j) {
            if (j < i) {
                indo += rep[j];
            } else {
                vindo += rep[j];
            }
        }
        if (abs(indo - vindo) < fo) {
            fo = abs(indo - vindo);
            selected = i;
        }
    }

    PRINT(rep);
    return std::make_tuple(Evaluation(fo), selected);
}


bool MyEvaluator::isMinimization() const
{
	// MINIMIZATION
	return true;
}
