#include <iostream>
using namespace std;

int main (){
  int arr[10] = {1,2,3,4,5,6,7,8,9,10};
  
  int * ptr = arr + 3;
  cout << *ptr << endl;

  int ** data = new int * [10];
  int * x0 = new int (10), * x1 = new int (20) , * x2 = new int (30);
  data[0] = x0;
  data[1] = x1;
  data[2] = x2;

  int * p1 = x0;
  cout << "p1 points to int : val : "<< *p1 << endl;
  // cout << *(&p1 + 1) << endl; // bad, p1 has its own address on stack
  // and we cannot change its address to &x0, because it is impossible,
  // just only because this address is already taken.

  int ** p2 = &x0; // points to x0, which points to 10.
  cout << **p2 << endl; // ok, p2 -> x0 -> 10
  //cout << **(p2 + 1) << endl;  // ERROR - trying to access unknown address

  int ** p3 = data;
  cout << **p3 << " " << **(p3 + 1) << " " << **(p3 + 2)  << endl;
  // OUTPUT : 10 20 30


  delete [] data;
  delete x0;
  delete x1;
  delete x2;
  return 0;
}