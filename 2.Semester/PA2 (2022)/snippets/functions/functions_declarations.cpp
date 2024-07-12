//functions/functions_declarations.cpp
#include <iostream>
using namespace std;
// we can make multiple declarations,
// even using same functions.
void foo (int, int);
void foo (int, int);
void foo (int, int);
void foo (int, int);
void foo (int, int);
void foo (int, int);
// but definition can be only one
// and it should not differ.
int main(){
  return 0;
}