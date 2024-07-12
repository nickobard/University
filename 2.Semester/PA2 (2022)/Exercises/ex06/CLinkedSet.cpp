/* __PROGT_BEGIN__ */
#include "CLinkedSet.h"
#include <iostream>
#include <cstring>
using namespace std;
/* __PROGT_END__ */
/**
 * @brief Destroy the CLinkedSet::CNode::CNode object
 * 
 * This object destroy the c-style string. Cool
 * 
 */
CLinkedSet::CNode::~CNode(){
  /// Look how it uses the delete [] keyword.
  delete [] m_Val;
}

const char * CLinkedSet::CNode::Value () const{
  return m_Val;
}

CLinkedSet::CLinkedSet()
: m_Begin(nullptr)
, m_Size(0)
{}

CLinkedSet::~CLinkedSet()
{
  while (m_Begin){
    CNode * tmp = m_Begin->m_Next;
    delete m_Begin;
    m_Begin= tmp;
  }
}

bool CLinkedSet::Insert (const char * val){
  CNode * new_node = new CNode{nullptr, strcpy(new char [strlen(val)+1], val)};
  if (Empty()){
    m_Begin = new_node;
    m_Size++;
    return true;
  } else {
    CNode * ptr = m_Begin;
    CNode * preptr = nullptr;
    while (ptr){
      int res = strcmp(val, ptr->m_Val);
      if ( res == 0 ){
        delete new_node;
        return false;
      }
      else if ( res < 0 ){
        if (!preptr){
          new_node->m_Next = ptr;
          m_Begin = new_node;
          m_Size++;
          return true;
        } else {
          preptr->m_Next = new_node;
          new_node->m_Next = ptr;
          m_Size++;
          return true;
        }
      }
      preptr = ptr;
      ptr = ptr->m_Next;
    }
      preptr->m_Next = new_node;
      m_Size++;
      return true;
  }
    delete new_node;
    return false;
}

bool CLinkedSet::Empty () const {
  return !m_Begin;
}

bool CLinkedSet::Contains ( const char * value ) const{
  CNode * ptr = m_Begin;
  while (ptr){
    if (!strcmp(ptr->m_Val, value))
      return true;
    ptr = ptr->m_Next;
  }
  return false;
}

size_t CLinkedSet::Size () const{
  return m_Size;
}

bool CLinkedSet::Remove ( const char * value ){
  if (Empty())
    return false;
  CNode * ptr = m_Begin;
  CNode * preptr = nullptr;
  while(ptr){
    if (!strcmp(ptr->m_Val, value)){
      if (!preptr){
        m_Begin = ptr->m_Next;
        delete ptr;
        m_Size--;
        return true;
      } else {
        preptr->m_Next = ptr->m_Next;
        delete ptr;
        m_Size--;
        return true;
      }
    }
    preptr = ptr;
    ptr = ptr->m_Next;
  }
  return false;
}

CLinkedSet::CLinkedSet(const CLinkedSet &cp)
: m_Begin(nullptr)
, m_Size(cp.m_Size)
{
  CNode * ptr = cp.m_Begin;
  CNode * cpy = m_Begin;
  while (ptr){
    CNode * tmp = new CNode {nullptr,strcpy(new char [strlen(ptr->m_Val)+1], ptr->m_Val)};
    if (!m_Begin){
      m_Begin = tmp;
      cpy = m_Begin;
    }
    else {
      cpy->m_Next = tmp;
      cpy = cpy->m_Next;
    }
    ptr = ptr->m_Next;
  }
}

CLinkedSet &CLinkedSet::operator= (const CLinkedSet &rhs){
  m_Size = rhs.m_Size;
   while (m_Begin){
    CNode * tmp = m_Begin->m_Next;
    delete m_Begin;
    m_Begin= tmp;
  }
  m_Begin = nullptr;
  CNode * ptr = rhs.m_Begin;
  CNode * cpy = m_Begin;
  while (ptr){
    CNode * tmp = new CNode {nullptr,strcpy(new char [strlen(ptr->m_Val)+1], ptr->m_Val)};
    if (!m_Begin){
      m_Begin = tmp;
      cpy = m_Begin;
    }
    else {
      cpy->m_Next = tmp;
      cpy = cpy->m_Next;
    }
    ptr = ptr->m_Next;
  }
  return *this;
}

/* __PROGT_BEGIN__ */
void CLinkedSet::print() const {
  if (Empty())
    return;
  cout << m_Begin->m_Val;
  CNode * ptr = m_Begin->m_Next;
  while(ptr){
    cout << " -> " << ptr->m_Val;
    ptr = ptr->m_Next;
  }
  cout << endl;
}
/* __PROGT_END__ */