//source functreturn.cpp
#include <iostream>
using namespace std;

void foo(){
  //void a; // cannot declare void variable
  //return a; // therefore it doesn't exists
}

int bar(){
  //return; // not valid, becuase it should have value in the return statement
  //return int; // not valid, because int doesn't represent value, it is just type specifier
  //return int a; // cannot combine variable declaration within the return statement
  int a = 1;
  return a == 1 ? 10 : 20 ;
}

int main (){
  cout << bar() << endl; // OUTPUT: 10
  return 0;
}