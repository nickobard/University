#include <iostream>
#include <string>
#include <iomanip>
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

class Berty : public Cow {
  public:
    Berty (int age);
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
//-----------------------------BERTY----------------------------------------

Berty::Berty(int age)
: Cow ( "Berty", age)
{}
//=============================FUNCTIONS====================================

void animalSays( const Animal &a){
  a.say();
}
void animalSaysStatic( const Animal a){
  a.say();
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
  Berty c(10);
  c.say();
  c.age();
  c.changeName("Big Berty");
  c.say();
  cout << setfill('-') << setw(50) << "" << endl;
  animalSays(a); //parameter is 
  animalSays(b);
  animalSays(c);
  cout << setfill('-') << setw(50) << "" << endl;
  animalSaysStatic(a);
  animalSaysStatic(b);
  animalSaysStatic(c);

  return 0;
  
}