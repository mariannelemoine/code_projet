#include "ControlArc.hpp"

const string & ControlArc::getPlace()
{
	return place;
}
  
const string & ControlArc::getReaction()
{
	return reaction;
}

const bool & ControlArc::isInhibitor()
{
	return inhibitor;
}

const unsigned int & ControlArc::getWeight()
{
	return weight;
}
