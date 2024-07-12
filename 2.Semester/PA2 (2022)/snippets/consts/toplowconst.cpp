#include <iostream>
using namespace std;

int main (){
  int i = 42;
  const int * ptr = &i;
  //*ptr = 69; // const is low-level, we can change ptr value
  int x = 69;
  ptr = &x;
  cout << *ptr << endl;
  int * const ptr2 = &i; // const is top-level, can change only dereferenced value
  *ptr2 = 69;
  cout << i << endl;
  const int * const ptr3 = &x; // both top-level and low-level
  // only for read.
  cout << *ptr3 << endl;
}