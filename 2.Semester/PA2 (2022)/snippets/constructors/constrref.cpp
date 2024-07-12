#include<iostream>
#include<string>
using namespace std;

class myString{
  public: // ???
    myString(string &str) : m_str(str) {} //using reference is valid,
    // because implicitely m_str(str) is m_str(*str).
    // But str parameter here is not created.
    // Would it be created without reference? 
    // Because initializer list is good, because it never
    // creates parameter, but directly initalize class members...
    string m_str;
};

int main (){
  string str = "Hello world!";
  cout << str << endl;

  myString a(str);
  cout << a.m_str << endl;
  str = "World, hello!";
  cout << str << endl;
  cout << a.m_str << endl;
  return 0;
}