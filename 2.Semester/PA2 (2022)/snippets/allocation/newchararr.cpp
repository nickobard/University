#include <cstring>
#include <iostream>
using namespace std;
class Person{
  public:
    Person(const char * val)
    : m_Name(strcpy(new char[strlen(val)+1],val))
    {}
    ~Person(){
      delete [] m_Name;
    }
    char * m_Name;
};

int main(){
  Person a("John Christescu");
  cout << a.m_Name << endl;
  return 0;
}