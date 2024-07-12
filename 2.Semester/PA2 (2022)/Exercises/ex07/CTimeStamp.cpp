//  #EX_BEGIN
#include "CTimeStamp.h"
//  #EX_END

CTimeStamp::CTimeStamp(int year, int month,   int day,
                       int hour, int minutes, int seconds )
  : c_year (year)
  , c_month (month)
  , c_day (day)

  , c_hour (hour)
  , c_minutes (minutes)
  , c_seconds (seconds)
  {}

ostream &operator<< (ostream &os, const CTimeStamp & t){
  cout << setfill(' ') 
       << t.c_year  << "." << setw(2) 
       << t.c_month << "." << setw(2) 
       << t.c_day   << " " << setfill('0') << setw(2)
       << t.c_hour  << "." << setw(2) 
       << t.c_minutes << "." << setw(2) 
       << t.c_seconds;
   return os; 
}
bool CTimeStamp::operator== (const CTimeStamp & rhs) const{
  return c_year    == rhs.c_year    &&
         c_month   == rhs.c_month   &&
         c_day     == rhs.c_day     &&
         c_hour    == rhs.c_hour    &&
         c_minutes == rhs.c_minutes &&
         c_seconds == rhs.c_seconds   ;
}

bool CTimeStamp::operator!= (const CTimeStamp & rhs) const{
  return !(*this == rhs);
}

bool CTimeStamp::operator> (const CTimeStamp & rhs) const{
  if ( c_year > rhs.c_year )
    {return true ;}
  else if (c_year != rhs.c_year)
    {return false;}
  if ( c_month > rhs.c_month )
    {return true ;}
  else if ( c_month != rhs.c_month)
    {return false;}
  if ( c_day > rhs.c_day )
    {return true ;}
  else if ( c_day != rhs.c_day)
    {return false;}

  return ( c_hour * 3600 + c_minutes * 60 + c_seconds ) >
         ( rhs.c_hour * 3600 + rhs.c_minutes * 60 + rhs.c_seconds );
}
bool CTimeStamp::operator< (const CTimeStamp & rhs) const{
  return !(*this > rhs || *this == rhs) ? true : false;
}
bool CTimeStamp::operator<= (const CTimeStamp & rhs) const{
  return !(*this > rhs) ? true : false;
}
bool CTimeStamp::operator>= (const CTimeStamp & rhs) const{
  return !(*this < rhs) ? true : false;
}
