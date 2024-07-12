#include <iostream>
using namespace std;

class Animal {
  public:
    virtual void sayHi() const {
      cout << "Animal: Hi" << endl;
    }

};

class Hog : public Animal {

  public:
    // override should be always at the end;
    // My question is - from which scope is this function?
    // Seems that it is from our scope..
    // override is implicit, becase in the base there exist accessible
    // same functions which is virtual.
    void sayHi () const /* override  */{
      cout << "Hog: Hi" << endl;
    }
// cannot overload with same parameters. So it can be only overloaded,
// the sayHi is from Hog scope, and we just say, use it in dynamic binding
// instead of Animal::sayHi version.
// Otherwise it behaves completely as ordinary function.
    /* void sayHi () const {
      cout << "Hello" << endl;
    } */
// cannot be overriden, beacuse no same function type in the base class.
    void sayHi (int i) const override { // error
      cout << "Hog: Hi, your number is " << i << endl;
    }


};

void say(const Animal &a){
  a.sayHi();
}

int main(){
  Animal a;
  Hog h;
  say(a);
  // is overriden, dynamic binding is applied. Override keyword is always implicit, but it is a good sign for programmers, that we want to override this function.
  // AND, most importantly, it is a good sign for the programmer,
  // which writes this function, because if he makes a mistake, he may not
  // notice it. Giving override let's a compiler TO CHECK, if it may be overriden or not. It is just safe. 
  // Otherwise it would be sufficient just to comment that this is overriden.
  say(h); // hog: hi
  
  return 0;
}