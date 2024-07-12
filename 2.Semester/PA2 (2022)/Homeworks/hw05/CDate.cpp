// #EX_BEGIN
#include "CDate.h"
// #EX_END

CDate::CDate (uint Y, uint M, uint D)
: m_Y(Y)
, m_M(M)
, m_D(D)
{}

bool operator< (const CDate &lhs, const CDate &rhs){
  if ( lhs.m_Y < rhs.m_Y )
    return true;
  if ( lhs.m_Y == rhs.m_Y ){
    if (lhs.m_M < rhs.m_M)
      return true;
    if (lhs.m_M == rhs.m_M)
      if (lhs.m_D < rhs.m_D)
        return true;
  }
  return false;
}

bool operator== (const CDate &lhs, const CDate &rhs){
  return lhs.m_Y == rhs.m_Y && 
         lhs.m_M == rhs.m_M && 
         lhs.m_D == rhs.m_D   ;
}

ostream &operator<< (ostream &os, const CDate &rhs){
  os << setfill('0') << setw(2) << rhs.m_D << "." 
                     << setw(2) << rhs.m_M << "."
                     << rhs.m_Y;
  return os;
}


