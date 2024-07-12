#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <cassert>
#include <iostream> 
#include <iomanip> 
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <memory>
using namespace std;
#endif /* __PROGTEST__ */

class CVATRegister
{
  struct TCompany{
    string m_origName;
    string m_origAddr;
    string m_id;
    unsigned int m_audit = 0;
    string m_lowName;
    string m_lowAddr;
  };
  public:
                  CVATRegister   ( void );
                  ~CVATRegister  ( void );
    bool          newCompany     ( const string    & name,
                                   const string    & addr,
                                   const string    & taxID );
    bool          cancelCompany  ( const string    & name,
                                   const string    & addr );
    bool          cancelCompany  ( const string    & taxID );
    bool          invoice        ( const string    & taxID,
                                   unsigned int      amount );
    bool          invoice        ( const string    & name,
                                   const string    & addr,
                                   unsigned int      amount );
    bool          audit          ( const string    & name,
                                   const string    & addr,
                                   unsigned int    & sumIncome ) const;
    bool          audit          ( const string    & taxID,
                                   unsigned int    & sumIncome ) const;
    bool          firstCompany   ( string          & name,
                                   string          & addr ) const;
    bool          nextCompany    ( string          & name,
                                   string          & addr ) const;
    unsigned int  medianInvoice  ( void ) const;
  // debug
    void printCmpnies() const;
    void printCmpny(const list<TCompany>::iterator cmpny) const;
  private:
  // binary search methods
  vector<list<TCompany>::iterator>::const_iterator binSearch (const string &taxID) const;
  vector<list<TCompany>::iterator>::const_iterator binSearch (const string &name, const string &addr) const ;

  // comparators
  static bool cmpNames(const list<TCompany>::iterator element, const TCompany &value ){
    return ( element->m_lowName <  value.m_lowName 
        || ( element->m_lowName == value.m_lowName 
        &&   element->m_lowAddr <  value.m_lowAddr ) );
  }
  static bool cmpIDs(const list<TCompany>::iterator element, const string &value){
    return element->m_id < value;
  }
  // other helper methods
  string translow (string str) const;
  // members
  list<TCompany> c_cmpnies;
  vector<list<TCompany>::iterator> c_names;
  vector<list<TCompany>::iterator> c_ids;
  vector<unsigned int> c_invs;
};

//==================== IMPLEMENTATION ==================================//

//---------------------CONSTRUCTORS-------------------------------------//

//constructor & destructor
CVATRegister::CVATRegister() = default;
CVATRegister::~CVATRegister() = default;

//----------------------------------------------------------------------//

string CVATRegister::translow( string str) const{
    for ( char &c : str ){
    c = tolower(c);
  }
  return str;
}
//---------------------BINARY SEARCH------------------------------------//
vector<list<CVATRegister::TCompany>::iterator>::const_iterator CVATRegister::binSearch(const string &taxID)const{
  return lower_bound (c_ids.begin(),c_ids.end(),taxID,cmpIDs);
}
vector<list<CVATRegister::TCompany>::iterator>::const_iterator CVATRegister::binSearch(const string &name, const string &addr)const{
  TCompany value;
  value.m_lowName = name;
  value.m_lowAddr = addr;
  return lower_bound (c_names.begin(),c_names.end(),value,cmpNames);
}
//---------------------ADD/DELETE COMPANY--------------------------------//
bool CVATRegister::newCompany ( const string &name,
                                const string &addr,
                                const string &taxID ){
  string lowName = translow(name);
  string lowAddr = translow(addr);

  auto itID   = binSearch(taxID);
  auto itName = binSearch(lowName, lowAddr);
  if ((itID   != c_ids.end()     && (*itID  )->m_id      == taxID  )
  ||  (itName != c_names.end()   && (*itName)->m_lowName == lowName
                                 && (*itName)->m_lowAddr == lowAddr))
    return false;

  c_cmpnies.push_back({name,addr,taxID,0,lowName,lowAddr});
  c_ids . insert(itID,   --c_cmpnies.end());
  c_names.insert(itName, --c_cmpnies.end());
  return true;
}


bool CVATRegister::cancelCompany ( const string &name, const string &addr) {
  string lowName = translow(name);
  string lowAddr = translow(addr);

  auto itName = binSearch(lowName, lowAddr);
  if (itName != c_names.end() && (*itName)->m_lowName == lowName 
                                && (*itName)->m_lowAddr == lowAddr)
  {
    auto itID = binSearch((*itName)->m_id);

    c_cmpnies.erase(*itName);
    c_names.erase(itName);
    c_ids.erase(itID);
    return true;
  }
  return false;
}


bool CVATRegister::cancelCompany ( const string &taxID) {

  auto itID = binSearch(taxID);
  if (itID != c_ids.end() && (*itID)->m_id == taxID )
  {
    auto itName = binSearch((*itID)->m_lowName, (*itID)->m_lowAddr);

    c_cmpnies.erase(*itID);
    c_ids.erase(itID);
    c_names.erase(itName);
    return true;
  }
  return false;
}

//---------------------INVOICES-----------------------------------------//
bool CVATRegister::invoice (const string &name, const string &addr,
                            unsigned int inv){
  string lowName = translow(name);
  string lowAddr = translow(addr);

  auto itName = binSearch(lowName, lowAddr);

  if ( itName != c_names.end() && (*itName)->m_lowName == lowName
                               && (*itName)->m_lowAddr == lowAddr )
  {
    (*itName)->m_audit += inv;
    c_invs.push_back(inv);
    return true;
  }
  return false;
}


bool CVATRegister::invoice (const string &taxID,
                            unsigned int inv){
  auto itID = binSearch(taxID);

  if ( itID != c_ids.end() && (*itID)->m_id == taxID )
  {
    (*itID)->m_audit += inv;
    c_invs.push_back(inv);
    return true;
  }
  return false;
}

//---------------------AUDITS-----------------------------------------//
bool CVATRegister::audit ( const string    & name,
                           const string    & addr,
                           unsigned int    & sumIncome ) const{
  string lowName = translow(name);
  string lowAddr = translow(addr);

  auto itName = binSearch(lowName, lowAddr);

  if ( itName != c_names.end() && (*itName)->m_lowName == lowName
               && (*itName)->m_lowAddr == lowAddr)
  {
    sumIncome = (*itName)->m_audit;
    return true;
  }
return false;
}


bool CVATRegister::audit ( const string    & taxID,
                           unsigned int    & sumIncome ) const{
  auto itID = binSearch(taxID);

  if ( itID != c_ids.end() && (*itID)->m_id == taxID)
  {
    sumIncome = (*itID)->m_audit;
    return true;
  }
return false;
}

//---------------------MEDIAN-----------------------------------------//
unsigned int  CVATRegister::medianInvoice  ( void ) const{
  if (c_invs.empty()) return 0;

  vector<unsigned int> copy =  c_invs;
  sort (copy.begin(),copy.end());

  return copy[copy.size()/2];
}

//---------------------FIRST NEXT COMPANY------------------------------//
bool CVATRegister::firstCompany ( string &name, string &addr) const {
  if (c_names.empty()) return false;
  name = c_names.front()->m_origName;
  addr = c_names.front()->m_origAddr;
  return true;
}


bool CVATRegister::nextCompany ( string &name, string &addr) const {
  if (c_cmpnies.empty()) return false;
  string lowName = translow(name);
  string lowAddr = translow(addr);
  auto itName = binSearch(lowName,lowAddr);
  if ( itName != c_names.end() && (*itName)->m_lowName == lowName 
                               && (*itName)->m_lowAddr == lowAddr 
                               && ++itName != c_names.end())
  {
    name = (*itName)->m_origName;
    addr = (*itName)->m_origAddr;
    return true;
  }
  return false;
}

//---------------------DEBUG--------------------------------------------//
void CVATRegister::printCmpnies () const {
      cout << "Companies order:" << endl;
      for ( const auto a : c_names)
      {
        printCmpny(a);
      }
      cout << "taxID order:" << endl;
      for ( const auto a : c_ids)
      {
        printCmpny(a);
      }
    }


void CVATRegister::printCmpny ( const list<CVATRegister::TCompany>::iterator a) const {
  cout  << a->m_origName << " "
        << a->m_origAddr << " "
        << a->m_id   << " "
        << a->m_audit << " "
        << a->m_lowName  << " "
        << a->m_lowAddr << endl;
}

#ifndef __PROGTEST__
//==================== MAIN FUNCTION ===================================//

int               main           ( void )
{
  string name, addr;
  unsigned int sumIncome;
  
  //---------------------OWN TESTS-----------------------------------//
  CVATRegister s3;
  assert (s3.newCompany("a","b","1"));
  assert (!s3.newCompany("a","b","1"));
  assert (!s3.newCompany("a","b","1"));
  assert (!s3.newCompany("a","b","1"));
  assert (s3.newCompany("a","c","3"));
  assert (s3.newCompany("a","d","2"));
  assert (s3.newCompany("b","a","5"));
  assert (s3.newCompany("b","b","4"));

 CVATRegister a1;
  a1.newCompany("a","a","1");
  a1.newCompany("b","c","2");
  a1.newCompany("a","g","3");
  a1.newCompany("b","b","4");
  a1.newCompany("b","a","5");
  a1.newCompany("a","d","6");
  a1.newCompany("a","b","7");
  a1.newCompany("g","f","8");
  a1.newCompany("a","c","9");
  //a1.printCmpnies();


  CVATRegister s1;
  assert ( ! s1.audit ("a","b",sumIncome));
  assert ( ! s1.audit ("1",sumIncome));
  assert ( ! s1.invoice ( "a", "b", 666));
  assert ( ! s1.invoice ( "1", 666));
  assert ( ! s1.firstCompany( name, addr ));
  assert ( s1.medianInvoice () == 0 );
  string n1, n2;
  assert ( ! s1.nextCompany ( n1, n2 ));
  assert ( s1 . newCompany( "a", "b","1"));
  //s1.printCmpnies();
  assert ( s1 . cancelCompany ( "a", "b"));
  assert ( ! s1 . cancelCompany ( "a", "b"));
  assert ( s1 . newCompany ( "a", "b", "2"));
  assert ( !s1 . newCompany ( "a", "b", "2"));
  assert ( s1.audit ("a","b",sumIncome) && sumIncome == 0 );
  assert ( ! s1.audit ("1", sumIncome));
  assert ( ! s1.audit ("3", sumIncome));

  //---------------------SPEED TEST-----------------------------------//

CVATRegister b3;
  assert ( b3 . newCompany ( "ACME", "Kolejni", "abcdef" ) );
  assert ( b3 . newCompany ( "Dummy", "Kolejni", "123456" ) );
  assert ( b3 . newCompany ( "Dummy", "Thakurova", "ABCDEF" ) );
  b3.invoice ("abcdef", 100);
  b3.invoice ("abcdef", 100);
  b3.invoice ("DuMmy", "koleJnI", 100);
  b3.invoice ("DuMmy", "koleJnI", 100);
  b3.invoice ("DuMmy", "koleJnI", 100);

  for ( size_t i = 0; i < 2'000'000; ++i){
    b3.invoice ("abcdef", 100); // 5 seconds
    b3.invoice ("DuMmy", "koleJnI", 100); //5 seconds
    b3.audit ("abcdef", sumIncome); // 0 seconds
    b3.audit ("dummy","kolejni", sumIncome); // 0 seconds
    //b3.medianInvoice(); // 0 seconds
  }
  //---------------------PROGTEST-----------------------------------//
/*
  */
  CVATRegister b1;
  assert ( b1 . newCompany ( "ACME", "Thakurova", "666/666" ) );
  assert ( b1 . newCompany ( "ACME", "Kolejni", "666/666/666" ) );
  assert ( b1 . newCompany ( "Dummy", "Thakurova", "123456" ) );
  assert ( b1 . invoice ( "666/666", 2000 ) );
  //b1.printCmpnies();
  assert ( b1 . medianInvoice () == 2000 );
  assert ( b1 . invoice ( "666/666/666", 3000 ) );
  assert ( b1 . medianInvoice () == 3000 );
  assert ( b1 . invoice ( "123456", 4000 ) );
  assert ( b1 . medianInvoice () == 3000 );
  assert ( b1 . invoice ( "aCmE", "Kolejni", 5000 ) );
  assert ( b1 . medianInvoice () == 4000 );
  assert ( b1 . audit ( "ACME", "Kolejni", sumIncome ) && sumIncome == 8000 );
  assert ( b1 . audit ( "123456", sumIncome ) && sumIncome == 4000 );
  assert ( b1 . firstCompany ( name, addr ) && name == "ACME" && addr == "Kolejni" );
  assert ( b1 . nextCompany ( name, addr ) && name == "ACME" && addr == "Thakurova" );
  assert ( b1 . nextCompany ( name, addr ) && name == "Dummy" && addr == "Thakurova" );
  assert ( ! b1 . nextCompany ( name, addr ) );
  assert ( b1 . cancelCompany ( "ACME", "KoLeJnI" ) );
  assert ( b1 . medianInvoice () == 4000 );
  assert ( b1 . cancelCompany ( "666/666" ) );
  assert ( b1 . medianInvoice () == 4000 );
  assert ( b1 . invoice ( "123456", 100 ) );
  assert ( b1 . medianInvoice () == 3000 );
  assert ( b1 . invoice ( "123456", 300 ) );
  assert ( b1 . medianInvoice () == 3000 );
  assert ( b1 . invoice ( "123456", 200 ) );
  assert ( b1 . medianInvoice () == 2000 );
  assert ( b1 . invoice ( "123456", 230 ) );
  assert ( b1 . medianInvoice () == 2000 );
  assert ( b1 . invoice ( "123456", 830 ) );
  assert ( b1 . medianInvoice () == 830 );
  assert ( b1 . invoice ( "123456", 1830 ) );
  assert ( b1 . medianInvoice () == 1830 );
  assert ( b1 . invoice ( "123456", 2830 ) );
  assert ( b1 . medianInvoice () == 1830 );
  assert ( b1 . invoice ( "123456", 2830 ) );
  assert ( b1 . medianInvoice () == 2000 );
  assert ( b1 . invoice ( "123456", 3200 ) );
  assert ( b1 . medianInvoice () == 2000 );
  assert ( b1 . firstCompany ( name, addr ) && name == "Dummy" && addr == "Thakurova" );
  assert ( ! b1 . nextCompany ( name, addr ) );
  assert ( b1 . cancelCompany ( "123456" ) );
  assert ( ! b1 . firstCompany ( name, addr ) );

  CVATRegister b2;
  assert ( b2 . newCompany ( "ACME", "Kolejni", "abcdef" ) );
  assert ( b2 . newCompany ( "Dummy", "Kolejni", "123456" ) );
  assert ( ! b2 . newCompany ( "AcMe", "kOlEjNi", "1234" ) );
  assert ( b2 . newCompany ( "Dummy", "Thakurova", "ABCDEF" ) );
  assert ( b2 . medianInvoice () == 0 );
  assert ( b2 . invoice ( "ABCDEF", 1000 ) );
  assert ( b2 . medianInvoice () == 1000 );
  assert ( b2 . invoice ( "abcdef", 2000 ) );
  assert ( b2 . medianInvoice () == 2000 );
  assert ( b2 . invoice ( "aCMe", "kOlEjNi", 3000 ) );
  assert ( b2 . medianInvoice () == 2000 );
  assert ( ! b2 . invoice ( "1234567", 100 ) );
  assert ( ! b2 . invoice ( "ACE", "Kolejni", 100 ) );
  assert ( ! b2 . invoice ( "ACME", "Thakurova", 100 ) );
  assert ( ! b2 . audit ( "1234567", sumIncome ) );
  assert ( ! b2 . audit ( "ACE", "Kolejni", sumIncome ) );
  assert ( ! b2 . audit ( "ACME", "Thakurova", sumIncome ) );
  assert ( ! b2 . cancelCompany ( "1234567" ) );
  assert ( ! b2 . cancelCompany ( "ACE", "Kolejni" ) );
  assert ( ! b2 . cancelCompany ( "ACME", "Thakurova" ) );
  assert ( b2 . cancelCompany ( "abcdef" ) );
  assert ( b2 . medianInvoice () == 2000 );
  assert ( ! b2 . cancelCompany ( "abcdef" ) );
  assert ( b2 . newCompany ( "ACME", "Kolejni", "abcdef" ) );
  assert ( b2 . cancelCompany ( "ACME", "Kolejni" ) );
  assert ( ! b2 . cancelCompany ( "ACME", "Kolejni" ) );
  /*
*/
  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
