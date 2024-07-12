#include <iostream>
using namespace std;

class Foo{
  public:
    Foo() = default;
    Foo(Foo); //invalid constructor. That will be infinite recursion
};

int main(){

  return 0;
}