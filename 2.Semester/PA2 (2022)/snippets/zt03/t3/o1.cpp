#include <iostream>
using namespace std;


class A
{
  public:
    A ( int x = 12314 ) : m_X ( new int ( x ) ) { }
    A ( const A & src ) : m_X ( new int ( *src . m_X ) ) { }
    virtual ~A ( void ) { delete m_X; }
    virtual void print ( void ) const { cout << *m_X; }
  private: 
    int *m_X;
};

class B : public A
{
  public:
    B ( int x, int y ) : A ( x ), m_Y ( new int ( y ) ) { }
    B ( const B & src ) : A ( 231 ), m_Y ( new int ( *src.m_Y ) ) { }   
    virtual ~B ( void ) { delete m_Y; }
    virtual void print ( void ) const { A::print (); cout << *m_Y; }
  private: 
    int *m_Y;
};
// Here we call copy constructor to create B val... Therefore copy constructor is used
void foo ( const B val )
{
  val . print ( );
}

int main ( void )
{
  B test ( 63, 58 );

  foo ( test );
  return 0;
}