#include <iostream>
#include <string>
using namespace std;

class Animal{
  public:
    Animal (string name) : m_Name (name) {}
    void sayYourName( const Animal &animal){
      cout << animal.m_Name << endl;
    }
  protected:
    string m_Name;
};

class Cow : public Animal {
  public:
    Cow(string name) : Animal(name){}

};

class Horse : Animal {
  public:
    Horse (string name) : Animal(name){}  
    void say (){
      sayYourName(*this);
    }
  
};

int main (){

  Animal anim("Jacky");
  anim.sayYourName(anim);
  // Base class should be constructed - compile error
  Cow c("Joshua");
  // Very interestign... It was said, that only virtual supports
  // binding... May be this is because of the public? But with public
  // the inerface of cow is .. public!
  anim.sayYourName(c);
  c.sayYourName(anim);

  Horse h("Pipelo");
  // not possible.. Does it mean it need virtual?
  anim.sayYourName(h);

  return 0;
}