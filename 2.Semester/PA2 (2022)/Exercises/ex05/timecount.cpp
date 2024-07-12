#ifndef __PROGTEST__
#include <iostream>
#include <iomanip>
#include <string>
#include <stdexcept>
using namespace std;

class CTimeTester;
#endif /* __PROGTEST__ */

class CTime
{
private:
    int m_Hour;
    int m_Minute;
    int m_Second;
public:
    // constructor, destructor
    CTime();
    CTime( int hour, int min);
    CTime( int hour, int min, int sec);
    // arithmetic operators
    CTime operator+ (const int sec) const ;
    friend CTime operator+ (const int sec, const CTime &rval) ;
    friend CTime operator- (const int sec, const CTime &rval) ;
    CTime operator- (const int sec) const ;
    CTime &operator+= ( const int sec) ;
    CTime &operator-= ( const int sec) ;
    CTime &operator++ () ;
    CTime &operator-- () ;
    CTime operator++ (int) ;
    CTime operator-- (int) ;

    friend int operator- (const CTime &a, const CTime &b);
    // comparison operators
    friend bool operator== (const CTime &a, const CTime &b);
    friend bool operator!= (const CTime &a, const CTime &b);
    friend bool operator<= (const CTime &a, const CTime &b);
    friend bool operator>= (const CTime &a, const CTime &b);
    friend bool operator<  (const CTime &a, const CTime &b);
    friend bool operator>  (const CTime &a, const CTime &b);

    // output operator
    friend ostream &operator << ( ostream &os, const CTime &time);
    friend class ::CTimeTester;
};
//-----------------------CONSTRUCTOR--------------------------------------- 

CTime::CTime ()
: m_Hour(0),
  m_Minute(0),
  m_Second(0)
{}
CTime::CTime( int hour, int min )
: m_Hour (hour),
  m_Minute (min),
  m_Second (0)
  {
      if ( m_Hour   > 23 
        || m_Hour   <  0
        || m_Minute > 59
        || m_Minute <  0 )
        throw invalid_argument("Invalid hour and minutes arguments.");
  }
CTime::CTime( int hour, int min, int sec)
: m_Hour(hour),
  m_Minute(min),
  m_Second(sec)
{
    if ( m_Hour   > 23 
      || m_Hour   <  0
      || m_Minute > 59
      || m_Minute <  0
      || m_Second <  0
      || m_Second > 59 )
        throw invalid_argument("Invalid hour, minutes and seconds arguments.");   
}
//-----------------------OUTPUT-------------------------------------------- 

ostream &operator << ( ostream &os, const CTime &time){
    os << setfill(' ')  << setw(2)
       << time.m_Hour   << ":" 
       << setfill('0')  << setw(2)
       << time.m_Minute << ":" << setw(2)
       << time.m_Second;
    return os;
}
//-----------------------ARITHMETIC---------------------------------------- 
CTime operator+ (const int sec, const CTime &rval) {
    return rval + sec;
}
CTime operator- (const int sec, const CTime &rval) {
    return rval - sec;
}


CTime CTime::operator+ (const int sec) const {
    int seconds = m_Hour * 3600 + m_Minute * 60 + m_Second;
    seconds += 86400 + sec % 86400 ;
    seconds %= 86400; 
    return CTime(seconds / 3600, seconds / 60 % 60, seconds % 60);
}

CTime CTime::operator- (const int sec) const {
    return *this + (-sec);
}

CTime &CTime::operator+= ( const int sec) {
    return *this = *this + sec;
}
CTime &CTime::operator-= ( const int sec) {
    return *this = *this - sec;
}

CTime &CTime::operator++ (){
    return *this += 1;
}

CTime &CTime::operator-- (){
    return *this -= 1;
}

CTime CTime::operator++ (int){
    CTime ret = *this;
    ++*this;
    return ret; 
}

CTime CTime::operator-- (int){
    CTime ret = *this;
    --*this;
    return ret; 
}


int operator- (const CTime &a, const CTime &b){
    int seconds = ( a.m_Hour * 3600 + a.m_Minute * 60 + a.m_Second  ) - 
                  ( b.m_Hour * 3600 + b.m_Minute * 60 + b.m_Second  ) ;
    seconds = seconds < 0 ? -seconds : seconds ;
    return seconds > 86400 / 2 ? 86400 - seconds : seconds ; 
}

//-----------------------COMPARISON---------------------------------------- 

bool operator== (const CTime &a, const CTime &b){
    if ( a.m_Hour == b.m_Hour
      && a.m_Minute == b.m_Minute
      && a.m_Second == b.m_Second )
        return true;
    return false;
}
bool operator!= (const CTime &a, const CTime &b){
    return ! ( a == b );
}
bool operator<= (const CTime &a, const CTime &b){
    if ( a == b 
    || ( a.m_Hour * 3600 + a.m_Minute * 60 + a.m_Second < 
         b.m_Hour * 3600 + b.m_Minute * 60 + b.m_Second ))
         return true;
    return false;
}
bool operator>= (const CTime &a, const CTime &b){
    if ( a == b 
    || ( a.m_Hour * 3600 + a.m_Minute * 60 + a.m_Second > 
         b.m_Hour * 3600 + b.m_Minute * 60 + b.m_Second ))
         return true;
    return false;
}
bool operator<  (const CTime &a, const CTime &b){
    return  !(a >= b);
}
bool operator>  (const CTime &a, const CTime &b){
    return !(a <= b);
}


#ifndef __PROGTEST__
struct CTimeTester
{
    static bool test ( const CTime & time, int hour, int minute, int second )
    {
        return time.m_Hour == hour 
            && time.m_Minute == minute
            && time.m_Second == second;
    }
};

#include <cassert>
#include <sstream>

int main ()
{
    //-----------------------OWN ASSERTS---------------------------------- 
    int sec =  -3600 * 100;
    CTime f1;
    cout << f1 - sec << endl;
    /*
    CTime s1 ;
    CTime s2 ( 12, 30);
    s1 = s2 - 3600 * 100;
    cout << s1 << endl;
    CTime s3;
    s3--;
    cout << s3 << endl;
    cout << CTime(13,30) - CTime(12,30) << endl;
    CTime s4;
    CTime s5(23,59,59);
    cout << s4 - s5 << endl;
    s1 = 3600 + s2;
    cout << s1 << endl;
    */
    //-----------------------PROGTEST ASSERTS-------------------------------
    CTime a { 12, 30 };
    assert( CTimeTester::test( a, 12, 30, 0 ) );

    CTime b { 13, 30 };
    assert( CTimeTester::test( b, 13, 30, 0 ) );


    assert( b - a == 3600 );

    assert( CTimeTester::test( a + 60, 12, 31, 0 ) );
    assert( CTimeTester::test( a - 60, 12, 29, 0 ) );

    assert( a < b );
    assert( a <= b );
    assert( a != b );
    assert( !( a > b ) );
    assert( !( a >= b ) );
    assert( !( a == b ) );

    while ( ++a != b );
    assert( a == b );

    std::ostringstream output;
    assert( static_cast<bool>( output << a ) );
    assert( output.str() == "13:30:00" );

    assert( a++ == b++ );
    assert( a == b );

    assert( --a == --b );
    assert( a == b );

    assert( a-- == b-- );
    assert( a == b );

    /*
    */
    return 0;
}
#endif /* __PROGTEST__ */
