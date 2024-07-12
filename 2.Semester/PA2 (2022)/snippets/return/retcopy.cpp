//return/retcopy.cpp
#include <iostream>
using namespace std;

int *bar2(int *a){
  return a;
}

int &bar(int &a){
  return a;
}

int foo (){
  return 10 + 15;
}

int main (){
  int c = 25 + foo(); // here the foo() should be temporary object,
  // so it is a copy of the returned value, that can be
  // manipulated.
  cout << c << endl; // 50

  bar(c) = 15; // reference return type is an lvalue, so we can
  // assign to it some value.
  cout << c << endl; // 15

  *bar2(&c) = 30; // this is analogous to the reference, but 
  // pointers are used instead. Here the *bar2(...) = 30 is like c = 30
  // so that also behave as lvalue.
  cout << c << endl; // 30


  //return 0 this is mandatory. Implicitely there is return 0;
}