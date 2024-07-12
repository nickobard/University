#include<iostream>
#include<string>
using namespace std;

class myString1{
  public:
    myString1(string &str) : m_str(str) {} // with reference
    // as parameter is copied only reference
    // and then it initialize the m_str through copying.
    // We have two copies, but one of them is reference - only 8 bytes
    // instead of 10*10e6 + 1 bytes.
    string m_str;
};

class myString2{
  public:
    myString2(string str) : m_str(str) {} // without reference
    // as parameter is copied the whole string,
    // and then the whole string initialize the m_str 
    // again with copying.
    // There for its time is two times bigger - 4 seconds instead of 2.
    // Because we copy string two times.
    string m_str;
};

int main (){
  string hello_world = "Hello world";
  string buffer;
  for ( int i = 0; i < 10e6 ; i ++){
    buffer += hello_world;
  }

  for ( int i = 0; i < 10e1; i++){
    myString1 a(buffer);  // with ref - 2.4s
    //myString2 a(buffer); // without ref - 4.5s
  }
  //cout << buffer << endl;
  return 0;
}