#include <iostream>
using namespace std;
// this typedef is global. It is seen in the whole program.
// because it belongs to this namespace
typedef int number;

number foo (){
  // base doesn't exist in this namespace
  // base a = 25;
  return 25;
}

int main(){
  // all those are local here
  typedef number base, my_int, * base_ptr;
  // number is an int.
  // all aliases have different color
  number num  = 25;
  base_ptr ptr = &num; // base_ptr is a pointer to the number *,
  // which is int *
  // suppose, that can be wrapped arount many many times
  typedef base_ptr *base_db;
  base_db db = &ptr;
  // base_db is a base_ptr * which is number ** which is int **.
  // And that is it!
  typedef number &base_ref;
  base_ref ref = num;
  // here base_ref is number & type, which is int & which is reference to int

  // it is important to understand, that the type aliases are not
  // new types, they are just another names.
  return 0;
}