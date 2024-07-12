#include <iostream>
using namespace std;

class MyClass {
  public:
    MyClass( int * data, int metaData) : m_Value(metaData), m_Data(data)  {}
    ~MyClass () { delete m_Data;}
    MyClass (MyClass && src){
      m_Data = src.m_Data;
      m_Value = src.m_Value;
      src.m_Data = nullptr;
    }
    void print () { cout << "meta: " << m_Value << " data: " << *m_Data << endl; }
  private:
    int m_Value;
    int * m_Data;
};

int main () {

  MyClass a(new int(10), 15);
  a.print();

  MyClass b = move(a); 
  b.print();

  // Segmentation fault. 
  // A was moved to MyClass. Therefore, a now has m_Data -> nullptr.
  a.print();

  return 0;
}