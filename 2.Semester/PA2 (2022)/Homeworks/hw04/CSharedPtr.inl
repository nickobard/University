
// #EX_BEGIN
#pragma once
#include "CSharedPtr.h"
// #EX_END

template<typename T>
CSharedPtr<T>::CSharedPtr()
: m_Ps (nullptr)
, m_Use(nullptr)
{}

template<typename T>
CSharedPtr<T>::~CSharedPtr()
{
  if (!m_Use)
    return;
  else if ( --*m_Use == 0 ){
    delete m_Ps;
    delete m_Use;
  }
}

template<typename T>
CSharedPtr<T>::CSharedPtr( const CSharedPtr<T> &src )
: m_Ps (src.m_Ps)
, m_Use (src.m_Use)
{
  if (!m_Use)
    return;
  else 
    ++*m_Use;
}

template<typename T>
void CSharedPtr<T>::move(CSharedPtr<T> src){
  T * tmp_Ps = m_Ps;
  uint32_t * tmp_Use = m_Use;

  m_Ps = src.m_Ps;
  m_Use = src.m_Use;

  src.m_Ps = tmp_Ps;
  src.m_Use = tmp_Use;
}

template<typename T>
CSharedPtr<T> &CSharedPtr<T>::operator= (const CSharedPtr<T> &rhs){
  if (this == &rhs)
    return *this;
  move (rhs);
  return *this;
}

template<typename T>
CSharedPtr<T>::CSharedPtr(T * val)
: m_Ps (val)
, m_Use (new uint32_t(1))
{}

template<typename T>
CSharedPtr<T> make_Shared ( const T & val ){
  return CSharedPtr<T> (new T(val));
}

template<typename T>
CSharedPtr<T> make_Shared ( ){
  return CSharedPtr<T> (new T());
}

template<typename T>
T * CSharedPtr<T>::get() const {
  return m_Ps;
}

template<typename T>
bool CSharedPtr<T>::unique() const {
  return m_Use && *m_Use == 1
         ? true
         : false;
}

template<typename T>
uint32_t CSharedPtr<T>::use_count() const{
  return m_Use
         ? *m_Use
         : 0;
}

template<typename T>
T &CSharedPtr<T>::operator* () const {
  return *m_Ps;
}

template<typename T>
T * CSharedPtr<T>::operator-> () const{
  return &m_Ps[index];
}

template<typename T>
bool CSharedPtr<T>::operator== (const CSharedPtr<T> &rhs) const {
  return m_Ps == rhs.m_Ps;
}

template<typename T>
bool CSharedPtr<T>::operator!= (const CSharedPtr<T> &rhs) const {
  return m_Ps != rhs.m_Ps;
}