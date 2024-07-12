#include <iostream>
using namespace std;

using ptr = int *;

int main(){

  int x;
  // another way to use it. It is much more comprehensible. 
  // And easier to understand.
  ptr my_ptr = &x;
  
  return 0;
}