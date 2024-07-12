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

class Man : Person{
  public:
    void say() override{
      sayHi();
    }
};

class Child : Man{
  public:
    void say() override{ // say remaind override for all say functions
    // that is somehow static for all family
        // sayHi(); // is inaccessible -> protected becomes private..
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