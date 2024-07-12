
#include <iostream>
using namespace std;

template < typename T >
T max ( T x, T y){
  return x > y ? x : y;
}

int main () {
  cout << ::max(10,10) << endl;
  cout << ::max(10, 10.23 ) << endl;
  cout << ::max(10,10l) << endl;
  cout << ::max(10l,10) << endl;


  return 0;
}