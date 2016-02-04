#include "Network.hpp"
#include "ControlArc.hpp"

#include <sstream>
#include <iterator>


using std::stringstream;
using std::ostream_iterator;
using std::ofstream;


void Network::init(string file){
  ifstream fic;
  fic.open(file.c_str());
  string line, dimension, size;
  stringstream sline;
  
  //Reading dimension
  getline(fic,line);
  sline.str(line);
  getline(sline,dimension,'=');
  cout << "Reading " << dimension << " ..." << endl;
  getline(sline,size);
  this->dim = atoi(size.c_str());
  cout << "Done" << endl;
  
  //Reading states
  cout << "Reading STATES ..." << endl;
  this->readStates(fic);
  cout << "Done" << endl;
  
  //Reading reactions
  getline(fic,line);
  cout << "Reading " << line << " ..." << endl;
  this->readReactions(fic);
  cout << "Done" << endl;
  
  //Reading sequences
  getline(fic,line);
  cout << "Reading " << line << " ..." << endl;
  this->readSequences(fic);
  cout << "Done" << endl;
  
  //Reading partitions
  getline(fic,line);
  cout << "Reading " << line << " ..." << endl;
  this->readPartitions(fic);
  cout << "Done " << endl;
  
  getline(fic,line);
  cout << line << endl;
  
  fic.close();
}

void Network::readStates(ifstream& fic){
  string line, p , u, nameset, name, capa;
  stringstream sline, snameset, scapa;
  
  //Reading state names
  getline(fic,line);
  sline.str(line);
  getline(sline,p,'=');
  getline(sline,nameset);
    //Remove curly brackets
  nameset.erase(0,1);
  nameset.erase(nameset.size() -1,1);
  
  snameset.str(nameset);
  for (int i = 0; i < dim; ++i)
  {
    getline(snameset,name,',');
    names.push_back(name);
  }
  
  //Reading state capacity
  getline(fic,line);
  sline.clear();
  sline.str(line);
  getline(sline,u,'=');
  getline(sline,capa);
    //Remove parenthesis
  capa.erase(0,1);
  capa.erase(capa.size() -1,1);
  
  scapa.str(capa);
  for (int i = 0; i < dim; ++i)
  {
    getline(scapa,capa,',');
    upper.push_back(atoi(capa.c_str()));
  }
  
  //READING STATES section
  getline(fic,line); //Remove empty line
  getline(fic,line);
  cout << "\t Reading " << line << " section ..." << endl;
  string st, id, sval; //state
  stringstream sst ; //state stream
  vector<int> vst; //State's vector
  int nb; //Vector's size
  
  
  getline(fic,line); //Read first state
  while(!line.empty())
  {
    sline.clear();
    sline.str(line);
    getline(sline,id,'='); //Extract state's id
    getline(sline,st); //Exact vector eg (1,1,2,0)
    st.erase(0,1); //Remove parenthesis
    st.erase(st.size()-1 , 1);
    
    sst.clear();
    sst.str(st);
    nb = count(st.begin(),st.end(),',') +1 ;
    for (int i = 0; i < nb; i++)
    {
      getline(sst,sval,',');
      vst.push_back(atoi(sval.c_str()));
    }
    State s(id,vst);
    states[id] = s;
    vst.clear();
    getline(fic,line);
  }
  
  
  //READING TERMINAL_STATES section
  getline(fic,line);
  cout << "\t Reading " << line << " section ..." << endl;
  getline(fic,line);
  while(!line.empty())
  {
    sline.clear();
    sline.str(line);
    getline(sline,id,'='); //Extract state's id
    getline(sline,st); //Exact vector eg (1,1,2,0)
    st.erase(0,1); //Remove parenthesis
    st.erase(st.size()-1 , 1);
    sst.clear();
    sst.str(st);
    
    for (int i = 0; i < nb; i++)
    {
      getline(sst,sval,',');
      vst.push_back(atoi(sval.c_str()));
    }
    State s(id,vst);
    terminal_states[id] = s;
    vst.clear();
    getline(fic,line);
  }
}

void Network::readReactions(ifstream& fic){
  string line;
  stringstream sline;
  
  //READING REACTIONS section
  string st, id, sval; //reaction
  stringstream sst ; //reaction stream
  vector<int> vst; //reaction's vector
  int nb; //Vector's size
  
  
  getline(fic,line);
  while(!line.empty())
  {
    sline.clear();
    sline.str(line);
    getline(sline,id,'='); //Extract state's id
    getline(sline,st); //Exact vector eg (1,1,2,0)
    
    st.erase(0,1); //Remove parenthesis
    st.erase(st.size()-1 , 1);
    
    sst.clear();
    sst.str(st);
    nb = count(st.begin(),st.end(),',') +1 ;
    
    for (int i = 0; i < nb; i++)
    {
      getline(sst,sval,',');
      vst.push_back(atoi(sval.c_str()));
    }
    reactions[id] = vst;
    vst.clear();
    getline(fic,line);
  }
}

void Network::readSequences(ifstream& fic){
  string line;
  stringstream sline;
  
  //READING SEQUENCES section
  string st, id, couple, sta, rea; //sequences
  stringstream sst, scouple ; //sequences stream
  vector<PairSR > vst; //sequences's vector
  int deb,fin;
  
  getline(fic,line);
  while(!line.empty())
  {
    sline.clear();
    sline.str(line);
    getline(sline,id,'='); //Extract state's id
    getline(sline,st); //Exact sequence eg (x1,r1),(x2,r2)...
    sst.clear();
    sst.str(st);
    
    while (!st.empty())
    {
      deb = st.find('(');
      fin = st.find(')');
      couple = st.substr(deb + 1,fin -1 ); //Exact pair without parenthesis
      scouple.clear();
      scouple.str(couple);
      
      getline(scouple,sta,',');
      getline(scouple,rea);
      st.erase(deb,fin+2);
      
      PairSR sr = make_pair(sta,rea);
      vst.push_back(sr);
    }
    sequences[id] = vst;
    vst.clear();
    getline(fic,line);
  }
}

void Network::readPartitions(ifstream& fic){
  string line;
  stringstream sline;
  
  //READING PARTITIONS section
  string st, id, sval; //partition
  stringstream sst ; //partition stream
  vector<string > vst; //partition's vector
  int nb; //Vector's size
  
  getline(fic,line);
  while(!line.empty())
  {
    sline.clear();
    sline.str(line);
    getline(sline,id,'='); //Extract state's id
    getline(sline,st); //Exact vector eg S1,S2,S3...
    
    sst.clear();
    sst.str(st);
    nb = count(st.begin(),st.end(),',') +1 ;
    
    for (int i = 0; i < nb; i++)
    {
      getline(sst,sval,',');
      vst.push_back(sval);
    }
    partitions[id] = vst;
    vst.clear();
    getline(fic,line);
  }
}


void Network::print(ostream& o) const{
  o << "Number of places : " << dim << endl;
  
  o << "\tPlaces : " << endl;
  vector<string>::const_iterator itn = names.begin();
  vector<string>::const_iterator nend = names.end();
  vector<int>::const_iterator itc = upper.begin();
  vector<int>::const_iterator cend = upper.end();
  
  while (itn != nend && itc != cend)
  {
    o << "Name : " << *itn << endl;
    o << "Maximum capacity : " << *itc << endl;
    ++itn ; ++itc;
  }
  
  
  
  o << "\n\tStates : " << endl;
  for (map<string,State>::const_iterator it = states.begin(); it != states.end() ; ++it)
  {
    o << "Id : " << it->first << endl;
    o << it->second;
  }
  o << "\n\tTerminal states : " << endl;
  for (map<string,State>::const_iterator it = terminal_states.begin(); it != terminal_states.end() ; ++it)
  {
    o << "Id : " << it->first << endl;
    o << it->second;
  }
  o << "\n\tReactions : " << endl;
  for (map<string,vector<int> >::const_iterator it = reactions.begin(); it != reactions.end() ; ++it)
  {
    o << "Id : " << it->first << endl;
    o << "Vector : (" ;
    for(unsigned i = 0; (i+1) < it->second.size(); ++i)
      o << it->second[i] << ",";
    
    o << it->second[it->second.size() -1] <<")" << endl;
  }
  o << "\n\tSequences : " << endl;
  for (map<string,vector<PairSR > >::const_iterator it = sequences.begin() ; it != sequences.end() ; ++it) {
    o << "Id : " << it->first << endl;
    o << "Sequence : " ;
    const vector<PairSR > v = it->second;
    for (vector<PairSR >::const_iterator it2 = v.begin() ; it2 != v.end() ; ++it2) {
      o << "(" << it2->first << "," << it2->second << ") ";
    }
    o << endl;
  } 
  o << "\n\tPartitions : " << endl;
  for(map<string,vector<string> >::const_iterator it = partitions.begin(); it != partitions.end(); ++it) {
    o << "Id : " << it->first << endl;
    o << "Partition : ";
    copy(it->second.begin(),it->second.end(),ostream_iterator<string>(cout," "));
    o << endl;
  }
}

ostream& operator<<(ostream& o ,const Network& net){
  net.print(o);
  return o;
}


string Network::findPartitions(string& seq){
  bool found = false; //Partitions not found
  string id; //Id's partition
  vector<string> vseq; //Vector of sequences
  vector<string>::iterator itvseq; //vector of partitions
  map<string,vector<string> >::iterator it = partitions.begin(); //
  while (it != partitions.end() && !found) {
    id = it->first; //
    vseq = it->second; //
    itvseq = find(vseq.begin(),vseq.end(),seq);
    if (itvseq != vseq.end()) //We found seq
    {
      found = true;
    }
    ++it;
  }
  return id;
}


void Network::findSequences() { //find all sequences that contains a terminal_state
  bool ts_found = false ; // true if we could a terminal state
  vector<PairSR > v;
  vector<PairSR >::iterator itv;
  vector<string> vpart;
  string st, id, q;
  map<string,State>::iterator its; //State iterator
  map<string,vector<string> >::iterator itp; //Partition iterator
  for(map<string,vector<PairSR > >::iterator it = sequences.begin() ; it != sequences.end() ; ++it){
    ts_found = false;
    id = it->first;
    v = it->second ; //Extracts the sequences' vector
    itv = v.begin();
    while (ts_found == false && itv != v.end()) {
      st = itv->first;
      its = terminal_states.find(st);
      if (its != terminal_states.end()) //We found a terminal state
      {
  ts_found = true ;
  //We need to add it in the tsequence container
  tsequences.push_back(id);
  /*We need to erase the sequence in the partition first
  q = this->findPartitions(id);
  itp = partitions.find(q);
  itp->second.erase(remove(itp->second.begin(),itp->second.end(),id),itp->second.end()) ;
  //Then we delete the sequence
  sequences.erase(it);*/
      }
      ++itv;
    } 
  }
}


void Network::findSPC(){
  vector< vector<PairSR > > vseq;
  vector<PairSR > vi, vj;
  vector<string> vid;
  string xi, xj, ri, rj, qi, qj;
  PairSS pss;
  unsigned ii, ij;
  bool found;
  
  for(map<string,vector<PairSR > >::const_iterator it = sequences.begin(); it != sequences.end() ; ++it)
  {
    vid.push_back(it->first); //Get the ID
    vseq.push_back(it->second); //Get the sequence
  }
  
  for( unsigned i = 0 ; (i+1) < vseq.size(); ++i) {
    vi = vseq[i];
    for( unsigned j = i+1 ; j < vseq.size() ; ++j) {
      vj = vseq[j];
      ii = 0;
      found = false;
      while(!found && ii < vi.size()){
  ij = 0;
  xi = vi[ii].first;
  ri = vi[ii].second;
  while(!found && ij < vj.size()){
    xj = vj[ij].first;
    rj = vj[ij].second;
    if (xi == xj && ri != rj) //SPC
    {
      found = true;
      qi = findPartitions(vid[i]);
      qj = findPartitions(vid[j]);
      if (qi != qj)
      {
        pss = make_pair(vid[i],vid[j]);
        spc.push_back(pss);
      }
    }
    ++ij;
  }
  ++ii;
      }
    }
  }
  
}



void Network::addFinalTerminal() {  // HAS to be done only ONE time
  for(map<string,vector<string> >::iterator it = partitions.begin(); it != partitions.end(); ++it) {
    const vector<PairSR> & vpsr = sequences[(it->second).front()];  // vector containing sequences of the partitions
    const PairSR & psr = *(vpsr.rbegin());  // last pair of state and reaction 
    
    const vector<int> & svec = isTerminal(psr.first)?terminal_states[psr.first].getVector():states[psr.first].getVector();  // vector of the state
    
    const vector<int> & rvec = reactions[psr.second];  // vector of the reaction
    
    
    vector<int> resvec;  // vector containing the result of the addition of the state vector and the reaction vector 
    
    // adding the state vector and reaction vector (it is equivalent to apply the reaction to the state
    std::transform(svec.begin(), svec.end(), rvec.begin(), std::back_inserter(resvec), std::plus<int>()); 
    
    bool not_found = true;  // says whether if there is a state vector with the same coordinates than the result vector
    
    // creates a map containing all the state vectors
    map<string, State > all_states(states);
    all_states.insert(terminal_states.begin(), terminal_states.end());
    
    map<string, State >::iterator jt = all_states.begin();  //iterates over the states
    do {
        const vector<int> & svec = (jt->second).getVector();  //state vector
        size_t i = 0;  
        bool all_found = true;  // says whether all the coordinates of the two vectors are equal
        do {
          all_found = (svec[i] == resvec[i]);  // test  if the coordinates of the two vectors are equal
          ++i;
        } while( all_found && (i < svec.size()));
        
        not_found = !all_found;  // if all the coordinates are the same, then the good state vector has been found
        ++jt;
    } while( not_found  && (jt != all_states.end()) );
    
    if(!not_found){  // if the state vector is found
      
      string id = ((--jt)->second).getName();  // get the name of the name of the state
      // Why not using (--jt)->first ?
      
      ++jt;
      PairSR ts = make_pair( id ,"TR" );  // make a pair with the name of the state and the terminal reaction 
      for(vector<string>::iterator sit = (it->second).begin(); sit != (it->second).end();++sit ) {  // add the pair at the end of each sequances of the partition
        sequences[it->first].push_back(ts);  
      }
    }
    
    // TODO : do something if there is no state vector found
    
  }
}



bool Network::testWPC(const string & xi, const string & xj, const string & ri, const string & rj){
  bool res = false;  // true if (xi, ri) and (xj, rj) are in WPC
  if((xi != xj) && (ri != rj)){  // a WPC is possible in this case 
    vector<int> vi, vj;  // state vectors  
    vector<int> ti = reactions[ri], tj = reactions[rj];  // transition vectors
    
    if(isTerminal(xi)){
      vi = terminal_states[xi].getVector();
    } else {
      vi = states[xi].getVector();
    }
    
    /* TODO : facto needed*/
    
    if(isTerminal(xj)){
      vj = terminal_states[xj].getVector(); // get the vector of xj
    } else {
      vj = states[xj].getVector(); // get the vector of xi
    }
    
    size_t nb_test = 0;

    for (size_t index = 0; index < vi.size(); ++index) {
        
        int sum1 = vi[index] + tj[index];// computes the sum of state vectors and the transition vectors at the place number index
        int sum2 = vj[index] + ti[index];
        
        if(sum1 >=0 && sum1 <= upper[index] && sum2 >=0 && sum2 <= upper[index]){  // check if the transitions are enabled for the place number index
            ++nb_test;
        }
    }
    
    if((nb_test == vi.size())){  // if the two transitions are enabled for all places in the two states, then (xi, ri) and (xj, rj) are in WPC
      res = true; 
    }
    
  }
  return res;
}

void Network::createControlArc(const string & xi, const string & xj, const string & ri, const string & rj)
{
  vector<int> diff1, diff2; // difference vector
  const vector<int> & vecti=(isTerminal(xi) ? terminal_states : states)[xi].getVector(); // transform the string into a vector xi 
  const vector<int> & vectj=(isTerminal(xj) ? terminal_states : states)[xj].getVector(); // transform the string into a vector xj
  unsigned int cpt=0;

 
  if(ri!="TR")
  {    
    transform(vecti.begin(), vecti.end(), vectj.begin(), std::back_inserter(diff1), std::minus <int>());//diff1=vecti-vectj
        
    for(vector<int>::iterator it = diff1.begin(); it != diff1.end(); ++it)
    {
    if(*it < 0)
        {
          cout<<"inhibiteur arc"<< " "<< xi << " "<< xj << " " << ri << " " << rj <<endl;
          ControlArc(names[cpt], ri, true, static_cast <unsigned int> (vecti[cpt])+1); // initializes an inhibitor-arc
          cout << " " << names[cpt] << " "<< ri << " " << static_cast <unsigned int> (vecti[cpt])+1 << endl; 
      } 
        else if(*it > 0) 
        {
          cout<< "read arc" << " "<< xi << " "<< xj << " " << ri << " " << rj <<endl;
          ControlArc(names[cpt], ri, false, static_cast <unsigned int> (vectj[cpt])+1); // initializes a read-arc
          cout << " " << names[cpt] << " "<< ri << " " << static_cast <unsigned int> (vectj[cpt])+1 << endl; 
    }
        ++cpt;
    }
  }
  
  cpt=0;
     
  if (rj!="TR")
  { 
    transform(vectj.begin(), vectj.end(), vecti.begin(), std::back_inserter(diff2), std::minus <int>());// diff2=vectj-vecti (xj-xi)

    for(vector<int>::iterator it = diff2.begin(); it != diff2.end(); ++it)
    {
    if(*it < 0)
        {
          cout<<"inhibiteur arc"<< " "<< xi << " "<< xj << " " << ri << " " << rj <<endl;
          ControlArc(names[cpt], rj, true, static_cast <unsigned int> (vectj[cpt])+1); // initializes an inhibitor-arc
      cout << " " << names[cpt] << " "<< rj << " " << static_cast <unsigned int> (vecti[cpt])-1 << endl;
        }
        
        else if(*it > 0)
        {
          cout<< "read arc" << " "<< xi << " "<< xj << " " << ri << " " << rj <<endl;
          ControlArc(names[cpt], rj, false, static_cast <unsigned int> (vecti[cpt])+1); // initializes a read-arc
          cout << " " << names[cpt] << " "<< rj << " " << static_cast <unsigned int> (vecti[cpt])+1 << endl; 
        }
        ++cpt;
    }
  }
}

void Network::findWPC(){
  vector< vector<PairSR > > vseq;
  vector<PairSR > vi, vj;
  vector<string> vid;
  string xi, xj, ri, rj, qi, qj, s1, s2;
  PairSS pss;
  unsigned ii, ij;
  bool found;
  addFinalTerminal();
  for(map<string,vector<PairSR > >::const_iterator it = sequences.begin(); it != sequences.end() ; ++it)
  {
    string id = it->first;
    vid.push_back(id); //Get the ID
    vseq.push_back(it->second); //Get the sequence
    
  }
  
  for( unsigned i = 0 ; (i+1) < vseq.size(); ++i) {
    vi = vseq[i];
    for( unsigned j = i+1 ; j < vseq.size() ; ++j) {
      vj = vseq[j];
      ii = 0;
      found = false;
      while(!found && ii < vi.size()){
        ij = 0;
        xi = vi[ii].first;
        ri = vi[ii].second;
        while(!found && ij < vj.size()){
          xj = vj[ij].first;
          rj = vj[ij].second;

    
          if (testWPC(xi, xj, ri, rj)) //WPC
          {
            createControlArc(xi, xj, ri, rj);
          }
          ++ij;
        }
        ++ii;
      }
    }
  }
  
}

void Network::printSPC(ostream& o) const{
  
  o << "List of SPC pairs : " << endl;
  for(vector<PairSS >::const_iterator it = spc.begin(); it != spc.end(); ++it){
    o << "(" << it->first << "," << it->second << ") ";
  }
  o<< endl;
}

void Network::printTS(ostream& o) const {
  o << "List of sequences that contains a terminal state" << endl ;
  copy(tsequences.begin(),tsequences.end(),ostream_iterator<string>(o,"\n"));
}


string stox(string s){
  assert(!s.empty());
  s[0] = 'x';
  return s;
}

void Network::writePorta(string file) const{
  size_t n = sequences.size();
  ofstream fic;
  fic.open(file.c_str());
  
  fic <<"DIM = "<< n << endl << endl;
  
  fic <<"LOWER_BOUNDS" << endl;
  vector<int> zeros(n,0);
  copy(zeros.begin(),zeros.end(),ostream_iterator<int>(fic," "));
  
  fic << endl << endl << "UPPER_BOUNDS" << endl;
  vector<int> ones(n,1);
  copy(ones.begin(),ones.end(),ostream_iterator<int>(fic," "));
  
  fic << endl << endl << "INEQUALITIES_SECTION" << endl << endl;
  
  //partitions
  vector<string> seq;
  vector<string> var; //Contains xi instead of si
  for(map<string,vector<string> >::const_iterator it = partitions.begin() ; it != partitions.end() ; ++it){
    seq = it->second;
    var.clear();
    transform(seq.begin(),seq.end(),back_inserter(var),stox);
    copy(var.begin(),var.end() - 1 ,ostream_iterator<string>(fic," + "));
    fic << var.back() << " = 1" << endl;
  }
  
  fic << endl;
  
  //sequences that contains a terminal_state
  var.clear();
  transform(tsequences.begin(),tsequences.end(),back_inserter(var),stox);
  copy(var.begin(),var.end(),ostream_iterator<string>(fic," = 0\n"));
  
  //SPC
  string xi, xj;
  for(vector<PairSS >::const_iterator it = spc.begin() ; it != spc.end() ; ++it){
    xi = stox(it->first);
    xj = stox(it->second);
    fic << xi << " + " << xj << " <= 1" << endl; 
  }
  
  fic << endl << "END" ;
  
  fic.close();
}
