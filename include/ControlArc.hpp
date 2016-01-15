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
	
  public :

  
	

};



#endif
