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
    // you can ignore parameter 'ads'
    // 'rep' is the representation of the solution
    double fo = 0; // Evaluation Function Value
    for (int i = 0; i < pNPP.getSize(); ++i) {
        fo += rep[i] ? this->pNPP[i] : -this->pNPP[i];
    }

    PRINT(rep);
    return Evaluation(fabs(fo));
}


bool MyEvaluator::isMinimization() const
{
	// MINIMIZATION
	return true;
}
