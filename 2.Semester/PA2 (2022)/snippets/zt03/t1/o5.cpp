#include <iostream>
using namespace std;

class A
 {
   public:
          A ( int x ) { m_X = x; }
    void print ( void ) const { cout << m_X; }
   private: 
    int m_X;
 };

class B : public A
 {
   public:
          B ( int x, int y ) : A ( x ) { m_Y = y; }
    void print ( void ) const { A::print (); cout << m_Y; }
   private: 
    int m_Y;
 };

void foo ( A val )
 {
   val . print ( );
 }

int main ( void )
 {
   B test ( 6, 20 );

   foo ( test );
   return 0;
 }