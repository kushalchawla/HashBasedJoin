//for testing purposes
// reading the content of a text file.
#include <iostream>     // std::cout
#include <fstream>  
#include <cstring>
#include <string>   // std::ifstream

using namespace std;

int main () {
  
  std::ofstream ofs;
  	
  ofs.open ("files/ii.txt");

  if(ofs.is_open())
  {
  	cout<<"yes its open"<<endl;
  }
  else
  {
  	cout<<"not open"<<endl;
  }
  int val;
  
  ofs<<"hello"<<endl;
  ofs.close();
  
  return 0;
}