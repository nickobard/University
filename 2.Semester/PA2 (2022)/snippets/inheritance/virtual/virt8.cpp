#include <iostream>
#include <string>
using namespace std;

class Animal {
  public:
    Animal (string str) : m_Name(str) {}
    virtual void sayYourName ( const Animal &src){
      cout << src.m_Name << endl;
    }
    string m_Name;
};
class Cow : Animal{
  public:
    Cow (string str) : Animal(str) {}
    void sayYourName (const Animal &src) override{
      cout << src.m_Name << endl;
    }
};


int main(){
  Animal a("Go-Go");
  Cow c ("Azor");
  // No, that is still inaccessible...
  // a.sayYourName(c);
  // well, I cann override it be even public,
  // but cannot pass the derived type...
  // I see it is always possible only with public. Never else

  // c.sayYourName(c);
  c.sayYourName(a); // That is OK
  return 0;
}