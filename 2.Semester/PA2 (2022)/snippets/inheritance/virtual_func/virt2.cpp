#include <iostream>
#include <string>
using namespace std;

class Animal {

  public:
    virtual void sayHi() const {
      cout << "Animal: Hi" << endl;
    }
};

class Cow : Animal {
  public: 
  /* // cannot override, because inherited sayHi() is private
    void sayHi() {
      cout << "Cow: public Hi" << endl;
    } */
  private:
    // sayHi should be private now
    // And still cannot override... I don't even know why..
    // Because virtual works only with public? Seems like so...
    void sayHi() {
      cout << "Cow: private Hi" << endl;
    }
};

class Horse : public Animal {
  public:
  // is that overriden or used by us from different scope?
  // Hmmm. Even that doesn't work. I miss something completely...
  // very interesting.. Why?
  
  // !!! BECAUSE FORGET TO USE CONST !!!
    void sayHi() override {
      cout << "Hello there" << endl;
    }
  private:

};

int main (){

  Horse h;
  // until we didn't change that 
  // virtual - until not explicitley overriden,
  // we use same version of the sayHi function
  h.sayHi();
  return 0;
}