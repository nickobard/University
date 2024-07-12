#ifndef __PROGTEST__
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <stdexcept>
using namespace std;
#endif /* __PROGTEST__ */

//=================================================================================================
// a dummy exception class, keep this implementation
class InvalidDateException : public invalid_argument
{
  public:
    InvalidDateException ( )
      : invalid_argument ( "invalid date or format" )
    {
    }
};
//=================================================================================================
// date_format manipulator - a dummy implementation. Keep this code unless you implement your
// own working manipulator.
ios_base & ( * date_format ( const char * fmt ) ) ( ios_base & x )
{
  return [] ( ios_base & ios ) -> ios_base & { return ios; };
}
//=================================================================================================
class CDate
{
  public:
  // constructor
    CDate (int year, int month, int day);
  // arithmetic operators
    friend CDate operator+ ( const CDate &lhs, const int rhs);
    friend CDate operator+ ( const int &lhs, const CDate &rhs);
    friend CDate operator- ( const CDate &lhs, const int rhs);
    friend time_t operator- ( const CDate &lhs, const CDate &rhs);
    CDate &operator++ (void) ;
    CDate &operator-- (void) ;
    CDate operator++ (int) ;
    CDate operator-- (int) ;
  // comparison operators
    bool operator== (const CDate &rhs) const;
    bool operator!= (const CDate &rhs) const;
    bool operator<= (const CDate &rhs) const;
    bool operator>= (const CDate &rhs) const;
    bool operator<  (const CDate &rhs) const;
    bool operator>  (const CDate &rhs) const;
  // io operators
    friend ostream &operator<< (ostream &os, const CDate &date );
    friend istream &operator>> (istream &is, CDate &date );
  private:
    bool checkInput (int year, int month, int days) const;
    void initInput (int year, int month, int days);
    int maxDaysInMonth (const int month, const int year) const; 
    tm m_date {};
    time_t m_time;
};
//-----------------------------CONSTRUCTOR----------------------------------
CDate::CDate (int year, int month, int days)
  {
    if ( !checkInput(year,month,days))
      throw InvalidDateException();
    initInput(year,month,days);
  }
//-----------------------------HELP FUNCTIONS-------------------------------
void CDate::initInput (int year, int month, int days){
    m_date.tm_year = year  - 1900;
    m_date.tm_mon  = month -    1;
    m_date.tm_mday = days        ;
    m_time = mktime(&m_date);
}

bool CDate::checkInput (int year, int month, int days) const{
    if ( year  < 2000 || year  > 2030 
    ||   month <    1 || month >   12 
    ||   days  <    1 || days  > maxDaysInMonth(month, year) )
      return false;
    return true;
}

int CDate::maxDaysInMonth (const int month, const int year) const{
  if ( month == 2 && ! ( year % 4 ) )
    return 29;
  int daysInMonths [12] = {31,28,31,30,31,30,31,31,30,31,30,31};
  return daysInMonths[month - 1];
}

//-----------------------------ARITHMETIC OPERATORS-------------------------
CDate operator+ ( const CDate &lhs, const int rhs){
  tm tmp = lhs.m_date;
  tmp.tm_mday += rhs;
  mktime(&tmp);
  return {tmp.tm_year + 1900, tmp.tm_mon + 1, tmp.tm_mday};
}
CDate operator+ ( const int &lhs, const CDate rhs){
  return rhs + lhs;
}
CDate operator- ( const CDate &lhs, const int rhs){
  return lhs + (-rhs);
}
time_t operator- ( const CDate &lhs, const CDate &rhs){
    return lhs.m_time > rhs.m_time 
    ? (lhs.m_time - rhs.m_time)/86400 
    : (rhs.m_time - lhs.m_time)/86400;
} 
CDate &CDate::operator++ (void) {
  *this = *this + 1;
  return *this;
}
CDate &CDate::operator-- (void) {
  *this = *this - 1;
  return *this;
}
CDate CDate::operator++ (int) {
  CDate tmp = *this;
  ++*this;
  return tmp;
}
CDate CDate::operator-- (int) {
  CDate tmp = *this;
  --*this;
  return tmp;
}

//-----------------------------COMPARISON OPERATORS-------------------------
bool CDate::operator== (const CDate &rhs) const{
  return m_time == rhs.m_time;
}
bool CDate::operator!= (const CDate &rhs) const{
  return !(*this == rhs);
}
bool CDate::operator<= (const CDate &rhs) const{
  return m_time == rhs.m_time || m_time < rhs.m_time;
}

bool CDate::operator>= (const CDate &rhs) const{
  return m_time == rhs.m_time || m_time > rhs.m_time;
}
bool CDate::operator<  (const CDate &rhs) const{
  return ! (*this >= rhs);
}
bool CDate::operator>  (const CDate &rhs) const{
  return ! (*this <= rhs);
}
//-----------------------------IO OPERATORS---------------------------------

ostream &operator<< (ostream &os, const CDate &date ){
  os << date.m_date.tm_year + 1900 << '-'
     << setfill('0') << setw(2)
     << date.m_date.tm_mon  +    1 << '-' 
     << setw(2) 
     << date.m_date.tm_mday ;
  return os;
}
istream &operator>> (istream &is, CDate &date ){
  int year, month, day;
  char dummy1, dummy2;
  if ( ! (is >> year >> dummy1 >> month >> dummy2 >> day)
  ||   dummy1 != '-' 
  ||   dummy2 != '-' 
  ||   ! date.checkInput(year, month, day)){
    is.setstate(ios::failbit);
    return is;
  }
  date.initInput(year,month,day);
  return is;
}


#ifndef __PROGTEST__
//=============================MAIN=========================================
int main ( void )
{
  ostringstream oss;
  istringstream iss;

//-----------------------------OWN ASSERTS----------------------------------
CDate f (2000,1,1);
cout << f << endl;
f = f  + 10;
cout << f << endl;

//-----------------------------PROGTEST ASSERTS-----------------------------

  CDate a ( 2000, 1, 2 );
  CDate b ( 2010, 2, 3 );
  CDate c ( 2004, 2, 10 );
  oss . str ("");
  oss << a;
  assert ( oss . str () == "2000-01-02" );
  oss . str ("");
  oss << b;
  assert ( oss . str () == "2010-02-03" );
  oss . str ("");
  oss << c;
  assert ( oss . str () == "2004-02-10" );
  a = a + 1500;
  cout << a << endl;
  oss . str ("");
  oss << a;
  assert ( oss . str () == "2004-02-10" );
  b = b - 2000;
  oss . str ("");
  oss << b;
  assert ( oss . str () == "2004-08-13" );
  assert ( b - a == 185 );
  assert ( ( b == a ) == false );
  assert ( ( b != a ) == true );
  assert ( ( b <= a ) == false );
  assert ( ( b >= a ) == true );
  assert ( ( b < a ) == false );
  assert ( ( b >= a ) == true );
  assert ( ( b > a ) == true );
  assert ( ( c == a ) == true );
  assert ( ( c != a ) == false );
  assert ( ( c <= a ) == true );
  assert ( ( c < a ) == false );
  assert ( ( c >= a ) == true );
  assert ( ( c > a ) == false );
  a = ++c;
  oss . str ( "" );
  oss << a << " " << c;
  assert ( oss . str () == "2004-02-11 2004-02-11" );
  a = --c;
  oss . str ( "" );
  oss << a << " " << c;
  assert ( oss . str () == "2004-02-10 2004-02-10" );
  a = c++;
  oss . str ( "" );
  oss << a << " " << c;
  assert ( oss . str () == "2004-02-10 2004-02-11" );
  a = c--;
  oss . str ( "" );
  oss << a << " " << c;
  assert ( oss . str () == "2004-02-11 2004-02-10" );
  iss . clear ();
  iss . str ( "2015-09-03" );
  assert ( ( iss >> a ) );
  oss . str ("");
  oss << a;
  assert ( oss . str () == "2015-09-03" );
  a = a + 70;
  oss . str ("");
  oss << a;
  assert ( oss . str () == "2015-11-12" );

  CDate d ( 2000, 1, 1 );
  try
  {
    CDate e ( 2000, 32, 1 );
    assert ( "No exception thrown!" == nullptr );
  }
  catch ( ... )
  {
  }
  iss . clear ();
  iss . str ( "2000-12-33" );
  assert ( ! ( iss >> d ) );
  oss . str ("");
  oss << d;
  assert ( oss . str () == "2000-01-01" );
  iss . clear ();
  iss . str ( "2000-11-31" );
  assert ( ! ( iss >> d ) );
  oss . str ("");
  oss << d;
  assert ( oss . str () == "2000-01-01" );
  iss . clear ();
  iss . str ( "2000-02-29" );
  assert ( ( iss >> d ) );
  oss . str ("");
  oss << d;
  assert ( oss . str () == "2000-02-29" );
  iss . clear ();
  iss . str ( "2001-02-29" );
  assert ( ! ( iss >> d ) );
  oss . str ("");
  oss << d;
  assert ( oss . str () == "2000-02-29" );
  /*
*/
  //-----------------------------------------------------------------------------
  // bonus test examples
  //-----------------------------------------------------------------------------
  /*
  CDate f ( 2000, 5, 12 );
  oss . str ("");
  oss << f;
  assert ( oss . str () == "2000-05-12" );
  oss . str ("");
  oss << date_format ( "%Y/%m/%d" ) << f;
  assert ( oss . str () == "2000/05/12" );
  oss . str ("");
  oss << date_format ( "%d.%m.%Y" ) << f;
  assert ( oss . str () == "12.05.2000" );
  oss . str ("");
  oss << date_format ( "%m/%d/%Y" ) << f;
  assert ( oss . str () == "05/12/2000" );
  oss . str ("");
  oss << date_format ( "%Y%m%d" ) << f;
  assert ( oss . str () == "20000512" );
  oss . str ("");
  oss << date_format ( "hello kitty" ) << f;
  assert ( oss . str () == "hello kitty" );
  oss . str ("");
  oss << date_format ( "%d%d%d%d%d%d%m%m%m%Y%Y%Y%%%%%%%%%%" ) << f;
  assert ( oss . str () == "121212121212050505200020002000%%%%%" );
  oss . str ("");
  oss << date_format ( "%Y-%m-%d" ) << f;
  assert ( oss . str () == "2000-05-12" );
  iss . clear ();
  iss . str ( "2001-01-1" );
  assert ( ! ( iss >> f ) );
  oss . str ("");
  oss << f;
  assert ( oss . str () == "2000-05-12" );
  iss . clear ();
  iss . str ( "2001-1-01" );
  assert ( ! ( iss >> f ) );
  oss . str ("");
  oss << f;
  assert ( oss . str () == "2000-05-12" );
  iss . clear ();
  iss . str ( "2001-001-01" );
  assert ( ! ( iss >> f ) );
  oss . str ("");
  oss << f;
  assert ( oss . str () == "2000-05-12" );
  iss . clear ();
  iss . str ( "2001-01-02" );
  assert ( ( iss >> date_format ( "%Y-%m-%d" ) >> f ) );
  oss . str ("");
  oss << f;
  assert ( oss . str () == "2001-01-02" );
  iss . clear ();
  iss . str ( "05.06.2003" );
  assert ( ( iss >> date_format ( "%d.%m.%Y" ) >> f ) );
  oss . str ("");
  oss << f;
  assert ( oss . str () == "2003-06-05" );
  iss . clear ();
  iss . str ( "07/08/2004" );
  assert ( ( iss >> date_format ( "%m/%d/%Y" ) >> f ) );
  oss . str ("");
  oss << f;
  assert ( oss . str () == "2004-07-08" );
  iss . clear ();
  iss . str ( "2002*03*04" );
  assert ( ( iss >> date_format ( "%Y*%m*%d" ) >> f ) );
  oss . str ("");
  oss << f;
  assert ( oss . str () == "2002-03-04" );
  iss . clear ();
  iss . str ( "C++09format10PA22006rulez" );
  assert ( ( iss >> date_format ( "C++%mformat%dPA2%Yrulez" ) >> f ) );
  oss . str ("");
  oss << f;
  assert ( oss . str () == "2006-09-10" );
  iss . clear ();
  iss . str ( "%12%13%2010%" );
  assert ( ( iss >> date_format ( "%%%m%%%d%%%Y%%" ) >> f ) );
  oss . str ("");
  oss << f;
  assert ( oss . str () == "2010-12-13" );

  CDate g ( 2000, 6, 8 );
  iss . clear ();
  iss . str ( "2001-11-33" );
  assert ( ! ( iss >> date_format ( "%Y-%m-%d" ) >> g ) );
  oss . str ("");
  oss << g;
  assert ( oss . str () == "2000-06-08" );
  iss . clear ();
  iss . str ( "29.02.2003" );
  assert ( ! ( iss >> date_format ( "%d.%m.%Y" ) >> g ) );
  oss . str ("");
  oss << g;
  assert ( oss . str () == "2000-06-08" );
  iss . clear ();
  iss . str ( "14/02/2004" );
  assert ( ! ( iss >> date_format ( "%m/%d/%Y" ) >> g ) );
  oss . str ("");
  oss << g;
  assert ( oss . str () == "2000-06-08" );
  iss . clear ();
  iss . str ( "2002-03" );
  assert ( ! ( iss >> date_format ( "%Y-%m" ) >> g ) );
  oss . str ("");
  oss << g;
  assert ( oss . str () == "2000-06-08" );
  iss . clear ();
  iss . str ( "hello kitty" );
  assert ( ! ( iss >> date_format ( "hello kitty" ) >> g ) );
  oss . str ("");
  oss << g;
  assert ( oss . str () == "2000-06-08" );
  iss . clear ();
  iss . str ( "2005-07-12-07" );
  assert ( ! ( iss >> date_format ( "%Y-%m-%d-%m" ) >> g ) );
  oss . str ("");
  oss << g;
  assert ( oss . str () == "2000-06-08" );
  iss . clear ();
  iss . str ( "20000101" );
  assert ( ( iss >> date_format ( "%Y%m%d" ) >> g ) );
  oss . str ("");
  oss << g;
  assert ( oss . str () == "2000-01-01" );
*/
  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
