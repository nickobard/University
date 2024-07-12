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
    };
      // post-order traversing
    void printNLR() const;
      // in-order traversing
    void printLNR() const;
      // post-order traversing
    void printLRN() const;

    bool setIsSet(int x) const;
    bool empty() const;
    bool setIns(int x);
    bool setDel(int x);
    void delTree(TNode * n);
  private:
    void printNLR(const TNode * n) const;
    void printLNR(const TNode * n) const;
    void printLRN(const TNode * n) const;

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

bool CSet::empty() const {
  return !m_Root;
}

bool CSet::setIns(int x){
  TNode ** tmp = &m_Root;
  while (*tmp){
    if( (*tmp)->m_Val == x ) // if this node has same value -> return false
    // element was found in the set, cannot insert
      return false;
    else if( x < (*tmp)->m_Val ) // if element is less ->
    // descend to the left successor
      tmp = &(*tmp)->m_L;
    else // if element is greater -> descend to the right successor
      tmp = &(*tmp)->m_R;
    // repeat for the current node
  }
  // if we are here -> element wasn't found, 
  // but we have pointer to the node where it should be (*tmp)
  // and pointer to the parent tmp, from where it points to the node

  TNode * n = new TNode {nullptr,nullptr,x};
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

void CSet::printNLR() const{
  cout << "NLR ( ";
  printNLR(m_Root);
  cout << ")" << endl;
}
void CSet::printNLR(const TNode * n) const{
  if (!n)
    return;
  cout << n->m_Val << " ";
  printNLR(n->m_L);
  printNLR(n->m_R);
}
void CSet::printLNR() const{
  cout << "LNR ( ";
  printLNR(m_Root);
  cout << ")" << endl;
}
void CSet::printLNR(const TNode * n) const{
  if (!n)
    return;
  printLNR(n->m_L);
  cout << n->m_Val << " ";
  printLNR(n->m_R);
}
void CSet::printLRN() const{
  cout << "LRN ( ";
  printLRN(m_Root);
  cout << ")" << endl;
}
void CSet::printLRN(const TNode * n) const{
  if (!n)
    return;
  printLRN(n->m_L);
  printLRN(n->m_R);
  cout << n->m_Val << " ";
}

bool CSet::setIsSet(int x) const{
  TNode * tmp = m_Root;
  while (tmp){
    if ( tmp->m_Val == x)
      return true;
    else if ( x < tmp->m_Val)
      tmp = tmp->m_L;
    else
      tmp = tmp->m_R;
  }
  return false;
}


bool CSet::setDel(int x){
  TNode ** tmp = &m_Root;
  while  (*tmp){
    if ( (*tmp)->m_Val == x )
    {
      // found. We have ponter from parent to the node,
      // where value is found successfuly
      //cout << (*tmp)->m_Val << " = " << x << endl; OK

      // if *tmp points to leaf
      if ( !((*tmp)->m_L || (*tmp)->m_R)){
        delete *tmp;
        *tmp = nullptr;
        return true;
      }
      if ( !(*tmp)->m_L ){
        TNode * tmp1 = (*tmp)->m_R;
        delete *tmp;
        *tmp = tmp1;
        return true;
      }
      TNode ** rpl = &(*tmp)->m_L;
      if (!(*rpl)->m_R){
        (*rpl)->m_R = (*tmp)->m_R;
        TNode * tmp1 = *rpl;
        delete *tmp;
        *tmp = tmp1;
        return true;
      }
      while ((*rpl)->m_R){
        rpl = &(*rpl)->m_R;
      }
      //cout << (*rpl)->m_Val << endl;
      //cout << (*rpl)->m_L->m_Val << endl;
      (*rpl)->m_R =(*tmp)->m_R;
      TNode * tmp2 = (*tmp)->m_L;
      delete *tmp;
      *tmp = *rpl;
      *rpl = (*rpl)->m_L;
      (*tmp)->m_L = tmp2;

      return true;
      
    }
    else if( x < (*tmp)->m_Val)
      tmp = &(*tmp)->m_L;
    else
      tmp = &(*tmp)->m_R;
  }
  //cout << x << " not found." << endl; OK
  return false;
}

int main(){
  CSet a;


  a.setIns(100);
  a.setIns(10);
  a.setIns(20);
  a.setIns(100);
  a.setIns(70);
  a.setIns(170);
  a.setIns(270);
  a.setIns(50);
  a.setIns(200);
  a.setIns(300);

  cout <<                    "\n"
  "         100         "    "\n"
  "        /   \\       "    "\n"
  "      10     170     "    "\n"
  "       \\       \\   "    "\n"
  "       20      270   "    "\n"
  "        \\     /   \\"    "\n"
  "        70   200  300"    "\n"
  "       /             "    "\n"
  "     50              "    "\n"
  << endl;
  a.printNLR();
  a.printLNR();
  a.printLRN();

  CSet b;

  b.setIns(100);
  b.setIns(10);
  b.setIns(20);
  b.setIns(100);
  b.setIns(70);
  b.setIns(170);
  b.setIns(270);
  b.setIns(50);
  b.setIns(200);
  b.setIns(300);
  b.setIns(195);
  b.setIns(235);
  b.setIns(240);
  b.setIns(237);
  b.setIns(236);
  b.setIns(238);
  b.printLRN();
  b.setDel(300);
  b.setDel(50);
  b.printLRN();
  b.setIns(300);
  b.printLRN();
  b.setDel(270);
  b.printLRN();
  b.printNLR();
  b.setDel(100);
  b.printNLR();
  b.setDel(70);
  b.printNLR();
  b.setDel(20);
  b.printNLR();
  b.setDel(10);
  b.printNLR();
  b.setDel(170);
  b.printNLR();
  b.setDel(240);  
  b.printNLR(); 
  b.setDel(238);
  b.printNLR();
  b.setDel(237);
  b.printNLR();
  b.setDel(236);
  b.printNLR();
  b.setDel(235);
  b.printNLR();
  b.setDel(200);
  b.printNLR();
  b.setDel(195);
  b.printNLR();
  b.setDel(300);
  b.printNLR();
  cout << b.empty() << endl;
/*

  b.setDel(10);
  b.setDel(0);
  b.setDel(123);
  b.setDel(300);
*/

  return 0;
}