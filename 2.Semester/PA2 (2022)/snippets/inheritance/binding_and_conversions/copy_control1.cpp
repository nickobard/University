#include <iostream>
using namespace std;

class Animal final {
  public:
    Animal() = default;
    // may not have type of the Animal - because dynamic binding may be
    // and what is interesting, compiler doesn't care about final keyword,
    // which means there cannot be derived class as the argument.
    Animal ( Animal src){} // error

};

int main (){
  // Cow c;
  // Animal a(c);
  return 0;
}