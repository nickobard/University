#include <iostream>
using namespace std;

class Person {
  public:
    virtual void sayHi() const {
      cout << "Hero: Hi" << endl;
    }
};

class Hero : Person {
  public:
    void saySelf(){
      // here member function use the conversion. Not user...
      // Here it is applicabel to use such conversion
      // Really don't know where and how to use it...
      say(*this);
    }
    virtual void sayHi() const {
      cout << "Hero: Hi" << endl;
    }
    void say(const Person &p){
      p.sayHi();
    }
    Person p;
};

int main () {
  Person p;
  
  Hero h;
  // so this is user code 
  // i am not inside the class. So, it is impossible... Hmmm
  // h.say(h);
  h.say(p);

  h.saySelf();

  return 0;
}