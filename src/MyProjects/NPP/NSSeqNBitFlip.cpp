#include <algorithm>
#include <vector>

#include "NSSeqNBitFlip.h"

using namespace std;
using namespace NPP;

// ============ MoveBitFlip ==============

template<unsigned int N>
bool MoveNBitFlip::canBeApplied(const RepNPP &rep, const MY_ADS *) {
    return true;
}

template<unsigned int N>
Move<RepNPP, MY_ADS> *MoveNBitFlip::apply(RepNPP &rep, MY_ADS *) {
    for (auto &x : this->item) {
        rep[x] = 1 - rep[x];
    }

    return new MoveNBitFlip(this->items);
}

template<unsigned int N>
MoveCost *MoveNBitFlip::cost(const Evaluation &, const RepNPP &rep, const MY_ADS *ads, bool mayEstimate) {
    return NULL;
    // Implement if a more efficient evaluation of the move is available
    //double move_cost = ...;
    //double move_cost_infeasible = ...;
    //return new MoveCost(move_cost, move_cost_infeasible);
}



// ============ NSIteratorBitFlip ==============

template<unsigned int N>
void NSIteratorNBitFlip::first() {
    this->items.clear();
    for (int i = 0; i < N; ++i) {
        this->items.insert(i);
    }
};

void NSIteratorBitFlip::next() {
    vector<int> values(this->items.begin(), this->items.end());
    sort(values.begin(), values.end());
};

bool NSIteratorBitFlip::isDone() {
    return item == N;
};

Move<RepNPP, MY_ADS> *NSIteratorBitFlip::current() {
    return new MoveBitFlip(item);
};




// ============ NSSeqBitFlip ==============


Move<RepNPP, MY_ADS> *NSSeqBitFlip::randomMove(const RepNPP &rep, const MY_ADS *) {
    return new MoveBitFlip(this->rg.rand(this->pNPP.getSize()));
}
