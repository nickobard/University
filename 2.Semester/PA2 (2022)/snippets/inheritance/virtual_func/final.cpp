#include <iostream>
using namespace std;

class Animal {
  public:
  // well, that is just useless, but we can do that.
    virtual void sayHi() const final {
      cout << "Animal: Hi" << endl;
    }
    virtual void sayHello() const {
      cout << "Animmal: Hello" << endl;
    }

};

class Beast : Animal {
  public:
  // well, final has some side effect.
  // It doesn't let us even todeclare our own, separaterd function..
  // Does there exist some keyword to round this problem??
    void sayHi() const {

    }
    // because this function doesn't match no base function,
    // it can be created easily.
    void sayHi(int) const {

    }
    void sayHello() const override final {
      // overridden, and last in the whole possible inheritance chain
    }
}


int main (){

  return 0;
}