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
};

int main () {

  shared_ptr<Animal> ptr (new Bear);
  ptr->sayHi();
  Bear b;
  shared_ptr<Animal> ptr2 = make_shared<Animal>(b);
  // the copy is used - b will be copied to the new Animal instance
  // se the Bear part will be sliced down.
  // We should directly provide our pointer to the bear.
  ptr2->sayHi();
  return 0;
}