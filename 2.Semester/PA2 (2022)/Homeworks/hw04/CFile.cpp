// #EX_BEGIN
#include "CFile.h"
// #EX_END

CFile::CFile() = default;

CFile::~CFile() = default;
CFile::CFile( const CFile &src) = default;
CFile &CFile::operator= ( const CFile &rhs) = default;

bool CFile::seek ( uint32_t offset ) {
  if ( offset <= m_File.p_Data->Size() ){
    m_File.m_Pos = offset;
    return true;
  }
  else
    return false;
}

uint32_t CFile::read ( uint8_t * dst, uint32_t bytes ){
  uint32_t cnt = 0;
  if ( (m_File.m_Pos + bytes) > m_File.p_Data->Size())
    bytes = m_File.p_Data->Size() - m_File.m_Pos; // DANGEROUS !!!
  while (cnt < bytes){
    dst[cnt++] = (*m_File.p_Data)[m_File.m_Pos++];
  }
  return cnt;
}

uint32_t CFile::write ( const uint8_t * src, uint32_t bytes ){
  if ( !bytes || !src )
    return 0;
  uint32_t cnt = 0;
  if (!m_File.p_Data.unique())
    m_File.p_Data = make_Shared<CVector>(*m_File.p_Data);
  while (m_File.m_Pos < m_File.p_Data->Size() && cnt < bytes){
    (*m_File.p_Data)[m_File.m_Pos++] = src[cnt++];
  }
  while (cnt < bytes ){
    m_File.p_Data->PushBack(src[cnt++]);
    m_File.m_Pos++;
  }
  return cnt;
}

uint32_t CFile::fileSize ( void ) const{
  return m_File.p_Data->Size();
}
void CFile::addVersion (){
  m_Versions.Push(m_File);
}

void CFile::truncate ( void ) {
  if (!m_File.p_Data.unique() && m_File.m_Pos != m_File.p_Data->Size())                      
    m_File.p_Data = make_Shared<CVector>(*m_File.p_Data);
  m_File.p_Data->ShrinkToFit(m_File.m_Pos);
}

bool CFile::undoVersion(){
  if (m_Versions.Empty())
    return false;
  m_File = m_Versions.Top();
  m_Versions.Pop();
  return true;
}




