#include <iostream>
#include <string>
using namespace std;

class Animal {
  public:
    void sayHi(){
      cout << "Animal: Hi" << endl;
    }
  protected:
    void name () {
      cout << "My name is Berta" << endl;
    }
  private:
    void age(){
      cout << "My age is 5" << endl;
    }
    
};

class privateCow : /* private */ Animal {
  public:
    void say(){
      sayHi();
      name(); // protected are always private
      // age(); // private becomes inaccessible
    }
};

class publicCow : public Animal {
  public:
    void sayName(){
      name();
      // age(); // private even through public is inaccessible
      // private is always inaccessible - really always
      // only public may not degrade to private, if used public in the 
      // class derivation list
    }
};

class protectedCow : protected Animal{
  public:
    void say(){
      sayHi();
      name(); // name s protected
      // age(); // age is inaccessible
    }

};

int main (){
  cout << "Animal: " << endl;
  Animal a;
  a.sayHi();
  // a.name() // no, all protected are private
  // a.age() // no, private
  cout << "private Cow: sayHi is from public becoms private " << endl;

  privateCow c1;
  c1.say(); // own public, that use sayHi, which became from public to private
  cout << "public Cow: sayHi from public remains public" << endl;

  publicCow c2;
  c2.sayHi();
  c2.sayName();
  // c2.name(); No, is inaccessible, remains protected - now is private.
  cout << "protected Cow: sayHi from public remains public" << endl;

  protectedCow c3;
  // c3.sayHi() // public becomes private
  c3.say();
  
  return 0;
}