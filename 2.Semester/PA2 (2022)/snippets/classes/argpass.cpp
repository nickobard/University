//classes/argpass.cpp
#include <iostream>
using namespace std;

struct C{
  C(){cout << "Object created." << endl;}
  C(const C&){ cout << "Copy constructor." << endl;}
};
void bar (C b){}

C foo(C b){
  return b;
}

int main(){
  C c;
  C b;
  c = b; // here no copy contructor is called,
  // it is just copied without construction
  // of the new element
  cout << "bar function:" << endl;
  bar(c); // here applies the copy constructor, but what about creation
  // of b parameter object?
  // Anyway, nothing is printed.
  cout << "foo function:" << endl;
  foo(c); // copy constructors were called
  // twice. First time passing argument,
  // second time returning and making
  // temporary on the call side
  cout << "foo function:" << endl;
  c = foo(c);// again, no construction was made, only copying.
  // But that doesn't mean, that the b object is not reserved.
  // It is reserved in the memory, but constructor wasn't called, 
  // instead the copy constructor was called.
  // But copy constructor was called both for constructing of b variable,
  // and was called to construct return value,
  // when only after that was assigned to the c 
  // struct variable. The return value probably
  // was stored in the registers, destroyed after
  // the assignment. But it is implementation 
  // defined behavior
  return 0;
}

// OUTPUT
/*
Object created.
Object created.
bar function:
Copy constructor.
foo function:
Copy constructor.
Copy constructor.
foo function:
Copy constructor.
Copy constructor. //also two. Does it mean that 
// c = foo(c); there was copy elision?
// becuase there was no third copy constructor...
*/