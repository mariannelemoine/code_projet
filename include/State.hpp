#ifndef STATE__H
#define STATE__H


#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>

using std::string;
using std::vector;
using std::ostream;
using std::endl;

class State{
  string name;
  vector<int> vec;
  
  void swap(State&);
  
  public:
  State();
  State(string,vector<int>);
  
  
  const string& getName() const ;
  const vector<int>& getVector() const ;
  
};

ostream& operator<<(ostream&, const State&);

#endif
