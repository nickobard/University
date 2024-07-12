// #EX_BEGIN
#include "CStack.h"
// #EX_END

void CStack::move(CStack src){
  CStack::CNode * tmp = m_Top;
  m_Top = src.m_Top;
  src.m_Top = tmp;
  m_Size = src.m_Size;
}

CStack::CStack ()
: m_Top (nullptr)
, m_Size (0)
{}

CStack::~CStack ()
{
  while (m_Top){
    CNode * tmp = m_Top->m_next;
    delete m_Top;
    m_Top = tmp;
  }
}

CStack::CStack ( const CStack &src)
: m_Top(nullptr)
, m_Size(0)
{ 
  if (src.Empty())
    return;
  CNode * tmp_src = src.m_Top;
  m_Top = new CNode {nullptr, tmp_src->m_File};
  CNode * ptr = m_Top;
  tmp_src = tmp_src->m_next;

  while(tmp_src){
    ptr->m_next = new CNode {nullptr,tmp_src->m_File};
    ptr = ptr->m_next;
    tmp_src = tmp_src->m_next;
  }
}

CStack &CStack::operator= (const CStack &rhs){
  if (this == &rhs)
    return *this;
  move(rhs);
  return *this;
}


bool CStack::Empty () const {
  return !m_Top;
}

void CStack::Push ( const TFile &version){
  CNode * new_node = new CNode {m_Top, version };
  m_Top = new_node;
  m_Size ++;
}

bool CStack::Pop (){
  if (Empty())
    return false;
  CNode * tmp = m_Top->m_next;
  delete m_Top;
  m_Top = tmp;
  m_Size--;
  return true;
}
TFile CStack::Top ( ) const{
  return m_Top->m_File; 
}

uint32_t CStack::Size() const {
  return m_Size;
}
