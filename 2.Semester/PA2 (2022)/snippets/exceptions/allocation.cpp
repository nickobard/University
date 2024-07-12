#include <iostream>
using namespace std;

class myException : public exception {
  public:
    myException(const char * msg) { cout << msg << endl;}
};

class Foo {

  public:

    Foo() : num(new int (5)) { cout << "constructor" << endl;}
    ~Foo() { cout << "destructor" << endl; delete num; }

  private:
    int * num;    

};

int main () {

  Foo f;
  try {
    throw myException("My message!");
  }
  catch(const exception & e) {}

  return 0;
}