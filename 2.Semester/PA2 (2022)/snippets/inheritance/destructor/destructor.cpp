#include <iostream>
#include <string>
using namespace std;

class Animal {
  public:
    virtual ~Animal(){
      cout << "Animal: Destructor." << endl;
      delete m_Val;
    }
  private:
    int * m_Val = new int (10);
};

class Cow : public Animal {
  public:
    virtual ~Cow(){
      cout << "Cow: Destructor." << endl;
      delete str;
    }
  private:
    string * str = new string ("Cow");
};


int main (){
  Animal * a = new Animal;
  delete a;


  a = new Cow;
  delete a;
  
  return 0;
}