#include <iostream>
using namespace std;

void func (){
  cout << "Hi" << endl;
}


class Base{
  public:
    void bar(){
      cout << "Hello!" << endl;
    }
    // canot use on nonstatic functions..
    // decltype(bar)) f = bar;
  
    // void (Base::*g)() = bar;

    static void foo(){
      cout << "Hiya!" << endl;
    }

    // decltype(foo) func = foo; also cannot use that.

};

int main () {
  // wow, auto can create pointer to the function! Awesome!
  auto f = func; 
  f(); // output: Hi
  f = 0; // now points to 0
  // f(); // segmentation fault - tried to jump to null address
  // for functon call
  Base b;
  // b.f;
  // b.g;

  return 0;
}