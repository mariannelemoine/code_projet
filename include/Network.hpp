#ifndef NETWORK__H
#define NETWORK__H

#include "State.hpp"
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <utility>
#include <map>
#include <queue>
#include <cassert>
#include <set>


using std::ifstream;
using std::ostream;
using std::string;
using std::cout;
using std::map;
using std::pair;
using std::set;


typedef pair<string,string> PairSR; //Pair (state,reaction)
typedef pair<string,string> PairSS; //Pair (sequence,sequence)

/* foward declarations */
class ControlArc;
struct CompareControlArc;

class Network{
  int dim; //Number of places
  map<string,State> states; //Contains each state with its id_string (eg X1)
  vector<string> names; //Name of places
  vector<int> upper; //max token capacity
  map<string,State> terminal_states; //Contains terminal_states
  map<string,vector<int> > reactions; // Contains reactions
  map<string,vector<PairSR > > sequences;
  map<string,vector<string> > partitions;
  vector<PairSS > spc; //Vector of sequences that are in SPC
  vector<string> tsequences; //Sequences' id that contains a terminal_state
  set<ControlArc, CompareControlArc> control_arcs;  // contain all the control arcs // BUG
  
  
  void readStates(ifstream&); //Reads STATES and TERMINAL_STATES
  void readReactions(ifstream&); //Reads REACTIONS section
  void readSequences(ifstream&); //Reads SEQUENCES section
  void readPartitions(ifstream&); //Reads PARTITIONS section
  string findPartitions(string&); //Finds PARTITIONS
  bool testWPC(const string & xi, const string & xj, const string & ri, const string & rj) ;  // Test if the couple of pairs states and transitions are in a WPC
  bool isTerminal(const string & xi) {return terminal_states.find(xi) != terminal_states.end(); }  // Test whether a state is terminal
  void addFinalTerminal() ;  // Add the final state in the sequences if it is terminal
  void createControlArc(const string & xi, const string & xj, const string & ri, const string & rj); //create a control arc between xi and xj
  
  public:
  void removeSequences() ; //Remove all sequences that contains a terminal state
  void print(ostream& o = cout) const;
  void printSPC(ostream& o = cout) const;
  void printTS(ostream& o = cout) const ;
  void init(string); //Initializes the network from an input file
  void findSequences() ; //Remove all sequences that contains a terminal_state
  void findSPC() ; //Create the vector of sequences that are in SPC
  void findWPC() ; // Create the vector of s   that are in WPC
  void writePorta(string) const;
  
};

ostream& operator<<(ostream&,const Network&);
string stox(string);
#endif
