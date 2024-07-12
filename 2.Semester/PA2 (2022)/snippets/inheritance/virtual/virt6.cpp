#include <iostream>
using namespace std;

class Person{
  public:
    virtual void say(){
      sayHi();
    }
  protected:
    void sayHi(){
      cout << "Hi" << endl;
    }
};
// with public protected remains protected
class Man : protected Person{
  public:
    void say() override{
      sayHi();
    }
};

class Child : Man{
  public:
    void say() override{ // say remaind override for all say functions
    // that is somehow static for all family
    // we can use sayHi as private, because man derives publicly form Preson
        sayHi(); 
    }
};

int main(){

Person p;
Man m;
Child c;

cout << "Person: ";
p.say();
cout << "Man: ";
m.say();
cout << "Child: ";
c.say();
  
  return  0;
}