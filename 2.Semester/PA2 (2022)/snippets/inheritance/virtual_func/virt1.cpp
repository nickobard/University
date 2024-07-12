#include <iostream>
using namespace std;



class Animal {
  public: 
    void SayHi()const{
      cout << "Animal: Hi" << endl;
    }
    void SayHello () const {
      cout << "Animal: Hello" << endl;
    }
  private:
  // cannot define same function with in the same scope.
  // Crucial is the scope, where that function is used
    /* void SayHi(){
      cout << "Animal: private Hi" << endl;
    } */
};

class Cow : Animal {
    public:
      void SayHi()const{
        // so we can use this private form the ANimal scope..
        // We can use because it is from another scope, and is private.
        // So there is no name clashes.
        // That corresponds with the fact, that base and derived are separated. They are at different scope. So between them there is no
        // name clashes
        Animal::SayHi();
        cout << "Cow: Hi" << endl;
      }
    private:
    // again, can use that, because we are at the Cow scope. Not clashes.
    // can have Animal:: and Cow:: functions with same name.
      void SayHello(){
        cout << "Cow: Hello" << endl;
      }
    
};

class Horse : public Animal {
  public:
  // even when it is public we can use that
  // but it will be completely different function
  // They all are completely different functions from other scopes.
  // So no dynamic binding should be applied...
    void SayHi()const{
      cout << "Horse: Hi" << endl;
    }

};
// Note, that here we pass const this -> therefore it can use ONLY const
// methods... Well, that is suprisingly interesting and very good I've noted that. 
void say( const Animal &src){
  src.SayHi();
}

int main (){

  Animal a;
  a.SayHi();
  say(a);
  cout << "\nCow time:" << endl; 

  Cow c;
  // Cow doesn't have public Animal::SayHi. So there are no clashes
  c.SayHi();
  // Cannot do that. Without public it doesn't have interface of tha Animal, even if that is virtual. So it is just impossible.
  // say(c);
  cout << "\nHorse time:" << endl;
  Horse h;
  // here it is the most important moment. Without virtual we just define
  // functions from different scopse.
  h.Animal::SayHi();

  h.Horse::SayHi();
  // we have defined SayHi in Horse, so it has more priority
  // No name clashes, but should be explicit
  h.SayHi();
  // No such functions in the Horse class, there fore is used implicitly
  // the Animal class method - from Animal scope
  h.SayHello();

  cout << "\nSay time:" << endl;

  // Though we pass there horse object, the dynamic type is chosen
  // BUT, because in the say functions we call function from Animal
  // scope, that only functions will be used instead of Horse sayHi
  // NO dynamic binding. That is the difference.
  // Tha Animal::sayHi is used. And because oru horse object contain same accessible interface, it will call that functions.

  say(h);
  
  return 0;
}