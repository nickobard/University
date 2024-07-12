#include <iostream>
#include <string>
using namespace std;
//=============================CLASSES======================================
class Animal {
  public:
    Animal(string nm, int age);
    virtual void say() const;
    virtual void age() const;
  protected:
    string m_name;
  private:
    int m_age;
};

class Cow : public Animal {
  public:
   Cow (string nm, int age );
   void age() const;
   void say() const override; //but it works without override too...
   // So why??
   void changeName ( const string &str);
  private:

};

//=============================DEFINITONS===================================

//-------------------------------ANIMAL---------------------------------------
Animal::Animal( string nm, int age)
: m_name ( move (nm) )
, m_age (age)
{}

void Animal::say() const{ // we don't have to specify virtual here
                          // because it is in the declaration.
                          // Thus implicitely it is also here.
  cout << "Animal: "<< "My name is " << m_name << endl;
}

void Animal::age() const{
  cout << "Animal " + m_name + ": My age is "<< m_age << endl;
}

//-----------------------------COW------------------------------------------
/*
void Cow::cow_age() const{
  cout << "Cow " + m_name + ": My name is " << m_age << endl;
}
*/

void Cow::say() const{
  cout << "Cow: "<< "My name is " << m_name << endl;
}

void Cow::changeName ( const string &str){
  m_name = str;
}

Cow::Cow ( string nm, int age )
: Animal (move(nm), age)
{}

void Cow::age() const{
  cout << "Animal " + m_name + ": My age is "<<  /*m_age*/
          "Error: m_age is inaccessible, not protected."
          " Cannot use to redefine." << endl;
}

//=============================MAIN=========================================

int main(){
  Animal a ("Emmy", 10);
  Cow b("Berta", 7);
  a.say();
  //cout << a.m_name << endl; Cannot use, becuase m_name is protected
  b.say();
  //cout << b.m_name << endl; again cannot use it, because it is protected
  b.changeName("Danil");
  b.say();
  b.age(); // Though age is virtual, we didn't redefine it, so it sustains 
  // same
  return 0;
}