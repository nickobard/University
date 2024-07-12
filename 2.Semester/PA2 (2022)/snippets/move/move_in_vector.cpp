#include <iostream>
#include <vector>
using namespace std;

bool ex = false;

class MyClass {
  public:
    MyClass( int * data, int metaData) : m_Value(metaData), m_Data(data)  {}
    ~MyClass () noexcept { delete m_Data;}
    MyClass(const MyClass &src) {
      cout << "Copy constructor!" << endl;
      m_Data = new int (*src.m_Data);
      m_Value = src.m_Value;
    }
    MyClass (MyClass && src) noexcept  {
      cout << "Move constructor!" << endl;
      m_Data = src.m_Data;
      m_Value = src.m_Value;
      src.m_Data = nullptr;
    }

    MyClass & operator= (MyClass src) {
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

  vector<MyClass> v1, v2;
  // move constructor was used to push back member.
  v1.push_back({new int(1), 1});
  // v1.shrink_to_fit();
  cout << v1.size() << endl;
  cout << v1.capacity() << endl;
  v1.push_back({new int(1), 1}); // Here when reallocating move constructor
  // is used only if destructor and move constructor are noexcept.


  return 0;
}