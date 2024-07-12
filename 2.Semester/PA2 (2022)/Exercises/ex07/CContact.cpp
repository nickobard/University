//  #EX_BEGIN
#include "CContact.h"
//  #EX_END


CContact::CContact (const CTimeStamp &timestamp, int num1, int num2)
: m_Timestamp (timestamp)
, phones {num1, num2}
{}

ostream &operator<< (ostream &os, const CContact &rhs){
  os <<  rhs.phones.first << " " 
     << rhs.phones.second << " " 
     << rhs.m_Timestamp ;
  return os;    
}

bool CContact::eqNums() const {
  return phones.first == phones.second;
}
