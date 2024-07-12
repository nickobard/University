#include <iostream>
#include <string>
using namespace std;
class Animal {
  public:
    Animal (const string & name) 
    : m_Name(name)
    {}
  private:
    string m_Name;
};

class Cow : public Animal {
  public:
  // Here we use Animal constructor... What about m_Age..
    // using Animal::Animal;
    // Here is another way using own construcotr instead of Animal's
    Cow ( const string & name )
    : Cow::Animal (name)
    {}
    int m_Age;
};

int main (){
  Cow c1 ("Berta");
  cout << c1.m_Age << endl;
  return 0;
}