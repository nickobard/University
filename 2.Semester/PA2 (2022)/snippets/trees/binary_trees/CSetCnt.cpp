#include <iostream>
using namespace std;

class CSet{
  public:
    CSet();
    ~CSet();
    struct TNode{
      TNode * m_R;
      TNode * m_L;
      int m_Val;
      size_t m_Cnt;
    };
    void printLNR() const;
    bool setIns(int x);
    void delTree(TNode * n);
  private:
    void printLNR(const TNode * n) const;

    TNode * m_Root;
    size_t m_Cnt;
};

CSet::CSet()
: m_Root(nullptr),
  m_Cnt(0)
{}
CSet::~CSet()
{
  delTree(m_Root);
}

bool CSet::setIns(int x){
  TNode ** tmp = &m_Root;
  while (*tmp){
    if( (*tmp)->m_Val == x ){
      (*tmp)->m_Cnt++;
      return true;
    }
    else if( x < (*tmp)->m_Val ) 
      tmp = &(*tmp)->m_L;
    else 
      tmp = &(*tmp)->m_R;
  }

  TNode * n = new TNode {nullptr,nullptr,x,1};
  *tmp = n;
  m_Cnt++; 

  return true;
}

void CSet::delTree(TNode * n){
  if (!n)
    return;
  delTree(n->m_L);
  delTree(n->m_R);
  delete n;
}

void CSet::printLNR() const{
  cout << "( ";
  printLNR(m_Root);
  cout << ")" << endl;
}
void CSet::printLNR(const TNode * n) const{
  if (!n)
    return;
  printLNR(n->m_L);
  for ( size_t i = 0; i < n->m_Cnt; i++){
    cout << n->m_Val << " ";
  }
  printLNR(n->m_R);
}

int main(){
  CSet a;
  a.setIns(100);
  a.setIns(100);
  a.setIns(70);
  a.setIns(50);
  a.setIns(200);
  a.setIns(300);
  a.printLNR();

  return 0;
}