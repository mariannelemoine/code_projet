#include "ControlArc.hpp"

const string & ControlArc::getPlace() const
{
  return place;
}
  
const string & ControlArc::getReaction() const
{
  return reaction;
}

const bool & ControlArc::isInhibitor() const
{
  return inhibitor;
}

const unsigned int & ControlArc::getWeight() const
{
  return weight;
}

ostream& operator << (ostream& o,const ControlArc& ca)
{
  string inh = (ca.isInhibitor() ? "inh" : "read");
  o << " " << ca.getPlace() << " " << ca.getReaction() << " " << inh << " " << ca.getWeight();  
  return o;
}
