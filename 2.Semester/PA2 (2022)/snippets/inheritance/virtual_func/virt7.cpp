#include <iostream>
#include <string>
using namespace std;

class Animal{
  public:
    virtual void sayHi (const string &msg = "Avada Kedavra!") const {
      cout << "Animal: Hi, " + msg << endl;
    }

};

class Hog : public Animal {
  public: 
  // Okey, we doesn't change default.
    void sayHi(const string &msg = "Run, Forest!") const override{
      cout << "Hog: Hi, " + msg << endl;
      // We can use that to call a version we do want to use actually.
      // But we should be careful, becase if we omit scope, it will be
      // infinite recursion to itself
      Animal::sayHi();
    }
};

void say(const Animal &a){
  a.sayHi();
  // using scope we can run particular version if needed.
  a.Animal::sayHi();
  // we can use that until it in the scope of the Animal - is its member.
  // Otherwise dynamic binding or error.

}

int main (){
  Hog h;
  // But it should use some parameter...
  h.sayHi(); // it used other default value... Interesting...
  // I suppose the problem will with dynamic bindings..
  // Here is virtual function of Hog, but default parameters are
  // of the Base class.. And always in dynamic binding are.
  say(h);
  return 0;
}