#include <iostream>
using namespace std;
// Here i want to check, whick access elements we can override, and wcich not.

class Animal {
  public:
    void anotherSay( const Animal &a) const {
      a.sayHi();
      a.sayHello();
    }
    virtual void sayHi() const {
      cout << "Animal: Hi" << endl;
    }
    
  private:
    virtual void sayHello() const {
      cout << "Animal: Hello" << endl;
    }
};

class Hog : Animal{
  // sayHi is private here
  public:
  // but anyway you do want to converse hog to animal...
  // That is impossible due to the access level...
  // But really don't understand how to use virtual for private?
  // And why at all use them for private, if I cannot use dynamic binding
  // with private? Seems really useless.
    void selfSay (const Hog &h) const{
      anotherSay(h);
    }
    void say (const Animal &a) const {
      a.sayHi();
      // again, not at least here..
      // a.sayHello();
    }
    void sayHi() const override{
      cout << "Hog: Hi, I am private." << endl;
    }
    // wow. If if is inaccessible, we can make it... Awesome..
    void sayHello() const override{
      cout << "Hog: Hello, I am private." << endl;
    }
};
class Horse : protected Animal{
  public:
    void sayHi() const override{
      cout << "Horse: Hi, I am protected." << endl;
    }

};
class Cow : public Animal {
  public:
    void sayHi() const override{
      cout << "Cow: Hi, I am public" << endl;
    }

};

void say (const Animal &a){
  a.sayHi();
  // is private. So even if we will change that, we just cannot use that..
  // except it is a friend... Or static? Our just a method we don't overload
  // a.sayHello();
}

int main () {
  Animal a;

  Hog h1;
  // say(h1); // private is not convertible
  Horse h2;
  // say(h2); // protected is not convertible
  Cow c;
  say(c);

  h1.say(a); // OK
  // cannot converse - not public... Hmm...
  // h1.say(h1);
  cout << "----------------------------------" << endl;

  // h1.selfSay();

  
  return 0;
}