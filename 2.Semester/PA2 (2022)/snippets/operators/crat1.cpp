#include <iostream>
#include <numeric>
#include <cmath>
#include <sstream>
using namespace std;

class CRat {
  public:
    explicit CRat(int n, int d);
    CRat operator + ( const CRat rv) const;
    //CRat &operator - (void); // this is bad, becuase as with the 
    // previous example we don't want to change our operand.
    // Thus it should not be reference. It should be new value.
    CRat operator- (void) const;
    CRat &operator+= (const CRat rval); // Here it is OK to use 
    // reference
    CRat &operator-= (const CRat rval);

    friend ostream &operator << (ostream &os, const CRat val);
    friend istream &operator >> (istream &is, CRat &val);

    explicit operator double ( void ) const{
      return (double) m_N/m_D;
    }

    void printRat(){
      cout << m_N << "/" << m_D << endl;
    }
  private:
    CRat normalized ( CRat a ) const {
      int div = std::gcd(a.m_N, a.m_D);
      //a.printRat();
      //cout << div << endl;
      a.m_N /= div;
      a.m_D /= div;
      return a;
    }
    int m_N, m_D;
};

CRat::CRat(int n = 0, int d = 1)
: m_N(n),
  m_D(d)
  {}

ostream &operator << (ostream &os, const CRat val){
  os << val.m_N << "/" << val.m_D;
  return os;
}

istream &operator >> (istream &is, CRat &val){
  char dummy;
  int n, d;
  if ( ! (is >> n >> dummy >> d )
       || dummy != '/'
       || d == 0 )
        {
          is.setstate(ios::failbit);
          return is;
        }
        val.m_N = n;
        val . m_D = d;
        return is;
}


CRat CRat::operator+ ( const CRat rv) const {
  return normalized(CRat(m_N * rv.m_D + rv.m_N * m_D, m_D * rv.m_D));
}
CRat CRat::operator- (void) const{
  return CRat(-m_N, m_D); // because of the explicit constructor cannot
  // write just { -m_N, m_D}
}
CRat &CRat::operator+= (const CRat rv){
  return *this = normalized(CRat(m_N * rv.m_D + rv.m_N * m_D, m_D * rv.m_D));
}
CRat &CRat::operator-=(const CRat rv){
  return  *this += -rv;
}


int main (){

  CRat a;
  CRat b (2,5), c (6,7);
  CRat d (1,3), f(1,3);

  // CRat CRat::operator+ (CRat &rv) const {
  // ...
  // a = b + c + (d + f); not valid - because after evaluating b + c
  // the rvalue of (d + f) is const or temporary - not variable, but
  // unnamed object, to which we cannot write, stored in the registers.
  // Becuase we cannot write to it, it should be const. Otherwise it 
  // would be a problem.
  // a = b + c + d + f - is OK at this point, becuase each rvalue isn't 
  // a const


  // CRat operator + (const CRat *rv) const;
  // a = (b + &c) + (&(d + &f)); // ERROR - taking address of rvalue.
  // that rvalue is const. Because that is not string literal, it behaves
  // as numeric literal. And from those we cannot take addresses. Even
  // const addresses. That is where references wins pointers.
  // const int * ptr = &10; //Not possible

  // CRat operator + (const CRat &rv) const; 
  // rvalue rv as reference will have same memory - 8 bytes as two ints.
  // but the passing by reference will do more instructions - derefence,
  // so it is a little bit complexier, that just plain copying.

  a = b + c + (d + f);
  a = -a;

  CRat y (5);
  y -= CRat(2);
  // because of the explicit constructor cannot write y -= 2;
  cout << y << endl;

  istringstream iss ("10/5");
  iss >> y;
  cout << y << endl;

  CRat t (2,3);
  double dbl = (double) t; // double dbl = t; //ERROR, should be explicit
  cout << dbl << endl;
  return 0;
}