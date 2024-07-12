#include <iostream>
using namespace std;

class Foo {
  class Bar {
    public:
      int pub = 10;
    private:
      int priv = 10;
  };

  public:
    void printInfo() const;
    int pub = 5;
    Bar bar;
  private:
    int priv = 5;
  
};

void Foo::printInfo() const{
  cout << "pub: " << pub << endl;
  // here all private are inaccessble from the foo...
  // And from bar inaccessible just everything.
  cout << "bar: " << bar.pub <<  /* bar.priv << */ endl;

}


int main (){

  Foo a;
  cout << a.bar.pub << endl;
  return 0;
}