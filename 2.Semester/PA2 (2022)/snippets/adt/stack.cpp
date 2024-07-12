#include<iostream>
#include<cstring>
using namespace std;

const size_t STACK_INIT = 2;

class CStackArray{
  public:
  struct TPoint{
    int m_X;
    int m_Y;
  };
    CStackArray();
    ~CStackArray();
    TPoint pop();
    TPoint peek() const;
    bool push(const TPoint &point);
    bool empty() const;
    void printStack() const;
  private:
    TPoint * m_stack;
    size_t m_used, m_cap;
};

CStackArray::CStackArray()
: m_stack (new TPoint [STACK_INIT]),
  m_used(0),
  m_cap (STACK_INIT)
  {}

CStackArray::~CStackArray()
{
  delete [] m_stack;
}

bool CStackArray::push(const TPoint &point){
  if ( m_used >= m_cap){
    m_cap = 10 + m_cap * 2;
    TPoint * tmp = new TPoint [m_cap];
    if (!tmp)
      return false;
    memcpy (tmp,m_stack, m_used * sizeof(TPoint));
    delete [] m_stack;
    m_stack = tmp;
  }
  m_stack[m_used++] = point;
  return true;
}

void CStackArray::printStack() const{
  for ( int i = m_used - 1; i >= 0; i--){
    cout << "{"<< m_stack[i].m_X << ", " << m_stack[i].m_Y << "}  ";
  }
  cout << endl;
}
CStackArray::TPoint CStackArray::pop(){
  if (!empty())
    return m_stack[--m_used];
  cout << "stack underflow" << endl;
  return {0,0}; 
}
bool CStackArray::empty() const{
  if (m_used == 0)
    return true;
  return false;
}

CStackArray::TPoint CStackArray::peek() const{
  if (!empty())
    return m_stack[m_used - 1];
  cout << "stack underflow" << endl;
  return {0,0};
}



int main(){
  CStackArray::TPoint b;
  CStackArray a;
  a.push({10,0});
  a.push({11,0});
  a.push({12,0});
  a.push({13,0});
  a.push({14,0});
  a.push({15,0});
  a.push({16,0});
  a.printStack();
  b = a.pop();
  cout << "{" << b.m_X << ", " << b.m_Y << "}" << endl;
  a.printStack();
  b = a.pop();
  b = a.pop();
  b = a.pop();
  a.printStack();
  b = a.peek();
  cout << "{" << b.m_X << ", " << b.m_Y << "}" << endl;
  a.printStack();
  a.push({10,0});
  a.push({11,0});
  a.push({12,0});
  a.push({13,0});
  a.push({14,0});
  a.push({15,0});
  a.printStack();

  return 0;
}