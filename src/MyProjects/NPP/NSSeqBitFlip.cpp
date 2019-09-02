#include "NSSeqBitFlip.h"

using namespace NPP;

// ============ MoveBitFlip ==============

bool MoveBitFlip::canBeApplied(const RepNPP& rep, const MY_ADS*)
{
    return true;
}

Move< RepNPP , MY_ADS  >* MoveBitFlip::apply(RepNPP& rep, MY_ADS*)
{
    rep[item] = 1-rep[item];
    
    return new MoveBitFlip(item); 
}

MoveCost* MoveBitFlip::cost(const Evaluation&, const RepNPP& rep, const MY_ADS* ads, bool mayEstimate)
{
   return NULL;
   // Implement if a more efficient evaluation of the move is available
   //double move_cost = ...;
   //double move_cost_infeasible = ...;
   //return new MoveCost(move_cost, move_cost_infeasible);
}



// ============ NSIteratorBitFlip ==============

void NSIteratorBitFlip::first()
{
   item = 0;	
};

void NSIteratorBitFlip::next()
{
	item=item+1;
};
	
bool NSIteratorBitFlip::isDone()
{
	return item == N;
};
	
Move< RepNPP , MY_ADS  >* NSIteratorBitFlip::current()
{
	return new MoveBitFlip(item);
};




// ============ NSSeqBitFlip ==============


Move<RepNPP , MY_ADS >* NSSeqBitFlip::randomMove(const RepNPP& rep, const MY_ADS*)
{
   return new MoveBitFlip(this->rg.rand(this->pNPP.getSize()));
}
