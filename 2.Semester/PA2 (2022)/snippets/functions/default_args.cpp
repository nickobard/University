#include <iostream>
using namespace std;

class Base {
  public:
  int foo(int i, int b = 10) const;
};
/**
 * It is very interesting, that we can add new default
 * paramters in the same namescope..
 */
int Base::foo(int i = 15, int b) const{
  return i * b;
}
// int bar (int i = 10, int b ); // cannot leave trailing nondefaulted
// parameters
int bar (int i, int b ){
  return i * b; // OK, definition is separated from declaration.
}
int bar (int i, int b = 31);
int bar (int i, int b );
int bar (int i, int b );
int bar (int i, int b );
int bar (int i, int b );
int bar (int i, int b );
int bar (int i = 25, int b ); // ok, add new defaulted 
int bar (int i, int b );
int bar (int i, int b );

// int bar (int i, int b = 31); // error, cannot redeclare with default parameters
// int bar (int i, int b = 325); // error - redefinition fo the declaration.
// at this moment, in this global scope, we have bar with two defaulted

int main (){
  Base a;
  cout << a.foo() << endl;
  cout << bar() << endl; // OK
  return 0;
}