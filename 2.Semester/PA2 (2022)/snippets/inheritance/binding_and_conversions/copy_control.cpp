#include <iostream>
using namespace std;

class Animal {
  public:
    Animal() = default;
    // that actually may be not const
    // but recomended, so it can use unnamed construction inside
    // like Animal a({}); <- withou const is no possible
    Animal ( Animal &src){}
    // Copy constructor is just a function,
    // therefore while there is a reference, dynamic type is
    // used when is not same as static type
};

class Cow : public Animal {
  public:
    Cow () = default;
    Cow (const Cow &src){}
    // BUT!!! We can use another copy constructor!!
    // Specially for such situations!
    Cow (const Animal &src){}
};

int main (){
  Cow c;
  // here we use copy constructor, which takes reference
  Animal a(c);
  // because copy constructor doesn't have const param,
  // canno use that
  // Animal b({});
  //  there is no conversion from from Animal to Cow
  //  Same as no conversion from with pointers
  // Compiler in such cases looks only on the static types
  Cow c2(a);
  return 0;
}