#include <iostream>
using namespace std;

class Animal {
  public:
    virtual void sayHi() const {
      cout << "Animal: Hi" << endl;
    }
    friend void say( const Animal &a ){
      a.sayHi();
    }
};

class Hog : Animal {
  public:
    void sayHi() const override{
      cout << "Hog: Hi" << endl;
    }
    void foo(){
      say(*this);
      // Again, dynamic binding is used here.
      //  Finally I have some concrete examples where it
      // is applied in with the not-public inheritance. Cool. I am happy.
      bar(*this);
    }
  private:
  // here bar is Hog:: function. Not Animal's.
  //  THe user is definitely a derived class
    void bar (const Animal &a){
      a.sayHi();
    }
    
};

int main (){
  Hog h;
  // cannot do that, we are ordinary user.
  // The class hog isn't itself user of that.
  // segmentation fault..
  // recursion is used... That why?
  // Understand now. SayHi() calls say, which by dynamic binding calls
  //  Hog::sayHi(), so it is a recursion...
  h.sayHi();
  // Here is used dynamic binding inside the Hog - conversion to Animal..
  // This is an example. But who uses it? Implementor or derived class?
  // Because we now used function of the base class to do that..
  h.foo();
  return 0;
}