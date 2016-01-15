#include "Network.hpp"

int main(int argc,char** argv){
  if (argc <= 1 || argc > 2)
  {
    cerr << "Please enter exactly one filename" << endl;
  }else
  {
    Network n;
    string file(argv[1]), name;
    stringstream sfile(file);
    getline(sfile,name,'.');
    name = name + ".ieq" ;
    
    n.init(argv[1]);
    n.findSequences();
    n.findSPC();
    n.findWPC();
    n.writePorta(name);
    
  }
  
  return 0;
}
