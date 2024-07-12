#include <iostream>
using namespace std;

constexpr int foo(int x){
  return x;
}

constexpr int bar ( int x){
  return x;
}

int base (){
  return 25;
}

int main (){
  int x = 52;
  // this is no valid, because x is not constant
  // constexpr int cint = x;

  // that works, because foo is constexpression. 
  // Does it meant that it will be evaluated while the compile time?
  constexpr int cint = foo(25); 
  // Very interesting... But that means, that foo() cannot call other
  // functions, that are not constexpression. Yeap, surely it cannot.
  // But can it take argumenst that are functions???

  // constexpr int cint2 = bar(base()); // it cannot even
  // call that functions, because it is not constexppresion
  // There is a ADL - argument dependent lookup.
  // So the type of the arguments should be constexpression to.
  // otherwise cannot compile

  // cint = 25; // also bad, trivially cannot change const.
  // constexpr int cint3 = foo(x);
  // Again, the ADL is used, x is not constexpression, so cannot do that.

  

  return 0;
}