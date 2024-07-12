#include <iostream>
using namespace std;

class MyClass {
  public:
    MyClass( int * data, int metaData) : m_Value(metaData), m_Data(data)  {}
    ~MyClass () { delete m_Data;}
    void print () { cout << "meta: " << m_Value << " data: " << *m_Data << endl; }
  private:
    int m_Value;
    int * m_Data;
};

int main () {

  MyClass a(new int(10), 15);
  a.print();

  // problem with double free. Data were moved. 
  // But there is no move constructor for that.
  MyClass b = move(a); 
  b.print();
  // double free..
  return 0;
}