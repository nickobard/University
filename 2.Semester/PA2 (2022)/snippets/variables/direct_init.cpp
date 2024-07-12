//projects/variables/direct_init.cpp
#include <iostream>
using namespace std;

int main(){
  int a (10);
  //a (20); ERROR, this is ambigious with function call.
  // direct initialization is only for initialization
  return 0;
}