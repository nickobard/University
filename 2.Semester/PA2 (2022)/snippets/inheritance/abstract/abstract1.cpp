#include <iostream>
using namespace std;

class Animal {
  public:
  // from this moment Animal is abstract class,
  // and sayHi is pure virtual function
    virtual void sayHi() = 0;
    // cannot define sayHi() here. Impossible
  private:
    virtual void sayHello();

};
// But outside can be defined. In the example when we won't override that.
void Animal::sayHi() {
  cout << "Animal: Hi" << endl;
}

void Animal::sayHello(){
  cout << "Animal: Hello" << endl;
}

class Hog : public Animal {
  public:
    void sayHi() override{
      cout << "Hog: Hi" << endl;
    }
    void sayHello (){
      cout << "Hog: Say Hello" << endl;
    }
};

class Cow : Animal {
  public: 
    void sayHi(){

    }
    // can override even if it is inaccessible. Good.
    void sayHello(){
      
    }
};

int main (){
  // if we do not override the sayHi, we cannot use that class and
  // instantiate an object of that.
  Hog h;
  // We should override that, Or we canot use that.
  h.sayHi();
  // But we can use after that this functon. After we have overridden 
  // the pure virtual
  h.Animal::sayHi(); 
  return 0;
}