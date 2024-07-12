#include <iostream>
using namespace std;

class A
 {
   public:
             A ( int x ) { m_X = x; }
    virtual ~A ( void ) { } 
    virtual void print ( void ) const { cout << m_X; }
   private: 
    int m_X;
 };
// That should be public. Otherwise cannot do conversion from B to A.
class B : public A
 {
   public:
          B ( int x, int y ) : A ( x ) { m_Y = y; }
          // here we override the print function.
    virtual void print ( void ) const override { A::print (); cout << m_Y; }
   private: 
    int m_Y;
 };

void foo ( A val )
 {
   val . print ( );
 }

int main ( void )
 {
   B test ( 11, 28 );
// cannot make conversion from D to B, because the private access level
// Otherwise if that was public, test would be memberwised copied
   foo ( test );
   test.print();
   return 0;
 }