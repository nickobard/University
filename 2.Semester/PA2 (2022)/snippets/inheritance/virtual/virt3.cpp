#include<iostream>
#include<string>
using namespace std;

class Creature {
  public:
    Creature(const string &nm);
    virtual void yourName() const;
  protected:
    string m_name;
  private:
    const string m_type;
};

class Human : Creature {
  public:
    Human (const string &nm);
    void yourName() const;
  private:
    const string m_type;
};

Creature::Creature(const string &nm)
: m_name(nm)
, m_type("Creature")
{}

void Creature::yourName()const{
  cout << m_type + ": " << "My name is " + m_name << endl;
}

Human::Human(const string &nm)
: Creature(nm)
, m_type("Human")
{}

void Human::yourName()const{
  cout << m_type + ": " << "My name is " + m_name << endl;
}

void sayYourNameDyn(const Creature &obj){
  obj.yourName();
}

void sayYourNameStat( Creature obj){
  obj.yourName();
}

int main(){
  Creature a("SssSSsss");
  Human b("David");
  a.yourName();
  b.yourName();

  sayYourNameDyn(a);
  //sayYourNameDyn(b); cannot use it, becuase is not public.
  // Creature is an inaccessible base of Human
  //sayYourNameStat(b); Same problem.
  return 0;
}