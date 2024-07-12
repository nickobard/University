#include <iostream>
#include <memory>
using namespace std;

class Animal {
  public:
    virtual void sayHi() const {
      cout << "Animal: Say Hi" << endl;
    }
};

class Bear : public Animal {
  public:
    void sayHi() const override {
      cout << "Bear: Say Hi" << endl;
    }
    void say( const Animal &a){
      shared_ptr<Animal> ptr (new Animal (a));
      ptr->sayHi();
    }
};

int main (){

  Animal a;
  Bear b;
  b.say(a);
  Bear b2;
  // Output will be Animal:
  // Because we put our b2 there, dynamic binding is enabled
  // but it is then sliced down when creating new Animal object.
  // From that moment we don't have our Bear object.
  // The only way is to use virtual clone, which will do allocation operation as expected
  b.say(b2);

  return 0;
}