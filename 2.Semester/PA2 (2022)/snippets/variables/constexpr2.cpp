#include <iostream>
using namespace std;
constexpr int * foo(){
  constexpr int x = 25;
  // constexpr const int * ptr = &x;  // try to access run-time storage
  // that is that - not fixed address, that will be destroyed after
  // function wil return something. Therefore it is not valid.
  // static int x2 = 25; // even that doesn't work....
  // constexpr const int * ptr = &x2; // hmmm...
  return ;
}
int main (){

  int j = 0;
  // constexpr int cint = j; Not valid
  // constexpr int * ptr = &j; cannot do that 
  // constexpr const int &ptr2 = &j; againt, cannot do that, doesn't make sense
  static constexpr int i = 24; // only for static... 
  // even main is run-time storage
  constexpr const int * ptr = &i; 

  // everything above can work differently for static or globals


  // constexpr int * ptr = foo();  
  return 0;
}