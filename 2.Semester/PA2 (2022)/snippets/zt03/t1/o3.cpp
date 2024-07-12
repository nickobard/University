#include <iostream>
using namespace std;

class A
{
  public:
    A ( int x = 66 ) : m_X ( new int ( x ) ) { }
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
    B ( const B & src ) : A ( src ), m_Y ( new int ( *src.m_Y ) ) { }   
    ~B ( void ) { delete m_Y; }
    virtual void print ( void ) const { A::print (); cout << *m_Y; }
  private: 
    int *m_Y;
};

void foo ( A * val )
{
  val -> print ( );
  delete val;  
}

int main ( void )
{
  foo ( new B ( 39, 62 ) );
  return 0;
}