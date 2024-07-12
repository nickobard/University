#include <iostream>
#include <vector>
using namespace std;

bool ex = false;

class MyClass {
  public:
    MyClass( int value, MyClass * next) :  m_Next(next), m_Value(value) {}
    ~MyClass () noexcept {}

    MyClass (MyClass && src) noexcept  {
      cout << "Move constructor!" << endl;
      m_Next = src.m_Next;
      m_Value = src.m_Value;
      src.m_Next = nullptr;
    }

    MyClass & operator= (MyClass && src) {
      swap(m_Next, src.m_Next);
      m_Value = src.m_Value;
      return *this;
    }

    void print () { cout << "Value: " << m_Value << endl; }
    MyClass * m_Next;
  private:
    int m_Value;
    
};

void foo ( MyClass & b, vector<MyClass> & vec){
  MyClass a(32, nullptr);
  b.m_Next = &a;
  vec.push_back(move(a));
}

int main () {

  MyClass b(69, nullptr);
  vector<MyClass> vec;
  foo(b, vec);
  vec[0].print();
  b.m_Next->print();

  return 0;
}