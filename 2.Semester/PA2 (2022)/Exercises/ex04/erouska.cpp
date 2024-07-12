#ifndef __PROGTEST__
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <array>
#include <cassert>
using namespace std;
#endif /* __PROGTEST__ */

//----------------------CTIMESTAMP-------------------------------------------------------------------//
/*
 * Class should store date and time. Also it should allow ==, <= and >=
 * operations to control whether one timestamp is before or after
 * then another timestamp
 */
class CTimeStamp
{
  public:
    //Constructor
    //Using contructor initializer list. That means the value is directly assigned to the object members, without unnecessary copying.
    CTimeStamp(int year, int month, int day,
               int hour, int minutes, int seconds )
    : c_year (year), c_month (month), c_day (day),
      c_hour (hour), c_minutes (minutes), c_seconds (seconds)
    {
    }
    //Interface
    // Compare operations using operation overloading. Using member functions and reference, so no copying will be made
    // using pointers to const, becuase we don't intend to change 
    // passed CTimeStamp ojbect, nor the this object, using const member
    // functions
    bool operator == (const CTimeStamp &) const;
    bool operator != (const CTimeStamp &) const;
    bool operator <  (const CTimeStamp &) const;
    bool operator >  (const CTimeStamp &) const;
    bool operator <= (const CTimeStamp &) const;
    bool operator >= (const CTimeStamp &) const;
    // Incovnenient using of printing out. Cannot be chained with cout.
    // Anyway, this function can be void, but it is good practice to make it return reference to the same object it used, allowing us to chain thic member function.
    // Because we use const method, the this pointer will bi to the const object, there fore it should return const object, thus we have const at the beginning of our CCtimeStamp method declaration
    const CTimeStamp &printTimestamp() const;
    // The problem of this is the order. Implicitly the lhs is this pointer,
    // so supports only such syntax:
    // a << cout << endl; 
    // Which is very inconvenient, and we can do nothin with that order,
    // but use friend function, which allow us to take as lhs every object
    // we want
    ostream &operator << (ostream &) const;
    // frined implementation - allow any order of operands
    friend ostream &operator<< (ostream &, const CTimeStamp &);
  private:
    //members
    int c_year, c_month, c_day;
    int c_hour, c_minutes, c_seconds;

};
// member function, the problem is with the order, which is not allowed here
// the left hand side is always this pointer, but we want the cout be as lhs
ostream &CTimeStamp::operator<< (ostream &os) const{
  cout << setfill(' ') 
       << c_year  << "." << setw(2) 
       << c_month << "." << setw(2) 
       << c_day   << " " << setfill('0') << setw(2)
       << c_hour  << "." << setw(2) 
       << c_minutes << "." << setw(2) 
       << c_seconds;
   return os; 
}
//frine function which allows us to print it using any specified order
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
         c_seconds == rhs.c_seconds ? true : false;
}

bool CTimeStamp::operator!= (const CTimeStamp & rhs) const{
  return !(*this == rhs);
}

bool CTimeStamp::operator> (const CTimeStamp & rhs) const{
  if ( c_year > rhs.c_year )
    {return true; }
  else if (c_year != rhs.c_year)
    {return false;}
  if ( c_month > rhs.c_month )
    {return true; }
  else if ( c_month != rhs.c_month)
    {return false;}
  if ( c_day > rhs.c_day )
    {return true; }
  else if ( c_day != rhs.c_day)
    {return false;}

  if ( ( c_hour * 3600 + c_minutes * 60 + c_seconds )
          > ( rhs.c_hour * 3600 + rhs.c_minutes * 60 + rhs.c_seconds ) )
    {return true; }
  else
    {return false;}

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
const CTimeStamp &CTimeStamp::printTimestamp () const{
  cout << *this;
  return *this;
}
//--------------------------CCONTACT---------------------------------------------------------------//
class CContact
{
  public:
    //Construktor
    // We can use the const with our timestamp parameter, because when we want to pass existing object, we don't want it to be changed or something.
    // But it is unnecessary when we don't use the constructor body.
    // It is just isn't used at all, because we anyway assing timestamp object to our own c_timestamp object, where typecasting is implicit to nonconst 
    CContact (/*const*/ CTimeStamp timestamp, int p_num1, int p_num2 )
    : c_timestamp (timestamp), c_pnum1 (p_num1), c_pnum2 (p_num2)
    {
    }
    // functions to print whole contact, same as in the previous class
    const CContact &printAll() const;
    friend ostream &operator<< (ostream &, const CContact &);
    // Now we may want to print timestamp of some contact.
    // For that we have getter - get_time, which returns copy of the c_timestamp
    int get_num1() const {return c_pnum1; }
    int get_num2() const {return c_pnum2; }
    // We dont want to copy, just read, so therefore we use constant and reference
    const CTimeStamp &get_time() const { return c_timestamp; }
  private:
    //member functions
    //members
    CTimeStamp c_timestamp;
    int c_pnum1;
    int c_pnum2;

};
const CContact &CContact::printAll() const{
  cout << c_timestamp << ": " << c_pnum1 << " " << c_pnum2 << endl;
  return  *this;
}
  // To make it more convenient for the user, we don't need to print everything, because user already usin getter print timestamp if it is necessary, or use printAll() method
ostream &operator<< (ostream &os, const CContact &contact){
  os << /*contact.c_timestamp << ": " <<*/ contact.c_pnum1 << " " << contact.c_pnum2;
  return os;
}


//---------------------------CEFACEMASK--------------------------------------------------------------//
class CEFaceMask
{
  // TODO
  public:
  // interface
  // This class works only as interface and doens't have any constructo
  // except the synthesized default contructor
  CEFaceMask &addContact( const CContact & );
  const CEFaceMask &printContacts () const;
  friend ostream &operator<< (ostream &, const CEFaceMask  &);
  friend ostream &operator<< (ostream &, const vector<int> &);
  // member functions for returning infected
  vector<int> listContacts (const int) const;
  vector<int> listContacts (const int, const CTimeStamp &,const CTimeStamp & ) const;
  private:
  bool is_unique(const int num, const vector<int> & ) const;
  vector<CContact> c_contacts;
};

CEFaceMask & CEFaceMask::addContact ( const CContact &contact ){
  c_contacts.push_back(contact);
  return *this;
}

const CEFaceMask &CEFaceMask::printContacts () const{
  for ( const auto &a : c_contacts )
  {
    cout << a.get_time() << ": " << a << endl;
  }
  return *this;
}
ostream &operator<< (ostream &os, const CEFaceMask & db){
  for ( const auto &a : db.c_contacts){
    cout << a.get_time() << ": " << a << endl;
  }
  return os;
}

ostream &operator<< (ostream &os, const vector<int> & list){
  for (const auto &a : list){
    cout << a << endl;
  }
  return os;
}
// used to find dupclicates in the infected contact list.
bool CEFaceMask::is_unique (const int num, const vector<int> & infected) const{
  for (const auto &a : infected)
  {
    if (a == num) return false;
  }
  return true;
}
// Use current contact list and find every ifected using only phone number.
// Uses current object.
vector<int> CEFaceMask::listContacts (const int phone_num) const{
  vector<int> infected;
  for (const auto &a : c_contacts){
    // if first num is equal to request, then the second num2 is our result
    if ( a.get_num1() == phone_num ){
      if (a.get_num2() == phone_num ) {continue;}
      if (is_unique( a.get_num2 (), infected))
        infected.push_back(a.get_num2());}
    else if (a.get_num2() == phone_num){
      if (is_unique(a.get_num1(), infected))
        infected.push_back(a.get_num1());}
  }
  return infected;
}
// fucntion to find infected from one date to another date
// Creates new CEFFaseMask object, where stores all infected in the preffered time period, then list it.
vector<int> CEFaceMask::listContacts(int phone_num, const CTimeStamp &time1,const CTimeStamp &time2) const
{
  CEFaceMask filtered;
  for ( const auto a : c_contacts)
  {
    if (a.get_time() >= time1 && a.get_time() <= time2)
      filtered.c_contacts.push_back(a);
  }
  return filtered.listContacts(phone_num);
}
//-----------------------------------------------------------------------------------------//
#ifndef __PROGTEST__
int main ()
{
//Own asserts
CTimeStamp a (2021, 1, 10, 12, 40, 10), b (2021, 1, 10, 12, 40, 10);
CTimeStamp c (2022, 1, 10, 12, 40, 10 );
a << cout << endl; //using method function without order
cout << a << endl; //using frined function with our own order
CContact c3 (a, 123123123, 321321321);
cout << c3 << endl;
cout << c3.get_time() << endl;
  /*
a.printTimestamp();
assert ( a == b );
assert ( !(a != b));
assert ( a != c );
assert ( c > a );
assert ( ! (a > b));
assert (!(a < b));
assert (a < c);
assert ( a>=b && a<=b );
CContact c1 ( CTimeStamp (2022,1,10,12,40,10), 123123123, 123532523);
c1.printContact();
CEFaceMask db;
db.addContact( CContact ( CTimeStamp (2022,1,10,12,40,10), 123123123, 123532523));
db.addContact( CContact ( CTimeStamp (2022,1,10,12,40,10), 123123123, 123532523));
db.addContact( CContact ( CTimeStamp (2022,1,10,12,40,10), 123123123, 123532523));
db.addContact( CContact ( CTimeStamp (2022,1,10,12,40,10), 123123123, 123532523));
db.printContacts();
db.addContact(CContact(a,234234123,523567435));
db.printContacts();
db.listContacts(123123123);
*/
  CEFaceMask test;

  test . addContact ( CContact ( CTimeStamp ( 2021, 1, 10, 12, 40, 10 ), 123456789, 999888777 ) );
  test . addContact ( CContact ( CTimeStamp ( 2021, 1, 12, 12, 40, 10 ), 123456789, 111222333 ) )
       . addContact ( CContact ( CTimeStamp ( 2021, 2, 5, 15, 30, 28 ), 999888777, 555000222 ) );
  test . addContact ( CContact ( CTimeStamp ( 2021, 2, 21, 18, 0, 0 ), 123456789, 999888777 ) );
  test . addContact ( CContact ( CTimeStamp ( 2021, 1, 5, 18, 0, 0 ), 123456789, 456456456 ) );
  test . addContact ( CContact ( CTimeStamp ( 2021, 2, 1, 0, 0, 0 ), 123456789, 123456789 ) );
  assert ( test . listContacts ( 123456789 ) == (vector<int> {999888777, 111222333, 456456456}) );
  assert ( test . listContacts ( 999888777 ) == (vector<int> {123456789, 555000222}) );
  assert ( test . listContacts ( 191919191 ) == (vector<int> {}) );
  assert ( test . listContacts ( 123456789, CTimeStamp ( 2021, 1, 5, 18, 0, 0 ), CTimeStamp ( 2021, 2, 21, 18, 0, 0 ) ) == (vector<int> {999888777, 111222333, 456456456}) );
  assert ( test . listContacts ( 123456789, CTimeStamp ( 2021, 1, 5, 18, 0, 1 ), CTimeStamp ( 2021, 2, 21, 17, 59, 59 ) ) == (vector<int> {999888777, 111222333}) );
  assert ( test . listContacts ( 123456789, CTimeStamp ( 2021, 1, 10, 12, 41, 9 ), CTimeStamp ( 2021, 2, 21, 17, 59, 59 ) ) == (vector<int> {111222333}) );
  //my own tests:
  test.printContacts();
  cout << test;
  return 0;
/*
  */
}
#endif /* __PROGTEST__ */
