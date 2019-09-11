#pragma once
#ifndef NPP_NSSEQBitFlip_H_
#define NPP_NSSEQBitFlip_H_

// Framework includes
#include "OptFrame/NSSeq.hpp"
#include "OptFrame/RandGen.hpp"

// Own includes
#include "ProblemInstance.h"
#include "Representation.h"

using namespace std;

namespace NPP {

class MoveBitFlip : public Move<RepNPP, MY_ADS>
{
private:
   int item;

public:
   MoveBitFlip(int _item)
     : item(_item)
   {
   }

   virtual ~MoveBitFlip()
   {
   }

   void print() const
   {
      cout << id() << " with params: '" << "item=" << item << "'" << endl;
   }

   string id() const
   {
      return Move<RepNPP, MY_ADS>::idComponent().append(":MoveBitFlip");
   }

   bool operator==(const Move<RepNPP, MY_ADS>& _m) const
   {
      const MoveBitFlip& m = (const MoveBitFlip&)_m;
      return item == m.item;
   }

   // Implement these methods in the .cpp file

   bool canBeApplied(const RepNPP& rep, const MY_ADS*) override;

   Move<RepNPP, MY_ADS>* apply(RepNPP& rep, MY_ADS*) override;

   MoveCost* cost(const Evaluation&, const RepNPP& rep, const MY_ADS* ads, bool mayEstimate) override;
};

class NSIteratorBitFlip : public NSIterator<RepNPP, MY_ADS>
{
private:
   int N, item;

public:
   NSIteratorBitFlip(int _N)
     : N(_N)
   {
   }

   virtual ~NSIteratorBitFlip()
   {
   }

   // Implement these methods in the .cpp file

   void first() override;
   void next() override;
   bool isDone() override;
   Move<RepNPP, MY_ADS>* current() override;
};

class NSSeqBitFlip : public NSSeq<RepNPP, MY_ADS>
{
private:
   // YOU MAY REMOVE THESE PARAMETERS IF YOU DON'T NEED (BUT PROBABLY WILL...)
   ProblemInstance& pNPP; // problem instance data
   RandGen& rg;          // random number generator

public:
   // YOU MAY REMOVE THESE PARAMETERS IF YOU DON'T NEED (BUT PROBABLY WILL...)
   NSSeqBitFlip(ProblemInstance& _pNPP, RandGen& _rg)
     : pNPP(_pNPP)
     , rg(_rg)
   {
   }

   virtual ~NSSeqBitFlip()
   {
   }

   void print() const
   {
      cout << "NSSeqBitFlip" << endl;
   }

   string id() const
   {
      return NSSeq<RepNPP, MY_ADS>::idComponent().append(":NSSeqBitFlip");
   }

   NSIterator<RepNPP, MY_ADS>* getIterator(const RepNPP& rep, const MY_ADS*) override
   {
      // return an iterator to the neighbors of 'rep'
      return new NSIteratorBitFlip(this->pNPP.getSize());
   }

   // Implement this method in the .cpp file

   Move<RepNPP, MY_ADS>* randomMove(const RepNPP& rep, const MY_ADS*) override;
};
}

#endif /*NPP_NSSEQBitFlip_H_*/
