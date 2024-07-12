#include <iostream>
#include <vector>
using namespace std;

class Animal {
  public:
    virtual void sayHi() const = 0;
};

class Hog : public Animal {
  public:
    void sayHi() const override{
      cout << "Hog: Hi" << endl;
    }
};

class Cow : public Animal {
  public:
    void sayHi() const override{
      cout << "Cow: Hi" << endl;
    }
};


void sayHi( const Animal &a){
  a.sayHi();
}

int main () {
  Hog h;
  Cow c;

  sayHi(h);
  sayHi(c);
// vector which stores all those pointers... Interesting..
  vector<Animal *> vec;
  vec.push_back(&h);
  vec.push_back(&c);

  vec[0]->sayHi();
  vec[1]->sayHi();
  
  return 0;
}