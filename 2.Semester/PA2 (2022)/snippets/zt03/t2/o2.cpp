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
    int m_X;
 };

class B : public A
 {
   public:
          B ( int x, int y ) : A ( x ) { m_Y = y; }
    friend ostream & operator << ( ostream & os, const B & x ) 
     { os << (const A &) x; return os << x . m_Y; }
   private: 
    int m_Y;
 };

void foo ( A & val )
 {
   cout << val;
 }

int main ( void )
 {
   B test ( 55, 72 );

   foo ( test );
   return 0;
 }