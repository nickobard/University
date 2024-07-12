#include <iostream>
#include <string>
using namespace std;

class A {
  public:
  // cannot do that..
    /* void say( const string &src)
    : n_Str 
    {
      string m_Str2;
    }
    */
  //  also cannot do that
    /* A sayHi (const string &src)
    : m_Str (src)
    {} */

    // ok, using constructor initializer list
    A (const string &str)
    : m_Str (str)
    {}
    // But didn't know that we can use constructor
    // initializer list in the copy constructor.. Great!
    A (const A &src) 
    : m_Str(src.m_Str)
    {}

    string m_Str; 

};

int main (){
  return 0;
}