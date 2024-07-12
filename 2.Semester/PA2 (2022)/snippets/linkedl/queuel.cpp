#include<iostream>
using namespace std;

class CQueueLinked{
  public:
    CQueueLinked();
    ~CQueueLinked();
    struct TNode {
      TNode * next;
      int val;
    };
    bool empty() const;
    void push(const int val);
    int  peek() const;
    int pop();
    void printQueue() const;
  private:
    TNode * m_front;
    TNode * m_rear;
};

CQueueLinked::CQueueLinked()
: m_front(nullptr),
  m_rear(nullptr)
{}

CQueueLinked::~CQueueLinked()
{
  if (!empty()){
    TNode * ptr = m_front;
    while (ptr){
      ptr = ptr->next;
      delete m_front;
      m_front = ptr;
    }
  }
}

bool CQueueLinked::empty() const{
  return !m_front;
}
void CQueueLinked::push(const int val){
  TNode * new_node = new TNode {nullptr, val};
  if (!empty())
    m_rear->next = new_node;
  else
    m_front = new_node;
  m_rear = new_node;
}

void CQueueLinked::printQueue() const{
  if(!empty()){
    TNode * ptr = m_front;
    cout << ptr->val;
    ptr = ptr->next;
    while (ptr)
    {
      cout << " -> " << ptr->val;
      ptr = ptr->next;
    }
    cout << endl;
    return;
  }
  cout << "Queue is empty." << endl;
}

int CQueueLinked::pop(){
  if(!empty()){
    TNode * ptr = m_front->next;
    int val = m_front->val;
    delete m_front;
    m_front = ptr;
    return val;
  }
  cout << "Queue is empty." << endl;
  return 0;
}

int  CQueueLinked::peek() const{
  return m_front->val;
}


int main(){
  CQueueLinked a;
  a.push(10);
  a.push(20);
  a.push(30);
  a.push(40);
  a.push(50);
  a.printQueue();
  cout << a.pop() << endl;
  cout << a.pop() << endl;
  cout << a.pop() << endl;
  a.printQueue();
  cout << a.peek() << endl;
  a.printQueue();
  return 0;
}