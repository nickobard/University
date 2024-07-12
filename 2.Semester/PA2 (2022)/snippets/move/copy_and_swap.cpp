#include <iostream>
using namespace std;

class MyClass {
  public:
    MyClass( int * data, int metaData) : m_Value(metaData), m_Data(data)  {}
    ~MyClass () { delete m_Data;}
    MyClass(const MyClass &src) {
      m_Data = new int (*src.m_Data);
      m_Value = src.m_Value;
    }
    MyClass (MyClass && src){
      m_Data = src.m_Data;
      m_Value = src.m_Value;
      src.m_Data = nullptr;
    }

    MyClass & operator= (MyClass src){
      swap(m_Data, src.m_Data);
      swap(m_Value, src.m_Value);
      return *this;
    }

    void print () { cout << "meta: " << m_Value << " data: " << *m_Data << endl; }
  private:
    int m_Value;
    int * m_Data;
};

int main () {

  MyClass a(new int(10), 15);
  a.print();

  MyClass b (new int (20), 42);
  b.print();

  a = b;
  a.print();
  b.print();

  return 0;
}