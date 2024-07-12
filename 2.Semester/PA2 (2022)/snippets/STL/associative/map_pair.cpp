#include <iostream>
#include <string>
#include <map>
using namespace std;

int main(){

  map<string, int> my_mega_map;
  // using key_type we can access need key type,
  // but I really don't know why to use that.
  // Just interesting
  map<string, int>::key_type str;
  
  str = "Hiya!";
  cout << str << endl;


  return 0;
}

