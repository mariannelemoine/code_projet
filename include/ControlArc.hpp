#ifndef CONTROLARC__H
#define CONTROLARC__H

#include "State.hpp"
#include "Network.hpp"

class ControlArc{

	string place;  // the place which the arc is connected
	string reaction;  // the reaction in relation with the arc   
	bool inhibitor;  // true if the arc is an inhibitor-arc 
	vector<PairSS> wpc; // wpcs that can be resolved by adding the arc to the network
	unsigned int weight;  // weight of the arc
	
  public:
  
  ControlArc(){}
  ControlArc(string p, string reac, bool ini, unsigned int w): place(p), reaction(reac), inhibitor(ini), weight(w){}
  
  const string & getPlace(); // get the place
  const string & getReaction(); // get the reaction
  const bool & isInhibitor(); // get the inhibitor
  const unsigned int & getWeight(); // get the weight of the arc
};

#endif
