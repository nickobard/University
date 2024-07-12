#include <cassert>
#include <iostream>
using namespace std;



int main (){
  // assert is not std, it is acutallu preprocessor macor
  assert(true);


  #ifndef NDEBUG
  // here is our debig code
  // use NDEBUG parameter while compiling to turn it off and turn off all assert
  // macros
  // __func__ is the local static - is global variable for the program
  cerr << __func__ << endl;
  cerr << __FILE__ << endl;
  cerr << __LINE__ << endl;
  cerr << __TIME__ << endl;
  cerr << __DATE__ << endl;

  #endif
  // while debugging will exit.
  // with NDEBUG won't proceed
  assert(false);

  return 0;
}