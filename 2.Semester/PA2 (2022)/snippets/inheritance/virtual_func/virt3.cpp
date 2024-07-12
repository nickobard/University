#include <iostream>
#include <string>
using namespace std;

class Animal {

  public:
    virtual void sayHi() const {
      cout << "Animal: Hi" << endl;
    }
    virtual void sayHello() const {
      cout << "Animal: Hello" << endl;
    }
    virtual void doNothing() const{

    }
};

class Cow : Animal {
  public: 
    void sayHi() const override{
      cout << "Cow: Hi" << endl;
    }
    void say() const {
      // using Animal sayHi()
      cout << "\n" << __func__ << endl;
      Animal::sayHi();
      Animal::sayHello();
      sayHello();
    }
  private:
    // inherited sayHi and sayHello hase private access modifier
    void sayHello() const override{
      cout << "Cow: Hello" << endl;
    }

};

class Horse : public Animal {
  public:
    void myDoNothing() const; // OK, declared, but not used. Is not virtual
    // should be defined if declared
    // virtual void doNothing() const override;
    virtual void sayHi() const override{
      cout << "Horse: Hi" << endl;
    }
  private:
    virtual void sayHello( ) const override{
      cout << "Horse: Hello" << endl;
    }

};


void say(const Animal &anim){
  cout << "\n" << __func__ << endl;
  anim.sayHi();
  anim.sayHello();
}

int main (){
  Cow c;
  c.sayHi(); // cow
  c.say();  // animal
  cout << "\nHorse: " << endl;
  Horse h;
  // until we didn't change that 
  // virtual - until not explicitley overriden,
  // we use same version of the sayHi function
  h.sayHi();
  say(h);
  // overriden sayHello is inaccessible. Though it overrides.
  // and is taken with priority... Interesting... Because we have
  // it our own defined. It prefers always its own scope. 
  // If not found, goes to the parent scope find there.
  // h.sayHello();
  // Very very interesting. So override doesn't change the subobject part of base class
  // Instread, we declare our own overriden, which is speciall for dynamic binding
  h.Animal::sayHello(); // Animal

  Animal a2 (c);
  return 0;
}