#pragma once
#ifndef NPP_NSSEQNBitFlip_H_
#define NPP_NSSEQNBitFlip_H_

#include <unordered_set>

// Framework includes
#include "../../OptFrame/NSSeq.hpp"
#include "../../OptFrame/RandGen.hpp"

// Own includes
#include "ProblemInstance.h"
#include "Representation.h"

using namespace std;

namespace NPP {

    template<unsigned int N>
    class MoveNBitFlip : public Move<RepNPP, MY_ADS> {
    private:
        unordered_set<int> items;

    public:
        MoveNBitFlip() {
            for (int i = 0; i < N; ++i) {
                this->items.insert(i);
            }
        }

        MoveNBitFlip(vector<int> _items) {
            this->items.insert(_items.begin(), _items.end());
        }

        MoveNBitFlip(unordered_set<int> _items) : items(_items) {
        }

        virtual ~MoveNBitFlip() {
        }

        void print() const {
            cout << id() << " with params: '" << "items=" << items << "'" << endl;
        }

        string id() const {
            return Move<RepNPP, MY_ADS>::idComponent().append(":MoveNBitFlip");
        }

        bool operator==(const Move<RepNPP, MY_ADS> &_m) const {
            const MoveNBitFlip &m = (const MoveBitFlip &) _m;
            if (this->items.size() != m.items.size()) {
                return false;
            }
            for (auto &x : this->items) {
                if (!m.items.contains(x)) {
                    return false;
                }
            }
            return true;
        }

        // Implement these methods in the .cpp file

        bool canBeApplied(const RepNPP &rep, const MY_ADS *) override;

        Move<RepNPP, MY_ADS> *apply(RepNPP &rep, MY_ADS *) override;

        MoveCost *cost(const Evaluation &, const RepNPP &rep, const MY_ADS *ads, bool mayEstimate) override;
    };

    template<unsigned int N>
    class NSIteratorNBitFlip : public NSIterator<RepNPP, MY_ADS> {
    private:
        unordered_set<int> items;
        int size;

    public:
        NSIteratorNBitFlip(int _size) : size(_size) {
        }

        virtual ~NSIteratorNBitFlip() {
        }

        // Implement these methods in the .cpp file

        void first() override;

        void next() override;

        bool isDone() override;

        Move<RepNPP, MY_ADS> *current() override;
    };

    template<unsigned int N>
    class NSSeqNBitFlip : public NSSeq<RepNPP, MY_ADS> {
    private:
        // YOU MAY REMOVE THESE PARAMETERS IF YOU DON'T NEED (BUT PROBABLY WILL...)
        ProblemInstance &pNPP; // problem instance data
        RandGen &rg;          // random number generator

    public:
        // YOU MAY REMOVE THESE PARAMETERS IF YOU DON'T NEED (BUT PROBABLY WILL...)
        NSSeqNBitFlip(ProblemInstance &_pNPP, RandGen &_rg)
                : pNPP(_pNPP), rg(_rg) {
        }

        virtual ~NSSeqNBitFlip() {
        }

        void print() const {
            cout << "NSSeqNBitFlip" << endl;
        }

        string id() const {
            return NSSeq<RepNPP, MY_ADS>::idComponent().append(":NSSeqNBitFlip");
        }

        NSIterator<RepNPP, MY_ADS> *getIterator(const RepNPP &rep, const MY_ADS *) override {
            // return an iterator to the neighbors of 'rep'
            return new NSIteratorNBitFlip(this->pNPP.getSize());
        }

        // Implement this method in the .cpp file

        Move<RepNPP, MY_ADS> *randomMove(const RepNPP &rep, const MY_ADS *) override;
    };
}

#endif /*NPP_NSSEQNBitFlip_H_*/
