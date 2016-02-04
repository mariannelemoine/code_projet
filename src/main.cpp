#include "Network.hpp"

using std::cerr;
using std::stringstream;

int main(int argc,char** argv){
  if (argc <= 1 || argc > 2)
  {
    std::cerr << "Please enter exactly one filename" << std::endl;
  }else
  {
    Network n;
    std::string file(argv[1]), name;
    std::stringstream sfile(file);
    std::getline(sfile,name,'.');
    name = name + ".ieq" ;
    
    n.init(argv[1]);
    n.findSequences();
    n.findSPC();
    n.findWPC();
    n.printControlArcs();
    n.writePorta(name);
    
  }
  
  return 0;
}
