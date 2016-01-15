#include "State.hpp"

State::State(){}
State::State(string n,vector<int> v):name(n),vec(v){}

const string& State::getName() const {
  return name;
}


const vector<int>& State::getVector() const {
  return vec;
}


/*void State::swap(State& s){
  std::swap(this->name,s.name);
  std::swap(this->vec,s.vec);
}

State& operator=(State s){
  s.swap(*this);
  return *this;
}*/


ostream& operator<<(ostream& o , const State& s ){
  o << "Name : " << s.getName() << endl;
  o << "Vector : (" ;
  const vector<int> v = s.getVector();
  for(unsigned i = 0; (i+1) < v.size(); ++i)
    o << v[i] << ",";
    
  o << v[v.size() -1] <<")" << endl;
  
  return o;
}
