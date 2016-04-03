//for testing purposes
// reading the content of a text file.
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
using namespace std;
int main () {
  std::ifstream ifs;

  ifs.open ("relation1.txt");
  if(ifs.is_open())
  {
  	cout<<"yes its open"<<endl;
  }
  else
  {
  	cout<<"not open"<<endl;
  }
  int val;
  while (ifs.good()) {
    ifs>>val;
    std::cout << val<<endl;
  }

  ifs.close();

  return 0;
}