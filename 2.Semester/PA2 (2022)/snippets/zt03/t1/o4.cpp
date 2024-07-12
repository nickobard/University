#include <iostream>
using namespace std;

class A
 {
   public:
             A ( void ) { cout << *this; }
    virtual ~A ( void ) { } 
    virtual void print ( ostream & os ) const { os << "A:"; }
    friend ostream & operator << ( ostream & os, const A & x )
     { x . print ( os ); return os; }
 };

class B : public A
 {
   public:
            B ( int x ) : m_X ( x ) { cout << *this; }
    virtual void print ( ostream & os ) const { os << "B:" << m_X; }
   private:
    int m_X;
 };

int main ( void )
 {
  //  within the construction is printed B usin operator <<,
  // which is defined only using function, which takes A class.
  // Dynamic binding will be applied. Therefore, will be using the B::print overriden function.
  // But before that all, the A class will be constructed, whill will
  // print first self version
   B test ( 32 );
   return 0;
 }