#include <iostream>
#include <string>
using namespace std;

class Animal{
  public:
    Animal(string name, int age) : name (name), age(new int(age)) {}
    void SayHi(){
      cout << "Hi" << endl;
    }
    ~Animal(){
      delete age;
    }
  protected:
    void SayName(){
      cout << name << endl;
    }
    string name;
  private:
    void SayAge(){
      cout << *age << endl;
    }
  int * age;
};

class Cow : public Animal{
  public:
    Cow(string name, string aname, int age )
    : Animal (name,age)
    , anotherName (new string(aname))
    {}

    ~Cow()
    {
      delete anotherName;
    }
  private:
    string * anotherName;

};

int main(){

  Animal a1("Jerry", 2);
  // deallocated normally... Because we didn't use dynamic allocation.
  Cow c1 ("Berta", "Biggy", 4); 
  Animal *a2;
  // Base should be accessible to is it in this way -> publci access specifier
  // If NOT public, we cannot access Animale base of Cow in Cow object
  a2 = &c1; 
  // because public, share same interface
  a2->SayHi();
  c1.SayHi(); 


  return 0;
}