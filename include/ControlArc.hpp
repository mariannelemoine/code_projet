#ifndef CONTROLARC__H
#define CONTROLARC__H

#include "State.hpp"
#include <math.h>

class ControlArc{

  string place;  // the place which the arc is connected
  string reaction;  // the reaction in relation with the arc   
  bool inhibitor;  // true if the arc is an inhibitor-arc 
  // vector<PairSS> wpc; // wpcs that can be resolved by adding the arc to the network
  unsigned int weight;  // weight of the arc
  
  public :
  
  ControlArc(string p, string reac, bool inhib, unsigned int w) : place(p), reaction(reac), 
    inhibitor(inhib), weight(w){}
  ~ControlArc(){}
  
  const string & getPlace() const;
  const string & getReaction() const;
  const bool & isInhibitor() const;
  const unsigned int & getWeight() const;
  
  

};

//  Fonctor used for the set container
struct CompareControlArc{
  bool operator ()(const ControlArc & arc1, const ControlArc & arc2) const{
    return (arc1.getPlace() < arc2.getPlace() || arc1.getReaction() < arc2.getReaction() || arc1.isInhibitor() < arc2.isInhibitor() || arc1.getWeight() < arc2.getWeight());
  }
};

ostream& operator << (ostream&,const ControlArc&);

#endif
