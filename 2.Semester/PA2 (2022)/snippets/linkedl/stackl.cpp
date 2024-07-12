#include <iostream>
using namespace std;
class CStackLinked{
  public:
    CStackLinked();
    ~CStackLinked();
    struct TNode{
      TNode * next;
      int val;
    };
    bool empty() const;
    void push(const int val);
    int  peek() const;
    int pop();
    void printStack() const;
  private:
    TNode * m_top;
};

CStackLinked::CStackLinked()
: m_top(nullptr)
  {}
CStackLinked::~CStackLinked()
{
  if (!empty()){
    TNode * ptr = m_top;
    while (ptr){
      ptr = ptr->next;
      delete m_top;
      m_top = ptr;
    }
  }
}

bool CStackLinked::empty() const{
  return !m_top;
}

void CStackLinked::push(const int val){
  TNode * new_Node = new TNode {nullptr, val}; 
  if (!empty()){
    new_Node->next = m_top;
  }
  m_top = new_Node;
}

void CStackLinked::printStack() const{
  if (!empty()){
    TNode * ptr = m_top;
    cout << ptr->val;
    ptr = ptr->next;
    while (ptr){
      cout << " -> " << ptr->val;
      ptr = ptr->next;

    }
    cout << endl;
  }
  else{
    cout << "Stack is empty." << endl;
  }
}

int  CStackLinked::peek() const{
  if (!empty())
    return m_top->val;
  cout << "Stack is empty." << endl;
  return 0;
}

int CStackLinked::pop(){
  if (!empty()){
    TNode * ptr = m_top;
    m_top = m_top->next;
    int val = ptr->val;
    delete ptr;
    return val;
  }
  cout << "Stack is empty." << endl;
  return 0;
}

int main(){
  CStackLinked a;
  a.printStack();
  a.push(10);
  a.push(20);
  a.push(30);
  a.push(40);
  a.push(50);
  a.printStack();
  cout << a.pop() << endl;
  cout << a.pop() << endl;
  cout << a.pop() << endl;
  a.printStack();

  return 0;
}