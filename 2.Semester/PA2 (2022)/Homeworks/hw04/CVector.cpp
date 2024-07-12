// #EX_BEGIN
#include "CVector.h"
// #EX_END

void CVector::move(CVector src){
  uint8_t * tmp = m_Data;
  m_Data = src.m_Data;
  src.m_Data = tmp;

  m_Used = src.m_Used;
  m_Cap = src.m_Cap;
}

CVector::CVector ()
: m_Data (nullptr)
, m_Cap (0)
, m_Used (0)
{}

CVector::~CVector () { 
  delete [] m_Data;
}

CVector::CVector ( const CVector &src ) 
: m_Data (nullptr)
, m_Cap (src.m_Used)
, m_Used (src.m_Used)
{
  if ( !src.Empty())
  {
    m_Data = new uint8_t [m_Cap];
    for ( uint32_t i = 0; i < m_Used; i ++ ){
      m_Data [i] = src.m_Data [i];
    }
  }
}
CVector &CVector::operator= (const CVector &src){
  if (this == &src)
    return *this;
  move(src);
  return *this;
}


void CVector::PushBack ( uint8_t val ) {
  if ( m_Used >= m_Cap ){
    m_Cap = 100 + m_Cap * 2;
    uint8_t * tmp = new uint8_t [m_Cap];
    if (!tmp)
      return;
    for ( uint32_t i = 0; i < m_Used; i++ ){
      tmp [i] = m_Data [i];
    }
      delete [] m_Data;
      m_Data = tmp;
  }
  m_Data [m_Used++] = val;
}

bool CVector::Empty () const {
  return !m_Data;
}

uint32_t CVector::Size () const {
  return m_Used; 
}
uint32_t CVector::MaxSize () const {
  return m_Cap;
}

uint8_t &CVector::operator [] (const uint32_t pos ){
  return m_Data[pos];
}

void CVector::ShrinkToFit(){
  if (m_Used == 0){
    delete [] m_Data;
    m_Data = nullptr;
    m_Cap = m_Used;
    return;
  }
  uint8_t * tmp = new uint8_t [m_Used];
  for ( uint32_t i = 0; i < m_Used; i++ ){
    tmp[i] = m_Data[i];
  }
  delete[] m_Data;
  m_Data = tmp;
  m_Cap = m_Used;
}

void CVector::ShrinkToFit( uint32_t pos ){
  m_Used = pos;
  ShrinkToFit();
}
// #EX_BEGIN
void CVector::print() const {
  cout << "{ ";
  for ( uint32_t i = 0; i < m_Used; i++ ){
    cout << (uint) m_Data[i] << " ";
  }
  cout << "}" << endl;
}
// #EX_END
