#include <iostream>
using namespace std;

class A
 {
   public:
  //  but... Well, i remember, that defaults are overridden by base class
          A ( int x = 42 ) { m_X = x; }
    void print ( void ) const { cout << m_X; }
   private: 
    int m_X;
 };

class B : public A
 {
   public:
          B ( int x, int y ) { m_Y = y; }
    void print ( void ) const { A::print (); cout << m_Y; }
   private: 
    int m_Y;
 };

void foo ( B & val )
 {
   val . print ( );
 }

int main ( void )
 {
   B test ( 85, 48 );

   foo ( test );
   return 0;
 }