#include <iostream>
using namespace std;

class A
 {
   public:
             A ( int x ) { m_X = x; }
    virtual ~A ( void ) { } 
    friend ostream & operator << ( ostream & os, const A & x ) 
     { return os << x . m_X; }
   private: 
  //  when we have friend, those are not members. So they neither are 
  // inhertied, nor have access specifiers.. They are just friends
  // and can be declared anywhere in the class..
  // that is why it doesn't matter, if we have print in public or private
     friend ostream & print ( ostream &os, const A & x){
       return os << x.m_X;
     }
    int m_X;
 };

class B : public A
 {
   public:
          B ( int x, int y ) : A ( x ) { m_Y = y; }
    friend ostream & operator << ( ostream & os, const B & x ) 
     { print(cout, (const A &) x ); return os << x . m_Y; }
   private: 
    int m_Y;
 };

void foo ( A val )
 {
  //  cout << val;
 }

int main ( void )
 {
   B test ( 68, 86 );

   foo ( test );
   return 0;
 }