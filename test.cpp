//for testing purposes
// reading the content of a text file.
#include <iostream>     // std::cout
#include <fstream>  
#include <cstring>
#include <string>    // std::ifstream

using namespace std;

int main () {
  std::ifstream ifs;
  	string s=to_string(1);

  	char *a=new char[s.size()+1];
	a[s.size()]=0;
	memcpy(a,s.c_str(),s.size());
  char str[]="relation";
  strcat(str,a);
  strcat(str,".txt");
  ifs.open (str);
  
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