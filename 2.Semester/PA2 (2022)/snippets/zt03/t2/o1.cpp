#include <iostream>
using namespace std;

class A
 {
   public:
  //  abstract class can have constructor, which do nothing
  // it even may have some members, that may be initialized
  // Which make sense, if we possible want to have some 
  // constants
             A ( void ) 
             : m_X (25)
            //  this output also is valid.
              { cout << m_X; cout << *this;  }
    virtual ~A ( void ) { } 
    virtual void print ( ostream & os ) const = 0;
    // this friend function is also OK. We can call and use everything
    // ... except pure virtual function. Such function cannot be called
    // and will create an error
    friend ostream & operator << ( ostream & os, const A & x )
     { /* x . print ( os ) ;*/ return os; }
      int m_X;
 };

class B : public A
 {
   public:
            B ( int x ) { m_X = x; }
    virtual void print ( ostream & os ) const { os << "B:" << m_X;
    // that prints A::m_X initialize in its own class...
        os << A::m_X; }
   private:
    int m_X;
 };

int main ( void )
 {
   B test ( 59 );
   test.print(cout);
   return 0;
 }