#include<iostream>
#include<vector>
#include<string>
using namespace std;

class CList {
  public:
    CList();
    ~CList();

    bool Insert_();
    bool Remove(...);
    bool Empty(...) const;
    void Display() const;
    size_t Size();
  private:
    struct CNode {
      string m_name;
      int m_val;
    };
    size_t m_size;
    CNode * m_head;
    CNode * m_back;
};

int main (){

  return 0;
}